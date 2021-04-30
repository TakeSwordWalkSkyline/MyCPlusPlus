//1.快慢指针检测单链表是否有环
//2.查找入环点
#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

bool hasCircles(Node *head, Node *&circleNode) {
    Node *fast, *slow;
    fast = slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            circleNode = slow;
            return true;
        }
    }
    return false;
}

Node *findLoopPorts(Node *head) {
    if (head == NULL || head->next == NULL) return NULL;

    Node *fast, *slow;
    fast = slow = head;

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            break;
        }
    }

    if (fast != slow) return NULL;

    fast = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

int main() {
    Node head;
    head.data = 0;

    Node n1;
    n1.data = 1;
    head.next = &n1;

    Node n2;
    n2.data = 2;
    n1.next = &n2;

    Node n3;
    n3.data = 3;
    n2.next = &n3;

    Node n4;
    n4.data =4;
    n3.next = &n4;

    Node n5;
    n5.data= 5;
    n4.next = &n5;

    Node n6;
    n6.data = 6;
    n5.next = &n6;
    n6.next = &n3; //入环点

    Node *meet_node;
    bool has_circle = hasCircles(&head, meet_node);
    cout << "has circle:" << has_circle << " meet node:" << meet_node->data << endl;

    Node *entrance = findLoopPorts(&head);
    cout << "loop entrance: " << entrance->data << endl;

    return 0;
}
