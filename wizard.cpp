#include "wizard.h"

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


ReaderWizard::ReaderWizard():
        m_Thread(this)
{
    m_Wizard.setPage(FIRST_PAGE, createFirstPage());
    m_Wizard.button(QWizard::NextButton)->setEnabled(false);
    m_Wizard.setPage(SELECT_PAGE, createFilePage());
    m_Wizard.setPage(PROCESSING_PAGE, createProcessingPage());



    m_Wizard.show();
}

ReaderWizard::~ReaderWizard()
{
    m_Thread.quit();
    m_Thread.wait();

    if (m_Reader)
        delete m_Reader;
}

QWizardPage* ReaderWizard::createFirstPage()
{
    auto page = new QWizardPage;
    page->setTitle("About");
    page->setButtonText(QWizard::CancelButton, "Exit");

    auto layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Application for searching unique words in text files"));
    page->setLayout(layout);

    return page;
}

QWizardPage* ReaderWizard::createFilePage()
{
    auto page = new WizardPage;
    page->setTitle("Select file");
    page->setButtonText(QWizard::CancelButton, "Exit");
    page->setButtonText(QWizard::NextButton, "Start");

    auto layout = new QVBoxLayout;
    auto select_button = new QPushButton("select file", this);
    connect(select_button, &QPushButton::clicked, [&]() {
        m_Path = QFileDialog::getOpenFileName(this);

        // check file and enable Start button
        if (!m_Path.isEmpty() && QFile(m_Path).size() > 0)
            m_Wizard.button(QWizard::NextButton)->setEnabled(true);
        else
            m_Path.clear();
    });

    layout->addWidget(new QLabel("Please select a text file for processing"));
    layout->addWidget(select_button);

    page->setLayout(layout);

    return page;
}

QWizardPage* ReaderWizard::createProcessingPage()
{
    auto page = new WizardPage;
    page->setTitle("Scanning");
    page->setButtonText(QWizard::CancelButton, "Exit");

    auto layout = new QVBoxLayout;
    layout->addWidget(m_ProgressBar = new QProgressBar);
    layout->addWidget(new QLabel("Start scanning.."));
    page->setLayout(layout);

    connect(&m_Wizard, &QWizard::currentIdChanged, this, [&](int _page) {
        if (_page == PROCESSING_PAGE)
        {
            if (m_Reader == nullptr)
                m_Reader = new Reader(m_Path);

            connect(&m_Thread, &QThread::started, m_Reader, &Reader::read);
            connect(m_Reader, &Reader::progressChanged, m_ProgressBar, &QProgressBar::setValue);

            m_Reader->moveToThread(&m_Thread);
            m_Thread.start();
        }
    });

    return page;
}
