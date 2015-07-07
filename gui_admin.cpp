#include "gui_admin.h"

Gui_Admin::Gui_Admin(QWidget* parent): QWidget(parent), db(new LinkedDB){
    this->setWindowTitle("Welcome to LinQedIn Admin");
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.5);
    this->setFixedSize(this->size());

    QHBoxLayout* adminLayout = new QHBoxLayout();

    QVBoxLayout* firstCol = new QVBoxLayout();
    usersList = new QListWidget(this);
    for(std::list<SmartUser>::const_iterator it = db->begin(); it != db->end(); ++it) {
        QListWidgetItem* user = new QListWidgetItem(QString::fromStdString((*it)->account()->username().getLogin()));
        usersList->insertItem(usersList->count(),user);
    }
    usersList->setCurrentRow(0);
    usersList->setFixedHeight(this->height()/1.75);
    usersList->setFixedWidth(200);
    filterSearch = new QLineEdit();
    filterSearch->setPlaceholderText("filter users by username");
    filterSearch->setFixedWidth(200);
    connect(filterSearch, SIGNAL(textEdited(QString)), this, SLOT(filterUsers(QString)));
    firstCol->addSpacing(50);
    firstCol->addWidget(filterSearch, 0, Qt::AlignCenter);
    firstCol->addWidget(usersList,0, Qt::AlignCenter);
    firstCol->addSpacing(50);

    QVBoxLayout* secCol = new QVBoxLayout();
    QPushButton* adduserB = new QPushButton("add new user");
    adduserB->setFixedSize(160,30);
    connect(adduserB, SIGNAL(clicked()), this, SLOT(openAddUser()));
    QPushButton* removeuserB = new QPushButton("remove user");
    removeuserB->setFixedSize(160,30);
    connect(removeuserB, SIGNAL(clicked()), this, SLOT(removeUser()));
    QPushButton* changesubuserB = new QPushButton("change Subscription");
    changesubuserB->setFixedSize(160,30);
    connect(changesubuserB, SIGNAL(clicked()), this, SLOT(openChangeSubType()));
    QPushButton* logoutB = new QPushButton("Logout");
    logoutB->setFixedSize(160,30);
    connect(logoutB, SIGNAL(clicked()), this, SLOT(logout()));

    secCol->setSpacing(10);
    secCol->addSpacing(50);
    secCol->addWidget(adduserB,0, Qt::AlignLeft);
    secCol->addWidget(removeuserB,0, Qt::AlignLeft);
    secCol->addWidget(changesubuserB,0, Qt::AlignLeft);
    secCol->addWidget(logoutB, 0, Qt::AlignLeft);
    secCol->addSpacing(50);


    adminLayout->addLayout(firstCol);
    adminLayout->addLayout(secCol);
    setLayout(adminLayout);
}

//logout and return to login window
void Gui_Admin::logout(){
    this->close();
    emit returnToLogin();
}

void Gui_Admin::filterUsers(QString s){
    for(int i = 0; i<usersList->count(); ++i){
        QListWidgetItem* item = usersList->item(i);
        QString usLabel = item->text();
        if(!(usLabel.contains(s, Qt::CaseInsensitive)))
            item->setHidden(true);
        else
            item->setHidden(false);
    }
}

void Gui_Admin::removeUser(){
    QListWidgetItem* curr = usersList->currentItem();
    try{
        db->removeUser(Username(curr->text().toStdString()));
        db->save();
        usersList->takeItem(usersList->currentRow());
    }
    catch(MyExc e){
        QMessageBox* msg = new QMessageBox();
        msg->setText(QString::fromStdString(e.errorMsg()));
        msg->show();
    }
}
void Gui_Admin::openAddUser(){
    addUserPage = new QDialog();
    addUserPage->setWindowTitle("Add a new User");
    _username = new QLineEdit();
    _username->setPlaceholderText("Username");
    _password = new QLineEdit();
    _password->setPlaceholderText("Password");
    _password->setEchoMode(QLineEdit::Password);
    _name = new QLineEdit();
    _name->setPlaceholderText("Name");
    _surname = new QLineEdit();
    _surname->setPlaceholderText("Surname");
    _type = new QComboBox();
    _type->addItem("Basic User");
    _type->addItem("Business User");
    _type->addItem("Executive User");
    QPushButton* addB = new QPushButton("Add");
    connect(addB, SIGNAL(clicked()), this, SLOT(addUser()));
    QVBoxLayout* regLayout = new QVBoxLayout();
    regLayout->addWidget(_username, 0, Qt::AlignCenter);
    regLayout->addWidget(_password, 0, Qt::AlignCenter);
    regLayout->addWidget(_name    , 0, Qt::AlignCenter);
    regLayout->addWidget(_surname , 0, Qt::AlignCenter);
    regLayout->addWidget(_type    , 0, Qt::AlignCenter);
    regLayout->addWidget(addB     , 0, Qt::AlignCenter);
    addUserPage->setLayout(regLayout);
    addUserPage->show();
}
void Gui_Admin::addUser(){
//QTextStream(stdout)<<_type->currentIndex();
    if(_username->text()!= "" && _password->text()!= "" && _name->text()!= "" && _surname->text()!= ""){
        Username credential(_username->text().toStdString(),_password->text().toStdString());
        Info* info = new Info(QDate::currentDate(), _name->text().toStdString(), _surname->text().toStdString());
        accountType t = static_cast<accountType>(_type->currentIndex());
        Account* acc=new Account(info, credential, t);
        User* usr = NULL;
        switch(t){
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
        db->addUser(usr);
        db->save();
        usersList->insertItem(usersList->count(), _username->text());
        addUserPage->close();
    }
    else{
        QMessageBox* err = new QMessageBox();
        err->setText("All fields are mandatory");
        err->show();
    }
}

void Gui_Admin::openChangeSubType(){
    typeChangePage = new QDialog();
    typeChangePage->setWindowTitle("Change Subscription Type");
    QVBoxLayout* dLayout = new QVBoxLayout();
    changeType = new QComboBox();
    changeType->addItem("Basic User");
    changeType->addItem("Business User");
    changeType->addItem("Executive User");

    QPushButton*  b1 = new QPushButton ("ok");
    changeType->setCurrentIndex(static_cast<int>(db->find(usersList->currentItem()->text().toStdString())->account()->getType()));

    connect(b1, SIGNAL(clicked()), this, SLOT(changeSubType()));

    dLayout->addWidget(changeType);
    dLayout->addWidget(b1);

    typeChangePage->setLayout(dLayout);
    typeChangePage->exec();
}
void Gui_Admin::changeSubType(){
    User* us = db->find(usersList->currentItem()->text().toStdString());
    accountType oldType = us->account()->getType();
    accountType newType = static_cast<accountType>(changeType->currentIndex());
    if(oldType != newType){
        us->account()->setType(newType);
        db->save();
    }
    typeChangePage->close();
}
