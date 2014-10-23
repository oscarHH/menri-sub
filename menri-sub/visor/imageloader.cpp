/***************************************************************************
 * copyright            : (C) 2007 Seb Ruiz <ruiz@kde.org>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2        *
 *   as published by the Free Software Foundation.                         *
 ***************************************************************************/

#include <QtGui>
#include <QDebug>


#include "imageloader.h"

ImageLoader::ImageLoader(QObject *parent)
    : QThread( parent ), m_abort( false )
{
}

ImageLoader::~ImageLoader()
{
    cancel();
}

void ImageLoader::load( QString filename )
{
    QMutexLocker locker(&m_mutex);

    m_fileList.append( filename );

    if( !isRunning() )
        start( LowPriority );
    else
        m_condition.wakeOne();
}

void ImageLoader::cancel()
{
    m_abort = true;
}



void ImageLoader::run()
{
    //forever
    while (!m_abort) {
        m_mutex.lock();
        if( m_fileList.isEmpty() )
            m_condition.wait( &m_mutex );

        QString filename = m_fileList.takeFirst();
        m_mutex.unlock();

        QImage image( filename );
        QImage scaled = image.scaled( 170, 170, Qt::KeepAspectRatio, Qt::FastTransformation );

        QStringList suffixes;
        suffixes << "B" << "KB" << "MB" << "GB";
        QString suffix = suffixes.takeFirst();

        QFileInfo info( filename );
        double size = (double) info.size();

        while( size > 1024 && !suffixes.isEmpty() )
        {
            suffix = suffixes.takeFirst();
            size /= (double) 1024;
        }

        QString description = QString( "\n%1 %2" ).arg( QString::number( size, 'g', 3 ), suffix );
        emit imageLoaded( filename, scaled, description );
    }
}





