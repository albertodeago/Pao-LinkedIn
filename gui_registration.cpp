#include "gui_registration.h"
#include <iostream>
#include<QMessageBox>
#include<QRegExp>
#include<QDate>

Gui_Registration::Gui_Registration(QWidget* parent) : QWidget(parent){

    admin = new Admin();

    this->setWindowTitle("Welcome to the registration page");
    QLabel* usernl = new QLabel("Username*: ",this);
    QLabel* passwl = new QLabel("Password*: ",this);
    QLabel* namel = new QLabel("Name*: ",this);
    QLabel* surnamel = new QLabel("Surname*: ",this);
    QLabel* birthl = new QLabel("Birthday: ",this);
    QLabel* emaill = new QLabel("Email: ",this);
    QLabel* addressl = new QLabel("Address: ",this);
    QLabel* tell = new QLabel("Phone: ",this);
    QLabel* skillsl = new QLabel("Skills: ",this);
    QLabel* languagesl = new QLabel("Languages: ",this);
    QLabel* interestsl = new QLabel("Interests: ",this);
    QLabel* mandatory = new QLabel("Fields with (*) are mandatory");
    mandatory->setTextFormat(Qt::RichText);
    usern = new QLineEdit(this);
    passw = new QLineEdit(this);
    passw->setEchoMode(QLineEdit::Password);    // *** for password security
    name  = new QLineEdit(this);
    surname  = new QLineEdit(this);
    birthday = new QDateEdit(this);
	 birthday->setDisplayFormat("dd.MM.yyyy");
    email = new QLineEdit(this);
    address = new QLineEdit(this);
    tel = new QLineEdit(this);
    skill = new QLineEdit(this);
    QPushButton* addSkill = new QPushButton("+",this);
    language = new QLineEdit(this);
    QPushButton* addLanguage = new QPushButton("+",this);
    interest = new QLineEdit(this);
    QPushButton* addInterest = new QPushButton("+",this);
    QPushButton* addExperience = new QPushButton("+",this);
    QLabel* separator = new QLabel("Add your work experiences below",this);
    QLabel* locationl = new QLabel("Location: ",this);
    QLabel* rolel = new QLabel("Role: ",this);
    QLabel* froml = new QLabel("Begin: ",this);
    QLabel* tol = new QLabel("End: ",this);
    location_e = new QLineEdit(this);
    role_e = new QLineEdit(this);
    from_e = new QDateEdit(this);
	 from_e->setDisplayFormat("dd.MM.yyyy");
    to_e = new QDateEdit(this);
	 to_e->setDisplayFormat("dd.MM.yyyy");

    QGroupBox* accTypeGroup = new QGroupBox();
    radio1 = new QRadioButton(tr("Basic User"));
    radio2 = new QRadioButton(tr("Business User"));
    radio3 = new QRadioButton(tr("Executive User"));
    radio1->setChecked(true);
    QHBoxLayout* typeLayout = new QHBoxLayout();
    typeLayout->addWidget(radio1); typeLayout->addWidget(radio2); typeLayout->addWidget(radio3);
    //accTypeGroup->setFlat(true);
    accTypeGroup->setStyleSheet("Border: 0px;");
    accTypeGroup->setLayout(typeLayout);

    QPushButton* okB = new QPushButton("Ok");
    QPushButton* exitB = new QPushButton("Cancel");
    buttons = new QDialogButtonBox;
    buttons->addButton(okB, QDialogButtonBox::AcceptRole);
    buttons->addButton(exitB, QDialogButtonBox::RejectRole);

    addSkill->setProperty("ActionRole",1);
    addLanguage->setProperty("ActionRole",2);
    addInterest->setProperty("ActionRole",3);
    addExperience->setProperty("ActionRole",4);
    add_buttons = new QDialogButtonBox;
    add_buttons->addButton(addSkill,QDialogButtonBox::ActionRole);
    add_buttons->addButton(addLanguage,QDialogButtonBox::ActionRole);
    add_buttons->addButton(addInterest,QDialogButtonBox::ActionRole);
    add_buttons->addButton(addExperience,QDialogButtonBox::ActionRole);

    QGridLayout* regLayout = new QGridLayout;
    regLayout->addWidget(usernl,0,0,Qt::AlignLeft);
    regLayout->addWidget(usern,0,1,Qt::AlignRight);
    regLayout->addWidget(passwl,1,0,Qt::AlignLeft);
    regLayout->addWidget(passw,1,1,Qt::AlignRight);
    regLayout->addWidget(namel,2,0,Qt::AlignLeft);
    regLayout->addWidget(name,2,1,Qt::AlignRight);
    regLayout->addWidget(surnamel,3,0,Qt::AlignLeft);
    regLayout->addWidget(surname,3,1,Qt::AlignRight);
    regLayout->addWidget(birthl,4,0);
    regLayout->addWidget(birthday,4,1);
    regLayout->addWidget(emaill,5,0,Qt::AlignLeft);
    regLayout->addWidget(email,5,1,Qt::AlignRight);
    regLayout->addWidget(addressl,6,0,Qt::AlignLeft);
    regLayout->addWidget(address,6,1,Qt::AlignRight);
    regLayout->addWidget(tell,7,0,Qt::AlignLeft);
    regLayout->addWidget(tel,7,1,Qt::AlignRight);
    regLayout->addWidget(skillsl,8,0,Qt::AlignLeft);
    regLayout->addWidget(skill,8,1,Qt::AlignCenter);
    regLayout->addWidget(addSkill,8,2,Qt::AlignRight);
    regLayout->addWidget(languagesl,9,0,Qt::AlignLeft);
    regLayout->addWidget(language,9,1,Qt::AlignCenter);
    regLayout->addWidget(addLanguage,9,2,Qt::AlignRight);
    regLayout->addWidget(interestsl,10,0,Qt::AlignLeft);
    regLayout->addWidget(interest,10,1,Qt::AlignCenter);
    regLayout->addWidget(addInterest,10,2,Qt::AlignRight);
    regLayout->addWidget(separator,11,0,Qt::AlignCenter);
    regLayout->addWidget(locationl,12,0,Qt::AlignLeft);
    regLayout->addWidget(location_e,12,1,Qt::AlignLeft);
    regLayout->addWidget(rolel,13,0,Qt::AlignLeft);
    regLayout->addWidget(role_e,13,1,Qt::AlignLeft);
    regLayout->addWidget(froml,14,0,Qt::AlignLeft);
    regLayout->addWidget(from_e,14,1,Qt::AlignLeft);
    regLayout->addWidget(tol,15,0,Qt::AlignLeft);
    regLayout->addWidget(to_e,15,1,Qt::AlignLeft);
    regLayout->addWidget(addExperience,15,2,Qt::AlignLeft);
    regLayout->addWidget(accTypeGroup, 16, 0, 1, 3);
    regLayout->addWidget(mandatory, 17,0);
    regLayout->addWidget(okB,17,1);
    regLayout->addWidget(exitB,17,2);
    setLayout(regLayout);

    connect(buttons, SIGNAL(clicked( QAbstractButton*)) , this, SLOT(onClicked( QAbstractButton* )));
    connect(add_buttons, SIGNAL(clicked( QAbstractButton*)) , this, SLOT(onAdd( QAbstractButton* )));
};

