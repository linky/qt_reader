#ifndef READER_H
#define READER_H

#include <QtCore/QObject>
#include <QtCore/QString>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(const QString& _path);

    virtual ~Reader();

public slots:
    void read();
signals:
    void progressChanged(int _progress);
private:
    QString m_Path;
};

#endif // READER_H
