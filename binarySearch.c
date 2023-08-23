#include<stdlib.h>
#include<stdio.h>

int binarySearch(int arr[], int searchVal, int low, int high)
{
	int mid = (low+high)/2 ;
	
	if(searchVal == arr[mid])
	{
		return mid ;
	}
	else if(searchVal < arr[mid])
	{
		return binarySearch(arr, searchVal, low, mid-1) ;
	}
	else if(searchVal > arr[mid])
	{
		return binarySearch(arr, searchVal, mid+1, high) ;
	}
	else
	{
		return -1 ;
	}
}

void main(int argc ,char* argv[])
{
	int searchVal = 0 ;
	
	printf("Enter The no. to be found: ") ;
	scanf("%d",&searchVal) ;
	
	int data[argc - 1] ;
	
	for(int i = 1 ; i < argc ; i++)
	{
		data[i-1] = atoi(argv[i]) ;
	}
	
	int result = binarySearch(data, searchVal, 0, argc - 1) ;
	
	if(result == -1)
	{
		printf("No. Not found");
	}
	else
	{
		printf("%d",result) ;
	}
}

