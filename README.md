<img width="465" height="40" alt="image" src="https://github.com/user-attachments/assets/1317c781-d72d-4890-aa44-e4d1250c46a5" /># STL Benchmarking
Project designed for personal C++ systems learning.<br/>
<br/>

# Purpose

Investigate the performance characteristics of different C++ STL containers under common workloads such as insertion, lookup, iteration and deletion.<br/>
<br/>

# Learning

The goal is to understand how memory layout, cache locality and algorithmic complexity affect real-world performance.<br/>
<br/>

# Test Memory Allocation Behavior

We first test out with using vectors:<br/>
<br/>
<img width="588" height="265" alt="image" src="https://github.com/user-attachments/assets/771d0da0-aa56-44e9-a8c3-f194376a210d" />  


In the function above, I use `reserve()`.  

`reserve()` pre-allocates memory for a specified amount of elements.<br/>
When I run the project, the time taken for pushing n = 1,000,000 as below:<br/>

<img width="333" height="28" alt="image" src="https://github.com/user-attachments/assets/00dd0720-f0ea-4ba1-a234-81027d6f17d1" /><br/>
<br/>
However when I comment out `reserve()`, note the timing change:  

<img width="331" height="23" alt="image" src="https://github.com/user-attachments/assets/462b1518-b5dc-4015-925e-e5a4839597dc" /><br/>

Without `reserve()`, the vector reallocates and copies multiple times as it grows, causing extra work.<br/>
With `reserve()`, all memory is allocated upfront, so no intermediate copying occurs, resulting in faster insertion.<br/>
<br/>
<img width="365" height="56" alt="image" src="https://github.com/user-attachments/assets/ff1b4eb6-c5a8-43f9-bad4-86b742605752" /><br/>
*Commented out the reserve() line, the vector capacity starts with 0.*<br/>
<br/>
Up to this point, we have only tested with int types, which are **4 bytes in size**.<br/>
So despite the vector having to repeatedly move/copy over data, it is still extremely cheap, hence only a 0.02s delay.<br/>
<br/>

# Test Object Size Impact

Next, I created a `struct Big` with 100 doubles (800 bytes).<br/>
<img width="169" height="73" alt="image" src="https://github.com/user-attachments/assets/c5945d60-be4f-4d7f-9759-4be2ddd829e9" /><br/>
<img width="244" height="26" alt="image" src="https://github.com/user-attachments/assets/839baeac-5103-4e30-82c3-77462662176f" /><br/>
<br/>
We run the program again, this time since the size dramatically increased (by two times), it is no surprise that the program took longer to complete.<br/>
<img width="317" height="21" alt="image" src="https://github.com/user-attachments/assets/45197bde-34ee-4b60-9fad-2e99d6643eab" /><br/>
<br/>
However, that was without reserve(). What if we used reserve()? Upon running again, it seems like there is a 0.01s difference:<br/>
<img width="320" height="21" alt="image" src="https://github.com/user-attachments/assets/feba918f-0770-4f37-af65-1228fab10341" /><br/>
<br/>
**Conclusion:** <br/>
- Larger objects increase the cost of copying during reallocation.<br/>
- Using `reserve()` mitigates repeated allocations and copies.<br/>
- The performance difference is visible but smaller than the size increase, showing the vector still benefits from contiguous memory and cache locality.<br/>
<br/>

# Benchmark Sequential Containers

I then compared `vector`, `deque`, and `list` for iteration and insertion performance.<br/>
<img width="261" height="244" alt="image" src="https://github.com/user-attachments/assets/a29ea4e0-9f1f-49f2-bee2-a78ff3f006ba" /><br/>
<br/>
The timings of each container:<br/>
<img width="339" height="67" alt="image" src="https://github.com/user-attachments/assets/16a00c86-07f8-475e-beb9-b378ea45a679" /><br/>
<br/>
Vector seems to be the fastest among the three. To understand why this is the case, **we must understand each of the three:** <br/>
- `vector` stores elements contiguously → fastest iteration due to cache locality.<br/>
- `list` uses scattered nodes → slower due to pointer chasing and cache misses.<br/>
- `deque` uses small contiguous blocks → iteration is faster than `list` but slightly slower than `vector` due to segmented memory layout.<br/>
<br/>

# Random Access Time

