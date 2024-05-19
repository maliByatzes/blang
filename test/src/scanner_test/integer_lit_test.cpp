#include "blang/error/error_reporter.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

// Tests

namespace blang {

class ScannerTest5 : public testing::Test
{
protected:
  error::ErrorReporter reporter;

  Scanner sc_23{ "23", reporter };
  Scanner sc_7522{ "7522", reporter };
  Scanner sc_decl{ "y: integer = 123;", reporter };
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

TEST_F(ScannerTest5, TestIntegerLitDecl) {
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, 1, 1, "y" },
    Token{ TokenType::t_colon, 2, 1, ':' },
    Token{ TokenType::t_integer, 10, 1, "integer" },
    Token{ TokenType::t_equal, 12, 1, '=' },
    Token{ TokenType::t_integer_lit, 16, 1, 123 },
    Token{ TokenType::t_semicolon, 17, 1, ';' },
    Token{ TokenType::t_eof, 18, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_decl);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest5, TestIntegerLitToken1)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_integer_lit, 2, 1, 23 },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_23);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest5, TestIntegerLitToken2)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_integer_lit, 4, 1, 7522 },
    Token{ TokenType::t_eof, 5, 1, '\0' },
  };
  // NOLINTEND

  run_scanner_test(expected_tokens, sc_7522);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
