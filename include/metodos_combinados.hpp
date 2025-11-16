#pragma once

#include "parser.hpp"   // Para FSSPInstance
#include "solution.hpp" // Para Solution

/**
 * @brief Método Híbrido: Ejecuta NEH y luego aplica Búsqueda Local (Swap).
 * (Cumple con Punto 3 y 4 del TP)
 */
Solution run_neh_swap(const FSSPInstance& instance);

/**
 * @brief Método Híbrido: Ejecuta NEH y luego aplica Búsqueda Local (Insertion).
 * (Cumple con Punto 3 y 4 del TP)
 */
Solution run_neh_insertion(const FSSPInstance& instance);

/**
 * @brief Método Híbrido: Ejecuta Palmer y luego aplica Búsqueda Local (Swap).
 * (Cumple con Punto 3 y 4 del TP)
 */
Solution run_palmer_swap(const FSSPInstance& instance);

/**
 * @brief Método Híbrido: Ejecuta Palmer y luego aplica Búsqueda Local (Insertion).
 * (Cumple con Punto 3 y 4 del TP)
 */
Solution run_palmer_insertion(const FSSPInstance& instance);


/**
 * @brief Método Híbrido: Ejecuta NEH + Swap + Insertion.
 * (Cumple con Punto 4.21 "combinación de operadores")
 */
Solution run_neh_swap_insertion(const FSSPInstance& instance);

/**
 * @brief Método Híbrido: Ejecuta NEH + Insertion + Swap.
 * (Cumple con Punto 4.21 "combinación de operadores")
 */
Solution run_neh_insertion_swap(const FSSPInstance& instance);