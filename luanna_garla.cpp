#include "read_csv.h"
#include "knn.h"
#include <iostream>

using namespace std;

void* processFile(string fileName, char delimiter, bool ignoreFirstLine);
void printData(void *newLista, bool isFirstColumnInt, int currentRows, int currentCols);

int main()
{
    char delimiter = ',';        // pode ser alterado
    bool ignoreFirstLine = true; // pode ser alterado
    
    string fileTraining = "dataset-training.csv";
    string labelTraining = "label-training.csv";

    string fileNoLabel = "dataset-no-label.csv";

    void *listDatasetTraining = processFile(fileTraining, delimiter, ignoreFirstLine);
    void *listLabelTraining = processFile(filabelTrainingleTraining, delimiter, ignoreFirstLine);
    // método fit

    void *listDatasetNoLabel = processFile(fileNoLabel, delimiter, ignoreFirstLine);
    //chamar função de predict do knn

    return 0;
}

void *processFile(string fileName, char delimiter, bool ignoreFirstLine)
{
    CSVReader reader(fileName, delimiter, ignoreFirstLine);
    cout << "-------------------------------------------------" << endl;
    cout << "Arquivo lido: " << fileName << endl;

    ifstream file(fileName.c_str());
    if (file.is_open())
    {
        void *newLista = reader.readData(file);

        return newLista;
    }
    else
    {
        cout << "Erro ao abrir o arquivo!" << endl;
    }
}