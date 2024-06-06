#ifndef BLANG_PARSER_HPP
#define BLANG_PARSER_HPP

#include "blang/scanner.hpp"
#include <vector>

namespace blang {

class Parser
{
public:
  explicit Parser(const std::vector<Token> &tokens) : m_tokens{ tokens } {}

private:
  std::vector<Token> m_tokens;
  std::size_t m_current{ 0 };
};

}// namespace blang

#endif
