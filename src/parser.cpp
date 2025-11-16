#include "parser.hpp" 
#include <iostream>
#include <fstream>   
#include <sstream>   

std::vector<FSSPInstance> parse_fssp_file(const std::string& filepath) {
    std::vector<FSSPInstance> instances;
    std::ifstream file(filepath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filepath << std::endl;
        return instances; 
    }

    while (std::getline(file, line)) {
        
        // 1. Buscar el inicio de una instancia
        if (line.rfind("instance", 0) == 0) {
            FSSPInstance current_instance;
            current_instance.name = line;

            // 2. Skip separator lines and description until we find the n m line
            // Read lines until we find one with two integers (n_jobs and m_machines)
            while (std::getline(file, line)) {
                // Try to parse as two integers
                std::stringstream ss(line);
                int n, m;
                if (ss >> n >> m) {
                    // Successfully read two integers
                    current_instance.n_jobs = n;
                    current_instance.m_machines = m;
                    break;
                }
                // Otherwise continue reading (skip empty lines, descriptions, separators)
            }

            // 3. Redimensionar la matriz de tiempos
            current_instance.processing_times.resize(
                current_instance.n_jobs,
                std::vector<int>(current_instance.m_machines)
            );

            // 4. Leer las 'n_jobs' líneas de trabajos
            for (int i = 0; i < current_instance.n_jobs; ++i) {
                if (!std::getline(file, line)) break;
                
                std::stringstream ss_job(line);
                int machine_index_temp;
                int time;

                // 5. Parsear los pares (índice, tiempo)
                for (int k = 0; k < current_instance.m_machines; ++k) {
                    ss_job >> machine_index_temp >> time;
                    current_instance.processing_times[i][k] = time;
                }
            }
            
            // 6. Guardar la instancia completa
            instances.push_back(current_instance);
        }
    }

    file.close();
    return instances;
}