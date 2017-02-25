#include "Controller/AppController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Parsey::Controller::AppController appController;
    appController.run();

    return a.exec();
}
