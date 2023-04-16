/*10.2-7
Give a Θ(n)-time nonrecursive procedure that reverses a singly linked list of
n elements. The procedure should use no more than constant storage beyond that needed
for the list itself.
*/

#include <iostream>
#include <memory>
#include <array>
#include <forward_list>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
using T = ListNode;
ListNode *reverseList(ListNode *head)
{
    T *p1{nullptr};
    T *p2{head};
    while (p2)
    {
        T *p3{p2->next};
        p2->next = p1;
        p1 = p2;
        p2 = p3;
    }
    head = p1;
    return head;
}

void print(T *head)
{
    while (head)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}
int main()
{
    const int L = 10;
    array<T, L> input{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < L - 1; i++)
    {
        input.at(i).next = &(input.at(i + 1));
    }
    input.at(L - 1).next = nullptr;
    T *head = &(input.at(0));
    T *newHead = reverseList(head);
    print(newHead);
}