from ctypes import (
    CDLL,
    c_char_p, 
    c_int, 
    POINTER, 
    c_char,
    create_string_buffer,
    Array,
    c_int32,
    c_float,
    Structure
)
import os
import sys
from pathlib import Path
import io
import pytest

# C files need to be compiled to shared library
# loading the shared library object
#lib = CDLL('../libminishell.so')  
lib = CDLL('../libminishell.so')  


#function prototypes
lib.msh_echo.argtypes = [c_int, POINTER(POINTER(c_char))]
lib.msh_echo.restype = c_int  # Important to set return type

#utils functions:
def create_string_array(strings):
    arr = (POINTER(c_char) * (len(strings) + 1))()
    for i, s in enumerate(strings):
        arr[i] = create_string_buffer(s.encode('utf-8'))
    arr[len(strings)] = None
    return arr

def test_example(capsys):
    string = "Hello world from Echo\n"
    strings = ['msh_echo'] + string.split()
    arr = create_string_array(strings)
    ret_val = lib.msh_echo(5, arr)
    c_output  = capsys.readouterr()
    assert ret_val == 0
    assert c_output.out == "Hello world from Echo"




