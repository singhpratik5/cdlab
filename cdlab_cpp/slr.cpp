#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Production {
    char lhs;
    string rhs;
};

struct Action {
    string actionType;  // "shift", "reduce", "accept", or "error"
    int state;          // state for shift
    int production;     // production number for reduce
};

map<int, map<char, Action>> slrTable;
vector<Production> productions;

void initializeGrammar() {
    productions = {
        {'E', "E+T"},
        {'E', "T"},
        {'T', "T*F"},
        {'T', "F"},
        {'F', "(E)"},
        {'F', "id"}
    };

    slrTable[0]['i'] = {"shift", 5, -1};
    slrTable[0]['('] = {"shift", 4, -1};
    slrTable[1]['+'] = {"shift", 6, -1};
    slrTable[1]['$'] = {"accept", -1, -1};
}

bool parseString(const string &input) {
    stack<int> parseStack;
    parseStack.push(0);

    size_t inputIndex = 0;
    char currentChar = input[inputIndex];

    while (true) {
        int state = parseStack.top();
        Action action = slrTable[state][currentChar];

        if (action.actionType == "shift") {
            parseStack.push(action.state);
            inputIndex++;
            currentChar = input[inputIndex];
        } else if (action.actionType == "reduce") {
            Production prod = productions[action.production];
            int rhsLength = prod.rhs.length();
            for (int i = 0; i < rhsLength; i++) {
                parseStack.pop();
            }

            int topState = parseStack.top();
            parseStack.push(slrTable[topState][prod.lhs].state);
        } else if (action.actionType == "accept") {
            cout << "String accepted!" << endl;
            return true;
        } else {
            cout << "Error: String rejected!" << endl;
            return false;
        }
    }
}

int main() {
    initializeGrammar();

    string input;
    cout << "Enter the string to parse (end with '$'): ";
    cin >> input;

    if (parseString(input)) {
        cout << "Parsing completed successfully." << endl;
    } else {
        cout << "Parsing failed." << endl;
    }

    return 0;
}
