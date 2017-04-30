#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int key;
	struct node *next;
} KeyNode;

void bubble_sort(int arr[],int len);
void select_sort(int arr[],int len);
void insert_sort(int arr[],int len);
void merge_sort(int arr[],int temp[],int start,int end);
void merge(int arr[],int temp[],int start,int mid,int end);
void quick_sort(int arr[],int start,int end);
int partition(int arr[],int start,int end);
void heap_sort(int arr[],int len);
void max_heapify(int arr[],int heap_size,int i);
void create_heap(int arr[],int len);
void count_sort(int arr[],int newArr[],int len,int max);
void radix_sort(int arr[],int len,int p,int k);
void bucket_sort(int arr[],int len,int bucket_size);

void show(int arr[],int len);

int main(void){
	int a[]={23,35,52,21,11,67,25,19,32,28};
	int b[10];
	int len=sizeof(a)/sizeof(int);
	show(a,len);
	bucket_sort(a,len,10);
	show(a,len);
}

void show(int arr[],int len){
	int i;        
	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void bubble_sort(int arr[],int len){
	int i,j;
	for(i=len-1;i>0;i--){
		for(j=0;j<i;j++){
			if(arr[j]>arr[j+1]){
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

void select_sort(int arr[],int len){
	int i,j,max;
	for(i=len-1;i>0;i--){
		max=0;
		for(j=1;j<=i;j++){
			if(arr[max]<arr[j]){
				max=j;
			}
		}
		int temp=arr[max];
		arr[max]=arr[i];
		arr[i]=temp;
	}
}

void insert_sort(int arr[],int len){
	int i,j,current;
	for(i=1;i<len;i++){
		current=arr[i];
		int k=i;
		for(j=i-1;j>=0;j--){
			if(current<arr[j]){
				arr[j+1]=arr[j];
				k=j;
			}
		}
		arr[k]=current;
	}
}

void merge_sort(int arr[],int temp[],int start,int end){
	if(start>=end)
		return;
	int mid=(start+end)/2;
	merge_sort(arr,temp,start,mid);
	merge_sort(arr,temp,mid+1,end);
	merge(arr,temp,start,mid,end);
}

void merge(int arr[],int temp[],int start,int mid,int end){
	int i,j,k;
	for(i=start;i<=mid;i++)
		temp[i]=arr[i];
	for(j=mid+1;j<=end;j++)
		temp[j]=arr[j];
	i=start;
	j=mid+1;
	k=start;
	while(i<=mid&&j<=end){
		if(temp[i]<temp[j])
			arr[k++]=temp[i++];
		else
			arr[k++]=temp[j++];
	}
	if(i==mid+1)
		while(j<=end)
			arr[k++]=temp[j++];
	if(j==end+1)
		while(i<=mid)
			arr[k++]=temp[i++];
}

void quick_sort(int arr[],int start,int end){
	if(start>=end)
		return;
	int mid=partition(arr,start,end);
	quick_sort(arr,start,mid-1);
	quick_sort(arr,mid+1,end);
}

int partition(int arr[],int start,int end){
	int part=arr[end];
	int i=start-1,j=start;
	while(j<end){
		if(arr[j]<=part){
			i=i+1;
			if(i!=j){
				int temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
		j++;
	}
	arr[end]=arr[i+1];
	arr[i+1]=part;
	return i+1;
}

void heap_sort(int arr[],int len){
	create_heap(arr,len);
	int heap_size=len-1,k;
	for(k=heap_size;k>0;k--){
		int temp=arr[0];
		arr[0]=arr[k];
		arr[k]=temp;
		heap_size=heap_size-1;
		max_heapify(arr,heap_size,0);
	}
}

void max_heapify(int arr[],int heap_size,int i){
	int l=2*i+1,r=2*i+2,largest;
	if(l<=heap_size&&arr[l]>arr[i])
		largest=l;
	else
		largest=i;
	if(r<=heap_size&&arr[r]>arr[largest])
		largest=r;
	if(largest!=i){
		int temp=arr[i];
		arr[i]=arr[largest];
		arr[largest]=temp;
		max_heapify(arr,heap_size,largest);
	}
}

void create_heap(int arr[],int len){
	int heap_size=len-1,j;
	for(j=(heap_size-1)/2;j>=0;j--){
		max_heapify(arr,heap_size,j);
	}
}

void count_sort(int arr[],int newArr[],int len,int max){
	int *temp=(int*)malloc(sizeof(int)*(max+1));
	int i;
	for(i=0;i<max+1;i++)
		temp[i]=0;
	for(i=0;i<len;i++)
		temp[arr[i]]+=1;
	for(i=1;i<max+1;i++)
		temp[i]=temp[i-1]+temp[i];
	for(i=0;i<len;i++){
		newArr[temp[arr[i]]-1]=arr[i];
		temp[arr[i]]=temp[arr[i]]-1;
	}
	free(temp);
}

void radix_sort(int arr[],int len,int p,int k){
	int *counts,*temp;
	int index,pval,i,j,n;
	counts=(int*)malloc(k*sizeof(int));
	temp=(int*)malloc(len*sizeof(int));
	for(n=0;n<p;n++){
		for(i=0;i<k;i++)
				counts[i]=0;
		pval=(int)pow((double)k,(double)n);
		for(j=0;j<len;j++){
			index=(int)(arr[j]/pval)%k;
			counts[index]=counts[index]+1;
		}
		for(i=1;i<k;i++)
			counts[i]=counts[i]+counts[i-1];
		for(j=len-1;j>=0;j--){
			index=(int)(arr[j]/pval)%k;
			temp[counts[index]-1]=arr[j];
			counts[index]--;
		}
		memcpy(arr,temp,len*sizeof(int));
	}
	free(counts);
	free(temp);
}

void bucket_sort(int arr[],int len,int bucket_size){
	int i,j;
	KeyNode **bucket=(KeyNode**)malloc(bucket_size*sizeof(KeyNode*));
	for(i=0;i<bucket_size;i++){
		bucket[i]=(KeyNode*)malloc(sizeof(KeyNode));
		bucket[i]->key=0;
		bucket[i]->next=NULL;
	}
	for(j=0;j<len;j++){
		KeyNode *node=(KeyNode*)malloc(sizeof(KeyNode));
		node->key=arr[j];
		node->next=NULL;
		int index=arr[j]/10;
		KeyNode *p=bucket[index];
		if(p->key==0){
			bucket[index]->next=node;
			(bucket[index]->key)++;
		}
		else{
			while(p->next!=NULL&&p->next->key<=node->key)
					p=p->next;
			node->next=p->next;
			p->next=node;
			(bucket[index]->key)++;
		}
	}
	KeyNode *k=NULL,*pre=NULL;
	j=0;
	for(i=0;i<bucket_size;i++)
			for(k=bucket[i]->next;k!=NULL;k=k->next){
					if(pre!=NULL)
							free(pre);
					pre=k;
					arr[j++]=k->key;
			}
	free(bucket);
}
