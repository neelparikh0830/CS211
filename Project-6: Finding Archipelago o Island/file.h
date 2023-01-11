#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

class myNode
{
	
    private:
    myNode* next;
	int i;
	
    public:
	
    myNode(int value);
    myNode(int value, myNode* node);
	void setNext(myNode* node);
    int getValue();
    myNode* getNext();
	
};

class myList
{
	
    private:
    myNode* head;
	
    public:
	
    myList();
    myNode* getHead();
    void setHead(myNode* node);
    int Top();
    void insertValue(int num);
    void pop(int num);
    void print();
    void deleteList();
    int currentValues();
    int NthValue(int value);
    bool foundFerry(int value);
    bool checkEmpty();
	
};

class Island
{
	
  private:
  int old;
  int visited;
  myList islandList;
  
  public:
  Island();
  int getValueVisited();
  void setValueVisited(int value);
  void insert(int value);
  void ilandPrint();
  void popPath(int value);
  void clearAll();
  myList getObject();
  myNode* getIlandHead();
  int numIsland(int value);
  bool findAdj(int value);
  int getPosition();
  void setPosition(int value);
  int lengthIsland();
  
};

class isQueue : public myList
{
	
    public:
	
    isQueue() : myList() {}
    void insertinQueue (int value);
    void removefromQueue ();
    int getFrontofQueue();
	
};

class myStack : public myList
{
	
    public:
	
    myStack() : myList() {}
    void insert (int num);
    void remove ();
    int getterFront();
	
};

class nodeFile
{
    private:
	nodeFile* next;
    char* n;
    public:
    nodeFile(char* namee);
	nodeFile* getNext();
    void setNext(nodeFile* node);
    char* getName();
};

class fileList
{
    private:
    nodeFile* head;
    public:
    fileList();
    void appendName(char* name);
    bool inList(char* name);
    void removeName(char* name);
};

class ArchipelagoExpedition {
    private:
    int size;
    Island* islands;
    fileList files;
    
    public:
    ArchipelagoExpedition();
    void processCommandLoop(FILE* inFile);
    void getItClear();
    void showCommands();
    void doTravel();
    bool bfs(int b, isQueue* qList);
    myList *breadthFirstSearch(int x, int y);
    void doResize();
    void doInsert();
    void doDelete();
    void doList();
    void doFile();
};
