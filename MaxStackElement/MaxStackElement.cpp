/*
You want to be able to access the largest element in a stack. ↴
Use the built-in stack class to implement a new class MaxStack with a method getMax() that returns the largest element in the stack. getMax() should not remove the item.

Your stacks will contain only integers.

**/

#include <iostream>
#include <stack>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

// fill in the definitions for push(), pop(), and getMax()


class MaxStack
{
    stack<int> main_stack;
    stack<int>max_values_stack;
    int current_max = std::numeric_limits<int>::min();
public:
    void push(int item)
    {
        if (item >= current_max){
            current_max = item;
            max_values_stack.push(current_max);
        }
        main_stack.push(item);
    }

    int pop()
    {
        if (main_stack.top() == max_values_stack.top())
        {
            max_values_stack.pop();
        }
        int result = main_stack.top();
        main_stack.pop();
        return result;
    }

    int getMax() const
    {
        return max_values_stack.top();
    }
};


















// tests

const lest::test tests[] = {
    {CASE("MaxStack test") {
        MaxStack s;
        s.push(5);
        EXPECT(s.getMax() == 5);
        s.push(4);
        s.push(7);
        s.push(7);
        s.push(8);
        EXPECT(s.getMax() == 8);
        EXPECT(s.pop() == 8);
        EXPECT(s.getMax() == 7);
        EXPECT(s.pop() == 7);
        EXPECT(s.getMax() == 7);
        EXPECT(s.pop() == 7);
        EXPECT(s.getMax() == 5);
        EXPECT(s.pop() == 4);
        EXPECT(s.getMax() == 5);
    }}
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}