#include "gui_user.h"

Gui_User::Gui_User(const Username& u, bool isAVisit, Username* friendToVisit,  QWidget* parent): client(new LinkedClient(u)) , _visit(isAVisit), QWidget(parent){
    if(_visit){
        userCaller = *friendToVisit;
        visitCallerClient = new LinkedClient(userCaller);
    }
    this->setWindowTitle("Welcome to LinQedIn "+QString::fromStdString(u.getLogin()));
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.8);
    this->setFixedSize(this->size());

    counter = 0;
    cfriend = 0;
    QFont font;
    font.setBold(true);
    font.setPointSize(11);

    int height = this->height();
    int width  = this->width();

    QWidget* top = new QWidget();
    top->setFixedSize((width-100),75);
    QHBoxLayout* topView = new QHBoxLayout();
    QPushButton* logoutB = new QPushButton("Logout",this);
        connect(logoutB,SIGNAL(clicked()),this,SLOT(logout()));
    QPushButton* resumeB = new QPushButton("Return", this);
        connect(resumeB,SIGNAL(clicked()),this,SLOT(resumeUserWindow()));
    if(_visit){
        logoutB->setVisible(false);
    }
    else{
        resumeB->setVisible(false);
    }
    logoutB->setAutoDefault(true);
    //QPushButton* msgB = new QPushButton("Messaggi",this);
    //msgB->setFixedWidth(100);
    //QPushButton* groupsB = new QPushButton("Gruppi",this);
    //groupsB->setFixedWidth(100);
    QPushButton* upgradeB = new QPushButton("Upgrade!");
    upgradeB->setFixedWidth(100);
    connect(upgradeB, SIGNAL(clicked()), this, SLOT(editSubscript()));
    if(!_visit)
        topView->addWidget(  upgradeB, 0, Qt::AlignLeft);
    //topView->addWidget(   msgB, 0, Qt::AlignLeft);
    //topView->addWidget(groupsB, 0, Qt::AlignLeft);
    topView->addStretch(1);
    topView->addWidget(logoutB, 0, Qt::AlignLeft);
    topView->addWidget(resumeB, 0, Qt::AlignLeft);
    top->setLayout(topView);

    QWidget* first = new QWidget();
    first->setFixedSize(width/5,height-100);
    firstCol = new QVBoxLayout();
    firstCol->setSpacing(10);
    //set client avatar
    if(client->getAvatar() != "")
        img= new QLabel("<img src='"+QString::fromStdString(client->getAvatar())+"' />",this);
    else
        img= new QLabel("<img src='images/default.jpg' />",this);
    img->setFixedSize(200,200);
    img->setObjectName("avatar");
    if(!_visit)
        img->installEventFilter(this);
    firstCol->addWidget(img,0,Qt::AlignCenter);
    QLabel* usernameL = new QLabel(QString::fromStdString(client->getUsername().getLogin()),this);
    usernameL->setObjectName("username");
    QLabel* passwordL = new QLabel(QString::fromStdString(client->getUsername().getPassword()),this);
    passwordL->setObjectName("password");
    QLabel* nameL =     new QLabel(QString::fromStdString(client->getInfo()->getName()),this);
    nameL->setObjectName("name");
    QLabel* surnameL =  new QLabel(QString::fromStdString(client->getInfo()->getSurname()),this);
    surnameL->setObjectName("surname");
    QLabel* birthL =    new QLabel((client->getInfo()->getBirthday().toString("yyyy.MM.dd")),this);
    birthL->setObjectName("birth");
    QLabel* addressL =  new QLabel(QString::fromStdString(client->getInfo()->getAddress()),this);
    addressL->setObjectName("address");
    QLabel* emailL =    new QLabel(QString::fromStdString(client->getInfo()->getEmail()),this);
    emailL->setObjectName("email");
    QLabel* telL =      new QLabel(QString::fromStdString(client->getInfo()->getTel()),this);
    telL->setObjectName("telephon");
    QPushButton* editInfo;
    if(!_visit){
        editInfo = new QPushButton("Edit Info");
        editInfo->setObjectName("editInfo Button");
        connect(editInfo, SIGNAL(clicked()), this, SLOT(editInfo()) );
    }
    usernameL-> setFont(font);
    passwordL-> setFont(font);
    nameL->     setFont(font);
    surnameL->  setFont(font);
    birthL->    setFont(font);
    addressL->  setFont(font);
    emailL->    setFont(font);
    telL->      setFont(font);
    firstCol->addWidget(usernameL,0,Qt::AlignCenter);
    firstCol->addWidget(passwordL,0,Qt::AlignCenter);
    firstCol->addWidget(nameL,0,Qt::AlignCenter);
    firstCol->addWidget(surnameL,0,Qt::AlignCenter);
    firstCol->addWidget(birthL,0,Qt::AlignCenter);
    firstCol->addWidget(addressL,0,Qt::AlignCenter);
    firstCol->addWidget(emailL,0,Qt::AlignCenter);
    firstCol->addWidget(telL,0,Qt::AlignCenter);
    if(!_visit){
        firstCol->addWidget(editInfo, 0, Qt::AlignCenter);
    }
    first->setLayout(firstCol);

    QWidget* second = new QWidget();
    second->setFixedSize(width/4,height-100);
    QVBoxLayout* secondCol = new QVBoxLayout();
    secondCol->setSpacing(10);

    QPixmap pixmap("images/add_button_mini.gif");
    QIcon ButtonIcon(pixmap);

    // Skills part
    skillslayout = new QVBoxLayout();
    skillslayout->setSpacing(10);
    QLabel* skillsL =   new QLabel("Skills",this);
    skillsL->setFont(font);
    skillslayout->addWidget(skillsL);

    if(!_visit){
        //line edit to add skills
        QHBoxLayout* tmpSlayout = new QHBoxLayout();
        skilltoadd = new QLineEdit();
        QPushButton* addskillbut = new QPushButton();
        addskillbut->setFixedSize(17,17);
        addskillbut->setFlat(true);
        addskillbut->setIcon(ButtonIcon);
        addskillbut->setIconSize(pixmap.rect().size());
        connect(addskillbut, SIGNAL(clicked()),this , SLOT(addSkill()));
        connect(skilltoadd, SIGNAL(returnPressed()),this, SLOT(addSkill()));
        tmpSlayout->addWidget(skilltoadd, 1 , Qt::AlignLeft);
        tmpSlayout->addWidget(addskillbut,0,Qt::AlignCenter);
        skillslayout->addLayout(tmpSlayout);
    }
    //get all the user skills
    std::list<string> skilllist = client->getInfo()->getSkills();
    for(std::list<string>::const_iterator it = skilllist.begin(); it!=skilllist.end(); ++it){
        addSkillRow(QString::fromStdString(*it), skillslayout);
    }
    secondCol->addLayout(skillslayout);

    //languages part
    langslayout = new QVBoxLayout();
    langslayout->setSpacing(10);
    QLabel* langsL =   new QLabel("Languages",this);
    langsL->setFont(font);
    langslayout->addWidget(langsL);
    if(!_visit){
        //lineedit to add langs
        QHBoxLayout* tmpLlayout = new QHBoxLayout();
        langtoadd = new QLineEdit();
        QPushButton* addlangbut = new QPushButton();
        addlangbut->setFixedSize(20,20);
        addlangbut->setFlat(true);
        addlangbut->setIcon(ButtonIcon);
        addlangbut->setIconSize(pixmap.rect().size());
        connect(addlangbut, SIGNAL(clicked()), this, SLOT(addLang()));
        connect(langtoadd, SIGNAL(returnPressed()),this, SLOT(addLang()));
        tmpLlayout->addWidget(langtoadd, 1 , Qt::AlignLeft);
        tmpLlayout->addWidget(addlangbut, 0 , Qt::AlignCenter);
        langslayout->addLayout(tmpLlayout);
    }
    std::list<string> langslist = client->getInfo()->getLanguages();
    for(std::list<string>::const_iterator it = langslist.begin(); it!=langslist.end(); ++it){
        addLangRow(QString::fromStdString(*it), langslayout);
    }
    secondCol->addLayout(langslayout);
    second->setLayout(secondCol);

    QWidget* third = new QWidget();
    third->setFixedSize(width/4,height-100);
    QVBoxLayout* thirdCol = new QVBoxLayout();
    //add interests
    interestslayout = new QVBoxLayout();
    interestslayout->setSpacing(10);
    QLabel* interestsL =   new QLabel("Interests",this);
    interestsL->setFont(font);
    interestslayout->addWidget(interestsL);
    if(!_visit){
        //lineedit to add langs
        QHBoxLayout* tmpIlayout = new QHBoxLayout();
        interesttoadd = new QLineEdit();
        QPushButton* addinterestbut = new QPushButton();
        addinterestbut->setFixedSize(15,15);
        addinterestbut->setFlat(true);
        addinterestbut->setIcon(ButtonIcon);
        addinterestbut->setIconSize(pixmap.rect().size());
        connect(addinterestbut, SIGNAL(clicked()), this, SLOT(addInterest()));
        connect(interesttoadd, SIGNAL(returnPressed()),this, SLOT(addInterest()));
        tmpIlayout->addWidget(interesttoadd, 1 , Qt::AlignLeft);
        tmpIlayout->addWidget(addinterestbut, 0 , Qt::AlignCenter);
        interestslayout->addLayout(tmpIlayout);
    }
    std::list<string> interestslist = client->getInfo()->getInterests();
    for(std::list<string>::const_iterator it = interestslist.begin(); it!=interestslist.end(); ++it){
        addLangRow(QString::fromStdString(*it), interestslayout);
    }
    thirdCol->addLayout(interestslayout);

    //add experiences
    explayout = new QVBoxLayout();
    explayout->setSpacing(10);
    QLabel* expL = new QLabel("Working Experiences",this);
    expL->setFont(font);
    explayout->addWidget(expL);
    if(!_visit){
        QGridLayout* grid = new QGridLayout();
        QLabel* whereL = new QLabel("Where",this);
        QLabel* roleL =  new QLabel("Role",this);
        QLabel* fromL =  new QLabel("From",this);
        QLabel* toL =    new QLabel("To",this);
        where = new QLineEdit();
        role =  new QLineEdit();
        from =  new QDateEdit();
        to =    new QDateEdit();
        QPushButton* addexp = new QPushButton();
        addexp->setFixedSize(16,16);
        addexp->setFlat(true);
        addexp->setIcon(ButtonIcon);
        addexp->setIconSize(pixmap.rect().size());
        connect(addexp, SIGNAL(clicked()), this, SLOT(addExp()));
        grid->addWidget(whereL, 0,0,1,1,Qt::AlignLeft);
        grid->addWidget(roleL,  1,0,1,1,Qt::AlignLeft);
        grid->addWidget(fromL,  0,2,1,1,Qt::AlignLeft);
        grid->addWidget(toL,    1,2,1,1,Qt::AlignLeft);
        grid->addWidget(where,  0,1,1,1,Qt::AlignLeft);
        grid->addWidget(role,   1,1,1,1,Qt::AlignLeft);
        grid->addWidget(from,   0,3,1,1,Qt::AlignLeft);
        grid->addWidget(to,     1,3,1,1,Qt::AlignLeft);
        grid->addWidget(addexp, 2,3,1,1,Qt::AlignRight);
        explayout->addLayout(grid);
    }
    thirdCol->addLayout(explayout);

    //read and write all the user experiences
    std::list<Experience> explist = client->getInfo()->getExperiences();
    for(std::list<Experience>::const_iterator it = explist.begin(); it!=explist.end(); ++it){
        addExpRow(*it , explayout);
    }

    third->setLayout(thirdCol);

    QWidget* fourth = new QWidget();
    fourth->setFixedSize(width/6,height-100);
    QVBoxLayout* fourthCol = new QVBoxLayout();
    QHBoxLayout* searchLayout = new QHBoxLayout();
    if(!_visit){
        searchBar = new QLineEdit();
        connect(searchBar,SIGNAL(returnPressed()), this, SLOT(search()));
        QPushButton* _resetSearch = new QPushButton();
		  _resetSearch->setFlat(true);
		  QPixmap pixmap("images/delete_button_mini.png");
	     QIcon ButtonIcon(pixmap);
		  _resetSearch->setIcon(ButtonIcon);
        _resetSearch->setFixedSize(15,15);
        connect(_resetSearch, SIGNAL(clicked()),this, SLOT(resetSearch()));
        searchLayout->addWidget(searchBar, 0 , Qt::AlignLeft);
        searchLayout->addWidget(_resetSearch, 0 , Qt::AlignRight);
        fourthCol->addLayout(searchLayout);
    }
    //add friend list
    friendslayout = new QVBoxLayout();
    if(!_visit){
        LinkedNet* friends = client->getNet();
        std::list<SmartUser> friendsList = friends->getUsers();
        QLabel* friendsL = new QLabel("Friends");
        friendsL->setFont(font);
        friendslayout->addWidget(friendsL,0,Qt::AlignCenter);
        for(std::list<SmartUser>::const_iterator it = friendsList.begin(); it != friendsList.end(); ++it){
            addFriendRow(QString::fromStdString((*it)->account()->username().getLogin()),QString::fromStdString((*it)->account()->getInfo()->getName()+" "+(*it)->account()->getInfo()->getSurname()), false);
        }
    }
    else{
        if(visitCallerClient->getAccType()>1){
            QPushButton* addFrBut = new QPushButton("Add this User");
            connect(addFrBut, SIGNAL(clicked()), this, SLOT(addThisFriend()));
            friendslayout->addWidget(addFrBut, 0, Qt::AlignCenter);
        }
    }

    fourthCol->addLayout(friendslayout);
    searchFriendsLayout = new QVBoxLayout();
    fourthCol->addLayout(searchFriendsLayout);
    fourth->setLayout(fourthCol);

    QGridLayout* userLayout = new QGridLayout(this);
    userLayout->addWidget(top, 0, 0, 1, 2, Qt::AlignCenter);
    userLayout->addWidget(first, 1, 0, 9, 1, Qt::AlignLeft);
    userLayout->addWidget(second, 0, 1, 9, 1, Qt::AlignLeft);
    userLayout->addWidget(third, 0, 2, 9, 1, Qt::AlignLeft);
    userLayout->addWidget(fourth, 1, 3, 9, 1, Qt::AlignLeft);
    setLayout(userLayout);
}

