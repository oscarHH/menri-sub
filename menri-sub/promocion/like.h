#ifndef LIKE_H
#define LIKE_H

#include <QDialog>

namespace Ui {
class like;
}

class like : public QDialog
{
    Q_OBJECT

public:
    explicit like(QWidget *parent = 0);
    ~like();

private:
    Ui::like *ui;
};

#endif // LIKE_H
