/*
Find a duplicate, Space Edition™.
We have a vector of integers, where:

The integers are in the range 

1..n
The vector has a length of 
n+1

It follows that our vector has at least one integer which appears at least twice. But it may have several duplicates, and each duplicate may appear more than twice.

Write a function which finds an integer that appears more than once in our vector. Don't modify the input! (If there are multiple duplicates, you only need to find one of them.)

We're going to run this function on our new, super-hip MacBook Pro With Retina Display™. Thing is, the damn thing came with the RAM soldered right to the motherboard, so we can't upgrade our RAM. So we need to optimize for space!
**/

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