void Gui_User::search(){
    if(searchBar->text()!="" ){
        resetSearch();
        std::list<User*> search_results = client->userSearch(searchBar->text().toStdString());
        searchBar->setText("");

        //nascondo la friendlist
//QTextStream(stdout)<<"in friends layout ci sono elementi "<<friendslayout->count()<<"\n";
        hideORshowAllFrom(friendslayout, true);

        //se non ci sono risultati metto un messaggio
        if(search_results.size()==0){
            QLabel* noResults = new QLabel("nessun risutlato trovato!");
            searchFriendsLayout->addWidget(noResults);
        }
        else{
            //sostituisco la friendlist con i risultati relativi alla ricerca
            for(std::list<User*>::const_iterator it = search_results.begin(); it != search_results.end(); ++it) {
                QHBoxLayout* friendl = new QHBoxLayout();
                friend_searched_list.insert(cfriend,friendl);

                QString n_s = QString::fromStdString((*it)->account()->getInfo()->getName());
                n_s.append(" "+QString::fromStdString((*it)->account()->getInfo()->getSurname()));

                //username mi serve per fare client->addFriend
                QLabel* usernameHided  = new QLabel( QString::fromStdString((*it)->account()->username().getLogin()));
                usernameHided->hide();
                QLabel* nome_cognome   = new QLabel(n_s);
                //Executive users can view the profile of a user
                if(client->getAccType() > 1){
                    nome_cognome->setObjectName(usernameHided->text());
                    nome_cognome->installEventFilter(this);
                }
                QPushButton* addFriend = new QPushButton();
                addFriend->setObjectName(QString::number(cfriend));
					 addFriend->setFixedSize(15,15);
					 QPixmap pixmap("images/add_button_mini.gif");
    				 QIcon ButtonIcon(pixmap);
					 addFriend->setIcon(ButtonIcon);
					 addFriend->setFlat(true);
					 addFriend->setIconSize(pixmap.rect().size());
                ++cfriend;

                connect(addFriend, SIGNAL(clicked()), this, SLOT(addFriend()));
                friendl->addWidget(usernameHided);
                friendl->addWidget(nome_cognome);
                friendl->addWidget(addFriend);
                searchFriendsLayout->addLayout(friendl);
            }
        }
    }
    searchBar->setFocus();
}
void Gui_User::resetSearch(){   // NON SO SE SIA GIUSTO DA PROVARE TUTTI I CASI LIMITE

    //if(searchFriendsLayout->count() != 0)
        hideORshowAllFrom(friendslayout, false);

//QTextStream(stdout)<<"\n ho "+QString::number(friendslayout->count())+" amici \n";
//QTextStream(stdout)<<"\n ho "+QString::number(searchFriendsLayout->count())+" risultati \n";

    if(searchFriendsLayout->count() == 0)
        return ;

    clearLayout(searchFriendsLayout, true);
    cfriend = 0;//serve?
}

