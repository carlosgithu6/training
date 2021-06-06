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