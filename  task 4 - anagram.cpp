#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
string word1, word2;
    cout<< "enter first word: ";
    cin>> word1;
    cout<< "enter second word: ";
    cin>> word2;

    // checking if word lengths are the same
    if (word1.length() != word2.length()) {
        cout<< "not anagrams" <<endl;
        return 0;
    }

     // sort both words
    sort(word1.begin(), word1.end());
    sort(word2.begin(), word2.end());

    // compare sorted word
    if (word1 == word2) {
        cout<<"anagrams"<< endl;
    } else {
        cout<<"not anagrams” <<endl;
    }

    return 0;
}