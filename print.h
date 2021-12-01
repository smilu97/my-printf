/**
 * @file print.h
 * @author smilu97
 * @createdAt 2021-11-27
 */

#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#define TOKEN_FLAG_MINUS (0x01)
#define TOKEN_FLAG_PLUS  (0x02)
#define TOKEN_FLAG_BLANK (0x04)
#define TOKEN_FLAG_SHARP (0x08)
#define TOKEN_FLAG_BIG_O (0x10)

#define TOKEN_TYPE_RAW     0
#define TOKEN_TYPE_ESCAPE  1
#define TOKEN_TYPE_LOWER_C 2
#define TOKEN_TYPE_LOWER_S 3
#define TOKEN_TYPE_LOWER_P 4
#define TOKEN_TYPE_LOWER_D 5
#define TOKEN_TYPE_LOWER_I 6
#define TOKEN_TYPE_LOWER_U 7
#define TOKEN_TYPE_LOWER_X 8
#define TOKEN_TYPE_UPPER_X 9

#include "str.h"

typedef uint32_t t_flag;
typedef uint32_t t_type;

typedef struct t_token
{
    const char *begin;
    ssize_t arg_index;
    t_flag flags;
    ssize_t width;
    ssize_t precision;
    t_type type;
    size_t length;
    struct t_token *next;
} s_token;

typedef struct t_arg_list
{
    long *values;
    size_t last_read;
} s_arg_list;

size_t my_printf(const char *fmt, ...);
size_t print_token(s_token *token, s_arg_list *arg_list);

s_token *build_token(const char *begin, size_t length);
void destroy_token_list(s_token *head);
void append_token(s_token **p_tail, s_token *rep);

t_string conv_ulong(unsigned long data, const char *base);

long read_arg(va_list ap, t_type type);
long get_arg(s_arg_list *arg_list, ssize_t arg_index);
s_arg_list read_args(va_list ap, s_token *head);

long parse_long(const char *begin, const char *end);
s_token *parse_fmt(const char *fmt);
s_token *parse_spec(const char *s);

int read_arg_index(const char **begin, s_token *token);
int read_flags(const char **begin, s_token *token);
int read_width(const char **begin, s_token *token);
int read_precision(const char **begin, s_token *token);
int read_type(const char **begin, s_token *token);

void print_token_raw(s_token *token, s_arg_list *arg_list);
void print_token_escape(s_token *token, s_arg_list *arg_list);
void print_token_lower_c(s_token *token, s_arg_list *arg_list);
void print_token_lower_s(s_token *token, s_arg_list *arg_list);
void print_token_lower_p(s_token *token, s_arg_list *arg_list);
void print_token_lower_d(s_token *token, s_arg_list *arg_list);
void print_token_lower_i(s_token *token, s_arg_list *arg_list);
void print_token_lower_u(s_token *token, s_arg_list *arg_list);
void print_token_lower_x(s_token *token, s_arg_list *arg_list);
void print_token_upper_x(s_token *token, s_arg_list *arg_list);
