#include <stdio.h>

#define PROCESSES 50
#define RESOURCES 50


int max[PROCESSES][RESOURCES], allocate[PROCESSES][RESOURCES], need[PROCESSES][RESOURCES],available[RESOURCES], currentWorking[RESOURCES], safeSequence[PROCESSES], completed[PROCESSES];

// Common function to print matrices
void printMatrix(int n, int m)
{
    int i, j;
    printf("\nMax Matrix : \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d \t", max[i][j]);
        }
        printf("\n");
    }

    printf("\nAllocate Matrix : \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d \t", allocate[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailability Matrix : \n");
    for(i = 0; i < m; i++)
    {
        printf("%d \t", available[i]);
    }
}

void arrangeProcess(int p, int r)
{
    int currentWorking[r];
    int i, j, index = 0, u = 0, k = 0;
    int needFlag = 0;
    // if available>need => 0, 1 otherwise

    // Copy availibility matrix into currentWorking matrix
    for(i = 0; i < r; i++)
    {
        currentWorking[i] = available[i];			
    }

    for(k = 0; k < p; k++)
    {
        for(i = 0; i < p; i++)
        {
            if (completed[i] == 0)
            {               
                needFlag = 0;
                for(j = 0; j < r; j++)
                {
                    // Need > Available
                    if (need[i][j] > currentWorking[j]) 
                    {
                        needFlag = 1;		
                        break;
                    }
                }
                
                
                // If Need < Available => Allocate resources
                if (needFlag == 0)
                {
                    safeSequence[index++] = (i + 1);
                    completed[i] = 1;
                    for(u = 0; u < r; u++)
                    {
                        currentWorking[u] += allocate[i][u];
                    }
                }
            }
        }
    }
}

// Function to calculate need matrix 
void calculateNeed(int p, int r)
{
    int i, j;
    for(i = 0; i < p; i++)
    {
        for(j = 0; j < r; j++)
        {
            // Need = Max - Allocated
            need[i][j] = max[i][j] - allocate[i][j];	
        }
    }   

    printf("\n\nNeed Matrix : \n");
    for(i = 0; i < p; i++)
    {
        for(j = 0; j < r; j++)
        {
            printf("%d \t", need[i][j]);
        }
        printf("\n");
    }

}

// Check if any element of completed array is 0 or not
int check(int p, int r)
{
    int i;
    for (i = 0; i < p; i++)
    {
        // If any element of complete matrix is zreo then it is not safe
        if (completed[i]==0)
        {
            return 0;			
        }
    }
    return 1;
}


// Function to get data of all matrices
void getData(int n, int m)
{
    int i, j;
    
    printf("\n\nMax Matrix : \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("\nProcess[%d] Resource[%d]: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("\n\nAllocation Matrix : \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("\nProcess[%d] Resource[%d]: ", i, j);
            scanf("%d", &allocate[i][j]);
        }
    }
    
    printf("\n\nAvailability matrix : \n");
    for(i = 0; i < m; i++)
    {
        printf("\nResource[%d]: ", i);
        scanf("%d", &available[i]);
    }
	
	
	// Initially set all elements of the completed matrix to 0
    for(i = 0; i < n; i++)
    {
        completed[i] = 0;
    }
}


// Resource Request Algorithm
int resourceRequest(int p, int r)
{    
    printf("\n------------------------- REQUESTUNG RESOURCES -------------------------\n");
    int i = 0, process, resReq[r];
    
    // Get Process number and requested resources 
    printf("\nProcess Number: ");
    scanf("%d", &process);
    printf("\nrRequests: \n");
    for(i = 0; i < r; i++)
    {
        printf("\nRequest for process[%d]: ", i);
        scanf("%d", &resReq[i]);
    }

	
	// If request > need => return 0 
    // Else update need matrix by subtracting resource request
    for(i = 0; i < r; i++)
    {    	
        if (resReq[i] > need[process][i])
        {
            printf("Resource[%d] request is greater than the need for process[%d]", i, process);
            return 0;
        }
        
        else
        {
            need[process][i] -= resReq[i];
        }
    }

    // If request > available return 0 
    // Else update available matrix by subtracting resource request
    for(i = 0; i < r; i++)
    {
        if (resReq[i] > available[i])
        {
            printf("Resource[%d] Request is greater than availibility for Process[%d]", i, process);
            return 0;
        }
        else
        {
            available[i] -= resReq[i];
        }
    }

    // Updating allocation matrix
    for(i = 0; i < r; i++)
    {
        allocate[process][i] += resReq[i];
    }

    // Schedule processes for given request
    arrangeProcess(p, r);
    printMatrix(p, r);
    return (check(p, r));
}

// Function to print safety sequence
void printSafeSeq(int p)
{

    int i;
    for(i = 0; i < p; i++)
    {
        printf("%d -> ", safeSequence[i]);
    }

}


int main()
{
    int processNumber, resourseNumber;
    printf("\n------------------------- BANKER'S ALGORITHM  -------------------------\n");
    printf("Banker's Algorithm");
    printf("\nNumber of processes: ");
    scanf("%d", &processNumber);
    printf("\nNumber of resources: ");
    scanf("%d", &resourseNumber);

    // Get and display the matrix data
    getData(processNumber, resourseNumber);
    printMatrix(processNumber, resourseNumber);

    // Calculate need matrix.
    calculateNeed(processNumber, resourseNumber);

    // Scheduling process
    arrangeProcess(processNumber, resourseNumber);

    // Check whether the given situation is safe
    if (check(processNumber, resourseNumber))
    {
        printf("\nSafe Sequence: ");
        printSafeSeq(processNumber);
        // Resource request algorithm
        if (resourceRequest(processNumber, resourseNumber))
        {
            printf("\n!!!!!!!!!!!!!!!!!!! REQUEST GRANTED !!!!!!!!!!!!!!!!!!!\n");
            printf("\nSafe sequence: ");
            printSafeSeq(processNumber);
        }
        else
        {
            printf("\n!!!!!!!!!!!!!!!!!!! REQUEST NOT GRANTED !!!!!!!!!!!!!!!!!!!\n");
        }
    }
    else
    {
        printf("\n!!!!!!!!!!!!!!!!!!! DEADLOCK !!!!!!!!!!!!!!!!!!!\n");
    }
    return 0;
}