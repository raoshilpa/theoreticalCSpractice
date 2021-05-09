# theoreticalCSpractice
Work done in Data Structures and Algorithms (and beyond!)

# linkedList
The "Set" object is an abstract data type Set of [strings/ints/etc], representing the concept of a collection of itemTypes. 
This type can be determined from the user's end. The Set object was implemented with a self-written doubly linked list.

void unite(const Set& s1, const Set& s2, Set& result);
When this function returns, result must contain one copy of each of the values that appear in s1 or s2 or both, and must not contain any other values. (You must not assume result is empty when it is passed in to this function; it might not be.) Since result is a Set, it must, of course, not have any duplicates. For example, if s1 were a set of ints into which the values

     2 8 3 9 5
have been inserted, and s2 had the values

     6 3 8 5 10
inserted, then no matter what value it had before, result must end up as a set containing these values and no others (not necessarily in this order):

     9 3 6 5 10 2 8
     
   
void difference(const Set& s1, const Set& s2, Set& result);
When this function returns, result must contain one copy of each of the values that appear in s1 or s2 but not both, and must not contain any other values. (You must not assume result is empty when it is passed in to this function; it might not be.) For example, if s1 and s2 were as in the example above, result must end up as a set containing these values and no others (not necessarily in this order):

     9 6 2 10

