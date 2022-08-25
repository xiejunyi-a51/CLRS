### Problem 4-2
Fick Nury directs an elite group of n superheroes called the Revengers. He has heard that supervillian Sanos is making trouble on a distant planet and needs to decide whether to confront her. Fick surveys the Revengers and compiles a list of n polls, where each poll is a tuple matching a different Revenger’s name with their integer opinion on the topic. Opinion +s means they are for confronting Sanos with strength s, while opinion −s means they are against confronting Sanos with strength s. Fick wants to generate a list containing the names of the log n Revengers having the strongest opinions (breaking ties arbitrarily), so he can meet with them to discuss. For this problem, assume that the record containing the polls is read-only access controlled (the material in classified), so any computation must be written to alternative memory.
(a) Describe an $\text{O}(n)$-time algorithm to generate Fick’s list.
(b) Now suppose Fick’s computer is only allowed to write to at most $\text{O}(\log{n})$ space. Describe an $\text{O}(n\log\log{n})$-time algorithm to generate Fick’s list.

**Solution**
(a) stick n revengers with the abs of their integer opinions in a max heap. Pop maximum items out $log \ n$ times.
Time = $\text{O}(n)+\log{n}*\text{O}(\log n)=\text{O}(n)$.
(b) stick log n revengers with abs value of integer opinions in a set AVL tree, which takes O($\log n*\log\log n$) time. For each of rest $n-\log n$ items, put them in tree and replace out minimum one.
Time = $\text{O}(\log{n}*\log\log{n}) + \text{O}(n)*\text{O}(\log\log{n})=\text{O}(n\log\log{n})$.

**Idea**
For more generalized problem, should we use heap or is AVL tree enough for our purpose? 
-- Suppose we build a heap of size k < n. It takes $\text{O}(k+(n-k)\log{k})$ to get biggest k items in n ones. And for AVL tree, it takes $\text{O}(k\log{k}+(n-k)\log{k})$. Therefore for any k < n, using a heap does not reduce time asymptotically.

### Problem 4-4. Receiver Roster
Coach Bell E. Check is trying to figure out which of her football receivers to put in her starting lineup. In each game, Coach Bell wants to start the receivers who have the highest performance (the average number of points made in the games they have played), but has been having trouble because her data is incomplete, though interns do often add or correct data from old and new games. Each receiver is identified with a unique positive integer jersey number, and each game is identified with a unique integer time. Describe a database supporting the following operations, each in worst-case $\text{O}(\log{n})$ time, where n is the number of games in the database at the time of the operation. Assume that n is always larger than the number of receivers on the team.
record(g, r, p) clear(g, r)
ranked receiver(k)
record p points for jersey r in game g
remove any record that jersey r played in game g return the jersey with the kth highest performance

**Idea**
Cross-Linking: using one set AVL tree/hashMap keyed on ids for searching ids and another set AVL tree/hashMap keyed on other properties for getting kth largest item efficiently.


