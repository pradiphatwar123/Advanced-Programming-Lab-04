/*********************************************************************************************************
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :  04 - Implementation of Binomial Heap Priority Queue

File name         :  BINOM_HEAP.CPP

Description       :  Implements Interfaces for PRIORITY QUEUE Abstract Data Type (ADT) using BINOMIAL HEAP

Programmers       :  (1) Pradeep Hatwar    (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++ 4.6

Date created      :  30/10/2013

List of functions : (1)  void BINOMHEAP(void)
                    (2)  void ~BINOMHEAP(void)
                    (3)  bool makeHeap(void)
                    (4)  bool insert(int)
                    (5)  bool deleteKey(int)
                    (6)  bool extractMin(void)
                    (7)  bool findMin(void)
		    (8)  bool update(int, int);	
                    (9)  bool decrease(key)
                    (10) bool increase(key)		    	
                    (11) BINOMHEAPNode* Binomial_Link(BINOMHEAPNode*, BINOMHEAPNode* )
		    (12) BINOMHEAPNode* Binomial_Heap_Union(BINOMHEAPNode* , BINOMHEAPNode* )
		    (13) BINOMHEAPNode* Binomial_Heap_Merge(BINOMHEAPNode* ,BINOMHEAPNode*) 
		    (14) BINOMHEAPNode* FIND_NODE(BINOMHEAPNode*,int) 
		    (15) void REVERT_LIST(BINOMHEAPNode*) 
History           :  

*************************************************************************************************/


#include<iostream>
#include <math.h>
#include "heap.h"
#include<cstdlib>
#include<ctype.h>
#include<fstream>
#include<cstring>
#include<sstream>


// Pointer to the root node of Binomial Heap
BINOMHEAPNode *binomHead; // Head pointer for the linked list containing root nodes
BINOMHEAPNode *Hr; //Pointer for reverse list of siblings to be used during extractMin

extern int	      Nodes_Count, Edges_Count;
extern Node	      *Graph_Nodes_List;		//Pointer to Graph Vertices dynamic Array
extern Edge	      *Graph_Edges_List;		//Pointer to Graph Edges dynamic Array
extern char	      rootNodes_str[1000];	

extern int deckeyVal, inckeyVal;
/*********************************************************************************************************
Function Name            : BINOMHEAP
Inputs                   : void                       
Returns                  : void
Description              : Constructor
*********************************************************************************************************/

BINOMHEAP :: BINOMHEAP()
{
         try{
		Graph_Nodes_List = new Node[NODES_COUNT]; // Graph_Nodes_List to hold list of nodes in a graph
	}catch(bad_alloc xa){		
		cout << "Failed to intialize Memory for Graph Nodes List" << endl; 
	}			
	try{
		Graph_Edges_List = new Edge[EDGES_COUNT]; // Graph_Edges_List to hold list of edges in a graph
	}catch(bad_alloc xa){
		cout << "Failed to intialize Memory for Graph Edges List" << endl; 
	}	

}

/*********************************************************************************************************
Function Name            : ~BINOMHEAP
Inputs                   : void                       
Returns                  : void
Description              : Destructor
*********************************************************************************************************/

BINOMHEAP :: ~BINOMHEAP()
{
       //delete [] Graph_Nodes_List; 
       //delete [] Graph_Edges_List;  
}

/*********************************************************************************************************
Function Name            : makeHeap 
Inputs                   : void                          
Returns                  : false In case of any error occurred during makeHeap operation on Binomial Heaps
                           true In case of successfull makeHeap operation on Binomial Heapse
Description              : This function makes Heap
*********************************************************************************************************/

bool BINOMHEAP :: makeHeap(void)
{
	binomHead = NULL; // Intialise Head pointer

	return true;     
}

/*********************************************************************************************************
Function Name            : insert 
Inputs                   : int - key                          
Returns                  : false In case of any error occurred during insert operation on Binomial Heaps
                           true In case of successfull insert operation on Binomial Heapse
Description              : This function inserts node with 'key' field into binomial 
*********************************************************************************************************/

