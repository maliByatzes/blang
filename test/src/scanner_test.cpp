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
  Scanner sc1{ ": ;", reporter };
  Scanner sc2{ "++", reporter };
};

TEST_F(ScannerTest, TestSingleToken)
{
  std::vector<Token> exp_sc1_tks{
    Token{ TokenType::t_colon, 1 },
    Token{ TokenType::t_semicolon, 3 },
    Token{ TokenType::t_eof, 4 },
  };
  std::vector<Token> sc1_tks{ sc1.scan_tokens() };

  ASSERT_EQ(sc1_tks.size(), exp_sc1_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) { return tk1.type == tk2.type && tk1.position == tk2.position; };

  bool are_eq = std::equal(sc1_tks.begin(), sc1_tks.end(), exp_sc1_tks.begin(), compare);
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestDoubleToken)
{
  std::vector<Token> exp_sc2_tks{
    Token{ TokenType::t_plus_plus, 2 },
    Token{ TokenType::t_eof, 3 },
  };
  std::vector<Token> sc2_tks{ sc2.scan_tokens() };

  ASSERT_EQ(sc2_tks.size(), exp_sc2_tks.size());

  auto compare{ [](const auto &tk1, const auto &tk2) { return tk1.type == tk2.type && tk1.position == tk2.position; } };

  bool are_eq{ std::equal(sc2_tks.begin(), sc2_tks.end(), exp_sc2_tks.begin(), compare) };
  ASSERT_TRUE(are_eq);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
