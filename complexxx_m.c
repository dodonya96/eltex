#include <stdio.h>
#include "complexxx.h"

complexxx mult(complexxx x, complexxx y)
{
    complexxx m;
    m.a = x.a * y.a - x.b * y.b;
    m.b = x.a * y.b + x.b * y.a;
    return m;
}
