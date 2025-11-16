#include "localsearch.hpp"  // Incluye la cabecera que acabamos de definir
#include "heuristicas.hpp"   // MUY IMPORTANTE: Para acceder a calculate_makespan
#include <vector>
#include <algorithm>        // Para std::swap y std::max
#include <limits>           // Para std::numeric_limits

using namespace std;


Solution apply_swap(const FSSPInstance& instance, const Solution& solucion_inicial) {
    
    vector<int> secuencia_actual = solucion_inicial.job_sequence;
    int makespan_actual = solucion_inicial.makespan;
    int n = secuencia_actual.size();
    bool hubo_mejora = true;

    while (hubo_mejora) {
        hubo_mejora = false; // Asumimos que no encontraremos mejora en esta ronda

        // 3. Dos bucles 'for' anidados (i, j) para probar todos los swaps
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                
                // Crear una secuencia de prueba
                vector<int> secuencia_prueba = secuencia_actual;
                
                // Aplicar el swap
                swap(secuencia_prueba[i], secuencia_prueba[j]);

                // Calcular el nuevo makespan
                int nuevo_makespan = calculate_makespan(instance, secuencia_prueba);

                //Si encuentras una mejora:
                if (nuevo_makespan < makespan_actual) {
                    
                    // - Actualiza 'current_solution'
                    secuencia_actual = secuencia_prueba;
                    makespan_actual = nuevo_makespan;
                    
                    // - Marca 'hubo_mejora = true'
                    hubo_mejora = true;

                    // - Rompe los 'for' y reinicia el 'while'
                    break; // Salir del bucle 'j'
                }
            } // Fin del bucle 'j'
            
            if (hubo_mejora) {
                break; // Salir del bucle 'i' para reiniciar el 'while' -> PRIMERA MEJORA, NO MEJOR MEJORA
            }           //  solucion mas rapida con la estrategia de buscar el primer swap que implique mejora
                        // para no tener que probar todas las combinaciones
        } 
    } 

    Solution solucion_final;
    solucion_final.job_sequence = secuencia_actual;
    solucion_final.makespan = makespan_actual;

    return solucion_final;
}



Solution apply_insertion(const FSSPInstance& instance, const Solution& solucion_inicial) {
    
    vector<int> secuencia_actual = solucion_inicial.job_sequence;
    int makespan_actual = solucion_inicial.makespan;
    int n = secuencia_actual.size();
    bool hubo_mejora = true;

    while (hubo_mejora) {
        hubo_mejora = false; // Asumimos que no encontraremos mejora

        // dos bucles for anidados (i para sacar, j para insertar)
        
        // 'i' es el índice del trabajo que VAMOS A SACAR
        for (int i = 0; i < n; i++) {
            
            // j: POSICIÓN DONDE VAMOS A INSERTARLO
            for (int j = 0; j < n; j++) {
                
                // No tiene sentido sacarlo e insertarlo en la misma posición
                if (i == j) {
                    continue;
                }

                // Crear una secuencia de prueba
                vector<int> secuencia_prueba = secuencia_actual;
                
                // Guardamos el trabajo que vamos a mover
                int trabajo_a_mover = secuencia_prueba[i];

                // Aplicar el "movimiento" (sacar y luego insertar)
                secuencia_prueba.erase(secuencia_prueba.begin() + i);
                secuencia_prueba.insert(secuencia_prueba.begin() + j, trabajo_a_mover);

                // Calcular el nuevo makespan
                int nuevo_makespan = calculate_makespan(instance, secuencia_prueba);

                // 4. Si encuentras una mejora:
                if (nuevo_makespan < makespan_actual) {
                    
                    // - Actualiza 'current_solution'
                    secuencia_actual = secuencia_prueba;
                    makespan_actual = nuevo_makespan;

                    // - Marca 'hubo_mejora = true'
                    hubo_mejora = true;

                    // - Rompe los 'for' y reinicia el 'while'
                    break; // Salir del bucle 'j'
                }
            } 
            
            if (hubo_mejora) {
                break; 
            }
        }
    } 

    Solution solucion_final;
    solucion_final.job_sequence = secuencia_actual;
    solucion_final.makespan = makespan_actual;

    return solucion_final;
}