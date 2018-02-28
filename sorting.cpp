#include <iostream>
#include <stack>

using namespace std;

void printArray(int arr[],int n){
	for(int i = 0 ; i < n ; i++){
		cout<<arr[i]<<" ";
	}
}

void selection(int arr[],int n){
	int temp,index;
	for(int i = 0 ; i < n-1 ; i++){
		index = i;
		for(int j = i+1 ; j < n ; j++){
			if(arr[index] > arr[j]){
				index = j;
			}
		}
		temp = arr[i];
		arr[i] = arr[index];
		arr[index] = temp;
	}
	printArray(arr,n);
}

void swap(int* a,int* b){
	int temp = *b;
	*b = *a;
	*a = temp;
}

int min(int a,int b){
	return (a<b) ? a:b;
}

int partition(int arr[],int low,int high){
	int pivot = arr[high];
	int i = (low-1);
	for(int j = low ; j < high ; j++){
		if(arr[j] <= pivot){
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	swap(&arr[i+1],&arr[high]);
	return i+1;
}

void quick(int arr[],int low,int high){
	if(low < high){
		int pi = partition(arr,low,high);
		quick(arr,low,pi-1);
		quick(arr,pi+1,high);
	}
}

void merge(int arr[],int l,int m,int r){
	int i,j,k;
	int n1 = m-l+1;
	int n2 = r-m;
	int L[n1],R[n2];
	for(i = 0 ; i < n1 ; i++)
		L[i] = arr[l+i];
	for (j = 0 ; j < n2 ; j++)
		R[j] = arr [m+1+j];
	i=0;
	j=0;
	k=l;
	while(i < n1 && j < n2){
		if(L[i] < R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while(i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}
	while(j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[],int l,int r){
	if(l < r){
		int m = (l+r)/2;
		mergeSort(arr,l,m);
		mergeSort(arr,m+1,r);
		merge(arr,l,m,r);
	}
}

void bucket(int arr[],int n){	
}

int getMax(int arr[],int n){
	int max = arr[0];
	for(int i = 1 ; i < n ; i++)
		if(max < arr[i])
			max= arr[i];
	return max;		
}

void countSort(int arr[],int exp,int n){
	int out[n];
	int count[10]={0};
	for(int i = 0 ; i < n ; i++)
		count[(arr[i]/exp)%10]++;
	for(int i = 1 ; i < 10 ; i++)
		count[i] += count[i-1];
	for(int i = n-1 ; i >= 0 ; i--){
		out[count[(arr[i]/exp)%10]-1] = arr[i];
		count[(arr[i]/exp)%10]--;
	}
	for(int i = 0 ; i < n ; i++)
		arr[i] = out[i];
}

void radix(int arr[],int n){
	int max = getMax(arr,n);
	for(int exp = 1 ; max/exp > 0 ; exp*=10)
		countSort(arr,exp,n);
}

void heapify(int arr[],int n,int i){
	int l = 2*i + 1;
	int r = 2*i + 2;
	int largest = i;
	if(l < n && arr[l] > arr[largest])
		largest = l;
	if(r < n && arr[r] > arr[largest])
		largest = r;
	if(largest != i){
		swap(&arr[i],&arr[largest]);
		heapify(arr,n,largest);
	}		
}

void heapSort(int arr[],int n){
	for(int i = n/2 - 1 ; i >= 0 ; i--)
		heapify(arr,n,i);
	for(int i = n-1 ; i > 0 ; i--){
		swap(&arr[0],&arr[i]);
		heapify(arr,i,0);
	}
}

void insertion(int arr[],int n){
	for(int i = 1 ; i < n ; i++){
		int key = arr[i];
		int j = i-1;
		while(j >=0 && key < arr[j]){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}

void bubbleSort(int arr[],int n){
	for(int i = 0 ; i < n-1 ; i++)
		for(int j = 0 ; j < n-1-i ; j++)
			if(arr[j] > arr[j+1])
				swap(&arr[j],&arr[j+1]);
}

void recBubble(int arr[],int n){
	if(n > 1){
		for(int j = 0 ; j < n-1 ; j++)
			if(arr[j] > arr[j+1])
				swap(&arr[j],&arr[j+1]);
		recBubble(arr,n-1);		
	}
}

void recInsertion(int arr[],int n,int index){
	if(index < n){
		int key = arr[index];
		int j = index - 1;
		while(j >= 0 && arr[j] > key){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
		recInsertion(arr,n,index+1);
	}
}

void itrMerge(int arr[],int n){
	for(int currSize = 1 ; currSize <= n - 1 ; currSize*=2){
		for(int leftStart = 0 ; leftStart < n-1 ; leftStart += currSize*2){
			int right = min(leftStart + currSize*2 - 1,n - 1);
			int mid = leftStart + currSize - 1;
			merge(arr,leftStart,mid,right);
		}
	}
}

void itrQuick(int arr[],int l,int n){
	stack<int> s;
	s.push(l);
	s.push(n);
	while(!s.empty()){
		int high = s.top();
		s.pop();
		int low = s.top();
		s.pop();
		int pi = partition(arr,low,high);
		if(pi - 1 > low){
			s.push(low);
			s.push(pi - 1);
		}
		if(pi + 1 < high){
			s.push(pi + 1);
			s.push(high);
		}
	}
}

int main() {
	int n,option;
	cout<<"Enter the number of elements"<<endl;
	cin>>n;
	int arr[n],out[n];
	cout<<"Enter the elements"<<endl;
	for(int i = 0 ; i < n ; i++){
		cin>>arr[i];
		out[i] = arr[i];
	}
	while(1){
		cout<<"Enter the sorting method"<<endl;
		cout<<"1.Selection sort"<<endl;
		cout<<"2.Quick sort"<<endl;		//imp
		cout<<"3.Merge sort"<<endl;		//imp
		cout<<"4.Bucket sort"<<endl;
		cout<<"5.Radix sort"<<endl;		//imp
		cout<<"6.Heap sort"<<endl;		//imp
		cout<<"7.Insertion sort"<<endl;
		cout<<"8.Bubble sort"<<endl;
		cout<<"9.Recursive bubble sort"<<endl;
		cout<<"10.Recursive insertion sort"<<endl;
		cout<<"11.Iterative merge sort"<<endl;
		cout<<"12.Iterative quick sort"<<endl;
		cout<<"13.Exit"<<endl;
		cin>>option;
		switch(option){
			case 1:
				selection(out,n);
				break;
			case 2:
				quick(out,0,n-1);
				printArray(out,n);
				break;
			case 3:
				mergeSort(out,0,n-1);
				printArray(out,n);
				break;
			case 4:
				bucket(out,n);
				printArray(out,n);
				break;
			case 5:
				radix(out,n);
				printArray(out,n);
				break;
			case 6:
				heapSort(out,n);
				printArray(out,n);
				break;
			case 7:
				insertion(out,n);
				printArray(out,n);
				break;
			case 8:
				bubbleSort(out,n);	
				printArray(out,n);
				break;
			case 9:
				recBubble(out,n);	
				printArray(out,n);
				break;	
			case 10:
				recInsertion(out,n,1);
				printArray(out,n);
				break;
			case 11:
				itrMerge(out,n);
				printArray(out,n);
				break;
			case 12:
				itrQuick(out,0,n-1);
				printArray(out,n);
				break;	
			case 13:
				exit(0);
				break;	
			default:
				break;	
		}
	}
}
