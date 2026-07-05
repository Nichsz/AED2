#include<iostream>
#include<chrono>
#include <fstream>
#include<string>
#include<queue>
#include<map>
#include <vector>
#include <unordered_map>
using namespace std;

vector<unsigned char> decoding(const vector<int>& op)
{
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    
    vector<unsigned char> output_bytes;
    if (op.empty()) return output_bytes;
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];

    for (char ch : s) {
        output_bytes.push_back(static_cast<unsigned char>(ch));
    }

    int count = 256;
    for (int i = 0; i < op.size() - 1; i++) {
        n = op[i+1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        for (char ch : s) {
            output_bytes.push_back(static_cast<unsigned char>(ch));
        }
        c = "";
        c += s[0];

        if (count < 4096) {
            table[count] = table[old] + c;
            count++;
        }
        old = n;
    }
    return output_bytes;
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

    vector<int> input_codes;
    int current_code = 0;
    int bit_count = 0;

    for (unsigned char byte : buffer) {
        for (int i = 7; i >= 0; i--) {
            int bit = (byte >> i) & 1;
            current_code = (current_code << 1) | bit;
            bit_count++;

            if (bit_count == 12) {
                input_codes.push_back(current_code);
                current_code = 0;
                bit_count = 0;
            }
        }
    }

    auto start_lzw = chrono::high_resolution_clock::now();
    vector<unsigned char> original_bytes = decoding(input_codes);
    auto end_lzw = chrono::high_resolution_clock::now();

    ofstream outFile("restored_output.txt", ios::binary);
    if (!outFile.is_open()) {
        cout << "error" << endl;
        return 1;
    }

    outFile.write(reinterpret_cast<const char*>(original_bytes.data()), original_bytes.size());
    outFile.close();

    auto end_total = chrono::high_resolution_clock::now();
    chrono::duration<double,  milli> duration_lzw = end_lzw - start_lzw;
    chrono::duration<double, milli> duration_total = end_total - start_total;

    cout << "Tempo total de execucao: " << duration_total.count() << " ms" << endl;

    return 0;
}