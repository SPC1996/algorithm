#include <stdio.h>
#include <stdlib.h>

int base_search(int arr[],int len,int key);
int binary_search(int arr[],int len,int key);
int find_min(int arr[],int len);
int find_max(int arr[],int len);
int random_search(int arr[],int start,int end,int rank);
int random_partition(int arr[],int start,int end);

void show(int arr[],int len);

int main(){
	int a[]={1,4,7,9,15,23,27,53,56,78};
    int b[]={23,45,23,56,1,3,2,68,45,10};
    int len=sizeof(a)/sizeof(int);
    int key=23;
    show(a,len);
    printf("binary_search:The index of %d is %d\n",key,binary_search(a,len,key));
    show(b,len);
    printf("base_search:The index of %d is %d\n",key,base_search(b,len,key));
    printf("The min number is %d\n",find_min(b,len));
    printf("The max number is %d\n",find_max(b,len));
    printf("The rank %d number is %d\n",4,random_search(b,0,len-1,4));

}

void show(int arr[],int len){
	int i;
	for(i=0;i<len;i++)
		printf("%d ",arr[i]);
	printf("\n");
}

int base_search(int arr[],int len,int key){
	int i;	
	for(i=0;i<len;i++)
		if(arr[i]==key)
			return i;
	return -1;
}

int binary_search(int arr[],int len,int key){
    int low,high,mid;
    low=0;
    high=len-1;
    mid=(low+high)/2;
    while(low<=high){
        if(arr[mid]==key)
            return mid;
        else if(arr[mid]>key)
            high=mid-1;
        else
            low=mid+1;
        mid=(low+high)/2;
    }
    return -1;
}

int find_min(int arr[],int len){
    int i,min=0;
    for(i=1;i<len;i++){
        if(arr[i]<arr[min])
            min=i;
    }
    return arr[min];
}

int find_max(int arr[],int len){
    int i,max=0;
    for(i=1;i<len;i++){
        if(arr[i]>arr[max])
            max=i;
    }
    return arr[max];
}

int random_search(int arr[],int start,int end,int rank){
    if(start==end)
        return arr[start];
    int q=random_partition(arr,start,end);
    int k=q-start+1;
    if(rank==k)
        return arr[q];
    else if(rank<k)
        return random_search(arr,start,q-1,rank);
    else
        return random_search(arr,q+1,end,rank-k);
}

int random_partition(int arr[],int start,int end){
    srand(time(NULL));
    int rand_index=start+(int)(rand()%(end-start+1));
    int tm=arr[end];
    arr[end]=arr[rand_index];
    arr[rand_index]=tm;
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

