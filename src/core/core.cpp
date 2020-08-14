//
//#include "core/core.h"
//#include "../../include/platform/opengl/opengl_rendering_context.h"
//#include "../../include/platform/opengl/opengl_imgui_overhead.h"
//#include <imgui.h>
//#include <platform/opengl/opengl_rendering_context.h>
//
//namespace Spark {
//    class Core::CoreData {
//        public:
//            CoreData();
//            ~CoreData();
//
//            void Initialize();
//            void Update();
//            void Shutdown();
//
//            Spark::ECS::Entities::EntityManager* GetEntityManager();
//
//        private:
//            ECS::Entities::EntityManager _entityManager {};
//            std::vector<ECS::Systems::BaseComponentSystemInterface*> _systems;
//            Graphics::Context::RenderingContext* _context;
//    };
//
//    Core* Core::_world = nullptr;
//
//    ECS::Entities::EntityManager *Core::GetEntityManager() {
//        return _data->GetEntityManager();
//    }
//
//    Core* Core::GetInstance() {
//        if (!_world) {
//            _world = new Core();
//        }
//
//        return _world;
//    }
//
//    Core::Core() : _data(new CoreData()) {
//        // Nothing to do here.
//    }
//
//    Core::~Core() {
//        delete _data;
//    }
//
//    void Core::Initialize() {
//        _data->Initialize();
//    }
//
//    void Core::Update() {
//        _data->Update();
//    }
//
//    void Core::Shutdown() {
//        _data->Shutdown();
//    }
//
//
//    Spark::ECS::Entities::EntityManager *Core::CoreData::GetEntityManager() {
//        return &_entityManager;
//    }
//
//    Core::CoreData::CoreData() {
//        _context = new Platform::OpenGL::OpenGLRenderingContext();
//    }
//
//    Core::CoreData::~CoreData() {
//
//    }
//
//    void Core::CoreData::Initialize() {
//    }
//
//    void Core::CoreData::Update() {
////        // Our state
////        bool show_demo_window = true;
////        bool show_another_window = false;
////        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
////        Platform::OpenGL::OpenGLWindow* windoww = dynamic_cast<Platform::OpenGL::OpenGLWindow*>(_context->GetWindow());
////        //windoww->~OpenGLWindow();
////
////        GLFWwindow* window = static_cast<GLFWwindow *>(_context->GetWindow()->GetNativeWindow());
////        Platform::OpenGL::OpenGLImGuiOverhead* imGuiOverhead = dynamic_cast<Platform::OpenGL::OpenGLImGuiOverhead*>(_context->GetImGui());
////
////        // Main loop
////        while (!glfwWindowShouldClose(window))
////        {
////            // Poll and handle events (inputs, window resize, etc.)
////            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
////            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
////            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
////            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
////            glfwPollEvents();
////
////            // Start the Dear ImGui frame
////            imGuiOverhead->StartFrame();
////
////            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
////            if (show_demo_window)
////                ImGui::ShowDemoWindow(&show_demo_window);
////
////            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
////            {
////                static float f = 0.0f;
////                static int counter = 0;
////
////                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
////
////                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
////                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
////                ImGui::Checkbox("Another Window", &show_another_window);
////
////                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
////                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
////
////                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
////                    counter++;
////                ImGui::SameLine();
////                ImGui::Text("counter = %d", counter);
////
////                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
////                ImGui::End();
////            }
////
////            // 3. Show another simple window.
////            if (show_another_window)
////            {
////                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
////                ImGui::Text("Hello from another window!");
////                if (ImGui::Button("Close Me"))
////                    show_another_window = false;
////                ImGui::End();
////            }
////
////            // Rendering
////            int display_w, display_h;
////            glfwGetFramebufferSize(window, &display_w, &display_h);
////            glViewport(0, 0, display_w, display_h);
////            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
////            glClear(GL_COLOR_BUFFER_BIT);
////
////            imGuiOverhead->RenderFrame();
////            imGuiOverhead->EndFrame();
////
////            glfwSwapBuffers(window);
////        }
//    }
//
//    void Core::CoreData::Shutdown() {
//        delete _context;
//    }
//}