bool BINOMHEAP :: insert(int key)
{
        bool error=false;
		BINOMHEAPNode *H1;

			
	if((binomHead != NULL) && (FIND_NODE(binomHead,key) != NULL))
	{
		cout << "Node with key " << key <<" already present in the heap " << endl;
		error = true;
	} 
	else
	{
	   	//Creating New Binomial Node for insert	
		try{
	    	H1 = new BINOMHEAPNode;
    		}catch (bad_alloc xa) {        	
        	cout << "Failed to Intialize binomial node of binomial heap" << endl;     
			error = true;
			return error;
    		}
		 
		//Assigning Values to the new Node
		 H1->key = key;
		 H1->Parent = NULL;
	     H1->Left_Child = NULL;
	     H1->Right_Sibling = NULL;
		 H1->degree = 0;


		 // Union of newly created node with the binomial heap
		 binomHead = Binomial_Heap_Union(binomHead, H1);

		 BINOMHEAPNode* p; // Node for displaying binomial heap root nodes


		if(binomHead == NULL) // Check for null pointer
		  { 
		  cout << "\nHEAP EMPTY"; 
		  error = true;
		  return error; 
		  } 


		//Display root nodes list on console
		cout << "\nTHE ROOT NODES ARE:-\n" << endl; 
		p=binomHead; 

		while(p!=NULL) 
		{ 
		  cout << p->key <<" (" << p->degree << ")"; 

		  if(p->Right_Sibling!=NULL) 
		  cout << "-->";
		  p=p->Right_Sibling; 
		} 
     }
     return error;
     
}
/*********************************************************************************************************
Function Name            : deleteKey 
Inputs                   : int - key 
						   int - newKey                         
Returns                  : false In case of any error occurred during deleteKey operation on Binomial Heaps
                           true In case of successfull deleteKey operation on Binomial Heapse
Description              : This function deletes node with 'key' field from binomial heap
*********************************************************************************************************/
bool BINOMHEAP :: deleteKey(int key)
{
      bool error=false;
	  
	  BINOMHEAPNode* p; 
		

	 if(binomHead==NULL) // Check for if head pointing to NULL
	  { 
		  cout << "HEAP EMPTY" << endl; 
		  error=true;
		  return error;
	  } 
	 else
	 {

	if (decrease(key,NEGATIVE_SENTINEL)== false) //Check If decrese operation is successful i.e. it returns false flag
			extractMin();	// Call extract min
	 }
     
     return error;
}

/*********************************************************************************************************
Function Name            : extractMin 
Inputs                   : void                         
Returns                  : false In case of any error occurred during extractMin operation on Binomial Heaps
                           true In case of successfull extractMin operation on Binomial Heapse
Description              : This function deletes node whose key is minimum from the binomial heap
*********************************************************************************************************/
bool BINOMHEAP :: extractMin()
{
     bool error=false;

	 int rev =0;
//Added to solve delete prob
//	BINOMHEAPNode* 7Hr; 
  //Hr=NULL; 
  //Added to solve delete prob


  int min; 
  BINOMHEAPNode* t=NULL; 
  BINOMHEAPNode* x=binomHead; 
  BINOMHEAPNode* p; 
  if(x==NULL) 
  { 
     cout << "NOTHING TO EXTRACT" << endl; 
	 error = true;
      return error; 
   } 
   p=x; 
   
   min=p->key;

    //DELETE_PROBLEM	
   while(p->Right_Sibling!=NULL)
   {
     if((p->Right_Sibling)->key< min ) 
     { 
        min=(p->Right_Sibling)->key; 
        t=p; 
        x=p->Right_Sibling; 
      } 
      p=p->Right_Sibling; 
   } 
   
 
  if(t==NULL&&x->Right_Sibling==NULL) 
  {
	  binomHead = NULL;
//Debug// cout << "case-1" << endl;
  }
  else if(t==NULL) 
  {
		binomHead = x->Right_Sibling;
//Debug// cout << "case-2" << endl;
  }
  else if(t->Right_Sibling==NULL) 
  {
	    t=NULL; 
//Debug// cout << "case-3" << endl;
  }
  else
  {
      t->Right_Sibling=x->Right_Sibling; 
//Debug// cout << "case-4" << endl;
  }

  if(x->Left_Child!=NULL) 

  { 


	 REVERT_LIST(x->Left_Child); 
	
   (x->Left_Child)->Right_Sibling=NULL;

//Debug
//	if(Hr == NULL)
//		cout << "\nHr is null";
//	else
//			cout << "\nHr is not null";
//	cout << "\n After reverting list Hr min is " << Hr->key;
//  rev= 1;

   } 

    binomHead=Binomial_Heap_Union(binomHead,Hr); 
    
     return error;
}
             

