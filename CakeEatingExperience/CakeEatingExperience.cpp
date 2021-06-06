
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


