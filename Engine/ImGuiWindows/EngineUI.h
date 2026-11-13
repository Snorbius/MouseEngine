#pragma once
#include "EngineMenuBar.h"
#include "MaterialCreator.h"

class EngineUI
{
public:
    EngineUI();
    ~EngineUI();
    
private:
    EngineMenuBar* menuBar;
    MaterialCreator* materialWindow;
    
public:
    bool showMaterialWindow = false;
    
    void Draw();
};
