HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  Cristian Mejia


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Websites: www.cplusplus.com, www.w3schools.com, en.cppreference.com, www.stackoverflow.com, www.geeksforgeeks.org
Resources: Submitty discussion forums, lecture notes, lecture solutions, lab

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

--------------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest          |
|          | sort     | dups     | mode     | pair     | sorted   | substr           | 
--------------------------------------------------------------------------------------
|          | O(nlogn) | O(n^2)   | O(nlogn) | O(nlogn) |O(f+nlogn)|O(l ^ 2 * n log n)|
| vector   |          |          |          |          |          |                  |
--------------------------------------------------------------------------------------
|          | O(nlogn) | O(n^2)   | O(nlogn) | O(nlogn) |O(f+nlogn)|O(l ^ 2 * n log n)|
| list     |          |          |          |          |          |                  |
--------------------------------------------------------------------------------------
|          | O(logn)  |O(logn)  |O(n log n)|O(n log n)|O(f+nlogn)|O(n*l^2log(n*l^2)) |
| bst      |          |         |          |          |          |                   |
--------------------------------------------------------------------------------------
|          | O(nlogn) |    X     |O(n log n)|O(n log n)|O(f+nlogn)|    X             |
| pq       |          |          |          |          |          |                  |
--------------------------------------------------------------------------------------
|          |    X     |  O(n)    |   O(n)   |  O(n)    |    X     |O(n*l^2log(n*l^2))|
| hash     |          |          |          |          |          |                  | 
--------------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

Vector:
sort               10,000 length 5 strings     0.0088 sec
sort               50,000 length 5 strings     0.0463 sec
sort              100,000 length 5 strings     0.1131 sec
sort              500,000 length 5 strings     0.5438 sec

k = 1.79917 X 10 ^-7

remove_dups         5,000 length 3 strings     0.2482 sec 
remove_dups        10,000 length 3 strings     0.9156 sec
remove_dups        20,000 length 3 strings     3.1254 sec 
remove_dups        50,000 length 3 strings    12.6821 sec

k = 5.364 x 10^ -5

mode               10,000 length 4 strings     0.0084 sec
mode               50,000 length 4 strings     0.0465 sec
mode              100,000 length 4 strings     0.0956 sec
mode              500,000 length 4 strings     0.4954 sec

closest_pair       10,000 8 digit integers     0.0067 sec   
closest_pair       50,000 8 digit integers     0.0357 sec    
closest_pair      100,000 8 digit integers     0.0739 sec  
closest_pair      500,000 8 digit integers     0.4065 sec

first 50 sorted   10,0000 length 4 strings     0.0087 sec   
first 50 sorted   20,0000 length 4 strings     0.0433 sec    
first 50 sorted   50,0000 length 4 strings     0.0964 sec   
first 50 sorted  100,0000 length 4 strings     0.5085 sec

Linked List:
sort               10,000 length 5 strings     0.0133 sec     
sort               50,000 length 5 strings     0.0787 sec    
sort              100,000 length 5 strings     0.1750 sec     
sort              500,000 length 5 strings     1.0857 sec

k = 3.54987 x 10^-7

remove_dups         5,000 length 3 strings     0.4561 sec     
remove_dups        10,000 length 3 strings     1.5616 sec    
remove_dups        20,000 length 3 strings     5.3018 sec     
remove_dups        50,000 length 3 strings    21.6421 sec

k = 1.093 x 10^ -4

mode               10,000 length 4 strings     0.0124 sec    
mode               50,000 length 4 strings     0.0691 sec    
mode              100,000 length 4 strings     0.1492 sec   
mode              500,000 length 4 strings     1.0434 sec 

closest_pair       10,000 8 digit integers     0.0120 sec    
closest_pair       50,000 8 digit integers     0.0687 sec   
closest_pair      100,000 8 digit integers     0.1470 sec    
closest_pair      500,000 8 digit integers     1.0972 sec 

first 50 sorted   10,0000 length 4 strings     0.0123 sec  
first 50 sorted   20,0000 length 4 strings     0.0700 sec     
first 50 sorted   50,0000 length 4 strings     0.1536 sec     
first 50 sorted  100,0000 length 4 strings     0.9565 sec