void Gui_User::hideORshowAllFrom(QLayout* lay, bool hide){
    QLayoutItem* item;
    for(int i = 0; i< lay->count(); ++i){
        item = lay->itemAt(i);
        if(QLayout* childLayout = item->layout()){
//QTextStream(stdout)<<"found a layout, showing it \n";
            hideORshowAllFrom(childLayout, hide);
        }
        else{
            item->widget()->setVisible(!hide);
        }
    }
}

void Gui_User::addFriend(){
    int i = QObject::sender()->objectName().toInt();
    QLayoutItem* item;
    QString _username, _fullname;
//QTextStream(stdout)<<"\n stai cercando di aggiungere agli amici "+QString::number(i);
    bool mustInsert = false;
    while((item=friend_searched_list[i]->takeAt(0)) != NULL){
        QLabel* tmp = dynamic_cast<QLabel*>(item->widget());
        if(tmp)
            if(tmp->isHidden()){
//QTextStream(stdout)<<"stai cercando di aggiugnere "+tmp->text();   //questo è l'username da aggiungere agli amici
                _username = tmp->text();
                User* tmpUser = (client->getUserFromUsername(tmp->text().toStdString()));
                client->getNet()->addUser(tmpUser);
                client->save();
                mustInsert = true;
            }
        if(mustInsert && tmp && !tmp->isHidden()){
//QTextStream(stdout)<<tmp->text(); // si, è fullname
            _fullname = tmp->text();
            addFriendRow(_username, _fullname, true);
        }
        delete item->widget();
        delete item;
    }
    delete friend_searched_list[i];
}

