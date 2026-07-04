#include<iostream>
#include <fstream>
#include<string>
#include<queue>
#include<map>
#include <vector>
#include<chrono>
using namespace std;

struct tnode{
    unsigned char value;
    tnode* left,*right;
    tnode(unsigned char a,tnode* b,tnode* c){
        value=a;
        left=b;
        right=c;
    }

};
tnode* Huffman(map<unsigned char,int> &Simbols){
    if(Simbols.empty()) return nullptr;
    if(Simbols.size()==1){
        return new tnode((*(Simbols.begin())).first,nullptr,nullptr);
    }
    priority_queue<pair<int,tnode*>,vector<pair<int,tnode*>>,greater<pair<int,tnode*>>> pq;
    for(auto [key,value] : Simbols){
        tnode* t = new tnode(key,nullptr,nullptr);
        pq.push({value,t});
    }
    while (pq.size()>1) {
        pair<int,tnode*> t1 = pq.top();
        pq.pop();
        pair<int,tnode*> t2 = pq.top();
        pq.pop();
        tnode* t = new tnode('\0',t1.second,t2.second);
        pq.push({t1.first+t2.first,t});
    }
    return pq.top().second;
}

void spanHuffman(string currCode,tnode* t,map<unsigned char,string> &HuffmanTABLE){
    if(!t) return;
    if(!(t->left) && !(t->right)){
        HuffmanTABLE[t->value]=currCode;
    }
    spanHuffman(currCode + '0', t->left, HuffmanTABLE);
    spanHuffman(currCode + '1', t->right,HuffmanTABLE);
}


int main(){
    string archiveName = "";
    cin >> archiveName;

    // 2. MARCA O INÍCIO DO TEMPO TOTAL (INCLUI LEITURA DE ARQUIVO)
    auto start_total = chrono::high_resolution_clock::now();

    ifstream inFile(archiveName, ios::binary);
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

    // 3. MARCA O INÍCIO DO PROCESSAMENTO DO ALGORITMO DE HUFFMAN
    auto start_huffman = chrono::high_resolution_clock::now();


    map<unsigned char,int> Simbols;
    for(unsigned char i : buffer) Simbols[i]++;
    map<unsigned char,string> HuffmanTABLE;
    tnode* r= Huffman(Simbols);
    spanHuffman("", r, HuffmanTABLE);

    // 4. MARCA O FIM DO ALGORITMO PURE DE HUFFMAN (ANTES DA ESCRITA EM DISCO)
    auto end_huffman = chrono::high_resolution_clock::now();

    //opening output file
    ofstream outFile("output.bin", ios::binary);
    if (!outFile.is_open()) {
        cout << "error" << endl;
        return 1;
    }

    //sending header decompresser data
    int numSimbols = Simbols.size();
    outFile.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    outFile.write(reinterpret_cast<const char*>(&numSimbols), sizeof(numSimbols));
    for (auto const& par : Simbols) {
        outFile.write(reinterpret_cast<const char*>(&par.first), sizeof(par.first));
        outFile.write(reinterpret_cast<const char*>(&par.second), sizeof(par.second));
    }

    // sending compressed data
    unsigned char byte = 0; 
    int bit_count = 0;
    for(unsigned char c : buffer){
        string PACKEDMESSAGE = HuffmanTABLE[c];
        for (char c : PACKEDMESSAGE) {
            byte = byte << 1;
            if (c == '1') {
                byte = byte | 1;
            }
            bit_count++;
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

    // 5. MARCA O FIM DO TEMPO TOTAL
    auto end_total = chrono::high_resolution_clock::now();

    // 6. CALCULA OS INTERVALOS EM MILISSEGUNDOS
    chrono::duration<double, milli> duration_huffman = end_huffman - start_huffman;
    chrono::duration<double, milli> duration_total = end_total - start_total;

    // 7. EXIBE AS MÉTRICAS DE TEMPO PRÁTICO
    cout << "\n=========================================" << endl;
    cout << "Compressao Huffman concluida com sucesso!" << endl;
    cout << "Tempo do algoritmo (Arvore/Tabela): " << duration_huffman.count() << " ms" << endl;
    cout << "Tempo total (I/O de Disco + Algoritmo): " << duration_total.count() << " ms" << endl;
    cout << "=========================================" << endl;

    return 0;
}

