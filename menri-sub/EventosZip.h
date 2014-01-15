#ifndef EVENTOSZIP_H
#define EVENTOSZIP_H

#include <JlCompress.h>
#include <quazipfile.h>
#include <quazip.h>
#include <zip.h>
#include <QStringList>
#include <QDebug>


class EventosZip
{
public:
    EventosZip();
    ~EventosZip();
    QStringList  listarzip();
};

#endif // EVENTOSZIP_H
