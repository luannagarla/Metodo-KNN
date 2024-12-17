#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

class KNN
{
private:
    int k;
    float train_data[100][100];
    int train_labels[100];
    int num_lines;
    int num_cols;

public:
    KNN()
    {
        k = 5;
        num_lines = 0;
        num_cols = 0;
    }

    KNN(int k_value)
    {
        k = k_value;
        num_lines = 0;
        num_cols = 0;
    }

    void fit(void *data, void *labels, int n_lines, int n_cols)
    {
        num_lines = n_lines;
        num_cols = n_cols;

        float *dataset = static_cast<float *>(data);
        int *labelset = static_cast<int *>(labels);

        for (int i = 0; i < n_lines; ++i)
        {
            for (int j = 0; j < n_cols; ++j)
            {
                train_data[i][j] = dataset[i * n_cols + j];
            }
            train_labels[i] = labelset[i];
        }
    }

    int *predict(void *test_data, int num_lines_test)
    {
        int *predictions = new int[num_lines_test];
        float *testDataset = static_cast<float *>(test_data);

        for (int t = 0; t < num_lines_test; ++t)
        {
            float test_point[10];

            for (int i = 0; i < num_cols; ++i)
            {
                test_point[i] = testDataset[t * num_cols + i];
            }

            float distances[100]; // Armazena as distâncias entre o ponto de teste e o treinamento
            for (int i = 0; i < num_lines; ++i)
            {
                float sum = 0.0;
                for (int j = 0; j < num_cols; ++j)
                {
                    float diff = train_data[i][j] - test_point[j];
                    sum += diff * diff; // Soma dos quadrados das diferenças
                }
                distances[i] = sqrt(sum); // Calcula a distância euclidiana
            }

            // Ordenar os índices dos exemplos de treinamento pelo valor da distância
            int indices[100];
            for (int i = 0; i < num_lines; ++i)
            {
                indices[i] = i;
            }

            for (int i = 0; i < num_lines - 1; ++i)
            {
                for (int j = i + 1; j < num_lines; ++j)
                {
                    if (distances[indices[i]] > distances[indices[j]])
                    {
                        std::swap(indices[i], indices[j]); // Ordenação simples
                    }
                }
            }

            // Contar os votos das classes dos k vizinhos mais próximos
            int votes[100] = {0}; // Vetor para contagem de votos por classe
            for (int i = 0; i < k; ++i)
            {
                int neighbor_index = indices[i];          // Índice do vizinho mais próximo
                int label = train_labels[neighbor_index]; // Classe do vizinho
                votes[label]++;
            }

            // Determinar a classe com o maior número de votos
            int max_votes = -1;
            int predicted_class = -1;
            for (int i = 0; i < 100; ++i)
            { // Percorre os votos possíveis
                if (votes[i] > max_votes)
                {
                    max_votes = votes[i];
                    predicted_class = i;
                }
            }

            predictions[t] = predicted_class; // Armazena a classe prevista
        }

        return predictions;
    }
};