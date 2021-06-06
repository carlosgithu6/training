#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <queue>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

void bfs(const unordered_map<string, vector<string>>& graph,
    const string& startNode, const string& endNode)
{
    unordered_set<string> nodesVisited;
    queue<string> nodesToVisit;
    nodesVisited.insert(startNode);
    nodesToVisit.push(startNode);

    while (!nodesToVisit.empty())
    {
        string currentNode = move(nodesToVisit.front());
       // cout << currentNode << "  ";
        if (currentNode == endNode)
        {
            break;
        }
        for (string s : graph.find(currentNode)->second)
        {
            if (nodesVisited.count(s) == 0)
            {
                  nodesToVisit.push(s);
                  nodesVisited.insert(s);
            }
        }     
        nodesToVisit.pop();
    }
}

vector<string> reconstructPath(const unordered_map<string, string>& whereNodeWasFound,
    const string& startNode, const string& endNode)
{
    vector<string> shortestPath;

    // start from the end of the path and work backwards
    string currentNode = endNode;

    while (!currentNode.empty()) {
        shortestPath.push_back(currentNode);
        currentNode = whereNodeWasFound.find(currentNode)->second;
    }

     reverse(shortestPath.begin(), shortestPath.end());
     return shortestPath;
}
vector<string> getPath( const unordered_map<string, vector<string>>& graph,
    const string& startNode, const string& endNode)
{
    unordered_set<string> nodesVisited;
    queue<string> nodesToVisit;
    unordered_map<string, string> whereNodeWasFound;
    if (graph.find(startNode) == graph.end() || graph.find(endNode) == graph.end())
        throw invalid_argument("Invalid Argument");
    nodesVisited.insert(startNode);
    nodesToVisit.push(startNode);
    whereNodeWasFound.emplace(startNode, "");
    while (!nodesToVisit.empty())
    {
        string currentNode = move(nodesToVisit.front());
        if (currentNode == endNode)
        {
           return reconstructPath(whereNodeWasFound, startNode, endNode);
        }
        for (string s : graph.find(currentNode)->second)
        {
            if (nodesVisited.count(s) == 0)
            {
                nodesToVisit.push(s);
                nodesVisited.insert(s);
                whereNodeWasFound.emplace(s, currentNode);
            }
        }
        nodesToVisit.pop();
    }
    return vector<string>();
}


















// tests

unordered_map<string, vector<string>> getNetwork()
{
    return unordered_map<string, vector<string>> {
        { "a", { "b", "c", "d" } },
        { "b", {"a", "d"} },
        { "c", {"a", "e"} },
        { "d", {"a", "b"} },
        { "e", {"c"} },
        { "f", {"g"} },
        { "g", {"f"} }
    };
}

const lest::test tests[] = {
    {CASE("two hop path 1") {
        const vector<string> expected {"a", "c", "e"};
        const auto actual = getPath(getNetwork(), "a", "e");
        EXPECT(actual == expected);
    }},
    {CASE("two hop path 2") {
        const vector<string> expected {"d", "a", "c"};
        const auto actual = getPath(getNetwork(), "d", "c");
        EXPECT(actual == expected);
    }},
    {CASE("one hop path 1") {
        const vector<string> expected {"a", "c"};
        const auto actual = getPath(getNetwork(), "a", "c");
        EXPECT(actual == expected);
    }},
    {CASE("one hop path 2") {
        const vector<string> expected {"f", "g"};
        const auto actual = getPath(getNetwork(), "f", "g");
        EXPECT(actual == expected);
    }},
    {CASE("one hop path 3") {
        const vector<string> expected {"g", "f"};
        const auto actual = getPath(getNetwork(), "g", "f");
        EXPECT(actual == expected);
    }},
    {CASE("zero hop path") {
        const vector<string> expected {"a"};
        const auto actual = getPath(getNetwork(), "a", "a");
        EXPECT(actual == expected);
    }},
    {CASE("no path") {
        const vector<string> expected;
        const auto actual = getPath(getNetwork(), "a", "f");
        EXPECT(actual == expected);
    }},
    {CASE("start node not present") {
        EXPECT_THROWS(getPath(getNetwork(), "h", "a"));
    }},
    {CASE("end node not present") {
        EXPECT_THROWS(getPath(getNetwork(), "a", "h"));
    }}
};

int main(int argc, char** argv)
{
   
    if (int failures = lest::run(tests, argc, argv))
        return failures;
    return std::cout << "All tests passed\n", EXIT_SUCCESS;
    
   // return lest::run(tests, argc, argv);
   /* bfs(getNetwork(), "a", "f");
    cout << endl;
    bfs1(getNetwork(), "a", "f");*/
    //return 0;
}
