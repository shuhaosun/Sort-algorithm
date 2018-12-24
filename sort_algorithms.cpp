# include <stdio.h> 
# include <stdlib.h>
#include <time.h>
#include <sys/time.h> 
#include <limits.h>
#include <malloc.h> 

int N;

struct node
{
 int low;
 int high;
};//记录快速排序待排序的区间[low,high]


void ArraySize(int size)
{
	N=(size*1024)/4;
}

void InsertSort(int a[],int n)//插入排序
{
	int i,j;
	int temp;
	for(i=0;i<n-1;i++)
	{
		temp=a[i+1];
		j=i;
		while(j>-1 && temp<a[j])
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
}

void QuickSort( int a[], int n )  //快速排序非递归实现 
{  
    node *S; 
	S=(node*)malloc(sizeof(node)*N); 
  
    int m;  
    int p;  
    int low, high;
	int i, j;  
	int temp;
  
    m = 0;  
    S[0].low = 0;  
    S[0].high = n-1;  
  
    while(1)
    {  
        if ( m < 0 )  
            break;  
        low = S[m].low;  
        high = S[m--].high;  
  
        if ( low >= high )  
            continue;  
        p = a[low];  
        i = low;  
        j = high+1;  
        while(1)  
        {  
            while( ++i <= high && a[i] < p );  
            while( a[--j] > p );  
            if ( i > j )  
                break;  
           	temp = a[i];
			a[i] = a[j];
			a[j] = temp; 
        }  
        temp = a[low];
		a[low] = a[j];
		a[j] = temp; 
  
        S[++m].low = low;  
        S[m].high   = j-1;  
        S[++m].low = j+1;  
        S[m].high   = high;  
    }  
    free(S);
}  

void Merge(int a[],int n,int swap[],int k) //一次二路归并排序 
{
	int m=0,u1,l2,i,j,u2;
	int l1=0;
	while(l1+k<=n-1)
	{
		l2=l1+k;
		u1=l2-1;
		u2=(l2+k-1<=n-1)? l2+k-1:n-1;
		
		//两个有序子数组合并
		for(i=l1,j=l2;i<=u1 && j<=u2;m++)
		{
			if(a[i]<=a[j])
			{
				swap[m]=a[i];
				i++;
			}
			else
			{
				swap[m]=a[j];
				j++;
			}
		}
		
		//子数组2已经归并完，将子数组1中剩余的元素存放到数组swap中
		while(i<=u1) 
		{
			swap[m]=a[i];
			m++;
			i++;
		}
		
		//子数组1已经归并完，将子数组2中剩余的元素存放到数组swap中
		while(j<=u2) 
		{
			swap[m]=a[j];
			m++;
			j++;
		}
		l1=u2+1;
	}
	//将原始数组中只够一组的数据元素顺序存放到数组swap中
	for(i=l1;i<n;i++,m++) 
	{
		swap[m]=a[i];
	}
}

void MergeSort(int a[],int n)//二路归并排序算法 
{
	int i,k=1;
	int *swap;
	swap=(int*)malloc(sizeof(int)*n);
	while(k<n)
	{
		Merge(a,n,swap,k);
		for(i=0;i<n;i++)
		{
			a[i]=swap[i];
		}
		k=2*k;
	}
	free(swap);
}

int main()
{

	int *a;
	int *b;
	int *c;
	int i,j;
	int k=0;
	int z;
	long count[10];
	long count2[10];
	long count3[10];
	long countavg=0;
	long countavg2=0;
	long countavg3=0;
	double time1=0;
	double time2=0;
	double time3=0;		
	int curcle=0;
    for(i=0;i<10;i++)
    {
    	count[i]=count2[i]=count3[i]=0;
	}
	while(curcle<2)
	{
		if(curcle==0)
		{
			N=256;
			printf("随机数组规模为1K时：\n");
		}
		if(curcle==1)
		{
			N=1024;
			printf("随机数组规模为4K时：\n");
		}
	a=(int*)malloc(sizeof(int)*N);
	b=(int*)malloc(sizeof(int)*N);
  	c=(int*)malloc(sizeof(int)*N);
	for(z=0;z<10;z++)
	{
	srand(time(NULL));
	for(i=0;i<N;i++)
	{
		a[i]=rand();
	 	b[i]=c[i]=a[i];
	}
	 timeval start,end;
	 long dif_sec, dif_usec;
	 	 
	 for(j=0;j<1000;j++)
	 {
	 	gettimeofday(&start, NULL);
		InsertSort(a,N);
		gettimeofday(&end, NULL);
		for(i=0;i<N;i++)
		{
			a[i]=b[i];
		}
		dif_sec = end.tv_sec - start.tv_sec;  
	    dif_usec = end.tv_usec - start.tv_usec; 
		count[k]=count[k]+dif_sec*1000000+dif_usec;
	 }
	 
	 for(j=0;j<1000;j++)
	 {
	 	gettimeofday(&start, NULL);
		QuickSort(b,N);
		gettimeofday(&end, NULL);
		for(i=0;i<N;i++)
		{
			b[i]=c[i];
		}
		dif_sec = end.tv_sec - start.tv_sec;  
	    dif_usec = end.tv_usec - start.tv_usec; 
		count2[k]=count2[k]+dif_sec*1000000+dif_usec;
	 }
	  
     for(j=0;j<1000;j++)
	 {
	 	gettimeofday(&start, NULL);
		MergeSort(c,N);
		gettimeofday(&end, NULL);
		for(i=0;i<N;i++)
		{
			c[i]=b[i];
		}
		dif_sec = end.tv_sec - start.tv_sec;  
	    dif_usec = end.tv_usec - start.tv_usec; 
		count3[k]=count3[k]+dif_sec*1000000+dif_usec;
	 }	
    k++;		
	}
	curcle++;
	for(i=0;i<10;i++)
	{
		countavg=countavg+count[i];
		countavg2=countavg2+count2[i];
		countavg3=countavg3+count3[i];
	}
	time1=(double)countavg/10000;
	time2=(double)countavg2/10000;
	time3=(double)countavg3/10000;	
	printf("InsertSort time: %f us    ",time1);
	printf("QuickSort time: %f us    ",time2);
	printf("MergeSort time: %f us    \n",time3);
	printf("\n");
	for(i=0;i<10;i++)
    {
    	count[i]=count2[i]=count3[i]=0;
	}
	countavg=countavg2=countavg3=k=0;
	free(a);
	free(b);
	free(c);
	}		

		
	while(curcle<4)
	{
		if(curcle==2)
		{
			N=4096;
			printf("随机数组规模为16K时：\n");
		}
		if(curcle==3)
		{
			N=16384;
			printf("随机数组规模为64K时：\n");
		}
	a=(int*)malloc(sizeof(int)*N);
	b=(int*)malloc(sizeof(int)*N);
  	c=(int*)malloc(sizeof(int)*N);
	srand(time(NULL));
	for(z=0;z<10;z++)
	{
	for(i=0;i<N;i++)
	{
		a[i]=rand();
	 	b[i]=c[i]=a[i];
	}
	 timeval start,end;
	 long dif_sec, dif_usec;
	 	 
	 for(j=0;j<20;j++)
	 {
	 	gettimeofday(&start, NULL);
		InsertSort(a,N);
		gettimeofday(&end, NULL);
		for(i=0;i<N;i++)
		{
			a[i]=b[i];
		}
		dif_sec = end.tv_sec - start.tv_sec;  
	    dif_usec = end.tv_usec - start.tv_usec; 
		count[k]=count[k]+dif_sec*1000000+dif_usec;
	 }
	 
	 for(j=0;j<20;j++)
	 {
	 	gettimeofday(&start, NULL);
		QuickSort(b,N);
		gettimeofday(&end, NULL);
		for(i=0;i<N;i++)
		{
			b[i]=a[i];
		}
		dif_sec = end.tv_sec - start.tv_sec;  
	    dif_usec = end.tv_usec - start.tv_usec; 
		count2[k]=count2[k]+dif_sec*1000000+dif_usec;
	 }
	  
     for(j=0;j<20;j++)
	 {
	 	gettimeofday(&start, NULL);
		MergeSort(c,N);
		gettimeofday(&end, NULL);
		for(i=0;i<N;i++)
		{
			c[i]=b[i];
		}
		dif_sec = end.tv_sec - start.tv_sec;  
	    dif_usec = end.tv_usec - start.tv_usec; 
		count3[k]=count3[k]+dif_sec*1000000+dif_usec;
	 }
	 k++;		
	}
	curcle++;
	for(i=0;i<10;i++)
	{
		countavg=countavg+count[i];
		countavg2=countavg2+count2[i];
		countavg3=countavg3+count3[i];
	}
	time1=(double)countavg/200;
	time2=(double)countavg2/200;
	time3=(double)countavg3/200;	
	printf("InsertSort time: %f us    ",time1);
	printf("QuickSort time: %f us    ",time2);
	printf("MergeSort time: %f us    \n",time3);
	printf("\n");
	for(i=0;i<10;i++)
    {
    	count[i]=count2[i]=count3[i]=0;
	}
	countavg=countavg2=countavg3=k=time1=time2=time3=0;	
	free(a);
	free(b);
	free(c);
	} 
	

	while(curcle<8)
	{
		if(curcle==4)
		{
			N=65536;
			printf("随机数组规模为256K时：\n");
		}
		if(curcle==5)
		{
			N=262144;
			printf("随机数组规模为1M时：\n");
		}
		if(curcle==6)
		{
			N=1048576;
			printf("随机数组规模为4M时：\n");
		}
		if(curcle==7)
		{
			N=4194304;
			printf("随机数组规模为16M时：\n");
		}	
	a=(int*)malloc(sizeof(int)*N);
	b=(int*)malloc(sizeof(int)*N);
  	c=(int*)malloc(sizeof(int)*N);
	for(z=0;z<10;z++)
	{
	srand(time(NULL));
	for(i=0;i<N;i++)
	{
		a[i]=rand();
	 	b[i]=c[i]=a[i];
	}
	 timeval start,end;
	 long dif_sec, dif_usec;
	 
	 
	 gettimeofday(&start, NULL);
	 	QuickSort(a,N);
	 gettimeofday(&end, NULL);
	 dif_sec = end.tv_sec - start.tv_sec;  
	 dif_usec = end.tv_usec - start.tv_usec;  
	 count[k]=count[k]+dif_sec*1000000+dif_usec;
	 
	 gettimeofday(&start, NULL);
	 	MergeSort(b,N);
	 gettimeofday(&end, NULL);
	 dif_sec = end.tv_sec - start.tv_sec;  
	 dif_usec = end.tv_usec - start.tv_usec;  
	 count2[k]=count2[k]+dif_sec*1000000+dif_usec;
	k++;	
	} 
	curcle++;
	for(i=0;i<10;i++)
	{
		countavg=countavg+count[i];
		countavg2=countavg2+count2[i];
	}
	time1=(double)countavg/10;
	time2=(double)countavg2/10;	
	printf("QuickSort time: %f us    ",time1);
	printf("MergeSort time: %f us    \n",time2);
	printf("\n");
	for(i=0;i<10;i++)
    {
    	count[i]=count2[i]=0;
	}
	countavg=countavg2=k=time1=time2=0;	
	free(a);
	free(b);
	free(c); 
	} 
 
 /* for(i=0;i<N;i++)
 {
 	printf("%d\t",c[i]);
 } */


 return 0;
}