/*********************************************************************************************************
Function Name            : findMin 
Inputs                   : void                         
Returns                  : false In case of any error occurred during findMin operation on Binomial Heaps
                           true In case of successfull findMin operation on Binomial Heaps
Description              : This function finds and returns the minimum 'key' from the ven binomial heap
*********************************************************************************************************/            
int BINOMHEAP :: findMin()
{
      int retval;
      unsigned int min = POSITIVE_SENTINEL;

	BINOMHEAPNode *x;
	BINOMHEAPNode *y = NULL;

  x = binomHead;

  while(x!=NULL)
  {
	
      if(x->key < min)
	  {
		  min = x->key;
		  y = x;
		  x = x->Right_Sibling;
	  }
  }
	if(min == POSITIVE_SENTINEL)
		retval = NEGATIVE_SENTINEL;	
	else
		retval = min;
	  cout << endl << "The minimum value is " << min;

     
     return retval;     
}
/*********************************************************************************************************
Function Name            : decrease 
Inputs                   : int key                         
Returns                  : false In case of any error occurred during decrease operation on Binomial Heaps
                           true In case of successfull decrease operation on Binomial Heaps
Description              : This function decreases the key value with the user given key value
*********************************************************************************************************/             
bool BINOMHEAP :: decrease(int key, int new_key)
{
      bool error=false;


	int temp;
	int k;

    	BINOMHEAPNode * p; 
    	BINOMHEAPNode * y; 
    	BINOMHEAPNode * z; 
    	p=FIND_NODE(binomHead,key); 


	k = new_key; // decrese by new_key

    if(p==NULL) 
      { 
       cout << "INVALID CHOICE OF KEY TO BE REDUCED" << endl; 
	   error = true;
       return error; 
      } 

	 if(k>p->key) 
	 { 
		  cout << "SORY!THE NEW KEY IS GREATER THAN CURRENT ONE" << endl; 
		  error = true;
		  return error; 
	  } 
	 p->key=k; 

	 if ( p->Parent != NULL) // Root Nodes to be deleted
	 {

		 y=p; 
		 z=p->Parent;

		  while(z!=NULL && y->key < z->key) 
		  { 
			temp=y->key; 
			y->key=z->key; 
			z->key=temp; 
			y=z; 
			z=z->Parent;
		  } 
	 }
	 else
	 {
		 cout << "parent is null";
	 }

   cout << "\nKEY REDUCED SUCCESSFULLY!" << endl; 
  
   return error;
}

/*********************************************************************************************************
Function Name            : increase 
Inputs                   : int key                         
Returns                  : false In case of any error occurred during decrease operation on Binomial Heaps
                           true In case of successfull decrease operation on Binomial Heaps
Description              : This function increases the key value with the user given key value
*********************************************************************************************************/  
bool BINOMHEAP :: increase(int key, int new_key)
{
 bool error=false;

	  

    int temp;
	int k;

    BINOMHEAPNode * p; 
    BINOMHEAPNode * y; 
    BINOMHEAPNode * z; 
	BINOMHEAPNode * x; 
	BINOMHEAPNode * q; 

    p=FIND_NODE(binomHead,key); 


	k = new_key; // decrese by new key

    if(p==NULL) 
      { 
       cout << "INVALID CHOICE OF KEY TO BE INCREASED" << endl; 
	   error = true;
       return error; 
      } 
	 if(k < p->key) 
	 { 
		  cout << "SORRY!THE NEW KEY IS LESSER THAN CURRENT ONE" << endl;
		  error = true;
		  return error; 
	  } 

	 p->key=k; 

	 cout<< " Value assined to p-key " << p->key;

	  
	  if(p->Left_Child != NULL)
	  {

	  x = p->Left_Child;

		  while((p->key > x->key) && (x->degree >= 0))
		  {

				q=x;

				while(x->Right_Sibling != NULL)
				{
					if(x->key > (x->Right_Sibling)->key)
					{

						q = x->Right_Sibling;
						x = x->Right_Sibling;

					}
				}


				temp = q->key;
				q->key = p->key;
				p->key = temp;
				p=q;
			
				if(p->Left_Child!=NULL)
				{
				x=p->Left_Child;
					while(x!=NULL && p->key <x->key)
					x=x->Right_Sibling;
				}

		  }
	  }

	
      
     return error;
}

