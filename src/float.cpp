#include "inttypes.hpp"

size_t to_float(char * str, float dt, int precision = 6)
{
    char *sptr = str;

    bool neg = false;
    if (dt < 0)
    {
        *sptr++ = '-';
        dt *= -1;
        neg = true;
    }

    int len = 0;
    int cast_dt = dt;
    dt -= cast_dt;
    while (cast_dt)
    {
        *sptr++ = '0' + cast_dt % 10;
        len++;
        cast_dt /= 10;
    }
    auto rev_str = [](char* lptr, char* rptr){
        while (lptr < rptr)
        {
            char ax = *lptr;
            *lptr++ = *rptr;
            *rptr-- = ax;
        }
    };
    rev_str(str + neg, sptr - 1);

    if (len == 0) *sptr++ = '0';
    *sptr++ = '.';

    dt *= 10;
    len = precision;
    while (dt > 0 && len--)
    {
        char tmp = ((int)dt % 10);
        *sptr++ = tmp + '0';
        dt -= tmp;
        if ((int)(dt * len * 10) == 0) break;
        dt *= 10;
    }
    if (len == 6) *sptr++ = '0';

    return sptr - str;
}