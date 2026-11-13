#include "EngineUI.h"

EngineUI::EngineUI()
{
    menuBar = new EngineMenuBar(this);
    materialWindow = new MaterialCreator();
}

EngineUI::~EngineUI()
{
    delete menuBar;
    delete materialWindow;
}

void EngineUI::Draw()
{
    menuBar->Draw();
    if (showMaterialWindow)
        materialWindow->Draw();
}
