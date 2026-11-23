#include <stdio.h>
#include <stdlib.h>

const int size = 6; //.rodata
int a = 3;          //.data
int b;              //.bss

void insertOnHeap(int* arr,int size, int *curr , int value){
    if(*curr < size){
        arr[*curr] = value;
        (*curr)++;
        insertOnHeap(arr,size,curr,value+2); //alocado na stack
    }
}
//alocado na stack
int main(){
    printf("%p\n",main);
    int *p;
    int curr = 0;
    p = (int*) calloc(size, sizeof(int)); //alocação no heap
    insertOnHeap(p,size,&curr,a);
    free(p);
}
