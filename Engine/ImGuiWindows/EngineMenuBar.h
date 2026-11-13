#pragma once

class EngineUI;

class EngineMenuBar
{
public:
    EngineMenuBar(EngineUI* root);
    
private:
    EngineUI* root;
    
public:
    void Draw();
};
