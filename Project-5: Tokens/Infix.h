#include <cstdio>
#include <cstring>
#include <cctype>

// Enumarated Type specifying all of the Tokens
enum TokenType{
    ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

class myStack {
    private:
    int* stackArr;
    int size;
    int inUse;
    // ---------------
    public:
    myStack();
    bool isEmpty();
    void push(int num);
    void popStack();
    void clear();
    int top();
};

class Token {
    private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error
    // --------------
    public:
    Token();
    Token (TokenType t);
    void setToType(TokenType t);
    void setToOperator(char c);
    void setToValue(int v);
    bool equalsType(TokenType t);
    bool equalsOperator(char c);
    char getOperator ();
    int getValue();
};

class TokenReader
{
    private:
    char inputline[300];  // this assumes that all input lines are 300 characters or less in length
    bool needline;
    int pos;
    // -------------------
    public:
    TokenReader();
    void clearToEoln();
    Token getNextToken();
};

void processExpression (Token inputToken, TokenReader *tr);
void printCommands();
int eval(int &val1, int &val2, char &op);
void popAndEval(myStack &numbers, myStack &operators);