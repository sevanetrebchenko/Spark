
#include <glad/glad.h>
#include <platform/opengl/opengl_rendering_context.h>
#include <utilitybox/logger/logging_system.h>

namespace Spark::Graphics {
    //------------------------------------------------------------------------------------------------------------------
    // OPENGL RENDERING CONTEXT DATA
    //------------------------------------------------------------------------------------------------------------------
    class OpenGLRenderingContext::OpenGLRenderingContextData {
        public:
            explicit OpenGLRenderingContextData(GLFWwindow* window);
            ~OpenGLRenderingContextData();

        private:
            void InitializeGlad();
            void InitializeOpenGLContext();

            GLFWwindow* _window;
            UtilityBox::Logger::LoggingSystem _loggingSystem;
    };

    OpenGLRenderingContext::OpenGLRenderingContextData::OpenGLRenderingContextData(GLFWwindow* window) : _window(window) {
        InitializeOpenGLContext();

        // Load Glad OpenGL extension (sets up OpenGL function pointers).
        InitializeGlad();

        glfwSwapInterval(1);
    }

    OpenGLRenderingContext::OpenGLRenderingContextData::~OpenGLRenderingContextData() {
        glfwTerminate();
    }

    void OpenGLRenderingContext::OpenGLRenderingContextData::InitializeGlad() {
        int initializationCode = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        // Failed to initialize Glad.
        if (!initializationCode) {
            _loggingSystem.Log(UtilityBox::Logger::LogMessageSeverity::SEVERE, "Exception thrown: failed to initialize Glad. Error code: %i", initializationCode);
            throw std::runtime_error("Glad initialization failed.");
        }
        else {
            _loggingSystem.Log(UtilityBox::Logger::LogMessageSeverity::DEBUG, "Successfully loaded and initialized Glad.");
        }
    }

    void OpenGLRenderingContext::OpenGLRenderingContextData::InitializeOpenGLContext() {
        // Set current OpenGL context to this window.
        glfwMakeContextCurrent(_window);
        _loggingSystem.Log(UtilityBox::Logger::LogMessageSeverity::DEBUG, "Current OpenGL context successfully set to this window.");
    }

    //------------------------------------------------------------------------------------------------------------------
    // OPENGL RENDERING CONTEXT
    //------------------------------------------------------------------------------------------------------------------
    OpenGLRenderingContext::OpenGLRenderingContext(GLFWwindow* window) : _data(new OpenGLRenderingContextData(window)) {
        // Nothing to do here.
    }

    OpenGLRenderingContext::~OpenGLRenderingContext() {
        delete _data;
    }
}
