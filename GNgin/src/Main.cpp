#include "Engine/Engine.h"

Engine* engine;

int main(int argc, char* argv[])
{
    engine = new Engine();

    return 0;
}

//#include "./Testing/Application.h"
//
//int main(int argc, char* args[]) {
//    Application app;
//
//    app.Setup();
//
//    while (app.IsRunning()) {
//        app.Input();
//        app.Update();
//        app.Render();
//    }
//
//    app.Destroy();
//
//    return 0;
//}