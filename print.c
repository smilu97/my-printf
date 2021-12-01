/**
 * @file print.c
 * @author smilu97
 * @createdAt 2021-11-27
 */

#include "print.h"

size_t my_printf(const char *fmt, ...)
{
    va_list ap;
    s_arg_list arg_list;
    s_token *head;
    s_token *cur;
    size_t total;

    total = 0;
    head = parse_fmt(fmt);
    va_start(ap, fmt);
    arg_list = read_args(ap, head);
    va_end(ap);
    if (arg_list.values)
    {
        cur = head;
        while (cur)
        {
            total += print_token(cur, &arg_list);
            cur = cur->next;
        }
        free(arg_list.values);
    }
    destroy_token_list(head);
    return (total);
}

size_t print_token(s_token *token, s_arg_list *arg_list)
{
    if (token->type == TOKEN_TYPE_RAW)
        print_token_raw(token, arg_list);
    else if (token->type == TOKEN_TYPE_ESCAPE)
        print_token_escape(token, arg_list);
    else if (token->type == TOKEN_TYPE_LOWER_C)
        print_token_lower_c(token, arg_list);
    else if (token->type == TOKEN_TYPE_LOWER_S)
        print_token_lower_s(token, arg_list);
    else if (token->type == TOKEN_TYPE_LOWER_P)
        print_token_lower_p(token, arg_list);
    else if (token->type == TOKEN_TYPE_LOWER_D)
        print_token_lower_d(token, arg_list);
    else if (token->type == TOKEN_TYPE_LOWER_I)
        print_token_lower_i(token, arg_list);
    else if (token->type == TOKEN_TYPE_LOWER_U)
        print_token_lower_u(token, arg_list);
    else if (token->type == TOKEN_TYPE_LOWER_X)
        print_token_lower_x(token, arg_list);
    else if (token->type == TOKEN_TYPE_UPPER_X)
        print_token_upper_x(token, arg_list);
}

s_arg_list read_args(va_list ap, s_token *head)
{
    s_arg_list arg_list;
    size_t count;
    size_t i;
    s_token *cur;

    arg_list.last_read = 0;
    count = 0;
    cur = head;
    while (cur)
    {
        count += TOKEN_TYPE_LOWER_C <= cur->type;
        cur = cur->next;
    }
    arg_list.values = (long*) malloc(sizeof(long) * (count + 1));
    if (!arg_list.values)
        return (arg_list);
    i = 1;
    cur = head;
    while (cur)
    {
        if (TOKEN_TYPE_LOWER_C <= cur->type)
            arg_list.values[i++] = read_arg(ap, cur->type);
        cur = cur->next;
    }
    return (arg_list);
}

long get_arg(s_arg_list *arg_list, ssize_t arg_index)
{
    if (arg_index == -1)
        return (arg_list->values[++arg_list->last_read]);
    return arg_list->values[arg_index];
}

long read_arg(va_list ap, t_type type)
{
    if (type == TOKEN_TYPE_LOWER_C)
        return (long) va_arg(ap, int);
    if (type == TOKEN_TYPE_LOWER_S)
        return (long) va_arg(ap, char*);
    if (type == TOKEN_TYPE_LOWER_P)
        return (long) va_arg(ap, void*);
    if (type == TOKEN_TYPE_LOWER_D)
        return (long) va_arg(ap, int);
    if (type == TOKEN_TYPE_LOWER_I)
        return (long) va_arg(ap, int);
    if (type == TOKEN_TYPE_LOWER_U)
        return (long) va_arg(ap, unsigned int);
    if (type == TOKEN_TYPE_LOWER_X)
        return (long) va_arg(ap, unsigned int);
    if (type == TOKEN_TYPE_UPPER_X)
        return (long) va_arg(ap, unsigned int);
    return va_arg(ap, long);
}

void destroy_token_list(s_token *head)
{
    s_token *next;

    while (head)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

s_token *build_token(const char *begin, size_t length)
{
    s_token *node;

    node = (s_token*) malloc(sizeof(s_token));
    node->begin = begin;
    node->type = TOKEN_TYPE_RAW;
    node->next = NULL;
    node->length = length;
    return (node);
}

void append_token(s_token **p_tail, s_token *rep)
{
    (*p_tail)->next = rep;
    (*p_tail) = rep;
}
