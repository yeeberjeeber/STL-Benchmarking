# STLBenchmarking
Project designed for personal C++ systems learning

# Purpose

What I am trying to do here is to check and compare against each data structure, to see the time / space used.

# Learning

First I am testing out with using vectors:

<img width="588" height="265" alt="image" src="https://github.com/user-attachments/assets/771d0da0-aa56-44e9-a8c3-f194376a210d" />

In the function above, I use reserve(). The purpose of reserve() is that it pre-allocates memory for a specified amount of elements.
When I run the project, the time taken for pushing a million numbers as below:
<img width="333" height="28" alt="image" src="https://github.com/user-attachments/assets/00dd0720-f0ea-4ba1-a234-81027d6f17d1" />

However when I comment out reserve(), note the timing change:
<img width="331" height="23" alt="image" src="https://github.com/user-attachments/assets/462b1518-b5dc-4015-925e-e5a4839597dc" />
