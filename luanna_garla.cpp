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
        cout << "Arquivos lidos com sucesso!" << endl;

        void *dataset = readerDataset.readData(fileDataset);
        void *label = readerLabel.readData(fileLabel);
        void *test = readerDatasetNoLabel.readData(fileDatasetNoLabel);

        float **listDataset = static_cast<float **>(dataset);
        int **listLabel = static_cast<int **>(label);
        float **listTest = static_cast<float **>(test);

        int rows = readerDataset.getCurrentRows();
        int cols = readerDataset.getCurrentCols();

        float *linearizedDataset = new float[rows * cols];
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                linearizedDataset[i * cols + j] = listDataset[i][j];
            }
        }

        int *linearizedLabels = new int[rows];
        for (int i = 0; i < rows; ++i)
        {
            linearizedLabels[i] = listLabel[i][0];
        }

        KNN knn(5);
        knn.fit(linearizedDataset, linearizedLabels, rows, cols);

        int num_lines_test = readerDatasetNoLabel.getCurrentRows();
        int num_cols_test = readerDatasetNoLabel.getCurrentCols();

        float *linearizedTest = new float[num_lines_test * num_cols_test];
        for (int i = 0; i < num_lines_test; ++i)
        {
            for (int j = 0; j < num_cols_test; ++j)
            {
                linearizedTest[i * num_cols_test + j] = listTest[i][j];
            }
        }

        // int *predictions = knn.predict(linearizedTest, num_lines_test);

        // for (int i = 0; i < num_lines_test; ++i)
        // {
        //     cout << "Classe prevista para o ponto de teste " << i << ": " << predictions[i] << endl;
        // }

        cout << "KNN finalizado!" << endl;
        delete[] linearizedDataset;
        delete[] linearizedLabels;
        delete[] linearizedTest;
        // delete[] predictions;
    }
    else
    {
        cout << "Erro ao abrir os arquivos! Confira os nomes passados." << endl;
    }
}