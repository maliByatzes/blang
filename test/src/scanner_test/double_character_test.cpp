#include "blang/error/error_reporter.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

// Tests

namespace blang {

class ScannerTest3 : public testing::Test
{
protected:
  error::ErrorReporter reporter;

  // Double-character tokens
  Scanner sc_eq_eq{ "==", reporter };
  Scanner sc_minus_minus{ "--", reporter };
  Scanner sc_bang_not{ "!=", reporter };
  Scanner sc_less_eq{ "<=", reporter };
  Scanner sc_greater_eq{ ">=", reporter };
  Scanner sc_and_and{ "&&", reporter };
  Scanner sc_or_or{ "||", reporter };
  Scanner sc_plus_plus{ "++", reporter };
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

TEST_F(ScannerTest3, TestEqualEqualToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_equal_equal, 2, 1, "==" },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_eq_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest3, TestMinusMinusToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_minus_minus, 2, 1, "--" },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_minus_minus);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest3, TestBangEqualToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_bang_equal, 2, 1, "!=" },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_bang_not);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest3, TestLessEqualToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_less_equal, 2, 1, "<=" },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_less_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest3, TestGreaterEqualToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_greater_equal, 2, 1, ">=" },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_greater_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest3, TestAndAndToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_and_and, 2, 1, "&&" },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_and_and);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest3, TestOrOrToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_or_or, 2, 1, "||" },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_or_or);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest3, TestPlusPlusToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_plus_plus, 2, 1, "++" },
    Token{ TokenType::t_eof, 3, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_plus_plus);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
