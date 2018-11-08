#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Finds minimum values and return minimum
int min(int one, int two, int three)
{
	int min;
	if(one < two)
	{
		min = one;
	}
	else
	{
		min = two;
	}
	if(min > three)
	{
		min = three;
	}
	
	return min;
}

// Function to make distance table
int stringAlignment(char* string1, char* string2, int m, int n, int list[100][100])
{
	
	for(int i = 0; i <= m; i++)
	{
		for(int k = 0; k <= n; k++)
		{
			
			// Increment all values of first column since its compared to empty string
			if(i == 0)
			{
				list[i][k] = k;
			}
			
			// Increment first row of values since its compared to empty string
			else if(k == 0)
			{
				list[i][k] = i;
			}
		
			// If values are equal then subtract one from last value
			else if(string1[i-1] == string2[k-1])
			{
				list[i][k] = list[i-1][k-1];
			}
			
			// Else increment by one
			else
			{
				list[i][k] = 1 + min(list[i][k-1], list[i-1][k], list[i-1][k-1]);
			}
		}
	}
	return list[m][n];
} 

// Print table function
void print_table(char* string1, char* string2, int list[100][100])
{
	int count = 0;
	int count2 = 0;
	int size2 = strlen(string2)+1;
	int size1 = strlen(string1)+1;
	
	for(int i = 0; i < size2; i++)
	{
		for(int k = 0; k < size1; k++)
		{
			// Prints first three empty boxes
			if((i == 0 && k < 2) || (i == 1 && k == 0))
			{
				printf("   |");
			}
			
			// Prints out second word
			else if( i == 0 && k > 1)
			{
				printf("  %c|", string1[count]);
				count++;
			}
			
			// Prints out first word
			else if(k == 0 && i > 1)
			{
				printf("  %c|", string2[count2]);
				count2++;
			}
			
			// Prints out the table created by our distance function
			else
			{
				printf("  %d|", list[i -1][k-1]);
			}
		}
		
		printf("\n");
		//Prints out dashed line after every row
		for(int dots = 0; dots < (4*(size1)); dots++)
		{
			printf("_");
		}
		printf("\n");
		
	}
	
}

// Aligns our text of compared words
void print_alignment(int list[100][100], int len1, int len2, char *string1, char* string2)
{
	char string_temp1[100];
	char string_temp2[100];
	char edit_distance[100];
	int temp;
	int count1 = strlen(string1);
	int count2 = strlen(string2);
	int traverse_left = count2;
	int traverse_up = count1;
	int full_len;
	
	// Gets maximum length
	if(len1 > len2)
	{
		temp = len1;
	}
	else{
		temp = len2;
	}
	full_len = temp;
	
	// Runs until traversed through graph to origin
	while(1)
	{
		int minimum = min(list[count1][traverse_left-1], list[traverse_up-1][count2], list[traverse_up-1][traverse_left-1]);
		
		// Traverses diagonally
		if((minimum == list[traverse_up-1][traverse_left-1]) && ((traverse_left != 0) && (traverse_up != 0)))
		{
			string_temp1[temp] = string1[count1-1];
			string_temp2[temp] = string2[count2-1];
			traverse_left--;
			traverse_up--;
			count1--;
			count2--;
			temp--;
		}
		
		// Traverses left
		else if(minimum == list[traverse_up][traverse_left-1] && traverse_left != 0)
		{
			string_temp2[temp] = string2[count2-1];
			string_temp1[temp] = '-';
			traverse_left--;
			count2--;
			temp--;
		}
		
		// Traverses upward
		else
		{
			string_temp1[temp] = string1[count1-1];
			string_temp2[temp] = '-';
			traverse_up--;
			count1--;
			temp--;
		}
		
		// Checks if values reached original point
		if(traverse_left == 0 && traverse_up == 0)
		{
			break;
		}
	}
	
	// Prints out strings created with added skips
	for(int i  = 1;i < full_len; i++)
	{
		printf("%c ", string_temp1[i]);
	}
	printf("\n");
	for(int i  = 1;i < full_len; i++)
	{
		printf("%c ", string_temp2[i]);
	}
	printf("\n");
	
	// Prints out difference string
	for(int i = 1; i < full_len;i++)
	{
		if(string_temp1[i] == '-' || string_temp2[i] == '-' || string_temp1[i] != string_temp2[i])
		{
			printf("X ");
		}
		else{
			printf(". ");
		}
	}
	printf("\n\n");
}

int main(void)
{
	char string1[100];
	char string2[100];
	int edit_distance;
	char *check = "-1\n";
	
	// Loops until user enter -1
	while(1)
	{
		int list[100][100];
		
		printf("\n");
		printf("Enter first: ");
		fgets(string1, 100, stdin);
		
		printf("Enter second: ");
		fgets(string2, 100, stdin);
		
		// Checks if user wants to break out of function
		if((strcmp(check, string1) == 0) && (strcmp(check, string2) == 0))
		{
			break;
		}
		
		int len1 = strlen(string1) ;
		int len2 = strlen(string2) ;
		
		// Function calls
		edit_distance = stringAlignment(string1, string2, len1, len2, list);
		print_table(string2, string1, list);
		printf("\nEdit distance: %d\n", edit_distance);
		print_alignment(list, len1, len2, string1, string2);
	}
	return 1;
}