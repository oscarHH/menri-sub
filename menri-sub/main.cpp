#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    QByteArray  encodedString =  argv[1];
    QTextCodec *codec = QTextCodec::codecForName("ISO 8859-15");
    QString img = codec->toUnicode(encodedString);
    //QString img = argv[1];

    MainWindow w;
    if(img != ""){
    w.mandarImagen(img);
    w.imagenListwidget(img);
    }
    w.show();
    w.setAcceptDrops(true);
		
    return a.exec();
}
