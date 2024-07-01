# minishell/CMakeLists.txt

cmake_minimum_required(VERSION 3.22)
project(minishell)

# Add subdirectories for libraries and source code
add_subdirectory(googletest)
add_subdirectory(libft)
add_subdirectory(srcs)
add_subdirectory(tests/builtins)
