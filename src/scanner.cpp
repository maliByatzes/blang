#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

namespace blang {

std::vector<Token> Scanner::scan_tokens()
{

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
    case '=':
      add_token(TokenType::t_equal);
    default:
      std::string message{ "Unexpected character: " + std::to_string(current_char) };
      m_reporter.set_error(m_position, message);
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
