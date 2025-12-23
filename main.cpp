#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载 QSS 样式表
    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        a.setStyleSheet(qss);
        file.close();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
