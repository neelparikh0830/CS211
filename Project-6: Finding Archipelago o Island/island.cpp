#include "file.h"

myNode :: myNode(int value)
{
    next = NULL;
    i = value;
}

myNode :: myNode(int value, myNode* node)
{
    next = node;
    i = value;
}

void myNode :: setNext(myNode* node)
{
    next = node;
}

int myNode :: getValue()
{
    return i;
}

myNode* myNode :: getNext()
{
    return next;
}

myList :: myList()
{
    head = NULL;
}

myNode* myList :: getHead()
{
    if (head != NULL)
	{
        return head;
    }
	else
	{
		return NULL;

	}
}

void myList :: setHead(myNode* node)
{
    head = node;
}

int myList :: Top()
{
	return head->getValue();
}

void myList :: insertValue(int num)
{
    myNode* node = new myNode(num);
	if ( head == NULL)
	{
		head = node;
	}
    else
	{
        myNode* prev = head;
        while (prev->getNext() != NULL)
		{
            prev = prev->getNext();
        }
        prev->setNext(node);
    }
}

void myList :: pop(int num)
{
    if (head != NULL)
	{
        myNode* prev = NULL;
		for (myNode* curr = head; curr != NULL; curr = curr->getNext())
		{
			if (curr->getValue() == num)
			{
                if (prev != NULL)
				{
					prev->setNext(curr->getNext());
					delete(curr);
					return;
                }
				else
				{
					head = curr->getNext();
					delete(curr);
					return;
                }
            }
            prev = curr;
		}
    }
}

void myList :: print() 
{
	printf("  ");
	for(myNode* node = head; node != NULL; node = node->getNext())
	{
		printf("%d  ", node->getValue());
	}
    printf("\n");
}
 
void myList :: deleteList()
{
    if (head != NULL)
	{
        myNode* temp1 = head;
        while (temp1->getNext() != NULL)
		{
            myNode* temp2 = temp1;
			delete(temp2);
            temp1 = temp1->getNext();
        }
        delete(temp1);
        head = NULL;
    }
}

int myList :: currentValues()
{ 
	int count = 0;
	for(myNode* temp = head; temp != NULL; temp = temp->getNext())
	{
		count++;
	}
	return count;
}

int myList :: NthValue(int value)
{
    myNode* temp = head;
    for (int i = 0; i < value; i++)
	{
        temp = temp->getNext();
    }
    return temp->getValue();
}

bool myList :: foundFerry(int value)
{
	for(myNode* temp = head; temp != NULL; temp = temp->getNext())
	{
		if (temp->getValue() == value)
		{
            return true;
        }
	}
	return false;
}

bool myList :: checkEmpty()
{
    if (head != NULL)
	{
        return false;
    }
    return true;
}

Island :: Island()
{
	int old = -1;
	visited = -1;
}

int Island :: getValueVisited()
{
    return visited;
}

void Island :: setValueVisited(int value)
{
    visited = value;
}

void Island :: insert(int value)
{
    islandList.insertValue(value);
}

void Island :: ilandPrint()
{
    islandList.print();
}

void Island :: popPath(int value)
{
    islandList.pop(value);
}

void Island :: clearAll()
{
    islandList.deleteList();
}

myList Island :: getObject()
{
    return islandList;
}

myNode* Island :: getIlandHead()
{
    islandList.getHead();
}

int Island :: numIsland(int value)
{
    return islandList.NthValue(value);
}

bool Island :: findAdj(int value)
{
    return islandList.foundFerry(value);
}

int Island :: getPosition()
{
    return old;
}

void Island :: setPosition(int value)
{
    old = value; 
}

int Island :: lengthIsland()
{
    return islandList.currentValues();
}

void isQueue :: insertinQueue (int value)
{
    myNode* temp1 = getHead();
    myNode* temp = new myNode(value);
    if (temp1 == NULL) 
	{
        setHead(temp);
        return;
    }
	else
	{
		while (temp1->getNext() != NULL)
		{
			temp1 = temp1->getNext();
		}
		temp1->setNext(temp);
	}	
    
}

void isQueue :: removefromQueue ()
{
    myNode* temp = getHead();
	setHead(temp->getNext());
}

int isQueue :: getFrontofQueue()
{
    myNode* temp = getHead();
    if (temp != NULL)
	{
		return temp->getValue();
    }
	else
	{
		return -999;
    }
}

void myStack :: insert (int num)
{
    myNode* tempHead = getHead();
    myNode* temp = new myNode(num);
    if (tempHead == NULL)
	{
        setHead(temp);
        //return;
    }
	else
	{	
		temp->setNext(tempHead);
		setHead(temp);
	}
}

void myStack :: remove()
{
    myNode* temp = getHead();
	setHead(temp->getNext());
}

int myStack :: getterFront()
{
    myNode* temp = getHead();
    if (temp != NULL)
	{
		return temp->getValue();
    }
	else
	{
		return -999;
    }
}