
cmake_minimum_required(VERSION 3.22)
project(gtest_builtin)

# Create the executable and specify the source files


add_executable(gtest_builtin
    ${PROJECT_SOURCE_DIR}/../../srcs/builtins/msh_echo.c
    ${PROJECT_SOURCE_DIR}/../../srcs/builtins/msh_pwd.c
    ${PROJECT_SOURCE_DIR}/../../srcs/builtins/msh_cd.c
    gtest_builtins.cpp
)

# Include directories for Google Test and libft
target_include_directories(gtest_builtin PRIVATE
    ${PROJECT_SOURCE_DIR}/../../libft/build
)

# Specify the path to the libft.a file
set(LIBFT_LIBRARY ${CMAKE_SOURCE_DIR}/../../libft/libft.a)

# Linking libraries
target_link_libraries(gtest_builtin
    gtest
	gtest_main
    ${LIBFT_LIBRARY}
)
