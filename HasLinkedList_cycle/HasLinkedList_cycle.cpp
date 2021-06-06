#include <iostream>
#include <vector>
#include <unordered_set>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

class LinkedListNode {
public:
    int intValue_;
    LinkedListNode* next_;

    LinkedListNode(int value) :
        intValue_(value),
        next_(nullptr)
    {
    }
};


//time O(n) space O(n) 
bool containsCycle1(const LinkedListNode* firstNode)
{
    if (firstNode == nullptr)
        return false;

    unordered_set<const LinkedListNode*> visitednodes;

    visitednodes.insert(firstNode);
    const LinkedListNode* ptr = firstNode;
    while (ptr->next_)
    {
        if (visitednodes.find(ptr->next_) != visitednodes.end())
        {
            return true;
        }

        else
            visitednodes.insert(ptr->next_);//O(n)
        ptr = ptr->next_;
    }

    return false;
}


//time O(n) space O(1) 
bool containsCycle(const LinkedListNode* firstNode)
{

    const LinkedListNode* runslow;
    const LinkedListNode* runfaster;
    if (firstNode == nullptr || firstNode->next_==nullptr)  return false;
    runfaster = firstNode->next_;
    runslow = firstNode;
    while (runfaster != nullptr && runfaster->next_)
    {
        runfaster = runfaster->next_->next_;
        runslow = runslow->next_;

        if (runfaster == runslow) return true;
            
    }
    return false;
}
















// tests

vector<LinkedListNode*> valuesToLinkedListNodes(const vector<int>& values);
void freeLinkedListNodes(vector<LinkedListNode*>& nodes);

const lest::test tests[] = {
    {CASE("linked list with no cycle") {
        auto nodes = valuesToLinkedListNodes(vector<int> {1, 2, 3, 4});
        EXPECT(containsCycle(nodes[0]) == false);
        freeLinkedListNodes(nodes);
    }},
    {CASE("cycle loops to beginning") {
        auto nodes = valuesToLinkedListNodes(vector<int> {1, 2, 3, 4});
        nodes[3]->next_ = nodes[0];
        EXPECT(containsCycle(nodes[0]) == true);
        freeLinkedListNodes(nodes);
    }},
    {CASE("cycle loops to middle") {
        auto nodes = valuesToLinkedListNodes(vector<int> {1, 2, 3, 4, 5});
        nodes[4]->next_ = nodes[2];
        EXPECT(containsCycle(nodes[0]) == true);
        freeLinkedListNodes(nodes);
    }},
    {CASE("two node cycle at end") {
        auto nodes = valuesToLinkedListNodes(vector<int> {1, 2, 3, 4, 5});
        nodes[4]->next_ = nodes[3];
        EXPECT(containsCycle(nodes[0]) == true);
        freeLinkedListNodes(nodes);
    }},
    {CASE("empty list") {
        EXPECT(containsCycle(nullptr) == false);
    }},
    {CASE("one element linked list no cycle") {
        auto node = new LinkedListNode(1);
        EXPECT(containsCycle(node) == false);
        delete node;
    }},
    {CASE("one element linked list cycle") {
        auto node = new LinkedListNode(1);
        node->next_ = node;
        EXPECT(containsCycle(node) == true);
        delete node;
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}

vector<LinkedListNode*> valuesToLinkedListNodes(const vector<int>& values)
{
    vector<LinkedListNode*> nodes;
    for (int value : values) {
        auto node = new LinkedListNode(value);
        if (!nodes.empty()) {
            nodes.back()->next_ = node;
        }
        nodes.push_back(node);
    }
    return nodes;
}

void freeLinkedListNodes(vector<LinkedListNode*>& nodes)
{
    for (auto node : nodes) {
        delete node;
    }
    nodes.clear();
}