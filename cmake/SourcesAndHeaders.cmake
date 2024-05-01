set(sources
    src/tmp.cpp
    src/scanner.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/blang/tmp.hpp
    include/blang/scanner.hpp
    include/blang/token_type.hpp
)

set(test_sources
  src/scanner_test.cpp
)
