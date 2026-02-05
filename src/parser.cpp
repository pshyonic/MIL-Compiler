#include "../include/parser.h"

#include <iostream>
#include <optional>

Parser::Parser(std::vector<Token> *t) {
    m_tokens = t;
    m_index = 0;
}

using stmt_list = std::vector<std::unique_ptr<stmt_node>>;

stmt_list Parser::parse_PROG() { return parse_STMT_LIST(); }

Token Parser::scan_token() {
    if (m_index >= m_tokens->size()) {
        std::cerr << "PARSE ERROR: End of Input" << std::endl;
        exit(1);
    }

    return m_tokens->at(m_index++);
}

std::unique_ptr<expr_node> Parser::parse_EXPR() {
    Token t = scan_token();

    if (t.type == TokenType::INT_LIT) {
        return std::make_unique<int_literal_node>(stoi(t.contents));
    }

    if (t.type == TokenType::_IDENTIFIER) {
        return std::make_unique<ident_node>(t.contents);
    }

    std::cerr << "PARSE ERROR:\nExpected Expression Node" << std::endl;
    exit(1);
}


std::unique_ptr<stmt_node> Parser::parse_STMT() {
    Token t = scan_token();
    if (t.type == TokenType::_KILL) {
        expect_token(TokenType::LPAREN);
        std::unique_ptr<expr_node> value = parse_EXPR();
        expect_token(TokenType::RPAREN);
        expect_token(TokenType::_SEMICOLON);

        return std::make_unique<killstmt_node>(std::move(value));
    } else if (t.type == TokenType::_LET) {
        t = expect_token(TokenType::_IDENTIFIER);
        std::string name = t.contents;
        expect_token(TokenType::_EQUALS);
        std::unique_ptr<expr_node> value = parse_EXPR();
        expect_token(TokenType::_SEMICOLON);

        return std::make_unique<decl_stmt_node>(std::move(name), std::move(value));
    } else {
        std::cerr << "PARSE ERROR:\nExpected Kill or Let Tokens" << std::endl;
        exit(1);
    }

}

stmt_list Parser::parse_STMT_LIST() {
    stmt_list list;
    while (peek_type() == TokenType::_KILL || peek_type() == TokenType::_LET) {
        list.push_back(parse_STMT());
    }

    return list;
}



Token Parser::expect_token(const TokenType t) {
    Token st = scan_token();
    if (st.type != t) {
        std::cerr << "PARSE ERROR:\nExpected Token " << t << std::endl;
        exit(1);
    }
    return st;
}

std::optional<TokenType> Parser::peek_type() {
    if (m_index >= m_tokens->size()) {
        return std::nullopt;
    }

    return m_tokens->at(m_index).type;
}

