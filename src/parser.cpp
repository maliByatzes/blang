#include "blang/parser.hpp"
#include "blang/token_type.hpp"
#include <string>

// NOLINTBEGIN
namespace blang {

sptrExpr Parser::expression() { return equality(); }

sptrExpr Parser::equality()
{
  sptrExpr expr = comparison();

  while (match({ TokenType::t_bang_equal, TokenType::t_equal_equal })) {
    Token _operator = previous();
    sptrExpr right = comparison();
    expr = std::make_shared<Binary>(expr, std::make_shared<Token>(_operator), right);
  }

  return expr;
}

sptrExpr Parser::comparison()
{
  sptrExpr expr = term();

  while (
    match({ TokenType::t_greater_than, TokenType::t_greater_equal, TokenType::t_less_than, TokenType::t_less_equal })) {
    Token _operator = previous();
    sptrExpr right = term();
    expr = std::make_shared<Binary>(expr, std::make_shared<Token>(_operator), right);
  }

  return expr;
}

sptrExpr Parser::term()
{
  sptrExpr expr = factor();

  while (match({ TokenType::t_minus, TokenType::t_plus })) {
    Token _operator = previous();
    sptrExpr right = factor();
    expr = std::make_shared<Binary>(expr, std::make_shared<Token>(_operator), right);
  }

  return expr;
}

sptrExpr Parser::factor()
{
  sptrExpr expr = unary();

  while (match({ TokenType::t_slash, TokenType::t_star })) {
    Token _operator = previous();
    sptrExpr right = unary();
    expr = std::make_shared<Binary>(expr, std::make_shared<Token>(_operator), right);
  }

  return expr;
}

sptrExpr Parser::unary()
{
  if (match({ TokenType::t_bang, TokenType::t_minus })) {
    Token _operator = previous();
    sptrExpr right = unary();
    return std::make_shared<Unary>(std::make_shared<Token>(_operator), right);
  }

  return primary();
}

sptrExpr Parser::primary()
{
  if (match({ TokenType::t_false })) { return std::make_shared<Literal>(false); }

  if (match({ TokenType::t_true })) { return std::make_shared<Literal>(true); }

  if (match({ TokenType::t_char_lit })) { return std::make_shared<Literal>(std::get<char>(previous().value)); }

  if (match({ TokenType::t_string_lit })) { return std::make_shared<Literal>(std::get<std::string>(previous().value)); }

  if (match({ TokenType::t_integer_lit })) { return std::make_shared<Literal>(std::get<int>(previous().value)); }

  if (match({ TokenType::t_left_paren })) {
    sptrExpr expr = expression();
    consume(TokenType::t_right_paren, "Expect ')' after expression.");
    return std::make_shared<Grouping>(expr);
  }
}

bool Parser::match(std::initializer_list<TokenType> types)
{
  for (auto const &type : types) {
    if (check(type)) {
      advance();
      return true;
    }
  }

  return false;
}

bool Parser::check(TokenType type)
{
  if (isAtEnd()) { return false; }
  return peek().type == type;
}

Token Parser::advance()
{
  if (!isAtEnd()) { m_current++; }
  return previous();
}

bool Parser::isAtEnd() { return peek().type == TokenType::t_eof; }

Token Parser::peek() { return m_tokens.at(m_current); }

Token Parser::previous() { return m_tokens.at(m_current - 1); }

}// namespace blang
// NOLINTEND
