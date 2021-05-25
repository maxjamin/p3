#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
/* Created by: Ben Smith
 * Class: CS3060 X01 summer 2021 B1
 * Assignment: Project 3
 */
#define MAX_NUMBER_OF_FACTORS 1000000
#define MAX_NUMBER_OF_NUMBERS 25

typedef struct Number_of_factors 
{
	int base_number;
	int prime_factors[MAX_NUMBER_OF_FACTORS];
	int sizeof_array;

} Number_of_factors;

int trial_divison(void *number_of_factors)
{
	if(number_of_factors)
	{
		Number_of_factors * ptr = (struct Number_of_factors *)
									number_of_factors;	
		int factor = 2;
		int number = ptr->base_number;
		//printf("Base %d\n", number );
		while(number > 1)
		{
			if(number % factor == 0)
			{
				(*ptr).prime_factors[(*ptr).sizeof_array] = factor;
				(*ptr).sizeof_array++;

				number /= factor;
			}
			else
				factor++;
		}
		return 0;
	}
}

void *find_prime_factors(void *number_of_factors)
{
	if(number_of_factors)
	{

		Number_of_factors * ptr = (struct Number_of_factors *) number_of_factors;
		trial_divison(ptr);

	}
	return NULL;
}

int main(int argc, char * const argv[])
{
	/*Allocate members of input numbers */
	Number_of_factors  *factors[argc];
	pthread_t thread_array[argc];

	if(argc <= 1)
	{
		printf("Usage:./p3 <number to factor>...\n");
		return 1;
	}

	for(int i=0; (i < MAX_NUMBER_OF_NUMBERS) && (i < argc-1); i++)
	{
		factors[i] = calloc(1, sizeof(Number_of_factors));
		factors[i]->base_number = atoi(argv[i+1]);
		factors[i]->sizeof_array = 0;

		pthread_create(&thread_array[i]
					, NULL
					, find_prime_factors
					, (void*) factors[i]);
	}

	//printf("# off args %d\n", argc);

	/*wait for threads to finish*/
	for(int i=0; (i < MAX_NUMBER_OF_NUMBERS) && (i < argc-1); i++)
	{
		pthread_join(thread_array[i], NULL);
	}

	for(int i=0; (i < MAX_NUMBER_OF_NUMBERS) && (i < argc-1); i++)
	{
		printf("%d: ",  factors[i]->base_number);
		for(int array_index = 0; array_index < factors[i]->sizeof_array; array_index++)
		{
			printf("%d ", factors[i]->prime_factors[array_index] );
		}
		printf("\n");
	}



	/*Delete allocated memory*/
	for(int i=0; (i < MAX_NUMBER_OF_NUMBERS) && (i < argc-1); i++)
		free(factors[i]);
	
}