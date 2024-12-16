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

    void fit(float *data, int labels[], int n_lines, int n_cols)
    {
        num_lines = n_lines;
        num_cols = n_cols;

        for (int i = 0; i < n_lines; ++i)
        {
            for (int j = 0; j < n_cols; ++j)
            {
                train_data[i][j] = data[i * n_cols + j]; 
            }
            train_labels[i] = labels[i];
        }
    }

    void predict(float test_data[][10], int num_test_samples, int predictions[])
    {
        for (int i = 0; i < num_test_samples; ++i)
        {
            float distances[100]; // Armazena distâncias para cada exemplo de treinamento
            int labels[100];      // Armazena classes correspondentes

            // Calcula a distância do exemplo de teste para cada exemplo de treinamento
            for (int j = 0; j < num_lines; ++j)
            {
                distances[j] = euclidean_distance(test_data[i], train_data[j]);
                labels[j] = train_labels[j];
            }

            // Ordena as distâncias em ordem crescente (simples Bubble Sort para iniciantes)
            for (int j = 0; j < num_lines - 1; ++j)
            {
                for (int k = j + 1; k < num_lines; ++k)
                {
                    if (distances[j] > distances[k])
                    {
                        swap(distances[j], distances[k]);
                        swap(labels[j], labels[k]);
                    }
                }
            }

            // Conta as classes dos k vizinhos mais próximos
            int class_count[10] = {0}; // Supondo no máximo 10 classes
            for (int j = 0; j < k; ++j)
            {
                class_count[labels[j]]++;
            }

            // Determina a classe mais frequente
            int best_class = 0;
            int max_count = 0;
            for (int j = 0; j < 10; ++j)
            {
                if (class_count[j] > max_count)
                {
                    best_class = j;
                    max_count = class_count[j];
                }
            }

            predictions[i] = best_class;
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