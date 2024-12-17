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

    void predict(float *test_data, int num_test_samples, int predictions[])
    {
        // Para cada exemplo de teste
        for (int t = 0; t < num_test_samples; ++t)
        {
            float test_point[10]; // Para armazenar os dados de uma amostra de teste
            for (int i = 0; i < num_cols; ++i)
            {
                test_point[i] = test_data[t * num_cols + i]; // Acessa os dados de teste como 1D
            }

            // Calcular a distância entre o ponto de teste e todos os pontos de treinamento
            float distances[100];
            for (int i = 0; i < num_lines; ++i)
            {
                float sum = 0;
                for (int j = 0; j < num_cols; ++j)
                {
                    sum += (train_data[i][j] - test_point[j]) * (train_data[i][j] - test_point[j]);
                }
                distances[i] = sqrt(sum); // Distância euclidiana
            }

            // Encontrar os k vizinhos mais próximos
            int indices[100];
            for (int i = 0; i < num_lines; ++i)
            {
                indices[i] = i;
            }

            // Ordenar os índices com base nas distâncias
            for (int i = 0; i < num_lines - 1; ++i)
            {
                for (int j = i + 1; j < num_lines; ++j)
                {
                    if (distances[indices[i]] > distances[indices[j]])
                    {
                        std::swap(indices[i], indices[j]);
                    }
                }
            }

            // Contar as classes dos k vizinhos mais próximos
            int votes[100] = {0}; // Contagem das classes
            for (int i = 0; i < k; ++i)
            {
                int neighbor_index = indices[i];
                int label = train_labels[neighbor_index];
                votes[label]++;
            }

            // Determinar a classe com mais votos
            int max_votes = -1;
            int predicted_class = -1;
            for (int i = 0; i < 100; ++i)
            {
                if (votes[i] > max_votes)
                {
                    max_votes = votes[i];
                    predicted_class = i;
                }
            }

            predictions[t] = predicted_class; // Atribui a classe prevista ao exemplo de teste
        }
    }

    float euclidean_distance(float *a, float *b)
    {
        float sum = 0;
        for (int i = 0; i < num_cols; ++i)
        {
            sum += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return sqrt(sum);
    }
};