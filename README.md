# Analisador Empírico de Algoritmos em C++

Este projeto foi desenvolvido como uma ferramenta para a análise empírica do tempo de execução de diferentes algoritmos de busca e ordenação. O programa executa cada algoritmo com entradas de tamanhos crescentes, mede o tempo médio de execução e, por fim, utiliza o método de Erro Médio Quadrático para determinar qual curva de complexidade teórica melhor se ajusta aos dados coletados.

---

## 📊 Funcionalidades

* **Análise de 4 Algoritmos:**
    * Busca Linear (O(n))
    * Busca Binária (O(log n))
    * Insertion Sort (O(n²))
    * Quick Sort (O(n log n))
* Análise de Complexidade: Compara o desempenho empírico com as seguintes curvas teóricas: O(n), O(n log n), O(n²), e O(n^3).
* Determinação de Melhor Ajuste: Calcula o Erro Médio Quadrático entre os dados medidos e os teóricos para indicar a curva de melhor ajuste.
* Exportação para CSV: Gera um arquivo `.csv` para cada algoritmo, contendo os dados normalizados, prontos para serem plotados em gráficos.

---

## 🚀 Como Compilar e Executar

Para compilar e executar este projeto, você precisará de um compilador C++ (como o g++) e do CMake instalados.

```bash
# 1. Clone o repositório (substitua pela URL do seu GitHub)
git clone [https://github.com/seu-usuario/analise-empirica-algoritmos.git](https://github.com/seu-usuario/analise-empirica-algoritmos.git)
cd analise-empirica-algoritmos

# 2. Crie a pasta de build e compile o projeto com CMake
mkdir build
cd build
cmake ..
make

# 3. Volte para a pasta raiz e execute o programa
cd ..
./build/alg_analyzer
```

Após a execução, os arquivos CSV serão gerados na pasta raiz do projeto.

---

## 📁 Estrutura do Projeto

O código está organizado da seguinte forma, separando os arquivos de cabeçalho (`include`) dos arquivos de implementação (`src`).

```
.
├── build/
├── include/
│   ├── binary_search.hpp
│   ├── calculate_time.hpp
│   ├── handle_input.hpp
│   ├── insertion_sort.hpp
│   ├── linear_search.hpp
│   └── quick_sort.hpp
├── src/
│   ├── binary_search.cpp
│   ├── calculate_time.cpp
│   ├── handle_input.cpp
│   ├── insertion_sort.cpp
│   ├── linear_search.cpp
│   ├── main.cpp
│   └── quick_sort.cpp
├── .gitignore
├── CMakeLists.txt
└── README.md
```

---

## 📈 Entendendo a Saída

O programa produz dois tipos de saída:

### 1. Saída no Console

Para cada algoritmo, o programa imprimirá qual foi a curva de complexidade teórica de melhor ajuste, com base no menor MSE encontrado.

**Exemplo de saída:**
```
-> Para o algoritmo 'quick_sort', a curva de melhor ajuste é: O(n log n)
Resultados salvos com sucesso em quick_sort.csv
```

### 2. Arquivos CSV

Para cada algoritmo, um arquivo `.csv` é gerado. Por exemplo, `quick_sort.csv`. Estes arquivos contêm os dados normalizados (escalados para o intervalo de [0, 1]) e prontos para serem plotados.

* Tamanho: O tamanho da entrada `n`.
* Tempo_Real_Norm: O tempo de execução medido, normalizado pelo valor máximo.
* O(n)_Norm, O(nlogn)_Norm, etc.: Os valores teóricos, também normalizados, para comparação visual da forma das curvas.

---

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.

## 👨‍💻 Autores

*Marcus Aurelius Costa de Paiva
*Luan Vinicius Alves Sampaio
*Wesley Kaillo Costa Sousa