void Gui_User::removeFriend(){
    int i = QObject::sender()->objectName().toInt();
    QLayoutItem* item;
    QString _username;
    while((item=user_list[i]->takeAt(0)) != NULL){
        QLabel* tmp = dynamic_cast<QLabel*>(item->widget());
        if(tmp){
            if(tmp->objectName() != ""){
                //_username = tmp->text(); // mi restituisce fullname non username
                _username = tmp->objectName();
                client->getNet()->removeUser(Username(_username.toStdString()));
                client->save();
//QTextStream(stdout)<<"\nrimosso dagli amici "+_username+"\n";
            }
        }
        delete item->widget();
        delete item;
    }
    delete user_list[i];
}
void Gui_User::addFriendRow(const QString& user_name, const QString& full_name, bool hided){
    QHBoxLayout* tmplayout = new QHBoxLayout();
    user_list.insert(counter,tmplayout);

    //QLabel* usernameHidden = new QLabel(user_name);
    //usernameHidden->hide();
    QLabel* temp = new QLabel(full_name,this);
    //potevo creare una MYLABEL aggiungendoci l'ONCLICK event, ma ho scelto di aggiungere l'evento così
    temp->installEventFilter(this);
    //aggiungo l'username relativo alla persona così da avere l'username univoco per il link alla pagina dell'amico
    temp->setObjectName(user_name);
    QPushButton* removefriend = new QPushButton();
	 removefriend->setFlat(true);
	 QPixmap pixmap("images/delete_button_mini.png");
    QIcon ButtonIcon(pixmap);
	 removefriend->setIcon(ButtonIcon);
    removefriend->setObjectName(QString::number(counter));
    removefriend->setFixedSize(15,15);

    if(hided){
        temp->setVisible(false);
        removefriend->setVisible(false);
    }

    connect(removefriend,SIGNAL(clicked()),this,SLOT(removeFriend()));
    //tmplayout->addWidget(usernameHidden, 0, Qt::AlignLeft);
    tmplayout->addWidget(temp, 0, Qt::AlignLeft);
    tmplayout->addWidget(removefriend, 0, Qt::AlignCenter);
    friendslayout->addLayout(tmplayout);
    ++counter;
}

