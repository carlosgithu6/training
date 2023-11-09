/*

You created a game that is more popular than Angry Birds.
Each round, players receive a score between 0 and 100, which you use to rank them from highest to lowest. So far you're using an algorithm that sorts in 

O(nlgn) time, but players are complaining that their rankings aren't updated fast enough. You need a faster sorting algorithm.

Write a function that takes:

a vector of unsortedScores
the highestPossibleScore in the game
and returns a sorted vector of scores in less than 

O(nlgn) time.

For example:

  const vector<int> unsortedScores {37, 89, 41, 65, 91, 53};
const int HIGHEST_POSSIBLE_SCORE = 100;

vector<int> sortedScores = sortScores(unsortedScores, HIGHEST_POSSIBLE_SCORE);
// sortedScores: [91, 89, 65, 53, 41, 37]

We’re defining 
n as the number of unsortedScores because we’re expecting the number of players to keep climbing.

And, we'll treat highestPossibleScore as a constant instead of factoring it into our big O time and space costs because the highest possible score isn’t going to change. Even if we do redesign the game a little, the scores will stay around the same order of magnitude.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include "lest.hpp"
using namespace std;

vector<int> sortScores(const vector<int>& unorderedScores, int highestPossibleScore)
{
    vector<int> result;
    result.reserve(highestPossibleScore + 1);
    vector<int> temp(highestPossibleScore, {0});
    if (unorderedScores.size() == 0)return result;
    for(int i :unorderedScores)
    {
        temp[i]++;
    }
    
    for (int k =highestPossibleScore-1;k>=0;k--)
    {   
        if (temp[k] != 0)
        {
            for (int i = 0;i < temp[k];i++)
            {
                result.push_back(k);
            }
        }
       

    }
    return result;
}
//vector<int> sortScores(const vector<int>& unorderedScores, int highestPossibleScore)
//{
//    vector<int> result;
//    unordered_map<int, size_t> counter;
//    for (int i : unorderedScores)
//    {
//        if (counter.find(i) != counter.end())
//            counter[i]++;
//        else
//            counter.insert({ i,1 });            
//    }
//
//    return result;
//}
// tests

const lest::test tests[] = {
    {CASE("no scores") {
        const vector<int> scores;
        const vector<int> expected;
        const auto actual = sortScores(scores, 100);
        EXPECT(actual == expected);
    }},
    {CASE("one score") {
        const vector<int> scores {55};
        const vector<int> expected {55};
        const auto actual = sortScores(scores, 100);
        EXPECT(actual == expected);
    }},
    {CASE("two scores") {
        const vector<int> scores {30, 60};
        const vector<int> expected {60, 30};
        const auto actual = sortScores(scores, 100);
        EXPECT(actual == expected);
    }},
    {CASE("many scores") {
        const vector<int> scores {37, 89, 41, 65, 91, 53};
        const vector<int> expected {91, 89, 65, 53, 41, 37};
        const auto actual = sortScores(scores, 100);
        EXPECT(actual == expected);
    }},
    {CASE("repeated scores") {
        const vector<int> scores {20, 10, 30, 30, 10, 20};
        const vector<int> expected {30, 30, 20, 20, 10, 10};
        const auto actual = sortScores(scores, 100);
        EXPECT(actual == expected);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}

