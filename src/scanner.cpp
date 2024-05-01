#include "blang/scanner.hpp"
#include <iostream>

namespace blang {

std::vector<Token> Scanner::scan_tokens()
{
  // consume the very first character from source string
  char current_char{ consume() };

  // switch-case on current_char and identify tokens
  switch (current_char) {
  // process all the one character tokens
  case ':':
    add_token(TokenType::t_colon);
    break;
  case ';':
    add_token(TokenType::t_semicolon);
    break;
  default:
    std::cerr << "Token not identified!\n";
  }

  return m_tokens;
}

char Scanner::consume()
{
  char r_char{ m_source.at(m_position) };
  m_position++;
  return r_char;
}

void Scanner::add_token(TokenType type) { m_tokens.push_back(Token{ type, m_position }); }

}// namespace blang
