#include<stdlib.h>

void merge(int *array, int low, int middle, int high) {
  int i, j, k;

  /* TODO: Sol yarim listenin boyunu hesaplayin */

  int szLeftHalf = middle - low + 1;

  /* TODO: Sag yarim listenin boyunu hesaplayin */

  int szRightHalf = (high - middle);

  /* TODO: Sol ve sag yarim liste icin dizi tanimlayin */
  
  int arrLeftHalf[szLeftHalf];
  int arrRightHalf[szRightHalf];
  
  /* TODO: Sol yarim listeyi sinirlarina gore doldurun */

  for (size_t x = 0; x < szLeftHalf; x++)
  {
    arrLeftHalf[x] = array[low + x];
  }

  /* TODO: Sag yarim listeyi sinirlarina gore doldurun */

  for (size_t y = 0; y < szRightHalf; y++)
  {
    arrRightHalf[y] = array[middle + 1 + y];
  }
  
  /* TODO: Birlestirme: Sol ve sag yarim listeleri kendi aralarinda
   * karsilastirarak listenin ilgili yerine yerlestirin.
   * iki yarim listeden birinin sonuna gelindiginde donguden cikilmalidir. */
  i = 0;
  j = 0;
  k = low;

  while(i < szLeftHalf && j < szRightHalf)
  {
    if(arrLeftHalf[i] <= arrRightHalf[j])
    {
      array[k] = arrLeftHalf[i];
      i++;
    }
    else
    {
      array[k] = arrRightHalf[j];
      j++;
    } 
    k++;
  }
  
  /* TODO: Yarim listelerin tum elemanlari listenin ilgili yerine
   * sokulmadiysa, kalan elemanlari yerlestirin. */
    while(i < szLeftHalf)
    {
      array[k] = arrLeftHalf[i];
      i++;
      k++;
    }

    while(j < szRightHalf)
    {
      array[k] = arrRightHalf[j];
      j++;
      k++;
    }
}

/* Bolme ve birlestirme metodunu gerceklestiren fonksiyon */
void merge_sort(int *array, int low, int high) {
  /* Eger elde kalan liste tek elemanli degilse */
  if (low < high) {
     // TODO 
    /* Orta noktayi bul */
    int middle = low + (high-low)/2;
    /* Sol tarafi ozyinelemeli olarak sirala */
    merge_sort(array, low, middle);
    /* Sag tarafi ozyinelemeli olarak sirala */
    merge_sort(array, middle+1, high);
    /* Siralanmis listeleri birlestir */
    merge(array, low, middle, high);
  }
}

void merge_sort_wrapper(int *array, int size) {
  merge_sort(array, 0, size - 1);
}
