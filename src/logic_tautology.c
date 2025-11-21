#include "logic_tautology.h"

#define MAX_VARS 10
#define MAX_EXPR 100

typedef struct {
    char name;
    int value;
} Variable;

static Variable vars[MAX_VARS];
static int var_count = 0;

static int is_variable(char c) {
    return (c >= 'A' && c <= 'Z');
}

static int is_operator(char c) {
    return c == '~' || c == '!' || c == '^' || c == 'v' || c == '>' || c == '=';
}

static int find_var(char name) {
    for (int i = 0; i < var_count; i++) {
        if (vars[i].name == name) return i;
    }
    if (var_count < MAX_VARS) {
        vars[var_count].name = name;
        vars[var_count].value = 0;
        return var_count++;
    }
    return -1;
}

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

static int infix_to_postfix(const char* infix, char* postfix) {
    char stack[MAX_EXPR];
    int stack_ptr = -1;
    int postfix_idx = 0;
    int last_was_operand = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (c == ' ') continue;

        if (is_variable(c) || c == '1' || c == '0') {
            if (last_was_operand) return 0;
            postfix[postfix_idx++] = c;
            last_was_operand = 1;
        }
        else if (c == '~' || c == '!') {
            stack[++stack_ptr] = c;
        }
        else if (is_operator(c)) {
            if (!last_was_operand) return 0;
            while (stack_ptr >= 0 && precedence(stack[stack_ptr]) >= precedence(c)) {
                postfix[postfix_idx++] = stack[stack_ptr--];
            }
            stack[++stack_ptr] = c;
            last_was_operand = 0;
        }
        else {
            return 0;
        }
    }

    while (stack_ptr >= 0) {
        postfix[postfix_idx++] = stack[stack_ptr--];
    }
    postfix[postfix_idx] = '\0';
    return last_was_operand;
}

static int evaluate_postfix(const char* expr) {
    int stack[MAX_EXPR];
    int stack_ptr = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];

        if (is_variable(c)) {
            int var_idx = find_var(c);
            stack[++stack_ptr] = (var_idx >= 0) ? vars[var_idx].value : 0;
        }
        else if (c == '1') stack[++stack_ptr] = 1;
        else if (c == '0') stack[++stack_ptr] = 0;
        else if (c == '~' || c == '!') stack[stack_ptr] = !stack[stack_ptr];
        else if (c == '^') {
            int b = stack[stack_ptr--], a = stack[stack_ptr--];
            stack[++stack_ptr] = a && b;
        }
        else if (c == 'v') {
            int b = stack[stack_ptr--], a = stack[stack_ptr--];
            stack[++stack_ptr] = a || b;
        }
        else if (c == '>') {
            int b = stack[stack_ptr--], a = stack[stack_ptr--];
            stack[++stack_ptr] = !a || b;
        }
        else if (c == '=') {
            int b = stack[stack_ptr--], a = stack[stack_ptr--];
            stack[++stack_ptr] = a == b;
        }
    }
    return (stack_ptr == 0) ? stack[stack_ptr] : 0;
}

static int next_combination() {
    for (int i = 0; i < var_count; i++) {
        if (!vars[i].value) {
            vars[i].value = 1;
            for (int j = 0; j < i; j++) vars[j].value = 0;
            return 1;
        }
    }
    return 0;
}

static void reset_variables() {
    for (int i = 0; i < var_count; i++) vars[i].value = 0;
}

int is_tautology(const char* expr) {
    if (!expr || !expr[0]) return 0;

    char postfix[MAX_EXPR];
    var_count = 0;

    if (!infix_to_postfix(expr, postfix)) return 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (is_variable(expr[i])) find_var(expr[i]);
    }

    if (var_count == 0) {
        reset_variables();
        return evaluate_postfix(postfix) ? 1 : 0;
    }

    reset_variables();
    do {
        if (!evaluate_postfix(postfix)) return 0;
    } while (next_combination());

        return 1;
}
