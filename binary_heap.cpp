/***********************************************************************************888
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :  04 - Implementation of Binary Heap Priority Queue

File name         :  BINOM_HEAP.CPP

Description       :  Implements Interfaces for PRIORITY QUEUE Abstract Data Type (ADT) using BINARY HEAP

Programmers       :  (1) Pradeep Hatwar    (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++ 4.6

Date created      :  30/10/2013

List of functions :
                  (1)  BINHEAP(); 
                  (2)  ~BINHEAP(); 
                  (3)  bool makeHeap();	
                  (4)  bool insert(int);
                  (5)  bool deleteKey(int);
                  (6)  bool extractMin();
                  (7)  int  findMin();
	          (8)  bool update(int, int);		             
                  (9)  void displayHeap(string );
		  (10) bool decrease(int,int);
                  (11) bool increase(int,int);	
                  (12) bool BinHeapify(int);
	          (13) bool Down_Travel(int);             
	          (14) int  Write_Output(string);	 				 
History           :  

*************************************************************************************************/


#include<iostream>
#include<math.h>
#include<cstdlib>
#include<ctype.h>
#include<fstream>
#include<cstring>
#include<sstream>


#include"heap.h"
using namespace std;

BINHEAPNode 	*binHead;
int     	size;
int 		heap[1000];

extern int	      Nodes_Count, Edges_Count;
extern Node	      *Graph_Nodes_List;		//Pointer to Graph Vertices dynamic Array
extern Edge	      *Graph_Edges_List;		//Pointer to Graph Edges dynamic Array

/*********************************************************************************************************
Function Name            : BINHEAP
Inputs                   : void                       
Returns                  : void
Description              : Constructor
*********************************************************************************************************/

BINHEAP :: BINHEAP()
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
Function Name            : ~BINHEAP
Inputs                   : void                       
Returns                  : void
Description              : Destructor
*********************************************************************************************************/

BINHEAP ::~BINHEAP()
{
	
}

/*********************************************************************************************************
Function Name            : makeHeap 
Inputs                   : void                          
Returns                  : false In case of any error occurred during makeHeap operation on Binay Heaps
                           true In case of successfull makeHeap operation on Binary Heap
Description              : This function makes Heap
*********************************************************************************************************/

bool BINHEAP::makeHeap()
{    
	size=0;
     
	return true;
}
/*********************************************************************************************************
Function Name            : insert 
Inputs                   : int - key                          
Returns                  : true -In case of any error occurred during insert operation on Binary Heap
                           false -In case of successfull insert operation on Binary Heap
Description              : This function inserts node with 'key' field into binary heap 
*********************************************************************************************************/

bool BINHEAP::insert(int key)
{
           bool error = false;
	   int iter;
	
	   for(iter = 0; iter < size; iter++)          // checking the key whether it is already present in the heap or not
	   {
		if(heap[iter] == key)                      ////if key present then return error
		{
			cout << "Node with key " << key << " is already present in the heap" << endl;  
			error = true;
			break;
		}	
	   }
	   if(!error)                                //otherwise insert the key into the heap
	   {	
           	heap[size++]=key;
           	if(size>1) BinHeapify(size-1);
	   }
	
           return error;
}

/*********************************************************************************************************
Function Name            : deleteKey 
Inputs                   : int - key 
Returns                  : true In case of any error occurred during deleteKey operation on Binary Heap
                           false In case of successfull deleteKey operation on Binary Heap
Description              : This function deletes node with 'key' field from Binary heap
*********************************************************************************************************/

bool BINHEAP::deleteKey(int key)
{
	bool error = false;
        int i=0,temp;
	
        while(heap[i]!=key && i<size) i++;                 // check whether the key is present in the heap or not                                               
                 if(i==size)                                // if not present then print the error message                                               
				{
				 cout<<"\nKey NOT FOUND!!!!\n\n";	
					error = true;
				}
                            else
                            {
                                if(i==size-1) size--;           //if KEY is last in array then simply decreasing size.
                                else
                                    {
                                                   heap[i]=heap[--size];
                                                   Down_Travel(i);
                                    }
                                }
                    return error;

}

