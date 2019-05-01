/*************************************
 * Shell Sort
 ************************************/

void shell_sort(int *array, int size) {
  /* Sedgewick tarafindan belirlenen gap serisi */
  int gaps[] = {4193, 1073, 281, 77, 23, 8, 1};
  int i, j, k;
  /*TODO*/
  int sizeGaps = sizeof(gaps)/sizeof(int);

  int h, v;
  for(i = 0; i<sizeGaps; i++){
      h = gaps[i];

      for(j=h; j<size; j++){
        v=array[j];
        k = j;
        while(k>=h && array[k-h]>v){
          array[k] = array[k-h];
          k = k-h;
        }
        array[k] = v;
      }
  }
}

void ciura_shell_sort(int *array, int size) {
  /* Ciura tarafindan belirlenen gap serisi */
  int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
  int i, j, k;

  /*TODO*/
  int sizeGaps = sizeof(gaps)/sizeof(int);

  int h, v;
  for(i = 0; i<sizeGaps; i++){
      h = gaps[i];

      for(j=h; j<size; j++){
        v=array[j];
        k = j;
        while(k>=h && array[k-h]>v){
          array[k] = array[k-h];
          k = k-h;
        }
        array[k] = v;
      }
  }
}


