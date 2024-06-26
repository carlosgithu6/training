/**
You want to build a word cloud, an infographic where the size of a word corresponds to how often it appears in the body of text.
To do this, you'll need data. Write code that takes a long string and builds its word cloud data in an unordered map ↴ , where the keys are words and the values are the number of times the words occurred.

Think about capitalized words. For example, look at these sentences:

  "After beating the eggs, Dana read the next step:"
"Add milk and eggs, then add flour and sugar."
What do we want to do with "After", "Dana", and "add"? In this example, your final unordered map should include one "Add" or "add" with a value of
2
2. Make reasonable (not necessarily perfect) decisions about cases like "After" and "Dana".

Assume the input will only contain words and standard punctuation.

You could make a reasonable argument to use regex in your solution. We won't, mainly because performance is difficult to measure and can get pretty bad.
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class WordCloudData
{
private:
    unordered_map<string, size_t> wordsToCounts_;
   
    void populateWordsToCounts1(const string& inputString)
    {
        vector<int> a;
      
        int _wordlength = 0;
        int _indexwordIni = 0;
        
        for (size_t i = 0;i <= inputString.size();i++)
        {
            if (i<= inputString.size() && isalpha(inputString[i]))
            {
                _wordlength++;
            }
            else
            {
                string _iword = inputString.substr(_indexwordIni, _wordlength);

                if (wordsToCounts_.find(_iword) != wordsToCounts_.end())
                {
                    wordsToCounts_[_iword]++;
                }
                else if(_wordlength>0)
                {
                    wordsToCounts_.insert({ move(_iword) ,1 });
                }
                _indexwordIni += _wordlength+1;
                _wordlength = 0;

            }
        }
    }
    void populateWordsToCounts(const string& inputString)
    {
        size_t _initIndex = 0;
        size_t _wordLength = 0;
        for (size_t i = 0; i <=inputString.size();i++)
        {
            const char& _ichar = inputString[i];
            if (isalpha(_ichar))_wordLength++;
            else
            {
                if (_ichar == ' ' || i==inputString.size())
                {
                    string _word = inputString.substr(_initIndex, _wordLength);
                    _initIndex = i + 1;
                    _wordLength = 0;
                    addWordstoMap(_word);
                }
                else {
                    if ((_ichar == '-' || _ichar=='\'') && isalpha(inputString[i - 1]) && isalpha(inputString[i + 1]))
                    {
                        _wordLength++;
                    }
                    else 
                    {
                        string _word = inputString.substr(_initIndex, _wordLength);
                        _initIndex = i + 1;
                        _wordLength = 0;
                        addWordstoMap(_word);
                    }
                    
                }

            }

        }
    }
    void addWordstoMap(string& _word)
    {
        if (_word.size() > 0) {
            if (wordsToCounts_.find(_word) != wordsToCounts_.end())
                wordsToCounts_[_word]++;
            else
            {
                if (_word == toLowerCase(_word)&& wordsToCounts_.find(capitalize(_word)) != wordsToCounts_.end())
                {
                    int tmp = wordsToCounts_[capitalize(_word)];
                    wordsToCounts_.erase(capitalize(_word));
                    wordsToCounts_.insert({ _word,tmp + 1 });
                }
                else 
                {
                    wordsToCounts_.insert({ _word,1 });
                }
                    
            }
        }
    }
    string capitalize(const string& word)
    {
        string result = word;
        result[0] = toupper(result[0]);
        return result;
    }
    string toLowerCase(const string& word)
    {
        string result = word;
        transform(result.begin(), result.end(),result.begin(),tolower);
        return result;
    }
public:
    WordCloudData(const string& inputString)
    {
        populateWordsToCounts(inputString);
    }

    const unordered_map<string, size_t> getWordsToCounts() const
    {
        return wordsToCounts_;
    }
};


int main()
{
   // WordCloudData wcd("Hola Carlos te gusta-programar y te gusta...       jugar a, 87,... programar carlos hola Programar");
   // WordCloudData wcd("Dessert - mille-feuille cake p-aaaaa q---qwedd");
    WordCloudData wcd("Allie's Bakery: Sasha's Cakes... allie's p----q-esq cakes  aaa.bbb ");
    unordered_map<string, size_t> wordsToCounts_= wcd.getWordsToCounts();
    for (const auto& n : wordsToCounts_) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
}

