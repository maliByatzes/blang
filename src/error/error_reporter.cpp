#include "blang/error/error_reporter.hpp"
#include <algorithm>
#include <iostream>

namespace blang::error {

void ErrorReporter::clear_errors()
{
  m_error_messages.clear();
  m_status = Status::OK;
}

Status ErrorReporter::get_status() const { return m_status; }

void ErrorReporter::print_errors() const
{
  auto print = [](const auto &err) { std::cerr << err << '\n'; };
  std::for_each(m_error_messages.begin(), m_error_messages.end(), print);
}

void ErrorReporter::set_error(std::size_t line, const std::string &message)
{
  m_error_messages.emplace_back("[Line " + std::to_string(line) + "] Error: " + message);
  m_status = Status::ERROR;
}

}// namespace blang::error
