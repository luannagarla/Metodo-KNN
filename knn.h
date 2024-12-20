#include <cmath>
#include <algorithm>
#include <iostream>

#define MAX_LINES 50
#define MAX_COLS 50

using namespace std;

class KNN
{
private:
    int k;
    float train_data[MAX_LINES][MAX_COLS];
    int train_labels[MAX_LINES];
    int num_lines;
    int num_cols;

public:
    KNN() : k(5), num_lines(0), num_cols(0) {}

    KNN(int k_value) : k(k_value), num_lines(0), num_cols(0) {}

    void fit(void *data, void *labels, int n_lines, int n_cols)
    {
        if (!data || !labels)
        {
            cerr << "Erro: Dados de treinamento ou rótulos inválidos!" << endl;
            return;
        }

        num_lines = n_lines;
        num_cols = n_cols;

        // Conversão dos ponteiros para os tipos corretos
        float *dataset = static_cast<float *>(data);
        int *labelset = static_cast<int *>(labels);

        // Copiando os dados para a matriz interna do KNN
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
        if (!test_data)
        {
            cerr << "Erro: Dados de teste inválidos!" << endl;
            return NULL;
        }

        int *predictions = new int[num_lines_test];
        // Conversão para o tipo correto
        float *testDataset = static_cast<float *>(test_data);

        for (int t = 0; t < num_lines_test; ++t)
        {
            float test_point[MAX_COLS];

            // Copiando o ponto de teste para o vetor local
            for (int i = 0; i < num_cols; ++i)
            {
                test_point[i] = testDataset[t * num_cols + i];
            }

            // Calculando as distâncias entre o ponto de teste e os dados de treinamento
            float distances[MAX_LINES];
            for (int i = 0; i < num_lines; ++i)
            {
                float sum = 0.0;
                for (int j = 0; j < num_cols; ++j)
                {
                    float diff = train_data[i][j] - test_point[j];
                    sum += diff * diff;
                }
                distances[i] = sqrt(sum);
            }

            // Ordenando as distâncias e escolhendo os k vizinhos mais próximos
            int indices[MAX_LINES];
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
                        swap(indices[i], indices[j]);
                    }
                }
            }

            // Votação para determinar a classe do ponto de teste
            int votes[MAX_LINES] = {0};
            for (int i = 0; i < k; ++i)
            {
                int neighbor_index = indices[i];
                int label = train_labels[neighbor_index];
                votes[label]++;
            }

            // Determinando a classe com maior número de votos
            int predicted_class = -1;
            int max_votes = -1;
            for (int i = 0; i < MAX_LINES; ++i)
            {
                if (votes[i] > max_votes)
                {
                    max_votes = votes[i];
                    predicted_class = i; // A classe mais votada
                }
            }

            // Atribuindo a classe prevista ao array de previsões
            predictions[t] = predicted_class;
        }

        return predictions;
    }
};
