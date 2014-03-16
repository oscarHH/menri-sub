#ifndef IMAGESVIEW_H
#define IMAGESVIEW_H

#include <QListView>

class ImagesView : public QListView
{
    Q_OBJECT
public:
    ImagesView( QWidget *parent = 0 );

protected:
    void contextMenuEvent( QContextMenuEvent *event );
    void keyPressEvent( QKeyEvent *event );
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent( QPaintEvent *event );

private slots:
    void removeSelectedImages();

signals:
    void cambiarImagen(bool);
};

#endif // IMAGESVIEW_H
