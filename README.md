# Projeto AED2 - Análise Comparativa de Compressão: LZW vs. Huffman em Cenários de Comunicação Tática (IoMT)

Este repositório contém a implementação prática e os dados experimentais desenvolvidos para o projeto final da disciplina de Algoritmos e Estruturas de Dados II (AED-II) ministrada pelo professor Carlo Kleber da Silva Rodrigues.

---

## Resumo do Projeto
O trabalho consiste em uma análise experimental comparativa entre os algoritmos clássicos de compressão de dados sem perdas (*lossless*): Lempel-Ziv-Welch (LZW) de 12 bits e a Codificação de Huffman. 

Para avaliar os algoritmos em um cenário de aplicação realista, simulamos fluxos de dados típicos de uma rede de Internet de Coisas Militar (IoMT - Internet of Military Things) e de Comunicação Tática. Avaliamos o desempenho dos algoritmos sobre massas de dados de sensoriamento e transmissão tática, tais como:
*   **Mensagens e relatórios táticos de texto** (`mensagens.txt`, `relatorio.txt`).
*   **Coordenadas de posicionamento geográfico** (`coordenadas.txt`).
*   **Leituras de telemetria de mísseis e biometria de combate** (`telemetria_misseis.txt`, `biometria_soldado.txt`).
*   **Padrões de repetição estruturada e alfabeto reduzido** (`mapa_satelite.txt`, `codebook.txt`, `morse_binario.txt`) testados em três diferentes escalas de tamanho (Pequeno: ~6 KB, Médio: 251 KB, Grande: 3001 KB).

O objetivo principal da compressão neste cenário é encurtar o tamanho físico das mensagens antes da transmissão. Na prática militar, pacotes menores reduzem o tempo de rádio ativo no ar (*airtime*), resultando em conservação de bateria dos dispositivos táticos de campo e diminuindo a pegada eletromagnética das tropas contra interceptações de guerra eletrônica inimiga (LPD - *Low Probability of Detection*).

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
