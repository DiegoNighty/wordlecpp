#include <iostream>
#include <cstring>

using namespace std;

enum class WordType {
    CORRECT, BAD_POSITION, INCORRECT
};

struct WordPart {
    char letter;
    WordType type;

    bool won = false;
};

WordPart* testWord(WordPart* parts, string intent, string realWord);
void printIntent(WordPart* intents);

int main() {
    int intents = 0;
    bool win;
    string current;

    cout << "Introduce la palabra (de 5 letras): " << endl;

    while (intents < 5) {
        intents++;

        cin >> current;

        WordPart parts[5];
        WordPart *currentIntent = testWord(parts, current, "exito");

        win = currentIntent[0].won;

        printIntent(parts);

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

void printIntent(WordPart* parts) {
    for (int i = 0; i < 5; ++i) {
        WordPart part = parts[i];

        if (part.type == WordType::CORRECT) {
            system("Color 0A");
        } else if (part.type == WordType::BAD_POSITION) {
            system("Color E4");
        } else {
            system("Color 7E");
        }

        cout << part.letter;
    }

    cout << endl;
}

WordPart* testWord(WordPart* parts, string intent, string realWord) {
    char intentArray[intent.length()];
    strcpy(intentArray, intent.c_str());

    if (intent == realWord) {
        for (int i = 0; i < sizeof intentArray; i++) {
            char letter = intentArray[i];

            parts[i] = {letter, WordType::CORRECT};
        }

        parts[0].won = true;
        return parts;
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

    return parts;
}

