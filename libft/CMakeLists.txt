
cmake_minimum_required(VERSION 3.22)
project(libft)

# Globbing to collect all .c files in the src directory
file(GLOB SOURCE_FILES "*.c")

# Create the executable
add_library(my_library STATIC ${SOURCE_FILES})
