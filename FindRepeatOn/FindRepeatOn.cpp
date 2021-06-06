#include <iostream>
#include <vector>
#include <thread>

// C++11 lest unit testing framework
#include "lest.hpp"

using namespace std;

unsigned int findDuplicate(const vector<unsigned int>& intVector)
{
    int runFaster;
    int runSlower;
    int posSlow;
    int posFaster;
    posSlow = intVector.size() - 1;
    runSlower = intVector[posSlow]; 
    posFaster = intVector[intVector[intVector.size() - 1] - 1] - 1;
    runFaster = intVector[posFaster];

    /*Este ciclo busca en O(n) y S(1) un elemento dentro del ciclo*/
    while (runSlower != runFaster)
    {
        posSlow = runSlower - 1;
        runSlower = intVector[posSlow];
        posFaster = intVector[runFaster - 1] - 1;
        runFaster = intVector[posFaster];   
    }
    int valueIntoCicle = intVector[posFaster];
    /* valueIntoCicle contine el valor buscado*/




    /*Este ciclo calcula la cantidad de elementos dentro del ciclo
    partiendo desde el siguiente hasta que encuentra su antecesor*/
    int lengthCicle = 1; //se inicia en 1 para contar el valor encontrado dentro del ciclo.
    int currentValue = intVector[valueIntoCicle-1];
    while (currentValue != valueIntoCicle)
    {
        lengthCicle++;
        currentValue = intVector[currentValue-1];
    }
    /*************************************************/
    int indexAhead,indexTail=0;
    indexAhead = intVector.size();
    int countDistance = 0;
    while (indexAhead != indexTail)
    {
        indexAhead = intVector[indexAhead-1];
        countDistance++;
        if (countDistance == lengthCicle+1) indexTail = intVector.size(); //aparece el puntero de atras
        if (indexTail !=0)
            indexTail= intVector[indexTail-1];
    }

    return indexTail;
}


















// tests

const lest::test tests[] = {
    {CASE("just the repeated number") {
        const vector<unsigned int> numbers {1, 1};
        const unsigned int expected = 1;
        const unsigned int actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    }},
    {CASE("short vector") {
        const vector<unsigned int> numbers {1, 2, 3, 2};
        const unsigned int expected = 2;
        const unsigned int actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    }},
    {CASE("medium vector") {
        const vector<unsigned int> numbers {1, 2, 5, 5, 5, 5};
        const unsigned int expected = 5;
        const unsigned int actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    }},
    {CASE("long vector") {
        const vector<unsigned int> numbers {4, 1, 4, 8, 3, 2, 7, 6, 5};
        const unsigned int expected = 4;
        const unsigned int actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    }}
};

int main(int argc, char** argv)
{
     if (int failures = lest::run(tests, argc, argv))
       return failures;
    
   return std::cout << "All tests passed\n", EXIT_SUCCESS;
}