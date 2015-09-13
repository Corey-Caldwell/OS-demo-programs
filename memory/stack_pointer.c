/* print my own stack pointer */
#include <stdio.h>
unsigned long get_sp(void) {
   __asm__("movl %esp,%eax");
}
int main() {
  printf("0x%lx\n", get_sp());
}
