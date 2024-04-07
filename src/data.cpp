#include "data.hpp"

Data::Data(WorkingMode mode, int count)
{
    switch (mode)
    {
    case WorkingMode::FIRST:
        for (int i = 0; i < count; i++)
        {
            positions.push_back(ImVec2(1000, 590));
            timers.push_back(createRandomValue(1, 3));
        }
        
        break;

    case WorkingMode::SECOND:
        for (int i = 0; i < count; i++)
        {
            positions.push_back(ImVec2(createRandomValue(0, 1000), 590));
            timers.push_back(createRandomValue(1, 3));
        }

        break;

    case WorkingMode::THIRD:
        for (int i = 0; i < count; i++)
        {
            positions.push_back(ImVec2(createRandomValue(0, 1000), createRandomValue(0, 1000)));
            timers.push_back(createRandomValue(1, 3));
        }

        break;
    }
    
}

int Data::getTimer(int index)
{
    return timers[index];
}

ImVec2 Data::getPosition(int index)
{
    return positions[index];
}

int Data::createRandomValue(int x, int y)
{
    return x + rand() % (y - x + 1);
}

int Data::createRandomValue(int x1, int x2, int y1, int y2)
{
    if (rand() % 2 == 0)
    {
        return createRandomValue(x1, x2);
    }
    
    return createRandomValue(y1, y2);
}