/*********************************************************************************************************
Function Name            : DELETE 
Inputs                   : (1) int position                          
Returns                  : false In case of any error occurred during DELETE operation on Red-Black Tree
                            true In case of successfull DELETE operation on Red-Black Tree
Description              : This function deletes an element in the Red-Black Tree
*********************************************************************************************************/
void BINOMHEAP :: displayHeap(string filename)
{            
	BINOMHEAPNode*  p; 
	int 		retval;
	string		tempstr;		
	stringstream	ss;	
	
	if(binomHead == NULL) 
	{ 
		cout << "\nHEAP EMPTY"; 		 
	} 
	else
	{
		cout << "\nTHE ROOT NODES ARE:-\n" << endl; 
		p=binomHead; 
		Nodes_Count = 0;	
		Edges_Count = 0;		
		strcpy(rootNodes_str,"{rank=same;");
		while(p->Right_Sibling != NULL) 
		{ 
		  	ss << p->key;
			tempstr = ss.str();
			strcat(rootNodes_str,tempstr.c_str());
			strcat(rootNodes_str," ");
			ss.clear();
			ss.str(""); 	
		  	cout << p->key <<" (" << p->degree << ")"; 
		  	Graph_Edges_List[Edges_Count].u.Value = p->key;
		  	Graph_Edges_List[Edges_Count].v.Value = p->Right_Sibling->key;
		  	Graph_Edges_List[Edges_Count++].roottoroot = true;	
		  	if(p->Right_Sibling!=NULL) 
		   	cout << "-->";
		  	p=p->Right_Sibling; 
		}
		ss << p->key;
		tempstr = ss.str();
		strcat(rootNodes_str,tempstr.c_str());
		strcat(rootNodes_str," ");
		ss.clear();
		ss.str(""); 	
		cout << p->key <<" (" << p->degree << ")"; 
		strcat(rootNodes_str,";}\n");
		cout << endl;
		Recursive_Display(binomHead);
		retval = Write_Output(filename);
	}
}
/*********************************************************************************************************
Function Name            : Recursive_Display
Inputs                   : (1) BINOMHEAPNode                          
Returns                  : 
Description              : This function Recursively Calls itself to display Heap Elements
*********************************************************************************************************/
void BINOMHEAP :: Recursive_Display(BINOMHEAPNode *current)
{
	BINOMHEAPNode	*temp1,*temp2;
	int 		count = 0;	
	string		tempstr;		
	stringstream	ss;	
	
	if(current == NULL)
		return; 
	else
	{	
		//temp1 = current;
		temp2 = current;
		strcat(rootNodes_str,"{rank=same;"); //To display sibling nodes at same height
		while(temp2 != NULL)			
		{
			ss << temp2->key;
			tempstr = ss.str();
			strcat(rootNodes_str,tempstr.c_str());
			strcat(rootNodes_str," ");
			ss.clear();
			ss.str("");
		
			temp2 = temp2->Right_Sibling;
			count++;
		}
		strcat(rootNodes_str,";}\n");
		temp2 = current;
		count = 0;
		while(temp2 != NULL)			
		{
			//Adding Edges related to child level Siblings
			if((temp2->Parent != NULL) && (temp2->Right_Sibling != NULL))
			{
				cout <<"Child Sibling Edge u " << temp2->key << "Edge v " << temp2->Right_Sibling->key << endl;
				Graph_Edges_List[Edges_Count].u.Value = temp2->key;
				Graph_Edges_List[Edges_Count].v.Value = temp2->Right_Sibling->key;
				Graph_Edges_List[Edges_Count++].roottoroot = true;			
			
			}

			if(temp2->Parent != NULL)
			{
				cout << "Child Node " << temp2->key << "--->"<< temp2->Parent->key << endl;
				Graph_Nodes_List[Nodes_Count].Value = temp2->key;
				Graph_Nodes_List[Nodes_Count++].Marked = false;
				
				Graph_Edges_List[Edges_Count].u.Value = temp2->key;
				Graph_Edges_List[Edges_Count].v.Value = temp2->Parent->key;
				Graph_Edges_List[Edges_Count++].roottoroot = true;
				
				if(temp2 == current)
				{
					Graph_Edges_List[Edges_Count].u.Value = temp2->Parent->key;
					Graph_Edges_List[Edges_Count].v.Value = temp2->key;
					Graph_Edges_List[Edges_Count++].roottoroot = false;		
				}
	
			}
			else
			{
				cout << "Root Node " << temp2->key << endl;
				Graph_Nodes_List[Nodes_Count].Value = temp2->key;
				Graph_Nodes_List[Nodes_Count++].Marked = false;			
			}
			Recursive_Display(temp2->Left_Child);
			temp2 = temp2->Right_Sibling;			
		}	
	}
}	

