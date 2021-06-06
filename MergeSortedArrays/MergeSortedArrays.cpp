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

