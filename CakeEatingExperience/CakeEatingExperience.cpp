/**
My cake shop is so popular, I'm adding some tables and hiring wait staff so folks can have a cute sit-down cake-eating experience.
I have two registers: one for take-out orders, and the other for the other folks eating inside the cafe. All the customer orders get combined into one list for the kitchen, where they should be handled first-come, first-served.

Recently, some customers have been complaining that people who placed orders after them are getting their food first. Yikes—that's not good for business!

To investigate their claims, one afternoon I sat behind the registers with my laptop and recorded:

The take-out orders as they were entered into the system and given to the kitchen. (takeOutOrders)
The dine-in orders as they were entered into the system and given to the kitchen. (dineInOrders)
Each customer order (from either register) as it was finished by the kitchen. (servedOrders)
Given all three vectors, write a function to check that my service is first-come, first-served. All food should come out in the same order customers requested it.

We'll represent each customer order as a unique integer.

As an example,

  Take Out Orders: [1, 3, 5]
 Dine In Orders: [2, 4, 6]
  Served Orders: [1, 2, 4, 6, 5, 3]
would not be first-come, first-served, since order 3 was requested before order 5 but order 5 was served first.

But,

  Take Out Orders: [17, 8, 24]
 Dine In Orders: [12, 19, 2]
  Served Orders: [17, 8, 12, 19, 24, 2]
would be first-come, first-served.

Note: Order numbers are arbitrary. They do not have to be in increasing order.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isFirstComeFirstServed1(const vector<int>& takeOutOrders,
    const vector<int>& dineInOrders,
    const vector<int>& servedOrders)
{
    if (servedOrders.size() != takeOutOrders.size() + dineInOrders.size()) return false;
    vector<vector<int>::const_iterator> check_takeOutOrders;
    vector<vector<int>::const_iterator> check_dineInOrders;
    
    for_each(takeOutOrders.begin(), takeOutOrders.end(),
        [&]( int item) {
            auto pos = find(servedOrders.begin(), servedOrders.end(),
                item);
            if (pos != servedOrders.end()) {
                return false;
            }
            check_takeOutOrders.push_back(pos);
        }
        );
    int i_init=0, i_end = 0;
    i_end = check_takeOutOrders.size() - 1;
    while (i_init<=i_end)
    {
        if (check_takeOutOrders[i_init] > check_takeOutOrders[i_init + 1])return false;

        i_init++;
    }
/*........................................................................................*/
    for_each(dineInOrders.begin(), dineInOrders.end(),
        [&](int item) {
            auto pos = find(servedOrders.begin(), servedOrders.end(),
                item);
            if (pos != servedOrders.end()) {
                return false;
            }
            check_dineInOrders.push_back(pos);
        }
    );
    int i_init1 = 0, i_end1 = 0;
    i_end1 = check_dineInOrders.size() - 1;
    while (i_init1 <= i_end1)
    {
        if (check_dineInOrders[i_init] > check_dineInOrders[i_init + 1])return false;
        i_init1++;
    }

    return true;
}


bool isFirstComeFirstServed(const vector<int>& takeOutOrders,
    const vector<int>& dineInOrders,
    const vector<int>& servedOrders)
{
    if (servedOrders.size() != takeOutOrders.size() + dineInOrders.size()) return false;
    int i_d = 0;
    int i_t = 0;
    for_each(servedOrders.begin(), servedOrders.end(), 
        [&](int item) {
            if (dineInOrders.size()>0 && item == dineInOrders[i_d])
                i_d++;
            if (takeOutOrders.size()>0 && item == takeOutOrders[i_t])
                i_t++;
        });
    return i_t == takeOutOrders.size() && i_d == dineInOrders.size();
}
/*
Bonus
This assumes each customer order in servedOrders is unique.
How can we adapt this to handle vectors of customer orders with potential repeats?
Our implementation returns true when all the items in dineInOrders and takeOutOrders are first-come first-served in servedOrders and false otherwise. That said, it'd be reasonable to throw an exception if some orders that went into the kitchen were never served, or orders were served but not paid for at either register. How could we check for those cases?
Our solution iterates through the customer orders from front to back. Would our algorithm work if we iterated from the back towards the front? Which approach is cleaner?
*/
int main()
{
    cout << isFirstComeFirstServed({}, { 1, 2, 3 }, { 1,2,3 });
}


