// COMPILE: gcc binary_search.c -o binary
// EXECUTE: ./binary
// child.c file

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

// Function to print array on console
void print_arr(int arr[50], int n) {
    int i;
    printf("[");
    for(i = 0; i < n - 1; i++) {
        printf(" %d, ",arr[i]);
    }
    printf(" %d ]", arr[i]);
    printf("\n");
}

// Binary search
// A iterative binary search function. It returns
// location of x in given array arr[l..r] if present,
// otherwise -1

void binary_search(int arr[50], int l, int r, int x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
  
        // Check if x is present at mid
        if (arr[m] == x) {
            printf("\n %d is present at index %d \n", x, m);
            break;
        }
  
        // If x greater, ignore left half
        if (arr[m] < x)
            l = m + 1;
  
        // If x is smaller, ignore right half
        else
            r = m - 1;
    }
  
    // if we reach here, then element was
    // not present
    if(l>r)
        printf("\n %d was not found in the array.", x);
}

// Main function of the program
void main(int argc, char* argv[]) {
    int arr[argc - 1], search;

    for (int i = 1; i<argc; i++) {
		arr[i-1] = atoi(argv[i]);
    }

        print_arr(arr, argc - 1);

        printf("\n Enter the value to be searched: ");
        scanf("%d", &search);

        binary_search(arr, 0, argc-1, search);
        printf("\n In Child the current PID is: %d \n", getpid());
   
}