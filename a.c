#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>


int main() {

	int fd ;
	
	
	char * myfifo = "/tmp/myfifo" ;
	
	mkfifo(myfifo,0666) ;
	
	char arr1[80] , arr2[80] ;
	
	while(1) {
	
		int i = 0 , wordCount = 0 , lineCount = 0 , charCount = 0 ;
		
		fd = open(myfifo,O_WRONLY) ;
		
		fgets(arr2,80,stdin);
		
		write(fd,arr2,strlen(arr2)+1);
		
		close(fd);
		
		fd = open(myfifo,O_RDONLY);
		
		read(fd,arr1,sizeof(arr1));
		
		printf("User 2: %s \n",arr1);
		
		close(fd);
		
		while(i < strlen(arr1)) {
			
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
		
		printf("wordCount: %d,lineCount: %d,charCount: %d \n",wordCount,lineCount,charCount) ;
	}
	
	
	return 0 ;
}
