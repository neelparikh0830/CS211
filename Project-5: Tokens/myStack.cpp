#include "Infix.h"

//-----------------------------------------------------------------
// stack implementation
/*Default constructor that creates memeory on heap and initilize private variables.*/
myStack :: myStack() 
{
	size = 2;
    inUse = 0;
	stackArr = new int[size];
}
/*Checks if the stack is empty or filled up with numbers or operators.*/
bool myStack :: isEmpty() 
{
    if (inUse == 0) 
	{
        return true;
    } else 
	{
        return false;
    }
}
/*Clears all the sized memory from the heap for the stack.*/
void myStack :: clear() {
    delete [] stackArr;
}
/*Returns the numbers or operator that has been added at the last in the stack.*/
int myStack :: top() {
  if ((inUse - 1) < 0) {
    return -999;
  }
  else
  {
	return stackArr[inUse -1];
  }
}
/*This function deletes last elements that has been addedd to the stack*/
void myStack :: popStack() {
    if (inUse < 0) {
        ;
    }
	else {
		inUse = inUse - 1;
	}
}
/*This function inserts a new number to the front of the stack*/
void myStack :: push(int num) {
    if (inUse >= size) {
        int *newArr = stackArr;
        stackArr = new int[size + 2];
        for (int i = 0; i < inUse; i++)
        stackArr[i] = newArr[i]; 
        delete [] newArr;
        size = size + 2;
    }
    stackArr[inUse] = num;
    inUse = inUse + 1;
}
//------------------------------------------------------------------------

// Class to hold the Token information
// Default to initialize to the ERROR TokenType
Token :: Token()
{
    type = ERROR;
    op = '$';
    val = -999;
}

// Initialize to a specific TokenType
Token :: Token (TokenType t)
{
    type = t;
    op = '$';
    val = -999;
}

// Set to a specific TokenType
void Token :: setToType(TokenType t)
{
    type = t;
    op = '$';
    val = -999;
}

// Set to a OPERATOR TokenType with specific operator value
void Token :: setToOperator(char c)
{
    type = OPERATOR;
    op = c;
    val = -999;
}

// Set to a VALUE TokenType with a specific numeric value
void Token :: setToValue(int v)
{
    type = VALUE;
    op = '$';
    val = v;
}

// return true if the Current Token is of the given TokenType
bool Token :: equalsType(TokenType t)
{
    if (type == t)
      return true;
    else
      return false;
}

// return true if the Current Token is of the OPERATOR TokenType
//     and contains the given operator character
bool Token :: equalsOperator(char c)
{
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
}

// Return the Operator for the current Token
//   verify the current Token is of the OPERATOR TokenType
char Token :: getOperator ()
{
    if (type == OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
}

// Return the Value for the current Token
//   verify the current token is of the value TokenType
int Token :: getValue()
{
    if (type == VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
}
//------------------------------------------------------------------------------------

// initialize the TokenReader class to read from Standard Input
TokenReader :: TokenReader()
{
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
}

// Force the next getNextToken to read in a line of input
void TokenReader :: clearToEoln()
{
    needline = true;
}

// Return the next Token from the input line
Token TokenReader :: getNextToken()
{
    char* endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets ( inputline, 300, stdin);

      if (endCheck == NULL )
      {
        printf ("Error in reading");
        Token t(EOFILE);
        return t;
      }

      for (int i = 0 ; i < strlen(inputline) ; i++)
          if ('\n' == inputline[i])
              inputline[i] = ' ';
      strcat (inputline , " ");    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while ( pos < strlen(inputline) && isspace(inputline[pos]) )
    {
      pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos]; pos++;

    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return Token (QUIT);
    }

    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return Token (HELP);
    }

    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('%' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t;
      t.setToOperator( ch );
      return t;
    }

    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
      int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
      ch = inputline[pos]; pos++;
      while (isdigit(ch))
      {
        number = number * 10 + int (ch) - int('0');
        ch = inputline[pos]; pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t;
      t.setToValue( number );
      return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token (ERROR);
}

// --------------------- End of myStack.cpp--------------------------