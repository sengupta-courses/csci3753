Pourna Sengupta
pose9026@colorado.edu 

Hello Module 
- helloModule.c: Example code given in write up. 
- Makefile: Creates module object helloModule.o
- helloModule.o: Module Object Code
- helloModule.ko: Kernel Module containing object to insert into running kernel. 
- helloModule.mod.c: Module Code
- hellowModule.mod.o: Module Code

Simple Character Module
- README.md: Contact information, descriptions of submitted files, instructions on how to install/use/conifgure module and device file, instructions on how to build and run test program.  
- Makefile: Creates module object charDriverModule.o 
- charDriver.c: Contains open(), close(), read(), write(), seek() functions as well as function operations, module_init() and module_exit(). 
- charDriverTest.c: Runs program for user to choose what to do with file. Includes read, write, seek, and exit. 


BUILDING: 
Build the LKM using terminal command 

    sudo make -C /home/kernel/linux-hwe-4.15.0/csci3753/CSCI3753_PA2/modules/charModule M=$PWD 

Build the test program using terminal command 

    gcc -o test charDriver.c charDriverTest.c 

TESTING: 
Insert LKM using terminal command 

    sudo insmod charDriver.ko

while in the director of charDriver.ko

Check if LKM was inserted correctly using terminal command 

    lsmod 

Create a device file using the terminal command

    sudo mknod -m 777 /dev/charDriver c 272 0 

Check that it was created using terminal command 
s
    ls/dev

RUN: 
Run the test code using terminal command 

    ./charDriverTest

Run through program and file operations or choose to exit the test. 
