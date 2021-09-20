HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  Cristian Mejia


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

COLLABORATORS: Aidan Saunders, Natalie L, Kelsey
Websites: www.cplusplus.com, www.w3schools.com, en.cppreference.com, www.stackoverflow.com
Resources: Submitty discussion forums, lecture notes, lab

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30



TESTING & DEBUGGING STRATEGY:
Please be concise!

Honestly, it was a lot of trial and error which isn't the most 
efficient way to debug. Towards the end, I started drawing 
diagrams to sort out the memory errors that occured when 
I wasn't properly setting the pointers. 


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

insert() = O(n^2) or O(n^3) 
// it doesn't iterate through the array 2 or 3 seperate times in actuality,
// so I'm not really sure if it counts as O(n^3) for worst case

erase() = O(1) or O(n)
pop_front() = O(n)
pop_back() = O(1) or O(n)
push_front() = if array is empty, O(1), or O(n)
push_back() = O(1)
copy_list = O(n^2)

I think that this is overall more efficient than the regular dslist
because there's less operations overall if you're not constantly inserting
and erasing elements. I believe that in the worst case scenario for UnrolledLL
and dslist, UnrolledLL would use less memory since the arrays are statically 
allocated. The UnrolledLL is lease efficient when you're inserting into a full
array. It's also least efficient when you're doing pop_front and push_front
because it's re-copying the array. So if the arrays were statically allocated
to be 6 elements, if each array was filled this data structure would be the 
least efficient of all the others where for dslist and STL list you just need to 
change pointers over copying arrays.



EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


