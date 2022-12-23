/* 12.1-3 Give a nonrecursive algorithm that performs an inorder tree walk.
(Hint: An easy solution uses a stack as an auxiliary data structure. A more complicated,
but elegant, solution uses no stack but assumes that we can test two pointers for equality.)
*/

#include <iostream>
#include <vector>

using namespace std;
using KeyType = int;
using State = uint8_t;
struct Node
{
    Node *left;
    Node *right;
    Node *parent;
    KeyType key;
    State state{0};
};

vector<Node *> stack;
void inorder_traverse(Node *subtree)
{
    auto &x = subtree;
    while (x or not stack.empty())
    {
        if (x)
        {
            stack.push_back(x);
            x = x->left;
        }
        else
        {
            x = stack.back();
            stack.pop_back();
            cout << x->key << " \n";
            x = x->right;
        }
    }
}

void inorder_traverse2(Node *subtree)
{
    auto &x = subtree;
    while (x)
    {
        if (0 == x->state)
        {
            x->state++;
            if (x->left)
            {
                x = x->left;
                continue;
            }
        }
        if (1 == x->state)
        {
            cout << x->key << " \n";
            x->state++;
            if (x->right)
            {
                x = x->right;
                continue;
            }
        }
        if (2 == x->state)
        {
            x = x->parent;
        }
    }
}

int main()
{
    return 0;
}