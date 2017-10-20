/*** Subset sum: given a set of numbers,
 *   informs the number of subsets whose
 *   elements add up to a given number.
 *   Relaxation: the set can have repeated numbers.
 ***/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <random>

typedef std::vector<uint32_t> MySet;

/**********************************************/
MySet generateSet( uint32_t size, uint32_t max_value, uint32_t seed );
void computeSubsets( MySet num_set, uint32_t objective );
uint32_t sumOfSubset( MySet::iterator element, MySet::iterator end,
                      uint32_t acc_value, uint32_t objective );
void printSet( MySet num_set );
/**********************************************/

int main( int argc, char* argv[] ) {

    /* Check if parameters have been passed */
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " [#items] [max item value] [value of interest] [random seed]" << std::endl;
        return 1;
    }

    uint32_t objective = std::stoul(argv[3]);
    MySet num_set = generateSet( std::stoul(argv[1]), std::stoul(argv[2]), std::stoul(argv[4]) );

#ifdef DEBUG
    printSet( num_set );
#endif

    computeSubsets( num_set, objective );
}

/*** Generates the input set ***/
MySet generateSet( uint32_t size, uint32_t max_value, uint32_t seed ) {
    std::mt19937 rand( seed );              //random number generator
    MySet num_set( size );                  //set with fixed size
    //generate set elements respecting the maximum value
    for (MySet::iterator value = num_set.begin(); value != num_set.end(); ++value) *value = rand() % max_value;
    std::sort( num_set.begin(), num_set.end() ); //sort set elements
    return num_set;
}

/*** Discovers the number of subsets whose elements
 * add up to the objective number ***/
void computeSubsets( MySet num_set, uint32_t objective ) {
    uint32_t result = 0;
    // computes the number of valid subsets starting at different points
    for (MySet::iterator init_value = num_set.begin(); init_value != num_set.end(); ++init_value)
        result += sumOfSubset( init_value, num_set.end(), 0, objective );
    std::cout << "Number of subsets = " << result << std::endl;
}

/*** Recursively finds valid subsets ***/
uint32_t sumOfSubset( MySet::iterator element, MySet::iterator end,
                      uint32_t acc_value, uint32_t objective ) {
    uint32_t total_subsets = 0; // Number of subsets found to return
    uint32_t current_value = acc_value + *element;
    // Finds a valid subset or searches with other possible elements
    if (current_value == objective) {
        ++total_subsets;
    } else {
        for (MySet::iterator next = ++element; next != end; ++next )
            total_subsets += sumOfSubset( next, end, current_value, objective );
    }
    return total_subsets;
}

/*** Prints debug data ***/
void printSet( MySet num_set ) {
    std::cerr << "Values in the set: ";
    for (auto value : num_set)
        std::cerr << value << ", ";
    std::cerr << std::endl;
}