//function to add a skill with the delete button aggregated
void Gui_User::addSkillRow(QString s, QVBoxLayout* lay){
    QHBoxLayout* tmplayout = new QHBoxLayout();
    user_list.insert(counter,tmplayout);
    QLabel* tmplabel = new QLabel(s);
    QPushButton* tmpbutton = new QPushButton("");
    if(!_visit){
        tmpbutton->setFlat(true);
        QPixmap pixmap("images/delete_button_mini.png");
        QIcon ButtonIcon(pixmap);
        tmpbutton->setIcon(ButtonIcon);
        tmpbutton->setIconSize(pixmap.rect().size());

        tmpbutton->setObjectName(QString::number(counter));
        tmpbutton->setFixedSize(15,15);
        connect(tmpbutton, SIGNAL(clicked()), this, SLOT(removeSkill()));
    }
    tmplayout->addWidget(tmplabel, 1 , Qt::AlignLeft);
    if(!_visit){
        tmplayout->addWidget(tmpbutton,0,Qt::AlignCenter);
    }
    lay->addLayout(tmplayout);
    ++counter;
}
//function to add a language with the delete button aggregated
void Gui_User::addLangRow(QString s, QVBoxLayout* lay){
    QHBoxLayout* tmplayout = new QHBoxLayout();
    user_list.insert(counter,tmplayout);
    QLabel* tmplabel = new QLabel(s);
    QPushButton* tmpbutton = new QPushButton("");
    if(!_visit){
        tmpbutton->setFlat(true);
        QPixmap pixmap("images/delete_button_mini.png");
        QIcon ButtonIcon(pixmap);
        tmpbutton->setIcon(ButtonIcon);
        tmpbutton->setIconSize(pixmap.rect().size());

        tmpbutton->setObjectName(QString::number(counter));
        tmpbutton->setFixedSize(15,15);
        connect(tmpbutton, SIGNAL(clicked()), this, SLOT(removeLang()));
    }
    tmplayout->addWidget(tmplabel, 1 , Qt::AlignLeft);
    if(!_visit)
        tmplayout->addWidget(tmpbutton,0,Qt::AlignCenter);
    lay->addLayout(tmplayout);
    ++counter;
}
//function to add an interest with the delete button aggregated
void Gui_User::addInterestRow(QString s, QVBoxLayout* lay){
    QHBoxLayout* tmplayout = new QHBoxLayout();
    user_list.insert(counter,tmplayout);
    QLabel* tmplabel = new QLabel(s);
    QPushButton* tmpbutton = new QPushButton("");
    if(!_visit){
        tmpbutton->setFlat(true);
        QPixmap pixmap("images/delete_button_mini.png");
        QIcon ButtonIcon(pixmap);
        tmpbutton->setIcon(ButtonIcon);
        tmpbutton->setIconSize(pixmap.rect().size());

        tmpbutton->setObjectName(QString::number(counter));
        tmpbutton->setFixedSize(15,15);
        connect(tmpbutton, SIGNAL(clicked()), this, SLOT(removeInterest()));
    }
    tmplayout->addWidget(tmplabel, 1 , Qt::AlignLeft);
    if(!_visit)
        tmplayout->addWidget(tmpbutton,0,Qt::AlignCenter);
    lay->addLayout(tmplayout);
    ++counter;
}
//function to add an experience with the delete button aggregated
void Gui_User::addExpRow(const Experience &e, QVBoxLayout* lay){
    QHBoxLayout* layout = new QHBoxLayout();
    QGridLayout* tmplayout = new QGridLayout();
    user_list.insert(counter,layout);
    QLabel* tmpwhere = new QLabel("worked at "+QString::fromStdString(e.getLocation()));
    QLabel* tmprole  = new QLabel("role: "+QString::fromStdString(e.getRole()));
    QLabel* tmpfrom  = new QLabel("from "+e.getFrom().toString("yyyy.MM.dd"));
    QLabel* tmpto    = new QLabel("to "+e.getTo().toString("yyyy.MM.dd"));

    QPushButton* tmpbutton = new QPushButton("");
    if(!_visit){
        tmpbutton->setFlat(true);
        QPixmap pixmap("images/delete_button_mini.png");
        QIcon ButtonIcon(pixmap);
        tmpbutton->setIcon(ButtonIcon);
        tmpbutton->setIconSize(pixmap.rect().size());

        tmpbutton->setObjectName(QString::number(counter));
        tmpbutton->setFixedSize(20,20);
        connect(tmpbutton, SIGNAL(clicked()), this, SLOT(removeExp()));
    }
    tmplayout->addWidget(tmpwhere, 0 , 0 ,1,1,Qt::AlignLeft);
    tmplayout->addWidget(tmprole , 1 , 0 ,1,1,Qt::AlignLeft);
    tmplayout->addWidget(tmpfrom , 0 , 1 ,1,1,Qt::AlignLeft);
    tmplayout->addWidget(tmpto   , 1 , 1 ,1,1,Qt::AlignLeft);
    if(!_visit)
        tmplayout->addWidget(tmpbutton, 2,1,1,1,Qt::AlignRight);
    layout->addLayout(tmplayout);
    lay->addLayout(layout);
    ++counter;
}


//logout and return to login window
void Gui_User::logout(){
    this->close();
    emit returnToLogin();
}
//resume user window from a visit to friend page
void Gui_User::resumeUserWindow(){
    this->close();
    Gui_User* userPage = new Gui_User(userCaller, false);
    userPage->show();
}

