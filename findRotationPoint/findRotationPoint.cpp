/*
I want to learn some big words so people think I'm smart.
I opened up a dictionary to a page in the middle and started
 flipping through, looking for words I didn't know. I put each
  word I didn't know at increasing indices in a huge vector 
  I created in memory. When I reached the end of the dictionary,
   I started from the beginning and did the same thing until 
   I reached the page I started at.

Now I have a vector of words that are mostly alphabetical, 
except they start somewhere in the middle of the alphabet, 
reach the end, and then start from the beginning of the alphabet.
 In other words, this is an alphabetically ordered vector that has been "rotated."
  For example:

  const vector<string> words {
    "ptolemaic",
    "retrograde",
    "supplant",
    "undulate",
    "xenoepist",
    "asymptote",  // <-- rotates here!
    "babka",
    "banoffee",
    "engender",
    "karpatka",
    "othellolagkage",
};

Write a function for finding the index of the "rotation point," 
which is where I started working from the beginning of the dictionary.
 This vector is huge (there are lots of words I don't know) so we want to be efficient here.

To keep things simple, you can assume all words are lowercase.
*/


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

