/*
 * main.c
 *
 *  Created on: Feb 21, 2019
 *      Author: Merve Unlu
 */

//LUTFEN README.txt ISIMLI DOSYAYI OKUYUNUZ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contactlist.h"

int main(int argc,char* argv[]){
	
	ContactList cl;
	int i = 0;

   // Alistirma 4
	cl = create_contact_list(3);

	while(cl.current_number != cl.max_number){
		Contact c;
		c.id = i;
		printf("Enter name: ");
		scanf("%s", c.name);
		printf("Enter surname: ");
		scanf("%s", c.surname);
		printf("Enter phone number: ");
		scanf("%s", c.tel_number);
		printf("Contact Added!\n");
		i++;
		printf("////////////////////////////////\n");
	
		add_new_contact(&cl, c);
	}
	printf("\n////////~CONTACTS~////////\n");
	print_contact_list(cl);

		
	
   // Alistirma 6
	printf("\n/////// SEARCH TAB ///////\n");
	char *name_src = malloc(sizeof(char)*20);
	char *print_number = malloc(sizeof(char)*20);

	printf("Enter name to search: ");
	scanf("%s", name_src);
	print_number = find_contact(&cl, name_src);

	if (print_number == NULL)
	{
		printf("There is no such person!\n");
	}
	else{
		printf("Telefon numarasi: %s\n", print_number);
	}


	// Alistirma 8
	char *name_src2 = malloc(sizeof(char)*20);
		printf("//////// CHANGING NUMBER ///////\n");
		printf("Enter the name of the person that you want to change phone number: ");
		scanf("%s", name_src2);

		change_tel_number(&cl, name_src2);

		print_contact_list(cl);

		free(name_src2);
		name_src2 = NULL;
		free(print_number);
		print_number = NULL;
		free(name_src);
		name_src = NULL;


	//BONUS
		printf("////// EXPORT FILE ///////\n");
			char *fileName;
				fileName = malloc(sizeof(char)*20);
				printf("Enter a filename: ");
				scanf("%s", fileName);

				save_contact_list(cl, fileName);
				
				free(fileName);
				fileName = NULL;

   // Alistirma 7
		//Rehberi siler
	delete_contact_list(&cl);

	

}
