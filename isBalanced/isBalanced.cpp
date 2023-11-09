/**
Write a function to see if a binary tree ↴ is "superbalanced"
 (a new tree property we just made up).
A tree is "superbalanced" if the difference 
between the depths of any two leaf nodes ↴ is no greater than one.
*/

#include <iostream>
#include <memory>
#include<stack>
#include<queue>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

class BinaryTreeNode
{
public:
    int value_;
    BinaryTreeNode* left_;
    BinaryTreeNode* right_;

    BinaryTreeNode(int value) :
        value_(value),
        left_(nullptr),
        right_(nullptr)
    {
    }

    ~BinaryTreeNode()
    {
        delete left_;
        delete right_;
    }

    BinaryTreeNode* insertLeft(int value)
    {
        this->left_ = new BinaryTreeNode(value);
        return this->left_;
    }

    BinaryTreeNode* insertRight(int value)
    {
        this->right_ = new BinaryTreeNode(value);
        return this->right_;
    }
};
bool isBalanced(const BinaryTreeNode* treeRoot)
{
    
    stack<pair<const BinaryTreeNode*,int>> nodes;
    nodes.push(make_pair(treeRoot, 1));
    
   
    int maxDepth = 0;
    int currentLeaveDepth = 0;
    while (!nodes.empty())
    {
        auto node = nodes.top();
        if (!node.first->left_ && !node.first->right_) {
           
           maxDepth = max(maxDepth, node.second);
           currentLeaveDepth = node.second;
           if ((maxDepth - currentLeaveDepth) > 1) return false;
        }
        nodes.pop();

        if (node.first->left_)  nodes.push(make_pair(node.first->left_, node.second + 1));
        if (node.first->right_) nodes.push(make_pair(node.first->right_, node.second + 1));
    }
  
    return true;
}
void traverseTreeInBreadth(const BinaryTreeNode* treeRoot)
{
    int countDepth = 1;
    queue<pair<const BinaryTreeNode*, int>> nodes;
    nodes.push(make_pair(treeRoot, countDepth));

    cout << "InBreadth" << endl;
    while (!nodes.empty())
    {
        auto node = nodes.front();
        if (!node.first->left_ && !node.first->right_)
            cout << node.first->value_ << " " << node.second << "; ";
        nodes.pop();
       
        if (node.first->left_) nodes.push(make_pair(node.first->left_, node.second+1));
        if (node.first->right_) nodes.push(make_pair(node.first->right_, node.second + 1));
    }
}
bool isBalanced1(const BinaryTreeNode* treeRoot)
{
    // a tre(e with no nodes is superbalanced, since there are no leaves!
    if (treeRoot == nullptr) {
        return true;
    }

    // will have up to 3 elements
    size_t depths[3];
    size_t depthCount = 0;

    // nodes will store pairs of a node and the node's depth
    stack<pair<const BinaryTreeNode*, size_t>> nodes;
    nodes.push(make_pair(treeRoot, 0));

    while (!nodes.empty()) {

        // get a node and its depth from the top of stack and pop it
        const BinaryTreeNode* node = nodes.top().first;
        size_t depth = nodes.top().second;
        nodes.pop();

        // case: we found a leaf
        if (!node->left_ && !node->right_) {

            // we only care if it's a new depth
            if (depthCount == 0 ||
                find(depths, depths + depthCount, depth) == depths + depthCount) {
                depths[depthCount] = depth;
                ++depthCount;

                // two ways we might now have an unbalanced tree:
                //   1) more than 2 different leaf depths
                //   2) 2 leaf depths that are more than 1 apart
                if (depthCount > 2 ||
                    (depthCount == 2 &&
                        max(depths[0], depths[1]) - min(depths[0], depths[1]) > 1)) {
                    return false;
                }
            }
        }

        // case: this isn't a leaf - keep stepping down
        else {
            if (node->left_) {
                nodes.push(make_pair(node->left_, depth + 1));
            }
            if (node->right_) {
                nodes.push(make_pair(node->right_, depth + 1));
            }
        }
    }

    return true;
}




// tests

const lest::test tests[] = {
    {CASE("Full Tree") {
        auto root = make_unique<BinaryTreeNode>(5);
        root->insertLeft(8)->insertLeft(1);
        root->insertRight(6)->insertRight(4);
        root->left_->insertRight(2);
        root->right_->insertLeft(3);
        EXPECT(isBalanced(root.get()) == true);
    }},
    {CASE("Both leaves at the same depth") {
        auto root = make_unique<BinaryTreeNode>(3);
        root->insertLeft(4)->insertLeft(1);
        root->insertRight(2)->insertRight(9);
        EXPECT(isBalanced(root.get()) == true);
    }},
    {CASE("Leaf heights differ by one") {
        auto root = make_unique<BinaryTreeNode>(6);
        root->insertLeft(1);
        root->insertRight(0)->insertRight(7);
        EXPECT(isBalanced(root.get()) == true);
    }},
    {CASE("Leaf heights differ by two") {
        auto root = make_unique<BinaryTreeNode>(6);
        root->insertLeft(1);
        root->insertRight(0)->insertRight(7)->insertRight(8);
        EXPECT(isBalanced(root.get()) == false);
    }},
    {CASE("Three leaves total") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(5);
        root->insertRight(9)->insertRight(5);
        root->right_->insertLeft(8);
        EXPECT(isBalanced(root.get()) == true);
    }},
    {CASE("Both subtrees superbalanced") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(5);
        root->insertRight(9)->insertRight(5);
        root->right_->insertLeft(8)->insertLeft(77777);
        EXPECT(isBalanced(root.get()) == false);
    }},
    {CASE("Both subtrees superbalanced two") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(2)->insertLeft(3);
        root->left_->insertRight(7)->insertRight(8);
        root->insertRight(4)->insertRight(5)->insertRight(6)->insertRight(9);
        EXPECT(isBalanced(root.get()) == false);
    }},
    {CASE("Three leaves at different levels") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(2)->insertLeft(3)->insertLeft(5);
        root->left_->insertRight(4);
        root->left_->left_->insertRight(6);
        root->insertRight(7)->insertRight(8)->insertRight(9)->insertRight(10);
        EXPECT(isBalanced(root.get()) == false);
    }},
    {CASE("Only one node") {
        auto root = make_unique<BinaryTreeNode>(1);
        EXPECT(isBalanced(root.get()) == true);
    }},
    {CASE("Linked list tree") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertRight(2)->insertRight(3)->insertRight(4);
        EXPECT(isBalanced(root.get()) == true);
    }},
};

int main(int argc, char** argv)
{
   
    if (int failures = lest::run(tests, argc, argv))
        return failures;
    return std::cout << "All tests passed\n", EXIT_SUCCESS;
  // return lest::run(tests, argc, argv);
}