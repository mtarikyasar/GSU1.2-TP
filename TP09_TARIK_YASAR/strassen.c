/*
 * strassen.c
 *
 *  Created on: Apr 11, 2019
 *      Author: Merve Unlu
 */


#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>
#include "strassen.h"


/* Zaman olcum fonksiyonlari */
int timeval_subtract(struct timeval *result,
                     struct timeval *t2, struct timeval *t1) {
  long int diff =
    (t2->tv_usec + 1000000 * t2->tv_sec) -
    (t1->tv_usec + 1000000 * t1->tv_sec);
  result->tv_sec = diff / 1000000;
  result->tv_usec = diff % 1000000;
  return (diff < 0);
}


/* Verilen tek boyutlu diziyi rastgele
 * sayilarla doldurur.
 * Tek boyutlu dizinin bir matrisi
 * ifade etmesi icin ayrica pitch degiskeni kullaniliyor.
 * Ornegin: {2,3,4,6,7,8,1,2,3} dizisi pitch = 3 olarak
 * 3x3 luk bir matrisi ifade eder */
void matrand(int n, int pitch, double M[]) {
  const double r = 10.0;
  int i,j;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      M[i*pitch + j] = r * (2*drand48() - 1);
    }
  }
}

/* Parametre olarak verilen matrisi ekrana basar.
 * Tek boyutlu oldugu icin pitch degeri kullanilir.*/
void matprint(int n, int pitch, const double M[]) {
  int i,j;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      printf("%10.2f ", M[i*pitch + j]);
    }
    printf("\n");
  }
}


/* Parametre olarak verilen iki matrisin toplamini
 * yeni bir matriste saklar.
 * Verilen her matris icin pitch degeri vardir.
 * Ornek: A = | 2  3 |          B = | -3 0 |
 *            | -1 4 | Apitch=2     |  3 4 | Bpitch=2
 *
 *       Sonuc S = |-1 3 |
 *                 | 2 8 | Spitch=2
 */
void matadd(int n,
            int Apitch, const double A[],
            int Bpitch, const double B[],
            int Spitch, double S[]) {
  // TODO: Alistirma 1
  
    for (int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        S[i*Spitch + j] = A[i*Apitch + j] + B[i*Bpitch + j];
      }
    }

}



/* Parametre olarak verilen iki matrisin farkini
 * yeni bir matriste saklar.
 * Verilen her matris icin pitch degeri vardir.
 * Ornek: A = | 2  3 |          B = | -3 0 |
 *            | -1 4 | Apitch=2     |  3 4 | Bpitch=2
 *
 *       Sonuc S = |  5 3 |
 *                 | -4 0 | Spitch=2
 */
void matsub(int n,
            int Apitch, const double A[],
            int Bpitch, const double B[],
            int Spitch, double S[]) {
  // TODO: Alistirma 2
  for (int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      S[i*Spitch + j] = A[i*Apitch + j] - B[i*Bpitch + j];
    }
  }
}


/* MatrisVektor toplami: S = A + b */
void matvecadd(int n,
            int Apitch, const double A[],
            int bpitch, const double b[],
            int Spitch, double S[],int dim) {
  // TODO: Alistirma 3
  
  int k = 0;

  if (dim == 0)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        S[i*Spitch + j] = A[i*Apitch + j] + b[j];
      }
    }
  }

  else if (dim == 1)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        S[i*Spitch + j] = A[i*Apitch + j] + b[i]; //???????
      }
    }
  }
}

/* A nin devrigi S matrisinde saklanacak. 
 */
void mattranspose(int n,
            int Apitch, const double A[],
            int Spitch, double S[]) {
  // TODO: Alistirma 4
  
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      S[i*Spitch + j] = A[j*Apitch + i];
    }
  }
}


