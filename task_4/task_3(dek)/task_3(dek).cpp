#include "stdafx.h"
#include <stdarg.h>
struct DEQ{
	double data;
	DEQ *prev,*next;
};
int size;
DEQ *front,*back;	//beginning and end of the list;
//function add element at the beginning of list;
void pushFront(int c,...)	
{
	
	DEQ* pel=new DEQ;
	va_list p1;		
	va_start(p1,c);
	pel->data=va_arg(p1,double);//get first element from list of parameters;
	if(front==NULL){	//if list is empty,add element at the first position;
		back=pel;
		pel->next=NULL;
	}else{
		pel->next=front;
		front->prev=pel;
	}
	front=pel;
	pel->prev=NULL;
	size++;
	for(int i=1;i<c;i++) //add other elements;
	{
		pel=new DEQ;
		pel->data=va_arg(p1,double);
		pel->next=front;
		front->prev=pel;
		front=pel;
		pel->prev=NULL;
		size++;
	}
}
//function add elements at the end of list;
void pushBack(int c,...)
{
	va_list p1;
	va_start(p1,c);
	DEQ* pel=new DEQ;
	pel->data=va_arg(p1,double);//get first element from list of parameters; 
	if (front==NULL)	//if list is empty,insert element at the last position;	
	{
		front=pel;
		pel->prev=NULL;
	}else{
		pel->prev=back;
		back->next=pel;
	}
	pel->next=NULL;
	back=pel;
	size++;
	for(int i=1;i<c;i++)	//add other elements;
	{
		pel=new DEQ;
		pel->data=va_arg(p1,double);
		back->next=pel;
		pel->prev=back;
		back=pel;
		back->next=NULL;
		size++;
	}
}
//function insert element at position "pos";
void insertAt(double p,int pos=0)
{
	int i=(int)0;
	if(pos<=(int)0){	//add element at the beginning of list;
		pushFront(1,p);
	}else if(pos>size)
	{
		pushBack(1,p);	//add element at the and of list;
	}else{
		DEQ* bef=front;
		DEQ* after;
		DEQ* pel=new DEQ;
		pel->data=p;
		while(i<pos){	//find element, befor which insert new element;
			bef=bef->next;
			i++;
		}
		after=bef->prev;
		bef->prev=pel;
		pel->next=bef;
		pel->prev=after;
		after->next=pel;
		size++;
	}
}
	//get first element
double popFront(void)
{
	if(front==NULL){
		puts("List is empty!");
		return (double)-1;
	}
	double res=front->data;
	size--;
	if(front->next==NULL){
		delete front;
		front=NULL;
		return res;
	}
	front=front->next;
	delete front->prev;
	front->prev=NULL;
	return res;
}
	//get last element;
double popBack(void)
{
	if(back==NULL){
		puts("List is empty!");
		return (double)-1;
	}
	double res=back->data;
	size--;
	if (back->prev==NULL){
		delete back;
		back=NULL;
		return res;
	}
	back=back->prev;
	delete back->next;
	back->next=NULL;
	return res;
}
	//print all list from beginng;
void print(void)
{
	DEQ* pel=front;
	while(pel!=NULL){
		printf("i=%.2f\n",pel->data);
		pel=pel->next;
	}
}
//function return element by it number;
double at(int pos)
{
	int i=(int)0;
	DEQ* pel=front;
	if((pos<(int)0)||(pos>size-(int)1)){
		puts("Error! Index out of bound!");
		return (int)-1;
	}
	while(i<pos){
		i++;
		pel=pel->next;
	}
	return pel->data;
}
//function return element posotion by value;
int at(double value)
{
	DEQ *pel=front;
	for(int i=(int)0;pel!=NULL;i++){
		if(pel->data==value) return i;
		pel=pel->next;
	}
	return (int)-1;
}
//function delete element by it position;
double deleteAt(int pos)
{
	DEQ*pel=front;
	double res;
	int i=0;
	if(pos<=(int)0)
		return popFront();	//delete first element;
	if(pos>size)
		return popBack();	//delete last element;
	while(i<pos){			//find element;
		i++;
		pel=pel->next;
	}
	res=pel->data;
	pel->prev->next=pel->next;
	pel->next->prev=pel->prev;
	size--;
	delete pel;
	return res;
}
int deleteAt(double value,int i=0)
{
	DEQ*pel=front;
	for(int j=0;(j<i)&&(pel);j++)//go to element with index i;
		pel=pel->next;
	while((pel)&&(pel->data!=value))//find element
	{
		pel=pel->next;
		i++;
	}
	if(pel==NULL) return (int)-1;//element not found;
	if (i==0) {		//delete first element;
		popFront();
		return i;
	}
	if(i==size){	//delete last element;
		popBack();
		return i;
	}				//delete element with index i;	
	pel->next->prev=pel->prev;
	pel->prev->next=pel->next;
	delete pel;
	return i;	
}
//function delete list;
void delDEQ(void)
{	
	DEQ*pel=front;
	while(pel!=NULL){
		front=pel->next;
		delete pel;
		pel=front;
		size--;
	}
	back=NULL;
}
int _tmain(int argc, _TCHAR* argv[])
{	//pointers on functions
	void(*ppushFront)(int,...)=pushFront;
	void(*ppushBack)(int,...)=pushBack;
	double(*ppopFront)(void)=popFront;
	double(*ppopBack)(void)=popBack;
	void (*pinsertAt)(double,int)=insertAt;
	void (*pprint)(void)=print;
	void (*pdelDEQ)(void)=delDEQ;
	for(int i=(int)0;i<4;i++){
		ppushBack(1,(double)i*i);
	}
	puts("print()");
	pprint();
	getchar();

	puts("insertAt(-100),1");	//insert element by position;
	insertAt(-100,1);
	pprint();
	getchar();

	puts("popFront()");		//delete first element; 
	ppopFront();
	pprint();
	getchar();

	puts("popBack()");		//delete last element;
	ppopBack();
	pprint();
	getchar();

	puts("pushFront(3,-1,-2,-3)");	//insert elements at the beginning of list;
	ppushFront(3,(double)-1,(double)-2,(double)-3);
	pprint();
	getchar();

	puts("pushBack(3,-1,-2,-3)");	//insert elements at the end of list;
	ppushBack(3,(double)-1,(double)-2,(double)-3);
	pprint();
	getchar();

	printf("at(4)=%.2f\n",at((int)4));//get 4th element;
	getchar();

	printf("at((double)4)=%d\n",at((double)4));//get "value" index ;
	getchar();

	puts("deleteAt(1)");	//delete at first position;
	deleteAt((int)1);
	pprint();
	getchar();
	
	puts("deleteAt((double)-1,2)");	//delete by value, start from 2nd position;
	deleteAt((double)-1,2);
	pprint();
	getchar();

	puts("Free list");		//delete all elements;
	pdelDEQ();
	pprint();
	getchar();

	puts("popFront()");		//delete first element of empty list;
	ppopFront();
	pprint();
	getchar();
	return 0;
}