/*********************************************************************************************************
Function Name            : Binomial_Link 
Inputs                   : 1) BINOMHEAPNode *y                         
						   2) BINOMHEAPNode *z
Returns                  : Linked Binomial Heap
Description              : This function links binomial trees with the same degree
*********************************************************************************************************/  
BINOMHEAPNode* BINOMHEAP :: Binomial_Link(BINOMHEAPNode *y, BINOMHEAPNode *z)
{
   
	BINOMHEAPNode* H = NULL;

	 y->Parent=z; 
    y->Right_Sibling=z->Left_Child; 
    z->Left_Child=y; 
    z->degree=z->degree+1; 

	cout << "z->degree and value is" << z->degree << "  " << z->key;

	return H;  



}
/*********************************************************************************************************
Function Name            : Binomial_Heap_Union 
Inputs                   : 1) BINOMHEAPNode *H1                         
						   2) BINOMHEAPNode *H2
Returns                  : New Binomial Heap
Description              : This function creates and returns a new heap that contain all the nodes of Heap
						   H1 and H2
*********************************************************************************************************/ 
BINOMHEAPNode* BINOMHEAP :: Binomial_Heap_Union(BINOMHEAPNode *H1, BINOMHEAPNode *H2)
{
     
   BINOMHEAPNode* prev_x; 
   BINOMHEAPNode* next_x; 
   BINOMHEAPNode* x;
   
   BINOMHEAPNode* H = NULL;
   H=Binomial_Heap_Merge(H1,H2); 

   if(H==NULL) 
    return H; 

   prev_x=NULL; 
   x=H; 
   next_x=x->Right_Sibling; 
   while(next_x!=NULL) 
      { 
        if((x->degree!=next_x->degree)||((next_x->Right_Sibling!=NULL)&&(next_x->Right_Sibling)->degree==x->degree)) 
        { 
        prev_x=x; 
        x=next_x; 
        } 
       else 
        { 
         if(x->key<=next_x->key) 
         { 
           x->Right_Sibling=next_x->Right_Sibling; 
           Binomial_Link(next_x,x); 
         } 
         else 
         { 
          if(prev_x==NULL) 
             H=next_x; 
          else 
             prev_x->Right_Sibling=next_x; 
          Binomial_Link(x,next_x); 
          x=next_x; 
         } 
     }  
    next_x=x->Right_Sibling; 
   } 
 return H; 




}

/*********************************************************************************************************
Function Name            : Binomial_Heap_Merge 
Inputs                   : 1) BINOMHEAPNode *H1                         
						   2) BINOMHEAPNode *H2
Returns                  : Merged Binomial Heap
Description              : This function merges the two heaps 
*********************************************************************************************************/ 

