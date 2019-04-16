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
  		C[i*Cpitch + j] = 0;
  	}
  }
  
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

  const size_t sz = new_n*new_n*sizeof(double);

  double *P[7];
  /* TODO: 7 adet Px hesabi icin yer ayirin
   * boyutlari sz olacak*/   
  for (int i = 0; i < 7; i++)
  {
    P[i] = (double*)malloc(sz);
   
      if (P[i] == NULL)
      {
        printf("Malloc Error!(P)");
      }
      
  }
  
  /* TODO: Toplama ve cikarmalar icin gecici T ve U matrisleri
   * icin yer ayirin, boyutlari sz olacak */
    
    double *T = malloc(sz);
    double *U = malloc(sz);

    if(T == NULL || U == NULL){
      printf("Malloc Error!");
    }
    
  /* TODO: A-B-C-D matrislerinin baslangic adreslerini ayarlayin
   * (Hepsi X matrisinin icerisinde gomulu) */
    
    double A[new_n*new_n];
    double B[new_n*new_n];
    double C[new_n*new_n];
    double D[new_n*new_n];

    for(int i = 0; i < new_n; i++)
    {
      for(int j = 0; j < new_n; j++)
      {
        A[i*new_n + j] = X[i*Xpitch + j];
        B[i*new_n + j] = X[i*Xpitch + j + new_n];
       }
    }

    int xy = 0;

    for(int i = new_n; i < n; i++)
    {
      for(int j = 0; j < new_n; j++)
      {
        C[xy*new_n + j] = X[i*Xpitch + j];
        D[xy*new_n + j] = X[i*Xpitch + new_n + j];
      }
      xy++;
    }

  /* TODO: E-F-G-H matrislerinin baslangic adreslerini ayarlayin
   * (Hepsi Y matrisinin icerisinde gomulu) */
  
    double E[new_n*new_n];
    double F[new_n*new_n];
    double G[new_n*new_n];
    double H[new_n*new_n];
    
    for(int i = 0; i < new_n; i++)
    {
      for(int j = 0; j < new_n; j++)
      {
        E[i*new_n + j] = Y[i*Ypitch + j];
        F[i*new_n + j] = Y[i*Ypitch + j + new_n];
       }
    }

    int yz = 0;

    for(int i = new_n; i < n; i++)
    {
      for(int j = 0; j < new_n; j++)
      {
        G[yz*new_n + j] = Y[i*Ypitch + j];
        H[yz*new_n + j] = Y[i*Ypitch + new_n + j];
      }
      yz++;
    }

    ////////////////////////////////////////////////////////////////////////////////

  /* TODO: P0 = A*(F - H) */

  matsub(new_n, new_n, F, new_n, H, new_n, T);
  matmult(new_n, new_n, A, new_n, T, new_n, P[0]);

  /* TODO: P1 = (A + B)*H */

  matadd(new_n, new_n, A, new_n, B, new_n, T);
  matmult(new_n, new_n, T, new_n, H, new_n, P[1]);

  /* TODO: P2 = (C + D)*E */

  matadd(new_n, new_n, C, new_n, D, new_n, T);
  matmult(new_n, new_n, T, new_n, E, new_n, P[2]);

  /* TODO: P3 = D*(G - E) */

  matsub(new_n, new_n, G, new_n, E, new_n, T);
  matmult(new_n, new_n, D, new_n, T, new_n, P[3]);

  /* TODO: P4 = (A + D)*(E + H) */

  matadd(new_n, new_n, A, new_n, D, new_n, T);
  matadd(new_n, new_n, E, new_n, H, new_n, U);
  matmult(new_n, new_n, T, new_n, U, new_n, P[4]);

  /* TODO: P5 = (B - D)*(G + H) */

  matsub(new_n, new_n, B, new_n, D, new_n, T);
  matadd(new_n, new_n, G, new_n, H, new_n, U);
  matmult(new_n, new_n, T, new_n, U, new_n, P[5]);

  /* TODO: P6 = (A - C)*(E + F) */

  matsub(new_n, new_n, A, new_n, C, new_n, T);
  matadd(new_n, new_n, E, new_n, F, new_n, U);
  matmult(new_n, new_n, T, new_n, U, new_n, P[6]);  

  ////////////////////////////////////////////////////////////////////////////////

  /* Sonucun hesaplanmasi */
  /* TODO: Z sol ust = (P3 + P4) + (P5 - P1) */
  double zUpperLeft[new_n*new_n];

  matadd(new_n, new_n, P[3], new_n, P[4], new_n, T);
  matsub(new_n, new_n, P[5], new_n, P[1], new_n, U);
  matadd(new_n, new_n, T, new_n, U, new_n, zUpperLeft);

  for(int i = 0; i < new_n; i++)
  {
    for(int j = 0; j < new_n; j++)
    {
      Z[i*Zpitch + j] = zUpperLeft[new_n*i + j];
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

  /* TODO: Z sol alt = (P2 + P3) */
  double zBottomLeft[new_n*new_n];
  int x = 0;

  matadd(new_n, new_n, P[2], new_n, P[3], new_n, zBottomLeft);

  for(int i = new_n; i < n; i++)
  {
    for(int j = 0; j < new_n; j++)
    {
      Z[i*Zpitch + j] = zBottomLeft[new_n*x + j];
    }
    x++;
  }

  ////////////////////////////////////////////////////////////////////////////////

  /* TODO: Z sag ust = (P0 + P1) */
  double zUpperRight[new_n*new_n];

  matadd(new_n, new_n, P[0], new_n, P[1], new_n, zUpperRight);

  for(int i = 0; i < new_n; i++)
  {
    for(int j = 0; j < new_n; j++)
    {
      Z[i*Zpitch + j + new_n] = zUpperRight[new_n*i + j];
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

  /* TODO: Z sag alt = (P0 + P4) - (P2 + P6) */
  double zBottomRight[new_n*new_n];
  int y = 0;

   matadd(new_n, new_n, P[0], new_n, P[4], new_n, T);
   matadd(new_n, new_n, P[2], new_n, P[6], new_n, U);
   matsub(new_n, new_n, T, new_n, U, new_n, zBottomRight);

   for(int i = new_n; i < n; i++)
  {
    for(int j = 0; j < new_n; j++)
    {
      Z[i*Zpitch + j + new_n] = zBottomRight[new_n*y + j];
    }
    y++;
  }

   ////////////////////////////////////////////////////////////////////////////////

  /* TODO: Gecici pointerlar U ve T'yi free() edin */

  free(U); 
  free(T); 

  /* TODO: P[] dizisindeki bellek alanlarini free() edin */
    for (int i = 0; i < 7; i++)
    {
        free(P[i]);
    }
}

