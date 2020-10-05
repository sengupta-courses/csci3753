//Pourna Sengupta
//charDriverTest.c 
//Programming Assignment 2 
//October 4, 2020

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>


#define BUFFER_SIZE 1024
#define DEVICE_NAME "/home/kernel/linux-hwe-4.15.0/csci3753/CSCI3753_PA2/modules/charModule/charDriver.c" //Name of Device Drivers


int main(){
    char userInput; 
    int length; 
    int whence; 
    int nOffset; 
    char buffer[BUFFER_SIZE];

    int tempFile= open("DEVICE_NAME", O_RDWR);
    bool programRun = true; 

    while(programRun){
        //USER MENU
        printf("Please choose from the options below: \n"); 
        printf("(R)ead\n"); 
        printf("(W)rite\n"); 
        printf("(S)eek\n"); 
        printf("(E)xit\n"); 
        scanf("%c", &userInput); 

        switch(userInput){
            //OPTION R
            //program asks for number of bytes to read using prompt
            //create large enough buffer using malloc()
            //read from device file starting from current position 
            //print data out to console 
            case 'r': 
                //Chose read option 
                printf("Enter the number of bytes you want to read: \n"); 
                scanf("%d", &length); 

                int tempR = read(tempFile, buffer, length); 
		if(tempR != 0){
			//not enough buffer space to read
			exit; 
		}
                printf("%s\n", buffer); 
                while(getchar() != '\n'); 
                break; 
            
            //OPTION W
            //program asks for data to be written from user using prompt 
            //user enters desired data terminated by a carriage return 
            case 'w': 
                //Chose write option 
                printf("Enter data you want to write: \n"); 
                scanf("%s", buffer); 

               	int tempW = write(tempFile, buffer, BUFFER_SIZE); 

                if(tempW == 0){
			//not enough buffer space
			exit; 
		}
		while(getchar() != '\n'); 

                break; 
            
            //OPTION S
            //program asks for values of the second and thrid parameters 
            case 's': 
                printf("Enter an offset value: \n"); 
                scanf("%d", &nOffset); 
                printf("Enter a value for whence: \n"); 
                scanf("%d", &whence); 

                int tempS = seek(tempFile, nOffset, whence); 
		while(getchar() != '\n'); 
                break; 

            
            //OPTION E
            //Quit Program 
            case 'e':
                programRun = false; 
                break; 


            //DEFAULT 
            default: 
                break; 
        }
    } 
    close(tempFile); 
    return 0; 
}

