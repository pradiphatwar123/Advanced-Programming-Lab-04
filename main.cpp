


#include "heap.h"

PRIORITY_QUEUE 	*pqPtr;
BINHEAP  	BinObj;
BINOMHEAP 	BinomObj;
FIBOHEAP 	FiboObj;
bool 		BinFlag,BinomFlag,FiboFlag;

int	      Nodes_Count = 0, Edges_Count = 0;
Node	      *Graph_Nodes_List;		//Pointer to Graph Vertices dynamic Array
Edge	      *Graph_Edges_List;		//Pointer to Graph Edges dynamic Array
char	      rootNodes_str[1000];	

int main(int argc,char *argv[])
{
    
	if(Validate_Cmdline(argc,argv) == -1)  // Check if proper number of inputs are not given in the command line
	{   
		cout << "Error: valid command for execution is <./a.out> -<option>"<< endl;
		cout << "Exiting ....." <<endl;
		exit(-1);		
	}
        else
	{
		if(BinFlag)
			pqPtr = &BinObj;
		else if(BinomFlag)
			pqPtr = &BinomObj;
		else 
			pqPtr = &FiboObj;			
		ShowMenu();		            	
     	}         

	return 0;
}
/******************************************************************************************************
command validation
*******************************************************************************************************/

int Validate_Cmdline(int argc,char *argv[])
{
	int 	error=0;
	string	tempstr, tempstr1;

	if(argc < 2)	
	{	
		cout << "Error: valid command for execution is " << endl;
		cout << "<exename> -<option>"<< endl;		
		error = -1;
	}		
	else
	{
		tempstr1 = argv[1];		
		tempstr = tempstr1.substr(1, strlen(argv[1]) - 1);	
		cout << "User Option Entered is " << tempstr << endl;

		if(tempstr.compare("binary") == 0)
		{			
			BinFlag = true;			
 		}	
		else if(tempstr.compare("binomial") == 0 )
		{		
			BinomFlag = true;
 		}
		else if(tempstr.compare("fibonacci") == 0)
		{		
			FiboFlag = true;
 		}	
		else
		{
			cout << "Error: Invalid Option " << endl;
			error = -1;	
		}
	}
	return error;        
}
// MENU
void ShowMenu(void)
{
	string	filename;
	int 	option,keyVal,new_key;	
	bool	retval;
	int	result;

	retval = pqPtr->makeHeap();
	if(retval)
	{
		while(1)
            	{
                     cout<<"\n MENU :Operations on Priority Queue";
                     cout<<"\n 1.Insert Element";
                     cout<<"\n 2.Delete Element";
                     cout<<"\n 3.Extract Minimum Element";
                     cout<<"\n 4.Find Minimum Element";
                     cout<<"\n 5.Update Element key Value";                    
                     cout<<"\n 6.Display Heap";
                     cout<<"\n 7.Exit";
                     cout<<"\n Please Enter Your Option  ";
                     cin>>option;
                     switch(option)
                     {
                                   case 1:
					cout << "Enter Key to insert" << endl;
                                        cin>>keyVal;
                                        if(!pqPtr->insert(keyVal))
                                        {
                                             cout<<"\nkey Inserted successfully";                    
                                        }
                                        else
                                            cout<<"\nError In Insertion";
                                        
                                        break; 
                                   
                                   case 2:
					cout << "Enter Key to delete" << endl;				       
                                        cin>>keyVal;
                                        if(!pqPtr->deleteKey(keyVal))
                                        {
                                             cout<<"\nkey Deleted successfully";                    
                                        }
                                        else
                                            cout<<"\nError In Deletion";

                                         break;
                                  
                                   case 3:
                                        if(!pqPtr->extractMin())
                                        {
                                            cout<<"\nMin Extraction successful";                    
                                        }
                                        else
                                            cout<<"\nError In extractMin";

                                        break;
                                   
                                   case 4:
                                        
					result = pqPtr->findMin();
					if(result != NEGATIVE_SENTINEL)
					{
                                            cout<<"\nMinimum Node in the Heap is " << result << endl;                    
                                        }
                                        else
                                            cout<<"\nNo Nodes in Heap " << endl;
                                        break;
                                   
                                   case 5:
					cout << "Enter Key " << endl;
                                        cin>>keyVal;
					cout << "Enter new key value " << endl;
					cin >> new_key;
                                        if(!pqPtr->update(keyVal,new_key))
                                        {
                                            cout<<"\n Update Successful";                    
                                        }
                                        else
                                            cout<<"\nError In Updation";
                                        break;                                  
                                   
                                   case 6:          
					cout << "Enter FileName " << endl;
					cin >> filename;                           				
                                        pqPtr->displayHeap(filename);
                                        
					break;                                   
                                   case 7:
                                        exit(0);

                                        break;                                                       
                                   default: 
                                        cout<<"\n Wrong Choice, Please Enter Valid choice";
                                                                                   
                     }            
                    
      	      }
	}
	else
	{
		cout << "Error: Failed to Initialize Heap " << endl;
	}
}
