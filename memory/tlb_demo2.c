/*
 * tlb_demo2.c
 *
 *   Fills a 2D array.
 *   Order of loops stores values out of order of memory address.
 *   Skipping around memory like this causes lots of TLB misses.
 */
#define SIZE 2500

/* data array is about 6000 4K pages */
int data[SIZE][SIZE];

main()
{
  int count = 0,i,j;

  while (count < 100) {
    for (j = 0; j<SIZE; j++)
      for (i = 0; i<SIZE; i++)
	data[i][j] = count;
    count++;
  }
}
