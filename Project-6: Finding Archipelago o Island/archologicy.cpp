#include "file.h"

ArchipelagoExpedition :: ArchipelagoExpedition()
 {
	size = 10;
    islands = new Island[size];
 }
  
  
 // The main loop for reading in input
 void ArchipelagoExpedition :: processCommandLoop (FILE* inFile)
 {
  char  buffer[300];
  char* input;

  input = fgets ( buffer, 300, inFile );   // get a line of input
    
  // loop until all lines are read from the input
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \n\t");

    printf ("*%s*\n", command);
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "q") == 0) 
      exit(1);
     
    else if ( strcmp (command, "?") == 0) 
      showCommands();
     
    else if ( strcmp (command, "t") == 0) 
      doTravel();
     
    else if ( strcmp (command, "r") == 0) 
      doResize();

    else if ( strcmp (command, "i") == 0) 
      doInsert();

    else if ( strcmp (command, "d") == 0) 
      doDelete();

    else if ( strcmp (command, "l") == 0) 
      doList();

    else if ( strcmp (command, "f") == 0) 
      doFile();

    else if ( strcmp (command, "#") == 0) 
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
 }
 
 void ArchipelagoExpedition :: showCommands()
 {
   printf ("The commands for this project are:\n");
   printf ("  q \n");
   printf ("  ? \n");
   printf ("  # \n");
   printf ("  t <int1> <int2> \n");
   printf ("  r <int> \n");
   printf ("  i <int1> <int2> \n");
   printf ("  d <int1> <int2> \n");
   printf ("  l \n");
   printf ("  f <filename> \n");
 }
 
 void ArchipelagoExpedition :: doTravel()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
  
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");

  
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   if(val1 <= 0 || val1 > size || val2 <= 0 || val2 > size)
   {
       printf("Invalid value for island\n");
       return;
   }
   printf ("Performing the Travel Command from %d to %d\n", val1, val2);
   myList *shortestPath = breadthFirstSearch(val1, val2);
   if (!shortestPath->checkEmpty())
   {
       printf("shortest path from %d to %d: ", val1, val2);
       while (!shortestPath->checkEmpty())
	   {
           printf("%d", shortestPath->Top());
           shortestPath->pop(shortestPath->Top());
           if (!shortestPath->checkEmpty())
		   {
               printf(" - ");
           }
       }
	   printf("\n");
   }
 }
 
 void ArchipelagoExpedition :: doResize()
 {
	int val1 = 0;
    char* next = strtok (NULL, " \n\t");
    // printf("%s\n", next);
    if ( next == NULL )
	{
        printf ("Integer value expected\n");
        return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0)
	{
        printf ("Integer value expected\n");
        return;
    }
    getItClear();
    size = val1;
    islands = new Island[size];
    printf("Performing the Resize Command with %d\n", val1);
 }
 
 void ArchipelagoExpedition :: doInsert()
 {
	int val1 = 0;
    int val2 = 0;
    // get an integer value from the input
    char* next = strtok (NULL, " \n\t");
    // printf("%s\n", next);
    if ( next == NULL )
    {
        printf ("Integer value expected\n");
        return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0)
    {
        printf ("Integer value expected\n");
        return;
    }
    // get another integer value from the input
    next = strtok (NULL, " \n\t");
    // printf("%s\n", next);
    if ( next == NULL )
    {
        printf ("Integer value expected\n");
        return;
    }
    val2 = atoi ( next );
    if ( val2 == 0 && strcmp (next, "0") != 0)
    {
        printf ("Integer value expected\n");
        return;
    }
	if(val1 == val2)
	{
		printf("Can not add ferry ride to self \n");
		return;
	}
    if(val1 <= 0 || val1 > size || val2 <= 0 || val2 > size) 
	{
       printf("Invalid value for island\n");
       return;
    }
    printf("Performing the Insert Command for %d\n", val1);
    if (islands[val1-1].findAdj(val2))
	{
        printf("Ferry ride already added!\n");
        return;
    }
    islands[val1-1].insert(val2);
 }
 
void ArchipelagoExpedition :: doDelete()
{
	int val1 = 0;
	int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
  
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");

   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   if(val1 <= 0 || val1 > size || val2 <= 0 || val2 > size) 
   {
       printf("Invalid value for island\n");
       return;
   }
    printf("Performing the Delete Command for %d\n", val1);
    islands[val1-1].popPath(val2);
}
 
  void ArchipelagoExpedition :: doList()
 {
	printf("Displaying the adjacency list:\n");
    int temp = 0;
    for (int i = 0; i < size; i++)
	{
        temp = i+1;
        printf("%d -->", temp);
        islands[i].ilandPrint();
    }
 }

 void ArchipelagoExpedition :: doFile()
 {
   // get a filename from the input
   char* fname = strtok (NULL, " \r\n\t");
   if ( fname == NULL )
   {
     printf ("Filename expected\n");
     return;
   }
   
   //printf ("Performing the File command with file: %s\n", fname);
   
   // next steps:  (if any step fails: print an error message and return ) 
   //  1. verify the file name is not currently in use
   printf ("Performing the File command with file: %s\n", fname);
    if(files.inList(fname))
	{
        printf ("File is already in use\n");
    }
	else
	{
        //  2. open the file using fopen creating a new instance of FILE*
        FILE * pFile = fopen(fname,"r");
        
        //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
        if (pFile != NULL)
		{
			files.appendName(fname);
            this->processCommandLoop(pFile);
        }
		else
		{
			printf ("Cannot open the file\n");
            return;
        }
        //  4. close the file when processCommandLoop() returns
        fclose(pFile);
        files.removeName(fname);
    }
 }
 
 myList* ArchipelagoExpedition :: breadthFirstSearch(int x, int y)
 {
    
    for (int i = 0; i < size; i++)
	{
        islands[i].setValueVisited(-1);
    }
    for (int i = 0; i < size; i++)
	{
        islands[i].setPosition(-1);
    }
    isQueue* IslandQueue = new isQueue();
    IslandQueue->insertinQueue(x);
    if (bfs(y, IslandQueue) == false) 
	{
        printf("You can NOT get from island %d to island %d\n", x, y);
        IslandQueue->deleteList();
        return IslandQueue;
    }
	else
	{
        printf("You can get from island %d to island %d\n", x, y);
        myStack *path = new myStack();
        int currentIsland = y;
        path->insert(y);
        do
		{
            currentIsland = islands[currentIsland-1].getPosition();
            path->insert(currentIsland);
        } 
		while (currentIsland != x);
        return path;
    }
}

bool ArchipelagoExpedition :: bfs(int b, isQueue* qList)
{
    while (!(qList->checkEmpty()) )
	{
        int a = qList->getFrontofQueue();
        qList->removefromQueue();
        for (int i = 0; i < islands[a-1].lengthIsland(); i++)
		{
            int temp = islands[a-1].numIsland(i);
            if (islands[temp-1].getPosition() == -1)
			{
                islands[temp-1].setPosition(a);
                if (temp == b)
				{
                    return true;
                }
                qList->insertinQueue(temp);
            }
        }
    }
    return false;
}

void ArchipelagoExpedition :: getItClear()
{
    for (int i = 0; i < size; i++)
	{
        islands[i].clearAll();
    }
    delete(islands);
}