We measured the time it takes to perform n = 10,000 random accesses in vector, deque, and list.<br/>
Each access performed a trivial sum operation to prevent the compiler from optimizing the loop away.<br/>
<br/>
<img width="410" height="61" alt="image" src="https://github.com/user-attachments/assets/28255380-6099-48b1-8779-a49e7b768b1a" /><br/>
<br/>
As we can see from the picture above, the list is clearly inefficient when it comes to accessing random indexes, as it is built for searching in sequence (forward -> backwards or vice versa).<br/>
<br/>
- vector stores elements contiguously → O(1) random access → cache-friendly<br/>
- deque stores elements in blocks → still O(1) access but slightly less cache-friendly<br/>
- list is a linked list → O(n) access per element → pointer chasing → many cache misses<br/>
<br/>

**Conclusion:** Lists are inefficient for random access due to pointer chasing and cache misses. Vectors remain optimal for this workload.<br/>
<br/>

# Associative Containers

Now we compare two associative containers: `map` and `unordered_map`.<br/>
Both store key → value pairs, but they are implemented using very different data structures.<br/>
When inserting n = 1,000,000 elements:<br/>
<img width="383" height="41" alt="image" src="https://github.com/user-attachments/assets/d95e1f12-7911-408e-92a1-b8f169ef282e" /><br/>
<br/>
<br/>
`map` took roughly twice as long compared to `unordered_map`.<br/>
This difference comes from how the containers are implemented internally.<br/>
- `map` is implemented using a **Red-Black Tree**.<br/>
  The elements are **always kept sorted**, so lookups, insertions or deletions require traversal → **O(log n) time complexity**.<br/>
- `unordered_map` is implemented using a **Hash Table**.<br/>
  Instead of maintaining sorted order, it computes a hash of the key and places the element into a bucket in memory → **O(1) time complexity** for insert, lookup and erase.<br/>
<br/>

# Scaling the experiment

To observe the scaling behaviour, I increased the dataset size to **n = 10000000**:<br/>
<img width="374" height="38" alt="image" src="https://github.com/user-attachments/assets/f3019ebb-9604-4abd-b0d5-afbd7fed8abd" /><br/>
<br/>
The runtime increased significantly, which is expected because the containers now manage a much larger number of elements.<br/>
<br/>

# Memory access behavior

The memory layout of the containers also affects performance.<br/>
For visual reference, this is what happens while accessing the memory in `map`: <br/>

**node -> pointer -> pointer -> pointer** <br/>

Each element is stored as a separate tree node containing several pointers.<br/>
This leads to:<br/>
- pointer chasing<br/>
- scattered memory access<br/>
- high probabilty of cache misses<br/>
<br/>

And likewise this happens while accessing memory in `unordered_map`: <br/>

**[Bucket][Bucket][Bucket][Bucket]** <br/>

The hash of the key determines which bucket to access.<br/>
This results in:<br/>
- fewer pointer traversals<br/>
- fewer memory jumps<br/>
- generally better cache behavior<br/>
<br/>
Although `unordered_map` is often faster for basic operations, `map` still provides useful properties.<br/>
- Its elements are sorted <br/>
- It can do range queries <br/>
- It can iterate in order <br/>
<br/>
Functions such as `lower_bound()` and `upper_bound()` make `map` useful for problems that require ordered traversal, but we will get into that another time.<br/>
<br/>
The next operation we are doing is looking up a random element in both `map` and `unordered_map`. When n = 1000000:<br/>
<img width="464" height="42" alt="image" src="https://github.com/user-attachments/assets/ffe5771a-97a1-4597-ac84-26fbee4c5772" /><br/>
<br/>
The timing pattern is similar to the insertion benchmark.<br/>
This is expected because both operations **require searching the underlying data structure**:<br/>
<br/>
Finally, we measured the time required to **erase elements**:<br/>
<img width="402" height="42" alt="image" src="https://github.com/user-attachments/assets/0aaddf3e-e5e5-42d6-8bc0-bc204192baf9" /><br/>
<br/>
The results follow the same pattern as the previous benchmarks.<br/>
The reasons are the same as the previous two operations:<br/>
- map erase            = O(log n) tree traversal + rebalance <br/>
- unordered_map erase  = O(1) bucket removal <br/>
Deleting an element from `map` requires locating the node in the tree and performing potential rebalancing operations, whereas `unordered_map` typically removes the element directly from its bucket.<br/>
<br/>