/* Parametre olarak verilen iki matris
 * carpimini geri dondurur.
 * Klasik Matris carpimi algoritmasi: C = A * B
 * Ornek: A = | 2  3 |          B = | -3 0 |
 *            | -1 4 | Apitch=2     |  3 4 | Bpitch=2
 *
 *       Sonuc S = |  3 12 |
 *                 | 15 16 | Spitch=2
 * 
*/
void matmult(int n,
             int Apitch, const double A[],
             int Bpitch, const double B[],
             int Cpitch, double C[]) {
  // TODO: Alistirma 6
  
  for (int i = 0; i < n; i++)
  { 
    for (int j = 0; j < n; j++)
    {
      for (int w = 0; w < n; w++)
      {
        C[i*Cpitch + j] += (A[w + i*Apitch]*B[w*Bpitch + j]);
       }
    }
  }
}



// TODO: Alistirma 7 
/* Parametre olarak verilen iki matris
 * carpimini geri dondurur.
 * Klasik Matris carpimi algoritmasi: C = A * B
 * Ornek: A = | 2  3 |          B = | -3 0 |
 *            | -1 4 | Apitch=2     |  3 4 | Bpitch=2
 *
 *       Sonuc S = |  3 12 |
 *                 | 15 16 | Spitch=2
 * Algoritma icin kullanilacak denklemler:
 *     X = | A  B |    Y = | E F |
           | C  D |        | G H |

       P0 = A * (F - H)
       P1 = (A + B) * H
       P2 = (C + D) * E
       P3 = D * (G - E)
       P4 = (A + D) * (E + H)
       P5 = (B - D) * (G + H)
       P6 = (A - C) * (E + F)
          _                                            _
     Z = | (P3 + P4) + (P5 - P1)   P0 + P1              |
         | P2 + P3                 (P0 + P4) - (P2 + P6)|
          -                                            -
 */
