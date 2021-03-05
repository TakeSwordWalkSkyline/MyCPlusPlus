/* *
 *给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

 *请你将两个数相加，并以相同形式返回一个表示和的链表。

 *你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

 *链接：https://leetcode-cn.com/problems/add-two-numbers
 */
#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *addTwoNums(ListNode *l1, ListNode *l2) {
    ListNode *temp = l1;
    int num1 = 0, num2 = 0;
    for (; temp != NULL; temp = temp->next) {
        num1 ++;
    }
    temp = l2;
    for (; temp != NULL; temp = temp->next) {
        num2 ++;
    }
    int num = (num1 > num2) ? num1 : num2;
    ListNode *head = NULL, *tail = NULL;
    int carry = 0;
    for (int i = 0; i < num; i++) {
        int n1 = (l1 == NULL) ? 0 : l1->val;
        int n2 = (l2 == NULL) ? 0 : l2->val;
        int sum = n1 + n2 + carry;
        if (head == NULL) {
            head = tail = new ListNode(sum % 10);
        } else {
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }
        carry = sum / 10;
        
        l1 = l1->next;
        l2 = l2->next;
    }
    if (carry != 0) {
        tail->next = new ListNode(carry);
    }
    return head;
}

int main() {
    ListNode *l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);
    ListNode *l2 = new ListNode(2);
    l2->next = new ListNode(7);
    l2->next->next = new ListNode(8);
    ListNode *l3 =addTwoNums(l1, l2);
}
