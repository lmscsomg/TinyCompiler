#include <stdio.h>
int main()
{
int fact, x;
scanf("%d", &x);
if (0 < x)
{
    fact = 1 ;
 do{
    fact = fact * x ;
    x = x - 1 ;

}while(!(x == 0));

printf("%d", fact);

}
return 0;
}