//add skill to layout and to userprofile
void Gui_User::addSkill(){
    std::string s = skilltoadd->text().toStdString();
    if(s=="")
        return ;
    if(client->getInfo()->addSkill(s)){
        addSkillRow(QString::fromStdString(s), skillslayout);
        try{
            client->save();
        }catch(MyExc e){
            QMessageBox* err = new QMessageBox();
            err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
            err->show();
        }
        skilltoadd->setText("");
    }
}
//remove skill from layout and from userprofile
void Gui_User::removeSkill(){
    int i = QObject::sender()->objectName().toInt();
    QLayoutItem* item;
    while((item=user_list[i]->takeAt(0)) != NULL){
        QLabel* tmp = dynamic_cast<QLabel*>(item->widget());
        if(tmp){
            client->getInfo()->removeSkill(tmp->text().toStdString());
            try{
                client->save();
            }catch(MyExc e){
                QMessageBox* err = new QMessageBox();
                err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
                err->show();
            }
        }
        delete item->widget();
        delete item;
    }
    delete user_list[i];
}

//add language to layout and to userprofile
void Gui_User::addLang(){
    std::string s = langtoadd->text().toStdString();
    if(s=="")
        return ;
    if(client->getInfo()->addLanguage(s)){
        addLangRow(QString::fromStdString(s), langslayout);
        try{
            client->save();
        }catch(MyExc e){
            QMessageBox* err = new QMessageBox();
            err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
            err->show();
        }
        langtoadd->setText("");
    }
}
//remove language from layout and from userprofile
void Gui_User::removeLang(){
    int i = QObject::sender()->objectName().toInt();
    QLayoutItem* item;
    while((item=user_list[i]->takeAt(0)) != NULL){
        QLabel* tmp = dynamic_cast<QLabel*>(item->widget());
        if(tmp){
            client->getInfo()->removeLanguage(tmp->text().toStdString());
            try{
                client->save();
            }catch(MyExc e){
                QMessageBox* err = new QMessageBox();
                err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
                err->show();
            }
        }
        delete item->widget();
        delete item;
    }
    delete user_list[i];
}

//add interest to layout and to userprofile
void Gui_User::addInterest(){
    std::string s = interesttoadd->text().toStdString();
    if(s=="")
        return ;
    if(client->getInfo()->addInterest(s)){
        addInterestRow(QString::fromStdString(s), interestslayout);
        try{
            client->save();
        }catch(MyExc e){
            QMessageBox* err = new QMessageBox();
            err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
            err->show();
        }
        interesttoadd->setText("");
    }
}
//remove interest from layout and from userprofile
void Gui_User::removeInterest(){
    int i = QObject::sender()->objectName().toInt();
    QLayoutItem* item;
    while((item=user_list[i]->takeAt(0)) != NULL){
        QLabel* tmp = dynamic_cast<QLabel*>(item->widget());
        if(tmp){
            client->getInfo()->removeInterest(tmp->text().toStdString());
            try{
                client->save();
            }catch(MyExc e){
                QMessageBox* err = new QMessageBox();
                err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
                err->show();
            }
        }
        delete item->widget();
        delete item;
    }
    delete user_list[i];
}
//add experience to layout and to userprofile
void Gui_User::addExp(){
    std::string _where = where->text().toStdString();
    std::string _role = role->text().toStdString();
    QDate _from = from->date();
    QDate _to = to->date();
    if(_where!="" && _role!="" && _from < _to){
        Experience e (_where,_role,_from,_to);
        if(client->getInfo()->addExperience(e)){
            addExpRow(e, explayout);
            try{
                client->save();
            }catch(MyExc e){
                QMessageBox* err = new QMessageBox();
                err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
                err->show();
            }
            where->setText("");
            role->setText("");
        }
    }
    return ;
}
//remove experience from layout and from userprofile
void Gui_User::removeExp(){
    int i = QObject::sender()->objectName().toInt();
    QLayoutItem* item;
    QGridLayout* l = dynamic_cast<QGridLayout*>(user_list[i]->takeAt(0));
    if(l){
        int c=0;
        QString _loc;
        QString _role;
        QDate _from;
        QDate _to;
        while((item=l->takeAt(0)) != NULL){

            QLabel* tmp = dynamic_cast<QLabel*>(item->widget());
            if(tmp){
//QTextStream(stdout)<<tmp->text()<<"\n";
                switch(c){
                    case 0:
                        _loc = tmp->text().remove("worked at ");
                    break;
                    case 1:
                        _role = tmp->text().remove("role: ");
                    break;
                    case 2:
                        _from = QDate::fromString(tmp->text().remove("from "),"yyyy.MM.dd");
                    break;
                    case 3:
                        _to = QDate::fromString(tmp->text().remove("to "),"yyyy.MM.dd");
                    break;
                }
            }
            delete item->widget();
            delete item;
            ++c;
        }
        try{
            Experience e(_loc.toStdString(),_role.toStdString(),_from,_to);
            client->getInfo()->removeExperience(e);
            try{
                client->save();
            }catch(MyExc e){
                QMessageBox* err = new QMessageBox();
                err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
                err->show();
            }
        }
        catch(MyExc e){
            QMessageBox* err = new QMessageBox();
            err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
            err->show();
        }
    }
 /*   else{
QTextStream(stdout)<<"null ";
    }
  */delete l;
    delete user_list[i];
}

