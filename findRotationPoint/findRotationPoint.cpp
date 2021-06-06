#include <iostream>
#include <vector>
using namespace std;
size_t findRotationPoint(const vector<string>& words)
{
    size_t ini = 0;
    size_t max = words.size() - 1;
    size_t middle;
    if (words[ini] < words[max])return 0;//("Not Rotation Point");

    while (ini < max)
    {
       
        middle = (max + ini) / 2;
        if (words[ini] <= words[middle]) 
        {
            ini = middle + 1;
        }
        else
        {
            max = middle;
        }
        if (words[middle] > words[middle + 1])
            return middle + 1;
                   
    }

    return -1;
}
size_t findRotationPoint2(const vector<string>& words)
{
    size_t floorIndex = 0;
    size_t ceilingIndex = words.size() - 1;
    
    while (floorIndex < ceilingIndex) {
    
        // guess a point halfway between floor and ceiling
        size_t guessIndex = floorIndex + ((ceilingIndex - floorIndex) / 2);

        // if guess comes after first word or is the first word
        if (words[guessIndex] >= words[0]) {
            // go right
            floorIndex = guessIndex;
        }
        else {
            // go left
            ceilingIndex = guessIndex;
        }

        // if floor and ceiling have converged
        if (floorIndex + 1 == ceilingIndex) {

            // between floor and ceiling is where we flipped to the beginning
            // so ceiling is alphabetically first
            break;
        }
    }

   return ceilingIndex;
 
}

int main()
{
    
   cout<< findRotationPoint({ "ptolemaic", "retrograde", "supplant", "undulate",
            "xenoepist", "asymptote", "babka", "banoffee", "engender", "karpatka",
            "othellolagkage","owssa" })<<endl;
   cout << findRotationPoint2({ "ptolemaic", "retrograde", "supplant", "undulate",
            "xenoepist", "asymptote", "babka", "banoffee", "engender", "karpatka",
            "othellolagkage","owssa" });
}

