/**
In order to win the prize for most cookies sold, my friend Alice and I are going to merge our Girl Scout Cookies orders and enter as one unit.
Each order is represented by an "order id" (an integer).

We have our lists of orders sorted numerically already, in vectors. Write a function to merge our vectors of orders into one sorted vector.

For example:

  const vector<int> myVector {3, 4, 6, 10, 11, 15};
const vector<int> alicesVector {1, 5, 8, 12, 14, 19};

vector<int> mergedVector = mergeVectors(myVector, alicesVector);

cout << "[";
for (size_t i = 0; i < mergedVector.size(); ++i) {
    if (i > 0) {
        cout << ", ";
    }
    cout << mergedVector[i];
}
cout << "]" << endl;
// prints [1, 3, 4, 5, 6, 8, 10, 11, 12, 14, 15, 19]

*/



#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//MIA
vector<int> mergeSortedArrays(const vector<int>& v1, const vector<int>& v2)
{
    vector<int> result(v1.size() + v2.size());
    int i_v1 = 0;
    int i_v2 = 0;
    for (size_t i = 0;i < result.size();i++)
    {
        if ((i_v1 < v1.size()) && 
            (i_v2 >= v2.size()||v1[i_v1] < v2[i_v2]))
        {
            result[i]=(v1[i_v1]);
            i_v1++;
        }
        else
        {
            result[i]=(v2[i_v2]);
            i_v2++;
        }
    }
    return result;
}


//CURSO
vector<int> mergeVectors(const vector<int>& myVector, const vector<int>& alicesVector)
{
    vector<int> mergedVector(myVector.size() + alicesVector.size());

    size_t currentIndexAlices = 0;
    size_t currentIndexMine = 0;
    size_t currentIndexMerged = 0;

    while (currentIndexMerged < mergedVector.size()) {

        // case: my vector is exhausted
        if (currentIndexMine >= myVector.size()) {
            mergedVector[currentIndexMerged] = alicesVector[currentIndexAlices];
            ++currentIndexAlices;
        }

        // case: Alice's vector is exhausted
        else if (currentIndexAlices >= alicesVector.size()) {
            mergedVector[currentIndexMerged] = myVector[currentIndexMine];
            ++currentIndexMine;
        }

        // case: my item is next
        else if (myVector[currentIndexMine] < alicesVector[currentIndexAlices]) {
            mergedVector[currentIndexMerged] = myVector[currentIndexMine];
            ++currentIndexMine;
        }

        // case: Alice's item is next
        else {
            mergedVector[currentIndexMerged] = alicesVector[currentIndexAlices];
            ++currentIndexAlices;
        }

        ++currentIndexMerged;
    }

    return mergedVector;
}

/*
Bonus
What if we wanted to merge several sorted vectors? 
Write a function that takes as an input a vector of sorted vectors and outputs a single sorted vector with all the items from each vector.

Do we absolutely have to allocate a new vector to use for the merged output?
 Where else could we store our merged vector? How would our function need to change?
*/

int main()
{

    vector<int> v1{};
    vector<int> v2{};
    auto vr = mergeSortedArrays(v1, v2);
    for_each(vr.begin(), vr.end(), [](int item) {
        cout << item << endl;});
}

