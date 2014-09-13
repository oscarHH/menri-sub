#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setStyle("fusion");
    QStringList img;
    img = a.arguments();

    //QString plataforma = QApplication::platformName();
    MainWindow w;


    if( (img.size()==2)   && ( !img.at(1).isEmpty() )){
        QFileInfo info;
        info.setFile(img.at(1));
        //w.RutaImagenes.append(img.at(1));
        w.m_imagesModel->addImage(img.at(1));
        //w.view->addItem(info.fileName());
        w.mandarImagen(img.at(1));
        w.updateActions();
    }
    w.showFullScreen();
    w.show();
    w.setAcceptDrops(true);


    return a.exec();
}
