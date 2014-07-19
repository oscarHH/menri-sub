#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include "PixmapWidget.h"
#include "../mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QMimeData>
float valorZoom = 1;
int coordenaX =0;
int coordenaY =0;
bool zoomRaton = false;

PixmapWidget::PixmapWidget( const QString &filename, QWidget *parent ) : QLabel( parent )
{
    m_pm = new QPixmap( filename );
    zoomFactor =valorZoom;
    this->f = zoomFactor;
    emit(tamanioWidget());
    setMinimumSize(  m_pm->width()*zoomFactor, m_pm->height()*zoomFactor );
    grados = 0;
    setAcceptDrops(true);
    this->move(coordenaX,coordenaY);
}


PixmapWidget::~PixmapWidget()
{
    delete m_pm;
}

void PixmapWidget::setGrados(int grados)
{
    this->grados = grados;

    tamanioWidget();
}

int PixmapWidget::getGrados()
{
    return grados;
}

QString PixmapWidget::getTamanioImagen()
{
    return  QString::number(m_pm->width()) + " x "+ QString::number(m_pm->height());
}

void PixmapWidget::tamanioWidget(){

    w = m_pm->width()*zoomFactor;
    h = m_pm->height()*zoomFactor;

    if(getGrados() == 90 || getGrados() == 270){
        setMinimumSize( h, w );
    }else{
        setMinimumSize( w, h);
    }
    repaint();
}


void PixmapWidget::setZoomFactor( float f )
{
    this->f = f;
    if( this->f == zoomFactor )
        return;

    zoomFactor = this->f;
    emit( zoomFactorChanged( zoomFactor ) );

    w = m_pm->width()*zoomFactor;
    h = m_pm->height()*zoomFactor;


    if(getGrados() == 90 || getGrados() == 270){
        setMinimumSize( h, w );
    }else{
        setMinimumSize( w, h);
    }

    QWidget *p = dynamic_cast<QWidget*>( parent() );
    if( p )
        resize( p->width(), p->height() );

    valorZoom  = f;
    repaint();
}



void PixmapWidget::paintEvent( QPaintEvent * /*event*/ )
{
    int xoffset, yoffset;

    //ancho
    if( width() > m_pm->width()*zoomFactor ){

        if(getGrados() == 90 || getGrados() == 270){
            xoffset = (height()-m_pm->width()*zoomFactor)/2;
        }else{
            xoffset = (width()-m_pm->width()*zoomFactor)/2;
        }
    }else{
        xoffset = 0;
    }


    //altura
    if( height() > m_pm->height()*zoomFactor ){
        if(getGrados() == 90 || getGrados() == 270){
            yoffset = (width()-m_pm->height()*zoomFactor)/2;
        }else{
            yoffset = (height()-m_pm->height()*zoomFactor)/2;
        }
    }else{
        yoffset = 0;
    }


    QPainter p( this );
    p.setRenderHint(QPainter::Antialiasing,true);
    p.setRenderHint(QPainter::SmoothPixmapTransform,true);


    if(getGrados() == 90 || getGrados() == 270){
        p.setViewport( yoffset,xoffset, m_pm->height()*zoomFactor, m_pm->width()*zoomFactor);
        p.setWindow(-50, -50, 100, 100);
    }else{
        p.setViewport(  xoffset, yoffset, m_pm->width()*zoomFactor, m_pm->height()*zoomFactor);
        p.setWindow(-50, -50, 100, 100);
    }

    p.rotate(getGrados());
    p.drawPixmap( -50, -50, 100, 100, *m_pm);


}



void PixmapWidget::wheelEvent( QWheelEvent *event )
{
    
   
    if(zoomRaton == true){
        coordenaX = event->x();
        coordenaY = event->y();
    
        this->f = zoomFactor + 0.001*event->delta();
        
        if( this->f < 32.0/m_pm->width() ){
            this->f = 32.0/m_pm->width();
    
        }
    
        emit(getCordenas(event->pos().x(),event->posF().y()));
    
        setZoomFactor( this->f );
        event->accept ();
    }
    
    

    return QWidget::wheelEvent (event);
    
}

void PixmapWidget::dragEnterEvent(QDragEnterEvent *event)
{

}

void PixmapWidget::dragMoveEvent(QDragMoveEvent *event)
{

}

void PixmapWidget::dropEvent(QDropEvent *event)
{

}

void PixmapWidget::startDrag(Qt::DropActions supportedActions)
{

    
}

//al hacer clicl secundario
void PixmapWidget::mousePressEvent(QMouseEvent *ev)
{
    
    
    if(ev->button() == Qt::RightButton){
        zoomRaton =true;
        ev->accept();
    }
}

void PixmapWidget::mouseReleaseEvent(QMouseEvent *ev)
{
  zoomRaton =false;
  
}

void PixmapWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
        coordenaX = ev->x ();
        coordenaY = ev->y();
    
        this->f += 0.5;
        
        if( this->f < 32.0/m_pm->width() ){
            this->f = 32.0/m_pm->width();
    
        }
    
        emit(getCordenas(ev->pos().x(),ev->pos().y()));
        
    
        setZoomFactor( this->f );
        ev->accept ();
}
