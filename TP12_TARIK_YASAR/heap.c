/*
 * heap.c
 *
 *  Created on: May 2, 2019
 *      Author: Merve Unlu
 */
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"heap.h"

int left(int i){
  return (2*i + 1);
}

int right(int i){
  return (2*i + 2);
}

/* Zaman olcum fonksiyonlari */
int timeval_subtract(struct timeval *result,
                     struct timeval *t2, struct timeval *t1) {
  long int diff =
    (t2->tv_usec + 1000000 * t2->tv_sec) -
    (t1->tv_usec + 1000000 * t1->tv_sec);
  result->tv_sec = diff / 1000000;
  result->tv_usec = diff % 1000000;
  return (diff < 0);
}

/*
 * Parametre olarak verilen
 * yigini ekrana basar.
 * size: boyutu
 */
void print_heap(int* array,int size){
	int i;
	for(i=0;i<size;i++)
		printf("%d ",array[i]);
	printf("\n");
}


/*
 * Parametre olarak verilen yiginin
 * maksimum yigin ozelligi tasimasini saglar.
 * size   : yigin boyutu
 * indeks : ozelligi bozan degerin indeksi
 */
void max_heapify_recursive(int *array,int indeks,int size){
  // TODO
    int l = left(indeks);
    int r = right(indeks);
    int maxValue = indeks;
    int temp = 0;

    if (l < size && array[l] > array[maxValue]){
      maxValue = l;
    }

    if (r < size && array[r] > array[maxValue]){
      maxValue = r;
    }

    if (maxValue != indeks){
      temp = array[indeks];
      array[indeks] = array[maxValue];
      array[maxValue] = temp;

      max_heapify_recursive(array, maxValue, size);
    }    
}


/*
 * Verilen bir diziden maksimum yigin
 * ozelliginde bir dizi olusturur.
 * size : dizinin boyutu
 */
void build_max_heap(int *array,int size){
	// TODO
  for (int i = size/2 - 1; i >= 0; i--){
    max_heapify_recursive(array, i, size);
  }
}

/*
 * Verilen sirasiz bir diziyi
 * yigin siralama kullanarak siralar.
 */
void heap_sort(int *array,int size){
   // TODO
   int temp = 0;

    build_max_heap(array, size);
    
    for (int i=size-1; i>=0; i--) 
    { 
        // Move current root to end
        temp = array[0];
        array[0] = array[i];
        array[i] = temp; 
  
        // call max heapify on the reduced heap 
        max_heapify_recursive(array, 0, i); 
    } 
}

