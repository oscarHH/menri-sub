#include "evento_qlabel.h"

evento_qlabel::evento_qlabel(QWidget *parent) :
    QLabel(parent)
{
}

void evento_qlabel::mousePressEvent(QMouseEvent *ev)
{
    emit mouse_pressed();
}
