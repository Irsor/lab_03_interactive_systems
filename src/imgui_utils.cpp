#include "imgui_utils.hpp"

void utils::createMenuBar(Timer* timer)
{
    if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Файл"))
            {
                if (ImGui::MenuItem(timer->getTextValue(0).c_str(), "Ctrl+O")) 
                {
                    if (timer->getGate())
                    {
                        timer->checkValue(0);
                    }
                }
                if (ImGui::MenuItem(timer->getTextValue(1).c_str(), "Ctrl+S")) 
                {
                    if (timer->getGate())
                    {
                        timer->checkValue(1);
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Редактировать"))
            {
                if (ImGui::MenuItem(timer->getTextValue(2).c_str(), "Ctrl+C")) 
                {
                    if (timer->getGate())
                    {
                        timer->checkValue(2);
                    }
                }
                if (ImGui::MenuItem(timer->getTextValue(3).c_str(), "Ctrl+V")) 
                {
                    if (timer->getGate())
                    {
                        timer->checkValue(3);
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Вид"))
            {
                if (ImGui::BeginMenu("Зум"))
                {
                    if (ImGui::MenuItem(timer->getTextValue(4).c_str()))
                    {
                        if (timer->getGate())
                    {
                        timer->checkValue(4);
                    }
                    }
                    if (ImGui::MenuItem(timer->getTextValue(5).c_str()))
                    {
                        if (timer->getGate())
                    {
                        timer->checkValue(5);
                    }
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Темы", ""))
                {
                    if (ImGui::MenuItem(timer->getTextValue(6).c_str()))
                    {
                        ImGui::StyleColorsLight();
                        if (timer->getGate())
                        {
                            timer->checkValue(6);
                        }
                    }
                    if (ImGui::MenuItem(timer->getTextValue(7).c_str()))
                    {
                        ImGui::StyleColorsDark();
                        if (timer->getGate())
                        {
                            timer->checkValue(7);
                        }
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();  
            }
            if (ImGui::BeginMenu("Окно"))
            {
                if (ImGui::MenuItem(timer->getTextValue(8).c_str()))
                {
                    if (timer->getGate())
                    {
                        timer->checkValue(8);
                    }
                }
                if (ImGui::MenuItem(timer->getTextValue(9).c_str()))
                {
                    if (timer->getGate())
                    {
                        timer->checkValue(9);
                    }
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Помощь"))
            {
                if (ImGui::MenuItem(timer->getTextValue(10).c_str()))
                {
                    if (timer->getGate())
                    {
                        timer->checkValue(10);
                    }
                }
                if (ImGui::MenuItem(timer->getTextValue(11).c_str()))
                {
                    if (timer->getGate())
                    {
                        timer->checkValue(11);
                    }
                }
                ImGui::EndMenu();
            }
            
            ImGui::EndMainMenuBar();
        }
}