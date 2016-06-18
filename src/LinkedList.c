#include "LinkedList.h"

/*=================================================================================*/

ListNode* CreateListNode(ListNode* root_node, void* value)
{
    ListNode* new_node = malloc(sizeof(ListNode));
    new_node->value = value;
    new_node->next = NULL;

    if (root_node != NULL)
    {
        ListNode* current_node = root_node;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }

    return new_node;
}

/*=================================================================================*/

int GetLinkedListLength(ListNode* root_node)
{
    if (root_node == NULL) return 0;
    int length = 1;
    ListNode* current_node = root_node;
    while (current_node->next != NULL)
    {
        current_node = current_node->next;
        length++;
    }
    return length;
}

/*=================================================================================*/

void* GetListNodeValue(ListNode* root_node, int position)
{
    ListNode* current_node = root_node;
    for (int i = 0; i < position; i++)
    {
        current_node = current_node->next;
    }
    return current_node->value;
}

/*=================================================================================*/

void RemoveListNode(ListNode** root_node, int position)
{
    if (position == 0)
    {
        ListNode* temporary = *root_node;
        *root_node = temporary->next;
        free(temporary);
    }
    else
    {
        ListNode* before_node = NULL;
        ListNode* after_node = NULL;
        ListNode* current_node = *root_node;

        for (int i = 0; i < position; i++)
        {
            before_node = current_node;
            current_node = current_node->next;
            after_node = current_node->next;
        }

        free(current_node);
        before_node->next = after_node;
    }
}

/*=================================================================================*/

void DestroyLinkedList(ListNode* root_node)
{
    ListNode* temporary;
    while (root_node != NULL)
    {
        temporary = root_node;
        root_node = root_node->next;
        free(temporary);
    }
}
