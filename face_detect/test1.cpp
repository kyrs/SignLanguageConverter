#include <stdio.h>
#include <unistd.h>
#include <string.h>
 #include<fstream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */

using namespace std;
 
int main(int argc, char** argv) {
 
    int GPIOPin=60, /* GPIO1_28 or pin 12 on the P9 header */ times=10;
    int GPIOPin1=30; 
    printf("\nStarting GPIO output program\n");
    FILE *myOutputHandle = NULL;
    FILE *myOutputHandle1 = NULL;
    
    char setValue[4], GPIOString[4], GPIOValue[64], GPIODirection[64];
    char setValue1[4], GPIOString1[4], GPIOValue1[64], GPIODirection1[64];
    
    sprintf(GPIOString, "%d", GPIOPin);
    sprintf(GPIOValue, "/sys/class/gpio/gpio%d/value", GPIOPin);
    sprintf(GPIODirection, "/sys/class/gpio/gpio%d/direction", GPIOPin);

    sprintf(GPIOString1, "%d", GPIOPin1);
    sprintf(GPIOValue1, "/sys/class/gpio/gpio%d/value", GPIOPin1);
    sprintf(GPIODirection1, "/sys/class/gpio/gpio%d/direction", GPIOPin1);

    // Export the pin12
    if ((myOutputHandle = fopen("/sys/class/gpio/export", "ab")) == NULL){
        printf("Unable to export GPIO pin\n");
        return 1;
    }
    strcpy(setValue, GPIOString);
    fwrite(&setValue, sizeof(char), 2, myOutputHandle);
    fclose(myOutputHandle);
 
    // Set direction of the pin12 to an output
    if ((myOutputHandle = fopen(GPIODirection, "rb+")) == NULL){
        printf("Unable to open direction handle\n");
        return 1;
    }
    strcpy(setValue,"out");
    fwrite(&setValue, sizeof(char), 3, myOutputHandle);
    fclose(myOutputHandle);
    
    // Export the pin11
    if ((myOutputHandle1 = fopen("/sys/class/gpio/export", "ab")) == NULL){
        printf("Unable to export GPIO pin\n");
        return 1;
    }
    strcpy(setValue1, GPIOString1);
    fwrite(&setValue1, sizeof(char), 2, myOutputHandle1);
    fclose(myOutputHandle1);
 
    // Set direction of the pin11 to an output
    if ((myOutputHandle1 = fopen(GPIODirection1, "rb+")) == NULL){
        printf("Unable to open direction handle\n");
        return 1;
    }
    strcpy(setValue1,"out");
    fwrite(&setValue1, sizeof(char), 3, myOutputHandle1);
    fclose(myOutputHandle1);
 
    for(int i=0; i<times; i++){
	int a;
	ifstream infile("motors.txt");
			infile>>a;
		if (a==1)
		{
			exit(EXIT_FAILURE);
		}	
	
        // Set output to high
        if ((myOutputHandle = fopen(GPIOValue, "rb+")) == NULL){
            printf("Unable to open value handle\n");
            return 1;
        }
		printf("%d",i);
        strcpy(setValue, "1"); // Set value high
        fwrite(&setValue, sizeof(char), 1, myOutputHandle);
        fclose(myOutputHandle);
        sleep(1); // wait for 1 sec
 
        // Set output to low
        if ((myOutputHandle = fopen(GPIOValue, "rb+")) == NULL){
            printf("Unable to open value handle\n");
            return 1;
        }
        strcpy(setValue, "0"); // Set value low
        fwrite(&setValue, sizeof(char), 1, myOutputHandle);
        fclose(myOutputHandle);
        sleep(4); //wait for 4 sec
        
        // Set output to high pin 11
        if ((myOutputHandle1 = fopen(GPIOValue1, "rb+")) == NULL){
            printf("Unable to open value handle\n");
            return 1;
        }
		
        strcpy(setValue1, "1"); // Set value high pin11
        fwrite(&setValue1, sizeof(char), 1, myOutputHandle1);
        fclose(myOutputHandle1);
        sleep(1); // wait for 1 sec
        
        // Set output to low pin11
        if ((myOutputHandle1 = fopen(GPIOValue1, "rb+")) == NULL){
            printf("Unable to open value handle\n");
            return 1;
        }
        strcpy(setValue1, "0"); // Set value low pin11
        fwrite(&setValue1, sizeof(char), 1, myOutputHandle1);
        fclose(myOutputHandle1);
        sleep(4); //wait for 4 sec
 
    }
 
    // Unexport the pin12
    if ((myOutputHandle = fopen("/sys/class/gpio/unexport", "ab")) == NULL) {
        printf("Unable to unexport GPIO pin\n");
        return 1;
    }
    strcpy(setValue, GPIOString);
    fwrite(&setValue, sizeof(char), 2, myOutputHandle);
    fclose(myOutputHandle);
    printf("\nCompleted GPIO output program\n");
    
    // Unexport the pin11
    if ((myOutputHandle1 = fopen("/sys/class/gpio/unexport", "ab")) == NULL) {
        printf("Unable to unexport GPIO pin\n");
        return 1;
    }
    strcpy(setValue1, GPIOString1);
    fwrite(&setValue1, sizeof(char), 2, myOutputHandle1);
    fclose(myOutputHandle1);
    printf("\nCompleted GPIO output program\n");
 
    return 0;
}
