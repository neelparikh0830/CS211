/*
 * Author: Neel Parikh
 * UIC Spring 2021
 * Sorting Project
*/



#include <stdio.h>
#include <stdlib.h>

void myFavoriteSort(int arr[], int size)
{
	int length = size - 1;
	int temp;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < (length - i); j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
// end of myFavoriteSort

// This function will make a copy of the values from one array to another array.
void makeArrayCopy(int fromArray[], int toArray[], int size)
{
	for (int k = 0; k < size; k++)
	{
		toArray[k] = fromArray[k];
	}
}
// end of makeArrayCopy

// This function compares the sorted and unsorted array and returns the count that stayed at same position.
void indexComparison(int unsortedArray[], int sortedArray[], int size, int *counter)
{
	for (int l = 0; l < size; l++)
	{
		if (unsortedArray[l] == sortedArray[l])
		{
			*counter = *counter + 1;
		}
	}
}
// end of indexComparison

// This function takes in size, copied array, and target as its input and "returns" index values. 
// This function computates if a sum target is found. And if found then returns one as an indication.
int targetSum(int arr[], int size, int target, int *index1, int *index2)
{ 
	int found = 0;
    	int first = 0;
	int last = size - 1;
	while (first < last)
	{
		int totalSum = arr[first] + arr[last];

		if (totalSum > target)
		{
			last--;
		}
		else if (totalSum == target)
		{
			*index1 = first;
			*index2 = last;
            		found++;
            		break;
		}
		else
		{
			first++;
		}
	}
	return found;
}	
// end of targetSum

int main(int argc, char **argv)
{
	int val;
	int userInput;
	int count = 0;
    	int sum = 0;

	/*prompt the user for input */
	printf("Enter in a list of numbers to be stored in a dynamic array.\n");
	printf("End the list with the terminal value of -999\n");

	int *arrFirst;	// for dynamic array
	int increase = 4;	// default size
	arrFirst = (int*) malloc(increase* sizeof(int));	// setting size of the array
	int arrSize = 0;
	/*loop until the user enters -999 */
	scanf("%d", &val);
	while (val != -999)
	{
		/*store the value into an array */
		if (arrSize == increase)
		{
			/*Code below is inspired from project 1 pdf. */

			int *var = arrFirst;
			arrFirst = (int*) malloc(increase *2* sizeof(int));	// making the array dynamic based on user requirements. (doubling)
			for (int i = 0; i < increase; i++)
			{
				arrFirst[i] = var[i];
			}

			free(var);
			
            		increase *= 2;
		}

		arrFirst[arrSize] = val;
		arrSize++;

		/*get next value */
		scanf("%d", &val);
	}

	int newArr[arrSize];
	/*call function to make a copy of the array of values */
	makeArrayCopy(arrFirst, newArr, arrSize);
	/*call function to sort one of the arrays */
	myFavoriteSort(newArr, arrSize);

	// Uncomment the lines below to prints the original and sorted array
	// Had this for debugging purposes. 

	/*Prompt user to enter a value to pick a task */
	printf("Enter 1 to perform index comparison, enter 2 to perform target sum.\n");
	scanf("%d", &userInput);
    
    while (userInput != 1 && userInput != 2)
    {
        printf("Invalid input. Enter 1 or 2.\n");
        scanf("%d", &userInput);
    }

	
    	if (userInput == 1)
    	{
    		indexComparison(arrFirst, newArr, arrSize, &count);
    		if (count != 0)
    		{
                	printf("%d values are in the same location in both arrays.\n", count);
    		}
    		else
    		{
    			printf("All elements change location in the sorted array.\n");
            	}
    	}
    	else
    	{
    		int positionFirst = 0;
    		int positionSecond = 0;
    
    		printf("Enter in a list of numbers to use for searching. \n");
    		printf("End the list with a terminal value of -999\n");
    		scanf("%d", &val);
    		while (val != -999)
    		{
    			//int sum = 0;
    			/*call function to perform target sum operation */
    			sum = targetSum(newArr, arrSize, val, &positionFirst, &positionSecond);
    			/*print out info about the target sum results  */
    			if (sum == 1)
    			{
    				printf("Success! Elements at indices %d and %d add up to %d\n", positionFirst, positionSecond, val);
    			}
    			else
    			{
    				printf("Target sum failed!\n");
    			}
    			/*get next value */
    			scanf("%d", &val);
    		}
    	}
	printf("Good bye\n");
    	free(arrFirst);
	return 0;
}