#ifndef READER_H
#define READER_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVector>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(const QString& _path);

    virtual ~Reader();

    QVector<QString> getResult() const;
public slots:
    void read();
signals:
    void progressChanged(int _progress);
    void completed();
private:
    QString m_Path;
    QVector<QString> m_Result;
};

#endif // READER_H
