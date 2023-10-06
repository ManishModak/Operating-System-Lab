#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>


int main() {

	int fd ;
	
	char * myfile = "/home/student/TA45/file.txt" ;
	
	FILE *fp ;
	
	char * myfifo1 = "/home/student/TA45/myfifo1" ;
	
	char * myfifo2 = "/home/student/TA45/myfifo2" ;
	
	mkfifo(myfifo1,0666) ;
	
	mkfifo(myfifo2,0666) ;
	
	char arr1[80] , arr2[80] ;
	
	while(1) {
	
		int i = 0 , wordCount = 0 , lineCount = 0 , charCount = 0 ;
		
		
		
		//Writing in fifo1
		
		fd = open(myfifo1,O_WRONLY) ;
		
		fgets(arr2,80,stdin);
		
		write(fd,arr2,strlen(arr2)+1);
		
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
		
		close(fd);
		
		
	
		
		//writing in fifo2
		
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
		
		fd = open(myfifo2,O_WRONLY) ;
		
		write(fd,tempstr,strlen(tempstr)+1);
		
		close(fd);
		
		
		
		//Reading From fifo1
		
		fd = open(myfifo1,O_RDONLY);
		
		read(fd,arr1,sizeof(arr1));
		
		printf("User 2: %s \n",arr1);
		
		close(fd);
		
		
		
		//Reading From fifo2
		
		char countData[100] ;
		
		fd = open(myfifo2,O_RDONLY) ;
		
		read(fd,countData,sizeof(countData));
		
		printf("User CountData: %s \n",countData);
		
		close(fd);
		
	}
	
	
	return 0 ;
}




/*

student@student:~$ gcc a.c -o a
student@student:~$ ./a

Hi Im Manish
User 2: Hello Myself zein
 
User CountData: wordCount: 3, lineCount: 1, charCount: 15

*/
