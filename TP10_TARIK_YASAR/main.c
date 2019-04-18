/*
 * main.c
 *
 *  Created on: Apr 18, 2019
 *      Author: Merve Unlu
 */


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include"sorting.h"
#define SIZE 20

/*
 * Rastgele dizi elemanlari uretir.
 * Dizi boyutu parametre olarak verilir.
 * Sayilar 0-100 arasindadir.
 */
void random_array(int* arrRand,int size){
   int i=0;
   srand(time(NULL));
   for(i=0;i<size;i++){
	   arrRand[i] =  rand()%100;
   }
}

int main(int argc,char* argv[]){

	int arrEx[] = {3,4,6,1,8,12,58,0,2,55,88,9,23,5,34,15,19,7,43,10};
	int arrEx1[] = {3,4,6,1,8,12,58,0,2,55,88,9,23,5,34,15,19,7,43,10};
	int i;

	int* arrRand = malloc(sizeof(int)*SIZE);
	random_array(arrRand,SIZE);

	/*
	 * Siralama algoritmaları için test
	 */
	insertion_sort(arrRand,SIZE);
	//assert(is_array_sorted(arrRand,SIZE));
	random_array(arrRand,SIZE);
	
	for(int x = 0; x < SIZE; x++){
		printf("%d, ", arrRand[x]);
	}
	selection_sort(arrRand,SIZE);
	printf("\n///////////////////////////\n");
	for(int x = 0; x < SIZE; x++){
		printf("%d, ", arrRand[x]);
	}
	bubble_sort(arrEx1,SIZE);

	// TODO: Algoritmalar ayni dizi verildiginde
	// nasil bir performans sergiliyor?
	// Hangisi daha hizli, clock kullanarak gosteriniz.
	// Yorumunuzu sorting.c icine ekleyiniz.

	time_t start0, start1, start2;
	time_t end0, end1, end2;

	int* randArr0 = malloc(sizeof(int)*SIZE);
	int* randArr1 = malloc(sizeof(int)*SIZE);
	int* randArr2 = malloc(sizeof(int)*SIZE);

	random_array(randArr0, SIZE);
	
	for(int i = 0; i < SIZE; i++){
		randArr1[i] = randArr0[i];
		randArr2[i] = randArr0[i];
	}

	start0 = clock();
	insertion_sort(randArr0, SIZE);
	end0 = clock();

	start1 = clock();
	selection_sort(randArr1, SIZE);
	end1 = clock();

	start2 = clock();
	bubble_sort(randArr2, SIZE);
	end2 = clock();

	double time0 = (double)(end0-start0)/CLOCKS_PER_SEC;
	double time1 = (double)(end1-start1)/CLOCKS_PER_SEC;
	double time2 = (double)(end2-start2)/CLOCKS_PER_SEC;

	printf("InsertionSort time:\t%lf\n", time0);
	printf("SelectionSort time:\t%lf\n", time1);
	printf("BubbleSort time:\t%lf\n", time2);




	// Sirali dizi ile maksimum testi
	assert(find_maxsum_elements_sorted(arrEx1,SIZE)==146);
	// Sirasiz dizi ile maksimum testi
	assert(find_maxsum_elements_unsorted(arrEx,SIZE)==146);

	// Mod elemani bulan fonksiyon testi
	int arrMode[] = {3,4,6,1,3,4,3,1,3,6};
	assert(find_mode_element(arrMode,10)==3);

	// minimum 5 eleman testi
	int arrRes[] = {0,0,0,0,0};
	int arrEx5[] = {3,4,6,1,8,12,58,0,2,55,88,9,23,5,34,15,19,7,43,10};
	minimum_k_elements(arrEx5,SIZE,5,arrRes);
	for(i=0;i<5;i++){
		assert(arrRes[i]==arrEx5[SIZE-1-i]);
	}

	//remove_duplications testi
	int arrDup[] = {3,4,6,1,3,2,3,1,3,6};
	int* dest;
	remove_duplications(arrDup,10,dest);
	for(i=1;i<=5;i++){
		assert(dest[i-1]!=dest[i]);
	}

	return 0;
}
