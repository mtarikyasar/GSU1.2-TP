/*
 * linkedlist.c
 *
 *  Created on: Mar 7, 2019
 *      Author: Merve Unlu
 */
#include"linkedlist.h"
#include<stdio.h>
#include<stdlib.h>

/* 10, 20, 30 elemanlarindan olusan basit bir liste
 * olusturan fonksiyon. */
// TODO: Alistirma 1
struct node* create_sample_list(void){
    struct node* head = NULL;
    struct node* second = NULL;
    struct node* third = NULL;

    head = malloc(sizeof(struct node));
    second = malloc(sizeof(struct node));
    third = malloc(sizeof(struct node));

    if (head == NULL)
    {
    	printf("MALLOC ERROR!\n");
    }
    if (second == NULL)
    {
    	printf("MALLOC ERROR!\n");
    }
    if (third == NULL)
    {
    	printf("MALLOC ERROR!\n");
    }

    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = NULL;

    return head;
}

/* Bagli listenin elemanlarini ekrana yazdiran fonksiyon. */
void Print(struct node* head){
    struct node* cur = head;
    for (; cur != NULL; cur = cur->next) {
        printf("%d -> ", cur->data);
    }
    puts("NULL");
}

/* Bir listenin belli bir icerige sahip olup olmadigini
 * dogrulayan test fonksiyonu. */
int verifyList(struct node* head, int *values){
    // TODO Alistirma 3
    struct node* cur = head;
    int i = 0;

	while(cur != NULL){
		if(cur -> data != values[i]) return 0;

		else return 1;
	}
}

/* Parametre olarak verilen
 * head'in gosterdigi listede kac dugum oldugunu
 * hesaplayip geriye dondurun. */
int Length(struct node* head){
   // TODO Alistirma 4

	struct node* cur = head;
	int i = 0;

	for (; cur != NULL ; cur = cur->next)
	{
		i++;
	}

	return i;
}

/* Listenin herhangi bir yerine dugum ekleyen asagidaki
 * fonksiyonu doldurun.
 * position == 0 ise listenin basina,
 * position == -1 ise listenin sonuna,
 * position baska bir deger ise araya ekleme yapacaksiniz.
 * Ornegin liste
 *      5, 10, 15
 * dugumlerinden olussun.
 *
 * position == 0  ise yeni liste: 20, 5, 10, 15
 * position == -1 ise yeni liste: 5, 10, 15, 20
 * position == 1  ise yeni liste: 5, 20, 10, 15
 *
 * olmalidir.
 */

void Insert(struct node** head, int new_value, int position) {
    // TODO Alistirma 5
    /* En one ekleme: position == 0
     * En sona ekleme: position == -1
     * Diger degerler, aralara ekleme.
     * (Position listenin uzunlugundan fazlaysa dogal olarak
     * en sona eklemis olacaksiniz) */
	struct node* new_node = malloc(sizeof(struct node));
	new_node -> data = new_value;

	if (new_node == NULL)
	{
		printf("Malloc error at Insert function!\n");
	}

	if(position == 0){
		new_node -> next = *head;
		*head = new_node;
	}

	struct node* tmp = malloc(sizeof(struct node));
	tmp = *head;

	if(position == (-1)){
		new_node -> next = NULL;
		if (tmp == NULL)
		{
			*head = new_node;
		}
		else
		{
			
			while(tmp -> next != NULL){
				tmp = tmp -> next;
			}
			tmp -> next = new_node;
		}
	}

	if (position != 0 && position != -1)
	{
		struct node* iter = *head;
		for (int i = 0; i < position-1; i++){
			iter = iter -> next;
		}
		new_node -> next = iter -> next;
		iter -> next = new_node;
		}
}

/* head'in gosterdigi listenin butun dugumlerini
 * free() ile temizleyin. */
void Free(struct node* head) {
   // TODO Alistirma 6
	struct node* cur = head;

   for(; cur != NULL; cur = cur->next)
   {
       free(cur);
}
}
/* position ile verilen pozisyondaki elemani *result
 * pointeriyla verilen yere yazin.
 * Eger olmayan bir pozisyon istendiyse fonksiyon 1 dondurmeli, liste sinirlari
 * dahilinde kalindi ve basarili olunduysa 0 dondurmelidir. */
int GetAt(struct node* head, int position, int *result) {
   // TODO: Alistirma 7
	struct node* cursor = head;

	int length = Length(head);

	if (length > position)
	{
		return 1;
	}

	for (size_t i = 1; i < position; i++)
	{
		cursor = cursor -> next;
	}

	result = &(cursor -> data);
return 0;
}
/* Listede value degerinin kac defa
 * yer aldigini hesaplayip geri donduren fonksiyonu yazin. */
int Count(struct node* head, int value) {
  // TODO: Alistirma 8

	struct node* cursor = head;
	int count = 0;

	while(cursor != NULL){
		if (cursor -> data == value)
		{
			count++;
		}

		cursor = cursor -> next;
	}

	return count;
}



