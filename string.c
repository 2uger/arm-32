#include "stdint.h"

// since it already define in compiler
void
mmemset(void *dst, char value, uint32_t size)
{
    char *c = dst;
    for (int i = 0; i < size; i++) {
        c[i] = value;
    }
}

void
mmemmove(void *dst, const void *src, uint32_t size)
{
    const char *s;
    char *d;
    int n;
    s = src;
    d = dst;
    n = size;
    
    if (s < d && s + n > d) {
        // at some point we will erase dest memory that
        // we already write into => start from end
        s += n;
        d += n;
        while (n) {
            *d = *s;
            d--;
            s--;
            n--;
        }
    } else {
        while (n) {
            *d = *s;
            d++;
            s++;
            n--;
        }
    }
}

char*
sstrcpy(const char *s, char *dst, uint32_t size)
{
    char *os;
    os = s;
    if (size <= 0)
        return os;
    while (size) {
        *dst = *s;
        s++, dst++, size--;
    }
    return os;
}

int
strncmp(const char *p, const char *q, int n)
{
  while(n > 0 && *p && *p == *q)
      n--, p++, q++;
  if(n == 0)
      return 0;
  return (char)*p - (char)*q;
}