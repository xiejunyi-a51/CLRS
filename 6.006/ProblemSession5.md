### Problem 5-2 Internet Investigation
MIT has heard complaints regarding the speed of their WiFi network. The network consists of $r$ routers, some of which are marked as entry points which are connected to the rest of the internet. Some pairs of routers are directly connected to each other via bidirectional wires. Each wire $w_i$ between two routers has a known length $l_i$ measured in a positive integer number of feet. The latency of a router in the network is proportional to the minimum feet of wire a signal from the router must pass through to reach an entry point. Assume the latency of every router is finite and there is at most $100r$ feet of wire in the entire network. Given a schematic of the network depicting all routers and the lengths of all wires, describe an $\text{O}(r)$-time algorithm to determine the sum total latency, summed over all routers in the network.
**Idea:** SuperNode Tactic
The brain-dead algorithm would be for each *entry point* $e$, compute SSSP to all other routers in the network. Then for each router $r$, update minimum latency to $e$ in each iteraion. The algo would take total time $\text{O}(|\text{entry points}|)\cdot T(SSSP)$.

First we notice even the fastest algo for general positive weighted graph would take $\text{O}(|V|\log|V| +|E|)=\text{O}(r\log r)>\text{O}(r)$. The solution is to transform network into unweighted graph by viewing any $l_i$-feet wire as a cascade of $l_i$ one-foot wires. New graph has number of edges $\sum_{w_i}(l_i) \le 100r$ and number of vertices $r+ \sum_{w_i}(l_i-2) < 101r$. SSSP by bfs on new graph takes only $\text{O}(|V|+|E|)=\text{O}(r)$.

Secondly, by introducing a new supernode "s" along with bidirectional 
edges to each *entry point*, we can do one SSSP instead of SSSP for every *entry point*. Latency for any router is:

$$
\delta^{*}(v) = \min_{e\in {\text{entry points}}}\delta(e,v) = \delta(s,v) - 1.
$$

Total latency is just sum over latency of all routers.

**Proof**
Assume $\delta^{*}(v)=\delta(e^{*},v)$ where $e^{*} \stackrel{p} \leadsto v$. If there exist some shorter latency $\delta^{*}(v)=\delta(e',v)$ where $e' \stackrel{p'} \leadsto v$, we can cut-and-paste $p'$ to replace $p$ and construct shorter path from $s$ to $v$. By proof of contradiction, $p$ is on shortest path from $s$ to $v$.

### Problem 5-3 Quadwizard Quest
Wizard Potry Harter and her three wizard friends have been tasked with searching every room of a Labyrinth for magical artifacts. The Labyrinth consists of $$ rooms, where each room has at most four doors leading to other rooms. Assume all doors begin closed and every room in the Labyrinth is reachable from a specified entry room by traversing doors between rooms. Some doors are protected by evil enchantments that must be disenchanted before they can be opened; but all other doors may be opened freely. Given a map of the Labyrinth marking each door as enchanted or not, describe an $\text{O}(n)$-time algorithm to determine the minimum number of doors that must be disenchanted in order to visit every room of the Labyrinth, beginning from the entry room.

**Idea:** Once an enchanted door is opened, it stays open and not requiring further effort.

**Solution:**
Step 1. Creat a graph $G=(V,E)$. $V$ is the $n$ rooms and $E$ is non-enchanted doors between rooms. Find each connected component $C_i$.

Step 2. Creat a new graph $G^{CC}=(V',E')$. Each $v_i\in V'$ represents a connected component $C_i$ in step 1. $E'=\{(v_i,v_j)|(u,v)\text{ is enchanted door }, v\in C_i, u\in C_j\}$. This step is just for better understanding but not really necessary for the result. $G$ is connected therefore $G^{CC}$ is connected.

Step 3. Minimum number of edges required to visit each vertex $v_i$ once is the number of edges for minimum spanning tree $|V'|-1$.

### Problem 5-4 flight itinerary
Four times BFS from home city and three touring cities respectively should solve the problem.