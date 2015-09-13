/*
 * mmap_test.c
 *   Use mmap to map some virtual memory at a requested address.
 */
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

extern _end;
extern data_start;
extern _edata;
extern _etext;
extern _start;

/* Each request to mmap will ask for BLOCK_SIZE memory */
#define BLOCK_SIZE 0x10000

main()
{
  char *address,*p;
  void *memblock;
  char i;

  printf("Break:\n");
  printf(" sbrk(0)= 0x%lx\n", sbrk(0));
  printf("\n");

  printf("Text region:\n");
  printf("&_start = 0x%lx\n", &_start);
  printf("&_etext = 0x%lx\n", &_etext);
  printf("\n");

  printf("Data region:\n");
  printf("&data_start = 0x%lx\n", &data_start);
  printf("&_end   = 0x%lx\n", &_end);
  printf("\n");

  while (1) {
    printf("Enter location of block to map (in hex): ");
    scanf("%lx", &address);
    
    printf("Map at %lx (ending at %lx)\n",address,address+BLOCK_SIZE-1);
    address = mmap(address,BLOCK_SIZE,PROT_READ|PROT_WRITE|PROT_EXEC,
			MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    if (address == (void *)-1) {
      /* failed */
      printf("RW allocation failed: ");
      perror("mmap");
    } else {
      printf("mmap returned %lx\n",address);
    }
  }
}
