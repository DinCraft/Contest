#define TESTS

#define TEST(method, id)  _test_##id##method()

#include "task.c"

static int id;

void throw(char string[])
{
    printf("\t%d: %s\n", id, string);
}

// START - _constructor_SingleLinkedCyclicList
void TEST(_constructor_SingleLinkedCyclicList, 1)
{
    id = 1;
    // ACTION
    // Calling constructor

    // SETUP
    struct SingleLinkedCyclicList list;
    // TEST
    _constructor_SingleLinkedCyclicList(&list);

    // CHECK
    if (list.head != NULL)
    {
        throw("calling constructor should set list.head to NULL");
        return;
    }
}
// END - _constructor_SingleLinkedCyclicList

// START - _method_SingleLinkedCyclicList_append
void TEST(_method_SingleLinkedCyclicList_append, 1)
{
    id = 1;
    // ACTION
    // Appending value to an empty list

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);

    // TEST
    _method_SingleLinkedCyclicList_append(&list, 1);

    // CHECK
    if (list.head->data != 1)
    {
        throw("appending value to an empty list must make it's head->data equal to that value");
        return;
    }
    if (list.head->next != list.head)
    {
        throw("after appending a value to an empty list head->next should be euqal to itself");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_append, 2)
{
    id = 2;
    // ACTION
    // Appending value to a list containing one element

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);

    // TEST
    _method_SingleLinkedCyclicList_append(&list, 2);

    // CHECK
    if (list.head->data != 1)
    {
        throw("adding '2' to a list [1] mustn't change it's head->data");
        return;
    }
    if (list.head->next == NULL)
    {
        throw("adding 2 to a list [1] must make head->next pointing to non-NULL value");
        return;
    }
    if (list.head->next->data != 2)
    {
        throw("adding 2 to a list [1] must make head->next pointing to value which data is equal to '2'");
        return;
    }
    if (list.head->next->next != list.head)
    {
        throw("adding an element to the list must make added element pointing to the head");
    }
}
// END - _method_SingleLinkedCyclicList_append

// START - _method_SingleLinkedCyclicList_get_length
void TEST(_method_SingleLinkedCyclicList_get_length, 1)
{
    id = 1;
    // Action
    // Checking length of an empty list

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);

    // TEST
    int length = _method_SingleLinkedCyclicList_get_length(&list);

    // CHECK
    if (length != 0)
    {
        throw("length of an empty list must be '0'");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_get_length, 2)
{
    id = 2;
    // Action
    // Checking length of an list containing one element

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);

    // TEST
    int length = _method_SingleLinkedCyclicList_get_length(&list);

    // CHECK
    if (length != 1)
    {
        throw("length of an list containing one element must be '1'");
        return;
    }
}
// END - _method_SingleLinkedCyclicList_get_length

