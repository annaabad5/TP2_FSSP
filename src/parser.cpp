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
        
        // 1. Buscar el inicio de una instancia (CORREGIDO)
        if (line.rfind("instance", 0) == 0) {
            FSSPInstance current_instance;
            current_instance.name = line; // Guarda el nombre (ej. "instance car1")

            // 2. Saltar la línea de descripción (AÑADIDO)
            // Leemos la línea (ej. "Carlier 11x5...") y la ignoramos
            // También saltamos líneas vacías o de '+++' que pueda haber
            while (std::getline(file, line) && (line.empty() || line.find("+++") != std::string::npos)) {
                // Saltar líneas de formato o vacías
            }
            // Ahora 'line' contiene la línea de descripción, la volvemos a saltar
            if (!std::getline(file, line)) break;


            // 3. Leer n y m (CORREGIDO)
            // Ahora 'line' SI contiene los números n y m
            std::stringstream ss_header(line);
            ss_header >> current_instance.n_jobs >> current_instance.m_machines;
            
            // Redimensionar la matriz de tiempos
            current_instance.processing_times.resize(
                current_instance.n_jobs,
                std::vector<int>(current_instance.m_machines)
            );

            // 4. Leer las 'n_jobs' líneas de trabajos (esto queda igual)
            for (int i = 0; i < current_instance.n_jobs; ++i) {
                if (!std::getline(file, line)) break; 
                
                std::stringstream ss_job(line);
                int machine_index_temp; 
                int time;

                // 5. Parsear los pares (índice, tiempo) (esto queda igual)
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