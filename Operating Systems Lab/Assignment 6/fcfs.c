#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>
#include <math.h>
#include <string.h>



//Main function
int main() {
	int sizeOfQueue;
	//accept input
	printf("Enter number of page frames:- \n");
	scanf("%d",&sizeOfQueue);
	int queue[sizeOfQueue];
	//fill whole array with -1
	memset(queue, -1, sizeOfQueue*sizeof(queue[0]));
	int sizeOfInputString;
	//accept input
	printf("Enter size of input string:- \n");
	scanf("%d",&sizeOfInputString);
	char str[sizeOfInputString];
	printf("Enter input string:- \n");
	scanf("%s", str);
	int currIndex=0;
	int miss=0;
	int searchInQueue(int target)
	{
		for(int i=0;i<sizeOfQueue;i++)
		{
			if(queue[i]==target-48)
			{
				return 1;
			}
		}
		return 0;
	}
	void displayQueue()
	{
		for(int i=0;i<sizeOfQueue;i++)
		{
			printf("%d\t",queue[i]);
		}
		printf("\n");
	}
	for(int i=0;i<sizeOfInputString;i++)
	{
		int found=searchInQueue(str[i]);
		if(found)
		{
			printf("\nHIT!!\n");
			displayQueue();
			continue;
		}
		miss++;
		printf("\nMISS!!\n");
		queue[currIndex]=str[i]-48;
		currIndex=(currIndex+1)%sizeOfQueue;
		displayQueue();
	}
	printf("\nThe hit ratio is: %d\n",(sizeOfInputString-miss));
	return 0;
	
}