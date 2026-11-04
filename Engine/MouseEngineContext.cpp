#include "MouseEngineContext.h"

#include <algorithm>

#include "BaseCamera.h"
#include "Object.h"
#include "Shader.h"
#include "Content/Meshes/CubeMesh.h"
#include "Content/Meshes/PyramidMesh.h"
#include "Temporary/AssessmentHouse.h"
#include "TimeManager.h"


MouseEngineContext::MouseEngineContext()
{
    // Order is important
    if (!InitialiseGLFW())
        return;
    if (!InitialiseGLAD())
        return;
    if (!InitialiseDebugContext())
        return;
    house = new AssessmentHouse();

    timeManager = new TimeManager();

    print_debug_line("Engine context created");
}

MouseEngineContext::~MouseEngineContext()
{
    delete house;
    delete timeManager;
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

void MouseEngineContext::HandleProcess()
{
    timeManager->Update();
    float deltaTime = timeManager->GetWorldDeltaTimef();
    
    for (Object* object : processObjects)
    {
        // Thanks to the ~Object deconstructor, this value *should* never be null, might need to revisit
        object->Process(deltaTime);
    }
}

void MouseEngineContext::EngineLoop()
{
    Shader shader(R"(C:\code\cpp\MouseEngine\Engine\Content\Shaders\basic_vertex.vert)",
                  R"(C:\code\cpp\MouseEngine\Engine\Content\Shaders\basic_fragment.frag)");
    
    PyramidMesh cube1 = PyramidMesh();
    cube1.transform.SetScale(glm::vec3(1));
    cube1.transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    
    BaseCamera camera = BaseCamera();
    camera.transform.SetPosition(glm::vec3(-15, 0, 0));
    camera.SetAspectRatio(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    
    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    while (!glfwWindowShouldClose(contextWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // glClear(GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 0.9f, 1.0f, 1.0f);
        
        cube1.transform.SetRotation(glm::vec3(glfwGetTime() * 25));
        
        shader.SetUniform("u_view", camera.GetView());
        shader.SetUniform("u_projection", camera.GetProjection());
        
        cube1.Render(&shader);
        
        HandleProcess();
        
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

void MouseEngineContext::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_SPACE)
            house->SwapRoofColor();
        if (key == GLFW_KEY_F1)
            ToggleWireframe();
    }

    for (IKeyboardInputCallback* object : inputObjects)
        if (object != nullptr)
            object->InputCallback(window, key, scancode, action, mods);
}

void MouseEngineContext::StaticInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    engineContextInstance->InputCallback(window, key, scancode, action, mods);
}