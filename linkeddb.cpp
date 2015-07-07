#include"linkeddb.h"

LinkedDB::LinkedDB(){
    load();
}

LinkedDB::~LinkedDB(){
    users.clear();
}

//non richiamo find poichè dovrei creare un oggetto User che è più dispendioso di un bool
void LinkedDB::addUser(User* u){
    bool isIn = false;
    for(std::list<SmartUser>::const_iterator it = users.begin(); it != users.end() && !isIn; ++it) {
        if(((*it)->account()->username()) == (u->account()->username())){
            isIn = true;
            throw MyExc(username, "This username is already in use!");
        }
    }
    if(!isIn) users.push_back(SmartUser(u));
}
void LinkedDB::removeUser(const Username& us){
    for(std::list<SmartUser>::iterator it = users.begin(); it != users.end(); ++it) {
        // Rimuovo prima l'user da tutte le amicizie
        try{
            (*it)->getNet()->removeUser(us);
        }
        catch(MyExc e){
            //non faccio nulla, semplicemente non l'ho trovato
        }
        //ora rimuovo l'utente vero e proprio
        if ((*it)->account()->username() == us)
            it = users.erase(it);
    }
}

void LinkedDB::load(){
    QString val;
    QFile file;
    file.setFileName("db.json");
    if (!file.exists()) {
        throw MyExc(database, "db file does not exists!");
    }
    if (!file.open(QIODevice::ReadOnly)) {
        throw MyExc(database, "problem reading the file!");
    }
    else{
       // QTextStream(stdout)<<"\n loading file!\n";                                                    //solo x debug
    }
    val = file.readAll();
    file.close();

    //procedo con la lettura del file
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject all_json = doc.object();
    QJsonValue all_users = all_json["users"];                      //get users
    QJsonArray users_array = all_users.toArray();                  //transform into an array
    for(QJsonArray::const_iterator it = users_array.begin(); it!=users_array.end(); ++it){
        QJsonValue test = *it;
        QJsonObject obj = test.toObject();
        QJsonValue user = obj["username"];
        QJsonValue pass = obj["password"];
        Username us( user.toString().toStdString() , pass.toString().toStdString());

        QJsonValue name = obj["name"];
        QJsonValue surname = obj["surname"];
        QJsonValue email = obj["email"];
        QJsonValue address = obj["address"];
        QJsonValue tel = obj["telephon"];
        QVariant birthday = QVariant(obj["birthday"]);
        QDate tmp = QDate::fromString(birthday.toString(),"yyyy.MM.dd");

        Info info(tmp, name.toString().toStdString(),surname.toString().toStdString(),email.toString().toStdString(),address.toString().toStdString(),tel.toString().toStdString());
        Info* p_info;
        QJsonArray _skills = obj["skills"].toArray();
        for(QJsonArray::const_iterator skillIt = _skills.begin(); skillIt!=_skills.end();++skillIt){
            info.addSkill((*skillIt).toString().toStdString());
        }
        QJsonArray _languages = obj["languages"].toArray();
        for(QJsonArray::const_iterator langIt = _languages.begin(); langIt!=_languages.end();++langIt){
            info.addLanguage((*langIt).toString().toStdString());
        }
        QJsonArray _interests = obj["interests"].toArray();
        for(QJsonArray::const_iterator intIt = _interests.begin(); intIt!=_interests.end();++intIt){
            info.addInterest((*intIt).toString().toStdString());
        }
        QJsonArray _experiences = obj["experiences"].toArray();
        for(QJsonArray::const_iterator expIt = _experiences.begin(); expIt!=_experiences.end();++expIt){
            QJsonObject _exp = (*expIt).toObject();
            std::string loc = _exp["location"].toString().toStdString();
            std::string role = _exp["role"].toString().toStdString();
            QVariant _from = QVariant(_exp["from"]);
            QVariant _to = QVariant(_exp["to"]);
            QDate from = QDate::fromString(_from.toString(),"yyyy.MM.dd");
            QDate to = QDate::fromString(_to.toString(),"yyyy.MM.dd");
            Experience tmp_exp(loc, role, from, to);
            info.addExperience(tmp_exp);
        }
        std::list<Experience> eee=info.getExperiences();
//for(std::list<Experience>::const_iterator asd=eee.begin(); asd!=eee.end();++asd)
//std::cout<<(*asd)->getLocation();
        p_info=&info;
        accountType _type = static_cast<accountType>(obj["accountType"].toInt());
        Account acc(p_info ,us, _type);
        acc.setAvatar(obj["avatarPath"].toString().toStdString());
        User* _user = NULL;
        SmartUser smus;
        switch(_type){
            case 0:
                _user = new BasicUser(&acc);
            break;
            case 1:
                _user = new BusinessUser(&acc);
            break;
            case 2:
                _user = new ExecutiveUser(&acc);
            break;
        }
		  smus = _user;


//QTextStream(stdout)<<QString::fromStdString(smus->account()->username().getLogin())<<" ";
        users.push_back(smus);
    }

    //read the net of all users
    for(std::list<SmartUser>::const_iterator it = users.begin(); it!= users.end(); ++it){
        for(int i=0; i<users_array.size(); ++i){
            QJsonObject obj = users_array[i].toObject();
            QJsonArray friends = obj["friends"].toArray();
            if((*it)->account()->username().getLogin() == obj["username"].toString().toStdString()) {
//QTextStream(stdout)<<"reading friends "<<obj["username"].toString()<<"\n";
                for(int k = 0; k < friends.size(); ++k){
                    Username tmp_user(friends[k].toString().toStdString(), "");
                    (*it)->addFriend(find(tmp_user));
                }
            }
        }
    }
}

