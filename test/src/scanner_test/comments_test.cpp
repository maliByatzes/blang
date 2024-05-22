#include "blang/error/error_reporter.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

// Tests

namespace blang {

class ScannerTest2 : public testing::Test
{
protected:
  error::ErrorReporter reporter;

  // Test string literal processing
  // Scanner sc_comment_1{ "/* A C-style comment*/", reporter };
  Scanner sc_comment_2{ "// A C++ comment\n", reporter };
  // Scanner sc_comments{ "/* A C-style comment */\na=5; // A C++ style comment\n", reporter };
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

TEST_F(ScannerTest2, TestComment2)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_eof, 18, 2, '\0' }// NOLINT
  };
  run_scanner_test(expected_tokens, sc_comment_2);
  ASSERT_EQ(sc_comment_2.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
