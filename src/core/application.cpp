
#include <core/application.h>
#include <graphics/window/window.h>

namespace Spark {
    //------------------------------------------------------------------------------------------------------------------
    // APPLICATION DATA
    //------------------------------------------------------------------------------------------------------------------
    class Application::ApplicationData {
        public:
            ApplicationData();
            ~ApplicationData();

            void Run();

        private:
            Graphics::Window* _window;

    };

    Application::ApplicationData::ApplicationData() : _window(Graphics::Window::Create()) {
        // Nothing to do here.
    }

    Application::ApplicationData::~ApplicationData() {
        delete _window;
    }

    void Application::ApplicationData::Run() {
    }


    //------------------------------------------------------------------------------------------------------------------
    // APPLICATION
    //------------------------------------------------------------------------------------------------------------------
    Application::Application() : _data(new ApplicationData()) {
        // Nothing to do here.
    }

    Application::~Application() {
        delete _data;
    }

    void Application::Run() {
        _data->Run();
    }
}