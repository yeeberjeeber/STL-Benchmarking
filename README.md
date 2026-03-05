# STL Benchmarking
Project designed for personal C++ systems learning

# Purpose

Investigate the performance characteristics of different C++ STL containers under common workloads such as insertion, lookup, iteration and deletion.

# Learning

The goal is to understand how memory layout, cache locality and algorithmic complexity affect real-world performance.

# Test Memory Allocation Behavior

We first test out with using vectors:<br/>
<br/>
<img width="588" height="265" alt="image" src="https://github.com/user-attachments/assets/771d0da0-aa56-44e9-a8c3-f194376a210d" />  


In the function above, I use `reserve()`.  

`reserve()` pre-allocates memory for a specified amount of elements.<br/>
When I run the project, the time taken for pushing a million elements as below:<br/>

<img width="333" height="28" alt="image" src="https://github.com/user-attachments/assets/00dd0720-f0ea-4ba1-a234-81027d6f17d1" /><br/>
<br/>
However when I comment out `reserve()`, note the timing change:  

<img width="331" height="23" alt="image" src="https://github.com/user-attachments/assets/462b1518-b5dc-4015-925e-e5a4839597dc" /><br/>
<br/>

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
<br/>
<img width="485" height="13" alt="image" src="https://github.com/user-attachments/assets/83002a6a-da8e-44b4-b65f-aecc4edd04dd" /><br/>
<img width="244" height="26" alt="image" src="https://github.com/user-attachments/assets/839baeac-5103-4e30-82c3-77462662176f" /><br/>
<br/>
We run the program again, this time since the size dramatically increased (by two times), it is no surprise that the program took longer to complete.<br/>
<img width="317" height="21" alt="image" src="https://github.com/user-attachments/assets/45197bde-34ee-4b60-9fad-2e99d6643eab" /><br/>
<br/>
However, that was without reserve(). What if we used reserve()? Upon running again, it seems like there is a 0.01s difference:<br/>
<img width="320" height="21" alt="image" src="https://github.com/user-attachments/assets/feba918f-0770-4f37-af65-1228fab10341" /><br/>
<br/>
Conclusion:<br/>
<br/>
- Larger objects increase the cost of copying during reallocation.<br/>
- Using `reserve()` mitigates repeated allocations and copies.<br/>
- The performance difference is visible but smaller than the size increase, showing the vector still benefits from contiguous memory and cache locality.<br/>

# Benchmark Sequential Containers

By this point we have tested mainly against vectors. Let us explore the timings on other sequential containers such as deque and list:<br/>
<img width="261" height="244" alt="image" src="https://github.com/user-attachments/assets/a29ea4e0-9f1f-49f2-bee2-a78ff3f006ba" /><br/>
<br/>
The timings of each container:<br/>
<img width="339" height="67" alt="image" src="https://github.com/user-attachments/assets/16a00c86-07f8-475e-beb9-b378ea45a679" /><br/>
<br/>
Vector seems to be the fastest among the three. To understand why this is the case, we must understand each of the three:<br/>
<br/>
1. A vector is a dynamic array, where it can shrink and grow based on the number of elements stored in it at runtime. It stores elements in contiguous memory, meaning that they are next to each other in memory.<br/>
2. A list uses linked nodes that point to each other and is doubly linked, meaning it can go forward and backward in sequence. Its nodes are scattered in the memory, causing pointer chasing, hence the longer time that you see above.<br/>
3. A deque can insert and remove from both ends compared to the traditional queue (push from the back, pop from the front). In memory, it is a little mix of both the vector and the list, where it has chunks of contiguous memory, yet these chunks are scattered.<br/>
<br/>

# Random Access time

We measured the time it takes to perform n = 10,000 random accesses in vector, deque, and list. Each access performed a trivial sum operation to prevent the compiler from optimizing the loop away.<br/>
<img width="410" height="61" alt="image" src="https://github.com/user-attachments/assets/28255380-6099-48b1-8779-a49e7b768b1a" /><br/>
<br/>
As we can see from the picture above, the list is clearly inefficient when it comes to accessing random indexes, as it is built for searching in sequence (forward -> backwards or vice versa).<br/>
<br/>
- vector stores elements contiguously → O(1) random access → cache-friendly<br/>
- deque stores elements in blocks → still O(1) access but slightly less cache-friendly<br/>
- list is a linked list → O(n) access per element → pointer chasing → many cache misses<br/>
<br/>
Conclusion: The poor performance of list is partly due to pointer chasing: each node may live anywhere in memory, causing many cache misses. In contrast, vector benefits from contiguous memory, which keeps elements in cache lines.<br/>
<br/>
