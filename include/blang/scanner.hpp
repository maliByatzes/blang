#ifndef BLANG_SCANNER_HPP
#define BLANG_SCANNER_HPP

#include "blang/error/error_reporter.hpp"
#include "blang/token_type.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace blang {

constexpr int TOKEN_ALIGNMENT = 16;
constexpr int NOT_IDENTIFIED_EXIT = 64;

// Token type struct to encapsulate all the attributes
struct alignas(TOKEN_ALIGNMENT) Token
{
  TokenType type;
  std::size_t position;
  int line;
};

// Scanner class which produces a vector of tokens one by one from a source
// file or source input.
class Scanner
{
public:
  Scanner() = default;
  Scanner(std::string source, error::ErrorReporter reporter)
    : m_source(std::move(source)), m_reporter(std::move(reporter))
  {}

  std::vector<Token> scan_tokens();

private:
  void add_token(TokenType type);
  char consume();
  [[nodiscard]] char peek_next() const;
  void consume_next(char next, TokenType dbl, TokenType single);
  [[nodiscard]] static bool valid_identifier_start_char(char chh);
  [[nodiscard]] static bool valid_identifier_char(char chh);

  std::string m_source;
  std::size_t m_position{ 0 };
  int m_line{ 1 };
  std::vector<Token> m_tokens;
  error::ErrorReporter m_reporter;
};

}// namespace blang

#endif
