#include <iostream>     
#include <fstream>      
#include <vector>       
#include <string>       
#include <chrono>       
#include <iomanip>      
#include <locale>       

#include "parser.hpp"
#include "solution.hpp"
#include "heuristicas.hpp"
#include "localsearch.hpp"
#include "metodos_combinados.hpp"

using namespace std;

int main() {
    
    // cargar todas las instancias
    string ruta_archivo = "data/flowshop1.txt";
    vector<FSSPInstance> instancias = parse_fssp_file(ruta_archivo);

    if (instancias.empty()) {
        cerr << "error: no se pudieron cargar las instancias de " << ruta_archivo << endl;
        return 1;
    }

    // preparar el archivo csv de resultados
    ofstream archivo_resultados("resultados.csv");
    if (!archivo_resultados.is_open()) {
        cerr << "error: no se pudo crear el archivo resultados.csv" << endl;
        return 1;
    }

    cout << "instancias cargadas: " << instancias.size() << ". iniciando experimentacion..." << endl;

    // configuracion para que el csv use '.' como separador decimal
    archivo_resultados.imbue(locale("C"));
    // fijar la precision de los tiempos (4 decimales)
    archivo_resultados << fixed << setprecision(4);
    
    // escribir la cabecera del csv
    // estos son los titulos de las columnas en tu excel
    archivo_resultados << "instancia,"
                       << "n,m,"
                       << "makespan_neh,tiempo_neh,"
                       << "makespan_palmer,tiempo_palmer,"
                       << "makespan_neh_swap,tiempo_neh_swap,"
                       << "makespan_neh_insert,tiempo_neh_insert,"
                       << "makespan_palmer_swap,tiempo_palmer_swap,"
                       << "makespan_palmer_insert,tiempo_palmer_insert,"
                       << "makespan_neh_swap_insert,tiempo_neh_swap_insert,"
                       << "makespan_neh_insert_swap,tiempo_neh_insert_swap\n";

    // bucle principal de experimentacion
    for (const auto& instancia : instancias) {
        
        // para saber que esta trabajando
        cout << "procesando: " << instancia.name << "..." << endl;

        // heuristicas constructivas (punto 4.19)
        
        auto inicio_neh = chrono::high_resolution_clock::now();
        Solution sol_neh = run_neh(instancia);
        auto fin_neh = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh = fin_neh - inicio_neh;
        double tiempo_neh = duracion_neh.count();

        auto inicio_palmer = chrono::high_resolution_clock::now();
        Solution sol_palmer = run_palmer(instancia);
        auto fin_palmer = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_palmer = fin_palmer - inicio_palmer;
        double tiempo_palmer = duracion_palmer.count();

        // constructiva + 1 busqueda local (punto 4.20)
        
        auto inicio_neh_swap = chrono::high_resolution_clock::now();
        Solution sol_neh_swap = run_neh_swap(instancia);
        auto fin_neh_swap = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh_swap = fin_neh_swap - inicio_neh_swap;
        double tiempo_neh_swap = duracion_neh_swap.count();

        auto inicio_neh_insert = chrono::high_resolution_clock::now();
        Solution sol_neh_insert = run_neh_insertion(instancia);
        auto fin_neh_insert = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh_insert = fin_neh_insert - inicio_neh_insert;
        double tiempo_neh_insert = duracion_neh_insert.count();
        
        auto inicio_palmer_swap = chrono::high_resolution_clock::now();
        Solution sol_palmer_swap = run_palmer_swap(instancia);
        auto fin_palmer_swap = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_palmer_swap = fin_palmer_swap - inicio_palmer_swap;
        double tiempo_palmer_swap = duracion_palmer_swap.count();
        
        auto inicio_palmer_insert = chrono::high_resolution_clock::now();
        Solution sol_palmer_insert = run_palmer_insertion(instancia);
        auto fin_palmer_insert = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_palmer_insert = fin_palmer_insert - inicio_palmer_insert;
        double tiempo_palmer_insert = duracion_palmer_insert.count();

        // constructiva + combinacion de operadores (punto 4.21)

        auto inicio_neh_swap_insert = chrono::high_resolution_clock::now();
        Solution sol_neh_swap_insert = run_neh_swap_insertion(instancia);
        auto fin_neh_swap_insert = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh_swap_insert = fin_neh_swap_insert - inicio_neh_swap_insert;
        double tiempo_neh_swap_insert = duracion_neh_swap_insert.count();

        auto inicio_neh_insert_swap = chrono::high_resolution_clock::now();
        Solution sol_neh_insert_swap = run_neh_insertion_swap(instancia);
        auto fin_neh_insert_swap = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh_insert_swap = fin_neh_insert_swap - inicio_neh_insert_swap;
        double tiempo_neh_insert_swap = duracion_neh_insert_swap.count();

        // escribir la fila de resultados en el csv
        archivo_resultados << instancia.name << ","
                           << instancia.n_jobs << "," << instancia.m_machines << ","
                           << sol_neh.makespan << "," << tiempo_neh << ","
                           << sol_palmer.makespan << "," << tiempo_palmer << ","
                           << sol_neh_swap.makespan << "," << tiempo_neh_swap << ","
                           << sol_neh_insert.makespan << "," << tiempo_neh_insert << ","
                           << sol_palmer_swap.makespan << "," << tiempo_palmer_swap << ","
                           << sol_palmer_insert.makespan << "," << tiempo_palmer_insert << ","
                           << sol_neh_swap_insert.makespan << "," << tiempo_neh_swap_insert << ","
                           << sol_neh_insert_swap.makespan << "," << tiempo_neh_insert_swap << "\n";
    }

    // cerrar archivos y terminar
    archivo_resultados.close();
    
    cout << "experimentacion finalizada." << endl;
    cout << "resultados guardados en: resultados.csv" << endl;

    return 0;
}