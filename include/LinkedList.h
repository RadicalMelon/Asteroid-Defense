#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*=================================================================================*/

#include "../Globals.h"

/*=================================================================================*/

typedef struct ListNode
{
    void* value;
    struct ListNode* next;
} ListNode;

/*=================================================================================*/

ListNode* CreateListNode(ListNode* root_node, void* value);
int GetLinkedListLength(ListNode* root_node);
void* GetListNodeValue(ListNode* root_node, int position);
void RemoveListNode(ListNode** root_node, int position);
void DestroyLinkedList(ListNode* root_node);

/*=================================================================================*/

#endif // LINKEDLIST_H
