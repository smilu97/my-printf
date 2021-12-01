/**
 * @file conv.c
 * @author smilu97
 * @createdAt 2021-12-02
 */

#include "print.h"

t_string conv_ulong(unsigned long data, const char *base)
{
    t_string ret;
    unsigned long bs;

    if (!init_string(&ret, 20))
        return (ret);
    bs = my_strlen(base);
    while (data || ret.len == 0)
    {
        if (!append_char(&ret, base[data % bs]))
        {
            destroy_string(&ret);
            return (ret);
        }
        data /= bs;
    }
    reverse_string(&ret);
    return (ret);
}
