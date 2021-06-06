#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void mergeSortedArrays(vector<int>& v1, const vector<int>& v2)
{
    vector<int> result(v1.size() + v2.size());
    size_t i_v1 = 0;
    size_t i_v2 = 0;
    for (size_t i = 0;i < result.size();i++)
    {
        if ((i_v1 < v1.size()) &&
            (i_v2 >= v2.size() || v1[i_v1] < v2[i_v2]))
        {
            result[i] = (v1[i_v1]);
            i_v1++;
        }
        else
        {
            result[i] = (v2[i_v2]);
            i_v2++;
        }
    }
    v1 = result;
   
}
void MegeVectorOfSoredVectors(vector<vector<int>>& vectorToSort, vector<int>& result)
{
    for (auto& i_vec : vectorToSort)
    {
        mergeSortedArrays(result, i_vec);
    }
}
int main()
{
    
    vector<vector<int>> vectorToSort{
                                  {11,12,13,14,15},
                                  {1,2,3},
                                  {4,5,6,7,8},
                                  {6,7,8,9,10}
                                 
    };

    vector<int> aaa;
    MegeVectorOfSoredVectors(vectorToSort, aaa);

    for_each(aaa.begin(), aaa.end(), [](int item) 
        {
            cout << item << endl;
        });
}

