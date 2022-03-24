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
        Intent currentIntent = testWord(current, "exito");
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
    for (WordPart part : intent.parts) {
        if (part.type == WordType::CORRECT) {
            cout << "&a";
        } else if (part.type == WordType::BAD_POSITION) {
            cout << "&b";
        } else {
            cout << "&c";
        }

        cout << part.letter;
    }

    cout << endl;
}

Intent testWord(string intent, string realWord) {
    WordPart parts[5];

    char intentArray[intent.length()];
    strcpy(intentArray, intent.c_str());

    Intent intentData = {false, *parts};

    if (intent == realWord) {
        for (int i = 0; i < sizeof intentArray; i++) {
            char letter = intentArray[i];

            parts[i] = {letter, WordType::CORRECT};
        }

        intentData.win = true;
        return intentData;
    }

    char sortedRealWord[realWord.length()];
    strcpy(sortedRealWord, realWord.c_str());
    sort(sortedRealWord, sortedRealWord + realWord.size());

    for (int i = 0; i < sizeof intentArray; i++) {
        char letter = intentArray[i];

        if (realWord[i] == letter) {
            parts[i] = {letter, WordType::CORRECT};
        } else if (binary_search(sortedRealWord, sortedRealWord + realWord.size(), letter)) {
            parts[i] = {letter, WordType::BAD_POSITION};
        } else {
            parts[i] = {letter, WordType::INCORRECT};
        }
    }

    return intentData;
}

