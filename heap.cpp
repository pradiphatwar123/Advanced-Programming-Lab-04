#ifndef _heap_H_
#define _heap_H_

#include<iostream>
#include<cstdlib>
#include<ctype.h>
#include<malloc.h>
#include<fstream>
#include<string.h>
#include<math.h>

using namespace std;


#define	POSITIVE_SENTINEL ((pow(2,((sizeof(int)*8)-1))) - 1)

#define NEGATIVE_SENTINEL (-(pow(2,((sizeof(int)*8)-1)))) 

#define NODES_COUNT	256
#define EDGES_COUNT	512

//Graph Node Structure 

class Node	
{
	public:
		int 	Value;
		bool	Marked;
};

//Graph Edge Structure 

class Edge
{
	public:
		Node	u;
		Node	v;
		bool	roottoroot;
};	 	


//Binary Heap

class BINHEAPNode
{
           public:
                int	key;
                int 	Parent;
                int 	Left;
                int 	Right;
                     
};

/*****************************************************************************************************
Binomial Heap
*****************************************************************************************************/
class BINOMHEAPNode
{
         public:
                int 		key;              			 		 		
		int 		degree;
                BINOMHEAPNode	*Parent;      
                BINOMHEAPNode	*Left_Child;
                BINOMHEAPNode	*Right_Sibling;
    
};
/****************************************************************************************************
Fibonacci Heap
*****************************************************************************************************/
class FIBOHEAPNode
{
          public:   
                int 		key;
		int		degree;	
		int		bMark;
                FIBOHEAPNode 	*Parent;
		FIBOHEAPNode 	*Child;
		FIBOHEAPNode 	*Left_Sibling;
		FIBOHEAPNode 	*Right_Sibling;	           
};

/*****************************************************************************************************
Priority Queue
*****************************************************************************************************/
class PRIORITY_QUEUE
{
                    
        public:  
                    PRIORITY_QUEUE(){};
                    ~PRIORITY_QUEUE(){};
	
		    virtual bool makeHeap(){};	
                    virtual bool insert(int){};
                    virtual bool deleteKey(int){};                         
                    virtual bool extractMin(void){};
                    virtual int  findMin(void){};
		    virtual bool update(int, int){};	                    
                    virtual void displayHeap(string ){};
                      
};
/*****************************************************************************************************

BINHEAP class Inheariting PRIORITY_QUEUE class
/*****************************************************************************************************/

class BINHEAP : public PRIORITY_QUEUE
{
      public:
             BINHEAP(); 
             ~BINHEAP(); 

	     bool makeHeap();	
             bool insert(int);
             bool deleteKey(int);
             bool extractMin();
             int  findMin();
	     bool update(int, int);		             
             void displayHeap(string );

	     bool decrease(int,int);
             bool increase(int,int);	
             bool BinHeapify(int);
	     bool Down_Travel(int);             
	     int  Write_Output(string);	 				
};

/*****************************************************************************************************
BINOMHEAP class Inheariting PRIORITY_QUEUE class
*****************************************************************************************************/

class BINOMHEAP : public PRIORITY_QUEUE
{
      public:
             BINOMHEAP(); 
             ~BINOMHEAP(); 

	     bool makeHeap();	
             bool insert(int );
             bool deleteKey(int );
             bool extractMin();
             int  findMin();             
	     bool update(int, int);			
             void displayHeap(string );

             bool increase(int, int);	
             bool decrease(int, int);
	     void Recursive_Display(BINOMHEAPNode *);	
             BINOMHEAPNode* Binomial_Link(BINOMHEAPNode *, BINOMHEAPNode *);
             BINOMHEAPNode* Binomial_Heap_Union(BINOMHEAPNode *, BINOMHEAPNode *);
	     BINOMHEAPNode* Binomial_Heap_Merge(BINOMHEAPNode *, BINOMHEAPNode *);
	     BINOMHEAPNode* FIND_NODE(BINOMHEAPNode* H,int k) ;
	     void REVERT_LIST(BINOMHEAPNode* y);
    	     int  Write_Output(string);	 		

};

/*****************************************************************************************************
FIBOHEAP class Inheariting PRIORITY_QUEUEclass
*****************************************************************************************************/
class FIBOHEAP : public PRIORITY_QUEUE
{
      public:
              FIBOHEAP(); 
              ~FIBOHEAP(); 
		
	      bool makeHeap();	
              bool insert(int );
              bool deleteKey(int );
              bool extractMin();
              int  findMin();
	      bool update(int, int);			             
              void displayHeap(string );
                  
	      bool decrease(int ,int );
              bool increase(int, int );   	
              void Fib_Heap_Consolidate();
              void Fib_Heap_Link(FIBOHEAPNode *,FIBOHEAPNode *);	
              void Fib_Heap_Cut(FIBOHEAPNode *,FIBOHEAPNode *);
              void Fib_Heap_CascadeCut(FIBOHEAPNode *);
              void Recursive_Display(FIBOHEAPNode *);
	      FIBOHEAPNode *Find_Node(int , FIBOHEAPNode *);		
	      int  Write_Output(string);	 	
};




int 	Validate_Cmdline(int, char *[]);
void 	ShowMenu(void);

#endif
