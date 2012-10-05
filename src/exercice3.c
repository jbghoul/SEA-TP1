#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;

static int
mul(int depth)
{
  int i;
  if(depth==0) {
    if(setjmp(buf)) {
    return 0;
    }
  }
  switch (scanf("%d", &i)) {
  case EOF :
    return 1; /* neutral element */
  case 0 :
   return mul(depth+1);
/* erroneous read */
  case 1 :
    if (i)
      return i * mul(depth+1);
    else
    /*return 0;*/
    longjmp(buf,1);
  }
}
int
main()
{
  int product;
  printf("A list of int, please\n");
  product = mul(0);
  printf("product = %d\n", product);
}
