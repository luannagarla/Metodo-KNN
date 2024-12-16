#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class KNN
{
private:
    int k;
    int maxRows, maxCols, trainingRows;
    float **trainingData;
    int *trainingLabels;

public:
    KNN(int k)
        : k(k)
    {
    }

    ~KNN()
    {
    }

    void fit(float data[][2], int labels[], int rows, int cols)
    {
        trainingRows = rows;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                trainingData[i][j] = data[i][j];
            }
            trainingLabels[i] = labels[i];
        }
    }

    int predict(float sample[], int cols)
    {
        float *distances = new float[trainingRows];
        int *labelIndices = new int[trainingRows];

        // Calcula a distância euclidiana
        for (int i = 0; i < trainingRows; ++i)
        {
            float distance = 0.0;
            for (int j = 0; j < cols; ++j)
            {
                distance += pow(sample[j] - trainingData[i][j], 2);
            }
            distances[i] = sqrt(distance);
            labelIndices[i] = i;
        }

        // Ordena os índices com base nas distâncias
        // sort(labelIndices, labelIndices + trainingRows, [&](int a, int b)
        //           { return distances[a] < distances[b]; });

        // Conta os k vizinhos mais próximos
        int *labelCounts = new int[maxRows](); // Inicializa com zeros
        for (int i = 0; i < k; ++i)
        {
            labelCounts[trainingLabels[labelIndices[i]]]++;
        }

        // Determina o rótulo mais frequente
        int predictedLabel = 0;
        int maxCount = 0;
        for (int i = 0; i < maxRows; ++i)
        {
            if (labelCounts[i] > maxCount)
            {
                maxCount = labelCounts[i];
                predictedLabel = i;
            }
        }

        delete[] distances;
        delete[] labelIndices;
        delete[] labelCounts;

        return predictedLabel;
    }
};

// int main()
// {
//     const int maxRows = 6;
//     const int maxCols = 2;

//     KNN knn(3, maxRows, maxCols);

//     float trainingData[6][2] = {
//         {1.0, 2.0}, {2.0, 3.0}, {3.0, 3.0}, {6.0, 5.0}, {7.0, 8.0}, {8.0, 8.0}};
//     int trainingLabels[6] = {0, 0, 0, 1, 1, 1};

//     knn.train(trainingData, trainingLabels, 6, 2);

//     float sample[2] = {4.0, 4.0};
//     int prediction = knn.predict(sample, 2);

//     cout << "Classe prevista: " << prediction << endl;

//     return 0;
// }