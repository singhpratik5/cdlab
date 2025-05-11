#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void removeComments(const string &inputFile, const string &outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile) {
        cerr << "Error opening input file: " << inputFile << endl;
        return;
    }

    if (!outFile) {
        cerr << "Error opening output file: " << outputFile << endl;
        return;
    }

    bool inSingleLineComment = false;
    bool inMultiLineComment = false;
    bool inStringLiteral = false;
    bool inCharLiteral = false;

    string line;
    while (getline(inFile, line)) {
        string newLine = "";
        size_t i = 0;

        while (i < line.length()) {
            if (!inSingleLineComment && !inMultiLineComment && !inCharLiteral && line[i] == '"') {
                inStringLiteral = !inStringLiteral;
            }

            if (!inSingleLineComment && !inMultiLineComment && !inStringLiteral && line[i] == '\'') {
                inCharLiteral = !inCharLiteral;
            }
            if (!inStringLiteral && !inCharLiteral && !inMultiLineComment && i + 1 < line.length() && line[i] == '/' && line[i + 1] == '/') {
                inSingleLineComment = true;
                break;
            }
            else if (!inStringLiteral && !inCharLiteral && !inSingleLineComment && !inMultiLineComment && i + 1 < line.length() && line[i] == '/' && line[i + 1] == '*') {
                inMultiLineComment = true;
                i++; 
            }
            else if (inMultiLineComment && i + 1 < line.length() && line[i] == '*' && line[i + 1] == '/') {
                inMultiLineComment = false;
                i++;  
            }
            else if (inSingleLineComment || inMultiLineComment) {
                i++;
            }
            else {
                newLine += line[i];  
                i++;
            }
        }

        if (!newLine.empty()) {
            outFile << newLine << endl;
        }
    }

    inFile.close();
    outFile.close();
}

int main() {
    string inputFile = "input.c";  
    string outputFile = "output.c";  

    removeComments(inputFile, outputFile);

    cout << "Comments removed successfully. Check the output in 'output.c'." << endl;

    return 0;
}
