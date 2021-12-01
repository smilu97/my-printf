/**
 * @file parse.c
 * @author smilu97
 * @createdAt 2021-11-27
 */

#include "print.h"

s_token *parse_fmt(const char *begin)
{
    s_token head;
    s_token *tail;
    s_token *node;
    const char *end;

    head.next = NULL;
    tail = &head;
    end = begin;
    while (*end)
    {
        begin = end;
        while ((*end) && (*end) != '%')
            end++;
        node = build_token(begin, end - begin);
        append_token(&tail, node);
        if (*end)
        {
            node = parse_spec(end);
            end += node->length;
            append_token(&tail, node);
        }
    }
    return (head.next);
}

long parse_long(const char *begin, const char *end)
{
    int sign;
    long v;

    v = 0;
    sign = 1 - ((*begin == '-') << 1);
    begin += (sign < 0);
    while (begin != end)
        v = (v * 10) + (*(begin++) - '0');
    return (v * sign);
}

s_token *parse_spec(const char *s)
{
    s_token *token;
    const char *cur;

    token = build_token(s, 0);
    cur = s + 1;
    read_arg_index(&cur, token);
    read_flags(&cur, token);
    read_width(&cur, token);
    read_precision(&cur, token);
    read_type(&cur, token);
    token->length = cur - s;
}
