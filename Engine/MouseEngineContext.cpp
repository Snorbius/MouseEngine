#include "MouseEngineContext.h"

#include <algorithm>
#include <format>
#include <utility>
#include <variant>

#include "AssetManager.h"
#include "BaseRenderer.h"
#include "InputManager.h"
#include "Object.h"
#include "TimeManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ECS/ComponentManager.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/CameraMovementComponent.h"
#include "ECS/Components/NewMeshComponent.h"
#include "ECS/Components/PlayerMovementComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ImGuiWindows/EngineUI.h"
#include "Resources/Resource.h"
#include "Resources/Scene.h"


MouseEngineContext::MouseEngineContext()
{
    engineContextInstance = this;
    
    // Order is important
    if (!InitialiseGLFW())
        return;
    if (!InitialiseGLAD())
        return;
#if DEBUG_ENABLED
    if (!InitialiseDebugContext())
        return;
#endif
    InitialiseImGui();

    Time = new TimeManager();
    Input = new InputManager(contextWindow);
    Assets = new AssetManager();
    Renderer = new BaseRenderer();
    Components = new ComponentManager();
    Entities = new EntityManager();
    
    print_debug_line("Engine context created");
    
    LoadScene("Engine/Content/Scenes/FlatPlane.scene");
    
    Input->RegisterInputFunction(GLFW_KEY_F1, PRESSED, [this](float _){ToggleWireframe();});
    Input->RegisterInputFunction(GLFW_KEY_ESCAPE, PRESSED, [this](float _)
    {
        Input->SetMouseCaptured(!Input->GetMouseCaptured());
        Input->SetMouseVisibility(!Input->GetMouseVisible());
    });
}

MouseEngineContext::~MouseEngineContext()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    
    delete Time;
    delete Input;
    delete Assets;
    delete Renderer;
    delete Components;
    delete Entities;
}

MouseEngineContext* MouseEngineContext::GetInstance()
{
    if (engineContextInstance == nullptr)
        engineContextInstance = new MouseEngineContext();
    
    return engineContextInstance;
}

bool MouseEngineContext::InitialiseGLFW()
{
    if (!glfwInit())
    {
        print_error("Failed to initialize GLFW");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if DEBUG_ENABLED
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
    
    contextWindow = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 
                                "Mouse Engine", nullptr, nullptr);
    
    glfwMakeContextCurrent(contextWindow);
    
    glfwSetKeyCallback(contextWindow, StaticInputCallback);
    glfwSetFramebufferSizeCallback(contextWindow, StaticResizeCallback);
    
    return true;
}

bool MouseEngineContext::InitialiseGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        print_error("Failed to initialize GLAD");
        return false;
    }
    
    return true;
}

bool MouseEngineContext::InitialiseDebugContext()
{
#if DEBUG_ENABLED
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    
    return true;
    }
    print_warning("Failed to initialise opengl debug context.");
#endif
    return false;
}

void MouseEngineContext::ToggleWireframe()
{
    wireframe = !wireframe;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    if (wireframe)
        glDisable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);
}

void MouseEngineContext::InitialiseImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(contextWindow, true);
    ImGui_ImplOpenGL3_Init();
}

void MouseEngineContext::HandleProcess()
{
    Time->Update();
    float deltaTime = Time->GetWorldDeltaTimef();
    Input->Update(deltaTime);
    
    for (Object* object : processObjects)
    {
        // Thanks to the ~Object deconstructor, this value *should* never be null, might need to revisit
        object->Process(deltaTime);
    }
}

void MouseEngineContext::RenderImGui(EngineUI* engineUI)
{
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
        
    engineUI->Draw();
        
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
    GLFWwindow* backupContext = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backupContext);
}

void MouseEngineContext::EngineLoop()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    EngineUI engineUI;
    
    Input->SetMouseCaptured(true);
    Input->SetMouseVisibility(false);
    
    Entity camera = Components->FilterEntities<CameraComponent>(Entities->GetAllEntities())[0];
    
    while (!glfwWindowShouldClose(contextWindow))
    {
        Renderer->ClearEntireScreen();
        
        HandleProcess();
        
        Components->GetComponent<PlayerMovementComponent>(camera).Process(Time->GetWorldDeltaTimef());
        Components->GetComponent<CameraMovementComponent>(camera).Process(Time->GetWorldDeltaTimef());
        
        CameraComponent& cameraComp = Components->GetComponent<CameraComponent>(camera);
        TransformComponent& cameraTransform = Components->GetComponent<TransformComponent>(camera);
        
        cameraComp.SetAspectRatio(static_cast<float>(framebufferSize.x), static_cast<float>(framebufferSize.y));
        Renderer->SetClearColor(glm::vec4(1.0f, 0.9f, 1.0f, 1.0f));
        Renderer->SetViewportDimensions(0, 0, framebufferSize.x, framebufferSize.y);
        Renderer->RenderScreen(cameraComp.GetView(), cameraComp.GetProjection());
        
        RenderImGui(&engineUI);
        
        glfwSwapBuffers(contextWindow);
        
        glfwPollEvents();
    }
}

void MouseEngineContext::RegisterForProcess(Object* object)
{
    // Only add it to the list if it doesn't already exist. This might not be worth it for performance reasons?
    if (std::ranges::find(processObjects, object) == processObjects.end()) 
        processObjects.emplace_back(object);
}

void MouseEngineContext::UnRegisterForProcess(Object* object)
{
    auto index = std::ranges::find(processObjects, object);
    if (index != processObjects.end())
        processObjects.erase(index);
}

bool MouseEngineContext::HasFocus() const
{
    return glfwGetWindowAttrib(contextWindow, GLFW_FOCUSED);
}

void MouseEngineContext::LoadScene(const std::string& scenePath)
{
    if (!std::filesystem::exists(scenePath))
        return;
    
    Scene* newScene = Scene::LoadResource<Scene>(scenePath);
    if (newScene == nullptr)
        return;
    
    if (ActiveScene != nullptr)
        delete ActiveScene;
    ActiveScene = newScene;
}

void MouseEngineContext::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input->InputCallback(window, key, scancode, action, mods);
}

void MouseEngineContext::StaticResizeCallback(GLFWwindow* window, int width, int height)
{
    engineContextInstance->ResizeCallback(window, width, height);
}

void MouseEngineContext::ResizeCallback(GLFWwindow* window, int width, int height)
{
    framebufferSize.x = width;
    framebufferSize.y = height;
    
    Renderer->SetViewportDimensions(0, 0, width, height);
    // if (activeCamera != nullptr)
    //     activeCamera->SetAspectRatio(static_cast<float>(width), static_cast<float>(height));
}

void MouseEngineContext::StaticInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    engineContextInstance->InputCallback(window, key, scancode, action, mods);
}