void Gui_Registration::onClicked( QAbstractButton* but) {
    QDialogButtonBox::ButtonRole button = buttons->buttonRole(but);
    if(button == QDialogButtonBox::AcceptRole) {
        //provo a registrarmi
        if(checkErrors()){
            //gli errori sono gia' gestiti dentro all funzione
        }
        else{
            //tento la registrazione vera e propria
            try{
                Username credential(usern->text().toStdString(),passw->text().toStdString());
                Info i(birthday->date(), name->text().toStdString(),surname->text().toStdString(),email->text().toStdString(),address->text().toStdString(),tel->text().toStdString());
                Info* info=&i;
                for(std::list<string>::const_iterator it = _skills.begin(); it!=_skills.end(); ++it){
                    info->addSkill(*it);
                }
                for(std::list<string>::const_iterator it = _languages.begin(); it!=_languages.end(); ++it){
                    info->addLanguage(*it);
                }
                for(std::list<string>::const_iterator it = _interests.begin(); it!=_interests.end(); ++it){
                    info->addInterest(*it);
                }
                for(std::list<Experience*>::const_iterator it = _experiences.begin(); it!=_experiences.end();++it){
                    info->addExperience(**it);
                }
                accountType _type;
                if (radio1->isChecked())
                    _type = _basic;
                else if(radio2->isChecked())
                    _type = _business;
                else _type = _executive;
                Account* acc=new Account(info, credential, _type);
                User* usr = NULL;
                switch(_type){
                case 0:
                    usr = new BasicUser(acc);
                break;
                case 1:
                    usr = new BusinessUser(acc);
                break;
                case 2:
                    usr = new ExecutiveUser(acc);
                break;
                }
                admin->insertUser(usr);
                //aprire userwindow
                user_page = new Gui_User(Username(usern->text().toStdString(), passw->text().toStdString() ), false);
                //connect(user_page,SIGNAL(returnToLogin()),login_page,SLOT(resumeLoginWindow()));
                user_page->show();
                this->close();
                    /***************************    N   B   **********************************/
            }catch(MyExc e){
                QMessageBox* err = new QMessageBox();
                err->setText(QString::fromUtf8((e.errorMsg()).c_str()));
                err->show();
            }
        }
    }
    else {
        this->close();
        emit returnToLogin();
    }
}

