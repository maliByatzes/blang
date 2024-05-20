#include "blang/error/error_reporter.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

// Tests

namespace blang {

class ScannerTest7 : public testing::Test
{
protected:
  error::ErrorReporter reporter;

  Scanner sc_all_single{ ":;[]{},()^*/%=-!+<>", reporter };
  Scanner sc_all_dbls{ "== -- != <= >= && ||", reporter };
  Scanner sc_mixture{ ": ; != = == < <= > > >= + ( { ) }", reporter };
  Scanner sc_identifier_kw{ "array arrayrt3d function if else falsefalse print voider", reporter };
  Scanner sc_declarations{ "x: integer;\nb: boolean = false;\nc: char = 'q';\ns: string = \"hello world\n\";",
    reporter };
  Scanner sc_array1{ "a: array [5] integer;", reporter };
  Scanner sc_array2{ "a: array [5] integer = {1,2,3};", reporter };
  Scanner sc_print{ "print \"The temperature is: \", temp, \" degrees\n\";", reporter };
  Scanner sc_function{ "square: function integer ( x: integer ) = {\n return xˆ2;\n}", reporter };
};

void run_scanner_test(const std::vector<Token> &expected_tokens, Scanner &scanner)
{
  std::vector<Token> actual_tokens{ scanner.scan_tokens() };
  ASSERT_EQ(actual_tokens.size(), expected_tokens.size());
  auto compare = [](const Token &tk1, const Token &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line && tk1.value == tk2.value;
  };
  ASSERT_TRUE(std::equal(actual_tokens.begin(), actual_tokens.end(), expected_tokens.begin(), compare));
}

/*
TEST_F(ScannerTest7, TestFunction)
{
  //NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, 6, 1, "square" },
    Token{ TokenType::t_colon, 7, 1, ':' },
    Token{ TokenType::t_function, 16, 1, "function" },
    Token{ TokenType::t_integer, 24, 1, "integer" },
    Token{ TokenType::t_left_paren, 26, 1, '(' },
    Token{ TokenType::t_identifier, 28, 1, "x" },
    Token{ TokenType::t_colon, 29, 1, ':' },
    Token{ TokenType::t_integer, 37, 1, "integer" },
    Token{ TokenType::t_right_paren, 41, 1, ')' },
    Token{ TokenType::t_equal, 43, 1, '=' },
    Token{ TokenType::t_left_brace, 45, 1, '{' },
    Token{ TokenType::t_return, 53, 2, "return" },
    Token{ TokenType::t_identifier, 55, 2, "x" },
    Token{ TokenType::t_exponent, 56, 2, '^' },
    Token{ TokenType::t_integer_lit, 57, 2, 2 },
    Token{ TokenType::t_semicolon, 58, 2, ';' },
    Token{ TokenType::t_right_brace, 60, 3, '}' },
    Token{ TokenType::t_eof, 61, 3, '\0' },
  };
  //NOLINTEND

  run_scanner_test(expected_tokens, sc_function);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}
*/

TEST_F(ScannerTest7, TestDeclarations)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, 1, 1, "x" },
    Token{ TokenType::t_colon, 2, 1, ':' },
    Token{ TokenType::t_integer, 10, 1, "integer" },
    Token{ TokenType::t_semicolon, 11, 1, ';' },
    Token{ TokenType::t_identifier, 13, 2, "b" },
    Token{ TokenType::t_colon, 14, 2, ':' },
    Token{ TokenType::t_boolean, 22, 2, "boolean" },
    Token{ TokenType::t_equal, 24, 2, '=' },
    Token{ TokenType::t_false, 30, 2, "false" },
    Token{ TokenType::t_semicolon, 31, 2, ';' },
    Token{ TokenType::t_identifier, 33, 3, "c" },
    Token{ TokenType::t_colon, 34, 3, ':' },
    Token{ TokenType::t_char, 39, 3, "char" },
    Token{ TokenType::t_equal, 41, 3, '=' },
    Token{ TokenType::t_char_lit, 44, 3, 'q' },
    Token{ TokenType::t_semicolon, 46, 3, ';' },
    Token{ TokenType::t_identifier, 48, 4, "s" },
    Token{ TokenType::t_colon, 49, 4, ':' },
    Token{ TokenType::t_string, 56, 4, "string" },
    Token{ TokenType::t_equal, 58, 4, '=' },
    Token{ TokenType::t_string_lit, 73, 5, "hello world" },
    Token{ TokenType::t_semicolon, 74, 5, ';' },
    Token{ TokenType::t_eof, 75, 5, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_declarations);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestAllSingleTokens)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_colon, 1, 1, ':' },
    Token{ TokenType::t_semicolon, 2, 1, ';' },
    Token{ TokenType::t_left_square, 3, 1, '[' },
    Token{ TokenType::t_right_square, 4, 1, ']' },
    Token{ TokenType::t_left_brace, 5, 1, '{' },
    Token{ TokenType::t_right_brace, 6, 1, '}' },
    Token{ TokenType::t_comma, 7, 1, ',' },
    Token{ TokenType::t_left_paren, 8, 1, '(' },
    Token{ TokenType::t_right_paren, 9, 1, ')' },
    Token{ TokenType::t_exponent, 10, 1, '^' },
    Token{ TokenType::t_star, 11, 1, '*' },
    Token{ TokenType::t_slash, 12, 1, '/' },
    Token{ TokenType::t_modulo, 13, 1, '%' },
    Token{ TokenType::t_equal, 14, 1, '=' },
    Token{ TokenType::t_minus, 15, 1, '-' },
    Token{ TokenType::t_bang, 16, 1, '!' },
    Token{ TokenType::t_plus, 17, 1, '+' },
    Token{ TokenType::t_less_than, 18, 1, '<' },
    Token{ TokenType::t_greater_than, 19, 1, '>' },
    Token{ TokenType::t_eof, 20, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_all_single);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestAllDoubleTokens)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_equal_equal, 2, 1, "==" },
    Token{ TokenType::t_minus_minus, 5, 1, "--" },
    Token{ TokenType::t_bang_equal, 8, 1, "!=" },
    Token{ TokenType::t_less_equal, 11, 1, "<=" },
    Token{ TokenType::t_greater_equal, 14, 1, ">=" },
    Token{ TokenType::t_and_and, 17, 1, "&&" },
    Token{ TokenType::t_or_or, 20, 1, "||" },
    Token{ TokenType::t_eof, 21, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_all_dbls);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestMixtureTokens)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_colon, 1, 1, ':' },
    Token{ TokenType::t_semicolon, 3, 1, ';' },
    Token{ TokenType::t_bang_equal, 6, 1, "!=" },
    Token{ TokenType::t_equal, 8, 1, '=' },
    Token{ TokenType::t_equal_equal, 11, 1, "==" },
    Token{ TokenType::t_less_than, 13, 1, '<' },
    Token{ TokenType::t_less_equal, 16, 1, "<=" },
    Token{ TokenType::t_greater_than, 18, 1, '>' },
    Token{ TokenType::t_greater_than, 20, 1, '>' },
    Token{ TokenType::t_greater_equal, 23, 1, ">=" },
    Token{ TokenType::t_plus, 25, 1, '+' },
    Token{ TokenType::t_left_paren, 27, 1, '(' },
    Token{ TokenType::t_left_brace, 29, 1, '{' },
    Token{ TokenType::t_right_paren, 31, 1, ')' },
    Token{ TokenType::t_right_brace, 33, 1, '}' },
    Token{ TokenType::t_eof, 34, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_mixture);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestIdentifierKWTokens)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_array, 5, 1, "array" },
    Token{ TokenType::t_identifier, 15, 1, "arrayrt3d" },
    Token{ TokenType::t_function, 24, 1, "function" },
    Token{ TokenType::t_if, 27, 1, "if" },
    Token{ TokenType::t_else, 32, 1, "else" },
    Token{ TokenType::t_identifier, 43, 1, "falsefalse" },
    Token{ TokenType::t_print, 49, 1, "print" },
    Token{ TokenType::t_identifier, 56, 1, "voider" },
    Token{ TokenType::t_eof, 57, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_identifier_kw);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestArray1)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, 1, 1, "a" },
    Token{ TokenType::t_colon, 2, 1, ':' },
    Token{ TokenType::t_array, 8, 1, "array" },
    Token{ TokenType::t_left_square, 10, 1, '[' },
    Token{ TokenType::t_integer_lit, 11, 1, 5 },
    Token{ TokenType::t_right_square, 12, 1, ']' },
    Token{ TokenType::t_integer, 20, 1, "integer" },
    Token{ TokenType::t_semicolon, 21, 1, ';' },
    Token{ TokenType::t_eof, 22, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_array1);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestArray2)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, 1, 1, "a" },
    Token{ TokenType::t_colon, 2, 1, ':' },
    Token{ TokenType::t_array, 8, 1, "array" },
    Token{ TokenType::t_left_square, 10, 1, '[' },
    Token{ TokenType::t_integer_lit, 11, 1, 5 },
    Token{ TokenType::t_right_square, 12, 1, ']' },
    Token{ TokenType::t_integer, 20, 1, "integer" },
    Token{ TokenType::t_equal, 22, 1, '=' },
    Token{ TokenType::t_left_brace, 24, 1, '{' },
    Token{ TokenType::t_integer_lit, 25, 1, 1 },
    Token{ TokenType::t_comma, 26, 1, ',' },
    Token{ TokenType::t_integer_lit, 27, 1, 2 },
    Token{ TokenType::t_comma, 28, 1, ',' },
    Token{ TokenType::t_integer_lit, 29, 1, 3 },
    Token{ TokenType::t_right_brace, 30, 1, '}' },
    Token{ TokenType::t_semicolon, 31, 1, ';' },
    Token{ TokenType::t_eof, 32, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_array2);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestPrint)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_print, 5, 1, "print" },
    Token{ TokenType::t_string_lit, 28, 1, "The temperature is: " },
    Token{ TokenType::t_comma, 29, 1, ',' },
    Token{ TokenType::t_identifier, 34, 1, "temp" },
    Token{ TokenType::t_comma, 35, 1, ',' },
    Token{ TokenType::t_string_lit, 47, 2, " degrees" },
    Token{ TokenType::t_semicolon, 48, 2, ';' },
    Token{ TokenType::t_eof, 49, 2, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_print);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
