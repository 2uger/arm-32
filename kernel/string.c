// since it already define in compiler
void * mmemmove(void * dst, const void * src, uint32_t size) {
    const char * s;
    char * d;
    int n;
    s = src;
    d = dst;
    n = size;
    
    if (s < d && s + n > d) {
        // at some point we will erase dest memory that
        // we already write into => start from end
        s += n;
        d += n;
        while (n > 0) {
            *--d = *--s;
            n--;
        }
    } else {
        while (n > 0) {
            *d++ = *s++;
            n--;
        }
    }
}