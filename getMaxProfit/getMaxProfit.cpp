/*
Writing programming interview questions hasn't made me rich yet ... so I might give up and start trading Apple stocks all day instead.
First, I wanna know how much money I could have made yesterday if I'd been trading Apple stocks all day.

So I grabbed Apple's stock prices from yesterday and put them in a vector called stockPrices, where:

The indices are the time (in minutes) past trade opening time, which was 9:30am local time.
The values are the price (in US dollars) of one share of Apple stock at that time.
So if the stock cost $500 at 10:30am, that means stockPrices[60] = 500.

Write an efficient function that takes stockPrices and returns the best profit I could have made from one purchase and one sale of one share of Apple stock yesterday.

For example:

  vector<int> stockPrices{10, 7, 5, 8, 11, 9};

getMaxProfit(stockPrices);
// returns 6 (buying for $5 and selling for $11)

In our C++ code, we assume we're using namespace std. Interviewers will commonly expect this when you're writing on a whiteboard because it simplifies your code. But it's not good practice in production—it floods the global namespace with things we don't need.

No "shorting"—you need to buy before you can sell. Also, you can't buy and sell in the same time step—at least 1 minute has to pass.
*/

#include <iostream>
#include <vector>
#include <exception>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;
//O(n^2)
int getMaxProfit1(const vector<int>& stockPrices)
{
    if (stockPrices.size() == 0 || stockPrices.size() == 1) throw runtime_error("");
    int maxi = numeric_limits<int>::min();
    for (size_t i = 0;i < stockPrices.size();i++)
    {
        for (size_t j = i + 1;j < stockPrices.size();j++)
        {
            int possiblemax = stockPrices[j] - stockPrices[i];
            maxi = max(maxi, possiblemax);
        }
    }

    return maxi;
}
//O(n)
int getMaxProfit(const vector<int>& stockPrices)
{
    if (stockPrices.size() == 0 || stockPrices.size() == 1) throw runtime_error("");
    int maxiprofit = numeric_limits<int>::min();
    int mini = numeric_limits<int>::max();
    int profit = 0;
    
    for (size_t i = 0;i < stockPrices.size();i++)
    {
        mini = min(mini, stockPrices[i]);
        if ((i + 1) < stockPrices.size()) {
            profit = stockPrices[i + 1] - mini;
            maxiprofit = max(maxiprofit, profit);
        }
    }

    return maxiprofit;
}
// tests

const lest::test tests[] = {
    {CASE("price goes up then down") {
        const int actual = getMaxProfit({1, 5, 3, 2});
        const int expected = 4;
        EXPECT(actual == expected);
    }},

    {CASE("price goes down then up") {
        const int actual = getMaxProfit({7, 2, 8, 9});
        const int expected = 7;
        EXPECT(actual == expected);
    }},

    {CASE("price goes up all day") {
        const int actual = getMaxProfit({1, 6, 7, 9});
        const int expected = 8;
        EXPECT(actual == expected);
    }},

    {CASE("price goes down all day") {
        const int actual = getMaxProfit({9, 7, 4, 1});
        const int expected = -2;
        EXPECT(actual == expected);
    }},

    {CASE("price stays the same all day") {
        const int actual = getMaxProfit({1, 1, 1, 1});
        const int expected = 0;
        EXPECT(actual == expected);
    }},

    {CASE("exception with empty prices") {
        EXPECT_THROWS(getMaxProfit({}));
    }},

    {CASE("exception with one price") {
        EXPECT_THROWS(getMaxProfit({1}));
    }},
};

int main(int argc, char** argv)
{
   return lest::run(tests, argc, argv);
   
}