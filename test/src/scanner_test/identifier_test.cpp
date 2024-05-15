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

  Scanner sc_i{ "i", reporter };
  Scanner sc_mystr{ "mystr", reporter };
  Scanner sc_fog123{ "fog123", reporter };
  Scanner sc_BigLongName55{ "BigLongName55", reporter };
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

TEST_F(ScannerTest, TestIdentifierToken1)
{
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, 1, 1, "i" },
    Token{ TokenType::t_eof, 2, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_i);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestIdentifierToken2)
{
  const size_t idef_pos = 5;
  const size_t eof_pos = 6;
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, idef_pos, 1, "mystr" },
    Token{ TokenType::t_eof, eof_pos, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_mystr);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestIdentifierToken3)
{
  const size_t idef_pos = 6;
  const size_t eof_pos = 7;
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, idef_pos, 1, "fog123" },
    Token{ TokenType::t_eof, eof_pos, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_fog123);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

TEST_F(ScannerTest, TestIdentifierToken4)
{
  const size_t idef_pos = 13;
  const size_t eof_pos = 14;
  std::vector<Token> expected_tokens{
    Token{ TokenType::t_identifier, idef_pos, 1, "BigLongName55" },
    Token{ TokenType::t_eof, eof_pos, 1, '\0' },
  };
  run_scanner_test(expected_tokens, sc_BigLongName55);
  ASSERT_EQ(reporter.get_status(), error::Status::OK);
}

}// namespace blang

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
