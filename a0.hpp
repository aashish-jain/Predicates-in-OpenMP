// File: a0.hpp
// Aashish
// Jain
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A0_HPP
#define A0_HPP

#include <vector>

// IMPLEMENT ME!

/* Takes two input vectors (a,b) and returns a new vector which results from appending a and b */
template <typename T>
inline std::vector<T> && append(std::vector<T> a, const std::vector<T> b) {
    a.insert(std::end(a), std::begin(b), std::end(b));
    return std::move(a);
} // append


template <typename T, typename Pred>
void omp_extract_if_custom_reduction(const std::vector<T>& in, std::vector<T>& out, Pred pred) {
    /* code */

    // Type encapsulation (alias) used for openmp
    using vector=std::vector<T>;

    // Custom reduction for vectors
    #pragma omp declare reduction \
    (vector_reduce:vector:omp_out=append(omp_out,omp_in)) \
    initializer(omp_priv = omp_orig)

    // Parallel loop
    # pragma omp parallel for reduction(vector_reduce:out)
    for(int i=0;i<in.size();i++)
        if(pred(in[i]))
            out.push_back(in[i]);        
} // omp_extract_if_custom_reduction


template <typename T, typename Pred>
void omp_extract_if(const std::vector<T>& in, std::vector<T>& out, Pred pred) {
    /* code */

    // Vector to store the elements that satisfy pred in x
    std::vector<int> mask(in.size());
    std::vector<int> s(in.size());

    //Parallelized loop for finding the elements satisfying pred in x
    #pragma omp parallel for
    for(int i=0;i<in.size();i++)
        s[i] = mask[i] = pred(in[i]);

    /* Calculating the serial prefix sum */
    // Creating a copy of the mask
    int n = s.size();

    // Can be done in parallel
    for(int i=0;i<n;i++)
        s[i]+=s[i-1];

    // Copying to the vector 
    out = std::vector<T>(s[n-1]);
    #pragma omp parallel for
    for(int i=0;i<n;i++)
        if(mask[i]==1)
            out[s[i]-1] = in[i];

} // omp_extract_if


#endif // A0_HPP