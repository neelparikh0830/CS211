// Author: Neel Parikh
// UIC CS 211 spring 2021
// Project 3: Maze Path Finder

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* This program will read the count 3 lines of input 
   and prints a static 2D maze*/

typedef struct mazeStruct
{
	char arr[32][32];  /* allows for a maze of size 30x30 plus outer walls */
	bool visited[32][32];
	int xsize, ysize;
	int xstart, ystart;
	int xend, yend;
} maze;

typedef struct nodeStruct
{
    int x;
    int y;
    struct nodeStruct *next;
} Node;

typedef struct stackStruct
{
    Node *head;
} stack;

stack *init()
{
  stack *Orig = (stack*)malloc(sizeof(stack));
  Orig->head = NULL;
  return Orig;
}
bool isEmpty(stack *s)
{
  if (s->head != NULL) 
  {
    return false;
  }
  else 
  {
    return true;
  }
}

void pop(stack *s, bool debugMode)
{
  if (s->head == NULL)
  {
    return;
  }
  Node *garbage = s->head;
  s->head = s->head->next;
  int xgarbage = garbage->x;
  int ygarbage = garbage->y;
  free(garbage);
  if(debugMode == true)
  {
    printf("(%d,%d) popped off the stack.\n", xgarbage, ygarbage);
  }
}

void push(stack *s, Node *node, bool debugMode)
{
	if (s->head == NULL)
	{
		;
	}
	else 
	{
		node->next = s->head;
	}
	s->head = node;
	int xpush = s->head->x;
	int ypush = s->head->y;
	if (debugMode == true) 
	{
		printf("(%d,%d) pushed into the stack.\n", xpush, ypush);
	}
}

Node *build(int x, int y)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->x = x;
	newNode->y = y;
	newNode->next = NULL;
	return newNode;
}

void reset(stack *s, bool debugMode)
{
	Node *old = NULL;
	Node *curr = s->head;
	while(curr != NULL) 
	{
		old = curr;
		curr = curr->next;
		int xprev = old->x;
		int yprev = old->y;
		free(old);
		if (debugMode == true) 
		{
			printf("(%d,%d) popped off the stack.\n", xprev, yprev);
		}
	}
	s->head = NULL;
}

void correct(maze m1, int xpos, int ypos)
{
	if ((m1.xstart == xpos && m1.ystart == ypos) || (m1.xend == xpos && m1.yend == ypos))
	{
		printf("Invalid coordinates: attempting to block start/end position.\n");
	}
	if ((xpos > m1.xsize) || (ypos > m1.ysize))
	{
		printf("Invalid coordinates: outside of maze range.\n");
    }
}

bool isPresent(maze m1, int x, int y)
{
    if ((m1.arr[x][y] != '*') && (m1.visited[x][y] != true))
    {
        return true;
    }
    else 
    {
        return false;
    }
}

int reversePrint(Node *first)
{
	if (first != NULL)
	{
		reversePrint(first->next);
		printf("(%i,%i) ", first->x, first->y);
		return 0;
	}
	else
	{
		return 0;
	}
}

void search(maze m1, stack *s, int debugMode)
{
	int count = 0;
    bool star = false;
    Node *first = build(m1.xstart, m1.ystart);
    push(s, first, debugMode);
    m1.visited[m1.xstart][m1.ystart] = true;
    

    while(!isEmpty(s) && !star)
    {
		Node *topNode = (s->head);
        if(topNode->x == m1.xend && topNode->y == m1.yend)
        {
			printf("\n");
            printf("The maze has a solution.\n");
            star = true;
        }
        else if(isPresent(m1, topNode->x + 1, topNode->y))  // down
        {
            Node *newNode = build(topNode->x+ 1, topNode->y);
            push(s, newNode,debugMode);
            if (m1.arr[newNode->x][newNode->y] == 'C') 
			{
				count++;
            }
            m1.visited[newNode->x][newNode->y] = true;
        }
        else if(isPresent(m1, topNode->x, topNode->y +1 ))  // right
        {
            Node *newNode = build(topNode->x, topNode->y+1);
            push(s, newNode,debugMode);
            if (m1.arr[newNode->x][newNode->y] == 'C') 
			{
				count++;
            }
            m1.visited[newNode->x][newNode->y] = true;
        }
        else if(isPresent(m1, topNode->x - 1, topNode->y))  // up
        {
            Node *newNode = build(topNode->x - 1, topNode->y);
            push(s, newNode,debugMode);
            if (m1.arr[newNode->x][newNode->y] == 'C') 
			{
				count++;
            }
            m1.visited[newNode->x][newNode->y] = true; 
        }
        else if(isPresent(m1, topNode->x, topNode->y - 1))  // left
        {
            Node *newNode = build(topNode->x, topNode->y - 1);
            push(s, newNode,debugMode);
            if (m1.arr[newNode->x][newNode->y] == 'C') 
			{
				count++;
            }
            m1.visited[newNode->x][newNode->y] = true;
        }
        else 
        {
            pop(s, debugMode);
        }

    }

    if (!isEmpty(s) || star) 
	{
		printf("The amount of coins collected: %d\n", count);
		printf("The path from start to end: \n");
    } 
	else 
	{
		printf("This maze has no solution.\n");
    }
}

