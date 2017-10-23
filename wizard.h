#ifndef WIZARD_H
#define WIZARD_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QWizard>
#include <QtWidgets/QProgressBar>
#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QMap>
#include <QtCore/QString>

#include "reader.h"

class ReaderWizard : public QWidget
{
    Q_OBJECT
public:
    class WizardPage : public QWizardPage
    {
    public:
        // check "correct file" condition
        bool isComplete() const override
        {
            return m_Complete;
        }

        void setComplete()
        {
            m_Complete = true;
        }
    private:
        bool m_Complete = false;
    };

    ReaderWizard();

    virtual ~ReaderWizard();
private:
    QWizardPage* createFirstPage();

    QWizardPage* createFilePage();

    QWizardPage* createProcessingPage();
private:
    enum PAGES { FIRST_PAGE, SELECT_PAGE, PROCESSING_PAGE };

    QWizard m_Wizard;
    QThread m_Thread;
    QString m_Path;
    QProgressBar* m_ProgressBar = nullptr;
    Reader* m_Reader = nullptr;
};

#endif // WIZARD_H
