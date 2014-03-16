#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

//#include <QWidget>
#include <QLabel>
#include <QString>

class QPixmap;

class PixmapWidget : public QLabel
{
    Q_OBJECT

public:
    PixmapWidget( const QString &filename, QWidget *parent=0 );
    ~PixmapWidget();
    float f ;
    QPixmap *m_pm;
    int grados;
    void setGrados(int grados);
    int getGrados();
    QString getTamanioImagen();

public slots:
    void setZoomFactor( float );

signals:
    void zoomFactorChanged( float );


protected:
    virtual void paintEvent( QPaintEvent* );
    virtual void wheelEvent( QWheelEvent* );
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void startDrag(Qt::DropActions supportedActions);
private:
     void tamanioWidget();
    int w, h;
    double zoomFactor;
    qreal m_rotation;
};

#endif // PIXMAPWIDGET_H
