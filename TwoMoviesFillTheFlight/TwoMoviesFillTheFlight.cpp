/*
You've built an inflight entertainment system with on-demand movie streaming.
Users on longer flights like to start a second movie right when their first one ends, but they complain that the plane usually lands before they can see the ending. So you're building a feature for choosing two movies whose total runtimes will equal the exact flight length.

Write a function that takes an integer flightLength (in minutes) and a vector of integers movieLengths (in minutes) and returns a boolean indicating whether there are two numbers in movieLengths whose sum equals flightLength.

When building your function:

Assume your users will watch exactly two movies
Don't make your users watch the same movie twice
Optimize for runtime over memory
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include<unordered_set>
using namespace std;

bool canTwoMoviesFillFlight1( const vector<int>& movieLengths, int flightLength)
{
   
    vector<int> _ml = movieLengths;
    sort(_ml.begin(), _ml.end(), std::greater<int>());//O(n lg(n))
    for (int k = 0;k < _ml.size();k++)
    {
        if (_ml[k] < flightLength)
        {
            auto pos = find(_ml.begin()++, _ml.end(), (flightLength - _ml[k]));//O(lg(n))
            if (k<_ml.size()-1 && pos != _ml.end()) return true;
        }
    }
   
    return false;
}
bool canTwoMoviesFillFlight2(const vector<int>& movieLengths, int flightLength)
{
    vector<int> _ml = movieLengths;
    sort(_ml.begin(), _ml.end(), std::less<int>());//O(n lg(n))
    for (size_t k = 0;k < _ml.size();k++)
    {
        if (_ml[k] < flightLength )
        {
            int target = (flightLength - _ml[k]);
            if (k!=0 && binary_search(_ml.begin(), _ml.end(),target ))//O(lg(n))
                return true;
        }
    }

    return false;
}
//I could not do that
bool canTwoMoviesFillFlight(const vector<int>& movieLengths, int flightLength)
{
    unordered_set<int>_uset;
  
    int target = 0;
    for (int l :movieLengths)//O(n)
    {
        target = flightLength - l;
        if (_uset.find(target) != _uset.end()) 
            return true;
        else
            _uset.insert(l);
    }
    return false;
}
/*
Bonus
What if we wanted the movie lengths to sum to something close to the flight length (say, within 20 minutes)?
What if we wanted to fill the flight length as nicely as possible with any number of movies (not just 2)?
What if we knew that movieLengths was sorted? Could we save some space and/or time?
*/
int main()
{
    cout << canTwoMoviesFillFlight({3,8}, 6);
}

