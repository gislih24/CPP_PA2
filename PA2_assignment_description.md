
# PA2 - Data Structures
You have to **re-register into Groups**, again max 3 students per group. Due to an excessive number of solo submissions last time we have little choice but to have a **minimum number of two students per group** unless you are exempted directly by the teacher.

**This is the <u>last</u> assignment with limitations on what can be used. We are still only working in C++98. Do not use C++03 or higher.**
You can **NOT** use any STL data structure, e.g. `std::vector`, `std::set`, `std::list`, etc.
You can include `#include <cassert>`, `#include <cstring>`, `#include <cstdio>` and use `strlen()`, `strcat()`, `strcpy()`, `atoi()`, `atof()`, `memcpy()`, `assert()`. Perhaps there are some more you can use, but you don’t really *need* any specific helper functions that you can’t just write yourselves for this project. You may ask if you want to include something else, but the answer is decently likely to be no.

*Students are meant to practice using pointers and arrays directly.*

## Handing in
- Hand in a single ZIP, including:
    - All code files (.cpp and .h)
        - Header files declaring the data structures and if templated also defining them.
	        - <font color="#00b0f0">Gísli note: Þurfum að gera þetta!</font>
        - Code files for each data structure if they are not templated.
        - Code files for simple programs that test your data structures, one for each data structure. You are allowed to make more than one per data structure.
    - Additional files and/or scripts needed to run your code that tests each of your implemented data structures. Use a **Makefile!**
    - `README.md` (or `README.txt`) in which is:
        - What abstract data structures you implemented, and a general summary of how they are implemented. For example, specify the growth factor of your dynamically sized array, specify what kind of self-balancing binary search tree you used, and mention any data structures you used to implement other data structures. Imagine that you are documenting your library enough that other programmers can use it.
        - What needs to be written in the terminal to compile and run the program. If you provide additional files for the tests, then clarify that and say how to run and verify that the tests ran correctly.
        - Anything else a student wishes to say. Put it here and **not in the Canvas comments**!
- This assignment will focus on <u>manual memory management</u>.
	- In C++, this mostly comes up in the implementations of data structures, which we can then use to avoid manual memory management.
	- Your task is to implement data structures generally found within standard libraries of programming languages.
	- There are many to choose from, and you are *not* required to implement all of them for a full grade.
	- Your implementations should either be specialisations for integers, or for an added bonus you can template them to support all types.
