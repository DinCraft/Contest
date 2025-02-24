#include <stdio.h>

#define METHOD(type, name) _method_##type##_##name

struct SElement
{
	int data;
	struct SElement *next;
};

struct SingleLinkedCyclicList
{
	struct SElement *head;
};

void METHOD(SingleLinkedCyclicList, append) ()
{

}

int main()
{
	printf("123");
	_method_SingleLinkedCyclicList_append();
}
