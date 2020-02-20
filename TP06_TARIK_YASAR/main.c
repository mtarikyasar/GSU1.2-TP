/*
 * main.c
 *
 *  Created on: Mar 14, 2019
 *      Author: Merve Unlu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "stack.h"
#include "rpn.h"

#define LINE_MAX 10

int main(int argc, char *argv[])
{
	/*
	 * Hesaplanmasi icin bir tanim degerini
	 * kullanicidan alir ve daha once tanimli
	 * fonksiyonlari cagirip hesaplar.
	 * Kullanici sistemden cikis yapmak icin exit yazip Enter a basmalidir.
	 */
	int continuing = 1;
	char line[LINE_MAX];
	
	double result;
	
        // Alistirma 1.f
        // stack.c yazdiginiz fonksiyonlari test edin.

		/////////////////// TEST FIELD ///////////////
		/*
		struct stackNode *newStack = malloc(sizeof(struct stackNode));
		if (newStack == NULL)
	{
		printf("MALLOC ERROR!!!\n");
	}
		int x, y;
		printf("Enter two numbers: ");
		scanf("%d %d", &x, &y);

		stack_push(&newStack, x);
		stack_push(&newStack, y);

		if (is_empty(newStack) != 0)
		{
			printf("Stack is empty!\n");
		}

		stack_print(newStack);
		printf("%f\n", stack_pop(&newStack));
		stack_print(newStack);
		printf("%f\n", stack_pop(&newStack));
		stack_print(newStack);
		*/


        // Alistirma 2.b yi tamamladiktan sonra alttaki satiri 
        // yorumdan cikarip test yapabilirsiniz.
        // Alistirma 2.c
        rpn_test_evaluate_RPN();

	    struct stackNode *stack = NULL;

	    printf("RPN Hesap Makinesi\nCikis icin exit yazip ENTER'a basin\n\n");

            // Alistirma 3   
	    		while(1){
	    			printf("Enter an equation: ");
	    			scanf("%s", line);
	    			if (!strcmp(line, "exit"))
	    			{
	    				printf("Exiting the program...\n");
	    				break;
	    			}
	    			else{
	    					result = evaluate_RPN(line, &stack);
	    					printf("Result of entered equation is: %.2lf\n", result);

	    			}

	    		}
	    		stack_free(&stack);


	    printf("Hesaplama isleminden cikildi.\n");
return 0;
}
