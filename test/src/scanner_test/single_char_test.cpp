#include "blang/error/error_reporter.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

// Tests

namespace blang {

class ScannerTest8 : public testing::Test
{
protected:
  error::ErrorReporter reporter;

  // Single-character tokens
  Scanner sc_colon{ ":", reporter };
  Scanner sc_semicolon{ ";", reporter };
  Scanner sc_left_sq{ "[", reporter };
  Scanner sc_right_sq{ "]", reporter };
  Scanner sc_left_brace{ "{", reporter };
  Scanner sc_right_brace{ "}", reporter };
  Scanner sc_comma{ ",", reporter };
  Scanner sc_left_paren{ "(", reporter };
  Scanner sc_right_paren{ ")", reporter };
  Scanner sc_exp{ "^", reporter };
  Scanner sc_star{ "*", reporter };
  Scanner sc_slash{ "/", reporter };
  Scanner sc_modulo{ "%", reporter };
  Scanner sc_eq{ "=", reporter };
  Scanner sc_minus{ "-", reporter };
  Scanner sc_bang{ "!", reporter };
  Scanner sc_plus{ "+", reporter };
  Scanner sc_less{ "<", reporter };
  Scanner sc_greater{ ">", reporter };
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

TEST_F(ScannerTest8, TestColonToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_colon, 1, 1, ':' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_colon);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestSemicolonToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_semicolon, 1, 1, ';' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_semicolon);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestLeftSquareToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_left_square, 1, 1, '[' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_left_sq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestRightSquareToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_right_square, 1, 1, ']' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_right_sq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestLeftBraceToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_left_brace, 1, 1, '{' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_left_brace);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestRightBraceToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_right_brace, 1, 1, '}' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_right_brace);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestCommaToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_comma, 1, 1, ',' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_comma);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestLeftParenToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_left_paren, 1, 1, '(' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_left_paren);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestRightParenToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_right_paren, 1, 1, ')' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_right_paren);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestExponentToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_exponent, 1, 1, '^' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_exp);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestStarToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_star, 1, 1, '*' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_star);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestSlashToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_slash, 1, 1, '/' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_slash);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestModuloToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_modulo, 1, 1, '%' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_modulo);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestEqualToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_equal, 1, 1, '=' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestMinusToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_minus, 1, 1, '-' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_minus);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestBangToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_bang, 1, 1, '!' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_bang);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}


TEST_F(ScannerTest8, TestPlusToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_plus, 1, 1, '+' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_plus);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestLessThanToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_less_than, 1, 1, '<' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_less);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest8, TestGreaterThanToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_greater_than, 1, 1, '>' },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_greater);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
