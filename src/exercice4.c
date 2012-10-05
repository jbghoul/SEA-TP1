#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;


typedef struct ctx_s {
unsigned int sp;
unsigned int bp;
} ctx_s;


int
main(void)
{
unsigned int x=0, y=0;
asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
  : "=r"(y),"=r"(x) 
  :
  );

printf("main \nbp: %ud \nsp: %ud\n",x,y);



return 0;

}