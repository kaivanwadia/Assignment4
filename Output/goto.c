#include <stdio.h>
void gototest() {
  int r = 0, x = 1;
l1:
  r++;
l2:
  if(r % 2 != 0) {
    r *= 2;
    goto l1;
  }
  if(r < 100) {
    x += 3;
    goto l2;
  }
  printf("%d\n", r);
}

int main()
{
  gototest();
  return 0;
}