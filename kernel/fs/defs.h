void clean_block(struct block *);
void print_disk(void);
void init_disk(void);
int read_disk(int, int, void *);
int write_disk(int, void *, int);

void binit(void);
void print_buffer_addrs(void);
void test_buffer(void);
struct CacheBuffer *bget(int, int);
