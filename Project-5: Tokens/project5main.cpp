#include "Infix.h"

void printCommands()
{
  printf ("The commands for this program are:\n\n");
  printf ("q - to quit the program\n");
  printf ("? - to list the accepted commands\n");
  printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

int eval(int &val1, int &val2, char &op)
{
  int returnVal = 0;
  if (op == '%' || op == '*' ) 
  {
    returnVal = (op == '%') ? (val1 % val2) : (val1 * val2);
    return returnVal;
  }
  else if (op == '/' || op == '+') 
  {
    returnVal = (op == '/') ? (val1 / val2) : (val1 + val2);
    return returnVal;
  }
  else if (op == '-') 
  {
    returnVal = val1 - val2;
    return returnVal;
  } 
  else 
  {
    printf("Invalid expression.\n");
    return -999;
  }
}

void popAndEval(myStack &numbers, myStack &operators) 
{
  char newOperator = (char)operators.top();
  operators.popStack();
  int val1, val2, val3;

  val2 = numbers.top();
  numbers.popStack();

  val1 = numbers.top();
  numbers.popStack();

  val3 = eval(val1, val2, newOperator);
  numbers.push(val3);
}

void processExpression (Token inputToken, TokenReader *tr)
{
	myStack values;  // stack that contains all the numbers from input.
	myStack ops;  // stack that contains all the operators from the input.
	int answer;
 /**********************************************/
 /* Declare both stack pointers here      */

 /* Loop until the expression reaches its End */
 if (values.isEmpty() && ops.isEmpty())
 {
	 
	 while (inputToken.equalsType(EOLN) == false)
	   {
		/* The expression contain a VALUE */
		if (inputToken.equalsType(VALUE))
		  {
			values.push(inputToken.getValue());  // add code to perform this operation here
		  }

		/* The expression contains an OPERATOR */
		else if (inputToken.equalsType(OPERATOR))
		{
			// add code to perform this operation here
			char ch = inputToken.getOperator();
			if (ch == '(') 
			{
			  ops.push(ch);
			}
			else if (ch == '*' || ch == '/' || ch == '%' || ch == '+' || ch == '-') 
			{
				if (ch == '*' || ch == '/' || ch == '%')
				{
				  while ( (!ops.isEmpty()) && ( (char)ops.top() == '*' || (char)ops.top() == '/' || (char)ops.top() == '%' ) ) 
				  {
					popAndEval(values, ops);
				  }
				  ops.push(ch);
				}
				else
				{
					while ( (!ops.isEmpty()) && (char)ops.top() != '(') 
					{
						popAndEval(values, ops);
					}
					ops.push(ch);
				}
			}
			else
			{
			  while ( (!ops.isEmpty()) && (char)ops.top() != '(' ) 
			  {
				popAndEval(values, ops);
			  }
			  if (ops.isEmpty()) 
			  {
				printf("Invalid Expression. \n");
				break;
			  } 
			  else 
			  {
				ops.popStack();
			  }
			}
		}

		/* get next token from input */
		inputToken = tr->getNextToken ();
	   }
	   
	    while (!ops.isEmpty()) 
		{
		  popAndEval(values, ops);
		}
		answer = values.top();
		values.popStack();
		//if (values.isEmpty() == false || ops.isEmpty() == false) ?  printf("Invalid Expression \n") : printf("\nExpression Result: %d \n", answer);
		if (!values.isEmpty()|| !ops.isEmpty())
		{
		  printf("\nInvalid Expression.\n");
		} 
		else 
		{
		  printf("\nExpression result: %d\n", answer);
		}
 }
 /* The expression has reached its end */

 // add code to perform this operation here

 printf ("\n");
 values.clear();
 ops.clear();
 
}

int main(int argc, char *argv[])
{
    /***************************************************************/
    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression:");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression:");
      inputToken = tr.getNextToken ();
    }

  printf ("\nQuitting Program\n");
  return 0;
}