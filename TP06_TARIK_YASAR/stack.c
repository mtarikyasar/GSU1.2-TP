/*
 * stack.c
 *
 *  Created on: Mar 14, 2019
 *      Author: Merve Unlu
 */


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

/*
 * Parametre olarak verilen yigit
 * elemanini bellekten siler.
 * yigit zaten bos ise herhangi bir islem
 * yapmaz.
 */
void stack_free(struct stackNode **top) {
    struct stackNode *ttop = *top;
    // Her bir eleman NULL
    // olmadigi surece silme islemi yapar.
    while (ttop != NULL) {
        struct stackNode *orphan = ttop;
        ttop = ttop->next;
        free(orphan);
    }
    *top = NULL;
}

/*
 * Parametre olarak verilen yigit yapisinin
 * bos olup olmadini kontrol eder.
 * yigit bos ise 1, degilse 0 dondurur.
 */
int is_empty(struct stackNode *top){
   int result = 0;
   /*Alistirma 1.a*/

   if (top == NULL){
   		result = 1;
   }

   else{
   	result = 0;
   }

   return result;

}


/*
 * Parametre olarak verilen yigit yapisinda
 * yeni veri data yapisini ekler.
 * (LIFO prensibi ile)
 */
void stack_push(struct stackNode **top, double data) {

	/* Alistirma  1.b */
	/* Yeni dugum icin gosterici olusturun
     * ve bellekte yer acin
     * Bellek icin kontrol yaptiktan sonra
     * yeni veri atamasini yapin
     * Bu atamadan sonra yigittaki
     * ilk deger guncelleyin.
    */

    struct stackNode *newNode = malloc(sizeof(struct stackNode));

    if (newNode == NULL)
    {
    	printf("MALLOC ERROR!!!\n");
    }

    newNode->data = data;

    if (is_empty(*top) != 0)
    {
    	newNode->next = NULL;
    }

    else{
    	newNode->next = *top;
    }

    *top = newNode;
}


/*
 * Parametre olarak verilen yigit yapisindan
 * ilk elemani siler.
 * Eger yigit bos ise -1 degerini gonderir.
 */
double stack_pop(struct stackNode **top) {

	struct stackNode *newNode = *top;

	if (newNode == NULL)
	{
	 	printf("MALLOC ERROR!\n");
	}

	double retval = -1;
	/* yigiti kontrol et, bos ise -1 dondur. */
	/* Alistirma 1.c */
    /* Bos degilse ilk elemani al,
     * sonraki elemani ilk eleman olarak ata,
     * ilk eleman icin ayrilan bellegi sil.
     * ilk eleman verisini dondur.
     */

	if (is_empty(*top) != 0)
	{
		retval = -1;
	}

	else{
		retval = (*top)->data;
		(*top)= newNode->next;

		free(newNode);
	}

    return retval;
}


/*
 * Alistirma 1.d 
 * stack_multi_pop fonksiyonunu tanimlayiniz.
 */
void stack_multi_pop(struct stackNode **top, int k){

	double retval = 0;
	double values[k];
	struct stackNode *newNode = malloc(sizeof(struct stackNode));

	if (is_empty(*top) != 0)
	{
		retval = -1;
	}

	else{
		for (int i = 0; i < k; i++)
	{
		stack_pop(top);
	}
}
}

/*
 * Parametre olarak verilen yigit yapisini
 * ekrana basar.
 * yigit bos ise "yigit bos" mesajini gosterir.
 */
void stack_print(struct stackNode *top) {
    /* Alistirma 1.e */
	/* yigit bos mu kontrol edin
     * Bos ise ekrana mesaj basip fonksiyondan cikmali
     */

	struct stackNode *newNode = top;

	if (is_empty(top) != 0)
	{
		printf("Stack is empty!!!\n");

			return;
	}

	/* 
	 * yigit bos degilse ilk elemandan baslayarak
	 * son elemana kadar hepsini ekrana yazsin.
	 */
	//Hint: yigit yapisi bagli liste olarak tanimlandigindan
	// ekrana basma islemi de bagli listeler ile benzer olacak.

    for (; newNode != NULL ; newNode=newNode->next)
    {
    	printf("%.2lf -> ", newNode->data);
    }
		printf("NULL\n");
	}


