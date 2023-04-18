While moving objects in $L$ into the first $m$ locations in multi-array $A$, it's inevitable to compromise the integrity of free list $F$ because $F$ is singly linked. So we need to reconstruct $F$ in the end.
```C++
swapListNode(x, y):
    swap(next[prev[y]], next[prev[x]])
    swap(prev[y], prev[x])
    swap(prev[next[y]], prev[next[x]])
    swap(next[y], next[x])

compactifyList(L,F):
    i = 1
    j = L
    while j:
        swapListNode(i, j)
        j = next[i]
        i = i + 1
    for k = i to n - 1:
        next[k] = k + 1
    F = i
```