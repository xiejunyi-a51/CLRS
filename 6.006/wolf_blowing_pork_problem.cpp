/*

Given a sequence A, for each A_i, count how many things to the right is smaller than A_i in O(nlogn) time.

Algorithm 

1. divide A into monotonically increasing contiguous subarrays
2. take every two subarray until there is only one or no more subarray left
    a. Let index i and j point to the first elements of left subarray L and right subarray R respectively
    b. for everything in R, since nothing to the right is smaller, write down 1 for them
    c. move j to the right one by one until L[j] is greater than or equal to R[i]
       write down number of steps moved of j -- b , associate it with element A[i]
       move i one step to the right
       repeat (b.) until i points to one-past-the-end of L
    d. now that each item in L and R knows how many things on the right-hand-side are smaller, merge L and R into one monotonically increasing subarray
3. each time (2.) is carried out, the number of monotonicallt increasing subarrays are reduced to half(+1).
   repeat (2.) until A[i] > A[i-1] for all i, with one modification:
   for each element in L, not write down but add to the auxiliary value b

*/