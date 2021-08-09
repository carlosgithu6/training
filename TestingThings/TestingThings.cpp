
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include<sstream>
#include<algorithm>
struct Line
{
    std::string data;
};

std::istream& operator>>(std::istream& in, Line& l)
{
    getline(in, l.data);
    return in;
}

std::string getStr(const Line& l)
{
    return l.data;
}

int main() {
    std::string line = "MN00BAJ01521;U;EQ;GLOBAL LIFE TECHNOLOGY;ESVUFR;BAJ / 100.00 MNT;;100;MNT;;;;;;;;;;;;CFI2015.;XULA;;;;;\"Mongolian Central Securities Depository Co.,Ltd\"~;GLOBAL LIFE TECHNOLOGY JSC;;TU.BAJ.C;N;\" 205 Heru industrial, Songino-Khairkhan district, 20th khoroo, Teeverchid street\";;Ulaanbaatar;976;Ulaanbaatar;MN;;;;;;MN;20130122143136;20200407093003";
    try {
        std::string filename = "C:\\Users\\carlo\\Desktop\\Preparing Interview\\bigfile1.txt";
        std::ofstream ostrm(filename);
        std::ifstream istrm(filename);
       for (int i = 1;i <= 7000001;i++)
         {
             ostrm << line << std::endl;
         }
        std::unique_ptr<std::vector<std::string>> coll(new std::vector<std::string>());
        coll->reserve(7000001);
        auto t01 = std::chrono::high_resolution_clock::now();
        std::transform(std::istream_iterator<Line>(istrm), std::istream_iterator<Line>(), std::back_inserter(*coll), getStr);
       // std::transform(std::istreambuf_iterator<Line>(istrm), std::istreambuf_iterator<Line>(), std::back_inserter(*coll), getStr);
        auto t02 = std::chrono::high_resolution_clock::now();
        std::cout << coll->size() << std::endl;
        std::cout << " Demoro seconds " << std::chrono::duration_cast<std::chrono::seconds>(t02 - t01).count() << std::endl;
        
        std::cin >> filename;
    }
    catch (std::exception e)
    {
        std::cout << e.what();
    }
}