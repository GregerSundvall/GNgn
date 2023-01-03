#include "Engine/Engine.h"
#include "SDL.h"
#include "GEngn.h"

Engine* engine = new Engine();

int main( int argc, char* argv[] )
{
    engine->Run();
    
    return 0;
}

