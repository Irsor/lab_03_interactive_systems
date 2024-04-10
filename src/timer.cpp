#include "timer.hpp"

Timer::Timer()
{
    setlocale(LC_ALL, "russian");
    srand(time(nullptr));

    for (int i = 0; i < 10; i++)
    {
        int timeValue = rand() % 6;
        this->times.push_back(timeValue);
        
        int itemIndex = rand() % 12;
        this->menuIndexes.push_back(itemIndex);
    }
    
}

std::string Timer::checkValue(int menuIndex)
{
    if (menuIndex == this->menuIndexes[index])
    {
        std::time_t time = std::time(nullptr) - this->timer;
        index++;
        if (index < 10)
        {
            std::thread thread([this]()
            {
                gate = false;
                this->start();
            });
            thread.detach();
        }

        logs.push_back(std::to_string(time));
        return std::to_string(time);
    }
    
    logs.push_back("Введено неверное значение!");
    return "Введено неверное значение!";
}

bool Timer::getGate()
{
    return this->gate;
}

void Timer::setGate(bool value)
{
    gate = value;
}

void Timer::start()
{
    std::this_thread::sleep_for(std::chrono::seconds(this->times[this->index]));
    this->timer = std::time(nullptr);
    this->gate = true;
    std::cout << this->textValues[this->menuIndexes[this->index]] << std::endl;
}

std::string Timer::getCurrentWidgetName()
{
    if (gate)
    {
        return this->textValues[this->menuIndexes[this->index]];
    }
    
    return "";
}

std::string Timer::getTextValue(int index)
{
    return textValues[index];
}

std::vector<std::string> Timer::getLogs()
{
    return logs;
}
