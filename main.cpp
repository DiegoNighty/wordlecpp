#include <iostream>

using namespace std;

enum class WordType {
    CORRECT, BAD_POSITION, INCORRECT
};

struct WordPart {
    char letter; WordType type;
};

struct Intent {
    bool win; WordPart parts[5];
};

Intent testWord(string intent, string realWord);

void printIntent(Intent intent);

int main() {
    int intents = 0;
    bool win;
    string current;

    cout << "Introduce la palabra (de 5 letras): " << endl;

    while (intents < 5) {
        intents++;

        cin >> current;
        Intent currentIntent = testWord(current, "hola");
        win = currentIntent.win;

        printIntent(currentIntent);

        if (win) {
            break;
        }
    }

    if (win) {
        cout << "Has ganado con " << intents << " intentos!";
    } else {
        cout << "Perdiste :v";
    }

    return 0;
}

void printIntent(Intent intent) {
    for (WordPart item : intent.parts) {
        if (item.type == WordType::CORRECT) {
            system("Color 0A");
        } else if (item.type == WordType::BAD_POSITION) {
            system("Color E4");
        } else {
            system("Color 7E");
        }

        cout << item.letter;
    }

    cout << endl;
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

