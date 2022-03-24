#include <iostream>
#include <cstring>

using namespace std;

enum class WordType {
    CORRECT, BAD_POSITION, INCORRECT
};

struct WordPart {
    char letter;
    WordType type;
};

struct Intent {
    bool win;
    WordPart parts[5];
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

void toArr(string str, char arr[]) {
    for (int i = 0; i < str.size(); i++) {
        arr[i] = str[i];
    }
}

Intent testWord(string intent, string realWord) {
    WordPart parts[5];

    if (intent == realWord) {
        for (int i = 0; i < intent.length(); i++) {
            char letter = intent[i];

            parts[i] = {letter, WordType::CORRECT};
        }

        return {true, *parts};
    }

    char sortedRealWord[realWord.length()];
    toArr(realWord, sortedRealWord);
    sort(sortedRealWord, sortedRealWord + realWord.size());

    for (int i = 0; i < intent.length(); i++) {
        char letter = intent[i];

        if (realWord[i] == letter) {
            parts[i] = {letter, WordType::CORRECT};
        } else if (binary_search(sortedRealWord, sortedRealWord + realWord.size(), letter)) {
            parts[i] = {letter, WordType::BAD_POSITION};
        } else {
            parts[i] = {letter, WordType::INCORRECT};
        }
    }

    return {false, *parts};
}

