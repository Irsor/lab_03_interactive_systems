#include <vector>
#include <ctime>
#include <random>
#include <thread>
#include <ctime>
#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer();
    std::string checkValue(int menuIndex);
    bool getGate();
    void start();
    std::string getCurrentWidgetName();
    std::string getTextValue(int index);
    std::vector<std::string> getLogs();

private:
    std::vector<int> menuIndexes;
    std::vector<int> times;

    int index = 0;
    bool gate = false;
    std::time_t timer = NULL;
    
    std::vector<std::string> textValues{"Открыть", "Сохранить", "Копировать", "Вставить", "Внутрь", "Наружу", 
    "Светлая", "Темная", "Новое окно", "Закрыть окно", "Приветствие", "Подробнее"};

    std::vector<std::string> logs{};
};