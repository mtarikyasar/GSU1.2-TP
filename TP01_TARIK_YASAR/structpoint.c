/*
 * created by: Merve Unlu
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include"structpoint.h"
#include<math.h>
#define MIN_INT 0
#define MAX_INT 1


/*
 * [min,max] arasinda rastgele sayi uretir
 */
float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}


/*
 * Point tipindeki iki değisken arasinda
 * uzakligi hesaplar.
 * Uzaklik hesabi: ((x1-x2)^2 + (y1-y2)^2)^(1/2)
 */
double distance(struct Point *a, struct Point *b)
{
  /* Alistirma 2.a*/
	double result = 0;

	result = sqrt((((b->x)-(a->x))*((b->x)-(a->x)))+(((b->y)-(a->y))*((b->y)-(a->y))));

		return result;
}

/*
 * Verilen bir noktanin verilen cember 
 * icinde olup olmadigina bakar. 
 */

int is_in_circle(struct Point *a, struct Circle *c)
{
  /* Alistirma 3*/

	if (distance(a, &(c->center)) <= c->radius)
	{
		return 1;
	}

	return 0;
}

/* Verilen point dizisini 
 * rastgele uretilen sayilar ile doldurur.
 */
void create_point_array(struct Point *pt_array,int N){
  /* Alistirma 4 */

		for (int i = 0; i < N; ++i)
		{
			pt_array[i].x = float_rand(MIN_INT, MAX_INT);
			pt_array[i].y = float_rand(MIN_INT, MAX_INT);
		}
}

