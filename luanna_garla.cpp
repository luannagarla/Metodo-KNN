#include "read_csv.h"
#include "knn.h"
#include <iostream>

using namespace std;

void Process(string datasetFileName, string labelFileName, char delimiter, bool ignoreFirstLine);

int main()
{
    char delimiter = ',';        // pode ser alterado
    bool ignoreFirstLine = true; // pode ser alterado

    string fileTraining = "dataset-training.csv";
    string labelTraining = "label-training.csv";
    string fileNoLabel = "dataset-no-label.csv";

    Process(fileTraining, labelTraining, delimiter, ignoreFirstLine);

    return 0;
}

void Process(string datasetFileName, string labelFileName, char delimiter, bool ignoreFirstLine)
{
    CSVReader readerDataset(datasetFileName, delimiter, ignoreFirstLine);
    CSVReader readerLabel(labelFileName, delimiter, ignoreFirstLine);

    ifstream fileDataset(datasetFileName.c_str());
    ifstream fileLabel(labelFileName.c_str());

    if (fileDataset.is_open() && fileLabel.is_open())
    {
        void *listDataset = readerDataset.readData(fileDataset);
        void *listLabel = readerLabel.readData(fileLabel);

        KNN knn(5);
        knn.fit(&listDataset, listLabel, readerDataset.getCurrentRows, readerDataset.getCurrentCols + 1);
    }
    else
    {
        cout << "Erro ao abrir os arquivos!" << endl;
    }
}