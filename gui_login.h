#ifndef GUI_LOGIN
#define GUI_LOGIN

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>

#include "gui_registration.h"
#include "gui_user.h"
#include "gui_admin.h"

class Gui_Login : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* usernameT;
    QLineEdit* passwordT;
    QDialogButtonBox* buttons;

    Gui_Registration* reg_page;
    Gui_User* user_page;
    Gui_Admin* admin_page;
    LinkedDB* db;

    void handleLogin() const;
public:
    Gui_Login(QWidget* = 0);
public slots:
    void onClicked(QAbstractButton* );
    void resumeLoginWindow();
};

#endif // GUI_LOGIN