void Gui_User::editSubscript(){
    dialog = new QDialog();
    dialog->setWindowTitle("Change your Subscription Type");
    QGridLayout* dLayout = new QGridLayout();
    QRadioButton* r1 = new QRadioButton("Basic User");
    r1->setObjectName("0");
    QRadioButton* r2 = new QRadioButton("Business User");
    r2->setObjectName("1");
    QRadioButton* r3 = new QRadioButton("Executive User");
    r3->setObjectName("2");
    connect(r1, SIGNAL(clicked()), this, SLOT(changeaType()));
    connect(r2, SIGNAL(clicked()), this, SLOT(changeaType()));
    connect(r3, SIGNAL(clicked()), this, SLOT(changeaType()));
    QPushButton*  b1 = new QPushButton ("ok", dialog);
    int tmp = client->getAccType();
    switch(tmp){
    case 0 :
        r1->setChecked(true);
        aType = _basic;
        break;
    case 1:
        r2->setChecked(true);
        aType = _business;
        break;
    case 2:
        r3->setChecked(true);
        aType = _executive;
        break;
    }
    connect(b1, SIGNAL(clicked()), this, SLOT(changeSubscript()));
    dLayout->addWidget(r1, 1, 0);
    dLayout->addWidget(r2, 1, 1);
    dLayout->addWidget(r3, 1, 2);
    dLayout->addWidget(b1, 2, 0, 1, 3, Qt::AlignCenter);

    dialog->setLayout(dLayout);
    dialog->exec();
}
void Gui_User::changeaType(){
    aType = static_cast<accountType>(QObject::sender()->objectName().toInt());
//QTextStream(stdout)<<QObject::sender()->objectName()<<"\n";
}
void Gui_User::changeSubscript(){
    if(aType != client->getAccType()){
        client->setAccType(aType);
        client->save();
        dialog->close();
        QMessageBox* message = new QMessageBox();
        message->setText("Your Subscription has been changed, but to take effects "
                         "you have to ReLogin, Sorry for the inconvenience");
        message->show();
    }
//QTextStream(stdout)<<aType;
    dialog->close();
}

void Gui_User::editInfo(){
    QLabel* item;
//QTextStream(stdout)<<"ci sono "+QString::number(firstCol->count())+" oggetti";
    int max = firstCol->count();
firstCol->setSpacing(2);
    for(int i=1; i<max; ++i){
//QTextStream(stdout)<<i;
//QTextStream(stdout)<<"\n";
        item = dynamic_cast<QLabel*>(firstCol->itemAt(i)->widget());
        if(item){
//QTextStream(stdout)<<"label \n";
            QLineEdit* tmp = new QLineEdit();
            tmp->setObjectName(item->objectName()+" edit");
            // non è possibile cambiare l'username (serve solo per il login, non è "utile" ai fini di linkedin (ricerche ecc..))
            if(item->objectName() == "username"){
                tmp->setDisabled(true);
                tmp->installEventFilter(this);
            }
            else if(item->objectName() == "password")
                tmp->setEchoMode(QLineEdit::Password);
            if(item->text() != "")
                tmp->setText(item->text());
            else
                tmp->setPlaceholderText(item->objectName());
            firstCol->itemAt(i)->widget()->hide();
            firstCol->addWidget(tmp, 0 , Qt::AlignCenter);
        }
        else{
            QPushButton* tmpbut = dynamic_cast<QPushButton*>(firstCol->itemAt(i)->widget());
            if(tmpbut){
//QTextStream(stdout)<<"button \n";
                QPushButton* tmpbut = new QPushButton("Save");

                connect(tmpbut, SIGNAL(clicked()), this, SLOT(saveProfile()));

                firstCol->itemAt(i)->widget()->hide();
                firstCol->addWidget(tmpbut, 0 , Qt::AlignCenter);
            }
        }
    }
    firstCol->setSpacing(10);
}

