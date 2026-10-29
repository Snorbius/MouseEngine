#include "Engine/MouseEngineContext.h"

int main(int argc, char* argv[])
{
    MouseEngineContext* engineContext = MouseEngineContext::GetInstance();
    engineContext->EngineLoop();
    
    return 0;
}