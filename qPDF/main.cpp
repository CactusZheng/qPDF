#include "qPDF.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qPDF w;
    w.show();
    return a.exec();
}
