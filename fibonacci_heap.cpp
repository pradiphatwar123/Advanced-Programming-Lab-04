/***********************************************************************************888
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :  04 - Implementation of Fibonacci Heap Priority Queue

File name         :  FIBO_HEAP.CPP

Description       :  Implements Interfaces for PRIORITY QUEUE Abstract Data Type (ADT) using FIBONACCI  HEAP

Programmers       :  (1) Pradeep Hatwar    (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++ 4.6

Date created      :  30/10/2013

List of functions :
                  (1)  FIBOHEAP(); 
                  (2) ~FIBOHEAP(); 
                  (3)  bool makeHeap();	
                  (4)  bool insert(int);
                  (5)  bool deleteKey(int);
                  (6)  bool extractMin();
                  (7)  int  findMin();
	          (8)  bool update(int, int);		             
                  (9)  void displayHeap(string );
		  (10) bool decrease(int,int);
                  (11) bool increase(int,int);	
                  (12) void Fib_Heap_Consolidate();
	          (13) void Fib_Heap_Link(FIBOHEAPNode *,FIBOHEAPNode *);	
              	  (14) void Fib_Heap_Cut(FIBOHEAPNode *,FIBOHEAPNode *);
              	  (15) void Fib_Heap_CascadeCut(FIBOHEAPNode *);
              	  (16) void Recursive_Display(FIBOHEAPNode *);
	      	  (17) FIBOHEAPNode *Find_Node(int , FIBOHEAPNode *);		
	      	  (18) int  Write_Output(string);	 				 
History           :  

*************************************************************************************************/

#include<iostream>
#include<map>
#include<cstdlib>
#include<ctype.h>
#include<fstream>
#include<cstring>
#include<sstream>
#include "heap.h"


FIBOHEAPNode			*FiboMin;
int	     			NumNodes = 0; 
map<int, FIBOHEAPNode *>	NodesMap;  

extern int	      Nodes_Count, Edges_Count;
extern Node	      *Graph_Nodes_List;		//Pointer to Graph Vertices dynamic Array
extern Edge	      *Graph_Edges_List;		//Pointer to Graph Edges dynamic Array
extern char	      rootNodes_str[1000];	

FIBOHEAP :: FIBOHEAP()
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

