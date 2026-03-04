# STLBenchmarking
Project designed for personal C++ systems learning

# Purpose

What I am trying to do here is to check and compare against each data structure, to see the time / space used.

# Learning

First I am testing out with using vectors:<br/>
<br/>
<img width="588" height="265" alt="image" src="https://github.com/user-attachments/assets/771d0da0-aa56-44e9-a8c3-f194376a210d" />  


In the function above, I use reserve().  

The purpose of reserve() is that it pre-allocates memory for a specified amount of elements.
When I run the project, the time taken for pushing a million elements as below:  

<img width="333" height="28" alt="image" src="https://github.com/user-attachments/assets/00dd0720-f0ea-4ba1-a234-81027d6f17d1" /><br/>
<br/>
However when I comment out reserve(), note the timing change:  

<img width="331" height="23" alt="image" src="https://github.com/user-attachments/assets/462b1518-b5dc-4015-925e-e5a4839597dc" /><br/>
<br/>

Hence when I do not use reserve():  
1. The vector starts small.  
2. Each time the vector runs out of capacity, it allocates a bigger block of memory.  
3. Then it copies or moves all existing elements into the new block.  
4. The old memory is freed.  
5. Steps 1 - 4 will happen multiple times, causing extra work and hence the delay.
<br/>
<img width="365" height="56" alt="image" src="https://github.com/user-attachments/assets/ff1b4eb6-c5a8-43f9-bad4-86b742605752" /><br/>
_Commented out the reserve() line, the vector capacity starts with 0._
