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
      consume_next('=', TokenType::t_equal_equal, TokenType::t_equal);
      break;
    case '[':
      add_token(TokenType::t_left_square);
      break;
    case ']':
      add_token(TokenType::t_right_square);
      break;
    case '{':
      add_token(TokenType::t_left_brace);
      break;
    case '}':
      add_token(TokenType::t_right_brace);
      break;
    case ',':
      add_token(TokenType::t_comma);
      break;
    case '(':
      add_token(TokenType::t_left_paren);
      break;
    case ')':
      add_token(TokenType::t_right_paren);
      break;
    case '-':
      consume_next('-', TokenType::t_minus_minus, TokenType::t_minus);
      break;
    case '!':
      consume_next('=', TokenType::t_bang_equal, TokenType::t_bang);
      break;
    case '^':
      add_token(TokenType::t_exponent);
      break;
    case '*':
      add_token(TokenType::t_star);
      break;
    case '/':
      add_token(TokenType::t_slash);
      break;
    case '%':
      add_token(TokenType::t_modulo);
      break;
    case '+':
      consume_next('+', TokenType::t_plus_plus, TokenType::t_plus);
      break;
    case '<':
      consume_next('=', TokenType::t_less_equal, TokenType::t_less_than);
      break;
    case '>':
      consume_next('=', TokenType::t_greater_equal, TokenType::t_greater_than);
      break;
    case '&':
      if (peek_next() == '&') {
        consume();
        add_token(TokenType::t_and_and);
      }
      break;
    case '|':
      if (peek_next() == '|') {
        consume();
        add_token(TokenType::t_or_or);
      }
      break;
    case ' ':
      break;
    default:
      std::string message{ "Unexpected character: " + std::to_string(current_char) };
      m_reporter.set_error(m_position, message);
    }
  }

  m_tokens.push_back(Token{ TokenType::t_eof, m_position + 1 });

  return m_tokens;
}

char Scanner::consume()
{
  char r_char{ m_source.at(m_position) };
  m_position++;
  return r_char;
}

void Scanner::add_token(TokenType type) { m_tokens.push_back(Token{ type, m_position }); }

char Scanner::peek_next() const { return m_source.at(m_position); }

void Scanner::consume_next(char next, TokenType dbl, TokenType single)
{
  if (peek_next() == next) {
    consume();
    add_token(dbl);
  } else {
    add_token(single);
  }
}

}// namespace blang
