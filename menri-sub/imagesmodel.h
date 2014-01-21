#ifndef IMAGESMODEL_H
#define IMAGESMODEL_H

#include "imageloader.h"

#include <QAbstractListModel>
#include <QIcon>
#include <QImage>
#include <QList>
#include <QPoint>

class ImagesModel : public QAbstractListModel
{
    Q_OBJECT

public:

    ImagesModel( QObject *parent = 0 );
    ~ImagesModel() { }

    QVariant      data( const QModelIndex &index, int role = Qt::DisplayRole ) const;
    Qt::ItemFlags flags( const QModelIndex &index ) const;
    bool          removeRows( int row, int count, const QModelIndex &parent );
    void          removeAll();
    int           rowCount( const QModelIndex &parent ) const;
    int           imageCount() const;
    QString       rutaImagen(int index);
    int           tamanioLista();
    void          addImage( const QString filename );
    void          addImages( const QStringList list );
    void          stopAddImages();

    bool          isAdding() { return m_loadCount > 0; }

    void          removeSelectedImages();

private slots:
    void          imageLoaded( const QString &filename, const QImage &thumbnail, const QString &description );

signals:
    void          imageAdded();
    void          imageRemoved();
    void          imageAddFinished();
    void          imageResizeFinished();

private:
    QStringList   m_filenames;
    QList<QIcon>  m_thumbnails;
    QStringList   m_descriptions;

    int           m_loadCount;

    ImageLoader   m_imageLoader;


};

#endif // IMAGESMODEL_H
