// COMPILE: gcc assignment_5.c
// RUN: ./a
/*
33323
PROBLEM STATEMENT:
Implement the Deadlock Avoidance Algorithm: Bankers Algorithm.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


//Main function
int main() {

	int numberOfProcesses;
	int numberOfResources;
	printf(" \n+-------------------------------+ INPUT +-------------------------------+\n");
	// Input of number of processes and resources
	printf("Number of processes: \n");
	scanf("%d",&numberOfProcesses);
	printf("Number of resources: \n");
	scanf("%d",&numberOfResources);

	// Declaring matrices 
	int available[numberOfResources];
	int availableOriginal[numberOfResources];
	int maxNeeded[50][50];
	int allocated[50][50];
	int needMatrix[50][50];	
	int completed[50];
	int safeSequence[50];
	int safeIndex = 0;
	int requestedResources[numberOfResources];
	printf(" \n+-------------------------------+ MAX NEEDED +-------------------------------+\n");
	for(int i=0; i<numberOfProcesses; i++)
	{
		for(int j=0; j<numberOfResources; j++)
		{
			int temp;
			printf("Enter [%d,%d] of maximum needed matrix \n",i,j);
			scanf("%d",&temp);
			maxNeeded[i][j]=temp;
		}
	}
	printf("Maximum needed matrix: \n");
	for(int i=0;i<numberOfProcesses;i++)
	{
		completed[i]=0;
		for(int j=0;j<numberOfResources;j++)
		{
			printf("%d \t",maxNeeded[i][j]);
		}
		printf("\n");
	}
	printf(" \n+-------------------------------+ ALLOCATED +-------------------------------+\n");
	for(int i=0;i<numberOfProcesses;i++)
	{
		for(int j=0;j<numberOfResources;j++)
		{
			int temp;
			printf("Enter [%d,%d] of allocated matrix \n",i,j);
			scanf("%d",&temp);
			allocated[i][j]=temp;
		}
	}
	printf("Allocated matrix: \n");
	for(int i=0;i<numberOfProcesses;i++)
	{
		completed[i]=0;
		for(int j=0;j<numberOfResources;j++)
		{
			printf("%d \t",allocated[i][j]);
		}
		printf("\n");
	}
	printf(" \n+-------------------------------+ RESOURCES +-------------------------------+\n");
	
	for(int i=0;i<numberOfResources;i++)
	{
		int temp;
		printf("Enter availiblity of resources [%d] \n", i+1);
		scanf("%d",&temp);
		available[i]=temp;
		
	}
	for(int i=0;i<numberOfResources;i++)
	{
		availableOriginal[i]=available[i];
		
	}
	
	printf("Need matrix: \n");
	for(int i=0;i<numberOfProcesses;i++)
	{
		completed[i]=0;
		for(int j=0;j<numberOfResources;j++)
		{
			needMatrix[i][j]=maxNeeded[i][j]-allocated[i][j];
			printf("%d \t",needMatrix[i][j]);
		}
		printf("\n");
	}
	printf("Completed matrix: \n");
	for(int i=0;i<numberOfProcesses;i++)
	{	
		printf("%d \t",completed[i]);
		printf("\n");
	}
	
	// Calculation
	int calculate(){
		// Setting completed to zero
		for(int i=0;i<numberOfProcesses;i++)
		{	
			completed[i]=0;
		}
		for(int i=0;i<numberOfResources;i++)
		{
			available[i]=availableOriginal[i];
		
		}
	
		safeIndex=0;
		
		while(1)
		{	
			int allDone=1;
			// If all processes completed => break
			for(int i=0;i<numberOfProcesses;i++)
			{
				if(completed[i]==0)
				{
					allDone=0;
				}
			}
			if(allDone==1)
			{
				printf("\nCOMPLETED!!\n");
				printf(" \n+-------------------------------+ SAFE SEQUENCE +-------------------------------+\n");
				for(int i=0;i<numberOfProcesses;i++)
				{
					if(i==numberOfProcesses-1)
					{
						printf("%d ",safeSequence[i]);
						printf("\n");
					}
					else
					{
						printf("%d -> ",safeSequence[i]);
					}
					
				}
				printf(" \n+-------------------------------++-------------------------------+\n");
				return 1;
			}
			
			int zeroChanges=1;
			for(int i=0;i<numberOfProcesses;i++)
			{
				if(completed[i]==0)
				{
					int allNeedsLesser=1;
					for(int j=0;j<numberOfResources;j++)
					{
						if(needMatrix[i][j]>available[j])
						{
							allNeedsLesser=0;
						}
					}
					if(allNeedsLesser==1)
					{
						for(int j=0;j<numberOfResources;j++)
						{
							available[j]=available[j]+allocated[i][j];
							
						}
						zeroChanges=0;
						safeSequence[safeIndex]=i+1;
						safeIndex++;
						completed[i]=1;
					}
						
				}
			}
			if(zeroChanges)
			{
				printf("ERROR!! NOT POSSIBLE!! \n");
			
				return 0;
			}
			printf("\nCompleted matrix after traversal: \n");
			for(int i=0;i<numberOfProcesses;i++)
			{	
				printf("%d \t",completed[i]);
				
			}
			printf("\n");
			
		}
	}
	calculate();
	void resourceRequest()
	{
		  int processNo;
		  printf("\nEnter process number: ");
		  scanf("%d",&processNo);
		  
		  for(int i=0;i<numberOfResources;i++)
		  {
		  	printf("\nEnter the units of resource [%d] requested: ",i+1);
		  	scanf("%d",&requestedResources[i]);
		  }
		  
		  for(int j=0;j<numberOfResources;j++)
		  {
		    // Checking if resources requested do no cross max needed for that process
		    if(requestedResources[j]<=maxNeeded[processNo][j])  
		    {
			// Checking if resources requested do no cross available resources
			if(requestedResources[j]<=available[j])
			{
				availableOriginal[j]=availableOriginal[j]-requestedResources[j];
				allocated[processNo][j]=allocated[processNo][j]+requestedResources[j];
				needMatrix[processNo][j]=needMatrix[processNo][j]-requestedResources[j]; 
			 }
			else
			{
			      printf("\nERROR: Process exceededing available resources!!\nRequest CANNOT be accepted!");
			      return;
			}
		    }
		    else
		    {
				printf("\nERROR: Process exceededing maximum limit of resources!!\nRequest CANNOT be accepted!");
		   		return;
		    }
		  }
		int status=calculate();
		if(status==1)
		{
			printf(" \n+-------------------------------+ REQUEST ACCEPTED +-------------------------------+\n");
		}
		else
		{
			 for(int j=0;j<numberOfResources;j++)
		  	{
		  		availableOriginal[j]=availableOriginal[j]+requestedResources[j];
				allocated[processNo][j]=allocated[processNo][j]-requestedResources[j];
				needMatrix[processNo][j]=needMatrix[processNo][j]+requestedResources[j]; 
			}
		  	
			printf(" \n+-------------------------------+ REQUEST REJECTED +-------------------------------+\n");
			printf(" \n+-------------------------------+ NO SAFE SEQUENCE +-------------------------------+\n");
		}


	}

	while(1)
	{
		printf(" \n+-------------------------------+ MENU  +-------------------------------+\n");
		printf("\n1) Press'+' to enter new request.\n2) Press '-' to terminate. \n");
		char choice;
		scanf("%c",&choice);
		if(choice=='+')
		{
			resourceRequest();
		}
		else if(choice == '-')
		{
			break;
		}
	}
	printf("\n +-------------------------------+ THANK YOU  +-------------------------------+\n");
	return 0;
	
}

