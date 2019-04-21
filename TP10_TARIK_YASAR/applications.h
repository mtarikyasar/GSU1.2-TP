/*
 * applications.h
 *
 *  Created on: Apr 19, 2019
 *      Author: Merve Unlu
 */

#ifndef APPLICATONS_H_
#define APPLICATONS_H_

int is_array_sorted(int* arritem,int size);
int find_maxsum_elements_sorted(int* arritem,int size);
int find_maxsum_elements_unsorted(int* arritem,int size);
int find_mode_element(int* arritem,int size);
void minimum_k_elements(int* arritem,int size,int k,int arrRes[k]);
void remove_duplications(int* arritem,int size,int* dest);

#endif /* APPLICATIONS_H_ */