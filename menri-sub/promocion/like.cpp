#include "like.h"
#include "ui_like.h"

like::like(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::like)
{
    ui->setupUi(this);
}

like::~like()
{
    delete ui;
}
