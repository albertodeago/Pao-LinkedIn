#ifndef GUI_USER
#define GUI_USER

#include <QPushButton>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QFont>
#include <QSpacerItem>
#include <QObject>
#include <QList>
#include <QDateEdit>
#include <QGroupBox>
#include <QMessageBox>
#include "linkedclient.h"
#include <QEvent>
#include <QFileDialog>
#include <QRadioButton>


class Gui_User: public QWidget
{
    Q_OBJECT
private:
    // per counter e cfriend servirebbe un metodo per il riutilizzo di indici per le rispettive vector, per motivi di tempo
    // non ho implementato niente a riguardo.
    int counter;
    int cfriend;

    bool _visit;
    Username userCaller;

    LinkedClient* client;
    LinkedClient* visitCallerClient;

    QLabel* img;
    accountType aType;
    QDialog* dialog;

    QLineEdit* searchBar;

    QVBoxLayout* firstCol;
    QVBoxLayout* skillslayout;
    QVBoxLayout* langslayout;
    QVBoxLayout* interestslayout;
    QVBoxLayout* explayout;
    QVBoxLayout* friendslayout;
    QVBoxLayout* searchFriendsLayout;
    QVector<QHBoxLayout*> user_list;
    QVector<QHBoxLayout*> friend_searched_list;

    QLineEdit* skilltoadd;
    QLineEdit* langtoadd;
    QLineEdit* interesttoadd;
    QLineEdit* where;
    QLineEdit* role;
    QDateEdit* from;
    QDateEdit* to;

    //3 function for the rows and the 6 add/remove are quite redundant, change if time let you (use a map)
    void addSkillRow(QString, QVBoxLayout *);
    void addLangRow(QString, QVBoxLayout *);
    void addInterestRow(QString, QVBoxLayout *);
    void addExpRow(const Experience& , QVBoxLayout *);
    void addFriendRow(const QString&, const QString&, bool);
    void clearLayout(QLayout*, bool);
    bool eventFilter(QObject *, QEvent*);
    void hideORshowAllFrom(QLayout*, bool);
public:
    Gui_User(const Username&, bool isAVisit = false, Username* = 0,  QWidget* =0);
public
    slots:
        void logout();
        void resumeUserWindow();
        void addSkill();
        void removeSkill();
        void addLang();
        void removeLang();
        void addInterest();
        void removeInterest();
        void addExp();
        void removeExp();
        void addFriend();
        void removeFriend();
        void search();
        void resetSearch();
        void editInfo();
        void saveProfile();
        void editSubscript();
        void changeSubscript();
        void changeaType();

        void addThisFriend();
    signals:
        void returnToLogin();
};

#endif // GUI_USER