BINOMHEAPNode* BINOMHEAP :: Binomial_Heap_Merge(BINOMHEAPNode* H1,BINOMHEAPNode* H2) 
{ 
  BINOMHEAPNode* H=NULL; 
  BINOMHEAPNode* y; 
  BINOMHEAPNode* z; 
  BINOMHEAPNode* a; 
  BINOMHEAPNode* b; 
  y=H1; 
  z=H2; 
  if(y!=NULL) 
  { 
    if(z!=NULL&&y->degree<=z->degree) 
      H=y; 
    else if(z!=NULL&&y->degree>z->degree)
      H=z; 
  else 
      H=y; 
  } 
 else 
   H=z; 
while(y!=NULL&&z!=NULL) 
 { 
   if(y->degree<z->degree) 
   { 
      y=y->Right_Sibling;  
   } 
   else if(y->degree==z->degree) 
      { 
        a=y->Right_Sibling; 
        y->Right_Sibling=z; 
        y=a; 
      } 
   else 
      { 
        b=z->Right_Sibling; 
        z->Right_Sibling=y; 
        z=b; 
      } 
  } 
  return H; 
}

/*********************************************************************************************************
Function Name            : FIND_NODE 
Inputs                   : 1) BINOMHEAPNode *H                         
						   2) int k
Returns                  : Node of a binomial heap which contains key 'k'
Description              : This function recursively finds the node in a binomial heap with key value 'k'
*********************************************************************************************************/ 
BINOMHEAPNode* BINOMHEAP :: FIND_NODE(BINOMHEAPNode* H,int k) 
{ 
 BINOMHEAPNode* x=H; 
 BINOMHEAPNode* p=NULL; 


	 if(x->key == k) 
	  { 
			p=x; 
			return p;
	  } 
 
	 if(x->Left_Child!=NULL&&p==NULL) 
	 { 
		   p=FIND_NODE(x->Left_Child,k); 
	 } 

	 if(x->Right_Sibling!=NULL&&p==NULL) 
	 { 
		  p=FIND_NODE(x->Right_Sibling,k); 
	 } 
	  return p;
  

 } 

/*********************************************************************************************************
Function Name            : REVERT_LIST 
Inputs                   : 1) BINOMHEAPNode *y                         
						   
Returns                  : Node of a binomial heap which contains key 'k'
Description              : This function recursively finds the node in a binomial heap with key value 'k'
*********************************************************************************************************/ 

void BINOMHEAP :: REVERT_LIST(BINOMHEAPNode* y) 
{ 
  if(y->Right_Sibling!=NULL) 
  { 
    //DELETE PROBLEM
    y->Parent = NULL;		
    REVERT_LIST(y->Right_Sibling); 
    (y->Right_Sibling)->Right_Sibling=y; 
   } 
 else 
   { 
   //DELETE PROBLEM
    y->Parent = NULL;		
     Hr=y; 
    } 
} 



/*********************************************************************************************************
Function Name            : update 
Inputs                   : (1) int key
						   (2) int new_key                          
Returns                  : It returns true if a node key is decreased or increased successfully
Description              : This function decreases key value to a new value
*********************************************************************************************************/
bool BINOMHEAP :: update(int key, int new_key)
{
	bool 		error = false;	
	BINOMHEAPNode 	*node,*y;
	
	if(binomHead == NULL)
	{
		cout << "There are no Elements in the Heap " << endl;
		error = true;
	}
	else if((binomHead != NULL) && (FIND_NODE(binomHead,new_key) != NULL))
	{
		cout << "Node with key " << new_key <<" already present in the heap " << endl;
		error = true;
	} 
	else 
	{	
		if(new_key == key)
		{
			cout << "New Key is same as current key" << endl;
			error = true;
		}
		else if(new_key < key)
		{
			error = decrease(key,new_key);	
		
		}
		else
			error = increase(key,new_key);		
     	}
    	return error;
}

