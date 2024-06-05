#include "blang/scanner.hpp"

namespace blang {

using value_object = std::variant<int, std::string, char>;

template<typename R> class Binary;
template<typename R> class Grouping;
template<typename R> class Literal;
template<typename R> class Unary;

// interface to all Expr's
template<typename R> struct ExprVisitor
{
  virtual R visitBinaryExpr(Binary<R> &expr) const = 0;
  virtual R visitGroupingExpr(Grouping<R> &expr) const = 0;
  virtual R visitLiteralExpr(Literal<R> &expr) const = 0;
  virtual R visitUnaryExpr(Unary<R> &expr) const = 0;
};

// interface to one expr
template<typename R> struct Expr
{
  virtual R accept(const ExprVisitor<R> &visitor) = 0;
};

template<typename R> class Binary : public Expr<R>
{
public:
  Binary(const Expr<R> &left, const Token &_operator, const Expr<R> &right)// NOLINT
    : m_left{ left }, m_operator{ _operator }, m_right{ right }
  {}

  R accept(const ExprVisitor<R> &visitor) override { return visitor.visitBinaryExpr(*this); }

private:
  Expr<R> m_left;
  Token m_operator;
  Expr<R> m_right;
};

template<typename R> class Grouping : public Expr<R>
{
public:
  explicit Grouping(const Expr<R> &expression) : m_expression{ expression } {}

  R accept(const ExprVisitor<R> &visitor) override { return visitor.visitGroupingExpr(*this); }

private:
  Expr<R> m_expression;
};

template<typename R> class Literal : public Expr<R>
{
public:
  explicit Literal(const value_object &value) : m_value{ value } {}// NOLINT

  R accept(const ExprVisitor<R> &visitor) override { return visitor.visitLiteralExpr(*this); }

private:
  value_object m_value;
};

template<typename R> class Unary : public Expr<R>
{
public:
  Unary(const Token &_operator, const Expr<R> &right) : m_operator{ _operator }, m_right{ right } {}// NOLINT

  R accept(const ExprVisitor<R> &visitor) override { return visitor.visitUnaryExpr(*this); }

private:
  Token m_operator;
  Expr<R> m_right;
};

}// namespace blang
