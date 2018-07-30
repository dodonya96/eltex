#include <stdio.h>
#include "complexxx.h"

complexxx divis(complexxx x, complexxx y){
    complexxx d;
    d.a = (x.a * y.a + x.b * y.b)/(y.a * y.a + y.b * y.b);
    d.b = (y.a * x.b - x.a * y.b)/(y.a * y.a + y.b * y.b);
    return d;
}
