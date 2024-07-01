cmake_minimum_required(VERSION 3.22)
project(gtest_env)

# Create the executable and specify the source files


add_executable(gtest_env
    ${PROJECT_SOURCE_DIR}/../../srcs/msh_env_list.c
    ${PROJECT_SOURCE_DIR}/../../srcs/builtins/msh_export.c
    gtest_env.cpp
)

# Include directories for Google Test and libft
target_include_directories(gtest_env PRIVATE
    ${PROJECT_SOURCE_DIR}/../../libft/build
)

# Specify the path to the libft.a file
set(LIBFT_LIBRARY ${CMAKE_SOURCE_DIR}/../../libft/libft.a)

# Linking libraries
target_link_libraries(gtest_env
    gtest
	gtest_main
    ${LIBFT_LIBRARY}
)
