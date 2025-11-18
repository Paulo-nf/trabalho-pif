#include "logic_tautology.h"
#include <string.h>
#include <ctype.h>

#define MAX_VARS 10
#define MAX_EXPR 100

typedef struct {
    char name;
    bool value;
} Variable;

static Variable vars[MAX_VARS];
static int var_count = 0;

// Check if character is a variable (CAPITAL letter only)
static bool is_variable(char c) {
    return (c >= 'A' && c <= 'Z');
}

// Check if character is an operator (ASCII only)
static bool is_operator(char c) {
    return c == '~' || c == '!' || c == '^' ||
    c == 'v' || c == '>' || c == '=';
}

// Function to find or create a variable
static int find_var(char name) {
    for (int i = 0; i < var_count; i++) {
        if (vars[i].name == name) {
            return i;
        }
    }
    if (var_count < MAX_VARS) {
        vars[var_count].name = name;
        vars[var_count].value = false;
        return var_count++;
    }
    return -1;
}

// Operator precedence
static int precedence(char op) {
    switch (op) {
        case '~': case '!': return 4;
        case '^': return 3;
        case 'v': return 2;
        case '>': return 1;
        case '=': return 0;
        default: return -1;
    }
}

// Convert infix to postfix without parentheses
static bool infix_to_postfix(const char* infix, char* postfix) {
    char stack[MAX_EXPR];
    int stack_ptr = -1;
    int postfix_idx = 0;
    bool last_was_operand = false;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (c == ' ') continue; // Skip spaces

        if (is_variable(c) || c == '1' || c == '0') {
            // Two operands in a row without operator - invalid
            if (last_was_operand) {
                return false;
            }
            postfix[postfix_idx++] = c;
            last_was_operand = true;
        }
        else if (c == '~' || c == '!') {
            // NOT operator
            stack[++stack_ptr] = c;
        }
        else if (is_operator(c)) {
            // Binary operator
            if (!last_was_operand) {
                return false; // Operator without left operand
            }
            while (stack_ptr >= 0 && precedence(stack[stack_ptr]) >= precedence(c)) {
                postfix[postfix_idx++] = stack[stack_ptr--];
            }
            stack[++stack_ptr] = c;
            last_was_operand = false;
        }
        else {
            return false; // Invalid character
        }
    }

    // Process remaining operators
    while (stack_ptr >= 0) {
        postfix[postfix_idx++] = stack[stack_ptr--];
    }

    postfix[postfix_idx] = '\0';

    // Final validation: must end with an operand
    return last_was_operand;
}

// Evaluate a postfix logical expression
static bool evaluate_postfix(const char* expr) {
    bool stack[MAX_EXPR];
    int stack_ptr = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];

        if (is_variable(c)) {
            int var_idx = find_var(c);
            if (var_idx >= 0) {
                stack[++stack_ptr] = vars[var_idx].value;
            } else {
                return false; // Variable not found
            }
        }
        else if (c == '1') {
            stack[++stack_ptr] = true;
        }
        else if (c == '0') {
            stack[++stack_ptr] = false;
        }
        else if (c == '~' || c == '!') { // NOT operation
            if (stack_ptr < 0) return false;
            stack[stack_ptr] = !stack[stack_ptr];
        }
        else if (c == '^') { // AND operation
            if (stack_ptr < 1) return false;
            bool b = stack[stack_ptr--];
            bool a = stack[stack_ptr--];
            stack[++stack_ptr] = a && b;
        }
        else if (c == 'v') { // OR operation
            if (stack_ptr < 1) return false;
            bool b = stack[stack_ptr--];
            bool a = stack[stack_ptr--];
            stack[++stack_ptr] = a || b;
        }
        else if (c == '>') { // IMPLICATION operation
            if (stack_ptr < 1) return false;
            bool b = stack[stack_ptr--];
            bool a = stack[stack_ptr--];
            stack[++stack_ptr] = !a || b;
        }
        else if (c == '=') { // BICONDITIONAL operation
            if (stack_ptr < 1) return false;
            bool b = stack[stack_ptr--];
            bool a = stack[stack_ptr--];
            stack[++stack_ptr] = a == b;
        }
        else {
            return false; // Invalid operator
        }
    }

    return stack_ptr == 0 ? stack[stack_ptr] : false;
}

// Generate next combination of variable values (binary counting)
static bool next_combination() {
    for (int i = 0; i < var_count; i++) {
        if (!vars[i].value) {
            vars[i].value = true;
            for (int j = 0; j < i; j++) {
                vars[j].value = false;
            }
            return true;
        }
    }
    return false;
}

// Reset all variables to false
static void reset_variables() {
    for (int i = 0; i < var_count; i++) {
        vars[i].value = false;
    }
}

int is_tautology(const char* expr) {
    if (expr == NULL || expr[0] == '\0') {
        return 0; // Invalid: empty expression
    }

    char postfix[MAX_EXPR];
    var_count = 0;

    // Convert to postfix with validation
    if (!infix_to_postfix(expr, postfix)) {
        return 0; // Invalid expression
    }

    // Extract variables from expression
    for (int i = 0; expr[i] != '\0'; i++) {
        if (is_variable(expr[i])) {
            find_var(expr[i]);
        }
    }

    if (var_count == 0) {
        // No variables, just evaluate the constant expression
        reset_variables();
        bool result = evaluate_postfix(postfix);
        return result ? 1 : 0;
    }

    // Test all possible combinations of variable values
    reset_variables();

    do {
        if (!evaluate_postfix(postfix)) {
            return 0; // Found a case where expression is false
        }
    } while (next_combination());

    return 1; // Expression is true for all combinations
}

bool evaluate_expression_with_values(const char* expr,
                                     const char* var_names,
                                     const bool* var_values,
                                     int var_count) {
    if (expr == NULL || var_names == NULL || var_values == NULL || var_count <= 0) {
        return false;
    }

    char postfix[MAX_EXPR];

    // Convert to postfix with validation
    if (!infix_to_postfix(expr, postfix)) {
        return false; // Invalid expression
    }

    // Reset and set variable values
    logic_cleanup();

    for (int i = 0; i < var_count; i++) {
        int idx = find_var(var_names[i]);
        if (idx >= 0) {
            vars[idx].value = var_values[i];
        }
    }

    return evaluate_postfix(postfix);
                                     }

                                     void logic_cleanup(void) {
                                         var_count = 0;
                                     }
