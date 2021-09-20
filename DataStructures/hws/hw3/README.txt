HOMEWORK 3: JAGGED ARRAY


NAME:  Cristian Mejia


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Websites: www.cplusplus.com, www.w3schools.com, en.cppreference.com, www.stackoverflow.com
Resources: Submitty discussion forums, lecture notes, lab

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

numElements
 unpacked: O(1), O(1), O(1)
 packed: O(1), O(1), O(1)

numBins
 unpacked: O(1), O(1), O(1)
 packed: O(1), O(1), O(1)

numElementsInBin
 unpacked: O(1), O(1), O(1)
 packed: O(1), O(1), O(1)

getElement
 unpacked: O(1), O(e), O(k)
 packed: O(1), O(1), O(1)

isPacked
 unpacked: O(1), O(1), O(1)
 packed: O(1), O(1), O(1)

clear
 unpacked: O(1), O(1), O(1)
 packed: O(b), O(e), O(k)

addElement
 unpacked: O(1), O(e), O(k)
 packed: O(1), O(1), O(1) // you can't edit it in packed mode

removeElement
 unpacked: O(1), O(e), O(k)
 packed: O(1), O(1), O(1) // you can't edit it in packed mode

pack
 unpacked: O(1), O(1), O(1)
 packed: O(1), O(1), O(1) // it's already in packed mode

unpack
 unpacked: O(1), O(1), O(1) // it's already in unpacked mode
 packed: O(1), O(1), O(1)

print 
 unpacked: O(1), O(e), O(k)
 packed: O(1), O(e), O(k)

constructor w/ integer argument
 unpacked: O(1), O(1), O(1)
 packed: O(1), O(1), O(1)

copy constructor
 unpacked: O(1), O(e), O(k)
 packed: O(1), O(e), O(k)

destructor
 unpacked: O(1), O(e), O(k)
 packed: O(1), O(e), O(k)

assignment operator
 unpacked: O(1), O(e), O(k)
 packed: O(1), O(e), O(k)




MISC. COMMENTS TO GRADER:  
I wasn't able to get any office hours again for another week so
I wasn't able to get through fixing all my memory leaks. I also 
found out really late what packed and unpacked really meant so I 
didn't have enough time to change my code correctly.


