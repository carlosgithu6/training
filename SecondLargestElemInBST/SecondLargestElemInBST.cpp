// SecondLargestElemInBST.cpp : 
#include <iostream>
#include <memory>
#include <exception>


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
//return a node and its pather at pair
pair<const BinaryTreeNode*, const BinaryTreeNode*> findLargestNode(const BinaryTreeNode* rootNode, const BinaryTreeNode* pather)
{
    if (!rootNode || (!rootNode->left_ && !rootNode->right_ && !pather))
        throw invalid_argument("");
    const BinaryTreeNode* ptr_tree = rootNode;
   
    if (ptr_tree->right_)//si tiene nodos a la derecha.
    {
        while (ptr_tree->right_)
        {
            pather = ptr_tree;
            ptr_tree = ptr_tree->right_;
        }
        return make_pair(ptr_tree, pather);
    }
    else  //si no tiene derecha pero tiene izquierda
    {
        return make_pair(ptr_tree, pather);
    }
   
    
}


int findSecondLargest(const BinaryTreeNode* rootNode)
{
    auto node_and_pather = findLargestNode(rootNode,nullptr);
    if (!node_and_pather.first->left_ )
        return node_and_pather.second->value_; // es el padre.
    else
    {
       return findLargestNode(node_and_pather.first->left_, node_and_pather.first).first->value_;
    }
   
}



/* solucion de interview cake
int findLargest(const BinaryTreeNode* rootNode)
{
    const BinaryTreeNode* current = rootNode;
    while (current->right_) {
        current = current->right_;
    }
    return current->value_;
}

int findSecondLargest(const BinaryTreeNode* rootNode)
{
    if (!rootNode || (!rootNode->left_ && !rootNode->right_)) {
        throw invalid_argument("Tree must have at least 2 nodes");
    }

    const BinaryTreeNode* current = rootNode;

    while (true) {

        // case: current is largest and has a left subtree
        // 2nd largest is the largest in that subtree
        if (current->left_ && !current->right_) {
            return findLargest(current->left_);
        }

        // case: current is parent of largest, and largest has no children,
        // so current is 2nd largest
        if (current->right_ &&
                !current->right_->left_ &&
                !current->right_->right_) {
            break;
        }

        // step to the right
        current = current->right_;
    }

    return current->value_;
}
*/











// tests

const lest::test tests[] = {
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
    if (int failures = lest::run(tests, argc, argv))
    {
        std::cout << "Failed\n";
        return failures;
    }
     
    return std::cout << "All tests passed\n", EXIT_SUCCESS;
}