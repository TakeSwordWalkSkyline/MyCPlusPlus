//哈希法判断链表是否有环
//遍历所有节点并且判断该节点是否被访问过
//使用哈希表来记录已经访问过的节点，每次达到一个节点的时候，如果该节点被访问过那么则链表有环否则没有


#include <iostream>
#include <unordered_set>
using std::unordered_set;

struct Node {
    int data;
    Node *next;
};

bool hasCircles(Node *head) {
    unordered_set<Node*> hash_table;
    while (head != NULL) {
        if (hash_table.count(head)) {
            return true;
        } else {
            hash_table.insert(head);
            head = head->next;
        }
    }
    return false;
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

    bool has_circle = hasCircles(&head);
    std::cout << "has circle:" << has_circle << std::endl;
}
