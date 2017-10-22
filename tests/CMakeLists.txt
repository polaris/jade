project (tests)

set(SOURCES
    main.cpp
    list.cpp
    array.cpp
    vector.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_generalized_initializers
        cxx_constexpr
        cxx_relaxed_constexpr
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -ggdb3
    -O0
    -fno-omit-frame-pointer
    -fno-common
    -fstrict-aliasing
    -Werror
    -Wall
    -Wextra
    -pedantic
    -Wcast-align
    -Wcast-qual
    -Wctor-dtor-privacy
    -Wdisabled-optimization
    -Wformat=2
    -Winit-self
    -Wmissing-include-dirs
    -Wmissing-prototypes
    -Wno-missing-braces
    -Wno-missing-field-initializers
    -Wstrict-prototypes
    -Wold-style-cast
    -Wold-style-definition
    -Woverloaded-virtual
    -Wredundant-decls
    -Wshadow
    -Wsign-promo
    -Wpointer-arith
    -Wstrict-overflow=5
    -Wundef
    -Wno-unused
    -Wno-variadic-macros
    -Wno-parentheses
    -fdiagnostics-show-option
    -Wswitch-default
    -Wswitch-enum
    -Wbad-function-cast
    -Winline
    -Wnested-externs
    -Wunreachable-code
    -Wfloat-equal
    -Wstrict-aliasing=2
)
