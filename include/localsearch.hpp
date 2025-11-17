#pragma once

#include "parser.hpp"   // Para FSSPInstance
#include "solution.hpp" // Para Solution

// (Asumo que 'using namespace std;' NO se usa en .hpp)
// (Es mala práctica usarlo en cabeceras)


/**
 * @brief Aplica un operador de Búsqueda Local de Intercambio (Swap).
 * * Toma una solución inicial y la mejora repetidamente intercambiando
 * pares de trabajos hasta alcanzar un óptimo local.
 * * @param instance Los datos del problema (para llamar a calculate_makespan).
 * @param initial_solution La solución de partida (ej. la salida de NEH).
 * @return La solución mejorada (óptimo local).
 */
Solution apply_swap(const FSSPInstance& instance, const Solution& initial_solution);


/**
 * @brief Aplica un operador de Búsqueda Local de Inserción (Insertion).
 * * Toma una solución inicial y la mejora repetidamente sacando un trabajo
 * e insertándolo en otra posición, hasta alcanzar un óptimo local.
 * * @param instance Los datos del problema (para llamar a calculate_makespan).
 * @param initial_solution La solución de partida (ej. la salida de NEH).
 * @return La solución mejorada (óptimo local).
 */
Solution apply_insertion(const FSSPInstance& instance, const Solution& initial_solution);