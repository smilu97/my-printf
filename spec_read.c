/**
 * @file specread.c
 * @author smilu97
 * @createdAt 2021-11-27
 */

#include "print.h"

int read_arg_index(const char **cur, s_token *token)
{
    const char *end;

    end = *cur;
    while (*end >= '0' && *end <= '9')
        end++;
    if (*end != '$')
    {
        token->arg_index = -1;
        return (0);
    }
    token->arg_index = parse_long(*cur, end);
    *cur = end + 1;
    return (1);
}

int read_flags(const char **begin, s_token *token)
{
    const char *cur;
    t_flag flags;

    cur = *begin;
    flags = 0;
    while (1) {
        if (*cur == '-')
            flags |= TOKEN_FLAG_MINUS;
        else if (*cur == '+')
            flags |= TOKEN_FLAG_PLUS;
        else if (*cur == ' ')
            flags |= TOKEN_FLAG_BLANK;
        else if (*cur == '#')
            flags |= TOKEN_FLAG_SHARP;
        else if (*cur == 'O')
            flags |= TOKEN_FLAG_BIG_O;
        else
            break ;
    }
    *begin = cur;
    token->flags = flags;
    return (1);
}

int read_width(const char **cur, s_token *token)
{
    const char *end;

    end = *cur;
    while (*end >= '0' && *end <= '9')
        end++;
    token->width = parse_long(*cur, end);
    *cur = end;
    return (1);
}

int read_precision(const char **cur, s_token *token)
{
    const char *end;

    if (**cur != '.')
        return (0);
    end = *cur + 1;
    while (*end >= '0' && *end <= '9')
        end++;
    token->precision = parse_long(*cur + 1, end);
    *cur = end;
    return (1);
}

int read_type(const char **cur, s_token *token)
{
    static const char * const symbols = "  cspdiuxX";
    t_type i;

    i = TOKEN_TYPE_LOWER_C;
    while (i <= 8)
    {
        if (**cur == symbols[i])
        {
            token->type = i;
            break ;
        }
        i++;
    }
    if (token->type == TOKEN_TYPE_RAW)
        token->type = TOKEN_TYPE_ESCAPE;
    (*cur)++;
    return (1);
}
