# Projeto AED2 - Compressão de Dados em Redes de Rádio Tático Militar (IoMT)

Este repositório contém a implementação prática desenvolvida para o projeto final da disciplina de Algoritmos e Estruturas de Dados II (AED-II) ministrada pelo professor Carlo Kleber da Silva Rodrigues.

---

# Resumo do Projeto
O trabalho apresenta uma análise competitiva entre os algoritmos clássicos de compressão de dados sem perdas (*lossless*) Lempel-Ziv-Welch (LZW) de 12 bits e a Codificação de Huffman, aplicados ao cenário de Internet de Coisas Militar (IoMT). 
Avaliamos o desempenho de ambos os algoritmos na redução de payloads típicos de transmissões de rádio tático Ad-Hoc/LoRa (como coordenadas GPS, mensagens de texto estruturadas e telemetria militar). O objetivo principal é diminuir o tempo de antena (*airtime*) das transmissões, resultando em conservação de bateria dos dispositivos táticos portáteis e na redução da probabilidade de detecção eletromagnética das tropas contra sistemas de guerra eletrônica inimigos (LPD - *Low Probability of Detection*).

---

## Integrantes do Grupo
Trabalho acadêmico desenvolvido em colaboração pelos integrantes:

*   **Integrante 1** - Carlos Eduardo Finatti Caldas RA: `11202320384` 
*   **Integrante 2** - Gabriela Jacintho Perez RA: `11202421338` 
*   **Integrante 3** - João Guilherme Caetano de Andrade RA: `11202321249` 
*   **Integrante 4** - Júlia Muniz Carvalho RA: `11202421988` 
*   **Integrante 5** - Leonardo Pavlavicius Estigarriba RA: `11202230855` 
*   **Integrante 6** - Lucas Fernandes Ataide RA: `11202421363` 
*   **Integrante 7** - Luís Emílio Gonçalves Dias RA: `11202421308` 
*   **Integrante 8** - Nicholas Fernandez Garcia RA: `11202421369`

---

## Como Compilar e Executar os Programas LZW

O projeto possui dois códigos independentes em C++ padrão: um para a compressão e outro para a descompressão. Ambos seguem o mesmo fluxo simples de execução por terminal.

### Passo 1: Compressão
Compila o compressor (lzw.cpp ou huffman.cpp) para realizar os testes de tempo de execução:
```bash
g++ compressor.cpp -o compressor
```

Execute o programa e digite o nome do arquivo original de texto que deseja compactar (ex: um arquivo da pasta de datasets):
```bash
./compressor
# Digite o arquivo de teste (ex: coordenadas.txt)
```
*   Saída: O programa gerará o arquivo binário compactado `output.bin` na mesma pasta.

---

### Passo 2: Descompressão
Compila o descompressor (lzw_dec.cpp ou huffman_dec.cpp):
```bash
g++ decompressor.cpp -o decompressor
```

Execute o descompressor. Como a saída do compressor anterior é sempre `output.bin`, você digitará esse nome quando solicitado pelo terminal:
```bash
./decompressor
# Digite o arquivo a descompactar: output.bin
```
*   Saída: O programa lerá o binário, reconstruirá o arquivo original de texto totalmente restaurado (ex: `recovered_output.txt`), sem perda de nenhum byte.