/*********************************************************************************************************
Function Name            : extractMin 
Inputs                   : void                         
Returns                  : false In case of any error occurred during extractMin operation on Binary Heap
                           true In case of successfull extractMin operation on Binary Heap
Description              : This function deletes node whose key is minimum from the Binary Heap
*********************************************************************************************************/

bool BINHEAP::extractMin()
{
     bool error=false;
     int k=-1;

     if(size == 0)
     {	 
	 cout<<"\nHeap is EMPTY\n\n";
	 error = true;
     }
     else
     {
         k=heap[0];
         deleteKey(heap[0]);
	 cout<<" minimum value"<<k;
     }     
     
     return error;
}                                                                         

/*********************************************************************************************************
Function Name            : findMin 
Inputs                   : void                         
Returns                  : false In case of any error occurred during findMin operation on Binary Heap
                           true In case of successfull findMin operation on Binomial Heaps
Description              : This function finds and returns the minimum 'key' from the ven Binary Heap
*********************************************************************************************************/            

int BINHEAP::findMin()
{       
	int 	retval;  
            
        if(size > -1) 
	{
        	cout<<"minimum value " <<heap[0];
		retval = heap[0];
	}
        else 
        {     
		retval = NEGATIVE_SENTINEL;
        }                          
	return retval;
}


