#include <iostream>
#include <vector>


using namespace std;

unsigned int findRepeat(const vector<unsigned int>& numbers)
{
    unsigned int floor = 1;
    unsigned int ceiling = numbers.size() - 1;
    unsigned int middle;
    unsigned int lowerRangeFloor;
    unsigned int lowerRangeCeiling;
    unsigned int upperRangeFloor;
    unsigned int upperRangeCeiling;
 

    while (floor < ceiling)
    {
        middle            = (floor + ceiling) / 2;
        lowerRangeFloor   = floor;
        lowerRangeCeiling = middle;
        upperRangeFloor   = middle + 1;
        upperRangeCeiling = ceiling;
        unsigned int itemInLowerRange = 0;
        for (unsigned int item : numbers)
        {
            //principle of pigeonhole.
            if (item >= lowerRangeFloor && item <= lowerRangeCeiling)
                itemInLowerRange++;
           
        }
        unsigned int distinctPossibleIntegersInLowerRange = lowerRangeCeiling - lowerRangeFloor+1;
        if (itemInLowerRange > distinctPossibleIntegersInLowerRange)
        {
            floor = lowerRangeFloor;
            ceiling = lowerRangeCeiling;
        }
        else
        {
            floor = upperRangeFloor;
            ceiling = upperRangeCeiling;
        }
    }
    return floor;
}
int main()
{
    cout << findRepeat({ 8,8,8,8,8,8,8,8,8 });
}
