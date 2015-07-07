#include "gui_login.h"
#include<QMessageBox>

Gui_Login::Gui_Login(QWidget* parent) : QWidget(parent), db(new LinkedDB()){
    usernameT = new QLineEdit(this);
    passwordT = new QLineEdit(this);
    this->setWindowTitle("Welcome to QLinkedIn");
    passwordT->setEchoMode(QLineEdit::Password);
    QLabel* usernameL = new QLabel("Username:", this);
    QLabel* passwordL = new QLabel("Username:", this);
    QPushButton* loginB = new QPushButton("Login");
    QPushButton* registerB = new QPushButton("Register");
    QPushButton* exitB = new QPushButton("Exit");
    buttons = new QDialogButtonBox;
    buttons->addButton(loginB, QDialogButtonBox::AcceptRole);
    buttons->addButton(registerB, QDialogButtonBox::ActionRole);
    buttons->addButton(exitB, QDialogButtonBox::RejectRole);

    QVBoxLayout* loginLayout = new QVBoxLayout;
    loginLayout->addWidget(usernameL, Qt::AlignLeft);
    loginLayout->addWidget(usernameT, Qt::AlignRight);
    loginLayout->addWidget(passwordL, Qt::AlignLeft);
    loginLayout->addWidget(passwordT, Qt::AlignRight);
    loginLayout->addWidget(buttons ,  Qt::AlignLeft);
    setLayout(loginLayout);

    connect(buttons, SIGNAL(clicked( QAbstractButton*)) , this, SLOT(onClicked( QAbstractButton* )));

}

void Gui_Login::onClicked( QAbstractButton* but) {
    QDialogButtonBox::ButtonRole button = buttons->buttonRole(but);
    if(button == QDialogButtonBox::AcceptRole) {
        //provo a loggare
        try{
            //  controllo se logga admin!!
            Username logger(usernameT->text().toStdString(), passwordT->text().toStdString());
            Username admin = db->getAdmin();
            if(admin == logger){
                admin_page = new Gui_Admin();
                connect(admin_page, SIGNAL(returnToLogin()), this, SLOT(resumeLoginWindow()));
                admin_page->show();
                this->close();
            }
            else{
                if(db->isValidCredentials(logger)){
                    user_page = new Gui_User((logger), false);
                    connect(user_page,SIGNAL(returnToLogin()),this,SLOT(resumeLoginWindow()));
                    user_page->show();
                    this->hide();
                }
                else{
                    QMessageBox* err=new QMessageBox();
                    err->setText("Wrong Credentials!");
                    err->show();
                }
            }
        }
        catch(MyExc e){
            QMessageBox* err=new QMessageBox();
            err->setText(QString::fromUtf8(e.errorMsg().c_str()));
            err->show();
        }
    }
    else if(button == QDialogButtonBox::ActionRole) {
        //apro registration page
        reg_page = new Gui_Registration();
        //connect del segnale per poter ritornare a loginwindow in senza uscire e riaprire il programma
        connect(reg_page,SIGNAL(returnToLogin()),this,SLOT(resumeLoginWindow()));
        reg_page->show();
        this->close();
    }
    else{
        this->close();
    }
}

void Gui_Login::resumeLoginWindow(){
    this->show();
    QWidget::activateWindow();
}


