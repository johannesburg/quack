#include <complex.h> 

typedef struct QubitRegister {
    complex double *state;
    int n_qubits;
} QubitRegister; 

typedef struct Unitary {
    complex double *elems;
    int size;
    char* label;
} Unitary;
// init, add, evolve, measure

QubitRegister* QubitRegister_new(int n_qubits, complex double *state); 

void QubitRegister_add(QubitRegister* q1, QubitRegister* q2);

void QubitRegister_evolve(QubitRegister* q, Unitary* u, int* qubits, int* control);

void QubitRegister_measure(QubitRegister* q, int* qubits);

Unitary* Unitary_new(int size, complex double *elems, char* label); 
