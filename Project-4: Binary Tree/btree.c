#include "header.h"

/* print a binary tree while performing an Preorder traversal.
Recall preorder traversal:
visit parent
visit left subtree
visit right subtree
you MUST use recursion */

void printPrefix(node* r)
{
    if (r == NULL)
    {
        return;
    }
    printf(" %s ", r->val);
    printPrefix(r->left);
    printPrefix(r->right);
}

void printPostfix(node* r)
{
    if ( r == NULL)
    {
    return;
    }
    printPostfix(r->left);
    printPostfix(r->right);
    printf(" %s ", r->val);
}

/*print a binary tree while performing an Inorder traversal.
Recall inorder traversal:
visit left subtree
visit parent
visit right subtree
you MUST use recursion */

void printInfix(node* r)
{
    if (r == NULL)
    {
        return;
    }
	if(strcmp(r->val, "+") == 0|| strcmp(r->val, "-") == 0 || strcmp(r->val, "*") == 0 || strcmp(r->val, "/") == 0)
	{
		printf("(");
	}
    printInfix(r->left);
    printf(" %s ", r->val);
    printInfix(r->right);
	if(strcmp(r->val, "+") == 0 || strcmp(r->val, "-") == 0 || strcmp(r->val, "*") == 0|| strcmp(r->val, "/") == 0)
	{
	  printf(")");
	}
}

/*
  clear a binary tree. Perform a recursive traversal of a
  tree destroying all nodes.
*/

void clearTree(node* root)
{
	if (root == NULL)
	{
		return;
	}		
	clearTree(root->left);
    clearTree(root->right);
    free(root);
    /*if (root != NULL)
    {
       clearTree(root->left);
       clearTree(root->right);
       free(root);
    }
    else
    {
       return;
    }*/
}

 
void parse(char* s, stack* stack, node **root) // 2 digits for 1 operaotr // by the end of the while one thing on the stack
{
    char* token = strtok(s, " ");
	int count = 0;
    while(token != NULL) // 1000 + 20
    {
		if(isdigit(token[0]))
		{
				node* tree = (node*)malloc(sizeof(node)); // null
				tree->val = token; //1000 is a string
				tree->right = NULL;
				tree->left = NULL; // 
				push(stack, tree); // pushed in stack
		}
		else
		{
				// + - / *
			node* tree = (node*)malloc(sizeof(node));
			tree->val = token; // 1000 + 20 //
			tree->right = top(stack);
			pop(stack);
			tree->left = top(stack);
			/*if(isEmpty(stack) == 1)
			{
			   clearTree(tree);
			  //clearStack(stack);
			  printf("Invalid expression. Enter a valid postfix expression \n");
			}*/
			//else
			//{
			  pop(stack);
			  push(stack, tree); // str // (20)<-(+) -> (100)
			//}
		}
		count++;
			token = strtok (NULL, " ");
    }
	*root = top(stack);
	 pop(stack);
	/* if(isdigit((*root)->val[0]))
	 {
		 clearTree(*root);
		 printf("Invalid expression. Enter a valid postfix expression \n");
	 }*/
	 if(isEmpty(stack) != 1 || count == 1)
	 {
		*root = NULL;
	 }
	 


	
}
int evalExpression(node* root)
{
	int result; // return
	int left_sum = 0;
	int right_sum = 0;
	/*if(atoi(root->val) != 0)
	{
		return atoi(root->val);
	}*/
	if(root == NULL) return 0;
	if(root->left == NULL && root->right == NULL)
	{
		return atoi(root->val);
	}
	else
	{
		left_sum = evalExpression(root->left);
		right_sum = evalExpression(root->right);
		if(strcmp(root->val, "+") == 0)
		{
			result = left_sum + right_sum;
		}
		else if(strcmp(root->val, "-") == 0)
		{
			result = left_sum - right_sum;
		}
		else if(strcmp(root->val, "*") == 0)
		{
			result = left_sum * right_sum;
		}
		else if(strcmp(root->val, "/") == 0)
		{
			result = left_sum / right_sum;
		}
	}
	return result;
	
}

void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("or any postfix mathematical expression using operators of *, /, +, -\n");
}