void LinkedDB::save() const{
    QFile db("db.json");
    if (!db.open(QIODevice::WriteOnly)) {
        throw MyExc(database, "can't open DB!");
    }
    else{ //just for debug purpose
//QTextStream(stdout)<<"\n saving file! \n";                                          //solo per debug
    }
    if(!db.exists())
        throw MyExc(database, "DB file does not exists!");

    //start the real saving
    QTextStream stream( &db );

    //saving of all users and their relative informations
    QJsonArray json_users;
    QJsonObject users_wrapper;
    for(std::list<SmartUser>::const_iterator it = users.begin(); it!= users.end() ; ++it){

        //creating the user
        QJsonObject json_user;
        QString tmp = QString::fromUtf8((*it)->account()->username().getPassword().c_str());
        json_user["password"]= tmp;
        tmp = QString::fromUtf8((*it)->account()->username().getLogin().c_str());
        json_user["username"]= tmp;


        std::map<std::string,std::string> infos = (*it)->account()->getInfo()->getAllInfo();
        json_user["name"]    =  QString::fromUtf8(infos["name"].c_str());
        json_user["surname"] =  QString::fromUtf8(infos["surname"].c_str());
        json_user["email"]   =  QString::fromUtf8(infos["email"].c_str());
        json_user["address"] =  QString::fromUtf8(infos["address"].c_str());
        json_user["telephon"]=  QString::fromUtf8(infos["telephon"].c_str());
       
        QDate b((*it)->account()->getInfo()->getBirthday());
        json_user["birthday"]=  b.toString("yyyy.MM.dd");
        json_user["avatarPath"] = QString::fromUtf8((*it)->account()->getAvatar().c_str());
        json_user["accountType"] = (*it)->account()->getType();

        //aggiungo tutte le skills, languages and interests
        std::list<string> temp_list= (*it)->account()->getInfo()->getSkills();
        QJsonArray tmp_skills;
        for(std::list<string>::const_iterator tmp_it = temp_list.begin(); tmp_it != temp_list.end(); ++tmp_it){
            tmp_skills.push_back(QJsonValue(QString::fromUtf8((*tmp_it).c_str())));
        }
        json_user["skills"] = tmp_skills;
        temp_list = (*it)->account()->getInfo()->getLanguages();
        QJsonArray tmp_languages;
        for(std::list<string>::const_iterator tmp_it = temp_list.begin(); tmp_it != temp_list.end(); ++tmp_it){
            tmp_languages.push_back(QJsonValue(QString::fromUtf8((*tmp_it).c_str())));
        }
        json_user["languages"] = tmp_languages;
        temp_list = (*it)->account()->getInfo()->getInterests();
        QJsonArray tmp_interests;
        for(std::list<string>::const_iterator tmp_it = temp_list.begin(); tmp_it != temp_list.end(); ++tmp_it){
            tmp_interests.push_back(QJsonValue(QString::fromUtf8((*tmp_it).c_str())));
        }
        json_user["interests"] = tmp_interests;
        std::list<Experience> temp_exp=(*it)->account()->getInfo()->getExperiences();
        QJsonArray tmp_exp;
        for(std::list<Experience>::const_iterator tmp_it = temp_exp.begin(); tmp_it != temp_exp.end(); ++tmp_it){
            QJsonObject ex;
            ex["location"]=QJsonValue(QString::fromUtf8((tmp_it->getLocation()).c_str()));
            ex["role"]=QJsonValue(QString::fromUtf8(((tmp_it)->getRole()).c_str()));
            ex["from"]=QJsonValue((tmp_it)->getFrom().toString("yyyy.MM.dd"));
            ex["to"]=QJsonValue((tmp_it)->getTo().toString("yyyy.MM.dd"));
            tmp_exp.push_back(ex);
        }
        json_user["experiences"] = tmp_exp;


        //adding the friends net
        QJsonArray j_friends;
        std::list<SmartUser> friends = (*it)->getNet()->getUsers();
        for(std::list<SmartUser>::const_iterator f_it = friends.begin(); f_it != friends.end(); ++f_it){
//QTextStream(stdout)<<"saving friends of "<<tmp<<": ";
//QTextStream(stdout)<<QString::fromStdString(f_it->getLogin())<<"\n";
            j_friends.append(QString::fromStdString((*f_it)->account()->username().getLogin()));
        }
        json_user["friends"] = j_friends;
        json_users.push_back(json_user);
    }
    users_wrapper["users"]=json_users;

    //aggiungo l'admin
    QJsonObject admin;
    admin["username"] = QString("admin");
    admin["password"] = QString("password");
    users_wrapper["admin"]= admin;
    QJsonDocument doc(users_wrapper);
    QByteArray users_save = doc.toJson();
    stream << users_save;
    db.close();
}

