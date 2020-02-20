/*
 * contactlist.c
 *
 *  Created on: Feb 21, 2019
 *      Author: Merve Unlu
 */

#include"contactlist.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


/*
 * Parametre olarak verilen sayi kadar
 * elemani olan bir dizi ile bunu gosteren
 * ContactList tipinde değişken oluşturur.
 */
ContactList create_contact_list(int number){
    ContactList c ;
    // Alistirma 1
    c.current_number = 0;
    c.max_number = number;

    c.contact_list = malloc(sizeof(Contact) * number);

    if (c.contact_list == NULL)
    {
      printf("Malloc basarisiz!\n");
    }

    return c;
}

/*
 * Parametre olarak verilen listeye
 * yeni elemani ekler.
 */
void add_new_contact(ContactList* c,Contact new_cnt){
  // Alistirma 2
	/*
	 * Eleman eklerken oncelikle
	 * guncel eleman sayisi ve max sayiyi kontrol ediniz.
	 * Guncel sayi daha buyukse hafizada yeniden yer
	 * acilmasi gerekecek.
	 */

	if (c->current_number == c->max_number)
	{
    c->max_number++;
    c->contact_list = realloc(c->contact_list, sizeof(Contact)* c->max_number);
		if (c->contact_list == NULL)
		{
			printf("Malloc hatasi!\n");
		}
	}

      c->contact_list[c->current_number].id = new_cnt.id;
      strcpy(c->contact_list[c->current_number].name, new_cnt.name);
      strcpy(c->contact_list[c->current_number].surname, new_cnt.surname);
      strcpy(c->contact_list[c->current_number].tel_number, new_cnt.tel_number);

      c->current_number++;
}

/*
 * Parametre olarak verilen
 * ContactList icindeki listeyi
 * ekrana basar.
 */
void print_contact_list(ContactList c){
  // Alistirma 3
  c.current_number = 0;
//  int number = c.current_number;

  do{
    printf("\t%d. PERSON \n", c.current_number);
    printf("ID: %d\n", c.contact_list[c.current_number].id);
    printf("Name: %s\n", c.contact_list[c.current_number].name);
    printf("Surname: %s\n", c.contact_list[c.current_number].surname);
    printf("Phone number: %s\n", c.contact_list[c.current_number].tel_number);
    
      c.current_number++;
  } while(c.current_number < c.max_number);

}

/*
 * Parametre olarak verilen
 * kisi listesinde istenen ismi arar.
 */
char* find_contact(ContactList *c,char* name){
    int i;
    char* tel_nbr = malloc(sizeof(char)*20);
    // Alistirma 5

    for (i = 0; i < c->max_number; i++)
    {
      if (strcmp(name, c->contact_list[i].name) == 0)
      {
        strcpy(tel_nbr, c->contact_list[i].tel_number);
      }

    }

    return tel_nbr;
}

/*
 * Parametre olarak verilen
 * listeyi bellekten siler.
 */
void delete_contact_list(ContactList *c){
  // Alistirma 7
  free(c->contact_list);
  c->contact_list = NULL;
}

/*
 * Parametre olarak verilen
 * kisi listesini adi verilen
 * dosyaya yazar.
 */
  
void save_contact_list(ContactList c,char* fname){
   // Alistirma BONUS
    FILE *fw = fopen(strcat(fname, ".txt"), "w");

  if(!fw){
    printf("File Opening Error!!! \n");
  }

  for(size_t i = 0; i < c.max_number; i++)
   {
     fprintf(fw, "\nID: %d\n", c.contact_list[i].id);
     fprintf(fw, "Name: %s\n", c.contact_list[i].name);
     fprintf(fw, "Surname: %s\n", c.contact_list[i].surname);
     fprintf(fw, "Phone number: %s\n", c.contact_list[i].tel_number);
}

   printf("Exported!\n");
    fclose(fw);

}
  //Alistirma 8 (Numara degistirme)

void change_tel_number(ContactList *c, char* name){
    char* new_tel_nbr = malloc(sizeof(char)*20);

    printf("Enter the new number(5xxxxxxxxx): ");
    scanf("%s", new_tel_nbr);

    for (int i = 0; i < c->max_number; i++)
    {
      if(strcmp(name, c->contact_list[i].name) == 0){
        printf("Number of the %s : %s", c->contact_list[i].name, c->contact_list[i].tel_number);
        strcpy(c->contact_list[i].tel_number, new_tel_nbr);

      }
    }

    printf("New number: %s\n", new_tel_nbr);
}