#define TESTS

#define TEST(method, id)  _test_##id##method()

#include "task.c"
// START - _constructor_SingleLinkedCyclicList
void TEST(_constructor_SingleLinkedCyclicList, 1)
{
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    if (list.head != NULL)
    {
        printf("\t1: calling constructor should set list.head to NULL\n");
    }
}
// END - _constructor_SingleLinkedCyclicList

// START - _method_SingleLinkedCyclicList_append
void TEST(_method_SingleLinkedCyclicList_append, 1)
{
    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);

    // CHECK
    _method_SingleLinkedCyclicList_append(&list, 1);

    // TEST
    if (list.head->data != 1)
    {
        printf("\t1: adding 1 to an empty list must make it's head->data equal to 1\n");
    }
    if (list.head->next != list.head)
    {
        printf("\t1: after appending a value to an empty list head->next should be euqal to itself\n");
    }
}

void TEST(_method_SingleLinkedCyclicList_append, 2)
{
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    if (list.head->data != 1)
    {
        printf("\t2: adding 2 to a list containig [1] mustn't change it's head->data\n");
    }
    if (list.head->next == NULL)
    {
        printf("\t2: adding 2 to a list containig [1] must make head->next pointing to non-NULL value\n");
    }
}
// END - _method_SingleLinkedCyclicList_append

int main()
{
    printf("_constructor_SingleLinkedCyclicList\n");
    {
        _test_1_constructor_SingleLinkedCyclicList();
    }
    printf("_method_SingleLinkedCyclicList_append\n");
    {
        _test_1_method_SingleLinkedCyclicList_append();
        _test_2_method_SingleLinkedCyclicList_append();
    }
}