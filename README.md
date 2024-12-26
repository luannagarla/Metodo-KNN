# Projeto 02 - POO: método KNN

**Objetivo:** Implementação em c++ de uma classe que cálcule o KNN 

**Teste do código:**
Para testar o código, basta apenas rodá-lo passando corretamente as referências (nome do local do arquivo) dos csv nas váriaveis <br>

string fileTraining = "dataset-training.csv";
string labelTraining = "label-training.csv";
string fileNoLabel = "dataset-no-label.csv";

No meu código, esses arquivos estavam dentro de uma pasta "Output" no mesmo local que os códigos .cpp e .h

**Sobre o código**
- Existe três arquivos para a execução do código
    - read_csv.h: responsável por salvar dados de arquivos csv em arrays
    - knn.h: responsável pelo cálculo do KNN 
    - luanna_garla.cpp: lê arquivos csv, salva-os utilizando o read_csv.h e cálcula o knn utilizando o knn.h
- Diversas conversões tiveram que ser feitas no luanna_garla.cpp para que os ponteiros salvos em read_csv.h fossem devidamente convertidos em arrays de float para utilização no knn.h
- Não foi definidio um critério de desempate do knn

