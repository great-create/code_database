#include <stdio.h>
int main(){
    int a = 20;
    int *b=&a;
    
    printf("a = %d\n",a);
    printf("Addr of a = %p\n",&a);
    
    printf("b = %p\n",b);
    printf("Addr of b = %p\n",&b);
    return 0;
}
