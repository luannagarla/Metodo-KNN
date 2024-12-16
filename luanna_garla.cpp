#include "knn.h"
#include <iostream>

using namespace std;

void processFile(string fileName, char delimiter, bool ignoreFirstLine);
void printData(void *newLista, bool isFirstColumnInt, int currentRows, int currentCols);

int main()
{
    string file1 = "features-Aula 13 - Projeto 1 - dataset1.csv";
    string file2 = "features-Aula 13 - Projeto 1 - dataset2.csv";
    string file3 = "label-Aula 13 - Projeto 1 - dataset1.csv";
    string file4 = "label-Aula 13 - Projeto 1 - dataset2.csv";

    char delimiter = ','; //pode ser alterado
    bool ignoreFirstLine = true; //pode ser alterado

    processFile(file1, delimiter, ignoreFirstLine);
    processFile(file2, delimiter, ignoreFirstLine);
    processFile(file3, delimiter, ignoreFirstLine);
    processFile(file4, delimiter, ignoreFirstLine);

    return 0;
}

void processFile(string fileName, char delimiter, bool ignoreFirstLine) //para otimizar código
{
    CSVReader reader(fileName, delimiter, ignoreFirstLine);
    cout << "-------------------------------------------------" << endl;
    cout << "Arquivo: " << fileName << endl;

    ifstream file(fileName.c_str());
    if (file.is_open())
    {
        void *newLista = reader.readData(file); 

        printData(newLista, reader.getIsFirstColumnInt(), reader.getCurrentRows(), reader.getCurrentCols());         
    }
    else
    {
        cout << "Erro ao abrir o arquivo!" << endl;
    }
}

void printData(void *newLista, bool isFirstColumnInt, int currentRows, int currentCols)
{
    if (isFirstColumnInt)
    {
        int **dataInt = static_cast<int **>(newLista); //tirando de void
        for (int i = 0; i < currentRows; i++)
        {
            for (int j = 0; j < currentCols; j++)
            {
                cout << dataInt[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        float **dataFloat = static_cast<float **>(newLista);
        for (int i = 0; i < currentRows; i++)
        {
            for (int j = 0; j < currentCols; j++)
            {
                cout << dataFloat[i][j] << " ";
            }
            cout << endl;
        }
    }
}
