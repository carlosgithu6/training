#include <iostream>
#include <stack>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

// fill in the definitions for enqueue() and dequeue()


class QueueTwoStacks
{
private:
    stack<int> inStack_;
    stack<int> outStack_;

public:
    void enqueue(int item)
    {
        inStack_.push(item);
    }

    void moveStackInverted(stack<int>& origin, stack<int>& destiny)
    {
        //mueve una pila para otra
        if (origin.size() == 0) throw runtime_error("queue is empty");
        for (;!origin.empty();) {
            
            destiny.push(origin.top());
            origin.pop();
        }
        
    }
    int dequeue()
    {
        int result;
        if (outStack_.empty()) moveStackInverted(inStack_, outStack_);
        result=outStack_.top();
        outStack_.pop();
        return result;
    }
};
// tests

const lest::test tests[] = {
    {CASE("basic queue operations") {
        QueueTwoStacks q;
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        EXPECT(q.dequeue() == 1);
        EXPECT(q.dequeue() == 2);
        q.enqueue(4);
        EXPECT(q.dequeue() == 3);
        EXPECT(q.dequeue() == 4);
    }},
    {CASE("exception when dequeue from new queue") {
        QueueTwoStacks q;
        EXPECT_THROWS(q.dequeue());
    }},
    {CASE("exception when dequeue from empty queue") {
        QueueTwoStacks q;
        q.enqueue(1);
        q.enqueue(2);
        q.dequeue();
        q.dequeue();
        EXPECT_THROWS(q.dequeue());
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}