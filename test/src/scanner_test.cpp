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
};

TEST_F(ScannerTest, TestColonToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_colon, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc1.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestSemicolonToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_semicolon, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc2.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestLeftSquareToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_left_square, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc3.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestRightSquareToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_right_square, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc4.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestLeftBraceToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_left_brace, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc5.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestRightBraceToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_right_brace, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc6.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestCommaToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_comma, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc7.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestLeftParenToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_left_paren, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc8.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestRightParenToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_right_paren, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc9.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestExponentToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_exponent, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc10.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestStarToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_star, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc11.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestSlashToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_slash, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc12.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestModuloToken)
{
  std::vector<Token> exp_sc_tks{
    Token{ TokenType::t_modulo, 1, 1 },
    Token{ TokenType::t_eof, 2, 1 },
  };
  std::vector<Token> sc_tks{ sc13.scan_tokens() };

  ASSERT_EQ(sc_tks.size(), exp_sc_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq = std::equal(sc_tks.begin(), sc_tks.end(), exp_sc_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

/*
TEST_F(ScannerTest, TestPlusPlusToken)
{
  std::vector<Token> exp_sc2_tks{
    Token{ TokenType::t_plus_plus, 2, 1 },
    Token{ TokenType::t_eof, 3, 1 },
  };
  std::vector<Token> sc2_tks{ sc2.scan_tokens() };

  ASSERT_EQ(sc2_tks.size(), exp_sc2_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq{ std::equal(sc2_tks.begin(), sc2_tks.end(), exp_sc2_tks.begin(), compare) };
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestEqualEqualToken)
{
  std::vector<Token> exp_sc3_tks{
    Token{ TokenType::t_equal_equal, 2, 1 },
    Token{ TokenType::t_eof, 3, 1 },
  };
  std::vector<Token> sc3_tks{ sc3.scan_tokens() };

  ASSERT_EQ(sc3_tks.size(), exp_sc3_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position && tk1.line == tk2.line;
  };

  bool are_eq{ std::equal(sc3_tks.begin(), sc3_tks.end(), exp_sc3_tks.begin(), compare) };
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
} */

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
