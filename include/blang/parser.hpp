#ifndef BLANG_PARSER_HPP
#define BLANG_PARSER_HPP

#include "blang/expr.hpp"
#include "blang/scanner.hpp"
#include "blang/token_type.hpp"
#include <initializer_list>
#include <memory>
#include <vector>

namespace blang {

using sptrExpr = std::shared_ptr<Expr>;

class Parser
{
public:
  explicit Parser(const std::vector<Token> &tokens) : m_tokens{ tokens } {}

private:
  sptrExpr expression();
  sptrExpr equality();
  sptrExpr comparison();
  sptrExpr term();
  sptrExpr factor();
  sptrExpr unary();
  sptrExpr primary();

  bool match(std::initializer_list<TokenType> types);
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token previous();
  void consume(TokenType type, const std::string& message);

  std::vector<Token> m_tokens;
  std::size_t m_current{ 0 };
};

}// namespace blang

#endif
