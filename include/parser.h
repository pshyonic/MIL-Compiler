#pragma once
#include "scanner.h"
#include "ast.h"

#include <optional>
#include <vector>


class Parser {
  public:
    explicit Parser(std::vector<Token> *t);


    using stmt_list = std::vector<std::unique_ptr<stmt_node>>;
    stmt_list parse_PROG();

  private:
    std::vector<Token> *m_tokens;
    size_t m_index;

    std::unique_ptr<stmt_node> parse_STMT();
    stmt_list parse_STMT_LIST();

    std::unique_ptr<expr_node> parse_EXPR();

    Token scan_token();

    Token expect_token(TokenType t);

    std::optional<TokenType> peek_type();
};