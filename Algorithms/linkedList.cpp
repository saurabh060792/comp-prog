#include <cstdio>
#include <algorithm>

using namespace std;

typedef struct linkedList
{
	int value;
	linkedList *next;

}linkedList;

linkedList* insert(linkedList *l, int value);
linkedList* remove(linkedList *l, int value);
void printLinkedList(linkedList *l);

int main()
{
	linkedList *l = NULL;
	
	return 0;
}

void printLinkedList(linkedList *l)
{
	while(l){ 
		printf("%d ",l->value);
		l = l->next;
	}
	printf("\n");
}


linkedList* insert(linkedList *l, int value)
{
	if(l) {
		linkedList *temp = new linkedList;
		temp->value = value;
		temp->next = l;
		l = temp;
	}
	else {
		l = new linkedList;
		l->value = value;
		l->next = NULL;
	}
	return l;
}

linkedList* remove(linkedList *l, int value)
{
	linkedList *temp, *temp2;

	if(!l) return NULL;
	while(l && l->value == value) {
		temp2 = l;
		l = l->next;
		delete temp2;
	}
	temp = l;
	while(temp && temp->next) {
		if(temp->next->value == value) {
			temp2 = temp->next;
			temp->next = temp->next->next;
			delete temp2;
			continue;
		}
		temp = temp->next;
	}
	return l;
}