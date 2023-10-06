#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>


int main() {

	char * myfile = "/home/student/TA45/file.txt" ;
	
	FILE *fp ;

	int fd1 ;
	
	char * myfifo1 = "/home/student/TA45/myfifo1" ;
	
	char * myfifo2 = "/home/student/TA45/myfifo2" ;
	
	mkfifo(myfifo1,0666) ;
	
	mkfifo(myfifo2,0666) ;
	
	char arr1[80] , arr2[80] ;
	
	while(1) {
	
		int i = 0 , wordCount = 0 , lineCount = 0 , charCount = 0 ;
		
		
		
		
		//Reading from fifo1
	
		fd1 = open(myfifo1,O_RDONLY);
		
		read(fd1,arr1,80);
		
		printf("User 1: %s \n",arr1);
		
		close(fd1);
		
		
		
		
		//Reading from fifo2
		
		char countData[100] ;
		
		fd1 = open(myfifo2,O_RDONLY) ;
		
		read(fd1,countData,sizeof(countData));
		
		printf("User CountData: %s \n",countData);
		
		close(fd1);
		
		
		
		//writing into fifo1
		
		fd1 = open(myfifo1,O_WRONLY) ;
		
		fgets(arr2,80,stdin);
		
		write(fd1,arr2,strlen(arr2)+1);
		
		while(i < strlen(arr2)) {
			
			if(arr2[i] == ' ')
			{
				wordCount++ ;
			}
			else if(arr2[i] == '\n')
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
			printf("Error Opening the File");
		}
		
		
		fd1 = open(myfifo2,O_WRONLY) ;
		
		write(fd1,tempstr,strlen(tempstr)+1);
		
		close(fd1);
		
		
	}
	
	
	return 0 ;
}


/*

student@student:~$ gcc b.c -o b
student@student:~$ ./b
User 1: Hi Im Manish
 
User CountData: wordCount: 3, lineCount: 1, charCount: 10
 
Hello Myself zein
User 1: Hi Im Manish


*/
