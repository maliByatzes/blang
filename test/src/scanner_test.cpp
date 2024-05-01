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
  Scanner sc1{ ":" };
  Scanner sc2{ ";" };
};

TEST_F(ScannerTest, TestColonToken)
{
  std::vector<Token> exp_sc1_tks{ Token{ TokenType::t_colon, 1 } };
  std::vector<Token> sc1_tks{ sc1.scan_tokens() };

  ASSERT_EQ(sc1_tks.size(), exp_sc1_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) { return tk1.type == tk2.type && tk1.position == tk2.position; };

  bool are_eq = std::equal(sc1_tks.begin(), sc1_tks.end(), exp_sc1_tks.begin(), compare);
  EXPECT_TRUE(are_eq);
}

TEST_F(ScannerTest, TestSemiColonToken)
{
  std::vector<Token> exp_sc2_tks{ Token{ TokenType::t_semicolon, 1 } };
  std::vector<Token> sc2_tks{ sc2.scan_tokens() };

  ASSERT_EQ(sc2_tks.size(), exp_sc2_tks.size());

  auto compare = [](auto const &tk1, auto const &tk2) { return tk1.type == tk2.type && tk1.position == tk2.position; };

  bool are_eq = std::equal(sc2_tks.begin(), sc2_tks.end(), exp_sc2_tks.begin(), compare);
  EXPECT_TRUE(are_eq);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
