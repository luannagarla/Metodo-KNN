#include "knn.h"
#include "read_csv.h"
#include <iostream>
#include <fstream>

using namespace std;

void Process(string datasetFileName, string labelFileName, string DatasetNoLabelFileName, char delimiter, bool ignoreFirstLine);

int main()
{
    char delimiter = ',';
    bool ignoreFirstLine = true;

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
        void *dataset = readerDataset.readData(fileDataset);            
        void *label = readerLabel.readData(fileLabel);                  
        void *test = readerDatasetNoLabel.readData(fileDatasetNoLabel); 

        float **listDataset = static_cast<float **>(dataset);
        int **listLabel = static_cast<int **>(label);
        float **listTest = static_cast<float **>(test);

        KNN knn(5);

        knn.fit(listDataset, listLabel, readerDataset.getCurrentRows(), readerDataset.getCurrentCols());

        int num_lines_test = readerDatasetNoLabel.getCurrentRows();
        int *predictions = knn.predict(listTest, num_lines_test);

        for (int i = 0; i < num_lines_test; ++i)
        {
            cout << "Classe prevista para o ponto de teste " << i << ": " << predictions[i] << endl;
        }

        delete[] predictions; 
    }
    else
    {
        cout << "Erro ao abrir os arquivos! Confira os nomes passados." << endl;
    }
}
