#include <iostream>
#include <string>
using namespace std;

void swap1(char& a, char& b)
{
    char tmp = a;
    a = b;
    b = tmp;
}
void reverse(string& str)
{

    int f = 0, b = str.size() - 1;
    while (f < b)
    {
        swap1(str[f],str[b]);
        //swap(str[f], str[b]);
        f++;b--;
    }
}
int main()
{
    string aa = "CARLOS BESIL RODRIGUEZ";
    reverse(aa);
    cout << aa;
}