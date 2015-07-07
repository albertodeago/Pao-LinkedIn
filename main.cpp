
#include"gui_login.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Gui_Login loginW;

    QFile File("styles/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    app.setStyleSheet(StyleSheet);

    loginW.show();
    return app.exec();
}

