

#include "../include/scanner.h"

// Public

// Constructor: defines the dfa
Scanner::Scanner() {
    for (int i = 0; i < DFA_MAX_STATES; i++) {
        for (int j = 0; j < DFA_MAX_ALPHABET; j++) {
            m_dfa[i][j] = -1;
        }
    }

    // INT LITERALS

    for (int i = 0; i <= 9; i++) {
        m_dfa[0][i] = 5;
    }

    for (int i = 0; i <= 9; i++) {
        m_dfa[5][i] = 5;
    }

    // Identifiers

    // first char of indentifeir

    // lowercase alphabet
    for (char c = 'a'; c <= 'z'; c++) {
        if (c != 'k' && c != 'l') {
            m_dfa[0][map_char(c)] = 2;
        }
    }
    // uppercase alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        m_dfa[0][map_char(c)] = 2;
    }

    // _
    m_dfa[0][map_char('_')] = 2;

    // 2nd character onwards

    // number
    for (int i = 0; i <= 9; i++) {
        m_dfa[2][i] = 2;
    }

    // lowercase alphabet
    for (char c = 'a'; c <= 'z'; c++) {
        if (c != 'k') {
            m_dfa[2][map_char(c)] = 2;
        }
    }
    // uppercase alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        m_dfa[2][map_char(c)] = 2;
    }

    // _
    m_dfa[2][map_char('_')] = 2;

    // Identifier Keyword Handling

    // for state 1 when 'i' is not input

    for (int i = 0; i <= 9; i++) {
        m_dfa[1][i] = 2;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (c != 'i') {
            m_dfa[1][map_char(c)] = 2;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        m_dfa[1][map_char(c)] = 2;
    }

    m_dfa[1][map_char('_')] = 2;

    // for state 6 when 'l' is not input

    for (int i = 0; i <= 9; i++) {
        m_dfa[6][i] = 2;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (c != 'l') {
            m_dfa[6][map_char(c)] = 2;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        m_dfa[6][map_char(c)] = 2;
    }

    m_dfa[6][map_char('_')] = 2;

    // for state 8

    for (int i = 0; i <= 9; i++) {
        m_dfa[8][i] = 2;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        m_dfa[8][map_char(c)] = 2;
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        m_dfa[8][map_char(c)] = 2;
    }

    m_dfa[8][map_char('_')] = 2;

    // for state 3 when 'e' is not input
    for (int i = 0; i <= 9; i++) {
        m_dfa[3][i] = 2;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (c != 'e') {
            m_dfa[3][map_char(c)] = 2;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        m_dfa[3][map_char(c)] = 2;
    }

    m_dfa[3][map_char('_')] = 2;

    // for state 7
    for (int i = 0; i <= 9; i++) {
        m_dfa[6][i] = 2;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        m_dfa[6][map_char(c)] = 2;
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        m_dfa[6][map_char(c)] = 2;
    }

    m_dfa[6][map_char('_')] = 2;

    // KEYWORDS

    // KILL
    m_dfa[0][map_char('k')] = 1;
    m_dfa[1][map_char('i')] = 6;
    m_dfa[6][map_char('l')] = 8;
    m_dfa[8][map_char('l')] = 2;

    // let
    m_dfa[0][map_char('l')] = 3;
    m_dfa[3][map_char('e')] = 7;
    m_dfa[7][map_char('t')] = 2;

    // SINGLE CHAR
    m_dfa[0][map_char('(')] = 4;
    m_dfa[0][map_char(')')] = 4;
    m_dfa[0][map_char(';')] = 4;
    m_dfa[0][map_char('=')] = 4;
    m_dfa[0][map_char('+')] = 4;
    m_dfa[0][map_char('-')] = 4;
}

std::vector<Token> Scanner::scan_src(const std::string &src) const {

    std::vector<Token> token_list;

    size_t index = 0;

    while (index < src.length()) {
        char c = src.at(index);

        // skip whitespaces
        if (std::isspace(c)) {
            index++;
            continue;
        }

        size_t start = index;
        int state = 0;
        int last_accept_state = -1;
        size_t last_accept_index = -1;

        do {
            int transition_index = map_char(c);
            if (transition_index == -1) {
                std::cerr << "Unidentified Character used: " << c << std::endl;
                exit(1);
            }
            int next_state = m_dfa[state][transition_index];
            if (next_state == -1) {
                break;
            }

            state = next_state;
            if (is_accept_state(state)) {
                last_accept_state = state;
                last_accept_index = index;
            }
            index++;
            if (index >= src.length())
                break;
            c = src.at(index);

            if (isspace(c))
                break;

        } while (index < src.length());

        if (last_accept_state == -1) {
            std::cerr << "Lexical Error. Failed to Tokenize" << std::endl;
            exit(1);
        }

        std::string current_token = src.substr(
            start, last_accept_index - start + 1); // might need a -1 too

        if (getType(current_token, last_accept_state) == TokenType::INT_LIT &&
            current_token.length() > 1 && current_token.at(0) == '0') {
            std::cerr << "Integers cannot have leading zeroes" << std::endl;
            exit(1);
        }

        if (getType(current_token, last_accept_state) == TokenType::INT_LIT && !fitsInt32(current_token)) {
            std::cerr << "OVERFLOW ERROR: Integer must be a 32bit value" << std::endl;
            exit(1);
        }

        token_list.push_back(
            Token{.type = getType(current_token, last_accept_state),
                  .contents = current_token});
    }

    token_list.push_back(
        Token{.type=TokenType::_EOF, .contents = std::string()}
    );

    return token_list;
}

// Private

int Scanner::map_char(char c) const {
    if (c >= '0' && c <= '9')
        return c - '0'; // 0–9

    if (c >= 'a' && c <= 'z')
        return 10 + (c - 'a'); // 10–35

    if (c >= 'A' && c <= 'Z')
        return 36 + (c - 'A'); // 36–61

    switch (c) {
    case '_':
        return 62;
    case '(':
        return 63;
    case ')':
        return 64;
    case ';':
        return 65;
    case '=':
        return 66;
    case '+':
        return 67;
    case '-':
        return 68;
    default:
        return -1;
    }
}

bool Scanner::is_accept_state(const int state) const {
    if (state > 0 && state <= 8) //  1-8 are accept states
        return true;
    else
        return false;
}

TokenType Scanner::getType(const std::string &accept_state,
                           const int last_accept_state) const {
    if (last_accept_state == 5) {
        return TokenType::INT_LIT;
    }

    if (last_accept_state == 2) {
        return isKeyword(accept_state);
    }

    if (last_accept_state == 4) {
        if (accept_state == "(") {
            return TokenType::LPAREN;
        } else if (accept_state == ")") {
            return TokenType::RPAREN;
        } else if (accept_state == ";") {
            return TokenType::_SEMICOLON;
        } else if (accept_state == "=") {
            return TokenType::_EQUALS;
        } else if (accept_state == "+") {
            return TokenType::_PLUS;
        } else if (accept_state == "-") {
            return TokenType::_MINUS;
        }
    }

    std::cerr << "UNEXPECTED TOKEN GENERATED" << std::endl;
    exit(1);
}

TokenType Scanner::isKeyword(const std::string &identifier) const {
    if (identifier == "kill") {
        return TokenType::_KILL;
    } else if (identifier == "let") {
        return  TokenType::_LET;
    }

    return TokenType::_IDENTIFIER;
}


bool Scanner::fitsInt32(const std::string& number) const {
    const std::string MAX_VALUE = "2147483647";

    if (number.size() < MAX_VALUE.size()) return true;
    if (number.size() > MAX_VALUE.size()) return false;

    return number <= MAX_VALUE;
}
