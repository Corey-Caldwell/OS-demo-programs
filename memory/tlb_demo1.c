/*
 * tlb_demo1.c
 *
 *   Fills a 2D array.
 *   Order of loops stores values in order of memory address.
 *
 */
#define SIZE 2500

/* data array is about 6000 4K pages */
int data[SIZE][SIZE];

main()
{
  int count = 0,i,j;

  while (count < 100) {
    for (i = 0; i<SIZE; i++)
      for (j = 0; j<SIZE; j++)
	data[i][j] = count;
    count++;
  }
}
