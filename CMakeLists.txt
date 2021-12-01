project(my_printf)

cmake_minimum_required(VERSION 3.15.0)

add_library(my_printf.a
        print.c print.h
        print_token.c
        conv.c
        parse.c
        spec_read.c
        str.c str.h
)

add_executable(test
        test.c
        print.h
)

link_libraries(test my_printf.a)
