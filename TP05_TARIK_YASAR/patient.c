#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "patient.h"

const char *priority_strings[] = {
    "Heart attack",
    "Fracture",
    "Nausea",    
    "Fever",
    "Headache",
    NULL,
};


/*
 * Parametre olarak verilen kuyruk yapisinin
 * elemanlarini ekrana basar.
 */
void print_queue(struct patientInfo *head) {
   if (!is_empty(head)) {
        printf("\nCurrent Queue:\n");
        printf("--------------\n");
        int i = 1;
        while (head) {
            printf("%2d: [%12s (priority: %d)] Social security number: %d\n", i, priority_strings[head->prio], head->prio, head->ssn);
            head = head->next;
            i += 1;
        }
        printf("\n");
    }
}

/*
 * Parametre olarak verilen kuyrugun bos olup
 * olmadigini kontrol eder.
 * Bos ise 1 degilse 0 dondurur.
 */
int is_empty(struct patientInfo *head) {
    // Alistirma 1
    if (head == NULL)
    {
        return 1;
    }

    else return 0;
}

/* Parametre olarak verilen elemanlardan
 * yeni bir hasta olusturup
 * kuyruga ekler.
 * Hastanin guvenlik numarasi ve 
 * oncelik bilgisi fonksiyon parametreleridir. 
 */
struct patientInfo* enqueue(struct patientInfo *head, enum Priority prio, int ssn) {
   // Alistirma 2
    struct patientInfo *newPatiant = malloc(sizeof(struct patientInfo));
  	
  	if(newPatiant == NULL){
  		printf("Malloc Error!\n");
  	}

  	newPatiant->prio = prio;
  	newPatiant->ssn = ssn;
  	newPatiant->next = NULL;

  	if (head == NULL)
  	{
  		return newPatiant;
  	}

  	if ((head->next) == NULL)
  	{
  		if (prio < (head->prio))
  		{
  			newPatiant->next = head;
  			return newPatiant;
  		}
  		else{
  			head->next = newPatiant;
  		}
  		return head;
  	}

  	struct patientInfo *cursor = head;

  	if (prio < head->prio)
  	{
  		newPatiant->next = head;
  		return newPatiant;
  	}

  	while(cursor->next){
  		if(prio < ((cursor->next)->prio)) {
  			break;
  		}
  		cursor = cursor->next;
  	}

  	struct patientInfo *tmp = cursor->next;
  	cursor->next = newPatiant;
  	newPatiant->next = tmp;
  	return head;
}


/*
 * Parametre olarak verilen kuyruktan ilk elemani siler
 * ve geri dondurur.
 */

struct patientInfo* dequeue(struct patientInfo **head) {
  // Alistirma 3
    struct patientInfo *tmp = *head;
    *head = (*head)->next;

    return tmp;
}


