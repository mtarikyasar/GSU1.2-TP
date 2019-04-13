/*
 * main.c
 *
 *  Created on: Apr 20, 2017
 *      Author: Merve Unlu
 */

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include"strassen.h"

int main(int argc, char *argv[]) {

  /* Fonksiyonlarin test edilmesi */
  double _X[4*4] = {
    1, 2, 3, 1,
    -1, 1, 2, 3,
    0, 4, 5, -3,
    -1, 1, 2, 3
  };
  double _Y[4*4] = {
    1, 2, 3, 4,
    4, 3, 2, 1,
    -1, -1, 2, 2,
    3, 0, 1, 2
  };
  double _Z[4*4] = {0};
  
  /////////////////////////////////////////////////////////////
  //TODO : Alistirma 5
  
  /*
  
  double _Q[4] = {1, 0 ,2, 5};
  
  matadd(4, 4, _X, 4, _Y, 4, _Z);

  printf("MATADD SONUC: \n");

  matprint(4, 4, _Z);

  printf("///////////////////////////\n");

  matsub(4, 4, _X, 4, _Y, 4, _Z);

  printf("MATSUB SONUC: \n");

  matprint(4, 4, _Z);

  printf("///////////////////////////\n");

  matvecadd(4, 4, _X, 4, _Q, 4, _Z, 0);

  printf("MATVECADD SONUC (DIM = 0) : \n");

  matprint(4, 4, _Z);

  printf("///////////////////////////\n");

  matvecadd(4, 4, _X, 4, _Q, 4, _Z, 1);

  printf("MATVECADD SONUC (DIM = 1) : \n");

  matprint(4, 4, _Z);

  printf("///////////////////////////\n");

  mattranspose(4, 4, _X, 4, _Z);

  printf("MATTRANSPOSE SONUC : \n");

  matprint(4, 4, _Z);

  printf("///////////////////////////\n");

  */
 
  /////////////////////////////////////////////////////////////
  
  matmult(4, 4, _X, 4, _Y, 4, _Z);
  matprint(4, 4, _Z);
  printf("=========================\n");

  double _Zfast[4*4] = {0};
  
  matmult_fast(4, 4, _X, 4, _Y, 4, _Zfast, 2);
  matprint(4, 4, _Zfast);
  
  double err = 0.0;
  int i ;
  for (i = 0; i < sizeof(_Z) / sizeof(double); ++i) {
    err += _Z[i] - _Zfast[i];
  }
  printf("Error between methods: %.5f\n", err);
  assert(err < 0.0000001);

  /////////////////////////////////////////////////////////////
  // TODO: Alistirma 8

  /* Matris boyutu (int)      : argv[1] */
  /* recursion base case (int): argv[2] */
  if (argc != 3) {
    printf("Usage: %s <matrix dimension> <base recursion case>\n", argv[0]);
    exit(1);
  }

  /* Komut satirindan verilen matris boyutu ve ozyinelemenin
   * sonlandirilacagi temel durum. */
  int mat_size = atoi(argv[1]);
  int min_mat_recurse = atoi(argv[2]);

  /* Zaman olcumleri icin gerekli */
  struct timeval tvBegin, tvEnd, tvDiff;

  //double *X, *Y, *Z, *Zfast;
  /* TODO: 4 gosterici icin ilgili yerleri ayirin */

  const int sz = mat_size*mat_size*(sizeof(double));

  double *X = malloc(sz);
  double *Y = malloc(sz);
  double *Z = malloc(sz);
  double *Zfast = malloc(sz);



  /* TODO: Gostericilerden birisi NULL ise bellek hatasi verip
   * programi 1 donus degeriyle sonlandirin. 
   * if kontrolunun icini doldurup yorum satirindan cikarin.
   */
    if (X == NULL || Y == NULL || Z == NULL || Zfast == NULL) {
       fprintf(stderr, "Error allocating memory.\n");
       exit(1);
   }  

  /* TODO: X ve Y matrislerini rasgele doldurun */

  matrand(mat_size, mat_size, X);
  matrand(mat_size, mat_size, Y);

  /* Klasik carpim algoritmasinin olcumu */
  gettimeofday(&tvBegin, NULL);
  matmult(mat_size, mat_size, X, mat_size, Y, mat_size, Z);
  gettimeofday(&tvEnd, NULL);
  timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
  printf("matmult (%dx%d) --> %ld.%06ld\n", mat_size, mat_size, (long int) tvDiff.tv_sec, (long int) tvDiff.tv_usec);

  /* Strassen carpim algoritmasinin olcumu */
  gettimeofday(&tvBegin, NULL);
  matmult_fast(mat_size, mat_size, X, mat_size, Y, mat_size, Zfast, min_mat_recurse);
  gettimeofday(&tvEnd, NULL);
  timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
  printf("matmult_fast (%dx%d - base_case: %d) --> %ld.%06ld\n", mat_size, mat_size, min_mat_recurse, (long int) tvDiff.tv_sec, (long int) tvDiff.tv_usec);

  /* TODO: 4 gostericiye ayrilan yerleri free() edin. */

  free(X);
  free(Y);
  free(Z);
  free(Zfast);

  return 0;
}
