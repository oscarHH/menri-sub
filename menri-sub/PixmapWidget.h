#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QWidget>
#include <QString>

class QPixmap;

class PixmapWidget : public QWidget
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


public slots:
    void setZoomFactor( float );

signals:
    void zoomFactorChanged( float );


protected:
    void paintEvent( QPaintEvent* );
    void wheelEvent( QWheelEvent* );

private:
     void tamanioWidget();
    int w, h;
    double zoomFactor;
    qreal m_rotation;
};

#endif // PIXMAPWIDGET_H
