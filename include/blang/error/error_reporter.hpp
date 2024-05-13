#ifndef BLANG_ERROR_REPORTER_HPP
#define BLANG_ERROR_REPORTER_HPP

#include <cstddef>
#include <string>
#include <vector>
namespace blang::error {

enum class Status { OK, ERROR };

class ErrorReporter
{
public:
  ErrorReporter() = default;

  void clear_errors();
  [[nodiscard]] Status get_status() const;
  void print_errors() const;
  void set_error(std::size_t line, const std::string &message);

private:
  std::vector<std::string> m_error_messages;
  Status m_status{ Status::OK };
};

}// namespace blang::error

#endif
