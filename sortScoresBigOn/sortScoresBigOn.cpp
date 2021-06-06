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

