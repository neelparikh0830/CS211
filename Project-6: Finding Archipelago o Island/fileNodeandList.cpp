#include "file.h"


nodeFile :: nodeFile(char* namee) 
{
	n = namee;
	next = NULL;
}
nodeFile* nodeFile :: getNext()
{
	return next;
}
void nodeFile :: setNext(nodeFile* node)
{
	next =  node;
}
char* nodeFile :: getName()
{
	return n;
}



fileList :: fileList()
{
	head = NULL;
}
void fileList :: appendName(char* name)
{
	nodeFile* prev = NULL;
	nodeFile* temp = new nodeFile(name);
	if (head == NULL)
	{
		head = temp;
	}
	else
	{
		for (prev = head; prev->getNext() != NULL; prev = prev->getNext())
		{
			;
		}
		prev->setNext(temp);
	}
}
bool fileList :: inList(char* name)
{
	for (nodeFile* temp = head; temp != NULL; temp = temp->getNext())
	{
		if(strcmp(temp->getName(), name) == 0)
		{
			return true;
		}
	}
	return false;
}
void fileList :: removeName(char* name)
{
	if (head != NULL)
	{
		nodeFile* prev = NULL;
		for (nodeFile* curr = head; curr != NULL; curr = curr->getNext())
		{
			if (strcmp(curr->getName(), name) == 0)
			{
				if(prev != NULL)
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
