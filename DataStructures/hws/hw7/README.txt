HOMEWORK 7: HALLOWEEN COSTUME MAPS


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


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  6


ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)

addCostume(): Adding the costumes takes O(log(n) + m) because searching through a map takes "log n" time and we 
have to account for adding "m" number of costumes.

rentCostume(): Searching through the costumes takes O(log n) because searching through a map takes "log n" time. Then
searching for the person takes O(log c) because it takes "log c" time. Adding/removing a person from the list of people 
who checked out the costume is O(1), unless the vector runs out of space then it would be O(c) for "c" number of customers. 

lookup(): O(log(n) + c) because searching through a map takes "log n" time and printing out each element/customer from the
vector takes "c" time.

printPeople(): O(c) because it goes through "c" customers in the map.


EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