FIBOHEAP :: ~FIBOHEAP()
{
	delete [] Graph_Nodes_List; 
	delete [] Graph_Edges_List; 
}
/*********************************************************************************************************
Function Name            : makeHeap
Inputs                   :                           
Returns                  : true
Description              : This function Initializes FiboMin to NULL
*********************************************************************************************************/             bool FIBOHEAP :: makeHeap()
{
	FiboMin = NULL;      

	return true;    	 
}
/*********************************************************************************************************
Function Name            : insert
Inputs                   : (1) int key                        
Returns                  : Returns true if insert is successful, otherwise false
Description              : This Function inserts a key into heap
*********************************************************************************************************/             bool FIBOHEAP :: insert(int key)
{
	FIBOHEAPNode	*node,*temp=NULL;
	bool 		error = false;	


	//Checking if node is already present in the heap
	temp = NodesMap[key];	
	if(temp != NULL)
	{
		cout << "Node with key " << key <<" already present in the heap " << endl;
		error = true;
	}
	if(!error)
	{
		//Creating NewNode 		
		try{
		    	node = new FIBOHEAPNode;
    		}catch (bad_alloc xa) {    
			error = true;    	
        		cout << "Failed to Create Node of Fibonacci Heap" << endl;           
    		}
		if(!error)
		{
			//Filling Node details
			node->key = key;
			node->degree = 0;
			node->Parent = NULL;
			node->Child = NULL;
			node->Left_Sibling = NULL;
			node->Right_Sibling = NULL;
			node->bMark = false;
        	
			if(FiboMin == NULL)	//No Nodes in Heap
			{
				node->Left_Sibling = node;
				node->Right_Sibling = node;
				FiboMin = node;			
			}
			else			//Adding new Node always to the right of FiboMin
			{				
				node->Left_Sibling = FiboMin;
				FiboMin->Right_Sibling->Left_Sibling = node;
				node->Right_Sibling = FiboMin->Right_Sibling;		
				FiboMin->Right_Sibling = node;
				if(node->key < FiboMin->key)	//Updating Min Node if new node key is smaller
				{
					FiboMin = node;
				}
			}	
			NodesMap[key] = node;	//Storing <Key, Node > into Map
			NumNodes++;	
		}
	}
	return error;	
}	
/*********************************************************************************************************
Function Name            : deleteKey
Inputs                   : (1) int key                          

Returns                  : It returns a true if delete is successful, else false
Description              : This function deletes a node with the given Key
*********************************************************************************************************/             bool FIBOHEAP :: deleteKey(int key)
{
	bool		error = false;
	FIBOHEAPNode	*node;
	int		new_key = NEGATIVE_SENTINEL;	
		     
	if(FiboMin == NULL)
	{
		cout << "There are no Elements in the Heap " << endl;
		error = true;
	}	
	else
	{		
		node = NodesMap[key];		
		if(node == NULL)
		{
			cout << "Node with Key " << key << " is not found in the Priority Queue " << endl;			
			error = true;
		}
		else
		{			
			error = decrease(key, new_key);	       //Decreasing the key value to NEGATIVE_SENTINEL	
			if(!error)
				error = extractMin();		       //Extracting Node with NEGATIVE_SENTINEL		
			if(!error)
				NumNodes = NumNodes - 1;
		}			
	}
		

	return error;
}
/*********************************************************************************************************
Function Name            : extractMin
Inputs                   :                          
Returns                  : It returns node with Min Node 
Description              : This function removes a node with minimum key from heap
*********************************************************************************************************/             
bool FIBOHEAP :: extractMin()
{
	bool 		error = false;
	FIBOHEAPNode	*z,*x,*temp_child;

	z = FiboMin;
	if(z != NULL)
	{
		//Add each child x of z to the root list
		if(z->Child != NULL)	//If z has child
		{
			x = z->Child;
			temp_child = z->Child;
			temp_child->Parent = NULL;	
		
			if(z->Right_Sibling != z)	//Root List has multiple root nodes
			{
				temp_child->Left_Sibling = z->Left_Sibling;
				z->Left_Sibling->Right_Sibling = temp_child;
				while(x->Right_Sibling != temp_child)
				{
					x = x->Right_Sibling;
					x->Parent = NULL; 
				} 
				x->Right_Sibling = z->Right_Sibling;
				z->Right_Sibling->Left_Sibling = x;
				FiboMin = z->Right_Sibling;					
			}
			else		//Root List has only 1 root node
			{
				while(x->Right_Sibling != temp_child)
				{					x = x->Right_Sibling;
					x->Parent = NULL; 
				} 				
				FiboMin = temp_child;		//FiboMin points to child 				
			}
			Fib_Heap_Consolidate();	//Consolidating Heap				
		}
		else			//If z has no child
		{
			if(z == z->Right_Sibling)	//z is the only node in the heap
			{
				FiboMin = NULL;
			}
			else				//Multiple root nodes are present in the heap
			{
				//Removing z from the root List by rearranging pointers
				z->Left_Sibling->Right_Sibling = z->Right_Sibling;
				z->Right_Sibling->Left_Sibling = z->Left_Sibling;
				FiboMin = z->Right_Sibling;
				Fib_Heap_Consolidate();	//Consolidating Heap	
			}			
		}									
		NumNodes = NumNodes - 1;
		NodesMap.erase(z->key); //Removing entry related to Min Key from Map
	}	
	else
	{
		cout << "There are no Nodes in the Heap " << endl;
		error = true;
	}
     	return error;
}
/*********************************************************************************************************
Function Name            : findMin
Inputs                   :                           
Returns                  : It return Min Key in Heap, Otherwise NEGATIVE SENTINEL
Description              : This function returns Minimum Value from Heap
*********************************************************************************************************/
int FIBOHEAP :: findMin()
{
	int retval;
	if(FiboMin != NULL)
		retval = FiboMin->key;
	else					
		retval = NEGATIVE_SENTINEL;	//No Elements in Heap

	return retval;
}
/*********************************************************************************************************
Function Name            : update 
Inputs                   : (1) int key
			   (2) int new_key                          
Returns                  : It returns true if a node key is decreased successfully
Description              : This function decreases key value to a new value
*********************************************************************************************************/
bool FIBOHEAP :: update(int key, int new_key)
{
	bool 		error = false;	
	FIBOHEAPNode	*node;
	
	if(FiboMin == NULL)
	{
		cout << "There are no Elements in the Heap " << endl;
		error = true;
	}
	else if(new_key == key)
	{
		cout << "New Key is same as current key" << endl;
		error = true;
	}
	else if((node = NodesMap[new_key]) != NULL)
	{
		cout << "Node with new key " << new_key << " is already present in the heap " << endl;
		error = true;
	}
	else if(new_key < key)
	{
		error = decrease(key,new_key);	
		
	}
	else
		error = increase(key,new_key);		
     	
    	return error;
}

