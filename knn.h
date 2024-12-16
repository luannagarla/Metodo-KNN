#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

template <typename T>
class KNN
{
private:
    int k;
    T **train_data;        // treinamento
    int *train_labels;     // labels treinamento
    int num_train_samples; // exemplos de treinamento
    int num_features;      // características por exemplo

    T euclidean_distance(const T *a, const T *b) const
    {
        T sum = 0;
        for (int i = 0; i < num_features; ++i)
        {
            sum += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return sqrt(sum);
    }

public:
    KNN() : k(5), train_data(NULL), train_labels(NULL), num_train_samples(0), num_features(0) {}

    KNN(int k_value) : k(k_value), train_data(NULL), train_labels(NULL), num_train_samples(0), num_features(0) {}

    void fit(T **data, int *labels, int n_samples, int n_features)
    {
        train_data = data;
        train_labels = labels;
        num_train_samples = n_samples;
        num_features = n_features;
    }

    int *predict(T **test_data, int num_test_samples) const
    {
        int *predictions = new int[num_test_samples]; // armazena as previsões

        for (int i = 0; i < num_test_samples; ++i)
        {
            T *test_point = test_data[i];

            // Calcula as distâncias do ponto de teste para todos os pontos de treinamento
            pair<T, int> *distances = new pair<T, int>[num_train_samples];
            for (int j = 0; j < num_train_samples; ++j)
            {
                T dist = euclidean_distance(test_point, train_data[j]);
                distances[j] = {dist, train_labels[j]};
            }

            // ordem crescente
            sort(distances, distances + num_train_samples);

            // Conta as classes dos k vizinhos mais próximos
            map<int, int> class_count;
            for (int j = 0; j < k; ++j)
            {
                class_count[distances[j].second]++;
            }

            // Determina a classe com maior frequência
            int best_class = -1;
            int max_count = -1;
            for (const auto &[cls, count] : class_count)
            {
                if (count > max_count)
                {
                    best_class = cls;
                    max_count = count;
                }
            }

            predictions[i] = best_class;
            delete[] distances; // libera a memória alocada 
        }

        return predictions;
    }
};