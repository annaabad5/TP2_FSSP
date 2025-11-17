#include <iostream>     // para cout, cerr, endl
#include <fstream>      // para ofstream (escribir archivos)
#include <vector>       // para vector
#include <string>       // para string
#include <chrono>       // para medir el tiempo
#include <iomanip>      // para setprecision (formato de decimales)
#include <locale>       // para la configuracion local (punto decimal)

// incluye tus archivos de cabecera
#include "parser.hpp"
#include "solution.hpp"
#include "heuristicas.hpp"
#include "localsearch.hpp"
#include "metodos_combinados.hpp"

using namespace std;

int main() {
    
    string ruta_archivo = "data/flowshop1.txt";
    vector<FSSPInstance> instancias = parse_fssp_file(ruta_archivo);

    if (instancias.empty()) {
        cerr << "error: no se pudieron cargar las instancias de " << ruta_archivo << endl;
        return 1;
    }

    ofstream archivo_resultados("resultados.csv");
    if (!archivo_resultados.is_open()) {
        cerr << "error: no se pudo crear el archivo resultados.csv" << endl;
        return 1;
    }

    cout << "instancias cargadas: " << instancias.size() << ". iniciando experimentacion..." << endl;

    archivo_resultados.imbue(locale("C"));
    archivo_resultados << fixed << setprecision(4);
    
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

    double suma_makespan_neh = 0, suma_tiempo_neh = 0;
    double suma_makespan_palmer = 0, suma_tiempo_palmer = 0;
    double suma_makespan_neh_swap = 0, suma_tiempo_neh_swap = 0;
    double suma_makespan_neh_insert = 0, suma_tiempo_neh_insert = 0;
    double suma_makespan_palmer_swap = 0, suma_tiempo_palmer_swap = 0;
    double suma_makespan_palmer_insert = 0, suma_tiempo_palmer_insert = 0;
    double suma_makespan_neh_swap_insert = 0, suma_tiempo_neh_swap_insert = 0;
    double suma_makespan_neh_insert_swap = 0, suma_tiempo_neh_insert_swap = 0;

    // --- CORRECCION: identificar la primera fila si es basura ---
    // rfind("This file", 0) == 0 es una forma de preguntar "el string empieza con 'This file'?"
    size_t inicio_bucle = 0;
    double n_instancias_reales = static_cast<double>(instancias.size());

    if (!instancias.empty() && instancias[0].name.rfind("This file", 0) == 0) {
        cout << "nota: se detecto y omitio la primera fila de texto del parser." << endl;
        inicio_bucle = 1; // empezamos el bucle desde la posicion 1 (saltamos la 0)
        n_instancias_reales -= 1.0; // restamos 1 del total para el promedio
    }

    // bucle principal de experimentacion
    // --- CORRECCION: usamos un bucle 'for' tradicional para empezar desde 'inicio_bucle' ---
    for (size_t i = inicio_bucle; i < instancias.size(); ++i) {
        
        const auto& instancia = instancias[i]; // obtenemos la instancia actual

        cout << "procesando: " << instancia.name << "..." << endl;

        // heuristicas constructivas
        auto inicio_neh = chrono::high_resolution_clock::now();
        Solution sol_neh = run_neh(instancia);
        auto fin_neh = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh = fin_neh - inicio_neh;
        double tiempo_neh = duracion_neh.count();
        suma_makespan_neh += sol_neh.makespan; 
        suma_tiempo_neh += tiempo_neh;         

        auto inicio_palmer = chrono::high_resolution_clock::now();
        Solution sol_palmer = run_palmer(instancia);
        auto fin_palmer = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_palmer = fin_palmer - inicio_palmer;
        double tiempo_palmer = duracion_palmer.count();
        suma_makespan_palmer += sol_palmer.makespan; 
        suma_tiempo_palmer += tiempo_palmer;         

        // constructiva + 1 busqueda local
        auto inicio_neh_swap = chrono::high_resolution_clock::now();
        Solution sol_neh_swap = run_neh_swap(instancia);
        auto fin_neh_swap = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh_swap = fin_neh_swap - inicio_neh_swap;
        double tiempo_neh_swap = duracion_neh_swap.count();
        suma_makespan_neh_swap += sol_neh_swap.makespan; 
        suma_tiempo_neh_swap += tiempo_neh_swap;         

        auto inicio_neh_insert = chrono::high_resolution_clock::now();
        Solution sol_neh_insert = run_neh_insertion(instancia);
        auto fin_neh_insert = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh_insert = fin_neh_insert - inicio_neh_insert;
        double tiempo_neh_insert = duracion_neh_insert.count();
        suma_makespan_neh_insert += sol_neh_insert.makespan; 
        suma_tiempo_neh_insert += tiempo_neh_insert;         
        
        auto inicio_palmer_swap = chrono::high_resolution_clock::now();
        Solution sol_palmer_swap = run_palmer_swap(instancia);
        auto fin_palmer_swap = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_palmer_swap = fin_palmer_swap - inicio_palmer_swap;
        double tiempo_palmer_swap = duracion_palmer_swap.count();
        suma_makespan_palmer_swap += sol_palmer_swap.makespan; 
        suma_tiempo_palmer_swap += tiempo_palmer_swap;         
        
        auto inicio_palmer_insert = chrono::high_resolution_clock::now();
        Solution sol_palmer_insert = run_palmer_insertion(instancia);
        auto fin_palmer_insert = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_palmer_insert = fin_palmer_insert - inicio_palmer_insert;
        double tiempo_palmer_insert = duracion_palmer_insert.count();
        suma_makespan_palmer_insert += sol_palmer_insert.makespan; 
        suma_tiempo_palmer_insert += tiempo_palmer_insert;         

        // constructiva + combinacion de operadores
        auto inicio_neh_swap_insert = chrono::high_resolution_clock::now();
        Solution sol_neh_swap_insert = run_neh_swap_insertion(instancia);
        auto fin_neh_swap_insert = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh_swap_insert = fin_neh_swap_insert - inicio_neh_swap_insert;
        double tiempo_neh_swap_insert = duracion_neh_swap_insert.count();
        suma_makespan_neh_swap_insert += sol_neh_swap_insert.makespan; 
        suma_tiempo_neh_swap_insert += tiempo_neh_swap_insert;         

        auto inicio_neh_insert_swap = chrono::high_resolution_clock::now();
        Solution sol_neh_insert_swap = run_neh_insertion_swap(instancia);
        auto fin_neh_insert_swap = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion_neh_insert_swap = fin_neh_insert_swap - inicio_neh_insert_swap;
        double tiempo_neh_insert_swap = duracion_neh_insert_swap.count();
        suma_makespan_neh_insert_swap += sol_neh_insert_swap.makespan; 
        suma_tiempo_neh_insert_swap += tiempo_neh_insert_swap;         

        // escribir la fila de resultados de la instancia
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

    // --- CORRECCION: calcular y escribir la fila de promedios ---
    // nos aseguramos de que n_instancias_reales no sea cero para evitar division por cero
    if (n_instancias_reales > 0) {
        archivo_resultados << "PROMEDIO," // columna 'instancia'
                           << "," // columna 'n'
                           << "," // columna 'm'
                           << (suma_makespan_neh / n_instancias_reales) << "," << (suma_tiempo_neh / n_instancias_reales) << ","
                           << (suma_makespan_palmer / n_instancias_reales) << "," << (suma_tiempo_palmer / n_instancias_reales) << ","
                           << (suma_makespan_neh_swap / n_instancias_reales) << "," << (suma_tiempo_neh_swap / n_instancias_reales) << ","
                           << (suma_makespan_neh_insert / n_instancias_reales) << "," << (suma_tiempo_neh_insert / n_instancias_reales) << ","
                           << (suma_makespan_palmer_swap / n_instancias_reales) << "," << (suma_tiempo_palmer_swap / n_instancias_reales) << ","
                           << (suma_makespan_palmer_insert / n_instancias_reales) << "," << (suma_tiempo_palmer_insert / n_instancias_reales) << ","
                           << (suma_makespan_neh_swap_insert / n_instancias_reales) << "," << (suma_tiempo_neh_swap_insert / n_instancias_reales) << ","
                           << (suma_makespan_neh_insert_swap / n_instancias_reales) << "," << (suma_tiempo_neh_insert_swap / n_instancias_reales) << "\n";
    }

    // cerrar archivos y terminar
    archivo_resultados.close();
    
    cout << "-----------------------------------------------------" << endl;
    cout << "experimentacion finalizada." << endl;
    cout << "resultados guardados en: resultados.csv" << endl;
    cout << "(promedio calculado correctamente excluyendo filas invalidas)" << endl;
    cout << "-----------------------------------------------------" << endl;

    return 0;
}