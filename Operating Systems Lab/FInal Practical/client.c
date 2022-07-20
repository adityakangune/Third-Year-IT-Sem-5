/*
33323 - Aditya Kangune
OSL Practicals
Chit Code - 15
Program name: client.c
*/

/*
Problem Statement:
15.Inter-process Communication using Shared Memory using System V. Application to demonstrate:
Client and Server Programs in which server process creates a shared memory segment and writes the
message to the shared memory segment. Client process reads the message from the shared memory
segment and displays it to the screen
*/

// COMPILE : gcc client.c -o client
// EXECUTE : ./client

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<string.h>


int main() {
    int i;
    void *shared_memory;
    char buff[100];
    int shmid;
    shmid = shmget((key_t)2345, 1024, 0666);
    printf("\n\t ------------------------------------- CLIENT ------------------------------------- \n\n");
    printf("\t\tKey of shared memory is: %d\n\n", shmid);
    shared_memory=shmat(shmid, NULL, 0); // process attached to shared memorysegment
    
    printf("\t\tProcess attached at %p\n\n", shared_memory);
    printf("\t\tData read from shared memory is: %s\n", (char*) shared_memory);

    printf("\n \t------------------------------------- CLIENT ENDS ------------------------------------- \n\n");
    

    printf("\n ++++++++++++++++++++++++++++++++++++ Inter-process Communication using Shared Memory ++++++++++++++++++++++++++++++++++++ \n\n");
}