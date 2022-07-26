### 3.2 implement a sequence interface gievn a set interface
* build(A) runs in expected O(n) time,
* get at and set at each run in expected O(1) time,
* insert at and delete at each run in expected O(n) time, and
* the four dynamic first/last operations each run in amortized expected O(1) time.
- - -
* Set Interface and Sequence Interface
    * Sequence about extrinsic order, set is about intrinsic order
    
    |set operations:|Sequence operations:
    |---|---
    |build(X)| build(X)
    |len()|len()
    |find(k)|get_at(i)
    ||set_at(i)
    |delete(k)| delete_at(i)
    ||delete_first()
    ||delete_last()
    |insert(x)| insert_at(i,x)
    ||insert_first(x)
    ||insert_last(x)
- - -
* Idea 1 : use sequence index as key in set.
* Idea 2 [deprecated] : maintain another set just like dynamic arrays. The trick is to always keep about half the items in both sets. Otherwise you need to deal with when deleting from one set that is already empty(Trying to delete that item in another set takes O(n) time because these two sets are in reverse order).
* Idea 3 : keep additional record of key 'first' of first item, which mapps to sequence index 0.
- - -
__Invariant__ : 
keys = {first, first + 1, ..., first + len() -1}
    
### 3.4 
a. find pairwise sum = k in expected O(n) time. 
* Idea : build hash table.

b. find biggest pairwise sum <= k = 600 $n^6$ in worst-case O(n) time.
* Idea1 : radix sort.
* Idea2 : binary search. But it ends up with worst-case O(nlogn) time.
* Notes: binary search when fails tells not only the key k is no there but also the previous value and the next value. That is , k is in range (right, left)  right < left, which is also the termination condition on for loop.
* Idea3: Two finger algorithm