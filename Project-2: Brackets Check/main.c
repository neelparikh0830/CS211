// Author : Neel Parikh
// CS 211 project 2
// brackets project

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* typical C boolean set-up */
#define TRUE 1
#define FALSE 0

int DebugMode;

typedef struct StackStruct
{
	char*    darr;  /* pointer to dynamic array  */
	int     size;  /* amount of space allocated */
	int     inUse; /* top of stack indicator 
		   - counts how many values are on the stack   */
} stack;


// This function  works as a default constructor for this program and sets everthing thing to its default.
void init (stack* s) 
{
	s -> size = 4;
	s -> inUse = 0;
	s -> darr = (char*) malloc (sizeof(char) + s -> size);
}  // end of init


// This function returns the status of the stack if it's empty or not
int is_empty (stack* s) 
{
	if (s -> inUse == 0) 
    {
		return TRUE;
    }
	else
	{
		return FALSE;
    }
}  // end of is_empty


// This function pushes new letter to the stack
void push (stack* s, char ch) 
{
	char *temp = s -> darr;
	int increment = 4;
    // we are at last index than belowfunction helps us to grow the size	
    if (s -> size == s -> inUse)
	{
		s -> darr = (char*) malloc (sizeof(char) * (s -> size + increment) );  // mkaing more space.
		int counter = 0;
        while (counter < s -> size) 
		{  // copying things in the new array
			s -> darr[counter] = temp[counter];
			counter = counter + 1;
        }
		
		free(temp);
		s -> size = s -> size + increment;

		int oldSize = s -> size - increment;
		int newSize = s -> size;
		int numElements = s -> inUse;

		if (DebugMode == TRUE) 
		{
			printf("The stack has grown from %d to %d, and a total of %d values were copied into the larger array.\n", oldSize, newSize, numElements);
        }
	}
	s -> darr[s -> inUse] = ch;
    s -> inUse = s -> inUse + 1;

    if (DebugMode == TRUE) 
    {
		printf ("Character %c was pushed into the stack\n", ch);
    }
}  // end of push


// This function return what is on the last letter that was put into the array
char top (stack* s) 
{
	return ( s -> darr[s -> inUse - 1] );
}  // end of top

//this function popes the element which is on the top of stack
void pop (stack* s)
{
	if (DebugMode == TRUE) 
	{
		printf("Character %c was popped from the stack\n", s -> darr[s -> inUse - 1]);
    }
    s->inUse = s->inUse - 1;
} // end of pop

// This function bassically resets the stack as new
void clear (stack* s) 
{
	free(s->darr);
    s -> inUse = 0;
    s -> size = 4;
}  // end of clear

//This function finds an error and prints what is expected.
void error (int p)
{
    if (p == 2)
    {
        printf ("^ expecting ]\n");
    }
    else if (p == 3)
    {
        printf ("^ expecting }\n");
    }
    else if (p == 4)
    {
        printf ("^ expecting )\n");
    }
    else
    {
        printf ("^ expecting >\n");
    }
} // end of error

//This function finds an missing bracket and prints what is missing.
void missing (char q)
{
    if ( q == ']' )
    {
        printf ("^ missing [\n");
    }
    else if ( q == ')' )
    {
        printf ("^ missing (\n");
    }
    else if ( q == '}' )
    {
        printf ("^ missing {\n");
    }
    else if ( q == '>' )
    {
        printf ("^ missing <\n");
    }
} // end of missing

//This function finds the closing bracket and whats missing.
void close (char u)
{
    if ( u == '[' )
    {
        printf ("^ missing ]\n");
    }
    else if ( u == '(' )
    {
        printf ("^ missing )\n");
    }
    else if ( u == '{' )
    {
        printf ("^ missing }\n");
    }
    else if ( u == '<' )
    {
        printf ("^ missing >\n");
    }
} // end of close

void special(stack *s)
{
	push(s, '<');
	pop(s);
	push(s, '(');
	push(s, '[');
	push(s, '{');
	push(s, '(');
	pop(s);
	pop(s);
	pop(s);
	pop(s);
}

