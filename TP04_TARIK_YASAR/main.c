/*
 * main.c
 *
 *  Created on: Mar 7, 2019
 *      Author: Merve Unlu
 */


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"linkedlist.h"

int main(int argc, char *argv[])
{
    int test[] = {5, 1024, 10, 20, 30, 100, 2048};
    int test1[] = {10, 20, 30};
    int tmp;

    /* TODO :Alistirma 2 Basit listeyi yarat
     *           Ekrana bas */
    struct node* head;
    head = create_sample_list();
    Print(head);

    /*TODO: Alistirma 3 verifyTest() fonksiyonu icin test */
    printf("\n/////LIST VERIFY/////\n");
    if (verifyList(head, test1) == 1)
    {
    	printf("Great! There is nothing wrong with the list!\n\n");
    }
    else if (verifyList(head, test1) == 0){
    	printf("Oops! There is a problem!\n\n");
    }

    /* TODO: Alistirma 4 Length() fonksiyonu icin test */
    printf("Listenin uzunlugu: %d\n", Length(head));

    Print(head);

    /*TODO: Alistirma 5 Listeye test teki elemanlari ekle. */
    int input = 0;

    //Insert(struct node** head, int new_value, int position)
    Insert(&head, test[0], 0);
    Insert(&head, test[1], 0);
    Insert(&head, test[5], -1);
    Insert(&head, test[6], -1);
    
    /* Su an liste: 5, 1024, 10, 20, 30, 100, 2048 */
    Print(head);

    /* TODO Alistirma 7 GetAt() fonksiyonu icin testler */
    GetAt(head, 0, &tmp) ;
    // donen deger 5 olmali
    printf("Donen deger %d \n",tmp);
    GetAt(head, 6, &tmp);
    // donen deger 2048 olmali
    printf("Donen deger %d \n",tmp);


    /* TODO Alistirma 8 Count() fonksiyonu icin testler */
    int number = Count(head, 5);

    printf("%d times\n", number);

    /* Bagli listeyi temizleyin */
    Free(head);

    return 0;
}
