#ifndef LISTNODE_H
#define LISTNODE_H


struct ListNode {
     int val;
      ListNode *next;
      ListNode(int x);
  };

void printList(ListNode *);
#endif // LISTNODE_H
