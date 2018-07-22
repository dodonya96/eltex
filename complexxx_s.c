#include <stdio.h>
#include "complexxx.h"

complexxx subtr(complexxx x, complexxx y)
{
    complexxx s;
    s.a = x.a - y.a;
    s.b = x.b - y.b;
    return s;
}
