/**
 * @file str.h
 * @author smilu97
 * @createdAt 2021-11-28
 */

#pragma once

typedef struct s_string
{
    char *data;
    size_t len;
    size_t cap;
} t_string;

char *init_string(t_string *s, size_t cap);
t_string destroy_string(t_string *s);
char *append_string(t_string *dst, const char *src, int left);
char *append_char(t_string *dst, char ch);
char *append_chars(t_string *dst, char ch, size_t n);
void reverse_string(t_string *dst);
char *pad_string(t_string *s, size_t len, char pad, int left);
char *shift_right_string(t_string *s, size_t n);
char *reserve_string(t_string *s, size_t sz);
char *my_memcpy(char *dst, const char *src, size_t n);
char *my_memset(char *dst, char ch, size_t n);
size_t my_strlen(const char *s);