/*********************************************************************************************************
Function Name            : decrease 
Inputs                   : (1) int key
			   (2) int new_key                          
Returns                  : It returns true if a node key is decreased successfully
Description              : This function decreases key value to a new value
*********************************************************************************************************/
bool FIBOHEAP :: decrease(int key, int new_key)
{
	bool 		error = false;	
	FIBOHEAPNode	*node,*y;
		
	node = NodesMap[key];		
	if(node == NULL)
	{
		cout << "Node with Key " << key << " is not found in the Priority Queue " << endl;			
		error = true;
	}
	else
	{			
		cout << "Node with Key " << key << " is found in the Priority Queue " << endl;
		NodesMap.erase(key);	
		node->key = new_key;
		NodesMap[new_key] = node;
		cout << "Node with new Key " << new_key << " is found in the Priority Queue " << endl;
		y = node->Parent;
		if((y != NULL) && (node->key < y->key))
		{
			cout << "Parent Node Key is " << y->key << endl;
			Fib_Heap_Cut(node,y);		//Removing Child Node and adding to Root List
			Fib_Heap_CascadeCut(y);				
		}			
		if(node->key < FiboMin->key)
		{
			FiboMin = node;
		}
	}			

     return error;
}
/*********************************************************************************************************
Function Name            : increase
Inputs                   : (1) int key
Returns                  : It returns true if key value can be increased successfully, otherwise false
Description              : This function increases key value to new value
*********************************************************************************************************/
bool FIBOHEAP :: increase(int key, int new_key)
{
	bool 		error = false;
	int 		count = 0,min = POSITIVE_SENTINEL,updated = 0;	
	FIBOHEAPNode	*node,*node1,*y,*temp,*temp1;
		
	node = NodesMap[key];		
	if(node == NULL)
	{
		cout << "Node with Key " << key << " is not found in the Priority Queue " << endl;			
		error = true;
	}
	else
	{	
		node1 = node;		
		cout << "Node with Key " << key << " is found in the Priority Queue " << endl;		
		y = node->Child;
		if(y == NULL)
		{
			cout << "Node has no child" << endl;
			//Deleting Node from Map
			NodesMap.erase(node->key);
			node->key = new_key;
			//Adding Modified node into Map
			NodesMap[node->key] = node;			
		}
		else
		{
			while(y != NULL)
			{
				temp = y;
				min = POSITIVE_SENTINEL;
				count = 0;
				//Checking all child nodes to see if a node with smaller key is available
				while(((temp != y) && (count > 0)) || (count == 0))
				{
					if(min > temp->key)
					{
						min = temp->key;	
						temp1 = temp;					
					}
					cout << "Child Node Key " << temp->key << "min " << min << endl;
					temp = temp->Right_Sibling;
					count++;					
				}			
				//Child Node with smaller key is found
				if(temp1->key < new_key)
				{
					cout << "Child Node with smaller key is found" << endl;
					cout << "Swapping key " << temp1->key << " with " << new_key << endl;
					//Deleting Child Node from Map
					NodesMap.erase(temp1->key);
					//Deleting Node from Map		
					NodesMap.erase(key);
					temp1->key = new_key;
					//Adding Modified Child into Map
					NodesMap[temp1->key] = temp1;
					node->key = min;		
					//Adding Modified Node into Map
					NodesMap[node->key] = node;
					updated = 1;					
				}				
				else
				{	
					if(updated == 0)
					{
						cout << "No child found with smaller key " << endl;
						NodesMap.erase(node->key);
						node->key = new_key;
						NodesMap[node->key] = node;
					}
					break;
				}	
				y = temp1->Child;		
				node = temp1;
				key = new_key;
			}			
		}
		//If node is parent node and if it's modified key is smaller than FiboMin 
		if((node1->Parent == NULL) && (node1->key < FiboMin->key))
		{
			FiboMin = node;
		}
		temp = FiboMin;
		count = 0;
		while(((temp != FiboMin) && (count > 0))) //Filling Root Level Edges
		{
			if(temp->key < FiboMin->key)
				FiboMin = temp;
			count++;
			temp = temp->Right_Sibling;
		}

	}
	return error;
}
/*********************************************************************************************************
Function Name            : displayHeap
Inputs                   : (1) int                           
Returns                  : for 
Description              : This function displays heap elements and writes output into filename
*********************************************************************************************************/
void FIBOHEAP :: displayHeap(string filename)
{
     	FIBOHEAPNode	*temp,*child,*temp1,*temp2,*temp3;
	int 		count = 0, retval;
	string		tempstr;		
	stringstream	ss;	

	//Display Code 
	cout << endl << "Nodes List " << endl;
	if(FiboMin == NULL)
	{
		cout << "No nodes in Heap " << endl;
		Nodes_Count = 0;	
		Edges_Count = 0;
		retval = Write_Output(filename);
	}
	else
	{
		temp = FiboMin;	
		Nodes_Count = 0;	
		Edges_Count = 0;	
		strcpy(rootNodes_str,"{rank=same;"); //To display root level nodes at same height
		while(((temp != FiboMin) && (count > 0)) || (count == 0)) //Filling Root Level Edges
		{
			//cout << "temp Key is " << temp->key << endl;
			//Making string to display root level nodes at same height in the graph
			ss << temp->key;
			tempstr = ss.str();
			strcat(rootNodes_str,tempstr.c_str());
			strcat(rootNodes_str," ");
			ss.clear();
			ss.str("");
			count++;
			//Filling Root Level Nodes Links
			Graph_Edges_List[Edges_Count].u.Value = temp->key;
			Graph_Edges_List[Edges_Count].v.Value = temp->Right_Sibling->key;
			Graph_Edges_List[Edges_Count++].roottoroot = true;
			
			Graph_Edges_List[Edges_Count].u.Value = temp->Right_Sibling->key;
			Graph_Edges_List[Edges_Count].v.Value = temp->key;
			Graph_Edges_List[Edges_Count++].roottoroot = true;
			temp = temp->Right_Sibling;
			
		}	
		strcat(rootNodes_str,";}\n"); 				
		Recursive_Display(FiboMin); 	//Calling Recursive Fucntion to display		
		retval = Write_Output(filename);						
	}		
	
}
/*********************************************************************************************************
Function Name            : Recursive_Display
Inputs                   : (1) FIBOHEAPNode                          
Returns                  : 
Description              : This function Recursively Calls itself to display Heap Elements
*********************************************************************************************************/
void FIBOHEAP :: Recursive_Display(FIBOHEAPNode *current)
{
	FIBOHEAPNode	*temp1,*temp2;
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
		while(((temp2 != current) && (count > 0)) || (count == 0))			
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
		while(((temp2 != current) && (count > 0)) || (count == 0))			
		{
			//Adding Edges related to child level Siblings
			if(temp2->Parent != NULL)
			{
				cout <<"Child Sibling Edge u " << temp2->key << "Edge v " << temp2->Right_Sibling->key << endl;
				Graph_Edges_List[Edges_Count].u.Value = temp2->key;
				Graph_Edges_List[Edges_Count].v.Value = temp2->Right_Sibling->key;
				Graph_Edges_List[Edges_Count++].roottoroot = true;			

				Graph_Edges_List[Edges_Count].u.Value = temp2->Right_Sibling->key;
				Graph_Edges_List[Edges_Count].v.Value = temp2->key;
				Graph_Edges_List[Edges_Count++].roottoroot = true;			
			}		
			if(temp2->Parent != NULL)
			{
				cout << "Child Node " << temp2->key << "--->"<< temp2->Parent->key << ", Marked---" << temp2->bMark <<  endl;
				Graph_Nodes_List[Nodes_Count].Value = temp2->key;
				Graph_Nodes_List[Nodes_Count++].Marked = temp2->bMark;
				
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
				Graph_Nodes_List[Nodes_Count++].Marked = temp2->bMark;			
			}			
			Recursive_Display(temp2->Child);
			temp2 = temp2->Right_Sibling;
			count++; 
		}	
	}
}	
/*********************************************************************************************************
Function Name            : Fib_Heap_Consolidate 
Inputs                   : 
Returns                  : 
Description              : This function Consolidates Heap after extractMin Operation is performed
*********************************************************************************************************/
void  FIBOHEAP :: Fib_Heap_Consolidate()
{
	double		phi;
	bool		error = false;
	int		size,iter,d,count=0;
	FIBOHEAPNode	*x,*w,*y,*temp,*node1,*tempw;
	FIBOHEAPNode	**Arr;

	phi = (1+sqrt(5))/2; //Golden Ratio
	size = (int)(floor(log(NumNodes)/log(phi)));
	cout << "Size of the Array " << size << endl;
	size = size+1;

	//Creating an Array of Pointers
	try
	{
		Arr = new FIBOHEAPNode*[size+1];
	}catch(bad_alloc xa){
		error = true;
		cout << "Failed to Initialize memory for Array" << endl; 
	}

	//Initializing Array with Null
	for(iter = 0; iter <= size; iter++)
	{
		Arr[iter] = NULL;		
	} 
	w = FiboMin;
	cout << "Intial FiboMin key is " << FiboMin->key << endl;
	tempw = NULL;
	while(((w != FiboMin) && (count > 0)) || (count == 0)) //count is to traverse entire root list
	{
		x = w;
		d = x->degree;
		cout << "x key is " << x->key << ", x degree is " << x->degree << endl;		
		while(Arr[d] != NULL)
		{			
			y = Arr[d];
			cout << "y key is " << y->key << ", y degree is " << y->degree << endl;			
			if(x == y) break;	//If w crosses FiboMin
			if(tempw != NULL)
				tempw = NULL;
			if(x->key > y->key)
			{		
				if(x->Right_Sibling != y)		
				{					
					tempw = x->Right_Sibling;	//To visit next node in the root list
					cout << "Inside swap, tempw points to " << tempw->key << endl;
				}	
				temp = x;
				x = y;
				y = temp;				
			}						
			if(FiboMin == y)	//To check loop condition and exit
				FiboMin = x;			
			cout << "FiboMin Points to " << FiboMin->key << endl;
			Fib_Heap_Link(y,x);
			if((x->key < y->key) && (tempw == NULL))
			{
				cout << "Assigning tempw when there is no swap " << endl;
				tempw = x->Right_Sibling;				
			}
							
			Arr[d] = NULL;
			d = d + 1; 
		}
		Arr[d] = x;
		cout << "FIrst Array Element " << Arr[d]->key << endl;	
		if(tempw != NULL)	//If x and y are swapped	
		{
			w = tempw;
			tempw = NULL;
		}
		else			//If x and y are not swapped
		{							
			w = w->Right_Sibling;
		}					
		count++;
		cout << "w points to " << w->key << endl;
	}
	FiboMin = NULL;
	for(iter = 0; iter <= size; iter++)
	{
		//cout << "Root Node Key is " << Arr[iter]->key << endl;
		if(Arr[iter] != NULL)
		{
			node1 = Arr[iter];			
			cout << "Root Node Key is " << node1->key << endl;
			if(FiboMin == NULL)
			{				
				node1->Left_Sibling = node1;
				node1->Right_Sibling = node1;
				FiboMin = node1;					
			}
			else
			{
				cout << "Node Key is " << node1->key << endl;
				node1->Left_Sibling = FiboMin;
				FiboMin->Right_Sibling->Left_Sibling = node1;
				node1->Right_Sibling = FiboMin->Right_Sibling;		
				FiboMin->Right_Sibling = node1;
				if(node1->key < FiboMin->key)	//Updating Min Node if new node key is smaller
				{
					FiboMin = node1;
				}	
			}	
		}
	}			
	delete [] Arr;	//Deleting the Memory Assigned to Arr of Pointers
		
}	
/*********************************************************************************************************
Function Name            : Fib_Heap_Link 
Inputs                   : (1) FIBOHEAPNode x 
			   (2) FIBOHEAPNode y
Returns                  : 
Description              : It Links subtree rooted at node y to x
*********************************************************************************************************/
void FIBOHEAP ::  Fib_Heap_Link(FIBOHEAPNode *y,FIBOHEAPNode *x)
{
	FIBOHEAPNode	*temp;	
	
	//Removing y from root list	
	y->Left_Sibling->Right_Sibling = y->Right_Sibling;
	y->Right_Sibling->Left_Sibling = y->Left_Sibling;		
	
	//Make y child of x
	if(x->Child == NULL)	//No Childs to x
	{
		x->Child = y;
		y->Left_Sibling = y;
		y->Right_Sibling = y;
		y->Parent = x;
	}
	else			//x has some childs
	{
		temp = x->Child;
		x->Child = y;
		y->Parent = x;
		y->Right_Sibling = temp;
		y->Left_Sibling = temp->Left_Sibling;
		temp->Left_Sibling->Right_Sibling = y;
		temp->Left_Sibling = y;
	}	
	x->degree++;		//Incrementing x's degree
	y->bMark = false;	//Unmarking y as it is made child
}

