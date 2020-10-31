#include <iostream>

using namespace std;

struct CLinkedListNode
{
	int Data;
	CLinkedListNode *Link;

	CLinkedListNode();
};

CLinkedListNode::CLinkedListNode()
{
	Data=0;
	Link=NULL;
}

class CLinkedList
{
private:
	CLinkedListNode *HeadPtr;
	CLinkedListNode *CurrNodePtr;

public:
	CLinkedList();
	~CLinkedList();

	void Insert(int Data);
	void Append(int Data);
	int GetFirstData();
	int GetNextData();
};

CLinkedList::CLinkedList()
{
	HeadPtr=NULL;
	CurrNodePtr=NULL;
}

CLinkedList::~CLinkedList()
{
	CLinkedListNode *RemovingNodePtr;

	RemovingNodePtr=HeadPtr;

	while(RemovingNodePtr!=NULL)
	{
		HeadPtr=RemovingNodePtr->Link;

		delete RemovingNodePtr;

		RemovingNodePtr=HeadPtr;
	}
}

void CLinkedList::Insert(int Data)
{
	CLinkedListNode *NewNodePtr;

	NewNodePtr=new CLinkedListNode;

	NewNodePtr->Data=Data;

	NewNodePtr->Link=HeadPtr;
	HeadPtr=NewNodePtr;

	/*
	if(HeadPtr==NULL)
	{
		HeadPtr=NewNodePtr;
	}
	else
	{
		NewNodePtr->Link=HeadPtr;
		HeadPtr=NewNodePtr;
	}
	*/
}

void CLinkedList::Append(int Data)
{
	CLinkedListNode *NewNodePtr;
	CLinkedListNode *LastNodePtr;

	NewNodePtr=new CLinkedListNode;

	NewNodePtr->Data=Data;

	if(HeadPtr==NULL)
	{
		HeadPtr=NewNodePtr;
	}
	else
	{
		LastNodePtr=HeadPtr;

		while(LastNodePtr->Link!=NULL)
		{
			LastNodePtr=LastNodePtr->Link;
		}

		LastNodePtr->Link=NewNodePtr;
	}
}

int CLinkedList::GetFirstData()
{
	CurrNodePtr=HeadPtr;

	if(CurrNodePtr!=NULL)
	{
		return CurrNodePtr->Data;
	}

	return 0;
}

int CLinkedList::GetNextData()
{
	if(CurrNodePtr!=NULL)
	{
		CurrNodePtr=CurrNodePtr->Link;

		if(CurrNodePtr!=NULL)
		{
			return CurrNodePtr->Data;
		}
	}

	return 0;
}

int main()
{
	CLinkedList LinkedList1,LinkedList2;

	cout<<"Enter inserting data: ";

	for(;;)
	{
		int Data;

		cin>>Data;

		if(Data==0)
		{
			break;
		}

		LinkedList1.Insert(Data);
	}

	int Data1;

	Data1=LinkedList1.GetFirstData();

	while(Data1!=0)
	{
		cout<<Data1<<" ";

		Data1=LinkedList1.GetNextData();
	}

	cout<<endl;

	cout<<"----------"<<endl;

	cout<<"Enter appending data: ";

	for(;;)
	{
		int Data;

		cin>>Data;

		if(Data==0)
		{
			break;
		}

		LinkedList2.Append(Data);
	}

	int Data2;

	Data2=LinkedList2.GetFirstData();

	while(Data2!=0)
	{
		cout<<Data2<<" ";

		Data2=LinkedList2.GetNextData();
	}

	cout<<endl;

	return 0;
}

