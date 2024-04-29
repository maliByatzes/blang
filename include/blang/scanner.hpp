#ifndef BLANG_SCANNER_HPP
#define BLANG_SCANNER_HPP

#include <cstddef>
#include <string>
#include <vector>

namespace blang {

// Enum class for a list of available tokens to be scanned
enum class TokenType {
  t_array, t_boolean, t_char, t_else, t_false, t_for, t_function,
  t_if, t_integer, t_print, t_return, t_string, t_true, t_void,
  t_while, t_identifier, t_integer_lit, t_bool_lit, t_char_lit,
  t_string_lit, t_colon, t_semicolon, t_equal, t_left_square,
  t_right_square, t_left_brace, t_right_brace, t_comma,
  t_left_paren, t_right_paren, t_plus_plus, t_minus_minus,
  t_minus, t_bang, t_exp, t_star, t_slash, t_modulo,
  t_plus, t_less_than, t_less_equal, t_greater_than,
  t_greater_equal, t_equal_equal, t_bang_equal,
  t_and_and, t_or_or, t_eof
};

// Scanner class which produces a vector of tokens one by one from a source
// file or source input.
class Scanner
{
public:
  Scanner() = default;
  explicit Scanner(std::string source) : m_source(std::move(source)) {}

private:
  std::string m_source;
  std::size_t m_position{ 0 };
  std::vector<TokenType> m_tokens;
};

}// namespace blang

#endif