BST:
sort               10,000 length 5 strings     0.0135 sec     
sort               50,000 length 5 strings     0.0743 sec     
sort              100,000 length 5 strings     0.1925 sec    
sort              500,000 length 5 strings     1.2487 sec 

remove_dups         5,000 length 3 strings     0.3522 sec    
remove_dups        10,000 length 3 strings     1.2725 sec     
remove_dups        20,000 length 3 strings     3.0645 sec   
remove_dups        50,000 length 3 strings     5.9420 sec   

mode               10,000 length 4 strings     0.0120 sec    
mode               50,000 length 4 strings     0.1115 sec     
mode              100,000 length 4 strings     0.1563 sec    
mode              500,000 length 4 strings     0.9548 sec   

closest_pair       10,000 8 digit integers     0.0106 sec     
closest_pair       50,000 8 digit integers     0.0634 sec    
closest_pair      100,000 8 digit integers     0.1495 sec   
closest_pair      500,000 8 digit integers     1.0124 sec    

first 50 sorted   10,0000 length 4 strings     0.0120 sec    
first 50 sorted   20,0000 length 4 strings     0.0651 sec     
first 50 sorted   50,0000 length 4 strings     0.2312 sec   
first 50 sorted  100,0000 length 4 strings     1.1616 sec

Priority Queue:
sort               10,000 length 5 strings     0.0170 sec    
sort               50,000 length 5 strings     0.0917 sec    
sort              100,000 length 5 strings     0.2044 sec     
sort              500,000 length 5 strings     1.1479 sec

mode               10,000 length 4 strings     0.0155 sec
mode               50,000 length 4 strings     0.0859 sec    
mode              100,000 length 4 strings     0.1828 sec   
mode              500,000 length 4 strings     1.1489 sec

closest_pair       10,000 8 digit integers     0.0163 sec    
closest_pair       50,000 8 digit integers     0.0856 sec  
closest_pair      100,000 8 digit integers     0.1753 sec  
closest_pair      500,000 8 digit integers     0.9502 sec

first 50 sorted   10,0000 length 4 strings     0.0054 sec    
first 50 sorted   20,0000 length 4 strings     0.0252 sec    
first 50 sorted   50,0000 length 4 strings     0.0545 sec   
first 50 sorted  100,0000 length 4 strings     0.2550 sec

Hash Table:
sort               10,000 length 5 strings     0.0064 sec    
sort               50,000 length 5 strings     0.0586 sec     
sort              100,000 length 5 strings     0.0785 sec   
sort              500,000 length 5 strings     0.5607 sec   

remove_dups         5,000 length 3 strings     0.2600 sec    
remove_dups        10,000 length 3 strings     0.9168 sec     
remove_dups        20,000 length 3 strings     2.5448 sec    
remove_dups        50,000 length 3 strings     4.3415 sec     

mode               10,000 length 4 strings     0.0073 sec    
mode               50,000 length 4 strings     0.0312 sec     
mode              100,000 length 4 strings     0.0653 sec   
mode              500,000 length 4 strings     0.4243 sec



DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  

The measurements and the performance of the functions were close to what I 
had predicted. The majority were only off by a small fraction because of the 
time to insert into the structure. I had not accounted for that. As for the 
coefficients of similar Big O algorithms, the list and vector sort functions 
both have the same Big O notation but different coefficients. This is most 
likely because of the way the data structures are implemented at their core. 
Linked Lists are nodes connected together with references to the next value 
whereas arrays are adjacent blocks of memory that store the data. The 
coefficients for their time complexity match my assumptions as the coefficient 
is greater for linked lists for sort. This makes linked lists very inefficient 
compared to vectors in these sorts of tests since it takes nearly twice the 
amount of time to complete some of these tests. The operations that were 
dependent on sorting benefited the BSTs since they are naturally sorted with a 
big O of O(log n). However, in some tests, BSTs, vectors, and priority queues 
had similar run times for the same operations. After completing all of the 
tests, for the tests that they were able to do the BSTs and hash tables were 
consistently more efficient compared to the other structures. Although the 
smaller tests had similar run times, the larger tests tended to benefit these 
data structures due to their design to be efficient at storing large amounts of 
data. In conclusion, I believe that my predictions for the run times fit the 
actual performance of these data structures which I didn't expect. I would've 
liked to produce more tests to reaffirm my understanding but I didn't have enough 
time to do so.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!
