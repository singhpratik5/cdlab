#include <stdio.h>
#include <string.h>

#define MAX 10
#define MAX_PROD 10
#define MAX_LEN 10

// Structure to hold a non-terminal and its productions
typedef struct {
    char nonTerminal;
    char productions[MAX_PROD][MAX_LEN];
    int prodCount;
} GrammarRule;

// Function to remove direct left recursion
void removeDirectLeftRecursion(GrammarRule *rule) {
    char alpha[MAX_PROD][MAX_LEN], beta[MAX_PROD][MAX_LEN];
    int alphaCount = 0, betaCount = 0;

    // Divide the productions into alpha (recursive) and beta (non-recursive)
    for (int i = 0; i < rule->prodCount; i++) {
        if (rule->productions[i][0] == rule->nonTerminal) {
            strcpy(alpha[alphaCount], rule->productions[i] + 1);  // Exclude the left-recursive part
            alphaCount++;
        } else {
            strcpy(beta[betaCount], rule->productions[i]);
            betaCount++;
        }
    }

    // If no direct recursion exists, print as it is
    if (alphaCount == 0) {
        printf("%c -> ", rule->nonTerminal);
        for (int i = 0; i < rule->prodCount; i++) {
            printf("%s", rule->productions[i]);
            if (i != rule->prodCount - 1)
                printf(" | ");
        }
        printf("\n");
        return;
    }

    // If direct recursion exists, rewrite the grammar
    printf("%c -> ", rule->nonTerminal);
    for (int i = 0; i < betaCount; i++) {
        printf("%s%c'", beta[i], rule->nonTerminal);  // Append new non-terminal for beta
        if (i != betaCount - 1)
            printf(" | ");
    }
    printf("\n");

    printf("%c' -> ", rule->nonTerminal);
    for (int i = 0; i < alphaCount; i++) {
        printf("%s%c' | ", alpha[i], rule->nonTerminal);  // Handle recursion
    }
    printf("ε\n");
}

// Function to remove indirect left recursion
void removeIndirectLeftRecursion(GrammarRule rules[], int nonTermCount) {
    for (int i = 0; i < nonTermCount; i++) {
        for (int j = 0; j < i; j++) {
            // Replace Ai -> Ajγ with Aj's productions
            char newProductions[MAX_PROD][MAX_LEN];
            int newCount = 0;

            for (int k = 0; k < rules[i].prodCount; k++) {
                if (rules[i].productions[k][0] == rules[j].nonTerminal) {
                    // Expand productions of Aj into Ai's place
                    for (int l = 0; l < rules[j].prodCount; l++) {
                        sprintf(newProductions[newCount++], "%s%s", rules[j].productions[l], rules[i].productions[k] + 1);
                    }
                } else {
                    strcpy(newProductions[newCount++], rules[i].productions[k]);
                }
            }

            // Update productions of Ai with the new expanded ones
            rules[i].prodCount = newCount;
            for (int k = 0; k < newCount; k++) {
                strcpy(rules[i].productions[k], newProductions[k]);
            }
        }

        // Now, remove direct left recursion from Ai
        removeDirectLeftRecursion(&rules[i]);
    }
}

int main() {
    GrammarRule rules[MAX];

    // Sample grammar: A -> Aa | b , B -> Bd | A
    rules[0].nonTerminal = 'A';
    strcpy(rules[0].productions[0], "Aa");
    strcpy(rules[0].productions[1], "b");
    rules[0].prodCount = 2;

    rules[1].nonTerminal = 'B';
    strcpy(rules[1].productions[0], "Bd");
    strcpy(rules[1].productions[1], "A");
    rules[1].prodCount = 2;

    int nonTermCount = 2;

    // Removing indirect and direct left recursion
    removeIndirectLeftRecursion(rules, nonTermCount);

    return 0;
}
