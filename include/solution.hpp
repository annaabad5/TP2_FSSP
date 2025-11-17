#pragma once

#include <vector>

// (No usamos 'using namespace std;' en archivos .hpp por buenas prácticas)

/**
 * @brief Estructura para guardar el resultado de una heurística.
 * * Contiene la secuencia de trabajos (el orden) y el makespan 
 * (costo) de esa secuencia.
 */
struct Solution {
    // La secuencia de trabajos. E.g., {0, 2, 1, 3}
    std::vector<int> job_sequence; 
    
    // El makespan final de esta secuencia
    int makespan;

    /**
     * @brief Constructor por defecto.
     * Inicializa el makespan en 0.
     */
    Solution() : makespan(0) {} 
};