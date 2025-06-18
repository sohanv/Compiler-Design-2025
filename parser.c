// for the grammar:
// E -> E + E
// E -> E * E
// E -> ( E )
// E -> id

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[100], input[100];
int top = -1, ip = 0;

void print_table(const char *action) {
    printf("$%-15s%-15s$\t%s\n", stack, input + ip, action);
}

int reduce() {
    // Try E->id
    if (top >= 1 && stack[top] == 'd' && stack[top-1] == 'i') {
        stack[top-1] = 'E';
        top--;
        print_table("REDUCE TO E");
        return 1;
    }
    // Try E->E+E
    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E') {
        stack[top-2] = 'E';
        top -= 2;
        print_table("REDUCE TO E");
        return 1;
    }
    // Try E->E*E
    if (top >= 2 && stack[top] == 'E' && stack[top-1] == '*' && stack[top-2] == 'E') {
        stack[top-2] = 'E';
        top -= 2;
        print_table("REDUCE TO E");
        return 1;
    }
    // Try E->(E)
    if (top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        stack[top-2] = 'E';
        top -= 2;
        print_table("REDUCE TO E");
        return 1;
    }
    return 0;
}

int main() {
    printf("GRAMMAR:\nE->E+E\nE->E*E\nE->(E)\nE->id\n");
    printf("Enter input string (end with $): ");
    scanf("%s", input);

    printf("\nStack           Input           Action\n");

    while (1) {
        // Shift
        stack[++top] = input[ip++];
        stack[top+1] = '\0';
        print_table("SHIFT");

        // Try to reduce as much as possible after each shift
        while (reduce());

        // Accept condition: stack has only 'E' and input is at end
        if (stack[0] == 'E' && stack[1] == '\0' && input[ip] == '$') {
            print_table("ACCEPT");
            break;
        }

        // If input is finished but stack can't be reduced to E, reject
        if (input[ip] == '$' && !(stack[0] == 'E' && stack[1] == '\0')) {
            print_table("REJECT");
            break;
        }
    }
    return 0;
}
