HOMEWORK 4: DVD LISTS


NAME:  Cristian Mejia


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Websites: www.cplusplus.com, www.w3schools.com, en.cppreference.com, www.stackoverflow.com
Resources: Submitty discussion forums, lecture notes, lab

Remember: Your implementation for this assignment must be done on your
Maown, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  40 (╯°□°）╯︵ ┻━┻


ORDER NOTATION:
For each function, using the variables:
  d = number of different movie DVD titles
  k = average or maximum copies of each DVD
  c = number of customers
  p = average or maximum movies ranked on each customer’s preference list
Include a short description of your order notation analysis.

dvd: O(d^2) O(1) O(0) O(0) 
// O(d^2) because it loops to see if DVD exists, O(0) because copies aren't involved

customer: O(0) O(0) O(c^2) O(p) 
// O(c^2) because it loops through many customer functions

add_preference: O(c^3) O(d^2) O(p) 
// O(c^3) because it loops 3 times, O(d^2) because it loops 2 times, O(p) because list has to update

ship: O(c^4) 
// O(c^4) because it loops 4 times

return_oldest: O(c^3) O(p) 
// O(c^3) because it loops 3 times and O(p) because list has to update itself

return_newest: O(c^3) O(p) 
// O(c^3) because it loops 3 times and O(p) because list has to update itself

print_customer: O(c^3) O(d) // O(c^3) because there are 3 loops, O(d) because it searchs through DVD inventory

print_dvd: O(d^2) O(1) // O(d^2) because there are 2 loops, O(1) because number of copies has to be accessed



EXTRA CREDIT:
Describe the analysis you performed on customer satisfaction.  Paste
in a small amount of sample analysis output and/or specify a sample
output file.  Describe your improved algorithm and compare the
analysis results of your new algorithm.  Please be concise!



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

I don't know why I'm running into segmentation fault errors, if you 
could tell me why I would appreciate that :)






