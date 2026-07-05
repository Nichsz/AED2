# Projeto AED2 - Compressão de Dados em Redes de Rádio Tático Militar (IoMT)

Este repositório contém a implementação prática desenvolvida para o projeto final da disciplina de **Algoritmos e Estruturas de Dados II (AED-II)**.

---

## 📝 Resumo do Projeto
O trabalho apresenta uma análise competitiva entre os algoritmos clássicos de compressão de dados sem perdas (*lossless*) **Lempel-Ziv-Welch (LZW)** de 12 bits e a **Codificação de Huffman**, aplicados ao cenário de **Internet de Coisas Militar (IoMT)** [sensors-26-01414.pdf, Cryptographic_Algorithms_with_Data_Shorter_than_th.pdf]. 

Avaliamos o desempenho de ambos os algoritmos na redução de payloads típicos de transmissões de rádio tático Ad-Hoc/LoRa (como coordenadas GPS, mensagens de texto estruturadas e telemetria militar) [sensors-26-01414.pdf]. O objetivo principal é diminuir o tempo de antena (*airtime*) das transmissões, resultando em **conservação de bateria dos dispositivos táticos portáteis** e na redução da probabilidade de detecção eletromagnética das tropas contra sistemas de guerra eletrônica inimigos (LPD - *Low Probability of Detection*) [sensors-26-01414.pdf, artigo-WPERF2018-Aceitacao.pdf].

---

## 👥 Integrantes do Grupo
Trabalho acadêmico desenvolvido em colaboração pelos integrantes:

*   **Integrante 1** - RA: `XXXXXX` (Desenvolvimento e Correção LZW)
*   **Integrante 2** - RA: `XXXXXX` (Desenvolvimento do Código Huffman)
*   **Integrante 3** - RA: `XXXXXX` (Estruturação e Coleta de Datasets)
*   **Integrante 4** - RA: `XXXXXX` (Planilha de Cálculos e Métricas)
*   **Integrante 5** - RA: `XXXXXX` (Escrita do Artigo SBC)
*   **Integrante 6** - RA: `XXXXXX` (Escrita do Artigo SBC)
*   **Integrante 7** - RA: `XXXXXX` (Revisão de Complexidade Big-O)
*   **Integrante 8** - RA: `XXXXXX` (Formatação LaTeX e Slides PDF)

---

## 🚀 Como Compilar e Executar os Programas LZW

O projeto possui dois códigos independentes em C++ padrão (ISO C++11): um para a **compressão** (nó transmissor) e outro para a **descompressão** (nó receptor) [sensors-26-01414.pdf, Cryptographic_Algorithms_with_Data_Shorter_than_th.pdf]. Ambos seguem o mesmo fluxo simples de execução por terminal.

### **1. Passo 1: Compressão (Nó Transmissor)**
Compila o compressor com otimização máxima (`-O3`) para realizar os testes de tempo de execução:
```bash
g++ -O3 compressor.cpp -o compressor
```

Execute o programa e digite o nome do arquivo original de texto que deseja compactar (ex: um arquivo da pasta de datasets):
```bash
./compressor
# Digite o arquivo de teste (ex: coordenadas_gps_grande.txt)
```
*   **Saída:** O programa gerará o arquivo binário compactado **`output.bin`** na mesma pasta.

---

### **2. Passo 2: Descompressão (Nó Receptor)**
Compila o descompressor com otimização máxima:
```bash
g++ -O3 decompressor.cpp -o decompressor
```

Execute o descompressor. Como a saída do compressor anterior é sempre `output.bin`, você digitará esse nome quando solicitado pelo terminal:
```bash
./decompressor
# Digite o arquivo a descompactar: output.bin
```
*   **Saída:** O programa lerá o binário, reconstruirá o dicionário dinamicamente em tempo de execução e gerará o arquivo original de texto totalmente restaurado (ex: `recovered_lzw.txt`), sem perda de nenhum byte (*Lossless* ✅) [sensors-26-01414.pdf].
