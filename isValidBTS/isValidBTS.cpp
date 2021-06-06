#include <iostream>
#include <memory>
#include <queue>
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


int findSecondLargest(const BinaryTreeNode* root)
{
    if (!root) throw invalid_argument("");
    const BinaryTreeNode* ptr_tree = root;
    int val = 0;

    while (ptr_tree)
    {
        if (ptr_tree->right_)
            val = ptr_tree->value_;

        ptr_tree = ptr_tree->right_;


    }
    return val;
}

bool isBinarySearchTree(const BinaryTreeNode* root)
{
    if (root == nullptr || (root->left_ == nullptr && root->right_ == nullptr))
        return true;

    queue<pair<const BinaryTreeNode*, int>> nodes;

    nodes.push(make_pair(root, -1));



    while (!nodes.empty())
    {
        auto node = nodes.front();
        nodes.pop();


        if (node.first->left_ && (node.first->value_ < node.first->left_->value_))
            return false;
        if (node.second == 0 && node.first->value_ > root->value_) return false;

        if (node.first->right_ && (node.first->value_ > node.first->right_->value_))
            return false;
        if (node.second == 1 && node.first->value_ < root->value_) return false;


        if (node.second == -1)
        {
            if (node.first->left_)
            {
                nodes.push(make_pair(node.first->left_, 0)); //subtree left
            }

            if (node.first->right_)
            {
                nodes.push(make_pair(node.first->right_, 1));//subtree right
            }
        }
        else
        {
            if (node.second == 0)
            {
                if (node.first->left_)
                {
                    nodes.push(make_pair(node.first->left_, 0)); //subtree left
                }

                if (node.first->right_)
                {
                    nodes.push(make_pair(node.first->right_, 0));//subtree left
                }
            }
            else
            {
                if (node.first->left_)
                {
                    nodes.push(make_pair(node.first->left_, 1)); //subtree right
                }

                if (node.first->right_)
                {
                    nodes.push(make_pair(node.first->right_, 1));//subtree right
                }
            }
        }

    }
    return true;
}
   



// tests

const lest::test tests[] = {
    {CASE("Valid full tree") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertRight(80);
        root->left_->insertRight(40);
        root->right_->insertLeft(60);
        EXPECT(isBinarySearchTree(root.get()) == true);
    }},
    {CASE("Both subtrees valid") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(20);
        root->insertRight(80)->insertRight(90);
        root->left_->insertRight(60);
        root->right_->insertLeft(70);
        EXPECT(isBinarySearchTree(root.get()) == false);
    }},
    {CASE("Descending linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(40)->insertLeft(30)->insertLeft(20)->insertLeft(10);
        EXPECT(isBinarySearchTree(root.get()) == true);
    }},
    {CASE("Out of order linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertRight(70)->insertRight(60)->insertRight(80);
        EXPECT(isBinarySearchTree(root.get()) == false);
    }},
    {CASE("TestCBESIL") {
        auto root = make_unique<BinaryTreeNode>(10);
        root->insertRight(20);
        root->insertLeft(5)->insertLeft(2);
        root->left_->insertRight(11);
        EXPECT(isBinarySearchTree(root.get()) == false);
    }},
    {CASE("TestTreeExample") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertRight(80)->insertRight(90)->insertRight(100)->insertLeft(95);
        root->right_->right_->insertLeft(85);
        root->right_->insertLeft(70)->insertLeft(60);
        root->insertLeft(30)->insertLeft(20)->insertLeft(10);
        root->left_->insertRight(40);
        EXPECT(isBinarySearchTree(root.get()) == true);
    }},
    {CASE("One node tree") {
        auto root = make_unique<BinaryTreeNode>(50);
        EXPECT(isBinarySearchTree(root.get()) == true);
    }}
};

const lest::test tests2[] = {
    {CASE("Full tree") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertRight(80);
        root->left_->insertRight(40);
        root->right_->insertLeft(60);
        EXPECT(findSecondLargest(root.get()) == 70);
    }},
    {CASE("Largest has a left child") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertLeft(60);
        root->left_->insertRight(40);
        EXPECT(findSecondLargest(root.get()) == 60);
    }},
    {CASE("Largest has a left subtree") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->left_->insertRight(40);
        root->insertRight(70)->insertLeft(60)->insertLeft(55)->insertRight(58);
        root->right_->left_->insertRight(65);
        EXPECT(findSecondLargest(root.get()) == 65);
    }},
    {CASE("Second largest is root node") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70);
        root->left_->insertRight(40);
        EXPECT(findSecondLargest(root.get()) == 50);
    }},
    {CASE("Descending linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(40)->insertLeft(30)->insertLeft(20)->insertLeft(10);
        EXPECT(findSecondLargest(root.get()) == 40);
    }},
    {CASE("Ascending linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertRight(60)->insertRight(70)->insertRight(80);
        EXPECT(findSecondLargest(root.get()) == 70);
    }},
    {CASE("Exception when tree has one node") {
        auto root = make_unique<BinaryTreeNode>(50);
        EXPECT_THROWS(findSecondLargest(root.get()));
    }},
    {CASE("Exception when tree is empty") {
        EXPECT_THROWS(findSecondLargest(nullptr));
    }},
};
int main(int argc, char** argv)
{

   /* if (int failures = lest::run(tests, argc, argv))
        return failures;*/
    if (int failures = lest::run(tests2, argc, argv))
        return failures;
    return std::cout << "All tests passed\n", EXIT_SUCCESS;
}