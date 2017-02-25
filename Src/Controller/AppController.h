#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

namespace Parsey {
    namespace UI {
        class MainWindow;
    }
}

namespace Parsey {
namespace Controller {

class AppController : public QObject
{
    Q_OBJECT

public:
    AppController();
    ~AppController();

    void run();

private:
    UI::MainWindow *mMainWindow;
};

}
}

#endif // APPCONTROLLER_H
