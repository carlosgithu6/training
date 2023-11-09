/**
Implement a queue ↴ with 2 stacks. ↴ Your queue should have an enqueue and a dequeue method and it should be "first in first out" (FIFO).
Optimize for the time cost of 
m
m calls on your queue. These can be any mix of enqueue and dequeue calls.

Assume you already have a stack implementation and it gives 
O
(
1
)
O(1) time push and pop.
*/
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