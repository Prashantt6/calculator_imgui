#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include<GLFW/glfw3.h>
#include <iostream>
#include<vector>

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
        static bool shift_btn = false;
        static bool alpha_btn = false;
        static bool mode_btn = false;
        static bool on_btn = false;
        static bool display = false;
        ImGui::Begin("SCIENTIFIC CALCULATOR", &show_demo_window);

        // Widgets 
        // ImGui::Text("Choose the type of operation");
        // ImGui::SameLine();
        if(display){
            ImGui::BeginChild("Display",ImVec2(200,80),true);
        // Operation for Mode button
        
        if(mode_btn){
        if (ImGui::Button("INTEGER")) {
                // show_int_calc = true;
                show_float_calc = false;
                mode_btn=false;  
            }
         ImGui::SameLine();    
        
        if (ImGui::Button("FLOAT")) {
            show_int_calc = false;
            //  show_float_calc = true;
             mode_btn=false;  
        }  
          
        }


            ImGui::EndChild();
        }
        if(ImGui::Button("SHIFT")){
            shift_btn = true;
            display= true;
        }
        ImGui::SameLine();
        if(ImGui::Button("ALPHA")){
            alpha_btn = true;
            display = true;
        }
        ImGui::SameLine();
        if(ImGui::Button("Mode")){
            mode_btn = true;
            display = true;
            
        }
        // static std::vector<float> numbers(100,0.0f);

        // for(int i = 0 ; i<numbers.size(); ++i){
        //     ImGui::PushID(i);
        //     // ImGui::
        // }
        ImGui::BeginChild("Number box", ImVec2(145,115),true);
        if(ImGui::Button("7")){

        }
        ImGui::SameLine();
         if(ImGui::Button("8")){

        }
        ImGui::SameLine();
         if(ImGui::Button("9")){

        }
           ImGui::SameLine();
           ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));        // Button background
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 1.0f, 1.0f)); // Hover color
ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.5f, 0.8f, 1.0f));  
         if(ImGui::Button("DEL")){

        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));        // Button background
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 1.0f, 1.0f)); // Hover color
ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.5f, 0.8f, 1.0f));  
         if(ImGui::Button("AC")){

        }
        ImGui::PopStyleColor(3);
         if(ImGui::Button("4")){

        }
           ImGui::SameLine();
         if(ImGui::Button("5")){

        }
           ImGui::SameLine();
         if(ImGui::Button("6")){

        }
           ImGui::SameLine();
         if(ImGui::Button("*")){

        }
           ImGui::SameLine();
         if(ImGui::Button("/")){

        }
         if(ImGui::Button("1")){

        }
           ImGui::SameLine();
         if(ImGui::Button("2")){

        }
           ImGui::SameLine();
        if(ImGui::Button("3")){

        }
        ImGui::SameLine();
        if(ImGui::Button("+")){

        }
        ImGui::SameLine();
        if(ImGui::Button("-")){

        }
        
        if(ImGui::Button("0")){

        }
        ImGui::SameLine();
        if(ImGui::Button("CALC")){

        }
        ImGui::EndChild();

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
                operation1 = "Multiplication";
                
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