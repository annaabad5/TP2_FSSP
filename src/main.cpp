#include <iostream>
#include "parser.hpp"

int main() {
    // Reemplaza con la ruta a tu archivo
    std::string filepath = "data/flowshop1.txt"; 
    std::vector<FSSPInstance> all_instances = parse_fssp_file(filepath);

    if (all_instances.empty()) {
        std::cout << "No se cargaron instancias." << std::endl;
        return 1;
    }

    std::cout << "Se cargaron " << all_instances.size() << " instancias." << std::endl;

    // Imprimir datos de la primera instancia para verificar
    FSSPInstance first = all_instances[0];
    std::cout << "--- Primera Instancia ---" << std::endl;
    std::cout << "Nombre: " << first.name << std::endl;
    std::cout << "Trabajos: " << first.n_jobs << ", Máquinas: " << first.m_machines << std::endl;
    
    std::cout << "Tiempos del primer trabajo (trabajo 0):" << std::endl;
    for (int k = 0; k < first.m_machines; ++k) {
        std::cout << "  Máquina " << k << ": " 
                  << first.processing_times[0][k] << "s" << std::endl;
    }

    // Aquí es donde llamarías a tus heurísticas:
    // Solution neh_solution = run_neh(first);
    // std::cout << "Makespan NEH: " << neh_solution.makespan << std::endl;

    return 0;
}