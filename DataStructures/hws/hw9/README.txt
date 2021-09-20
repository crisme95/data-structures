HOMEWORK 9: MINIBLAST


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


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10


HASH FUNCTION DESCRIPTION

I borrowed my hash function from lecture. How it makes the 
hash is that it takes the value of the index, multiplies it
by 8 and then adds the ASCII value of the indexed character
from the key.


HASH TABLE IMPLEMENTATION

My hash table is a vector of vectors. The vectors are pair types
where each pair is made up of the kmer and it's index in the genome.
During the insertion process, my program checks if at the index the key 
matches with another key in that vector. If so, it gets added on and if
not, it linearly probes until we find an empty spot. If there are too many
keys in the table, the table resizes by doubling its previous size.


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?

The amount of memory that the hash table would require is O(L) since I have to store the
entire genome sequence for it to be read. The query length would be O(k + q) because I'm 
saving q and taking length k out of q also. For the number of locations where a key is 
found, the memory usage would be O(L - k) since we don't want keys shorter than k. 


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

The running time for the genome command is O(L) since I'm reading through
every character in the file. The kmer command takes O((L - k) + p*k) since I have
to create (L - k) number of keys and make the table which takes (p*K) operations
since there are that many locations where the kmer could be. The table_size and 
occupancy command is O(1) since I'm only reading one line. 


EXTRA CREDIT
Add a new command to implement the database using one of the other
data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


