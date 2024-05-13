#ifndef BLANG_SCANNER_HPP
#define BLANG_SCANNER_HPP

#include "blang/error/error_reporter.hpp"
#include "blang/token_type.hpp"
#include <cstddef>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace blang {

using value_object = std::variant<int, std::string, char>;

constexpr int TOKEN_ALIGNMENT = 64;
constexpr int NOT_IDENTIFIED_EXIT = 64;

// Token type struct to encapsulate all the attributes
struct alignas(TOKEN_ALIGNMENT) Token
{
  TokenType type;
  std::size_t position;
  int line;
  value_object value;
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
  void add_token(TokenType type, const value_object &value);
  char consume();
  [[nodiscard]] std::optional<char> peek_next() const;
  void consume_next(char next,
    TokenType dbl,
    const value_object &val_dbl,
    TokenType single,
    const value_object &val_single);
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
