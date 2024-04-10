#include "imgui_utils.hpp"

void utils::createMenuBar(Timer* timer)
{
    if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Файл"))
            {
                if (ImGui::MenuItem(timer->getTextValue(0).c_str(), "Ctrl+O")) 
                {
                    timer->setGate(false);
                }
                if (ImGui::MenuItem(timer->getTextValue(1).c_str(), "Ctrl+S")) 
                {
                    timer->setGate(false);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Редактировать"))
            {
                if (ImGui::MenuItem(timer->getTextValue(2).c_str(), "Ctrl+C")) 
                {
                    timer->setGate(false);
                }
                if (ImGui::MenuItem(timer->getTextValue(3).c_str(), "Ctrl+V")) 
                {
                    timer->setGate(false);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Вид"))
            {
                if (ImGui::BeginMenu("Зум"))
                {
                    if (ImGui::MenuItem(timer->getTextValue(4).c_str()))
                    {
                        timer->setGate(false);
                    }
                    if (ImGui::MenuItem(timer->getTextValue(5).c_str()))
                    {
                        timer->setGate(false);
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Темы", ""))
                {
                    if (ImGui::MenuItem(timer->getTextValue(6).c_str()))
                    {
                        ImGui::StyleColorsLight();
                        timer->setGate(false);

                    }
                    if (ImGui::MenuItem(timer->getTextValue(7).c_str()))
                    {
                        ImGui::StyleColorsDark();
                        timer->setGate(false);
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();  
            }
            if (ImGui::BeginMenu("Окно"))
            {
                if (ImGui::MenuItem(timer->getTextValue(8).c_str()))
                {
                    timer->setGate(false);
                }
                if (ImGui::MenuItem(timer->getTextValue(9).c_str()))
                {
                    timer->setGate(false);
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Помощь"))
            {
                if (ImGui::MenuItem(timer->getTextValue(10).c_str()))
                {
                    timer->setGate(false);
                }
                if (ImGui::MenuItem(timer->getTextValue(11).c_str()))
                {
                    timer->setGate(true);
                }
                ImGui::EndMenu();
            }
            
            ImGui::EndMainMenuBar();
        }
}