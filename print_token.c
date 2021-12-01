/**
 * @file print_token.c
 * @author smilu97
 * @createdAt 2021-11-28
 */

#include "print.h"
#include "str.h"

void print_token_raw(s_token *token, s_arg_list *arg_list)
{
    write(1, token->begin, token->length);
}

void print_token_escape(s_token *token, s_arg_list *arg_list)
{
    write(1, token->begin + 1, 1);
}

void print_token_lower_c(s_token *token, s_arg_list *arg_list)
{
    char data;

    data = (char) get_arg(arg_list, token->arg_index);
    write(1, &data, sizeof(char));
}

void print_token_lower_s(s_token *token, s_arg_list *arg_list)
{
    const char *data;

    data = (const char*) get_arg(arg_list, token->arg_index);
    write(1, data, my_strlen(data));
}

void print_token_lower_p(s_token *token, s_arg_list *arg_list)
{
    unsigned long data;

    data = (unsigned long) get_arg(arg_list, token->arg_index);

}

void print_token_lower_d(s_token *token, s_arg_list *arg_list)
{

}

void print_token_lower_i(s_token *token, s_arg_list *arg_list)
{

}

void print_token_lower_u(s_token *token, s_arg_list *arg_list)
{

}

void print_token_lower_x(s_token *token, s_arg_list *arg_list)
{

}

void print_token_upper_x(s_token *token, s_arg_list *arg_list)
{

}
