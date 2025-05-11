#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for std::find
using namespace std;

#define max_prod 10

struct production {
    char nT;
    vector<string> rhs;
    vector<char> first;
};

void find_first(production &pro, production prod[], int n) {
    for (string str : pro.rhs) {
        int curr = 0;
        // Check each symbol in the production rule
        while (curr < str.size()) {
            char symbol = str.at(curr);
            if (!isalpha(symbol)) { // If it's a terminal
                //if (find(pro.first.begin(), pro.first.end(), symbol) == pro.first.end()) {
                    pro.first.push_back(symbol); // Add terminal to first set
                //}
                break; // Once a terminal is found, stop processing the rule
            } else { // If it's a non-terminal
                // Find the non-terminal in the production list
                for (int i = 0; i < n; ++i) {
                    if (prod[i].nT == symbol) {
                        find_first(prod[i], prod, n);
                        // Add the first set of the non-terminal to the current non-terminal
                        for (char c : prod[i].first) {
                            if (c != '#' && find(pro.first.begin(), pro.first.end(), c) == pro.first.end()) {
                                pro.first.push_back(c);
                            }
                        }
                        // If epsilon (#) is found, check the next symbol
                        if (find(prod[i].first.begin(), prod[i].first.end(), '#') != prod[i].first.end()) {
                            curr++; // Move to the next symbol
                            if (curr == str.size()) {
                                if (find(pro.first.begin(), pro.first.end(), '#') == pro.first.end()) {
                                    pro.first.push_back('#'); // Add epsilon if all symbols can derive epsilon
                                }
                            }
                        } else {
                            break; // If epsilon is not in the first set of the non-terminal, stop
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the no of productions: ";
    cin >> n;

    if (n > max_prod) {
        cout << "Max prod limit exceeded." << endl;
        return 0;
    }

    production prod[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter the nonterminal: ";
        cin >> prod[i].nT;

        int numProd;
        cout << "Enter the number of productions for non-terminal " << prod[i].nT << ": ";
        cin >> numProd;

        for (int j = 0; j < numProd; j++) {
            string rhsProd;
            cout << prod[i].nT << " -> ";
            cin >> rhsProd;
            prod[i].rhs.push_back(rhsProd); // Push to vector
        }
    }

    // Calculate first set for each production
    for (int i = 0; i < n; i++) {
        find_first(prod[i], prod, n);
    }

    // Display first set
    for (int i = 0; i < n; i++) {
        cout << "First(" << prod[i].nT << "): {";
        for (size_t j = 0; j < prod[i].first.size(); j++) {
            cout << prod[i].first[j];
            if (j < prod[i].first.size() - 1) cout << ", ";
        }
        cout << "}" << endl;
    }

    return 0;
}