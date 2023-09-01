#include "WindowApp.h"
#include <cstdlib>

int main(int argc, char** argv)
{
    WindowApp* app = new WindowApp();
    app->run_loop();

    return EXIT_SUCCESS;
}