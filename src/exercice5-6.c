 
#include <setjmp.h>
#include <stdio.h>
#include <assert.h>

/*static jmp_buf buf;*/


typedef struct ctx_s {
unsigned int sp;
unsigned int bp;
} ctx_s;

static ctx_s contexte;




typedef void (func_t)(void*);

int try(struct ctx_s *pctx, func_t *f, void* arg);

int throw(struct ctx_s *pctx, int r);


int trivial(int ret) {
  return ret;
}

void toto (void *i) {
  int n = * ((int *)i);
  throw(&contexte,n);
}

int
main(void)
{
unsigned int x=0, y=0;

int ret;
int * nb;

asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
  : "=r"(y),"=r"(x) 
  :
  );

printf("main \nbp: %ud \nsp: %ud\n",x,y);

try(&contexte,toto,);
printf("f return %d\n", ret);


return 0;
}


int try(struct ctx_s *pctx, func_t *f, void * arg) {
asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
  : "=r"(pctx->sp),"=r"(pctx->bp)
  );

  f(arg);
  return 0;
}

int throw(struct ctx_s *pctx, int r) {

/*
 * Au changement de contexte, on va perdre l'information
 * sur la variable locale r, il faut donc préalablement la stocker.
 * En déclarant un statique, on alloue une place dans le tas, et donc
 * cette zone est indépendante des changements de contextes.
 */
static int ret = 0;
ret = r;
asm ("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
  :
  : "r"(pctx->sp),"r"(pctx->bp)
  : "%esp","%ebp"
  );

/*
 * throw va devoir se faire passer pour un try en rechargement son contexte
 * Or, try est une fonction non terminale car elle appelle une fonction f
 * donc throw doit aussi être une fonction non terminale. C'est pourquoi
 * on appelle une fonction triviale
 * remarque : printf("") et assert(1) ne marchent pas (supprimés par compilo ?)
*/
  trivial(0);

  return ret;
}
