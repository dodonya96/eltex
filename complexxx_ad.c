#include <stdio.h>
#include "complexxx.h"

complexxx addit(complexxx x, complexxx y){
    complexxx ad;
    ad.a = x.a + y.a;
    ad.b = x.b + y.b;
    return ad;
}
