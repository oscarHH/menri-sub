#ifndef CONFIGURACIONES_H
#define CONFIGURACIONES_H

#include <QDialog>

namespace Ui {
class Configuraciones;
}

class Configuraciones : public QDialog
{
    Q_OBJECT

public:
    explicit Configuraciones(QWidget *parent = 0);
    ~Configuraciones();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

private:
    Ui::Configuraciones *ui;
};

#endif // CONFIGURACIONES_H
