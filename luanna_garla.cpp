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

        // Chama readData e converte explicitamente o ponteiro para o tipo esperado
        void *dataset = readerDataset.readData(fileDataset);
        void *label = readerLabel.readData(fileLabel);
        void *test = readerDatasetNoLabel.readData(fileDatasetNoLabel);

        int rows = readerDataset.getCurrentRows();
        int cols = readerDataset.getCurrentCols();

        float **listDataset = reinterpret_cast<float **>(dataset);
        int *listLabel = reinterpret_cast<int *>(label); // Modificação para int* (vetor unidimensional)
        float **listTest = reinterpret_cast<float **>(test);

        // Configuração do KNN
        KNN knn(5);
        knn.fit(listDataset, listLabel, rows, cols);

        int num_lines_test = readerDatasetNoLabel.getCurrentRows();
        int num_cols_test = readerDatasetNoLabel.getCurrentCols();

        // Teste de dados sem linearização
        float **convertedTest = new float *[num_lines_test];
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

        cout << "---------------RESULTADO-----------------" << endl;

        int *predictions = knn.predict(convertedTest, num_lines_test);

        for (int i = 0; i < num_lines_test; ++i)
        {
            cout << "Classe prevista para o ponto de teste " << i + 1<< ": " << predictions[i] << endl;
        }

        // Libere a memória dos dados de teste
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