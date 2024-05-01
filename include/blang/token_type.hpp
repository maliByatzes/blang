#ifndef BLANG_TOKEN_TYPE_HPP
#define BLANG_TOKEN_TYPE_HPP

namespace blang {

// Enum class for a list of available tokens to be scanned
enum class TokenType {
  t_array,
  t_boolean,
  t_char,
  t_else,
  t_false,
  t_for,
  t_function,
  t_if,
  t_integer,
  t_print,
  t_return,
  t_string,
  t_true,
  t_void,
  t_while,
  t_identifier,
  t_integer_lit,
  t_bool_lit,
  t_char_lit,
  t_string_lit,
  t_colon,
  t_semicolon,
  t_equal,
  t_left_square,
  t_right_square,
  t_left_brace,
  t_right_brace,
  t_comma,
  t_left_paren,
  t_right_paren,
  t_plus_plus,
  t_minus_minus,
  t_minus,
  t_bang,
  t_exp,
  t_star,
  t_slash,
  t_modulo,
  t_plus,
  t_less_than,
  t_less_equal,
  t_greater_than,
  t_greater_equal,
  t_equal_equal,
  t_bang_equal,
  t_and_and,
  t_or_or,
  t_eof
};

}// namespace blang

#endif
