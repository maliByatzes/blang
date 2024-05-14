#include "blang/scanner.hpp"
#include "blang/token_type.hpp"
#include <cctype>
#include <locale>
#include <string>

namespace blang {

using value_object = std::variant<int, std::string, char>;

std::vector<Token> Scanner::scan_tokens()
{

  while (m_position < m_source.size()) {// NOLINT // unsure abt this condition, check later
    char current_char{ consume() };

    switch (current_char) {
    case ':':
      add_token(TokenType::t_colon, ':');
      break;
    case ';':
      add_token(TokenType::t_semicolon, ';');
      break;
    case '=':
      consume_next('=', TokenType::t_equal_equal, "==", TokenType::t_equal, '=');
      break;
    case '[':
      add_token(TokenType::t_left_square, '[');
      break;
    case ']':
      add_token(TokenType::t_right_square, ']');
      break;
    case '{':
      add_token(TokenType::t_left_brace, '{');
      break;
    case '}':
      add_token(TokenType::t_right_brace, '}');
      break;
    case ',':
      add_token(TokenType::t_comma, ',');
      break;
    case '(':
      add_token(TokenType::t_left_paren, '(');
      break;
    case ')':
      add_token(TokenType::t_right_paren, ')');
      break;
    case '-':
      consume_next('-', TokenType::t_minus_minus, "--", TokenType::t_minus, '-');
      break;
    case '!':
      consume_next('=', TokenType::t_bang_equal, "!=", TokenType::t_bang, '!');
      break;
    case '^':
      add_token(TokenType::t_exponent, '^');
      break;
    case '*':
      add_token(TokenType::t_star, '*');
      break;
    case '/':
      add_token(TokenType::t_slash, '/');
      break;
    case '%':
      add_token(TokenType::t_modulo, '%');
      break;
    case '+':
      consume_next('+', TokenType::t_plus_plus, "++", TokenType::t_plus, '+');
      break;
    case '<':
      consume_next('=', TokenType::t_less_equal, "<=", TokenType::t_less_than, '<');
      break;
    case '>':
      consume_next('=', TokenType::t_greater_equal, ">=", TokenType::t_greater_than, '>');
      break;
    case '&':
      if (peek_next().has_value() && peek_next().value() == '&') {
        consume();
        add_token(TokenType::t_and_and, "&&");
      }
      break;
    case '|':
      if (peek_next().has_value() && peek_next().value() == '|') {
        consume();
        add_token(TokenType::t_or_or, "||");
      }
      break;
    case '\'':
      process_char_lit();
      break;
    case '"':
      process_string_lit();
      break;
    case ' ':
      break;
    case '\n':
      m_line++;
      break;
    default:

      if (valid_identifier_start_char(current_char)) {
        process_identifier(current_char);
      } else if (static_cast<bool>(std::isdigit(current_char))) {
        process_integer_lit(current_char);
      }

      else {
        std::string message{ "Unexpected character: " + std::to_string(current_char) };
        m_reporter.set_error(m_position, message);
      }
    }
  }

  m_tokens.push_back(Token{ TokenType::t_eof, m_position + 1, m_line, '\0' });

  return m_tokens;
}

char Scanner::consume() { return m_source.at(m_position++); }

void Scanner::add_token(TokenType type, const value_object &value)
{
  m_tokens.push_back(Token{ type, m_position, m_line, value });
}

std::optional<char> Scanner::peek_next() const
{
  if (m_position >= m_source.size()) { return {}; }
  return m_source.at(m_position);
}

void Scanner::consume_next(char next,
  TokenType dbl,
  const value_object &val_dbl,
  TokenType single,
  const value_object &val_single)
{
  if (peek_next().has_value() && peek_next().value() == next) {
    consume();
    add_token(dbl, val_dbl);
  } else {
    add_token(single, val_single);
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

void Scanner::process_identifier(char curr_char)
{
  std::string buffer{};
  buffer.push_back(curr_char);

  while (peek_next().has_value() && valid_identifier_char(peek_next().value())) {// NOLINT
    char next_char = consume();
    buffer.push_back(next_char);
  }

  add_token(TokenType::t_identifier, buffer);
}

void Scanner::process_integer_lit(char curr_char)
{
  std::string buffer{};
  buffer.push_back(curr_char);

  while (peek_next().has_value() && static_cast<bool>(std::isdigit(peek_next().value()))) {// NOLINT
    char next_char = consume();
    buffer.push_back(next_char);
  }

  int value = std::stoi(buffer);
  add_token(TokenType::t_integer_lit, value);
}

void Scanner::process_char_lit()
{
  std::locale c_loc("C");
  if (peek_next().has_value() && std::isalpha(peek_next().value(), c_loc)) {
    char value = consume();
    if (peek_next().has_value() && peek_next().value() == '\'') {
      add_token(TokenType::t_char_lit, value);
      consume();
    } else {
      std::string message{ "Unterminated character, missing \"'\"" };
      m_reporter.set_error(m_position, message);
    }
  }
}

void Scanner::process_string_lit()
{
  std::string buffer{};
  while (peek_next().has_value() && peek_next().value() != '"') {// NOLINT
    // allow multi-line strings FOR NOW!!
    // TODO: Disallow multi-line string literals
    char next_char = consume();
    if (next_char == '\n') {
      m_line++;
    } else {
      buffer.push_back(next_char);
    }
  }

  consume();
  add_token(TokenType::t_string_lit, buffer);
}

}// namespace blang
