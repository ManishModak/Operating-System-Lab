#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>


int main() {

	char * myfile = "/home/manish/git_environment.txt" ;
	
	FILE *fp ;

	int fd1 ;
	
	char * myfifo1 = "/home/manish/myfifo1" ;
	
	char * myfifo2 = "/home/manish/myfifo2" ;
	
	mkfifo(myfifo1,0666) ;
	
	mkfifo(myfifo2,0666) ;
	
	char arr1[80] , arr2[80] ;
	
	while(1) {
	
		int i = 0 , wordCount = 0 , lineCount = 0 , charCount = 0 ;


		//Reading from fifo1
	
		fd1 = open(myfifo1,O_RDONLY);
		
		read(fd1,arr1,80);
		
		printf("User 1: %s \n",arr1);
		
		while(i != strlen(arr1) ) {
		      
			if(arr1[i] == ' ')
			{
				wordCount++ ;
			}
			else if(arr1[i] == '\n')
			{
				wordCount++ ;
				lineCount++ ;
			}
			else
			{
				charCount++ ;
			}
			
			i++;
		}
		
		close(fd1);
		
		
		
		//count data and wrirting in fifo2
			
		char tempstr[100];
		sprintf(tempstr, "wordCount: %d, lineCount: %d, charCount: %d\n", wordCount, lineCount, charCount);

			
		fp = fopen(myfile,"w");
		
		if(fp) 
		{
			fputs(tempstr, fp);
                        fclose(fp);
		}
		else
		{
			printf("Error Opening the File: %s\n", myfile);
		}
		
		
		fd1 = open(myfifo2,O_WRONLY) ;
		
		write(fd1,tempstr,strlen(tempstr)+1);
		
		close(fd1);
		
	}
	
	
	return 0 ;
}


/*

manish@manish-VirtualBox:~/git_environment/Operating-System-Lab/Lab7/A$ gcc b.c -o b
manish@manish-VirtualBox:~/git_environment/Operating-System-Lab/Lab7/A$ ./b
User 1: Hi
 
User 1: Where are you from ?



*/
