#pragma once

#include <iostream>
#include <string>
#include <vector>

#define DFA_MAX_STATES 9
#define DFA_MAX_ALPHABET 71

enum class TokenType {
    _KILL,
    LPAREN,
    RPAREN,
    INT_LIT,
    _SEMICOLON,
    _EQUALS,
    _IDENTIFIER,
    _LET,
    _PLUS,
    _MINUS,
    _MULT,
    _DIV,
    _EOF
};

struct Token {
    TokenType type;
    std::string contents; // stores data if required, else NULL
};

inline std::ostream &operator<<(std::ostream &os, TokenType t) {
    switch (t) {
    case TokenType::_KILL:
        return os << "kill";
    case TokenType::LPAREN:
        return os << "'('";
    case TokenType::RPAREN:
        return os << "')'";
    case TokenType::INT_LIT:
        return os << "Integer Literal";
    case TokenType::_SEMICOLON:
        return os << "';'";
    case TokenType::_EQUALS:
        return os << "'='";
    case TokenType::_IDENTIFIER:
        return os << "Identifier";
    case TokenType::_LET:
        return os << "Let";
    case TokenType::_PLUS:
        return os << "+";
    case TokenType::_MINUS:
        return os << "-";
    }
    return os << "<unexpected token>";
}

class Scanner {
  public:
    Scanner();

    // scans the source code and returns a list of tokens
    std::vector<Token> scan_src(const std::string &src) const;

  private:
    int m_dfa[DFA_MAX_STATES][DFA_MAX_ALPHABET];

    size_t index;

    // maps a character to get the transition index on the DFA
    int map_char(const char c) const;

    // returns true if the state is an accept state
    bool is_accept_state(const int state) const;

    // identifies the token type based on extracted string
    TokenType getType(const std::string &accept_state,
                      const int last_accept_state) const;

    // checks if extracted string is a particular token
    TokenType isKeyword(const std::string& identifier) const;

    bool fitsInt32(const std::string& number) const;
};