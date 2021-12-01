/**
 * @file str.c
 * @author smilu97
 * @createdAt 2021-11-28
 */

#include <malloc.h>
#include "str.h"

char *init_string(t_string *s, size_t cap)
{
    s->data = (char*) malloc(sizeof(char) * cap);
    if (s->data == NULL)
        return (NULL);
    s->len = 0;
    s->cap = cap;
    return (s->data);
}

t_string destroy_string(t_string *s)
{
    free(s->data);
    s->data = NULL;
    s->cap = 0;
    s->len = 0;
    return (*s);
}

char *append_string(t_string *dst, const char *src, int left)
{
    size_t n;

    n = my_strlen(src);
    if (dst->len + n > dst->cap)
        if (!reserve_string(dst, dst->len + n))
            return (NULL);
    if (left)
        if (!shift_right_string(dst, n))
            return (NULL);
    my_memcpy(dst->data + dst->len * (1 - left), src, n);
    dst->len += n;
    return (dst->data);
}

char *append_char(t_string *dst, char ch)
{
    if (dst->len >= dst->cap)
        if (!reserve_string(dst, dst->len << 1))
            return (NULL);
    dst->data[dst->len++] = ch;
    return (dst->data);
}

char *append_chars(t_string *dst, char ch, size_t n)
{
    if (dst->len + n > dst->cap)
        if (!reserve_string(dst, dst->len + n))
            return (NULL);
    my_memset(dst->data + dst->len, ch, n);
    dst->len += n;
    return (dst->data);
}

char *reserve_string(t_string *s, size_t sz)
{
    size_t rsz;
    char *buf;

    if (sz <= s->cap)
        return (s->data);
    rsz = s->cap;
    while (rsz < sz) rsz <<= 1;
    buf = (char*) malloc(sizeof(char) * rsz);
    if (buf == NULL)
        return (NULL);
    my_memcpy(buf, s->data, s->len);
    free(s->data);
    s->data = buf;
    s->cap = rsz;
    return (buf);
}

char *pad_string(t_string *s, size_t len, char pad, int left)
{
    if (left)
    {
        if (!shift_right_string(s, len))
            return (NULL);
        my_memset(s->data, pad, len);
        return (s->data);
    }
    return append_chars(s, pad, len);
}

char *shift_right_string(t_string *s, size_t n)
{
    char *cur;

    if (s->len == 0)
        return (s->data);
    if (n + s->len > s->cap)
        if (!reserve_string(s, n + s->len))
            return (NULL);
    cur = s->data + (s->len - 1);
    while (cur >= s->data)
    {
        *(cur + n) = *(cur);
        cur--;
    }
    return (s->data);
}

char *my_memcpy(char *dst, const char *src, size_t n)
{
    char *ret;

    ret = dst;
    while (n--)
        *(dst++) = *(src++);
    return (ret);
}

char *my_memset(char *dst, char ch, size_t n)
{
    char *cur;

    cur = dst;
    while (n--)
        *(cur++) = ch;
    return (dst);
}

size_t my_strlen(const char *s)
{
    const char *e;

    e = s;
    while (*e)
        e++;
    return (e - s);
}

void reverse_string(t_string *dst)
{
    char tmp;
    size_t i;
    size_t j;
    size_t e;

    i = 0;
    e = dst->len >> 1;
    while (i < e) {
        j = dst->len - 1 - i;
        tmp = dst->data[i];
        dst->data[i] = dst->data[j];
        dst->data[j] = tmp;
        i++;
    }
}
