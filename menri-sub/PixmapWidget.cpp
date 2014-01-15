#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include "PixmapWidget.h"
#include "mainwindow.h"
#include <QGraphicsPixmapItem>
PixmapWidget::PixmapWidget( const QString &filename, QWidget *parent ) : QWidget( parent )
{
    m_pm = new QPixmap( filename );
    zoomFactor = 0.3;
    this->f = zoomFactor;
    setMinimumSize(  m_pm->width()*zoomFactor, m_pm->height()*zoomFactor );
    grados = 0;
}


PixmapWidget::~PixmapWidget()
{
    delete m_pm;
}

void PixmapWidget::setGrados(int grados)
{
    this->grados = grados;
}

int PixmapWidget::getGrados()
{

    return grados;
}


void PixmapWidget::setZoomFactor( float f )
{
    int w, h;
    this->f = f;
    if( this->f == zoomFactor )
        return;

    zoomFactor = this->f;
    emit( zoomFactorChanged( zoomFactor ) );

    w = m_pm->width()*zoomFactor;
    h = m_pm->height()*zoomFactor;
    setMinimumSize( w, h);


    QWidget *p = dynamic_cast<QWidget*>( parent() );
    if( p )
       resize( p->width(), p->height() );

    repaint();
}



void PixmapWidget::paintEvent( QPaintEvent * /*event*/ )
{
    //QMatrix matrix;
    //event->DragMove;
    int xoffset, yoffset;


    if( width() > m_pm->width()*zoomFactor )
    {
        xoffset = (width()-m_pm->width()*zoomFactor)/2;

    }
    else
    {
        xoffset = 0;
    }

    if( height() > m_pm->height()*zoomFactor )
    {
        yoffset = (height()-m_pm->height()*zoomFactor)/2;

    }
    else
    {
        yoffset = 0;
    }

    QPainter p( this );
    p.setRenderHint(QPainter::Antialiasing,true);
    p.setRenderHint(QPainter::SmoothPixmapTransform,true);



/*
    if(getGrados() == 90 || getGrados() == 270){

        p.setViewport( yoffset , xoffset, m_pm->height()*zoomFactor/2,m_pm->width()*zoomFactor/2);
        QRect r1(50,50, 100, 100);
        p.setWindow(r1);
        p.rotate(getGrados());
        //le hace caso al setWindow
        p.drawPixmap( 100,100,-50,-50, *m_pm);
    }else{
        p.setViewport(  xoffset-1, yoffset-1, m_pm->width()*zoomFactor, m_pm->height()*zoomFactor);
        p.setWindow(-50, -50, 100, 100);
        p.rotate(getGrados());
        //le hace caso al setWindow
        p.drawPixmap( -50, -50, 100, 100, *m_pm);
    }*/
    p.setViewport(  xoffset-1, yoffset-1, m_pm->width()*zoomFactor, m_pm->height()*zoomFactor);
    p.setWindow(-50, -50, 100, 100);
    p.rotate(getGrados());
    //le hace caso al setWindow
    p.drawPixmap( -50, -50, 100, 100, *m_pm);
}

    //p.restore();


void PixmapWidget::wheelEvent( QWheelEvent *event )
{
    this->f = zoomFactor + 0.001*event->delta();
    if( this->f < 32.0/m_pm->width() ){
        this->f = 32.0/m_pm->width();
    }
    setZoomFactor( this->f );
}
