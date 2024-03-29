# Linear Sorting 
* In comparison model, we can get best worst-case O($n\log n$) time for sorting. But by leveraging direct access, we can achieve linear time sorting algorithm.
* direct access array sort
    * assume input are distinct  integers, and in small range -- the space of keys $u$ is on the order of $n$.
* counting sort
    * alllow repeated input, but still requires them bounded by small range.
    * T = O($n+u$)
* tuple sort
    * do counting sort on each digit, starting at least significant. Because if suffixes are in sorted order, any two keys with same prefix will remain sorted after stable sorting on prefix.
* radix sort
    * base n representation of k = a*n+b --> ab
    * assume input size n, space of keys of size $u$ is smaller than $n^c$. Then base n representation of any input has less than or equal to c digits, and each digit is in range 0 to $n-1$. Do counting sort on each digit starting at the least significant. Counting sort on each digit takes O(n) time. Total radix sort time T = n + n $\times \log_nu$ = O(n).
    * Tuple Sort vs. Radix Sort: radix sort effectively at a single call to counting sort does a whole bunch of $\log n$ digits in original representation. In other words radix sort reduces each number to its log base n shorter version, ergo less passes of counting sort. 
