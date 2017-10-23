#ifndef WIZARD_H
#define WIZARD_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QWizard>
#include <QtWidgets/QProgressBar>
#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QVector>

#include "reader.h"

class ReaderWizard : public QWidget
{
    Q_OBJECT
public:
    ReaderWizard();

    virtual ~ReaderWizard();
private:
    QWizardPage* createFirstPage();

    QWizardPage* createFilePage();

    QWizardPage* createProcessingPage();
private:
    struct Page : QWizardPage
    {
        bool isComplete() const override { return false; } // TODO disable Next button
    };

    enum PAGES { FIRST_PAGE, SELECT_PAGE, PROCESSING_PAGE };

    QWizard m_Wizard;
    QThread m_Thread;
    QString m_Path;
    QProgressBar* m_ProgressBar = nullptr;
    Reader* m_Reader = nullptr;
};

#endif // WIZARD_H
