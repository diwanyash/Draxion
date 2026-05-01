#define IMGUI_IMPL_OPENGL_LOADER_IMGL3W
#include "ImGuiLayer.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>
#include "Draxion/Events/EventDispatcher.h"

/////////////TOBE_DELETED//////////

#include "Window.h"
#include "GLFW/glfw3.h"
#include "Application.h"

///////////////////////////////////


void Draxion::ImGuiLayer::OnAttach()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();


     // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void Draxion::ImGuiLayer::OnDetach()
{
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
}

void Draxion::ImGuiLayer::OnImGuiRender()
{
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

void Draxion::ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Draxion::ImGuiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    Application& app = Application::Get();
    io.DisplaySize = ImVec2{ app.GetWindow().GetWidth(), app.GetWindow().GetHeight()};

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if ( io.ConfigFlags & ImGuiConfigFlags_DockingEnable )
    {
        GLFWwindow* backup_currunt_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows(); 
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent( backup_currunt_context );
    }
}