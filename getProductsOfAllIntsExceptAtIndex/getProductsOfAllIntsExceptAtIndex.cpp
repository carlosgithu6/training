/*
You have a vector of integers, and for each index you want to find the product of every integer except the integer at that index.
Write a function getProductsOfAllIntsExceptAtIndex() that takes a vector of integers and returns a vector of the products.

For example, given:

  [1, 7, 3, 4]

your function would return:

  [84, 12, 28, 21]
 
by calculating:

  [7 * 3 * 4,  1 * 3 * 4,  1 * 7 * 4,  1 * 7 * 3]
 
Here's the catch: You can't use division in your solution!


*/



// getProductsOfAllIntsExceptAtIndex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
vector<int> getProductsOfAllIntsExceptAtIndexV0(const vector<int>& intVector)
{
    if (intVector.size() < 2)throw invalid_argument("");
    vector<int> result(intVector.size());
    vector<int> productsBefore_i(intVector.size());
    vector<int> productsAfter_k(intVector.size());
    productsBefore_i[0] = 1;
    productsAfter_k[intVector.size() - 1] = 1;
    int productBefore_i = intVector[0];
    int productAfter_k = intVector[intVector.size()-1];
    for (int i = 1, k = intVector.size()-2;i<intVector.size() ; i++,k--)
    {
        productsBefore_i[i] = productBefore_i;
        productBefore_i = productBefore_i * intVector[i];
        productsAfter_k[k] = productAfter_k;
        productAfter_k = productAfter_k * intVector[k];
    }
    for (int i = 0;i < intVector.size();i++)
    {
        result[i] = productsBefore_i[i] * productsAfter_k[i];
    }
    return result;
}
vector<int> getProductsOfAllIntsExceptAtIndexV1(const vector<int>& intVector)
{
    if (intVector.size() < 2)throw invalid_argument("");
    vector<int> result(intVector.size());
    vector<int> productsBefore_i(intVector.size());
    productsBefore_i[0] = 1;
    
    int productBefore_i = intVector[0];
    int productAfter_k = 1;
    for (size_t i = 1;i < intVector.size(); i++)
    {
        productsBefore_i[i] = productBefore_i;
        productBefore_i = productBefore_i * intVector[i];        
    }

    for (int i = intVector.size()-1;i>=0 ;i--)
    {
        result[i] = productsBefore_i[i] * productAfter_k;
        productAfter_k = productAfter_k * intVector[i];
    }
    return result;
}
vector<int> getProductsOfAllIntsExceptAtIndex(const vector<int>& intVector)
{
    if (intVector.size() < 2)throw invalid_argument("");
    vector<int> result(intVector.size());
    result[0] = 1;

    int productBefore_i = intVector[0];
    int productAfter_k = 1;
    for (size_t i = 1;i < intVector.size(); i++)
    {
        result[i] = productBefore_i;
        productBefore_i = productBefore_i * intVector[i];
    }

    for (size_t i = intVector.size();i > 0;--i)
    {
        size_t j = i - 1; //tecnica para evitar warning
        result[j] = result[j] * productAfter_k;
        productAfter_k = productAfter_k * intVector[j];
    }
    return result;
}
int main()
{
    getProductsOfAllIntsExceptAtIndex({ 1,7,3,4});
    //[84, 12, 28, 21]
}