// Per questioni di tempo non ho messo controlli sull'input qui (al contrario della registrazione)
// avrei potuto mettere i controlli direttamente neli metodi "setter" della classe Info
void Gui_User::saveProfile(){
    int max = firstCol->count();
    QLineEdit* isEdit;
    QLabel* tmp;
    QString tmpstring;
    QDate tmpdata;

    //1° ciclo, salvo le nuove informazioni
    for(int i=10; i<max; ++i){
//QTextStream(stdout)<<QString::number(i)<<"  ";
        isEdit = dynamic_cast<QLineEdit*>(firstCol->itemAt(i)->widget());
        if(isEdit){
//QTextStream(stdout)<<isEdit->objectName()+"\n";
            switch(i){
            case 10:
                //username edit da fare
                //se cambio username, deve cambiare l'sername su tutte le liste amici
                //delete firstCol->itemAt(i)->widget();
                firstCol->itemAt(i)->widget()->hide();
                firstCol->itemAt(i-9)->widget()->show();
            break;
            case 11:
                //password edit
                client->getUsername().setPassword(isEdit->text().toStdString());    // NON LA CAMBIA
                tmp = static_cast<QLabel*>(firstCol->itemAt(i-9)->widget());
                tmp->setText(isEdit->text());
                firstCol->itemAt(i)->widget()->hide();
                tmp->show();
            break;
            case 12:
                //name edit
                client->getInfo()->setName(isEdit->text().toStdString());
                tmp = static_cast<QLabel*>(firstCol->itemAt(i-9)->widget());
                tmp->setText(isEdit->text());
                firstCol->itemAt(i)->widget()->hide();
                //delete firstCol->itemAt(i)->widget();
                tmp->show();
            break;
            case 13:
                //surname edit
                client->getInfo()->setSurname(isEdit->text().toStdString());
                tmp = static_cast<QLabel*>(firstCol->itemAt(i-9)->widget());
                tmp->setText(isEdit->text());
                firstCol->itemAt(i)->widget()->hide();
                //delete firstCol->itemAt(i)->widget();
                tmp->show();
            break;
            case 14:
                //birth edit
                tmpstring = isEdit->text();
                tmpdata = (QDate::fromString(tmpstring, "yyyy.MM.dd"));//tmpstring.left(4).toInt(), tmpstring.mid(5,2).toInt(), tmpstring.right(2).toInt()));
                if(!tmpdata.isValid() || tmpdata>QDate::currentDate()){
                    firstCol->itemAt(i)->widget()->hide();
                    firstCol->itemAt(i-9)->widget()->show();
                    QMessageBox* err = new QMessageBox();
                    err->setText("invalid birth date, valid format is 'yyyy.MM.dd' or you have entered an invalid birthday data.");
                    err->show();
                }
                else{
                    client->getInfo()->setBirthdate(tmpdata);
                    tmp = static_cast<QLabel*>(firstCol->itemAt(i-9)->widget());
                    tmp->setText(isEdit->text());
                    firstCol->itemAt(i)->widget()->hide();
                    tmp->show();
                }
            break;
            case 15:
                //address edit
                client->getInfo()->setAddress(isEdit->text().toStdString());
                tmp = static_cast<QLabel*>(firstCol->itemAt(i-9)->widget());
                tmp->setText(isEdit->text());
                firstCol->itemAt(i)->widget()->hide();
                //delete firstCol->itemAt(i)->widget();
                tmp->show();
            break;
            case 16:
                //email edit
                client->getInfo()->setEmail(isEdit->text().toStdString());
                tmp = static_cast<QLabel*>(firstCol->itemAt(i-9)->widget());
                tmp->setText(isEdit->text());
                firstCol->itemAt(i)->widget()->hide();
                //delete firstCol->itemAt(i)->widget();
                tmp->show();
            break;
            case 17:
                //Telephon edit
                client->getInfo()->setTel(isEdit->text().toStdString());
                tmp = static_cast<QLabel*>(firstCol->itemAt(i-9)->widget());
                tmp->setText(isEdit->text());
                firstCol->itemAt(i)->widget()->hide();
                //delete firstCol->itemAt(i)->widget();
                tmp->show();
            break;
            }
        }
        //potrei mettere l'if fuori dal for semplicemente facendo itemAt(18)
        if(i==18){
            //save button
//QTextStream(stdout)<<"save button \n";
            firstCol->itemAt(i)->widget()->hide();
            firstCol->itemAt(i-9)->widget()->show();
        }
    }
    client->save();

    // rimuovo tutte le cose che avevo lasciato nascoste
    // rimuoverle nel precedente for faceva traslare tutti gli inidici
//QTextStream(stdout)<<"\n sono presenti "<<firstCol->count()<<" elementi \n";
	QLayoutItem* todelete;
    while((todelete = firstCol->takeAt(10)) != NULL){
        delete todelete->widget();
        delete todelete;
    }
/*QTextStream(stdout)<<"\n sono presenti "<<firstCol->count()<<" elementi \n";
    for(int i = 1; i<firstCol->count(); ++i)
QTextStream(stdout)<<firstCol->itemAt(i)->widget()->objectName()<<"\n";*/
}


void Gui_User::clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
//QTextStream(stdout)<<"deleted a widget \n";
        }
        if (QLayout* childLayout = item->layout()){
//QTextStream(stdout)<<"found a layout, deleting it \n";
            clearLayout(childLayout, deleteWidgets);}
        delete item;
    }
}



bool Gui_User::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        QLabel* label = dynamic_cast<QLabel*>(obj);
        if(label){
            //controllo se label è avatar
            if(label->objectName() == "avatar"){ //apri un img selector
                QString avatarPath = QFileDialog::getOpenFileName(this, "Select Avatar, must be 200x200", "C:/Users/obeso/Desktop/Uni/p2/progetto", tr("Image Files (*.png *.jpg *.bmp)"));
                if (avatarPath != ""){
                    client->setAvatar(avatarPath.toStdString());
                    client->save();
                    img->setText("<img src='"+avatarPath+"' />");
                }
            }
            //else non è avatar
            else{
                //apro la finestra dell'user indicato
                /*QMessageBox* err = new QMessageBox;
                err->setText("apro la pagina di "+label->objectName());
                err->show();*/
                Gui_User* friendPage = new Gui_User(label->objectName().toStdString(), true, &(client->getUsername()));
                this->close();
                friendPage->show();
            }
        }
        else{
            QMessageBox* err = new QMessageBox;
            err->setText("You cannot change your Username!");
            err->show();
        }
    }
    return false;
}

void Gui_User::addThisFriend(){
    QMessageBox* msg = new QMessageBox();
    try{
        visitCallerClient->getNet()->addUser(client->getUserFromUsername(client->getUsername().getLogin()));//ridondante
        visitCallerClient->save();
        msg->setText("Operation successful");
    }
    catch(MyExc e){
        msg->setText(QString::fromStdString(e.errorMsg()));
    }
    msg->show();
}
