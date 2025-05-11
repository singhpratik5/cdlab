#include <stdio.h>
#include <stdbool.h>

void remove_comments(FILE *input, FILE *output) {
    char ch, next;
    bool in_string = false;  // to handle strings so comments inside strings are not removed
    bool in_single_line_comment = false;
    bool in_multi_line_comment = false;

    while ((ch = fgetc(input)) != EOF) {
        // Handle string literals to avoid removing comments within strings
        if (ch == '"' && !in_single_line_comment && !in_multi_line_comment) {
            in_string = !in_string;
            fputc(ch, output);
            continue;
        }

        // Check for the start of a single-line comment (//)
        if (!in_string && !in_multi_line_comment && ch == '/' && (next = fgetc(input)) == '/') {
            in_single_line_comment = true;
        }
        // Check for the start of a multi-line comment (/*)
        else if (!in_string && !in_single_line_comment && ch == '/' && next == '*') {
            in_multi_line_comment = true;
        }
        // Check for the end of a single-line comment
        else if (in_single_line_comment && ch == '\n') {
            in_single_line_comment = false;
            fputc(ch, output);  // keep the newline
        }
        // Check for the end of a multi-line comment (*/)
        else if (in_multi_line_comment && ch == '*' && (next = fgetc(input)) == '/') {
            in_multi_line_comment = false;
        }
        // If currently in a comment, skip the character
        else if (in_single_line_comment || in_multi_line_comment) {
            continue;
        }
        // If not in a comment, write the character to the output
        else {
            fputc(ch, output);
            if (ch == '/' && (next == '/' || next == '*')) {
                ungetc(next, input);  // Put back the character after checking
            }
        }
    }
}

int main() {
    FILE *input = fopen("input.c", "r");
    FILE *output = fopen("output.c", "w");

    if (input == NULL) {
        perror("Error opening input file");
        return 1;
    }
    if (output == NULL) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }

    remove_comments(input, output);

    fclose(input);
    fclose(output);

    printf("Comments removed successfully.\n");
    return 0;
}
