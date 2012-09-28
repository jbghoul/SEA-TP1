#include <setjmp.h>
#include <stdio.h>
int i = 0;
jmp_buf buf;
int
main()
{
int j = 0;
if (setjmp(buf))
for (; j<5; j++)
i++;
else {
for (; j<5; j++)
i--;
longjmp(buf,~0);
}
printf("%d\n", i );
}