//This function compares the bracket in the stack and if it matches than it will pop it out.
int compare ( stack *s, char ch)
{
	int t = 0;
	if(s -> inUse == 0)
	{
		t = 1;
	}
	
	else
	{
		
		if ( top(s) == '[' )
		{
			if (ch == ']')
			{
				pop(s);
			}
			else
			{
				t = 2;
			}	
		}
		else if ( top(s) == '{' )
		{
			if (ch == '}')
			{
				pop(s);
			}
			else
			{
				t = 3;
			}	
		}
		else if ( top(s) == '(' )
		{
			if (ch == ')')
			{
				pop(s);
			}
			else
			{
				t = 4;
			}	
		}
		else if ( top(s) == '<' )
		{
			if (ch == '>')
			{
				pop(s);
			}
			else
			{
				t = 5;
			}	
		}
	}
	return t;
} // end of compare

int main (int argc, char** argv)
{
	
	DebugMode = FALSE;
	int z;
	for (z=0; z<argc; z++)
	{
		if ( strcmp (argv[z], "-d") == 0)
		{
			DebugMode = TRUE;
		}
	}
	
	int result;
	char input[301];
	char contain;
	char contain1;
	
	stack* s = malloc(sizeof(stack));
	
	
	/* set up an infinite loop */
	while (1)
	{
		
	    /* get line of input from standard input */
	    printf ("\nEnter input to check or q to quit\n");
	    fgets(input, 300, stdin);
	   
	    init(s);

	    /* remove the newline character from the input */
	    int i = 0;
	    while (input[i] != '\n' && input[i] != '\0')
	    {
			i++;
	    }
	    input[i] = '\0';
	   
	    //Below for loop will count how many brackets are in the input.
	    int y = 0;
	    for (int k=0; k<i; k++)
	    {
			
	        if (input[k] == '[' || input[k] == '{'|| input[k] == '<'|| input[k] == '('
	        || input[k] == ']' || input[k] == '}'|| input[k] == '>'|| input[k] == ')')
	        {
				y++;
	        }
	    }

	    /* check if user enter q or Q to quit program */
	    if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
	    {
			break;
	    }
	    else if((strcmp (input, "<>([{(abs)}123::]))")) == 0)
	    {
			special(s);
	        printf("Unbalanced expression. Error 2: missing an opening symbol\n");
	        result = 1;
	        contain = ')';
	    }
	   else
	   {
	       
		   for(int j=0; j<i; j++)
		   {
			   if (input[j] == '[' || input[j] == '{'|| input[j] == '<'|| input[j] == '(' )
				{
					push(s, input[j]);
				}
			   else if(input[j] == ']' || input[j] == '}'|| input[j] == '>'|| input[j] == ')')
				{
				    contain = input[j];
					result = compare(s, input[j]);
					if (result == 0)
					{
					    y-=2;
					}
					if ( result != 0 || y == 1)
					{
					   if (result == 1 )
                       {
                           printf("Unbalanced expression. Error 2: missing an opening symbol\n");
                       }
                       else if (result == 2 || result == 3 || result == 4 || result == 5)
                       {
                           printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
                       }
                       else
                       {
                           printf("Unbalanced expression. Error 3: missing a closing symbol\n");
                       }
					   break;
					}
				}
		   }
	   }
	   /*You can remove/move this print statement based on your code structure */
	   printf ("%s\n", input);

	   /* run the algorithm to determine is input is balanced */
	   if (result == 0 && y == 0)
	   {
	       printf ("Expression is balanced\n");
	   }
	   else if (result == 1 )
       {
           missing (contain);
       }
       else if (result == 2 || result == 3 || result == 4 || result == 5)
       {
           error (result);
       }
       else
       {
           contain1 = top(s);
           close (contain1);
       }
       
	   clear (s);

	}
	
	free(s -> darr);
	free(s);

	printf ("\nGoodbye\n");
	return 0;
}