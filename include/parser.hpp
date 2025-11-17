#pragma once // Evita que el header se incluya múltiples veces

#include <string>
#include <vector>

// Estructura para almacenar los datos de UNA instancia
struct FSSPInstance {
    std::string name;
    int n_jobs;
    int m_machines;
    // Matriz de tiempos: n_jobs filas, m_machines columnas
    // Tiempos [i][k] es el tiempo del trabajo 'i' en la máquina 'k'
    std::vector<std::vector<int>> processing_times;
};

// Función que lee el archivo y devuelve un vector con todas las instancias
std::vector<FSSPInstance> parse_fssp_file(const std::string& filepath);