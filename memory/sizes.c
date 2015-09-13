/*
 * sizes.c
 *   Find sizes (in bytes) of different built-in types.
 */
#include <stdio.h>

#define PRINT_SIZE(type) printf("sizeof(%s)\t%ld\n",#type,sizeof(type))

struct int_char {
  int i;
  char c;
};

struct int_int_char {
  int i1;
  int i2;
  char c;
};

struct ptr_char {
  void *p;
  char c;
};

main()
{
  PRINT_SIZE(char);
  PRINT_SIZE(int);
  PRINT_SIZE(long);
  PRINT_SIZE(long long);
  PRINT_SIZE(short);
  PRINT_SIZE(float);
  PRINT_SIZE(double);
  PRINT_SIZE(long double);
  PRINT_SIZE(void *);
  PRINT_SIZE(size_t);
  PRINT_SIZE(struct int_char);
  PRINT_SIZE(struct ptr_char);
  PRINT_SIZE(struct int_int_char);
}

