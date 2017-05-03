#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



int main()
{
int array = (int*)malloc(sizeof(int)*100);
int *ptr;
free(ptr);
printf("%d\n", ptr[50]);

}