bool BINHEAP :: update(int key, int new_key)
{
	bool 		error = false, found = false;		
	int iter;
	
	for(iter = 0; iter < size; iter++)
	{
		if(heap[iter] == new_key)
		{			
			found = true;
			break;
		}	
	}
	if(size == 0)
	{
		cout << "There are no Elements in the Heap " << endl;
		error = true;
	}
	else if(new_key == key)
	{
		cout << "New Key is same as current key" << endl;
		error = true;
	}
	else if(found == true)
	{
		cout << "Node with key " << key << " is already present in the heap" << endl;
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
Inputs                   : int key                         
Returns                  : false In case of any error occurred during decrease operation on Binary Heap
                           true In case of successfull decrease operation on Binary Heap
Description              : This function decreases the key value with the user given key value
*********************************************************************************************************/             

bool BINHEAP::decrease(int key, int new_key)
{
           bool error=false;
           int i=0,k;

           while(heap[i]!=key && i<size) i++;
           if(i==size) 
		{
		cout<<"\nKey NOT FOUND!!!!\n\n";
		error = true;
	   }
           else
           {
                      k = new_key;		                
                      heap[i]=k;
                      BinHeapify(i);                      
           }

           return error;
}

/*********************************************************************************************************
Function Name            : increase 
Inputs                   : int key                         
Returns                  : false In case of any error occurred during increase operation on Binary Heap
                           true In case of successfull increase operation on Binary Heap
Description              : This function increases the key value with the user given key value
*********************************************************************************************************/  

bool BINHEAP::increase(int key, int new_key)
{
     bool error = false;
     int i=0,k;
     while(heap[i]!=key && i<size) i++;
     if(i==size)
	{ 
		cout<<"\nKey NOT FOUND!!!!\n\n";	
		error = true;
	}
     else
     {
          k = new_key;
            heap[i]=k;
                Down_Travel(i);
      }

         return error;
}

/*********************************************************************************************************
Function Name            : displayHeap 
Inputs                   : int file                         
Returns                  : false In case of any error occurred during displayHeap operation on Binary Heap
                           true In case of successfull displayHeap operation on Binary Heap
Description              : This function increases the key value with the user given key value
*********************************************************************************************************/  
void BINHEAP::displayHeap(string filename)
{
	int temp;
                   cout<<"\n\n\n";
		   Nodes_Count  = 0;
		   Edges_Count = 0;	
                   for(int i=0;i<size;i++) 
		   {
				Graph_Nodes_List[Nodes_Count].Value = heap[i];
				Graph_Nodes_List[Nodes_Count++].Marked = false;
				
				if(i > 0)
				{	
					Graph_Edges_List[Edges_Count].u.Value = heap[i];
					temp = floor((i+1)/2) - 1;
					//cout << "Parent Index inside Display Heap " << temp << ", i " << i << endl;	
					Graph_Edges_List[Edges_Count].v.Value = heap[temp];
					Graph_Edges_List[Edges_Count++].roottoroot = false;
				} 	
				cout<<heap[i]<<" ";
		    }
		    if(size == 0 )
			cout << "No nodes in the Heap " << endl;	
		    Write_Output(filename);
                   cout<<"\n\n\n";		  
}

/*********************************************************************************************************
Function Name            : BinHeapify 
Inputs                   : int location                         
Returns                  : false In case of any error occurred during BinHeapify operation on Binary Heap
                           true In case of successfull BinHeapify operation on Binary Heap
Description              : This function maintains the min heap property 
*********************************************************************************************************/  


bool BINHEAP::BinHeapify(int location)            // to locate the index for inserted key
{
                            bool error;
                            int size=location+1,temp;
                            while(heap[size-1]<heap[(size/2)-1] && size>1)
                            {
                                                          temp=heap[(size/2)-1];
                                                          heap[(size/2)-1]=heap[size-1];
                                                          heap[size-1]=temp;
                                                          size=size/2;                      // parent index
                            }

                            return error;
}


bool BINHEAP::Down_Travel(int location)
{
                              bool error=0;
                              int j=location, temp;
                              while((2*j+2)<size && (heap[2*j+1]<heap[j] || heap[2*j+2]<heap[j]))  // if both child present then check that at least one
                                                                                                   //  the child key is lesser than parent
                              {
                                                     if(heap[2*j+1]<heap[j] && heap[2*j+1]<heap[2*j+2])  //left child key is lesser than it's parent and sibling
                                                     {
                                                                     temp=heap[j];
                                                                     heap[j]=heap[2*j+1];
                                                                     heap[2*j+1]=temp;
                                                                     j=2*j+1;
                                                     }
                                                     else                                                // otherwise exchange parent with right child
                                                     {
                                                         temp=heap[j];
                                                         heap[j]=heap[2*j+2];
                                                         heap[2*j+2]=temp;
                                                         j=2*j+2;
                                                     }
                              }
                              if((2*j+1)<size && heap[2*j+1]<heap[j] )                                   // if only left child present
                              {
                                                  temp=heap[j];
                                                  heap[j]=heap[2*j+1];
                                                  heap[2*j+1]=temp;
                              }
                              return error;
}




int BINHEAP :: Write_Output(string optfile)
{	
	int 		retval = 0,mst_edge = 0, no_chars = 0, iter = 0;
	ofstream 	optstrm;
	char		buff[100];
	size_t 		pos=-1;
	string		tempstr;		
	stringstream	ss;
	
	cout << "Inside Write_Output " << endl;
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
							
							ss << Graph_Edges_List[iter].v.Value;	 
		 					tempstr = ss.str();
							strcpy(buff,tempstr.c_str());
																					
							strcat(buff," ");
							strcat(buff,"->");
							strcat(buff," ");
							
							ss.clear();
							ss.str("");
						
							ss << Graph_Edges_List[iter].u.Value;	 
		 					tempstr = ss.str();
							strcat(buff,tempstr.c_str());
							

							ss.clear();
							ss.str("");

							strcat(buff," ");
							if(Graph_Edges_List[iter].roottoroot)//For Root Level Edges
							{
								strcat(buff,"[style=dotted]");
							
							}
							/*else		//For Non-Root Level
							{
								strcat(buff,"\",style=dotted]");
							}*/
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
