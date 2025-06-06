#include "operation.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stack>
#include <vector>
#include <string>

std::string expression = "";
std::string result = "";
double evaluate(const std::string& expression);

int main() {
    // Initializing GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 800, "IMGUI WINDOW", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initializing ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Starting ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show_demo_window = true;
        static const char* error = "";
        static bool show_int_calc = false;
        static bool show_float_calc = false;
        static bool shift_btn = false;
        static bool alpha_btn = false;
        static bool mode_btn = false;
        static bool on_btn = false;
        static bool display = false;
        static bool dispnum = false;
        static bool calc = false;

        ImGui::Begin("SCIENTIFIC CALCULATOR", &show_demo_window);

        if (display) {
            ImGui::BeginChild("Display", ImVec2(200, 80), true);

            // Operation for Mode button
            if (mode_btn) {
                if (ImGui::Button("INTEGER")) {
                    show_float_calc = false;
                    mode_btn = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("FLOAT")) {
                    show_int_calc = false;
                    mode_btn = false;
                }
            }

            if (dispnum) {
                ImGui::Text("%s", expression.c_str());
            }

            if (calc) {
                dispnum = false;
                try {
                    result = std::to_string(evaluate(expression));
                } catch (const std::exception& e) {
                    result = "Error: " + std::string(e.what());
                }
                ImGui::Text("Result: %s", result.c_str());
            }

            ImGui::EndChild();
        }

        if (ImGui::Button("SHIFT")) {
            shift_btn = true;
            display = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("ALPHA")) {
            alpha_btn = true;
            display = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Mode")) {
            mode_btn = true;
            display = true;
        }

        ImGui::BeginChild("Number box", ImVec2(145, 115), true);

        if (ImGui::Button("7")) { expression += "7"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("8")) { expression += "8"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("9")) { expression += "9"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.5f, 0.8f, 1.0f));
        if (ImGui::Button("DEL")) {
            if (!expression.empty()) expression.pop_back();
            display = dispnum = true; calc = false;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.5f, 0.8f, 1.0f));
        if (ImGui::Button("AC")) {
            expression = "";
            display = dispnum = true; calc = false;
        }
        ImGui::PopStyleColor(3);

        if (ImGui::Button("4")) { expression += "4"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("5")) { expression += "5"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("6")) { expression += "6"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("*")) { expression += "*"; display = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("/")) { expression += "/"; display = true; calc = false; }

        if (ImGui::Button("1")) { expression += "1"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("2")) { expression += "2"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("3")) { expression += "3"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("+")) { expression += "+"; display = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("-")) { expression += "-"; display = true; calc = false; }

        if (ImGui::Button("0")) { expression += "0"; display = dispnum = true; calc = false; }
        ImGui::SameLine();
        if (ImGui::Button("CALC")) {
            calc = true;
            display = true;
        }

        ImGui::EndChild();
        ImGui::End();

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
// cmake --build build
