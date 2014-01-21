/***************************************************************************
 * copyright            : (C) 2007 Seb Ruiz <ruiz@kde.org>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2        *
 *   as published by the Free Software Foundation.                         *
 ***************************************************************************/

#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QMutex>
#include <QSize>
#include <QStringList>
#include <QThread>
#include <QWaitCondition>

class QImage;
class QIcon;

class ImageLoader : public QThread
{
    Q_OBJECT
public:
    ImageLoader( QObject *parent = 0 );
    ~ImageLoader();
    void load( QString filename );
    void cancel();

signals:
    void imageLoaded( const QString &filename, const QImage &thumbnail, const QString &description );

protected:
    void run();

private:
    QMutex          m_mutex;
    QWaitCondition  m_condition;
    bool            m_abort;
    QStringList     m_fileList;


};

#endif // IMAGELOADER_H
