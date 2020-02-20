/*
 * created by: Merve Unlu
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "structpoint.h"

int main()
{
  struct Point p1;
  struct Point *pt1 = &p1;
  pt1->x = 11;
  pt1->y = 9;

  printf("Nokta 1: x %f, y %f\n",pt1->x,pt1->y);

  //Alistirma 1.b

  struct Circle c1;
  struct Circle *ct1 = &c1;

  ct1->center.x = 0.5;
  ct1->center.y = 0.5;
  ct1->radius = 0.5;

  printf("Cember 1: ((x: %f, y: %f)(r: %f))\n", ct1->center.x, ct1->center.y, ct1->radius);

  // Alistirma 2.b

  struct Point p2;
  struct Point *pt2 = &p2;

  pt2->x = ct1->center.x;
  pt2->y = ct1->center.y;

  printf("Uzaklik: %lf\n", distance(pt1, pt2));

  // Alistirma 3 

  printf("Nokta cemberin icinde mi: %d\n", is_in_circle(pt1, ct1));

  // Alistirma 4
  int n_point = 100;
  struct Point pt_array[n_point];
  // create_point_array() ile pt_array i doldurun;
  
    create_point_array(pt_array, n_point);
  
  int i;

  for(i=0;i<n_point;i++){
    // pt_array deki her elemani printf ile basin;
    printf(">> Noktalar (x: %lf, y: %lf)\n", pt_array[i].x, pt_array[i].y);
  }

  // Alistirma 5
  int nbr_in_circle = 0 ; // dairedeki nokta sayaci 
  for(i=0;i<n_point;i++){
    // TODO :  
    //  1- nokta daire icinde mi kontrol et 
    //  2- daire icindeyse sayaci 1 arttir 

    if(is_in_circle(&(pt_array[i]), ct1) == 1) nbr_in_circle++;
  }
  printf("Cember icinde olanlar: %d\n", nbr_in_circle);

  double calculated_pi = 0;

  // pi sayisini nokta sayisini kullanarak hesapla 
  calculated_pi = ((4*(float)nbr_in_circle)/(float)n_point);

  printf("Hesaplanan pi sayisi: %f\n",calculated_pi);
    
  return 0;
}
