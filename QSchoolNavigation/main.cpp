#pragma execution_character_set("utf-8")
#include <QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include <QProcess>
#include <QFontDatabase>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QIcon>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
    a.setWindowIcon(QIcon(":/main.ico"));
    a.setApplicationDisplayName("");
    QString qssFile = ":/qss/flatwhite.css";
    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
    MainWidget w;
    w.show();

    return a.exec();
}
