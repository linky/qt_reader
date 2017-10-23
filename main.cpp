#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

#include "wizard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ReaderWizard wizard;

    return app.exec();
}