/*********************************************************************************************************
Function Name            : Write_Output 
Inputs                   : (1) string optfile
						                  
Returns                  : It returns -1 in case of any error
						   It returns 0 in case of no error
Description              : This function writes nodes and edges information in the output fille in.gv format
*********************************************************************************************************/
int BINOMHEAP :: Write_Output(string optfile)
{	
	int 		retval = 0,mst_edge = 0, no_chars = 0, iter = 0;
	ofstream 	optstrm;
	char		buff[100];
	size_t 		pos=-1;
	string		tempstr;		
	stringstream	ss;
	


	const char *outputfile = optfile.c_str();	
	optstrm.open(outputfile, ios::out | ios::trunc); // Opening outputfile in write Mode//

	if(!optstrm)
	{
		cout << "Failed to open File " << outputfile << endl;		
		retval = -1;
	}
	else
	{			
		//writing Graph Elements to the output file		
		strcpy(buff,"digraph G {\n");
		no_chars = strlen(buff);	
		buff[no_chars] = '\0';
		if(optstrm.write(buff,no_chars))
		{
			strcpy(buff,"// nodes\n");
			no_chars = strlen(buff);	
			buff[no_chars] = '\0';
			if(optstrm.write(buff,no_chars))
			{	
				no_chars = strlen(rootNodes_str);
				rootNodes_str[no_chars] = '\0';
				if(!optstrm.write(rootNodes_str,no_chars))
				{
					retval = -1;					
				}		
				for(iter = 0; iter < Nodes_Count; iter++)
				{
					cout << "Node Key " << Graph_Nodes_List[iter].Value << ", Node Marked "<< Graph_Nodes_List[iter].Marked << endl;
					ss << Graph_Nodes_List[iter].Value;	 
		 			tempstr = ss.str();
					strcpy(buff,tempstr.c_str());
					strcat(buff,";\n");	
					no_chars = strlen(buff);
					buff[no_chars] = '\0';
					if(!optstrm.write(buff,no_chars))
					{
						retval = -1;
						break;
					}		
					ss.clear();
					ss.str("");						
				}
				if(retval != -1)
				{	
					strcpy(buff,"// edges\n");
					no_chars = strlen(buff);	
					buff[no_chars] = '\0';
					if(optstrm.write(buff,no_chars))
					{	
						for(iter = 0; iter < Edges_Count; iter++)
						{
							cout << "Edge First Node " << Graph_Edges_List[iter].u.Value << endl;
							cout << "Edge Second Node " << Graph_Edges_List[iter].v.Value << endl;
							cout << "RootToRoot Edge " << Graph_Edges_List[iter].roottoroot << endl;
							
							if(Graph_Edges_List[iter].roottoroot)
							{
								ss << Graph_Edges_List[iter].u.Value;	 
		 						tempstr = ss.str();
								strcpy(buff,tempstr.c_str());
							}
							else
							{	
								ss << Graph_Edges_List[iter].u.Value;	 
		 						tempstr = ss.str();
								strcpy(buff,tempstr.c_str());
							}			
							strcat(buff," ");
							strcat(buff,"->");
							strcat(buff," ");
							
							ss.clear();
							ss.str("");
							if(Graph_Edges_List[iter].roottoroot)
							{
								ss << Graph_Edges_List[iter].v.Value;	 
		 						tempstr = ss.str();
								strcat(buff,tempstr.c_str());
							}
							else
							{	
								ss << Graph_Edges_List[iter].v.Value;	 
		 						tempstr = ss.str();
								strcat(buff,tempstr.c_str());
							}
							ss.clear();
							ss.str("");

							strcat(buff," ");
							if(Graph_Edges_List[iter].roottoroot)//For Root Level Edges
							{
								strcat(buff,"[style=dotted,color=blue]");
							
							}
							else
								strcat(buff,"[color=red]");	
							strcat(buff,";\n");	
							no_chars = strlen(buff);
							buff[no_chars] = '\0';
							if(!optstrm.write(buff,no_chars))
							{
								retval = -1;
								break;
							}
							
						}
					}
					else
					{
						retval = -1;
					}
				}
				if(retval != -1)
				{
					strcpy(buff,"}\n");
					no_chars = strlen(buff);	
					buff[no_chars] = '\0';
					if(!optstrm.write(buff,no_chars))
					{
						retval  = -1;
					}			
				}					
			}
			else
			{
				retval = -1;
			}	
		}
		else
		{
			retval = -1;
		}
		optstrm.close();	// Closing output file 							
	}	
	return retval;

} 
                   