// START - _method_SingleLinkedCyclicList_exists
void TEST(_method_SingleLinkedCyclicList_exists, 1)
{
    id = 1;
    // ACTION
    // Check if an element exists in an empty list

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    struct SingleLinkedElement *element = malloc(sizeof(struct SingleLinkedElement));

    // TEST
    int existence = _method_SingleLinkedCyclicList_exists(&list, element);

    // CHECK
    if (existence == 1)
    {
        throw("there can't be any elements in an empty list");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_exists, 2)
{
    id = 2;
    // ACTION
    // Check if a single element exists in a list [1]

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    struct SingleLinkedElement *element = malloc(sizeof(struct SingleLinkedElement));

    // TEST
    int existence = _method_SingleLinkedCyclicList_exists(&list, element);

    // CHECK
    if (existence == 1)
    {
        throw("there can't be an element which is not in the list");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_exists, 3)
{
    id = 3;
    // ACTION
    // Check if an element from list exists in that list [1]

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    struct SingleLinkedElement *element = list.head;

    // TEST
    int existence = _method_SingleLinkedCyclicList_exists(&list, element);

    // CHECK
    if (existence == 0)
    {
        throw("element from the list must be in the list");
        return;
    }
}
// END - _method_SingleLinkedCyclicList_exists

// START - _method_SingleLinkedCyclicList_remove
void TEST(_method_SingleLinkedCyclicList_remove, 1)
{
    id = 1;
    // ACTION
    // Trying to remove an element from an empty list

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    struct SingleLinkedElement *element = malloc(sizeof(struct SingleLinkedElement));
    element->data = 1;
    element->next = NULL;

    // TEST
    _method_SingleLinkedCyclicList_remove(&list, element);

    // CHECK
    if (list.head != NULL)
    {
        throw("head must be NULL in empty list");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove, 2)
{
    id = 2;
    // ACTION
    // Trying to remove an existing element from the list [1]

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    struct SingleLinkedElement *element = list.head;

    // TEST
    _method_SingleLinkedCyclicList_remove(&list, element);

    // CHECK
    if (list.head != NULL)
    {
        throw("head must be NULL in empty list");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove, 3)
{
    id = 3;
    // ACTION
    // Trying to remove the first element from the list [1, 2]

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    struct SingleLinkedElement *element = list.head;

    // TEST
    _method_SingleLinkedCyclicList_remove(&list, element);

    // CHECK
    if (list.head == NULL)
    {
        throw("head must can't be NULL in a non-empty list");
        return;
    }
    if (list.head->data != 2)
    {
        throw("head must point to the remaining element in list with one element");
        return;
    }
    if (list.head->next != list.head)
    {
        throw("head->next must point to head in list with one element");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove, 4)
{
    id = 4;
    // ACTION
    // Trying to remove the first element from the list [1, 2, 3]

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    _method_SingleLinkedCyclicList_append(&list, 3);
    struct SingleLinkedElement *element = list.head;

    // TEST
    _method_SingleLinkedCyclicList_remove(&list, element);

    // CHECK
    if (list.head == NULL)
    {
        throw("head must can't be NULL in a non-empty list");
        return;
    }
    if (list.head->data != 2)
    {
        throw("head must point to the next element after head");
        return;
    }
    if (list.head->next->next != list.head)
    {
        throw("head->next->next must point to head in list with two elements");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove, 5)
{
    id = 5;
    // ACTION
    // Trying to remove the second element from the list [1, 2, 3]

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    _method_SingleLinkedCyclicList_append(&list, 3);
    struct SingleLinkedElement *element = list.head->next;

    // TEST
    _method_SingleLinkedCyclicList_remove(&list, element);

    // CHECK
    if (list.head == NULL)
    {
        throw("head can't be NULL in a non-empty list");
        return;
    }
    if (list.head->data != 1)
    {
        throw("head must remain the same after deleting head->next");
        return;
    }
    if (list.head->next->next != list.head)
    {
        throw("head->next->next must point to head in list with two elements");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove, 6)
{
    id = 6;
    // ACTION
    // Trying to remove the second element from the list [1, 2]

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    struct SingleLinkedElement *element = list.head->next;

    // TEST
    _method_SingleLinkedCyclicList_remove(&list, element);

    // CHECK
    if (list.head == NULL)
    {
        throw("head can't be NULL in a non-empty list");
        return;
    }
    if (list.head->data != 1)
    {
        throw("head must remain the same after deleting head->next");
        return;
    }
    if (list.head->next != list.head)
    {
        throw("head->next must point to head in list with one element");
        return;
    }
}
// END - _method_SingleLinkedCyclicList_remove

// START - _method_SingleLinkedCyclicList_remove_from
void TEST(_method_SingleLinkedCyclicList_remove_from, 1)
{
    id = 1;
    // ACTION
    // Trying to remove zero elements from the list [1, 2] starting from non-existant element

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    struct SingleLinkedElement *element = NULL;

    // TEST
    _method_SingleLinkedCyclicList_remove_from(&list, element, 0);

    // CHECK
    if (list.head == NULL)
    {
        throw("head can't be NULL in a non-empty list");
        return;
    }
    if (_method_SingleLinkedCyclicList_get_length(&list) != 2)
    {
        throw("length must be equal to 2");
        return;
    }
    if (list.head->data != 1)
    {
        throw("head must remain the same");
        return;
    }
    if (list.head->next->data != 2)
    {
        throw("head->next must remain the same");
        return;
    }
    if (list.head->next->next != list.head)
    {
        throw("head->next->next must point to head");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove_from, 2)
{
    id = 2;
    // ACTION
    // Trying to remove the zero elements from the list [1, 2] starting from first element

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    struct SingleLinkedElement *element = list.head;

    // TEST
    _method_SingleLinkedCyclicList_remove_from(&list, element, 0);

    // CHECK
    if (list.head == NULL)
    {
        throw("\t2: head can't be NULL in a non-empty list");
        return;
    }
    if (_method_SingleLinkedCyclicList_get_length(&list) != 2)
    {
        throw("length must be equal to 2");
        return;
    }
    if (list.head->data != 1)
    {
        throw("head must remain the same");
        return;
    }
    if (list.head->next->data != 2)
    {
        throw("head->next must remain the same");
        return;
    }
    if (list.head->next->next != list.head)
    {
        throw("head->next->next must point to head");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove_from, 3)
{
    id = 3;
    // ACTION
    // Trying to remove the one element from the list [1, 2] starting from non-existant element

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    struct SingleLinkedElement *element = NULL;

    // TEST
    _method_SingleLinkedCyclicList_remove_from(&list, element, 1);

    // CHECK
    if (list.head == NULL)
    {
        throw("head can't be NULL in a non-empty list");
        return;
    }
    if (_method_SingleLinkedCyclicList_get_length(&list) != 2)
    {
        throw("length must be equal to 2");
        return;
    }
    if (list.head->data != 1)
    {
        throw("head must remain the same");
        return;
    }
    if (list.head->next->data != 2)
    {
        throw("head->next must remain the same");
        return;
    }
    if (list.head->next->next != list.head)
    {
        throw("head->next->next must point to head");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove_from, 4)
{
    id = 4;
    // ACTION
    // Trying to remove the one element from the list [1, 2] starting from first element

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    struct SingleLinkedElement *element = list.head;

    // TEST
    _method_SingleLinkedCyclicList_remove_from(&list, element, 1);

    // CHECK
    if (list.head == NULL)
    {
        throw("head can't be NULL in a non-empty list");
        return;
    }
    if (_method_SingleLinkedCyclicList_get_length(&list) != 1)
    {
        throw("length must be equal to 1");
        return;
    }
    if (list.head->data != 1)
    {
        throw("head must remain the same");
        return;
    }
    if (list.head->next != list.head)
    {
        throw("head->next must point to head");
        return;
    }
}

void TEST(_method_SingleLinkedCyclicList_remove_from, 5)
{
    id = 5;
    // ACTION
    // Trying to remove the one element from the list [1, 2] starting from first element

    // SETUP
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
    _method_SingleLinkedCyclicList_append(&list, 1);
    _method_SingleLinkedCyclicList_append(&list, 2);
    struct SingleLinkedElement *element = list.head;

    // TEST
    _method_SingleLinkedCyclicList_remove_from(&list, element, 1);

    // CHECK
    if (list.head == NULL)
    {
        throw("head can't be NULL in a non-empty list");
        return;
    }
    if (_method_SingleLinkedCyclicList_get_length(&list) != 1)
    {
        throw("length must be equal to 1");
        return;
    }
    if (list.head->data != 1)
    {
        throw("head must remain the same");
        return;
    }
    if (list.head->next != list.head)
    {
        throw("head->next must point to head");
        return;
    }
}
// END - _method_SingleLinkedCyclicList_remove_from

int main()
{
    printf("START\n");
    printf("_constructor_SingleLinkedCyclicList\n");
    {
        _test_1_constructor_SingleLinkedCyclicList();
    }
    printf("_method_SingleLinkedCyclicList_append\n");
    {
        _test_1_method_SingleLinkedCyclicList_append();
        _test_2_method_SingleLinkedCyclicList_append();
    }
    printf("_method_SingleLinkedCyclicList_get_length\n");
    {
        _test_1_method_SingleLinkedCyclicList_get_length();
        _test_2_method_SingleLinkedCyclicList_get_length();
    }
    printf("_method_SingleLinkedCyclicList_exists\n");
    {
        _test_1_method_SingleLinkedCyclicList_exists();
        _test_2_method_SingleLinkedCyclicList_exists();
        _test_3_method_SingleLinkedCyclicList_exists();
    }
    printf("_method_SingleLinkedCyclicList_remove\n");
    {
        _test_1_method_SingleLinkedCyclicList_remove();
        _test_2_method_SingleLinkedCyclicList_remove();
        _test_3_method_SingleLinkedCyclicList_remove();
        _test_4_method_SingleLinkedCyclicList_remove();
        _test_5_method_SingleLinkedCyclicList_remove();
        _test_6_method_SingleLinkedCyclicList_remove();
    }
    printf("_method_SingleLinkedCyclicList_remove_from\n");
    {
        _test_1_method_SingleLinkedCyclicList_remove_from();
        _test_2_method_SingleLinkedCyclicList_remove_from();
        _test_3_method_SingleLinkedCyclicList_remove_from();
        _test_4_method_SingleLinkedCyclicList_remove_from();
    }
    printf("END");
}