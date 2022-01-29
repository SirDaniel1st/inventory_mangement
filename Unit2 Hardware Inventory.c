#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

//Creating the Structs that will be used in the development and running  of the inventory program

struct Stock{
    int itemID;
    float costP;
    int amt;
    char name[100];
    char supplier[100];
};

//defining a global varaibles for an array of stocks
struct Stock stocks[100];

// define a Node in a linked list
struct Node {
   struct Stock data;
   struct Node * next;
};

// define Queue structure
struct Queue {
   struct Node *front;
   struct Node *rear;    
};  

// Linked list function
struct Node * createNode (struct Stock stock){
	Node * newNode; 
	newNode = (Node *) malloc (sizeof (Node));
	newNode->data = stock;
	newNode->next = NULL;
	return newNode;
}

// Queue functions
struct Queue * initQueue() {
	Queue * q;
	q = (Queue *) malloc (sizeof (Queue));
	q->front = NULL;
	q->rear = NULL;
}

bool isEmpty(Queue * q) {
    return (q->front == NULL);
}

void enqueue(Queue * q, struct Stock stock) {
	Node *newNode = createNode(stock);
	if (isEmpty(q)) { //First node in queue
		q->front = newNode;             
		q->rear = newNode;
	}    
	else { 
		q->rear->next = newNode;
		q->rear = newNode;
	}   
}          

struct Stock dequeue(Queue * q) {
	struct Stock n;
	Node *temp;
	if (isEmpty(q)) {
		printf("Queue is empty.");
	}
	n = q->front->data;
	temp = q->front;
	q->front = q->front->next;
	if (q->front == NULL)
		q->rear = NULL;
	free(temp);
	return n;
}

struct Stock peek(Queue * q) {
	struct Stock n;
	Node *top;
	if (isEmpty(q)) {
		printf("Queue is empty.");
	}
	n = q->front->data;
	return n;
}

//read data into struct array function
int readData(){
    FILE *fp;
    int id=0, amt=0, i=0;
    float cPrice=0.00;
    char name[100], supplier[100];

    fp=fopen("StockList.txt","r");
    while(!feof(fp)){
        fscanf(fp,"%d %f %d",&id,&cPrice,&amt);
		fscanf(fp, "%s",name);
		fscanf(fp,"%s",supplier);
        stocks[i].itemID=id;
        stocks[i].costP=cPrice;
        stocks[i].amt=amt;
        strcpy(stocks[i].name,name);
        strcpy(stocks[i].supplier,supplier);
        i++;
    }
    fclose(fp);
    return i;
}

int main(){
	int i=0;
	i=readData();
	printf("Amount of Items : %d",i);
	return 0;
}