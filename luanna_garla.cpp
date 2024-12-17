#include "read_csv.h"
#include "knn.h"
#include <iostream>

using namespace std;
void Process(string datasetFileName, string labelFileName, string DatasetNoLabelFileName, char delimiter, bool ignoreFirstLine);

int main()
{
    char delimiter = ',';        // pode ser alterado
    bool ignoreFirstLine = true; // pode ser alterado

    string fileTraining = "dataset-training.csv";
    string labelTraining = "label-training.csv";
    string fileNoLabel = "dataset-no-label.csv";

    Process(fileTraining, labelTraining, fileNoLabel, delimiter, ignoreFirstLine);

    return 0;
}

void Process(string datasetFileName, string labelFileName, string DatasetNoLabelFileName, char delimiter, bool ignoreFirstLine)
{
    CSVReader readerDataset(datasetFileName, delimiter, ignoreFirstLine);
    CSVReader readerLabel(labelFileName, delimiter, ignoreFirstLine);
    CSVReader readerDatasetNoLabel(DatasetNoLabelFileName, delimiter, ignoreFirstLine);

    ifstream fileDataset(datasetFileName.c_str());
    ifstream fileLabel(labelFileName.c_str());
    ifstream fileDatasetNoLabel(DatasetNoLabelFileName.c_str());

    if (fileDataset.is_open() && fileLabel.is_open() && fileDatasetNoLabel.is_open())
    {
        void *listDataset = readerDataset.readData(fileDataset);
        void *listLabel = readerLabel.readData(fileLabel);
        void *listTest = readerDatasetNoLabel.readData(fileDatasetNoLabel);

        KNN knn(3);
        knn.fit(listDataset, listLabel, readerDataset.getCurrentRows(), readerDataset.getCurrentCols() + 1);

        int num_lines_teste = readerDatasetNoLabel.getCurrentRows();
        int *predictions = knn.predict(listTest, num_lines_teste);
        
        cout << "Classes previstas para as amostras de teste:" << std::endl;
        for (int i = 0; i < num_lines_teste; ++i)
        {
            std::cout << "Amostra " << i + 1 << ": Classe " << predictions[i] << std::endl;
        }

        delete[] predictions; //desalocação
    }
    else
    {
        cout << "Erro ao abrir os arquivos! Confira os nomes passados." << endl;
    }
}