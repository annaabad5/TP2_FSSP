#include "heuristics.hpp" 
#include <vector>
#include <numeric>     
#include <algorithm>   
#include <limits>      
#include <utility>     
using namespace std;



int calcularMakespan(const FSSPInstance& instance, const std::vector<int>& sequence) {
    int n = sequence.size();
    if (n == 0) {
        return 0;
    }
    int m = instance.m_machines;

    
    // obtener la referencia a los tiempos (mas rapido que copiar)
    const auto& tiempos = instance.processing_times; 
    
    vector<vector<int>> C(n, vector<int>(m));

    // rellenar la primera celda
    int primer_job = sequence[0]; 
    C[0][0] = tiempos[primer_job][0];

    // (Recorre las máquinas 'k' para el primer trabajo 'i=0')
    for (int k = 1; k < m; k++) {
        C[0][k] = C[0][k-1] + tiempos[primer_job][k];
    }

    // (Recorre los trabajos 'i' para la primera máquina 'k=0')
    for (int i = 1; i < n; i++) {
        int job_idx_actual = sequence[i]; // Índice real del trabajo
        C[i][0] = C[i-1][0] + tiempos[job_idx_actual][0];
    }

    // Rellenar el resto de la matriz (i > 0, k > 0)
    for (int i = 1; i < n; i++) {
        int job_idx_actual = sequence[i];
        for (int k = 1; k < m; k++) {
            C[i][k] = max(C[i-1][k], C[i][k-1]) + tiempos[job_idx_actual][k]; 
            // 2 condiciciones: El trabajo actual (i) debe haber terminado en la máquina anterior (k-1). 
            // Y la máquina actual (k) debe haber terminado con el trabajo anterior (i-1).
        
        }
    }
    return C[n-1][m-1];
}




Solution run_neh(const FSSPInstance& instance) {
    int n = instance.n_jobs;
    int m = instance.m_machines;

    const auto& tiempos = instance.processing_times;

    vector<pair<int, int>> lista_prioridad;

    for (int j = 0 ; j < n ; j++){
        int tiempo_t = 0;
        for (int i = 0 ; i < m; i++){
            tiempo_t += tiempos[j][i]

        }
        pair<int, int> elem = {tiempo_t, j};
        lista_prioridad.push_back(elem);
    }
    sort(lista_prioridad.rbegin(), lista_prioridad.rend());
    
    
    vector<int> current_sequence;
    int current_makespan = 0; 

    // Iteramos sobre la lista de prioridades (ya ordenada)
    for (int i = 0; i < n; ++i) {
        
        // Obtenemos el ID del trabajo a insertar (es el .second del pair)
        int job_to_insert = lista_prioridad[i].second;

        int best_makespan = numeric_limits<int>::max(); // infinito
        int best_position = 0;

        // Probamos insertar en CADA posición (de 0 a 'size()')
        for (int j = 0; j <= current_sequence.size(); ++j) {
            
            // 1. Crear una secuencia de prueba
            vector<int> test_sequence = current_sequence;
            
            // 2. Insertar el trabajo en la posición 'j'
            test_sequence.insert(test_sequence.begin() + j, job_to_insert);

            // 3. Calcular el makespan de esta secuencia de prueba
            int test_makespan = calculate_makespan(instance, test_sequence);

            // 4. Quedarnos con la mejor
            if (test_makespan < best_makespan) {
                best_makespan = test_makespan;
                best_position = j;
            }
        }

        // Fin del bucle interno
        // Ya encontramos la mejor posición, la insertamos en la secuencia "real"
        current_sequence.insert(current_sequence.begin() + best_position, job_to_insert);
        current_makespan = best_makespan; // Actualizamos el makespan
    }

    // evolver la solución final 
    Solution final_solution;
    final_solution.job_sequence = current_sequence;
    final_solution.makespan = current_makespan; 
    
    return final_solution;
}


Solution run_palmer(const FSSPInstance& instance) {
    int n = instance.n_jobs;
    int m = instance.m_machines;
    const auto& tiempos = instance.processing_times;

    // Indice de pendiente para cada trabajo

    // {indice_palmer, id_del_trabajo}
    vector<pair<int, int>> indices_trabajos;

    for (int j = 0; j < n; ++j) {
        int indice_pendiente = 0;
        
        for (int k = 0; k < m; ++k) {
            // para cada máquina: (m - 2k - 1)
            int peso = m - (2 * k) - 1;
            indice_pendiente += peso * tiempos[j][k];
        }
        
        indices_trabajos.push_back({indice_pendiente, j});
    }

    // ordenar los trabajos por el índice (descendente) 
    sort(indices_trabajos.rbegin(), indices_trabajos.rend());

    //vonstruir la secuencia final 
    vector<int> secuencia_final;
    
    //  extraemos los IDs de los trabajos en el orden en que quedaron en la lista
    for (int i = 0; i < n; ++i) {
        secuencia_final.push_back(indices_trabajos[i].second);
    }

    // calcular el makespan y devolver
    int makespan_final = calculate_makespan(instance, secuencia_final);

    Solution solucion_final;
    solucion_final.job_sequence = secuencia_final;
    solucion_final.makespan = makespan_final;

    return solucion_final;
}