set(sources
    src/scanner.cpp
    src/parser.cpp
    src/error/error_reporter.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/blang/scanner.hpp
    include/blang/parser.hpp
    include/blang/ast.hpp
    include/blang/token_type.hpp
    include/blang/error/error_reporter.hpp
)

set(test_sources
  src/scanner_test/double_character_test.cpp
  src/scanner_test/identifier_test.cpp
  src/scanner_test/longer_source_test.cpp
  src/scanner_test/single_char_test.cpp
  src/scanner_test/string_literal_test.cpp
  src/scanner_test/keywords_test.cpp
  src/scanner_test/char_lit_test.cpp
  src/scanner_test/comments_test.cpp
  src/scanner_test/integer_lit_test.cpp
  src/scanner_test/error_reporter_test.cpp
)
