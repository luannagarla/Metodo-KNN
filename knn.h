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
    float train_data[MAX_LINES][MAX_COLS]; // Dados de treinamento (matriz bidimensional)
    int train_labels[MAX_LINES];           // Rótulos de treinamento (vetor unidimensional)
    int num_lines;
    int num_cols;

public:
    KNN() : k(5), num_lines(0), num_cols(0) {}

    KNN(int k_value) : k(k_value), num_lines(0), num_cols(0) {}

    void fit(float **data, int *labels, int n_lines, int n_cols)
    {
        if (!data || !labels)
        {
            cout << "Erro: Dados de treinamento ou rótulos inválidos!" << endl;
            return;
        }

        num_lines = n_lines;
        num_cols = n_cols;

        for (int i = 0; i < num_lines; ++i)
        {
            for (int j = 0; j < num_cols; ++j)
            {
                train_data[i][j] = data[i][j];
            }
            train_labels[i] = labels[i]; 
        }

        cout << "Dados carregados com sucesso no método fit!" << endl;
    }

    int *predict(float **test_data, int num_lines_test)
    {
        if (!test_data)
        {
            cerr << "Erro: Dados de teste inválidos!" << endl;
            return NULL;
        }

        int *predictions = new int[num_lines_test];

        for (int t = 0; t < num_lines_test; ++t)
        {
            float test_point[MAX_COLS];

            // Copiando o ponto de teste para o vetor local
            for (int i = 0; i < num_cols; ++i)
            {
                test_point[i] = test_data[t][i];
            }

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

            // Desempate baseado nos votos dos vizinhos
            int votes[MAX_LINES] = {0};
            for (int i = 0; i < k; ++i)
            {
                int neighbor_index = indices[i];
                int label = train_labels[neighbor_index];
                votes[label]++;
            }

            int predicted_class = -1;
            int max_votes = -1;
            for (int i = 0; i < MAX_LINES; ++i)
            {
                if (votes[i] > max_votes)
                {
                    max_votes = votes[i];
                    predicted_class = i;
                }
            }

            predictions[t] = predicted_class;
        }

        return predictions;
    }
};