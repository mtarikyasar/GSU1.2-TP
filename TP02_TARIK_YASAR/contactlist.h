/*
 * contactlist.h
 *
 *  Created on: Feb 21, 2019
 *      Author: Merve Unlu
 */

#ifndef CONTACTLIST_H_
#define CONTACTLIST_H_

/*
 * Kisi tipini ifade eder.
 * name: adi
 * surname: soyadi
 * tel_number: telefon numarasi
 * id: id numarasi
 */
typedef struct mContact{
	char name[20];
	char surname[20];
	char tel_number[11];
	int id;
} Contact;

/*
 * Kisi listesini ifade eder.
 * contact_list: kisileri tasiyan
 *      dizidir.
 * max_number: dizideki maksimum
 *      eleman sayisidir.
 * current_number: dizideki guncel
 *      eleman sayisidir.
 */
typedef struct mContactList{
	Contact* contact_list;
	int current_number;
	int max_number;
} ContactList;

ContactList create_contact_list(int number);
void add_new_contact(ContactList* c,Contact new_cnt);
void print_contact_list(ContactList c);
char* find_contact(ContactList *c,char* name);
void delete_contact_list(ContactList *c);

//Alistirma 8
void change_tel_number(ContactList *c, char* name);

// BONUS
void save_contact_list(ContactList c,char* fname);


#endif /* CONTACTLIST_H_ */
