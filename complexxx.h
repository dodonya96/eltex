/*complexxx.h*/
#include <stdio.h>

typedef struct {
    double a, b;
}complexxx;

complexxx addit(complexxx x, complexxx y);
complexxx subtr(complexxx x, complexxx y);
complexxx mult(complexxx x, complexxx y);
complexxx divis(complexxx x, complexxx y);
