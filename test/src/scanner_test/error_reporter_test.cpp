#include "blang/error/error_reporter.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

// Tests

namespace blang {

class ScannerTest4 : public testing::Test
{
protected:
  error::ErrorReporter reporter;

  // Test string literal processing
  Scanner sc_err{ "x: integer?\ny$ char&", reporter };
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

TEST_F(ScannerTest4, TestErr)
{
  // NOLINTBEGIN
  std::vector<Token> expected_tokens {
    Token{TokenType::t_identifier, 1, 1, "x"},
    Token{TokenType::t_colon, 2, 1, ':'},
    Token{TokenType::t_integer, 10, 1, "integer"},
    Token{TokenType::t_identifier, 13, 2, "y"},
    Token{TokenType::t_char, 19, 2, "char"},
    Token{TokenType::t_eof, 21, 2, '\0'},
  };
  //NOLINTEND
  run_scanner_test(expected_tokens, sc_err);

  ASSERT_EQ(sc_err.get_status() ,error::Status::ERROR);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