Username LinkedDB::getAdmin() const{
    QString val;
    QFile file;
    file.setFileName("db.json");
    if (!file.exists()) {
        throw MyExc(database, "db file does not exists!");
    }
    if (!file.open(QIODevice::ReadOnly)) {
        throw MyExc(database, "problem reading the file!");
    }
    val = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject all_json = doc.object();
    QJsonObject admin = all_json["admin"].toObject();
    return (Username(admin["username"].toString().toStdString(), admin["password"].toString().toStdString()));
}

User* LinkedDB::find(const Username &u) const{
    for(std::list<SmartUser>::const_iterator it = users.begin(); it != users.end(); ++it) {
        if(((*it)->account()->username()) == u){
//QTextStream(stdout)<<"utente trovato \n";
//QTextStream(stdout)<<QString::fromStdString((*it)->account()->username().getLogin())<<" trovato \n";
            return &(**it);
        }
    }
//QTextStream(stdout)<<"utente NON trovato \n";
    return NULL;
}

bool LinkedDB::isValidCredentials(const Username& u) const{
    std::string _user = u.getLogin();
    std::string _pass = u.getPassword();

    QString val;
    QFile file;
    file.setFileName("db.json");
    if (!file.exists()) {
        throw MyExc(database, "DB file does not exists!");
    }
    if (!file.open(QIODevice::ReadOnly)) {
        throw MyExc(database, "an error as occurred while reading the DB!");
    }
    else{
//QTextStream(stdout)<<"loading file!\n";                 //solo x debug
    }
    val = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject all_json = doc.object();
    QJsonValue all_users = all_json["users"];
    QJsonArray users_array = all_users.toArray();
    for(QJsonArray::const_iterator it = users_array.begin(); it!=users_array.end(); ++it){
        QJsonValue test = *it;
        QJsonObject obj = test.toObject();
        QJsonValue user = obj["username"];
        QJsonValue pass = obj["password"];

        if(_user == user.toString().toStdString() && _pass == pass.toString().toStdString()){
            return true;
        }
    }
    return false;
}

int LinkedDB::size() const{
    return users.size();
}

std::list<SmartUser> LinkedDB::getUsersDB()const{
    return users;
}

std::list<SmartUser>::const_iterator LinkedDB::begin() const{
    return users.begin();
}
std::list<SmartUser>::const_iterator LinkedDB::end() const{
    return users.end();
}
