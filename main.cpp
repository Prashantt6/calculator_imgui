#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include<GLFW/glfw3.h>
#include <iostream>

int main(){ 
    // Initializing glfw 
    if ( !glfwInit()) {
        std::cerr<<"Failed to initialize GLFW";
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800,800,"IMGUI WINDOW", NULL , NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initializing imgui 
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark(); //Sets dark theme

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Main loop

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        // Starting imgui frame 
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show_demo_window = true ;
        static float float_val1 = 0.0f;
        static float float_val2 = 0.0f;
        static int int_val1 = 0;
        static int int_val2 = 0;
        static const char* operation1 = " ";
         static const char* operation2 = " ";
        static int result1 = 0;
        static float result2 = 0.0f;
         static const char* error = "";

        static bool show_int_calc = false;
        static bool show_float_calc = false;

        ImGui::Begin("SIMPLE CALCULATOR", &show_demo_window);

        // Widgets 
        ImGui::Text("Choose the type of operation");
        ImGui::SameLine();

        if (ImGui::Button("INTEGER")) {
                show_int_calc = true;
                show_float_calc = false;
            }
         ImGui::SameLine();    
        
        if (ImGui::Button("FLOAT")) {
            show_int_calc = false;
             show_float_calc = true;
        }    


        if(show_int_calc){
            // ImGui::SliderInt("Integer slide 1", &int_val1, -1000,1000);
            // ImGui::SliderInt("Integer slide 2", &int_val2, -1000, 1000);
            ImGui::InputInt("Integer value 1", &int_val1);
            ImGui::InputInt("Integer value", &int_val2);
            if(ImGui::Button("ADD")){
                result1 = int_val1 + int_val2;
                operation1 = " Addition";
            }
            ImGui::SameLine();
            if(ImGui::Button("SUBTRACT")){
                result1 = int_val1 - int_val2;
                operation1 = " Substraction";
            
            }
            ImGui::SameLine();
            if(ImGui::Button("MULTIPLY"))
            {
                result1 = int_val1 * int_val2;
                operation2 = "Multiplication";
                
            }
            ImGui::SameLine();
            if(ImGui::Button("DIVIDE")){
                if(int_val2!= 0){
                    result1 = int_val1 / int_val2 ;
                    
                }
                else {
                    // ImGui::Text("Cannot be divided by zero");
                    result1 = 0;
                    error = "CANNOT BE DIVIDED BY ZERO";
                }
                operation1 = "Divison";
                
            }
            if (error[0] != '\0') {
                     ImGui::Text("%s", error);
                }
            ImGui::Text("You did %s", operation1);
            ImGui::Text("Result : %d",result1);



        }
        
        if(show_float_calc){
            // ImGui::SliderFloat("Float slider 1" , &float_val1 , -1000.0f , 1000.0f);
            // ImGui::SliderFloat("Float slider 2" , &float_val2 , -1000.0f , 1000.0f);

            ImGui::InputFloat("Integer value 1", &float_val1);
            ImGui::InputFloat("Integer value", &float_val2);
            if(ImGui::Button("ADD"))
            {
                result2 = float_val1 + float_val2 ;
                operation2 = "Addition";
            }
             ImGui::SameLine();
             if(ImGui::Button("SUBTRACT"))
            {
                result2 = float_val1 - float_val2 ;
                operation2 = "Subtraction";
            }
             ImGui::SameLine();
             if(ImGui::Button("MULTIPLY"))
            {
                result2 = float_val1 * float_val2 ;
                operation2 = "Multiplication";
            }
             ImGui::SameLine();
            if(ImGui::Button("DIVIDE")){
                if(float_val2!= 0){
                    result2 = float_val1 / float_val2 ;
                }
                else {
                
                    result2 = 0;
                    error = "CANNOT BE DIVIDED BY ZERO";
                }
                operation2 = "Divison";
            }
             if (error[0] != '\0') {
                     ImGui::Text("%s", error);
                }
            ImGui::Text("You did %s", operation2);
            ImGui::Text("Result : %.3f",result2);
        }
           ImGui::End();
           
        //    render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window , &display_w, &display_h);
        glViewport(0,0,display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Sets dark gray background

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);



    }

    // cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


// to build in terminal cmake --build build