#include "WindowApp.h"
#include <cstdlib>

int main(int argc, char** argv)
{
    WindowApp* app = new WindowApp();
    app->runLoop();

    return EXIT_SUCCESS;
}