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
  // blang::Scanner sc2{ ";" };
  // blang::Scanner sc3{ ": ;" };
};

TEST_F(ScannerTest, TestSingleTokens)
{
  std::vector<Token> exp_sc1_tks{ Token{ TokenType::t_colon, 0 } };
  std::vector<Token> sc1_tks{ sc1.scan_tokens() };

  ASSERT_EQ(sc1_tks.size(), exp_sc1_tks.size());

  bool are_eq = std::equal(sc1_tks.begin(), sc1_tks.end(), exp_sc1_tks.begin(), [](auto const &tk1, auto const &tk2) {
    return tk1.type == tk2.type && tk1.position == tk2.position;
  });
  EXPECT_TRUE(are_eq);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
