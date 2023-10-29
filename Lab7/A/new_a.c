#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>


int main() {

        int fd ;
	
	char * myfifo1 = "/home/manish/myfifo1" ;
	
	char * myfifo2 = "/home/manish/myfifo2" ;
	
	mkfifo(myfifo1,0666) ;
	
	mkfifo(myfifo2,0666) ;
	
	char arr1[80] , arr2[80] ;
	
	while(1) {
		
		//Writing in fifo1
		
		fd = open(myfifo1,O_WRONLY) ;
		
		fgets(arr2,80,stdin);
		
		write(fd,arr2,strlen(arr2)+1);
	      
		close(fd);
		
		
		//Reading From fifo2
		
		char countData[100] ;
		
		fd = open(myfifo2,O_RDONLY) ;
		
		read(fd,countData,sizeof(countData));
		
		printf("Message CountData: %s \n",countData);
		
		close(fd);
		
	}
	
	
	return 0 ;
}




/*

manish@manish-VirtualBox:~/git_environment/Operating-System-Lab/Lab7/A$ gcc a.c -o a
manish@manish-VirtualBox:~/git_environment/Operating-System-Lab/Lab7/A$ ./a
Hi
Message CountData: wordCount: 1, lineCount: 1, charCount: 2
 
Where are you from ?
Message CountData: wordCount: 5, lineCount: 1, charCount: 16


*/
