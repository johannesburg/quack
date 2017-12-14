#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include "quack.h"

QubitRegister* QubitRegister_new(int n_qubits, complex double *state) {
    QubitRegister* q = (QubitRegister*) malloc(sizeof(QubitRegister));
    if (state == NULL) {
        state = (complex double *) malloc((1 << n_qubits) * sizeof(complex double)); 
        state[0] = 1.0; // this might break :(
    }
    q->state = state;
    q->n_qubits = n_qubits;
    return q;
}

void QubitRegister_add(QubitRegister* q1, QubitRegister* q2) {
    int size = q1->n_qubits + q2->n_qubits;
    complex double* state = (complex double*) malloc((1 << size) * sizeof(complex double));
    int index = 0;
    for (int i = 0; i < (1 << q1->n_qubits); i++) {
        for (int j = 0; j < (1 << q2->n_qubits); j++) {
            state[index++] = q1->state[i] * q2->state[j]; // complex multiplication?
        }
    }
    free(q1->state);
    q1->state = state;
    q1->n_qubits = size;
}

void QubitRegister_evolve(QubitRegister* q, Unitary* u, int* qubits, int* control) {
    complex double * state = (complex double *) malloc((1 << q->n_qubits) * sizeof(complex double)); 
    // state = U * q->state
    for (int row = 0; row < u->size; row++) {
        complex double sum = 0; // zero complex number?
        for (int col = 0; col < u->size; col++) {
            sum += u->elems[row * u->size + col] * q->state[col]; //complex number mul
        }  
        state[row] = sum;
    }
}

Unitary* Unitary_new(int size, complex double *elems, char* label) {
   Unitary* u = (Unitary*) malloc(sizeof(Unitary)); 
   u->size = size;
   u->elems = elems;
   u->label = label;
   return u;
}
