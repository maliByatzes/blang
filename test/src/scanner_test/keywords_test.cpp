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

  Scanner sc_array{ "array", reporter };
  Scanner sc_boolean{ "boolean", reporter };
  Scanner sc_char{ "char", reporter };
  Scanner sc_else{ "else", reporter };
  Scanner sc_false{ "false", reporter };
  Scanner sc_for{ "for", reporter };
  Scanner sc_function{ "function", reporter };
  Scanner sc_if{ "if", reporter };
  Scanner sc_integer{ "integer", reporter };
  Scanner sc_print{ "print", reporter };
  Scanner sc_return{ "return", reporter };
  Scanner sc_string{ "string", reporter };
  Scanner sc_true{ "true", reporter };
  Scanner sc_void{ "void", reporter };
  Scanner sc_while{ "while", reporter };
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

TEST_F(ScannerTest7, TestArrayToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_array, 5, 1, "array" },// NOLINT
    Token{ TokenType::t_eof, 6, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_array);
  ASSERT_EQ(sc_array.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestBooleanToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_boolean, 7, 1, "boolean" },// NOLINT
    Token{ TokenType::t_eof, 8, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_boolean);
  ASSERT_EQ(sc_boolean.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestCharToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_char, 4, 1, "char" },// NOLINT
    Token{ TokenType::t_eof, 5, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_char);
  ASSERT_EQ(sc_char.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestElseToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_else, 4, 1, "else" },// NOLINT
    Token{ TokenType::t_eof, 5, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_else);
  ASSERT_EQ(sc_else.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestFalseToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_false, 5, 1, "false" },// NOLINT
    Token{ TokenType::t_eof, 6, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_false);
  ASSERT_EQ(sc_false.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestForToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_for, 3, 1, "for" },// NOLINT
    Token{ TokenType::t_eof, 4, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_for);
  ASSERT_EQ(sc_for.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestFunctionToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_function, 8, 1, "function" },// NOLINT
    Token{ TokenType::t_eof, 9, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_function);
  ASSERT_EQ(sc_function.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestIfToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_if, 2, 1, "if" },// NOLINT
    Token{ TokenType::t_eof, 3, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_if);
  ASSERT_EQ(sc_if.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestIntegerToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_integer, 7, 1, "integer" },// NOLINT
    Token{ TokenType::t_eof, 8, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_integer);
  ASSERT_EQ(sc_integer.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestPrintToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_print, 5, 1, "print" },// NOLINT
    Token{ TokenType::t_eof, 6, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_print);
  ASSERT_EQ(sc_print.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestReturnToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_return, 6, 1, "return" },// NOLINT
    Token{ TokenType::t_eof, 7, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_return);
  ASSERT_EQ(sc_return.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestStringToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_string, 6, 1, "string" },// NOLINT
    Token{ TokenType::t_eof, 7, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_string);
  ASSERT_EQ(sc_string.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestTrueToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_true, 4, 1, "true" },// NOLINT
    Token{ TokenType::t_eof, 5, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_true);
  ASSERT_EQ(sc_true.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestVoidToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_void, 4, 1, "void" },// NOLINT
    Token{ TokenType::t_eof, 5, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_void);
  ASSERT_EQ(sc_void.get_status(), error::Status::OK);
}

TEST_F(ScannerTest7, TestWhileToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_while, 5, 1, "while" },// NOLINT
    Token{ TokenType::t_eof, 6, 1, '\0' },// NOLINT
  };
  run_scanner_test(expected_tokens, sc_while);
  ASSERT_EQ(sc_while.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
