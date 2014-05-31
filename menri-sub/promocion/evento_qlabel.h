#ifndef EVENTO_QLABEL_H
#define EVENTO_QLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class evento_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit evento_qlabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);

signals:
    void mouse_pressed();
};

#endif // EVENTO_QLABEL_H
