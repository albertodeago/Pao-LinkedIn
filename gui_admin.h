#ifndef GUI_ADMIN
#define GUI_ADMIN

#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDesktopWidget>
#include <QComboBox>
#include <QMessageBox>

#include "linkeddb.h"

class Gui_Admin : public QWidget
{
    Q_OBJECT
private:
    LinkedDB* db;
    QLineEdit* filterSearch;
    QListWidget* usersList;

    QDialog* addUserPage;
    QLineEdit* _username;
    QLineEdit* _password;
    QLineEdit* _name;
    QLineEdit* _surname;
    QComboBox* _type;

    QDialog* typeChangePage;
    QComboBox* changeType;

public:
    Gui_Admin(QWidget* = 0);

public slots:
    void logout();
    void removeUser();
    void openAddUser();
    void addUser();
    void openChangeSubType();
    void changeSubType();
    void filterUsers(QString);
signals:
    void returnToLogin();
};


#endif // GUI_ADMIN