void matmult_fast(int n,
                  int Xpitch, const double X[],
                  int Ypitch, const double Y[],
                  int Zpitch, double Z[], int min_mat_recurse) {
  /* min_mat_recurse'e kucuk esik bir
   * matris geldiyse klasik algoritmayi kullan */
  if (n <= min_mat_recurse) {
    matmult(n, Xpitch, X, Ypitch, Y, Zpitch, Z);
    return;
  }

  /* Bu cagridaki alt-matrislerin boylari n/2 olacak */
  const int new_n = n/2;

  const int sz = new_n*new_n*sizeof(double);

  //BURADA KAFAM COK KARISTI SOYLE YAPTIM BEN DE

  //double *P[7];
  /* TODO: 7 adet Px hesabi icin yer ayirin
   * boyutlari sz olacak*/

    double P0[2*2];  //0
    double P1[2*2];  //1
    double P2[2*2];  //2
    double P3[2*2];  //3
    double P4[2*2];  //4
    double P5[2*2];  //5
    double P6[2*2];  //6


  /* TODO: Toplama ve cikarmalar icin gecici T ve U matrisleri
   * icin yer ayirin, boyutlari sz olacak */
    
    double *T = malloc(sizeof(sz));
    double *U = malloc(sizeof(sz));
    
  /* TODO: A-B-C-D matrislerinin baslangic adreslerini ayarlayin
   * (Hepsi X matrisinin icerisinde gomulu) */

    double A[2*2];
    double B[2*2];
    double C[2*2];
    double D[2*2];
    int newPitch = n/2;
    
    for(int i = 0; i < newPitch; i++)
    {
      for(int j = 0; j < newPitch; j++)
      {
            A[i*newPitch + j] = X[i*Xpitch + j];
            B[i*newPitch + j] = X[i*Xpitch + j + newPitch];
       }
    }

    int xy = 0;

    for(int i = 2; i < n; i++)
    {
      for(int j = 0; j < newPitch; j++)
      {
        C[xy*newPitch + j] = X[i*Xpitch + j];
        D[xy*newPitch + j] = X[i*Xpitch + newPitch + j];
      }
      xy++;
    }

  /* TODO: E-F-G-H matrislerinin baslangic adreslerini ayarlayin
   * (Hepsi Y matrisinin icerisinde gomulu) */

    double E[2*2];
    double F[2*2];
    double G[2*2];
    double H[2*2];
    
    for(int i = 0; i < newPitch; i++)
    {
      for(int j = 0; j < newPitch; j++)
      {
            E[i*newPitch + j] = Y[i*Ypitch + j];
            F[i*newPitch + j] = Y[i*Ypitch + j + newPitch];
       }
    }

    int yz = 0;

    for(int i = 2; i < n; i++)
    {
      for(int j = 0; j < newPitch; j++)
      {
        G[yz*newPitch + j] = Y[i*Ypitch + j];
        H[yz*newPitch + j] = Y[i*Ypitch + newPitch + j];
      }
      yz++;
    }

    ////////////////////////////////////////////////////////////////////////////////
  

  /* TODO: P0 = A*(F - H) */

  matsub(2, 2, F, 2, H, 2, T);
  matmult(2, 2, A, 2, T, 2, P0);

  /* TODO: P1 = (A + B)*H */

  matadd(2, 2, A, 2, B, 2, T);
  matmult(2, 2, T, 2, H, 2, P1);

  /* TODO: P2 = (C + D)*E */

  matadd(2, 2, C, 2, D, 2, T);
  matmult(2, 2, T, 2, E, 2, P2);


  /* TODO: P3 = D*(G - E) */

  matsub(2, 2, G, 2, E, 2, T);
  matmult(2, 2, D, 2, T, 2, P3);

  /* TODO: P4 = (A + D)*(E + H) */

  matadd(2, 2, A, 2, D, 2, T);
  matadd(2, 2, E, 2, H, 2, U);
  matmult(2, 2, T, 2, U, 2, P4);

  /* TODO: P5 = (B - D)*(G + H) */

  matsub(2, 2, B, 2, D, 2, T);
  matadd(2, 2, G, 2, H, 2, U);
  matmult(2, 2, T, 2, U, 2, P5);

  /* TODO: P6 = (A - C)*(E + F) */

  matsub(2, 2, A, 2, C, 2, T);
  matadd(2, 2, E, 2, F, 2, U);
  matmult(2, 2, T, 2, U, 2, P6);  

  ////////////////////////////////////////////////////////////////////////////////

  /* Sonucun hesaplanmasi */
  /* TODO: Z sol ust = (P3 + P4) + (P5 - P1) */
  double zUpperLeft[2*2];

  matadd(2, 2, P3, 2, P4, 2, T);
  matsub(2, 2, P5, 2, P1, 2, U);
  matadd(2, 2, T, 2, U, 2, zUpperLeft);

  for(int i = 0; i < newPitch; i++)
  {
    for(int j = 0; j < newPitch; j++)
    {
      Z[i*Zpitch + j] = zUpperLeft[newPitch*i + j];
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

  /* TODO: Z sol alt = (P2 + P3) */
  double zBottomLeft[2*2];
  int x = 0;

  matadd(2, 2, P2, 2, P3, 2, zBottomLeft);

  for(int i = newPitch; i < n; i++)
  {
    for(int j = 0; j < newPitch; j++)
    {
      Z[i*Zpitch + j] = zBottomLeft[newPitch*x + j];
    }
    x++;
  }

  ////////////////////////////////////////////////////////////////////////////////

  /* TODO: Z sag ust = (P0 + P1) */
  double zUpperRight[2*2];

  matadd(2, 2, P0, 2, P1, 2, zUpperRight);

  for(int i = 0; i < newPitch; i++)
  {
    for(int j = 0; j < newPitch; j++)
    {
      Z[i*Zpitch + j + newPitch] = zUpperRight[newPitch*i + j];
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

  /* TODO: Z sag alt = (P0 + P4) - (P2 + P6) */
  double zBottomRight[2*2];
  int y = 0;

   matadd(2, 2, P0, 2, P4, 2, T);
   matadd(2, 2, P2, 2, P6, 2, U);
   matsub(2, 2, T, 2, U, 2, zBottomRight);

   for(int i = newPitch; i < n; i++)
  {
    for(int j = 0; j < newPitch; j++)
    {
      Z[i*Zpitch + j + newPitch] = zBottomRight[newPitch*y + j];
    }
    y++;
  }

   ////////////////////////////////////////////////////////////////////////////////

  /* TODO: Gecici pointerlar U ve T'yi free() edin */

  /* TODO: P[] dizisindeki bellek alanlarini free() edin */
}
