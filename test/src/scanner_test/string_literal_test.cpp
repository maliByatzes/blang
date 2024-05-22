#include "blang/error/error_reporter.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

// Tests

namespace blang {

class ScannerTest10 : public testing::Test
{
protected:
  error::ErrorReporter reporter;

  // Test string literal processing
  Scanner sc_hello{ "\"hello\"", reporter };
  Scanner sc_hello_2{ "\"h5725gf45llo\"", reporter };
  Scanner sc_hello_nl{ "\"he\nllo\"", reporter };
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

TEST_F(ScannerTest10, TestStringLitHelloToken)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_string_lit, 7, 1, "hello" },
    Token{ TokenType::t_eof, 8, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_hello);
  ASSERT_EQ(sc_hello.get_status(), error::Status::OK);
}

TEST_F(ScannerTest10, TestStringLitHelloNumToken)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_string_lit, 14, 1, "h5725gf45llo" },
    Token{ TokenType::t_eof, 15, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_hello_2);
  ASSERT_EQ(sc_hello_2.get_status(), error::Status::OK);
}

TEST_F(ScannerTest10, TestStringLitHelloNLToken)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_string_lit, 8, 2, "hello" },
    Token{ TokenType::t_eof, 9, 2, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_hello_nl);
  ASSERT_EQ(sc_hello_nl.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
