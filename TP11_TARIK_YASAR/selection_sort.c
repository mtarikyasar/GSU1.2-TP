#include <stdlib.h>
#include <stdio.h>

void selection_sort(int* arritem, int size){
    int i, j, min, temp;

    for(i = 0; i < size; i++){
        min = i;

        for(j = i; j < size; j++){

            if(arritem[j] < arritem[min]) {
                min = j;
            }
        }

        temp = arritem[min];
        arritem[min] = arritem[i];
        arritem[i] = temp;
    }
}