/*********************************************************************************************************
Function Name            : Fib_Heap_Cut
Inputs                   : (1) FIBOHEAPNode x
			   (2) FIBOHEAPNode y                          
Returns                  : 
Description              : This function cuts subtree rooted at node x and places it root list
*********************************************************************************************************/
void  FIBOHEAP :: Fib_Heap_Cut(FIBOHEAPNode *x,FIBOHEAPNode *y)
{
	

	//Removing x from child list of y
	if(x->Right_Sibling != x)	//y has More than 1 child
	{
		y->Child = x->Right_Sibling;
		x->Right_Sibling->Parent = y;
		x->Right_Sibling->Left_Sibling = x->Left_Sibling;
		x->Left_Sibling->Right_Sibling = x->Right_Sibling;				
	}
	else				//y has only x as child
		y->Child = NULL;
	y->degree--; //Decrementing y degree
	//Adding x to the root nodes list 
	FiboMin->Right_Sibling->Left_Sibling = x;	
	x->Left_Sibling = FiboMin;
	x->Right_Sibling = FiboMin->Right_Sibling;	
	FiboMin->Right_Sibling = x;
	x->Parent = NULL;
	x->bMark = false;	//Unmarking Node when it is added to the root list
	
}
/*********************************************************************************************************
Function Name            : Fib_Heap_CascadeCut 
Inputs                   : (1) FIBOHEAPNode x                         
Returns                  : 
Description              : This function Cascadingly cuts nodes if the nodes were marked, otherwise 	marks them
*********************************************************************************************************/
void  FIBOHEAP :: Fib_Heap_CascadeCut(FIBOHEAPNode *y)
{
	FIBOHEAPNode	*z;

	z = y->Parent;
	if(z != NULL)
	{
		//If first child is cut from Non-root Node Mark it
		if(y->bMark == false)
		{
			cout << "y points to " << y->key << ",y Mark " << y->bMark << endl;	
			y->bMark = true;		
			cout << "y points to " << y->key << ",y Mark " << y->bMark << endl;	
		}
		//If 2nd child is cut call Recursive Cascade Cut
		else
		{
			Fib_Heap_Cut(y,z);			
			Fib_Heap_CascadeCut(z);
		}
	}	


}
int FIBOHEAP :: Write_Output(string optfile)
{	
	int 		retval = 0,mst_edge = 0, no_chars = 0, iter = 0;
	ofstream 	optstrm;
	char		buff[100];
	size_t 		pos=-1;
	string		tempstr;		
	stringstream	ss;
	

	cout << "Rank Nodes String " << rootNodes_str << endl;

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
				//Put the below code in else condition		
				for(iter = 0; iter < Nodes_Count; iter++)
				{
					cout << "Node Key " << Graph_Nodes_List[iter].Value << ", Node Marked "<< Graph_Nodes_List[iter].Marked << endl;
					ss << Graph_Nodes_List[iter].Value;	 
		 			tempstr = ss.str();
					strcpy(buff,tempstr.c_str());
					if(Graph_Nodes_List[iter].Marked)
					{
						strcat(buff,"[color=gray,style=filled]");
					}
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
							cout << "Edge u " << Graph_Edges_List[iter].u.Value <<  ", Edge v " << Graph_Edges_List[iter].v.Value << ", RootToRoot Edge " << Graph_Edges_List[iter].roottoroot << endl;
							
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
