/*
 * main.c
 *
 *  Created on: Mar 28, 2019
 *      Author: Merve Unlu
 */
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"name.h"

int main(int argc,char* argv[]){
    clock_t t,start;
    double time_taken;

    char* fname="TP08names.txt";
    char* vname="TP08values.txt";
    char* token="Blancha"; // Atamayi degistirebilirsiniz.

    struct dbName* dname ;
    dname = malloc(sizeof(struct dbName));
    read_name_file(dname,fname);
    read_value_file(dname,vname);
    //print_db(*dname);

    // Zamanlayici baslatiliyor.
    start = clock();
    printf("%d\n",search_uniform(*dname,token));
    // gecen zaman hesabi yapiliyor.
    t = clock() - start;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Dogrusal arama %f saniyede tamamladi.\n",time_taken);

    // Zamanlayici baslatiliyor.
    start = clock();
    printf("%d\n",search_binary(*dname,token));
    // gecen zaman hesabi yapiliyor.
    t = clock() - start;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("İkili arama %f saniyede tamamladi.\n",time_taken);

    start = clock();
    printf("%d\n",search_binary(*dname,"Janeen"));
    t = clock() - start;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Binary search takes %f second to run\n",time_taken);

    struct dbName* dGood = malloc(sizeof(struct dbName));
    dGood->currentSize = 0 ;
    struct dbName* dBad = malloc(sizeof(struct dbName));
    dBad->currentSize = 0 ;

    split_names(dname,dGood,dBad);
    printf("Good\n");
    print_db(*dGood);
    printf("Bad\n");
    print_db(*dBad);

    printf("%d\n",search_good_bad(*dGood, *dBad,"Karlyn"));
    printf("%d\n",search_good_bad(*dGood, *dBad,"Kerrill"));
    printf("%d\n",search_good_bad(*dGood, *dBad,"Marjie"));
    return 0 ;
}
