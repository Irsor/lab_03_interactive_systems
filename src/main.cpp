#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

#include <iostream>

#include "imgui_utils.hpp"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    float width = 640;
    float height = 480;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Лабораторная работа № 3", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    /* Initialize ImGui */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("../assets/fonts/DudkaThin.ttf", 20, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");

    bool checkBoxValue = false;

    // Загрузка изображения.
    int imageWidth;
    int imageHeight;
    int channels;
    unsigned char* imageData = stbi_load("../assets/images/hearths.jpg", &imageWidth, &imageHeight, &channels, STBI_rgb_alpha);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    Timer timer;
    std::thread thread([&timer]() 
    {
        timer.start();
    });
    thread.detach();    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* ImGui Frame */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Get GLFW window size
        int fb_width, fb_height;
        glfwGetFramebufferSize(window, &fb_width, &fb_height);

        utils::createMenuBar(&timer);
        // Ширина и длинна предыдущего виджета.
        auto previousWidgetSize = ImGui::GetItemRectSize();

        // Set ImGui window position and size
        ImGui::SetNextWindowPos(ImVec2(0, previousWidgetSize.y));
        ImGui::SetNextWindowSize(ImVec2(fb_width, fb_height - previousWidgetSize.y));
        ImGui::Begin("My Fullscreen Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 320);
        
        ImGui::BeginChild("LeftChild", ImVec2(0, 0), true, ImGuiWindowFlags_NoTitleBar);
        ImGui::Text("Входные значения:");
        ImGui::Text(timer.getCurrentWidgetName().c_str());
        ImGui::EndChild();

        ImGui::NextColumn();

        ImGui::BeginChild("RightChild", ImVec2(0, 0), true, ImGuiWindowFlags_NoTitleBar);
        ImGui::Text("Выходные значения:");
        auto logs = timer.getLogs();
        for (auto log : logs)
        {
            ImGui::Text(log.c_str());
        }
        ImGui::EndChild();

        ImGui::End();
        ImGui::Render();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

        /* ImGui Render */
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    stbi_image_free(imageData);
    glfwTerminate();
    return 0;
}
