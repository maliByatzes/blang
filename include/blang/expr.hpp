#ifndef BLANG_EXPR_HPP
#define BLANG_EXPR_HPP

#include "blang/scanner.hpp"
#include <memory>

namespace blang {

using value_object = std::variant<int, std::string, char>;

class Expr // NOLINT
{
public:
  virtual ~Expr() = default;

  class VisitorBase //NOLINT
  {
  public:
    virtual ~VisitorBase() = default;

    virtual void visitBinaryExpr(const Expr *expr) = 0;
    virtual void visitGroupingExpr(const Expr *expr) = 0;
    virtual void visitLiteralExpr(const Expr *expr) = 0;
    virtual void visitUnaryExpr(const Expr *expr) = 0;
  };

  template<typename R> class Visitor : public VisitorBase
  {
  public:
    //NOLINTBEGIN
    virtual R visitBinaryExpr(const Expr *expr) = 0;
    virtual R visitGroupingExpr(const Expr *expr) = 0;
    virtual R visitLiteralExpr(const Expr *expr) = 0;
    virtual R visitUnaryExpr(const Expr *expr) = 0;
    //NOLINTEND
  };

  virtual void accept(VisitorBase &visitor) const = 0;

  template<typename R> R accept(Visitor<R> &visitor) const
  {
    accept(static_cast<VisitorBase &>(visitor));
    return visitor.result;
  }
};

class Binary : public Expr
{
public:
  Binary(std::shared_ptr<Expr> left, std::shared_ptr<Token> _operator, std::shared_ptr<Expr> right)
    : m_left{ std::move(left) }, m_operator{ std::move(_operator) }, m_right{ std::move(right) }
  {}

  void accept(VisitorBase &visitor) const override { visitor.visitBinaryExpr(this); }

private:
  std::shared_ptr<Expr> m_left;
  std::shared_ptr<Token> m_operator;
  std::shared_ptr<Expr> m_right;
};

class Grouping : public Expr
{
public:
  explicit Grouping(std::shared_ptr<Expr> expression) : m_expression{ std::move(expression) } {}

  void accept(VisitorBase &visitor) const override { visitor.visitGroupingExpr(this); }

private:
  std::shared_ptr<Expr> m_expression;
};

class Literal : public Expr
{
public:
  explicit Literal(std::shared_ptr<value_object> value) : m_value{ std::move(value) } {}

  void accept(VisitorBase &visitor) const override { visitor.visitLiteralExpr(this); }

private:
  std::shared_ptr<value_object> m_value;
};

class Unary : public Expr
{
public:
  Unary(std::shared_ptr<Token> _operator, std::shared_ptr<Expr> right)
    : m_operator{ std::move(_operator) }, m_right{ std::move(right) }
  {}

  void accept(VisitorBase &visitor) const override { visitor.visitUnaryExpr(this); }

private:
  std::shared_ptr<Token> m_operator;
  std::shared_ptr<Expr> m_right;
};

}// namespace blang

#endif
