/*
You're working on a secret team solving coded transmissions.
Your team is scrambling to decipher a recent message, worried it's a plot to break into a major European National Cake Vault. The message has been mostly deciphered, but all the words are backward! Your colleagues have handed off the last step to you.

Write a function reverseWords() that takes a message as a string and reverses the order of the words in place. ↴
*/

#include <iostream>
#include <string>
#include <stack>
#include <utility>



using namespace std;

void reverseWordsV1(string& message)//mio usando una pila
{

    string b = "";

    stack<string> ss;
    for (size_t i = 0; i < message.length(); i++)
    {
        if (message[i] != ' ')
            b += message[i];
        else
        {
            ss.push(b);
            ss.push(" ");
            b = "";
        }
    }
    ss.push(b);
    message = "";

    while (!ss.empty()) {
        message += ss.top();
        ss.pop();
    }
}
void reverseCharacters(string& message, int left, int right)
{

    while (left < right)
    {
        swap(message[left], message[right]);
        left++;
        right--;
    }
}
void reverseWordsV2(string& message)//mio
{
    reverseCharacters(message, 0, message.size() - 1);
    int li = 0;
    int lf = 0;
    int i_end = message.size();
    while (lf <= i_end)
    {
        if (message[lf] == ' ' || lf == i_end)
        {
            reverseCharacters(message, li, lf-1);
            li = lf + 1;
        }
        lf++;
    }
}
void reverseWordsV3(string& message)//curso
{

    if (message.empty()) {
        return;
    }
    reverseCharacters(message, 0, message.length() - 1);
    size_t currentWordStartIndex = 0;
    for (size_t i = 0; i <= message.length(); ++i) {
        if (i == message.length() || message[i] == ' ') {
            reverseCharacters(message, currentWordStartIndex, i - 1);
            currentWordStartIndex = i + 1;
        }
    }
}

/*
Bonus
How would you handle punctuation?
*/
int main(int argc, char** argv)
{
    string a = "CARLOS ANTONIO BESIL RODRIGUEZ NECUZE GONZALEZ";
    reverseWordsV2(a);
  
    cout << a;
    int aa;
    cin >>aa;
}