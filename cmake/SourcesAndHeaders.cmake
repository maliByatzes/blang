set(sources
    src/scanner.cpp
    src/error/error_reporter.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/blang/scanner.hpp
    include/blang/token_type.hpp
    include/blang/error/error_reporter.hpp
)

set(test_sources
  src/scanner_test.cpp
)
