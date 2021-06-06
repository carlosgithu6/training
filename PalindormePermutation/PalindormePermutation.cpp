#include <iostream>
#include<unordered_set>
#include<unordered_map>
#include<chrono>
#include <future>
using namespace std;
using namespace std::chrono;
bool hasPalindromePermutation1(const string& str)
{
    unordered_map<char, int> counter;
    bool is_even = (str.size() % 2 == 0);
    int  count_odds = 0;
    for (char ch : str)
    {
        /*
        * Se cuenta cuantas veces aparece cada letra
        */
        if (counter.find(ch) != counter.end())
            counter[ch]++;
        else
            counter.insert({ ch, 1 });

    }
   
    for (auto& pair : counter)
    {
        /*
        * Si la cantidad de letras es par entonces todas las letras deben
        * aparecer un numero par de veces
        */
        if (is_even && pair.second % 2 != 0) return false;
        
        /*
        * Si la cantidad de letras es impar entonces debe haber solo una letra
        * que aparezca un numero impar de veces.
        */
        if (!is_even && pair.second % 2 !=0 ) {
            count_odds++;
        }
        if (count_odds > 1) return false;
    }
    return true;
}


bool hasPalindromePermutation(const string& str)
{
    unordered_set<char> inout;

    for (char c : str)
    {
        if (inout.find(c) == inout.end()) 
            inout.erase(c);
        else
            inout.insert(c);
    }
    /*
    * Una cadena tiene una permutacion palindrome si tiene  
    * uno o cero caracter sin un par
    */
    return  inout.size() <= 1;
    
}

int main()
{
  
        auto t01 = high_resolution_clock::now();
        hasPalindromePermutation("aabbwerreetgergergergrgrgwregnhfffkffhwekfhekfhewkjfewkwbwkjbffewkjbfrtreecd");
        auto t02 = high_resolution_clock::now();
        cout<<" Curso, nanoseconds "<< duration_cast<nanoseconds>(t02 - t01).count()<<endl;
       
     
  
        auto t03 = high_resolution_clock::now();
         hasPalindromePermutation("aabbwerreetgergergergrgrgwregnhfffkffhwekfhekfhewkjfewkwbwkjbffewkjbfrtreecd");
        auto t04 = high_resolution_clock::now();
        cout.write(" Mio, nanoseconds" + duration_cast<nanoseconds>(t04 - t03).count(), 100);
      


    cin.get();
}

