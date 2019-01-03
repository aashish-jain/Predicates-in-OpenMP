# Predicates-in-OpenMP
A header file for processing predicates in parallel using OpenMP

<p>This project implements efficient parallel C++/OpenMP function <code>omp_extract_if</code>. The function works as follows: given a sequence <code>X</code> of some objects of type <code>T</code>, and a predicate that returns <code>true or false</code>, if an object satisfies some condition, the function creates sequence <code>Y</code> with a copy of only these objects in <code>X</code> for which the predicate is true. 

Here, the order in which elements in <code>Y</code> appear can be arbitrary (as long as all objects that should be copied are copied). The input sequence is assumed to be significantly large.
