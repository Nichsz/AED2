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
    output_code.push_back(table[p]);
    return output_code;
}

int main(){
    string archiveName = "";
    cin >> archiveName;
    ifstream inFile(archiveName, ios::binary);

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

    auto start_lzw = chrono::high_resolution_clock::now();
    vector<int> output_code = encoding(buffer);
    auto end_lzw = chrono::high_resolution_clock::now();

    ofstream outFile("output.bin", ios::binary);
    if (!outFile.is_open()) {
        cout << "error" << endl;
        return 1;
    }
    
    unsigned char byte = 0; 
    int bit_count = 0;
    for (int code : output_code) {
        for (int i = 11; i >= 0; i--) {
            int bit = (code >> i) & 1;
            byte = (byte << 1) | bit;
            bit_count++;
            if (bit_count == 8) {
                outFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
                byte = 0;
                bit_count = 0;
            }
        }
    }

    int padding = 0;
    if (bit_count > 0) {
        padding = 8 - bit_count;
        byte = byte << padding;
        outFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }
    outFile.close();

    auto end_total = chrono::high_resolution_clock::now();
    chrono::duration<double,  milli> duration_lzw = end_lzw - start_lzw;
    chrono::duration<double, milli> duration_total = end_total - start_total;
    cout << "Tempo total de execucao: " << duration_total.count() << " ms" << endl;

    return 0;
}