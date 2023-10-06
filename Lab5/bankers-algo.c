#include<stdio.h>
#include <stdbool.h>

int main() {
  
  int processes,resources ;
  
  printf("Enter The No of Processes: ");
  scanf("%d",&processes);
  
  printf("\nEnter The No Resources: ");
  scanf("%d",&resources);
  
  int allocation[processes][resources],max[processes][resources],available[resources] ;
  
  for(int i = 0 ; i < processes ; i++) {
    printf("Enter %dth process allocation",i);
  
    for(int j = 0 ; j < resources ; j++) {
      scanf("%d",allocation[i][j]);
    }
  }
  
  for(int i = 0 ; i < processes ; i++) {
    printf("Enter %dth process max",i);
  
    for(int j = 0 ; j < resources ; j++) {
      scanf("%d",max[i][j]);
    }
  }
  
  for(int j = 0 ; j < resources ; j++) {
      scanf("%d",available[j]);
  }
  
  int need[processes][resources] ;
  
  for(int i = 0 ; i < processes ; i++) {
    for(int j = 0 ; j < resources ; j++) {
      need[i][j] = max[i][j] - allocation[i][j] ;
    }
  }
  
  int safeSeq[processes],safeSeqIndex = 0;
  
  bool inSafeSeq[processes],checkCondition = false;
  
  for(int i = 0 ; i < processes ; i++) {
    inSafeSeq[i] = false ;
  }
  
  for(int i = 0 ; i < processes ; i++) {
    for(int j = 0 ; j < processes ; j++) {
      if(inSafeSeq[j] == false) 
      {
        checkCondition = true ;
        for(int k = 0 ; k < resources ; k++)
        {
          if(need[j][k] > available[k])
          {
            checkCondition = false ;
          }
        }
      }
      
      if(checkCondition = true)
      {
        safeSeq[safeSeqIndex] = j ;
        safeSeqIndex++ ;
        inSafeSeq[j] = true ;
        
        for(int k = 0 ; k < resources ; k++)
        {
          available[k] += allocation[j][k] ;
        }
      }
    }
  }
  
  bool safeSeqAchevied = true ;
  
  for(int i = 0 ; i < processes ; i++)
  {
    if(inSafeSeq[i] == false)
    {
      safeSeqAchevied = false ;
      printf("Safe Sequence not met");
    }
  }
  
  int k;
  
  if(safeSeqAchevied == true)
  {
    printf("Following is the Safe Sequence");
    for(k = 0 ; k < processes-1 ; k++)
    {
      printf("P%d %d ->",&k,safeSeq[k]);
    }
    printf("P%d %d",&k,safeSeq[k]);
  }
  
  return 0;
}