- (What we’re allowed to do:)
	- You are <font color="#ff0000">not</font> allowed to use built-in data structures; you must manage the memory yourselves.
	- You are allowed to use your previously implemented data structures for some of the other data structures.
	- You **should** test your data structures properly and use the **compiler** flags, **`gdb`**, and **`valgrind`** to assist you in debugging.
	- You will be able to submit your data structures for testing on Kattis, which will inform you whether you get incorrect results or whether you have memory leaks. Link: [RU Kattis Links to an external site.](https://ru.kattis.com/courses/T-403-FORC/FORC2026/assignments/aaohpd "Link")
- (Deduction info:)
	- If a program using your data structure gets **incorrect results**, then you should expect **major deductions**.
	- If your data structures have **worse-than-expected time complexities**, then you should expect **major deductions**.
	- If a program using your data structure has memory issues (leaks, accessing unowned memory, etc.) that **DO result in the program crashing**, you should expect **major deductions**.
	- If a program using your data structure has memory issues (leaks, accessing unowned memory, etc.) that **DO NOT result in the program crashing**, you should expect **minor deductions**.
	- If your data structures have correct time complexities, but do **an excessive amount of unnecessary work**, then you should expect **minor deductions**.

You **should** document time complexities and exceptional cases for each operation of each data structure. You can either do this in the README or by adding a comment above the function **declaration!**

**There are 120 base points available, and scoring 100 gives you a 10.
***There are additionally 10 points available for templating your data structures.***

## What to do
1. Implement a <u>dynamically sized array</u>. This is the built-in list data structure in Python or the vector data structure in C++. (20 points)
    - Here you can template the data type stored in the dynamically sized array.
    - You must implement:
	    - the default constructor,
	    - copy constructor,
	    - `push_back`,
	    - `pop_back`,
	    - `insert`,
	    - `erase`,
	    - `operator[]`,
	    - `operator=`,
	    - `resize`,
	    - and `reserve` methods.
    - Statement on Kattis as PDF: [dynamicallysizedarray.pdf](https://reykjavik.instructure.com/courses/10032/files/2546644?wrap=1 "dynamicallysizedarray.pdf") [Download dynamicallysizedarray.pdf](https://reykjavik.instructure.com/courses/10032/files/2546644/download?download_frd=1)
    - Template for reading input: [template.cpp](https://reykjavik.instructure.com/courses/10032/files/2546645?wrap=1 "template.cpp") [Download template.cpp](https://reykjavik.instructure.com/courses/10032/files/2546645/download?download_frd=1)
2. Implement a <u>linked-list</u> data structure. This is the built-in list data structure in C++. (20 points)
	- If you implement a singly linked list, you get a maximum of 10 points; it is intended to be doubly linked, so it can support all the operations efficiently.
    - Here you can template the data type stored in the linked list nodes.
    - You must implement:
	    - the default constructor,
	    - copy constructor,
	    - assignment (`operator=`),
	    - `front`,
	    - `back`,
	    - `insert`,
	    - `erase`,
	    - `size`,
	    - `successor`,
	    - and `predecessor`.
    - Statement on Kattis as PDF: [doublylinkedlist.pdf](https://reykjavik.instructure.com/courses/10032/files/2546641?wrap=1 "doublylinkedlist.pdf") [Download doublylinkedlist.pdf](https://reykjavik.instructure.com/courses/10032/files/2546641/download?download_frd=1)
    - Template for reading input: [kattis_dll_template.cpp](https://reykjavik.instructure.com/courses/10032/files/2546643?wrap=1 "kattis_dll_template.cpp") [Download kattis_dll_template.cpp](https://reykjavik.instructure.com/courses/10032/files/2546643/download?download_frd=1)
3. Implement a <u>queue</u>, <u>stack</u>, **OR** <u>double-ended queue</u> data structure. These are the built-in stack, queue, and deque data structures in C++. (15 points)
    - Here you can template the data type stored in data structures. 
    - If you implement either a queue, a stack, or both, you get a maximum of 10 points.
    - For queue and stack you must implement the default constructor, copy constructor, assignment (`operator=`), push, pop, size and access to the front/top element.
    - If you implement a double-ended queue, *you can get the full 15 points*.
    - For deque, you must implement:
	    - the default constructor,
	    - copy constructor,
	    - assignment (`operator=`),
	    - `push_front`,
	    - `push_back`,
	    - `pop_front`,
	    - `pop_back`,
	    - element access at the front,
	    - element access at the back,
	    - and `size`.
    - Statements on Kattis as PDFs:
        - [stack2.pdf](https://reykjavik.instructure.com/courses/10032/files/2546647?wrap=1 "stack2.pdf") [Download stack2.pdf](https://reykjavik.instructure.com/courses/10032/files/2546647/download?download_frd=1)
        - [queue2.pdf](https://reykjavik.instructure.com/courses/10032/files/2546648?wrap=1 "queue2.pdf") [Download queue2.pdf](https://reykjavik.instructure.com/courses/10032/files/2546648/download?download_frd=1)
        - [deque.pdf](https://reykjavik.instructure.com/courses/10032/files/2546649?wrap=1 "deque.pdf") [Download deque.pdf](https://reykjavik.instructure.com/courses/10032/files/2546649/download?download_frd=1)
4. Implement a <u>heap</u> data structure. This is the built-in `priority_queue` data structure in C++. (15 points)
    - Here, you can template the data type stored in the heap.
    - You can also use templates to support a custom comparator function that determines the ordering of items.
    - You must implement:
	    - the default constructor,
	    - copy constructor,
	    - assignment (`operator=`),
	    - `push`,
	    - `pop`, (`pop` should return the minimum element.)
	    - `size`,
	    - and element access to the top element.
    - Statement on Kattis as PDF: [heap2.pdf](https://reykjavik.instructure.com/courses/10032/files/2546642?wrap=1 "heap2.pdf") [Download heap2.pdf](https://reykjavik.instructure.com/courses/10032/files/2546642/download?download_frd=1)
5. Implement a <u>hash table</u> structure with key-value pairs. This is the built-in dict in Python or `unordered_map` data structure in C++. (20 points)
    - If your hash table does not support hash collisions in some way, or if you implement a bloom filter, then you can get a maximum of 10 points.
    - If your hash table only supports keys, but not values, then you will be deducted a few points.
    - Here you can template the key type used in the hash table.
    - You can also template the value type used in the hash table.
    - You can even template the hash function provided to allow the user of the library to specify their own hash for their key type of choice.
    - You must implement:
	    - the default constructor,
	    - copy constructor,
	    - assignment (`operator=`),
	    - `insert`,
	    - `find`,
	    - `erase`,
	    - `operator[]`,
	    - `size`.
    - Statement on Kattis as PDF: [hashtable2.pdf](https://reykjavik.instructure.com/courses/10032/files/2546646?wrap=1 "hashtable2.pdf") [Download hashtable2.pdf](https://reykjavik.instructure.com/courses/10032/files/2546646/download?download_frd=1)
6. Implement a <u>self-balancing binary search tree</u> structure with key-value pairs. This is the built-in map data structure in C++. (30 points)
    - If you implement a data structure that represents a binary tree, but not a binary search tree, you get a maximum of 5 points.
    - If you implement a data structure that represents a binary search tree which does not self-balance then you get a maximum of 15 points.
    - If your binary search tree only supports keys, but not values, then you will be deducted a few points. 
    - Here you can template the key type used in the hash table.
    - You can also template the value type used in the hash table.
    - You can even template the comparator function provided to allow the user of the library to specify their own ordering of keys.
    - You must implement:
	    - the default constructor,
	    - copy constructor,
	    - assignment (`operator=`),
	    - `insert`,
	    - `find`,
	    - `erase`,
	    - `operator[]`,
	    - `size`,
	    - `successor`,
	    - `predecessor`,
	    - `rank`,
	    - `kth_element`,
	    - `lower_bound`,
	    - and `upper_bound`.
    - Statement on Kattis as PDF: [selfbalancingbst.pdf](https://reykjavik.instructure.com/courses/10032/files/2546650?wrap=1 "selfbalancingbst.pdf") [Download selfbalancingbst.pdf](https://reykjavik.instructure.com/courses/10032/files/2546650/download?download_frd=1)
    - Template for input: [bst_template.cpp](https://reykjavik.instructure.com/courses/10032/files/2546651?wrap=1 "bst_template.cpp") [Download bst_template.cpp](https://reykjavik.instructure.com/courses/10032/files/2546651/download?download_frd=1)

## Examples

- **If you implement a dynamically sized array (20), linked list (20), stack (10), heap (15), and hash table (20), you get 85 points. If you further template at least one of them (5), you get 90 points. If you template all of them (10), you get 95 points.**
- **Suppose instead that you implement the dynamically sized array (20), linked list (20), deque (15), and a (non-self-balancing) binary search tree (15), then you will get 70 points total.**

**Both examples assume you do not have any errors and that you implement all functions. You will always receive some partial score if you implement some of the required functionality, but it can range from 1 point to the maximum, depending on how much is missing.**
