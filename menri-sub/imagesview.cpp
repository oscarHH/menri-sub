#include "imagesview.h"
#include <QDebug>
#include <QMenu>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QContextMenuEvent>
#include <QPainter>
ImagesView::ImagesView(QWidget *parent)
 : QListView( parent )
{
        setViewMode( QListView::IconMode );
        setMovement( QListView::Static );
        setResizeMode( QListView::Adjust );
        setWrapping( true );
        setIconSize( QSize(170, 170) );
        setGridSize( QSize(200, 200) );
        setSpacing( 2 );
        setSelectionMode( QAbstractItemView::SingleSelection );
}

void ImagesView::removeSelectedImages()
{
    QModelIndexList indexes = selectedIndexes();

    if( indexes.isEmpty() )
        return;

    foreach( QModelIndex i, indexes )
        model()->removeRows( i.row(), 1, QModelIndex() );
}



void ImagesView::contextMenuEvent( QContextMenuEvent *event )
{
    QModelIndex current = indexAt( event->pos() );
    if( current.isValid() )
    {
        QItemSelectionModel *selectModel = selectionModel();
        selectModel->select( current, QItemSelectionModel::Select );
    }
    else
        return;

    QModelIndexList indexes = selectedIndexes();

    if( indexes.isEmpty() )
        return;

    QMenu context( tr( "Actions" ), this );
    const QString text = tr( "Remove %n image(s)", "", indexes.size() );
    context.addAction( text, this, SLOT( removeSelectedImages() ) );
    context.exec( event->globalPos() );
}

void ImagesView::keyPressEvent( QKeyEvent *event )
{
    if( event->matches( QKeySequence::Delete ) )
    {
        removeSelectedImages();
        return;
    }
    QListView::keyPressEvent( event );
}

void ImagesView::paintEvent( QPaintEvent *event )
{
    if( model()->rowCount() > 0 )
    {
        QListView::paintEvent( event );
        return;
    }

    QPainter painter( viewport() );

    QPalette palette;

    QPen pen( palette.color( QPalette::Highlight ) );

    QFont font = painter.font();
    font.setBold( true );
    font.setPointSize( font.pointSize() + 10 );

    const QString text = tr( "Agregar Imagenes" );

    const QFontMetrics fm( font );
    if( fm.width( text ) > viewport()->rect().width() )
        return;

    painter.setPen( pen );
    painter.setFont( font );

    painter.drawText( rect(), Qt::AlignCenter, text );
}
