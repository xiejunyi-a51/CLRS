It is often desirable to keep all elements of a doubly linked list compact in storage, using, for example, the first $m$ index locations in the multiple-array representation. (This is the case in a paged, virtual-memory computing environment.) Explain how to implement the procedures ALLOCATE-OBJECT and FREE-OBJECT so that the representation is compact. Assume that there are no pointers to elements of the linked list outside the list itself. (Hint: Use the array implementation of a stack.)
**Solution:**
The idea is if everytime we can move the object to be freed to the last of occupied first $m$ slots, then the representation will remain compact. Since the last freed object is always in the leftmost slot of free lists, allocate_object() won't compromise the compactness and its behavior doesn't need to change.

```C++
allocateObject():
    if not free:
        error "out of space"
        return nullptr
    x = free
    free = next[free]
    return x
swapListNode(x, y):
    swap(next[prev[y]], next[prev[x]])
    swap(prev[y], prev[x])
    swap(prev[next[y]], prev[next[x]])
    swap(next[y], next[x])

freeObject(x):
    y = free - 1
    swapListNode(x, y)
    next[prev[y]] = next[y]
    prev[next[y]] = prev[y]
    next[y] = free
    free = y
```