int main (int argc, char **argv)
{
	maze m1;
	stack *s = init();
	int xpos, ypos;
	int i,j;
	int posFile = 0;
	bool debugMode = false;
	char nike;
	FILE *src;
	
	/* verify the proper number of command line arguments were given */
	
	if(argc < 2) 
	{
		printf("Usage: %s <input file name>\n", argv[0]);
		exit(-1);
	}
	else if (argc == 2 || argc == 3) 
	{
		if (argc == 2)
		{
			posFile = 1;
		}
		else
		{
			debugMode = true;
			if(strcmp(argv[1],"-d")==0)
			{
				posFile = 2;
			}
			else if(strcmp(argv[2],"-d")==0)
			{
				posFile = 1;
			}
		}
	}
	else
	{
		printf("Too many arguments!\n");
		exit(-1);
	}
   
	/* Try to open the input file. */
	if ( ( src = fopen( argv[posFile], "r" )) == NULL )
	{
		printf ( "Can't open input file: %s", argv[1] );
		exit(-1);
	}
	

	/* read in the size, starting and ending positions in the maze */
	if ((fscanf (src, "%d %d", &m1.xsize, &m1.ysize) == EOF) ||  (fscanf (src, "%d %d", &m1.xstart, &m1.ystart) == EOF)
		|| (fscanf (src, "%d %d", &m1.xend, &m1.yend) == EOF))
	{
		printf("Invalid data file.\n");
		exit(-1);
	}
	/* print them out to verify the input */
	if ((m1.xsize <= 0 || m1.ysize <= 0) || (m1.xstart > m1.xsize || m1.ystart > m1.ysize) || (m1.xend > m1.xsize || m1.yend > m1.ysize))
	{
		if (m1.xsize <= 0 || m1.ysize <= 0) 
		{
			printf("Maze sizes must be greater than 0.\n");
			exit(-1);
		}
		else if (m1.xstart > m1.xsize || m1.ystart > m1.ysize)
		{
			printf ("size: %d, %d\n", m1.xsize, m1.ysize);
			printf("Start/End position outside of maze range.\n");
			exit(-1);
		}
		else
		{
			printf ("size: %d, %d\n", m1.xsize, m1.ysize);
			printf ("start: %d, %d\n", m1.xstart, m1.ystart);
			printf("Start/End position outside of maze range.\n");
			exit(-1);
		}	
	}
	else
	{
		printf ("size: %d, %d\n", m1.xsize, m1.ysize);
		printf ("start: %d, %d\n", m1.xstart, m1.ystart);
		printf ("end: %d, %d\n", m1.xend, m1.yend);
	}

	/* initialize the maze to empty */
	for (i = 0; i < m1.xsize+2; i++)
	{
		for (j = 0; j < m1.ysize+2; j++)
		{
			m1.arr[i][j] = '.';
		}
	}

	/* mark the borders of the maze with *'s */
	for (i=0; i < m1.xsize+2; i++)
    {
		m1.arr[i][0] = '*';
		m1.arr[i][m1.ysize+1] = '*';
    }
	for (i=0; i < m1.ysize+2; i++)
    {
		m1.arr[0][i] = '*';
		m1.arr[m1.xsize+1][i] = '*';
    }

	/* mark the starting and ending positions in the maze */
	m1.arr[m1.xstart][m1.ystart] = 's';
	m1.arr[m1.xend][m1.yend] = 'e';
		  
	/*This code will only read the count three lines */
	/*Complete this code by reading the rest of the input
    and placing blocked and coin positions. */
	/* Blocked positions are marked with 'b' in the input file	
    They should be marked by * in the maze */

	/*Coin positions are marked by 'c' in the input file
    They should be marked by C in the maze*/
	
	while (fscanf (src, "%d %d %c", &xpos, &ypos, &nike) != EOF) 
	{
		if (nike == 'c' || nike == 'b') 
		{
			correct(m1, xpos, ypos);
			if (m1.xstart != xpos || m1.ystart != ypos)
			{
				if (m1.xend != xpos || m1.yend != ypos)
				{
					if (nike == 'b') 
					{			
						m1.arr[xpos][ypos] = '*';
					}
					else
					{
						m1.arr[xpos][ypos] = 'C';
					}
				}
			}
		}
		else
		{
			printf("Invalid type: type is not recognized.\n");
		}
	}
	
	/*Close the file*/
	fclose(src);

	/* print out the initial maze */
	for (i = 0; i < m1.xsize+2; i++)
    {
		for (j = 0; j < m1.ysize+2; j++)
		{
			printf ("%c", m1.arr[i][j]);
		}
		printf("\n");
    }
	
	search(m1, s, debugMode);
	Node* oldHead = s->head;
	reversePrint(oldHead);
	printf("\n");
	reset(s,debugMode);
	free(s);
}
