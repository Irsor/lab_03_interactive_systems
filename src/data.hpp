#include <vector>
#include "../external/imgui/imgui.h"

enum WorkingMode
{
    FIRST,
    SECOND,
    THIRD
};

class Data
{
public:
    Data() {};
    Data(WorkingMode mode, int count = 11);

    int getTimer(int index);
    ImVec2 getPosition(int index);

private:
    std::vector<ImVec2> positions;
    std::vector<int> timers;

    int createRandomValue(int x, int y);
    int createRandomValue(int x1, int x2, int y1, int y2);
};
