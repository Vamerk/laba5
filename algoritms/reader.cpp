#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::string inputFileName = "in.json";
    std::ifstream inputFile(inputFileName);


    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл: " << inputFileName << std::endl;
        return 1; 
    }

    // Чтение данных из файла
    char c;
    std::vector<std::vector<int>> myArray;
    while (inputFile.get(c)) {
        if (std::isdigit(c)) {
            inputFile.unget();
            int value;
            inputFile >> value;
            std::vector<int> row;
            row.push_back(value);

            inputFile >> c; 

            inputFile >> value;
            row.push_back(value);

            myArray.push_back(row);
        }
    }

    // Вывод массива
    for (const auto& row : myArray) {
        for (int element : row) 
            std::cout << element << " ";    
        std::cout << std::endl;
    }

    inputFile.close(); 

    return 0;
}
