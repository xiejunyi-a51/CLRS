### 10.3-3
```C++
allocateObject():
    if not free:
        error "out of space"
    else
        x = free
        free = A[free+1]
        return x

freeObject(x):
    A[x+1] = free
    free = x

list_insert(x):
    object = allocateObject()
    A[object] = x
    A[object+1] = L
    A[L+2] = object
    L = object

list_search(k):
    i = 1
    while i <= len(A):
        if k == A[i]:
            return i
        i = i + 3
    return -1
    
list_delete(x):
    L = A[x+2]
    freeObject(x)
```
