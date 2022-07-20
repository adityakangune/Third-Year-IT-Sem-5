// COMPILE : gcc assignment2bparent.c -o 2Boutput
// EXECUTE : ./2Boutput

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#define MAXSIZE 50

// Function to print array on console
void print_arr(int arr[MAXSIZE], int n) {
    int i;
    printf("[");
    for(i = 0; i < n - 1; i++) {
        printf(" %d, ",arr[i]);
    }
    printf(" %d ]", arr[i]);
    printf("\n");
}

// Quick Sort
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[MAXSIZE], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(int array[MAXSIZE], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

void main() {
    // Declare the variables
    int arr[MAXSIZE], n;
    pid_t pid;

    // The main proces starts
    printf("\n This is the main process - ");
    printf("\n Process ID: %d", getpid());
    printf("\n Parent ID: %d \n", getpid());

    // Take the array input
    printf("\n Enter number of elements: ");
    scanf("%d", &n);
    printf("\n Enter the array elements:");
    for(int i = 0; i < n; i++) {
        printf("\n Enter the element [%d] : ", i);
        scanf("%d", &arr[i]);
    }

    // Sorting the array
    printf("\nSorted array using QUICKSORT: ");
    quickSort(arr, 0, n - 1);
    print_arr(arr, n);

    // Fork System call
    printf("Forking the current proces - \n");
    pid = fork();

    if(pid == -1) {
        printf("Unfortunately the pid was not born");
    }
    else if(pid == 0) {
        // Inside the child process
        printf("\n This is the pid process!");
        printf("Current pid is: %d", getpid());

        int i;
		    char *buffer[n+1];
	
        // arg 0 = name of executable file
        buffer[0] = "./binary";
    

        for(i = 1; i < n + 1; i++) {
            // Allocating memory
            buffer[i] = malloc(10);
            snprintf(buffer[i], 10, "%d", arr[i - 1]);
        }

        // Setting last element to NULL
        buffer[i] = NULL;
        // print_arr(buffer);

        // Calling pid proces on top of parent (overriding)
        execv("./binary", buffer);

        printf("\n\n CHILD EXECUTED SUCCESSFULLY \n\n");

    }

    else {
        // Inside parent process
        printf("\n This is the parent process!");
        printf("\n Current proccess ID is: %d", getpid());
        printf("\n Child ID is: %d", pid);
        printf("\n-------------- PARENT IS WAITING FOR CHILD TO COMLPETE --------------");
        wait(NULL);
        printf("\n\n Parent executed successfully \n\n");
    }
    
}


// #include<stdio.h>
// #include<unistd.h>
// #include<sys/types.h>
// #include<sys/wait.h>
// #include<stdlib.h>
// #define MAXSIZE 10

// // function to print the array
// void print(int arr[MAXSIZE], int n) {
// 	printf("\n Array is: ");
// 	for (int i=0; i<n; i++) 
// 		printf(" %d ", arr[i]);
		
// }


// //quick sort
// void quicksort(int arr[MAXSIZE],int first,int last)
// {
//     int temp;
//     if (first < last) {
//     	int pivot = first;
//     	int i = first;
//     	int j = last;
    	
//     	while (i < j) {
//     		while (arr[i] <= arr[pivot] && i < last) 
//     			i++;
//     		while (arr[j] > arr[pivot])
//     			j--;
    		
//     		if (i < j) {
//     			temp = arr[i];
//     			arr[i] = arr[j];
//     			arr[j] = temp;
//     		}
//     	}
    	
//     	temp = arr[pivot];
//     	arr[pivot] = arr[j];
//     	arr[j] = temp;
    	
//     	quicksort(arr,first,j-1);
//     	quicksort(arr,j+1,last);
//     }
// }

// //main
// void main() {
// 	int arr[MAXSIZE], n;
// 	pid_t pid;
	
// 	printf("\nMain Process is starting...\n ");
// 	printf("\nProcess ID: %d",getpid());
// 	printf("\nParent ID: %d",getppid());
	
// 	printf("\nEnter the size of array:");
// 	scanf("%d", &n);
// 	printf("\nEnter the elements:");
// 	for (int i = 0; i<n; i++) {
// 		printf("\narr[%d]:", i);
// 		scanf("%d", &arr[i]);
// 	}
	
// 	print(arr, n);
	
// 	printf("\nSorted array using Quick sort: ");
// 	quicksort(arr, 0, n-1);
	
// 	print(arr, n);
	
// 	printf("\nForking the current Process...");
// 	pid = fork();
	
// 	if (pid == -1)
// 		printf("Child was not created :(");
// 	else if (pid == 0) {
// 		printf("\n\n\nGreetings from the pid process!");
// 		printf("\nChild Process ID: %d", getpid());
		
// 		int i;
// 		char *buffer[n+1];
// 		buffer[0] = "./pid";
		
// 		for (i=1; i<n+1; i++) {
// 			buffer[i] = malloc(7);
// 			snprintf(buffer[i], 7, "%d", arr[i-1]);
// 		}
		
// 		buffer[i] = NULL;
		
// 		execv("./pid", buffer);
		
// 		printf("\n\n[NOTE] Child process executed sucessfully! \n\n\n");
// 	}
// 	else {
// 		printf("\nGreetings from the parent process!");
// 		printf("\n Parent process ID: %d", getpid());
// 		printf("\nChild Process ID: %d", pid);
// 		printf("\n------------------Parent waiting for pid to complete------------------");
// 		wait(NULL);
// 		printf("\n\n[NOTE] Parent process executed sucessfully! \n\n\n");
// 	}	
// }
