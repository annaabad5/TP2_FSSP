#include "metodos_combinados.hpp"
#include "heuristicas.hpp"
#include "localsearch.hpp"

using namespace std;

// Punto 3 del tp, combinamos las heuristicas construidas con los operadores de busqueda local

Solution run_neh_swap(const FSSPInstance& instance) {
    Solution solucion_constructiva = run_neh(instance);
    Solution solucion_mejorada = apply_swap(instance, solucion_constructiva);
    return solucion_mejorada;
}

Solution run_neh_insertion(const FSSPInstance& instance) {
    Solution solucion_constructiva = run_neh(instance);
    Solution solucion_mejorada = apply_insertion(instance, solucion_constructiva);
    return solucion_mejorada;
}

Solution run_palmer_swap(const FSSPInstance& instance) {
    Solution solucion_constructiva = run_palmer(instance);
    Solution solucion_mejorada = apply_swap(instance, solucion_constructiva);
    return solucion_mejorada;
}

Solution run_palmer_insertion(const FSSPInstance& instance) {
    Solution solucion_constructiva = run_palmer(instance);
    Solution solucion_mejorada = apply_insertion(instance, solucion_constructiva);
    return solucion_mejorada;
}

Solution run_neh_swap_insertion(const FSSPInstance& instance) {
    Solution solucion_neh = run_neh(instance);
    Solution solucion_swap = apply_swap(instance, solucion_neh);
    Solution solucion_final = apply_insertion(instance, solucion_swap);
    return solucion_final;
}

Solution run_neh_insertion_swap(const FSSPInstance& instance) {
    Solution solucion_neh = run_neh(instance);
    Solution solucion_insertion = apply_insertion(instance, solucion_neh);
    Solution solucion_final = apply_swap(instance, solucion_insertion);
    return solucion_final;
}