#include "reader.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QWizard>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QProgressBar>
#include <QtCore/QTextStream>
#include <QtCore/QThread>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDebug>


Reader::Reader(const QString& _path):
    m_Path(_path)
{

}

Reader::~Reader()
{

}

void Reader::read()
{
    QFile file(m_Path);
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);

    QMap<QString, int> words_counter;
    qint64 bytes = 0, tmp = 0;
    const qint64 size = file.size();
    const QRegExp separator(R"((\s+|\.|,|;|:|\(|\)))");

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        bytes += line.length() + 1;
        QStringList words = line.split(separator, QString::SkipEmptyParts);
        for (const auto& word : words)
            ++words_counter[word];

        const int progress = bytes*100/size;
        if (progress > tmp)
        {
            tmp = progress;

            emit progressChanged(progress); // update user progress bar
        }
    }

    for (auto it = words_counter.constBegin(); it != words_counter.constEnd(); ++it)
        if (it.value() == 1)
            ;//qDebug() << it.key() << "\n";
}
