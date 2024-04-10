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
#include <windows.h>

enum ContentType 
{
    WORK_NAME, 
    WORK_GOAL,
    QUEST,
    HICK_LAW,
    MENU,
    IMGUI_DOC,
    IMGUI_MENU,
    EMPTY
};

ContentType type = ContentType::EMPTY;
char searchText[20] = "";

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    float width = 800;
    float height = 480;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Лабораторная работа № 4", NULL, NULL);
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
    io.Fonts->AddFontFromFileTTF("../assets/fonts/Involve-Regular.otf", 20, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    ImGui::StyleColorsClassic();

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

        // if (timer.getGate())
        {
            static int selectedOption = 0;
            static const char* options[] = { "Option 1", "Option 2" };
    
            ImGui::BeginGroup();
    
            for (int i = 0; i < IM_ARRAYSIZE(options); i++) {
                ImGui::SameLine();
                if (ImGui::Selectable(options[i], selectedOption == i, 0, ImVec2(100, 0))) {
                    selectedOption = i;
                }
            }
    
            ImGui::EndGroup();
    
            switch (selectedOption)
            {
            case  0:
                if (ImGui::TreeNode("Справочник"))
                {
                    if (ImGui::TreeNode("Информация о работе"))
                    {
                        if (ImGui::Button("Название работы"))
                        {
                            type = ContentType::WORK_NAME;                              
                        }

                        if (ImGui::Button("Цель работы"))
                        {
                            type = ContentType::WORK_GOAL;                              
                        }

                        if (ImGui::Button("Задание"))
                        {
                            type = ContentType::QUEST;                              
                        }

                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNode("Дополнительная информация"))
                    {
                        if (ImGui::Button("Закон Хика"))
                        {
                            type = ContentType::HICK_LAW;                              
                        }

                        if (ImGui::Button("Пункты меню"))
                        {
                            type = ContentType::MENU;                              
                        }

                        ImGui::TreePop();
                    }

                    if (ImGui::TreeNode("Документация"))
                    {
                        if (ImGui::Button("Документация ImGui"))
                        {
                            ShellExecute(0,"open","https://github.com/ocornut/imgui",NULL,NULL,SW_SHOWDEFAULT);
                        }

                        if (ImGui::Button("Меню"))
                        {
                            type = ContentType::IMGUI_MENU;                              
                        }

                        ImGui::TreePop();
                    }

                    ImGui::TreePop();
                }

                break;
            
            case 1:        
                ImGui::InputText("##", searchText, sizeof(searchText));
                ImGui::SameLine();
                if (ImGui::Button("Поиск"))
                {
                    if (strcmp(searchText, "название") == 0)
                    {
                        type = ContentType::WORK_NAME;
                    } else if (strcmp(searchText, "цель") == 0)
                    {
                        type = ContentType::WORK_GOAL;
                    } else if (strcmp(searchText, "задание") == 0)
                    {
                        type = ContentType::QUEST;
                    } else if (strcmp(searchText, "закон") == 0)
                    {
                        type = ContentType::HICK_LAW;
                    } else if (strcmp(searchText, "меню") == 0)
                    {
                        type = ContentType::MENU;
                    } else if (strcmp(searchText, "документация") == 0)
                    {
                        type = ContentType::IMGUI_DOC;
                    } 
                }

                ImGui::Text("название\nцель\nзадание\nзакон\nменю\nдокументация\n");
                break;
            }
        }

        ImGui::EndChild();

        ImGui::NextColumn();

        ImGui::BeginChild("RightChild", ImVec2(0, 0), true, ImGuiWindowFlags_NoTitleBar);

        switch (type)
        {
        case ContentType::WORK_NAME:
            ImGui::Text("Измерение времени реакции пользователя\n на события от выбора пункта меню.\n Использование метода Хика.");
            break;

        case ContentType::WORK_GOAL:
            ImGui::Text("Целью работы является фиксирование\n времени реакции пользователя на события\n на экране монитора посредством выбора пункта\n меню по системному таймеру и путем\n вычисления по методу Хика.");
            break;

        case ContentType::QUEST:
            ImGui::Text("Пользуясь инструментальными\n средствами, воспроизвести первичное\n окно с текстовой областью\n для выводов результатов и стандартную\n панель меню с перечисленными\n пунктами.");
            break;
        
        case ContentType::HICK_LAW:
            ImGui::Text("T = a+blog2(n + 1)\n Где T — среднее значение времени\n реакции по всем альтернативным сигналам;\n n — число равновероятных альтернативных сигналов;\n a и b — коэффициенты пропорциональности.");
            break;

        case ContentType::MENU:
            ImGui::Text("Файл\nПравка\nВид\nОкно\nСправка");
            break;
            
        case ContentType::IMGUI_MENU:
            ImGui::Text("if (ImGui::BeginMenu(File)");
            ImGui::Text("{");
            ImGui::Text("if (ImGui::MenuItem(New))");
            ImGui::Text("if (ImGui::MenuItem(Open))");
            ImGui::Text("if (ImGui::MenuItem(Save))");
            ImGui::Text("ImGui::EndMenu();");
            ImGui::Text("}");
            break;

        default:
            break;
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
