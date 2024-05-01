#include "blang/scanner.hpp"
#include "blang/token_type.hpp"
#include <algorithm>
#include <iostream>

namespace blang {

std::vector<Token> Scanner::scan_tokens()
{
  /*
  auto iter = std::find_if_not(m_source.begin(), m_source.end(), [this](char curr) {
    switch (curr) {
    case ':':
      add_token(TokenType::t_colon);
      return false;
    case ';':
      add_token(TokenType::t_semicolon);
      return false;
    default:
      return true;
    }
  });

  if (iter != m_source.end()) {}
*/

#pragma unroll 1
  while (m_position < m_source.size()) {
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
