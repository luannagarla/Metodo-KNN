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
        cout << "---- Arquivos lidos com sucesso! ----" << endl << endl;

        //leitura dos csv
        void *dataset = readerDataset.readData(fileDataset);
        void *label = readerLabel.readData(fileLabel);
        void *test = readerDatasetNoLabel.readData(fileDatasetNoLabel);

        int rows = readerDataset.getCurrentRows();
        int cols = readerDataset.getCurrentCols();

        //cast para uso do knn
        float **listDataset = reinterpret_cast<float **>(dataset);
        float *listLabel = reinterpret_cast<float *>(label); 

        // adiciona em nova estrutura 
        float **convertedDataSet = new float *[rows];
        for (int i = 0; i < rows; ++i)
        {
            convertedDataSet[i] = new float[cols];
            for (int j = 0; j < cols; ++j)
            {
                convertedDataSet[i][j] = listDataset[i][j];
                cout << "Dado de treinamento[" << i << "][" << j << "] = "
                     << convertedDataSet[i][j] << endl;
            }
        }

        int *convertedLabels = new int[rows];  
        for (int i = 0; i < rows; ++i)
        {
            convertedLabels[i] = listLabel[i];  
            cout << "Label convertido: " << convertedLabels[i] << endl;
        }

        //chamadas knn
        KNN knn(5);
        knn.fit(convertedDataSet, convertedLabels, rows, cols); //fit

        int num_lines_test = readerDatasetNoLabel.getCurrentRows();
        int num_cols_test = readerDatasetNoLabel.getCurrentCols();
        
        float **listTest = reinterpret_cast<float **>(test);
        float **convertedTest = new float *[num_lines_test]; //conversão adequada do csv de teste
        for (int i = 0; i < num_lines_test; ++i)
        {
            convertedTest[i] = new float[num_cols_test];
            for (int j = 0; j < num_cols_test; ++j)
            {
                convertedTest[i][j] = listTest[i][j];
                cout << "Dado a ser testado[" << i << "][" << j << "] = "
                     << convertedTest[i][j] << endl;
            }
        }

        //predições
        cout << endl << "---------------RESULTADO-----------------" << endl;

        int *predictions = knn.predict(convertedTest, num_lines_test);

        for (int i = 0; i < num_lines_test; ++i)
        {
            cout << "Classe prevista para o ponto de teste " << i + 1 << ": " << predictions[i] << endl;
        }

        // destrutor
        for (int i = 0; i < rows; ++i)
        {
            delete[] convertedDataSet[i];
        }
        delete[] convertedDataSet;
        delete[] convertedLabels;

        for (int i = 0; i < num_lines_test; ++i)
        {
            delete[] convertedTest[i];
        }
        delete[] convertedTest;

        delete[] predictions;
    }
    else
    {
        cout << "Erro ao abrir os arquivos! Confira os nomes passados." << endl;
    }
}