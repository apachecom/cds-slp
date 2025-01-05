
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <benchmark/benchmark.h>
#include <slp/RePairSLPIndex.h>


std::string load_data(const std::string& collection) {
    // Abrir el archivo para lectura binaria
    std::ifstream input_file(collection, std::ios::binary);
    if (!input_file) {
        throw std::runtime_error("Error: Unable to open the file " + collection);
    }

    // Leer todo el contenido del archivo
    std::vector<char> buffer((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    input_file.close();

    // Convertir el buffer a std::string
    std::string data(buffer.begin(), buffer.end());

    // Escribir los datos en un archivo temporal
    std::ofstream temp_file("./temp_collection", std::ios::binary);
    if (!temp_file) {
        throw std::runtime_error("Error: Unable to write to the temporary file.");
    }
    temp_file.write(data.data(), data.size());
    temp_file.put('\0'); // Agregar un carácter nulo al final
    temp_file.close();

    std::cout << "DATA LOADED\n";
    return data;
}



int main (int argc, char *argv[] ){

    if(argc < 2){
        std::cout<<"bad parameters...."<<std::endl;
        return 0;
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;

}
