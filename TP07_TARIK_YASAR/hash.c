#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include"hash.h"
#define MULTIPLIER 31 

/* Stringler icin basit bir hash hesaplama fonksiyonu.
 * Her harfin ASCII degeri, onceki hash degerinin bir
 * carpanina ekleniyor.
 * Ornegin: "abcde" stringi icin:
 * ascii degerleri : a=97, b=98,c=99,d=100,e=101 
 *  h0 = 0 * 31 + 97 = 97
 *  h1 = h0 * 31 + 98 = 3105
 *  h2 = h1 * 31 + 99 = 96354
 *  h3 = h2 * 31 + 100 = 2987074
 *  h4 = h3 * 31 + 101 = 92599395
 *  92599395 % MAXBUCKETS (1000) = 395
 */
unsigned long hash_compute(const char *str){
  unsigned long hash = 0;
  while(*str){
    hash = (hash*MULTIPLIER) + *str;
    ++str;
  }
  return hash % MAXBUCKETS;
}

/* Her elemani bir bagli liste gostericisi olan table
 * dizisi parametre olarak veriliyor. Bu table dizisi
 * aslinda hash veriyapisini temsil eder.
 *
 * str ile verilen string hash'te var ise adresi
 * dondurulur. Yoksa ve create == 1 ise, hash
 * veriyapisina bu string eklenir.
*/
Key* hash_lookup(Key **table,const char *str,int create){
  // Alistirma 1
  //  str icin hash fonksiyonu cagirin
  
  unsigned long hash = hash_compute(str);
  Key *node = table[hash];
  Key* cur = node;

  // table hash tablosunda degeri arayin
  // deger bulunursa o degiskeni geri dondurun.
  // deger yoksa ve ekleme yapilacaksa

  while(cur != NULL){
    if (strcmp(cur->word, str) == 0)
    {
      return cur;
    }
    cur = cur->next;
  }
    
  if(create){
    // Hafizada eklenecek deger icin yer acin
    // hafizada yer acildiysa  
    // yeni eleman icin count,word,next atamalari yapin
    // yeni eklenen elemani geri dondurun
    Key *newNode = malloc(sizeof(Key));

    newNode->count = 0;
    newNode->word = strdup(str);
    table[hash] = newNode;
    newNode->next = node;
    return newNode;
   }
 

  return NULL;
}


/* Verilen hash tablosunda aynı  
 * hash koda sahip kac tane kelime olduğunu  
 * geri döndürür. 
*/
int hash_count_word(Key **table,const char *str){
  int cnt = 0;
  // Alistirma 2
    unsigned long hash = hash_compute(str);
    unsigned long ctrlHash;

    Key *node = table[hash];
    Key *cur = node;

    while(cur != NULL){
      ctrlHash = hash_compute(cur->word);
        if (ctrlHash == hash)
        {
          cnt++;
        }
      cur = cur->next;
    }

    return cnt;
}

/* Verilen hash tablosunda aynı  
 * hash koda sahip kelimeleri ekrana basar. 
*/
void hash_same_code(Key **table,const char *str){
  // Alistirma 3
  unsigned long hash = hash_compute(str);
    unsigned long ctrlHash;

    Key *node = table[hash];
    Key *cur = node;

    while(cur != NULL){
      ctrlHash = hash_compute(cur->word);
        if (ctrlHash == hash)
        {
          printf("%s: ", cur->word);
          printf("%lu\n", hash_compute(cur->word));
        }
      cur = cur->next;
    }
}

/* count parametresi >= n olan kelimeleri ekrana
 * yazdiran fonksiyon. Ekrana yazdirirken
 * "%30s-->%5ld\n" formatini kullaniyor.
 * %ld: unsigned long icin gerekiyor.
*/
void hash_dump(Key **table,int n){
  Key *k;
  int i;
  for(i=0;i<MAXBUCKETS;++i){
    for(k=table[i];k!=NULL;k=k->next){
      if(k->count<=n){
	printf("%30s --> %5ld\n",k->word,k->count);
       }
     }
  }
}

/* table ile verilen hash veriyapisini
 * isletim sistemine iade eden fonksiyon.
 * Temizlerken, her bagli listenin dugumlerini
 * ve bu dugumlerdeki "word" uyesini free()
 * etmeniz gerekiyor.
*/
void hash_free(Key **table){
  // Alistirma 6

  /* NOT: NASIL FREE ETMEM GEREKTIGINI ANLAMADIGIM 
          ICIN BU FONKSIYONU BOS BIRAKTIM */

 /* for (int i = 0; i < MAXBUCKETS; i++)
  {
    for (; table != NULL; table = table->next)
    {
        free(table->word);

    }
  }
  */

}





