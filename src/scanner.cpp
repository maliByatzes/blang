#include "blang/scanner.hpp"
#include "blang/token_type.hpp"
#include <cctype>
#include <locale>

namespace blang {

std::vector<Token> Scanner::scan_tokens()
{

  while (m_position < m_source.size()) {
    char current_char{ consume() };

    switch (current_char) {
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
      if (peek_next().has_value() && peek_next().value() == '&') {
        consume();
        add_token(TokenType::t_and_and);
      }
      break;
    case '|':
      if (peek_next().has_value() && peek_next().value() == '|') {
        consume();
        add_token(TokenType::t_or_or);
      }
      break;
    case ' ':
      break;
    case '\n':
      m_line++;
      break;
    default:

      if (valid_identifier_start_char(current_char)) {
        // initialize a temp buffer
        std::string buffer{};
        buffer.push_back(current_char);

        while (peek_next().has_value() && valid_identifier_char(peek_next().value())) { // NOLINT
          char next_char = consume();
          buffer.push_back(next_char);
        }

        add_token(TokenType::t_identifier);
      } else {
        std::string message{ "Unexpected character: " + std::to_string(current_char) };
        m_reporter.set_error(m_position, message);
      }
    }
  }

  m_tokens.push_back(Token{ TokenType::t_eof, m_position + 1, m_line });

  return m_tokens;
}

char Scanner::consume() { return m_source.at(m_position++); }

void Scanner::add_token(TokenType type) { m_tokens.push_back(Token{ type, m_position, m_line }); }

std::optional<char> Scanner::peek_next() const
{
  if (m_position >= m_source.size()) { return {}; }
  return m_source.at(m_position);
}

void Scanner::consume_next(char next, TokenType dbl, TokenType single)
{
  if (peek_next().has_value() && peek_next().value() == next) {
    consume();
    add_token(dbl);
  } else {
    add_token(single);
  }
}

bool Scanner::valid_identifier_start_char(char chh)
{
  std::locale c_loc("C");
  return std::isalpha(chh, c_loc) || chh == '_';
}

bool Scanner::valid_identifier_char(char chh)
{
  return valid_identifier_start_char(chh) || static_cast<bool>(std::isdigit(chh));
}

}// namespace blang
