#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;


int toto(int);
int banane(int);

int banane(int fin) {
unsigned int x=0, y=0;
asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
  : "=r"(y),"=r"(x) 
  :
  );

printf("banane \nbp: %ud \nsp: %ud\n",x,y);
  if(fin) {
  return 0;
  }
  else {
  return toto(1);
  }
}


int toto(int fin) {
unsigned int x=0, y=0;
unsigned int* p = &x;

asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
  : "=r"(y),"=r"(x) 
  :
  );

printf("toto \nbp: %ud \nsp: %ud\n",x,y);

printf("x : %ud\n", &p);
  if(fin) {
  return 0;
  }
  else
  {
  return banane(0);
}
}


int
main(void)
{
unsigned int x=0, y=0;
asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
  : "=r"(y),"=r"(x) 
  :
  );

printf("main \nbp: %ud \nsp: %ud\n",x,y);

toto(0);

asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
  : "=r"(y),"=r"(x) 
  :
  );

printf("main \nbp: %ud \nsp: %ud\n",x,y);

return 0;

}