void Gui_Registration::onAdd(QAbstractButton* but){
    int test = but->property("ActionRole").toInt();
    std::string s;
    switch(test){
        case 1:
            s = skill->text().toStdString();
            if(s!=""){
                _skills.push_back(s);
                skill->setText("");
                skill->setFocus();
            }
        break;
        case 2:
            s = language->text().toStdString();
            if(s!=""){
                _languages.push_back(s);
                language->setText("");
                language->setFocus();
            }
        break;
        case 3:
            s = interest->text().toStdString();
            if(s!=""){
                _interests.push_back(s);
                interest->setText("");
                interest->setFocus();
            }
        break;
        case 4:
            std::string l = location_e->text().toStdString();
            std::string r = role_e->text().toStdString();
            QDate f = from_e->date();
            QDate t = to_e->date();
            if(l!= "" && r!= "" && f<t){
                //could substitute the if statement with a try catch
                Experience* e = new Experience(l,r,f,t);
                _experiences.push_back(e);
                location_e->setText("");
                role_e->setText("");
            }
            else{
                QMessageBox* err = new QMessageBox();
                err->setText("one of the experiences fields are incorrect!");
                err->show();
            }
        break;
        //default non è presente, non può arrivare un int test < 1 || test > 4
    }
}

//check errors controlla l'integrità dei campi, prima di provare a fare la registrazione vera e propria nel "DB"
bool Gui_Registration::checkErrors(){
    QMessageBox* err = new QMessageBox();
    if(usern->text() == "" || passw->text() == "" || name->text() == "" || surname->text() == ""){
        err->setText("username,password,name and surname are mandatory!");
        err->show();
        return true;
    }
    if(usern->text().contains(" ") || passw->text().contains(" ")){
        err->setText("username and password can't contain spaces");
        err->show();
        return true;
    }
    QRegExp regex("[0-9]{1,1}");
    if(name->text().contains(regex) || surname->text().contains(regex)){
        err->setText("name and surname cannot contains numbers");
        err->show();
        return true;
    }
    if(birthday->date() >= QDate::currentDate()){
        err->setText("cannot be unborn");
        err->show();
        return true;
    }
    // non controllo il campo email, basterebbe usare di nuovo una regexp
    QRegExp regex2("[a-Z][1,1]");
    if(tel->text().contains(regex2)){
        err->setText("invalid telephon number");
        err->show();
        return true;
    }
    delete err;
    return false;
}

