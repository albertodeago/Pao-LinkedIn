#ifndef GUI_REGISTRATION
#define GUI_REGISTRATION

#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QDateEdit>
#include <list>
#include <string>
#include "admin.h"
#include "gui_user.h"
#include <QRadioButton>

class Gui_Registration : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* usern;
    QLineEdit* passw;
    QLineEdit* name;
    QLineEdit* surname;
    QDateEdit* birthday;
    QLineEdit* email;
    QLineEdit* address;
    QLineEdit* tel;
    QLineEdit* skill;
    QLineEdit* language;
    QLineEdit* interest;
    QLineEdit* location_e;
    QLineEdit* role_e;
    QDateEdit* from_e;
    QDateEdit* to_e;
    QRadioButton* radio1;
    QRadioButton* radio2;
    QRadioButton* radio3;
    QDialogButtonBox* buttons;
    QDialogButtonBox* add_buttons;

    std::list<string> _languages;
    std::list<string> _skills;
    std::list<string> _interests;
    std::list<Experience*> _experiences;

    Gui_User* user_page;

    Admin* admin;
public:
    Gui_Registration(QWidget* = 0);
    bool checkErrors();
public
    slots:
        void onClicked(QAbstractButton* );
        void onAdd(QAbstractButton* );
    signals:
        void returnToLogin();
};

#endif // GUI_REGISTRATION

