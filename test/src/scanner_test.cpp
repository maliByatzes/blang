#include "blang/error/error_reporter.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

// Tests

namespace blang {

class ScannerTest : public testing::Test
{
protected:
  error::ErrorReporter reporter;
  // Single-character tokens
  Scanner sc1{ ":", reporter };
  Scanner sc2{ ";", reporter };
  Scanner sc3{ "[", reporter };
  Scanner sc4{ "]", reporter };
  Scanner sc5{ "{", reporter };
  Scanner sc6{ "}", reporter };
  Scanner sc7{ ",", reporter };
  Scanner sc8{ "(", reporter };
  Scanner sc9{ ")", reporter };
  Scanner sc10{ "^", reporter };
  Scanner sc11{ "*", reporter };
  Scanner sc12{ "/", reporter };
  Scanner sc13{ "%", reporter };
  Scanner sc14{ "=", reporter };
  Scanner sc15{ "-", reporter };
  Scanner sc16{ "!", reporter };
  Scanner sc17{ "+", reporter };
  Scanner sc18{ "<", reporter };
  Scanner sc19{ ">", reporter };
  // Double-character tokens
  Scanner sc20{ "==", reporter };
  Scanner sc21{ "--", reporter };
  Scanner sc22{ "!=", reporter };
  Scanner sc23{ "<=", reporter };
  Scanner sc24{ ">=", reporter };
  Scanner sc25{ "&&", reporter };
  Scanner sc26{ "||", reporter };
  // Identifer tokens
  Scanner sc27{ "i", reporter };
  Scanner sc28{ "mystr", reporter };
  Scanner sc29{ "fog123", reporter };
  Scanner sc30{ "BigLongName55", reporter };
};

void run_scanner_test(const std::vector<Token> &expected_tokens, Scanner &scanner)
{
  std::vector<Token> actual_tokens{ scanner.scan_tokens() };
  ASSERT_EQ(actual_tokens.size(), expected_tokens.size());
  auto compare = [](const Token &tk1, const Token &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };
  ASSERT_TRUE(std::equal(actual_tokens.begin(), actual_tokens.end(), expected_tokens.begin(), compare));
}

TEST_F(ScannerTest, TestColonToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_colon, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc1);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestSemicolonToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_semicolon, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc2);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestLeftSquareToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_left_square, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc3);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestRightSquareToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_right_square, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc4);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestLeftBraceToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_left_brace, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc5);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestRightBraceToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_right_brace, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc6);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestCommaToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_comma, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc7);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestLeftParenToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_left_paren, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc8);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestRightParenToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_right_paren, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc9);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestExponentToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_exponent, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc10);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestStarToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_star, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc11);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestSlashToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_slash, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc12);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestModuloToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_modulo, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc13);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

/*
TEST_F(ScannerTest, TestEqualToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_equal, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc14);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestMinusToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_minus, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc15);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestBangToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_bang, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc16);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}


TEST_F(ScannerTest, TestPlusToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_plus, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc17);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestLessThanToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_less_than, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc18);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestGreaterThanToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_greater_than, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc19);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}
*/

TEST_F(ScannerTest, TestEqualEqualToken)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_equal_equal, 2, 1 },
    Token{ TokenType::t_eof, 3, 1 },
  };
  run_scanner_test(expected_tokens, sc20);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestIdentifierToken) {
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, 1, 1},
    Token{ TokenType::t_eof, 2, 1 },
  };
  run_scanner_test(expected_tokens, sc21);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
