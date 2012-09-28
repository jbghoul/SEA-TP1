#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;
static int i = 0;
static int
cpt()
{
  int j = 0;
  if (setjmp(buf)) {
    printf("coucou\n");
    for (j=0; j<5; j++)
    i++;
  } else {
    for (j=0; j<5; j++)
    i--;
  }
}
int
main()
{
  int np = 0 ;
  cpt();
  printf("i *= %d\n", i );
  if (! np++)
  longjmp(buf,~0);
  printf("i = %d\n", i );
}