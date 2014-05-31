#include "like.h"
#include "evento_qlabel.h"
#include "ui_like.h"
#include "QDebug"
#include <QDesktopServices>
#include <QUrl>
like::like(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::like)
{
    ui->setupUi(this);

    connect(ui->lblFacebook,SIGNAL(mouse_pressed()),this,SLOT(abrirFace()));
    connect(ui->lbltwetter,SIGNAL(mouse_pressed()),this,SLOT(abrirTwee()));
    connect(ui->lblYoutube,SIGNAL(mouse_pressed()),this,SLOT(abrirYoutube()));
}

like::~like()
{
    delete ui;
}

void like::abrirTwee()
{
QDesktopServices::openUrl(QUrl("https://twitter.com/menrisub"));
}

void like::abrirYoutube()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/channel/UCa2OKexb1lXS7Nd5PJFidRw"));

}

void like::abrirFace()
{
    //abre una pagina web
    QDesktopServices::openUrl(QUrl("https://www.facebook.com/pages/Menri-sub/310914435725031"));
}



