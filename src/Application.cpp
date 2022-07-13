#include "Application.h"

Application &Application::getInstance() {
    static Application instance;
    return instance;
}
