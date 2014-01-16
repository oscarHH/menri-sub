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
    //QString plataforma = QApplication::platformName();

    MainWindow w;
    if(!img.isEmpty()){
     QFileInfo info;
     info.setFile(img);
     w.RutaImagenes.append(img);
     w.view->addItem(info.fileName());
     w.mandarImagen(img);
     w.updateActions();
    }
    w.show();
    w.setAcceptDrops(true);
		
    return a.exec();
}
