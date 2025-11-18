#ifndef LOGIC_TAUTOLOGY_H
#define LOGIC_TAUTOLOGY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
    #endif

    /**
     * @brief Checks if a logical expression is a tautology
     *
     * @param expr Logical expression without parentheses
     * @return int 1 if tautology, 0 if not or if expression is invalid
     *
     * Supported operators (ASCII only):
     * - NOT: ~ or !
     * - AND: ^
     * - OR: v
     * - IMPLICATION: >
     * - BICONDITIONAL: =
     *
     * Variables: single CAPITAL letters (A-Z)
     * Constants: 1 (true), 0 (false)
     *
     * Example: "P ^ Q > P" evaluates to (P ∧ Q) → P (tautology)
     */
    int is_tautology(const char* expr);

    /**
     * @brief Evaluates a logical expression with given variable values
     *
     * @param expr Expression without parentheses
     * @param var_names Array of variable names (as string)
     * @param var_values Array of variable values
     * @param var_count Number of variables
     * @return bool Result of evaluation, false if expression is invalid
     */
    bool evaluate_expression_with_values(const char* expr,
                                         const char* var_names,
                                         const bool* var_values,
                                         int var_count);

    /**
     * @brief Cleans up any internal state (useful for multiple expressions)
     */
    void logic_cleanup(void);

    #ifdef __cplusplus
}
#endif

#endif // LOGIC_TAUTOLOGY_H
