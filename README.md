# Mouse Engine
This engine primarily acts as a learning opportunity, do not expect this to be actually *good*. :)
The engine is written using modern openGL (4.3+). [GLFW](https://www.glfw.org/) and [GLAD](https://github.com/dav1dde/glad) are used for opengl communication.

(the readme and overall engine structure are still heavily wip, expect things to change rather frequently)

(also, it's mouse as in 🐭, not 🖱️)
## Engine Context
MouseEngineContext.h/cpp

This class (and associated singleton, we'll see if I end up regretting this) serves as the primary engine entry point and accessor. It initializes the engine, sets up glfw, glad etc. and runs the main engine loop. Every class in the engine has access to this one class and will be able to access other critical parts of the engine through this one (such as manager classes and such). 

### Mouse Logs
LogManager.h/cpp

This namespace primarily acts as a helper library with some print functions and opengl error checking. The LogManager is planned to handle some debug and crash logging in the future.