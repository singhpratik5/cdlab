#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

struct Production {
    char lhs;
    vector<string> rhs;
};

map<char, set<char>> FIRST, FOLLOW;
vector<Production> productions;

bool isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

void calculateFIRST(char symbol) {
    if (FIRST.count(symbol)) return;

    set<char> firstSet;
    for (const auto& prod : productions) {
        if (prod.lhs == symbol) {
            for (const auto& rule : prod.rhs) {
                for (size_t i = 0; i < rule.size(); i++) {
                    char ch = rule[i];
                    if (!isNonTerminal(ch)) {
                        firstSet.insert(ch);
                        break;
                    } else {
                        calculateFIRST(ch);
                        bool hasEpsilon = false;
                        for (char f : FIRST[ch]) {
                            if (f == '#') hasEpsilon = true;
                            else firstSet.insert(f);
                        }
                        if (!hasEpsilon) break;
                    }
                }
            }
        }
    }
    FIRST[symbol] = firstSet;
}

void calculateFOLLOW(char symbol) {
    if (FOLLOW.count(symbol)) return; 

    if (symbol == productions[0].lhs) FOLLOW[symbol].insert('$');

    for (const auto& prod : productions) {
        for (const auto& rule : prod.rhs) {
            for (size_t i = 0; i < rule.size(); i++) {
                if (rule[i] == symbol) {
                    bool hasEpsilon = true;
                    for (size_t j = i + 1; j < rule.size() && hasEpsilon; j++) {
                        hasEpsilon = false;
                        char next = rule[j];
                        if (!isNonTerminal(next)) {
                            FOLLOW[symbol].insert(next);
                            break;
                        } else {
                            for (char f : FIRST[next]) {
                                if (f == '#') hasEpsilon = true;
                                else FOLLOW[symbol].insert(f);
                            }
                        }
                    }
                    if (hasEpsilon || i + 1 == rule.size()) {
                        if (symbol != prod.lhs) {
                            calculateFOLLOW(prod.lhs);
                            FOLLOW[symbol].insert(FOLLOW[prod.lhs].begin(), FOLLOW[prod.lhs].end());
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        Production p;
        cout << "Enter left-hand side of production " << i + 1 << ": ";
        cin >> p.lhs;
        int rhsCount;
        cout << "Enter number of right-hand side options for " << p.lhs << ": ";
        cin >> rhsCount;
        for (int j = 0; j < rhsCount; j++) {
            string rhs;
            cout << "Enter production " << j + 1 << " for " << p.lhs << ": ";
            cin >> rhs;
            p.rhs.push_back(rhs);
        }
        productions.push_back(p);
    }

    for (const auto& prod : productions) {
        calculateFIRST(prod.lhs);
    }

    for (const auto& prod : productions) {
        calculateFOLLOW(prod.lhs);
    }

    cout << "\nFIRST sets:\n";
    for (const auto& f : FIRST) {
        cout << "FIRST(" << f.first << ") = { ";
        for (char c : f.second) cout << c << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (const auto& f : FOLLOW) {
        cout << "FOLLOW(" << f.first << ") = { ";
        for (char c : f.second) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}