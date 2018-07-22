#include<stdio.h>
#include<stdlib.h>
#include"complexxx.h"

int main()
{
    complexxx x;
    complexxx y;
    complexxx z;
    int num=1, d;
    while(num<5){
	printf("enter the numbers a and b \n");
	scanf("%lf %lf %lf %lf", &x.a, &x.b, &y.a, &y.b);
	printf("select an operation:\n 1)SUM;\n 2)DIFFERENCE;\n 3)COMPOSITION;\n 4)DIVISION.\n");
	scanf("%d", &num);
	switch(num){
	case 1:
	    z = addit(x,y);
	    break;
	case 2:
	    z = subtr(x,y);
	    break;
	case 3:
	    z = mult(x,y);
	    break;
	case 4:
	    z = divis(x,y);
	    break;
	default:
	    printf("Not found \n");
	    break;
	}
	if(z.b<0)
	    printf ("%lf%lfi\n", z.a, z.b);
	else
	    printf ("%lf+%lfi\n", z.a, z.b);
	printf("1 for next or 2 for exit: ");
	scanf("%d",&d);
	if(d==2)
	    return -1;
    }
    return 0;
}
