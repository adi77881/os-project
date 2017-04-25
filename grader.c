/*Author: Baladitya, Shwetha
  Date Created: June-09-2016
  Program Name:grader.c
  Purpose: Create multiple threads in order to calculate results and display in parent
  Execution command: gcc -pthread -o gradeer gradeer.c -lm 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //Library to create threads
#include <math.h> //To do mathematical Operations

//Declaration and Intialaization
int c,recordcount=0,*aray,i=0,j=0;
FILE *file;
int values[9];
int number,count,sum=0,minimum,maximum,median,passed=0;
float avg;

//Function to find Median
void *myMedian(void *vargp)
{
	int l,m,temp,key;

        printf("Thread Id in Median is :%lu \n",pthread_self());
	//Sorting an array using Selection sort
	for(m=1;m<i;m++)
	{
		l=m-1;
		key=*(aray+m);
		while(l>=0 && *(aray+l)>key)
		{
			*(aray+l+1)=*(aray+l);
			l--;
		}
		*(aray+l+1)=key;
	}

	//Median if the no of elements are even or odd
	if(i%2==0)
		median=(*(aray+i/2)+*(aray+i/2-1))/2;
	else
		median=*(aray+i/2);

	return NULL;
}

void *myMinimum(void *vargp)
{
        printf("Thread Id of Minimum is :%lu \n",pthread_self());
	//Getting directly 1st value from sorted array 
	minimum=*(aray+0);
	return NULL;
}

void *myAvg(void *vargp)
{

        printf("Thread Id of Average is :%lu \n",pthread_self());
	//Finding an Average
	for(j=0;j<i;j++)
	{
		sum+=*(aray+j);
	}
	avg=sum/i; 
	return NULL;
}

void *myMaximum(void *vargp)
{
        printf("Thread Id of maximum is :%lu \n",pthread_self());
	//Getting directly last value from sorted array
	maximum=*(aray+i-1);
	return NULL;
}


int main()
{
	pthread_t tid[4];
	int k=0;
       char account[]="grader";
       char check[10];
       char filename[256];
  while(1)
  {
       printf("user_account>");//enter the input string
        scanf("%s",check);
      if(strcmp(account,check)==0)//if input==grader
      {
	//Opening file grades.txt in read mode
        printf("Please enter file name:");
       scanf("%s",filename);
	file = fopen(filename, "r");
	if (file) {
		while ((c = getc(file)) != EOF)
		{
			if(c==44)
			{
				++recordcount;
			}

		}
		++recordcount;

		printf("Record count is :%d \n",recordcount);
		//Moving cursor first character location
		rewind(file);
		//Allocating space dynamically for the records
		aray=(int*)malloc(recordcount*sizeof(int));

		while ((c = getc(file)) != EOF)
		{
			if(c==44)
			{
				// printf("%d  ",number);
				*(aray+i)=number;
				i++;
				number=0;
				count=0;
			}
			else if ((c-'0')==-38){continue;}
			else
			{
				number=(c-'0')+number*pow(10,count);
                                if(count==0)count++;				
				//        printf("%d  ",(c-'0'));
			}

		}
		*(aray+i)=number;
		i++;

		fclose(file);

		printf("Read grades: ");
		for(j=0;j<i;j++)
			printf("%d  ",*(aray+j));
                printf("\n Thread Id of Parent is :%lu \n",pthread_self());

		pthread_create(&tid[0], NULL,myMedian, NULL);
		pthread_create(&tid[1], NULL,myMinimum, NULL);
		pthread_create(&tid[2], NULL, myAvg, NULL);
		pthread_create(&tid[3], NULL, myMaximum, NULL);

		for(k=0;k<4;k++)
			pthread_join(tid[k], NULL);

		printf("\n Average is :%f \n",avg);
		printf(" Median is :%d \n",median);
		printf(" Minimum is:%d \n",minimum);
		printf(" Maximum is:%d \n",maximum);
		for(j=0;j<i;j++)
		{
			if(*(aray+j)>=85)
				passed++;
		}

		printf("Number of Students Who Pass:%d \n",passed);

                 break;
	  //	exit(0);
	}

       }
      else
      {
          printf("Please enter correct user account \n");
          
       }
    }
	return;


}
