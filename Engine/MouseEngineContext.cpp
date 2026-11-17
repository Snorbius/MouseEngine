#include "MouseEngineContext.h"

#include <algorithm>
#include <format>

#include "AssetManager.h"
#include "BaseCamera.h"
#include "BaseRenderer.h"
#include "InputManager.h"
#include "Object.h"
#include "Shader.h"
#include "Texture.h"
#include "Content/Meshes/CubeMesh.h"
#include "Content/Meshes/PyramidMesh.h"
#include "Temporary/AssessmentHouse.h"
#include "TimeManager.h"
#include "Content/Meshes/SphereMesh.h"
#include "Interfaces/IKeyboardInputCallback.h"
#include "Temporary/Assessment3D.h"
#include "Temporary/AssessmentGraphicalPolish.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiWindows/EngineMenuBar.h"
#include "ImGuiWindows/EngineUI.h"
#include "ImGuiWindows/MaterialCreator.h"
#include "Resources/Material.h"
#include "Resources/Resource.h"


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
    
    house = new AssessmentHouse();

    print_debug_line("Engine context created");
}

MouseEngineContext::~MouseEngineContext()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    
    delete house;
    delete Time;
    delete Input;
    delete Assets;
    delete Renderer;
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
    Input->Update();
    float deltaTime = Time->GetWorldDeltaTimef();
    
    for (Object* object : processObjects)
    {
        // Thanks to the ~Object deconstructor, this value *should* never be null, might need to revisit
        object->Process(deltaTime);
    }
}

void MouseEngineContext::EngineLoop()
{
    Shader shader = *Assets->LoadShader({
        .vertexPath = R"(Engine/Content/Shaders/basic_vertex.vert)", 
        .fragmentPath = R"(Engine/Content/Shaders/basic_fragment.frag)"
    });
    
    BaseCamera camera = BaseCamera();
    camera.transform.SetPosition(glm::vec3(0, 0, 15));
    camera.transform.SetRotation({0, -90.0f, 0});
    camera.SetAspectRatio(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    activeCamera = &camera;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    AssessmentGraphicalPolish polish;
    
    EngineUI engineUI;
    
    Input->SetMouseCaptured(true);
    Input->SetMouseVisibility(false);
    
    MeshComponent test(
        Assets->LoadMesh("Engine/Content/Meshes/cirno.obj"),
        nullptr
    );
    test.transform.SetScale(4);
    
    while (!glfwWindowShouldClose(contextWindow))
    {
        glDisable(GL_SCISSOR_TEST);
        Renderer->SetClearColor(glm::vec4(1.0f, 0.9f, 1.0f, 1.0f));
        Renderer->ClearScreen();
        glEnable(GL_SCISSOR_TEST);
        
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        
        engineUI.Draw();
        
        for (Shader* element : Assets->GetAllLoadedShaders())
        {
            element->SetUniform("u_view", camera.GetView());
            element->SetUniform("u_projection", camera.GetProjection());
        }

        if (numPlayers > 1)
        {
            int rows = static_cast<int>(ceil(sqrt(numPlayers - 1)));
            int columns = static_cast<int>(ceil(sqrt(numPlayers)));
            int viewportWidth = framebufferSize.x / columns;
            int viewportHeight = framebufferSize.y / rows;
            
            for (int i = 0; i < numPlayers; ++i)
            {
                int x = viewportWidth * (i % columns);
                // int y = viewportHeight * (i % columns * columns);
                int y = viewportHeight * floor((i / columns));
                
                activeCamera->SetAspectRatio(static_cast<float>(viewportWidth), static_cast<float>(viewportHeight));
                Renderer->SetViewportDimensions(x, y, viewportWidth, viewportHeight);
                Renderer->RenderScreen();
            }
        }
        else
        {
            activeCamera->SetAspectRatio(static_cast<float>(framebufferSize.x), static_cast<float>(framebufferSize.y));
            Renderer->SetViewportDimensions(0, 0, framebufferSize.x, framebufferSize.y);
            Renderer->RenderScreen();
        }
        
        
        HandleProcess();
       
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        GLFWwindow* backupContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupContext);
        
        glfwSwapBuffers(contextWindow);
        
        glfwPollEvents();
    }
}

void MouseEngineContext::RegisterForInput(IKeyboardInputCallback* object)
{
    inputObjects.emplace_back(object);
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

void MouseEngineContext::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_SPACE)
            house->SwapRoofColor();
        if (key == GLFW_KEY_F1)
            ToggleWireframe();
    }
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        Input->SetMouseCaptured(!Input->GetMouseCaptured());
        Input->SetMouseVisibility(!Input->GetMouseVisible());
    }

    for (IKeyboardInputCallback* object : inputObjects)
        if (object != nullptr)
            object->InputCallback(window, key, scancode, action, mods);
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
    if (activeCamera != nullptr)
        activeCamera->SetAspectRatio(static_cast<float>(width), static_cast<float>(height));
}

void MouseEngineContext::StaticInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    engineContextInstance->InputCallback(window, key, scancode, action, mods);
}
