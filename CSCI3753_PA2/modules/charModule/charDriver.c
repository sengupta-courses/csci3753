//Pourna Sengupta
//charDriver.c 
//Programming Assignment 2 
//October 4, 2020

#include </linux/init.h>
#include </linux/module.h>

#include </linux/fs.h>
#include </linux/slab.h>
#include </linux/uaccess.h>


#define BUFFER_SIZE 1024
#define MAJOR_NUMBER 271 //Major number corresponding to device driver
#define DEVICE_NAME "/home/kernel/linux-hwe-4.15.0/csci3753/CSCI3753_PA2/modules/charModule/charDriver.c" //Name of Device Driver

//static variables 
static char *devBuff; 
//for counters
static int countO = 0; 
static int countC = 0; 


//VARIABLES
//buffer: userspace buffer where data you want to read from the device file is being written 
//length: length of the userspace buffer
//offset: set to current position of opened file after read
//copy_to_user: source is device_buffer, destination is userspace buffer 

//If a user attempts to read, write or seek before the beginning or beyond the end of the device_
//buffer, an error should be indicated by returning a -1, and the current position should be left 
//unchanged.  You will need to implement some sort of bounds checking to ensure this behavior.

//OPEN
//The open function takes two parameters, a pointer to an inode struct (which represents the 
//physical file on the hard disk), and a pointer to a file struct (represents the state of a file), 
//and returns an integer indicating success or failure.  In this function, you don't need to do 
//anything other than log the​ number of times the device has been opened.

//print to the log file that the device is opened 
//print the number of times this device has been opened until now
ssize_t charDriverOpen(struct inode *pinode, struct file, *pfile){
	printk(KERN_ALERT "Device is opened.\n", func); 
	countO++; 
	printk("Opens %d times.\n", countO); 
	//Return 0
	return 0; 
}


//RELEASE/CLOSE
//The release function takes the same two parameters as open() and again returns an integer 
//indicating success or failure.  Use printk() to output the​ number of times the device has been closed.

//print to the log file that the device is closed
//print the number of times this device has been closed until now
ssize_t charDriverClose(struct inode *pinode, struct file, *pfile){
	printk(KERN_ALERT "Device is closed.\n", func); 
	countC++; 
	printk("Closes %d times.\n", countC); 
	//Return 0
	return 0; 
}

//READ
//The read function expects four parameters: a file pointer, a pointer to a user-space buffer, 
//the size of that buffer, and a pointer to the current position.  Use the function ​copy_to_user()​ ​
//to copy data from the ​device_buffer, starting at the current position,​ ​to the user-space buffer.  
//If successful, make sure to update the current position, and then return the number of bytes read.  
//Use ​printk()​ to log the number of bytes read.

ssize_t charDriverRead(struct file *pfile, char _user *buffer, size_t length, loff_t, *offset){
	printk(KERN_ALERT "Reading function.\n", func); 
	//max bytes read into buffer
	int max = BUFF_SIZE - *offset; 
	//bytes read and to be read 
	int bytesRead; 
	int bytesUnread; 

	if(max > length){
		bytesUnread = length; 
	}
	
	else{
		bytesUnread = max; 
	}
	if(bytesUnread = 0){
		printk(KERN_ALERT "0 bytes read.\n"); 
	} 

	r = tor - copy_to_user(buffer, devBuff + *offset, bytesUnread); 
	printk(KERN_ALERT "%d bytes read.\n", bytesRead); 
	)

	offset += bytesRead; 
	printk(KERN_ALERT "Read Finished.\n"); 
	
	//Return 0 
	return 0; 
}

//Write - ​The write function is similar to read.  Copy data stored in the user-space buffer into the device_buffer​ using ​copy_from_user()​.  The write starts from the current position, and if successful, the position should be updated.  Use ​printk()​ to log the number of bytes written.  Finally, return the number of bytes written to the caller.  If the user sets the current position back to the beginning of the file (by using seek), this operation may overwrite previously written data.  

ssize_t charDriverWrite(struct file *pfile, const char _user *buffer, size_t length, loff_t *offset){
	printk(KERN_ALERT "Writing function.", func); 
	int max = BUFF_SIZE - *offset; 
	//bytes written and to write 
	int bytesWritten; 
	int bytesUnwritten; 

	if(max > length){
		bytesUnwritten = length; 
	} 

	else{
		bytesUnwritten = max; 
	}

	bytesWritten = bytesUnwritten - copy_from_user(devBuff + *offset, buffer, bytesUnwritten); 

	//number of bytes written 
	printk(KERN_ALERT "% bytes written.\n", w); 
	*offset += w; 
	
	printk(KERN_ALERT "Writing finished.\n"); 
	//return length
	return length; 
}


//Seek - ​The seek function takes three parameters, a file pointer, an offset, and the value whence.  Whence describes how to interpret the offset (note that offset can be negative).  If the value of whence is ​0​ (​SEEK_SET​), the position is set to the value of the offset.  If the value of whence is ​1​ (SEEK_CUR​), the current position is incremented (or decremented, if negative) by offset bytes.  Finally, if the value of whence is ​2 (​SEEK_END​), the position is set to offset bytes from the end of the file.

//Update open file position according to the values of offset and whence 
loff_t charDriverSeek(struct file *pfile, loff_t offset, int whence){

	loff_t nOffset = 0; 
	switch(whence){
		//SEEK_SET
		case 0: 
			nOffset = offset; 
			break; 
		//SEEK_CUR
		case 1: 
			nOffset = pfile -> f_pos + offset; 
			break; 
		//SEEK_END
		nOffset = BUFFER_SIZE - offset; 
		break; 
	}
	
	if(nOffset < 0){
		return -1; 
	}
	if(nOffset > BUFFER_SIZE){
		return -1; 
	}
	
	pfile -> f_pos = nOffset; 
	//Return 0 
	return 0; 

}
 
struct file_operations charDriverOps = {
	//add the function pointers to point to the corresponding file ops
	//look at the file fs.h in the linux source code
	.owner = THIS_MODULE, 
	.open = charDriverOpen,
	.release = charDriverClose, 
	.read = charDriverRead, 
	.write = charDriverWrite, 
	.seek = charDriverSeek, 
};

static int charDriverInit(void){
	//print to the log file that the init function is called 
	//register the device 
	//return 0
	return 0; 
}

static void charDriverExit(void){
	//print to the log file that the exit function is called
	//unregister the device using the register_chrdev() function 
	print(KERN_ALERT "Exit Character Driver\n", func); 
	if(devBuff){
		kfree(devBuff);
	}

	unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME); 
}

//add module_init and module_exit to point to the corresponding init and exit functions
module_init(charDriverInit); 
module_exit(charDriverExit); 
