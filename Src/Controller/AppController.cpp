#include "AppController.h"

#include "UI/MainWindow.h"

namespace Parsey {
namespace Controller {

AppController::AppController()
{
    mMainWindow = new UI::MainWindow();
}

AppController::~AppController()
{
    delete mMainWindow;
}

void AppController::run()
{
    mMainWindow->show();
}

}
}
