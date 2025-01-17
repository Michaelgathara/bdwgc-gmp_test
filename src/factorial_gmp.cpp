#include <iostream>
#include "gmp.h"
#include "gmpxx.h"
#include "gc.h"


using namespace std;

void* allocate_function (size_t alloc_size) {
    return GC_malloc(alloc_size);
}

void* reallocate_function (void *ptr, size_t old_size, size_t new_size) {
    return GC_realloc(ptr, new_size);
}

void deallocate_function (void *ptr, size_t size) {
    GC_free(ptr);
}

void factorial(int n) {
    mpz_t result;
    // initializes result and sets the value to 0
    mpz_init(result);

    // calculates the factorial of n and stores the outcome in result
    mpz_fac_ui(result, n);
    // gets the string representation of op using mpz_get_str(char *str, int base, mpz_t op)
    std::cout << n << "! = " << mpz_get_str(nullptr, 10, result) << std::endl;

    // Is used to clear any GMP resources used by a mpz_t variable
    // Done once a variable is no longer needed
    // mpz_clear(result);
}

int main ()
{
    // Setting the memory functions to be used by GMP
    // Described in Section 13 Custom Allocation of the GMP manual
    mp_set_memory_functions(&allocate_function, 
                            &reallocate_function, 
                            &deallocate_function);

  factorial(10000);
  return 0;
}