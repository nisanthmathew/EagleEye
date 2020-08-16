#ifndef IMAGEVIEWEREVENTS_H
#define IMAGEVIEWEREVENTS_H

#include <QObject>

class ImageViewerEvents : public QObject
{
    Q_OBJECT
public:
    explicit ImageViewerEvents(QObject *parent = nullptr);

signals:

};

#endif // IMAGEVIEWEREVENTS_H
