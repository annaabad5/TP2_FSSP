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
        // Find "instance" anywhere in the line
        if (line.find("instance") != std::string::npos) {
            FSSPInstance current_instance;
            current_instance.name = line;

            // Read next line that contains two integers (n_jobs m_machines)
            int n_jobs = 0, m_machines = 0;
            bool found = false;
            
            while (std::getline(file, line) && !found) {
                std::stringstream ss(line);
                if (ss >> n_jobs >> m_machines) {
                    // Check if we got valid dimensions
                    if (n_jobs > 0 && m_machines > 0) {
                        found = true;
                    }
                }
            }
            
            if (!found) {
                continue; // Skip if we couldn't find dimensions
            }

            current_instance.n_jobs = n_jobs;
            current_instance.m_machines = m_machines;

            // Resize the processing times matrix
            current_instance.processing_times.resize(
                n_jobs,
                std::vector<int>(m_machines)
            );

            // Read n_jobs lines of job data
            for (int i = 0; i < n_jobs; ++i) {
                if (!std::getline(file, line)) break;
                
                std::stringstream ss_job(line);
                int machine_idx, time;

                // Parse machine_idx and time pairs
                for (int k = 0; k < m_machines; ++k) {
                    if (ss_job >> machine_idx >> time) {
                        current_instance.processing_times[i][k] = time;
                    }
                }
            }
            
            // Store the complete instance
            instances.push_back(current_instance);
        }
    }

    file.close();
    return instances;
}