#pragma once

#include <vector>
#include "parser.hpp"   // Necesita la definición de FSSPInstance
#include "solution.hpp" // Necesita la definición de Solution

// (No usamos 'using namespace std;' en archivos .hpp)

/**
 * @brief Calcula el makespan (Cmax) para una secuencia de trabajos dada.
 * * Esta es la función de evaluación clave que usan todas las heurísticas.
 * * @param instance Los datos del problema (tiempos de procesamiento).
 * @param sequence La secuencia de trabajos a evaluar (e.g., {0, 2, 1}).
 * @return El makespan (tiempo total) para esa secuencia.
 */
int calculate_makespan(const FSSPInstance& instance, const std::vector<int>& sequence);

/**
 * @brief Ejecuta la heurística constructiva NEH.
 * * @param instance Los datos del problema.
 * @return Una 'Solution' (secuencia + makespan) generada por NEH.
 */
Solution run_neh(const FSSPInstance& instance);

/**
 * @brief Ejecuta la heurística constructiva de Palmer.
 * * @param instance Los datos del problema.
 * @return Una 'Solution' (secuencia + makespan) generada por Palmer.
 */
Solution run_palmer(const FSSPInstance& instance);