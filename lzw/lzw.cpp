#include<iostream>
#include<chrono>
#include <fstream>
#include<string>
#include<queue>
#include<map>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> encoding(const vector<unsigned char>& s1)
{
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }
    
    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;

    for (int i = 0; i < s1.size(); i++) {
        if (i != s1.size() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {

            output_code.push_back(table[p]);
            if (code < 4096) { 
                table[p + c] = code;
                code++;
            }
            p = c;
        }
        c = "";
    }
    //cout << p << "\t" << table[p] << endl;
    output_code.push_back(table[p]);
    return output_code;
}

int main(){
    string archiveName = "";
    cin >> archiveName;
    ifstream inFile(archiveName, ios::binary);

    // 1. Marca o início do cronômetro global
    auto start_total = chrono::high_resolution_clock::now();

    if (!inFile.is_open()) {
        cout << "error" << endl;
        return 1;
    }
    
    inFile.seekg(0, ios::end);
    streamsize sz = inFile.tellg();
    inFile.seekg(0, ios::beg);

    vector<unsigned char> buffer(sz);
    inFile.read(reinterpret_cast<char*>(buffer.data()), sz);
    inFile.close();
    // 2. Se quiser medir APENAS a função de compressão LZW pura:
    auto start_lzw = chrono::high_resolution_clock::now();
    vector<int> output_code = encoding(buffer);
    auto end_lzw = chrono::high_resolution_clock::now();

    //opening output file
    ofstream outFile("output.bin", ios::binary);
    if (!outFile.is_open()) {
        cout << "error" << endl;
        return 1;
    }
    
    unsigned char byte = 0; 
    int bit_count = 0;
    for (int code : output_code) {
        // LZW padrão usa 12 bits. Vamos ler do bit mais significativo (11) ao menos significativo (0)
        for (int i = 11; i >= 0; i--) {
            // Extrai o bit atual do código LZW
            int bit = (code >> i) & 1;
            
            // Empurra o byte atual para a esquerda e adiciona o bit
            byte = (byte << 1) | bit;
            bit_count++;
            
            // Quando juntar 8 bits, grava 1 byte no arquivo
            if (bit_count == 8) {
                outFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
                byte = 0;
                bit_count = 0;
            }
        }
    }

    //padding the data
    int padding = 0;
    if (bit_count > 0) {
        padding = 8 - bit_count;
        byte = byte << padding;
        outFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }
    outFile.close();

    // 3. Marca o fim do cronômetro global
    auto end_total = chrono::high_resolution_clock::now();

    // 4. Calcula as diferenças (em milissegundos)
    chrono::duration<double,  milli> duration_lzw = end_lzw - start_lzw;
    chrono::duration<double, milli> duration_total = end_total - start_total;

    // 5. Exibe os resultados na tela
    cout << "\n=========================================" << endl;
    cout << "Compressao concluida com sucesso!" << endl;
    cout << "Tempo apenas do LZW: " << duration_lzw.count() << " ms" << endl;
    cout << "Tempo total de execucao: " << duration_total.count() << " ms" << endl;
    cout << "=========================================" << endl;

    return 0;
}