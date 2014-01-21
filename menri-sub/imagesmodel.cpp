#include <QtGui>
#include <QDebug>


#include "ImagesModel.h"
#include "ImageLoader.h"

ImagesModel::ImagesModel(QObject *parent): QAbstractListModel( parent )
  , m_loadCount( 0 )
{
    connect( &m_imageLoader,  SIGNAL( imageLoaded( const QString &, const QImage &, const QString & ) ),
                  this,SLOT( imageLoaded( const QString &, const QImage &, const QString & ) ) );

}

QVariant ImagesModel::data( const QModelIndex &index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    if( role == Qt::DecorationRole )
        return m_thumbnails.at( index.row() );

    if( role == Qt::DisplayRole )
    {
        QFileInfo info( m_filenames.at( index.row() ) );
        QString description = info.fileName() + "\n" + m_descriptions.at( index.row() );
        return description;
    }

    if( role == Qt::UserRole )
        return m_filenames.at( index.row() );

    return QVariant();
}


Qt::ItemFlags ImagesModel::flags( const QModelIndex &index ) const
{
    if( index.isValid() )
        return ( Qt::ItemIsEnabled | Qt::ItemIsSelectable );

    return Qt::ItemIsDropEnabled;
}


int ImagesModel::rowCount( const QModelIndex &parent ) const
{
    if( parent.isValid() ) return 0;
    return m_filenames.size();
}

int ImagesModel::imageCount() const { return m_filenames.size(); }

QString ImagesModel::rutaImagen(int index)
{
    return m_filenames.at(index);
}

int ImagesModel::tamanioLista()
{
    return m_filenames.size();
}

bool ImagesModel::removeRows( int row, int count, const QModelIndex &parent )
{
    if( parent.isValid() )
        return false;

    if( row >= m_filenames.size() || row + count <= 0 )
        return false;

    int beginRow = qMax( 0, row );
    int endRow = qMin( row + count - 1, m_filenames.size() - 1 );

    beginRemoveRows( parent, beginRow, endRow );

    qDebug ()<< m_filenames.at(0);
    while( beginRow <= endRow )
    {
        m_thumbnails.removeAt( beginRow );
        m_filenames.removeAt( beginRow );
        m_descriptions.removeAt( beginRow );
        ++beginRow;
        emit imageRemoved();
    }

    endRemoveRows();
    return true;
}

void ImagesModel::removeAll()
{
        m_thumbnails.clear();
        m_filenames.clear();
        m_descriptions.clear();
        emit imageRemoved();
}





void ImagesModel::addImage( const QString filename )
{
    m_imageLoader.load( filename );
}

void ImagesModel::addImages( const QStringList list )
{
    m_loadCount += list.size();
   // SquashWindow::instance()->setStatusBarText( tr( "Loading %n image(s)...", "", m_loadCount ) );

    foreach( QString location, list )
        addImage( location );
}

void ImagesModel::imageLoaded( const QString &filename, const QImage &thumbnail, const QString &description )
{
    int row = m_filenames.size();

    beginInsertRows( QModelIndex(), row, row );

    // we must create the icon here and not in the thread because QWidget and friends aren't reentrant.
    QIcon iconThumb = QIcon( QPixmap::fromImage( thumbnail ) );

    m_filenames.insert( row, filename );
    m_thumbnails.insert( row, iconThumb );
    m_descriptions.insert( row, description );

    endInsertRows();
    emit imageAdded();
}

void ImagesModel::stopAddImages()
{
    m_imageLoader.cancel();

}

