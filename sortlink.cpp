#include <iostream>
#include <stack>

using namespace std;

struct Node{
	int data;
	Node* next;
	Node* prev;
};

struct Node* addNode(Node* head,int num){
	Node* temp = new Node();
	temp->data = num;
	temp->next = NULL;
	temp->prev = NULL;
	if(head == NULL){
		head = temp;
		return head;
	}
	temp->next = head;
	head->prev = temp;
	head = temp;
	return head;
}

void printList(Node* head){
	Node* temp = head;
	while(temp != NULL){
		cout<<temp->data<<" ";
		temp = temp->next;
	}
	cout<<endl;
}

struct Node* lastNode(Node* head,int r){
	Node* temp = head;
	if(r == 1) return head;
	for(int i = 1 ; i < r ; i++){
		temp = temp->next;
	}
	return temp;
}

void swap(Node* head,int a,int b){
	int temp = lastNode(head,a)->data;
	lastNode(head,a)->data = lastNode(head,b)->data;
	lastNode(head,b)->data = temp;
}

void merge(){
}

int partition(Node* head,int l,int r){
	int i = l - 1;
	int pivot = lastNode(head,r)->data;
	while(l < r){
		int curr = lastNode(head,l)->data;
		if(curr <= pivot){
			i++;
			swap(head,i,l);
		}
		l++;
	}
	swap(head,i+1,r);
	return i+1;
}

struct Node* quick(Node* head,int l,int r){
	stack<int> s;
	s.push(l);
	s.push(r);
	while(!s.empty()){
		r = s.top();
		s.pop();
		l = s.top();
		s.pop();
		int pi = partition(head,l,r);
		if(pi - 1 > l){
			s.push(l);
			s.push(pi - 1);
		}
		if(pi + 1 < r){
			s.push(pi + 1);
			s.push(r);
		}
	}
	return head;
}

int main() {
	Node* head = new Node();
	head = NULL;
	int n,option,num;
	cout<<"Enter the number of elements"<<endl;
	cin>>n;
	cout<<"Enter the elements"<<endl;
	for(int i = 0 ; i < n ; i++){
		cin>>num;
		head = addNode(head,num);
	}
	printList(head);
	while(1){
		cout<<"Enter the sorting method"<<endl;
		cout<<"1.Merge link sort"<<endl;
		cout<<"2.Quick link sort"<<endl;
		cout<<"3.Exit"<<endl;
		cin>>option;
		switch(option){
			case 1:
				merge();
				printList(head);
				break;
			case 2:
				head = quick(head,1,n);
				printList(head);
				break;
			case 3:
				exit(0);
				break;	
			default:
				break;	
		}
	}
}
