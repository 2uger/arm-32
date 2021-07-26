#define BLOCK_SIZE 32 
#define BLOCKS_NUM 16

void print_disk(void);

void init_disk(void);

int read_disk(int, int, void *);

int write_disk(int, void *, int);
