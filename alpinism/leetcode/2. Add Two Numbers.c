/*

en:
    You are given two non-empty linked lists representing two non-negative integers. 

    The digits are stored in reverse order and each of their nodes contain a single digit. 

    Add the two numbers and return it as a linked list.

    You may assume the two numbers do not contain any leading zero, except the number 0 itself.

    Example:

    Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
    Output: 7 -> 0 -> 8
    Explanation: 342 + 465 = 807.


    Definition for singly-linked list.
    struct ListNode {
      int val;
      struct ListNode *next;
    };

zh-cn:
    给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

    如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

    您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

    示例:
        输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
        输出：7 -> 0 -> 8
        原因：342 + 465 = 807
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ListNode
{
    int val;
    struct ListNode *next;
} __ListNode;

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    int flag = 0;
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode)), *current = head;
    memset(head, 0, sizeof(struct ListNode));
    while (current != NULL)
    {
        l1 = (l1 != NULL) ? (flag += l1->val, l1->next) : NULL;
        l2 = (l2 != NULL) ? (flag += l2->val, l2->next) : NULL;
        current->val = flag % 10;
        flag /= 10;
        current->next = (l1 != NULL || l2 != NULL || flag != 0) ? (struct ListNode *)malloc(sizeof(struct ListNode)) : NULL;
        current = current->next;
    }
    return head;
}
int main(int argc, char **argv)
{
    __ListNode *l1, *l2;
    __ListNode a0, a1, a2, b0, b1, b2;

    a0.val = 2;
    a0.next = &a1;
    a1.val = 4;
    a1.next = &a2;
    a2.val = 3;
    a2.next = NULL;

    b0.val = 5;
    b0.next = &b1;
    b1.val = 6;
    b1.next = &b2;
    b2.val = 4;
    b2.next = NULL;

    l1 = &a0;
    l2 = &b0;
    l1 = addTwoNumbers(l1, l2);
    while (l1 != NULL)
    {
        printf("%d\n", l1->val);
        l1 = l1->next;
    }
    return 0;
}
