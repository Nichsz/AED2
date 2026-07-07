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

int main(){
    string archiveName = "";
    cin >> archiveName;

    auto start_total = chrono::high_resolution_clock::now();

    ifstream inFile(archiveName, ios::binary);
    if (!inFile.is_open()) {
        cout << "error" << endl;
        return 1;
    }

    streamsize sz;
    inFile.read(reinterpret_cast<char*>(&sz), sizeof(sz));

    int numSimbols;
    inFile.read(reinterpret_cast<char*>(&numSimbols), sizeof(numSimbols));

    map<unsigned char,int> Simbols;
    for(int i = 0; i < numSimbols; i++){
        unsigned char key;
        int value;
        inFile.read(reinterpret_cast<char*>(&key), sizeof(key));
        inFile.read(reinterpret_cast<char*>(&value), sizeof(value));
        Simbols[key] = value;
    }

    auto start_huffman = chrono::high_resolution_clock::now();

    tnode* r = Huffman(Simbols);

    auto end_huffman = chrono::high_resolution_clock::now();

    ofstream outFile("restoured_output.bin", ios::binary);
    if (!outFile.is_open()) {
        cout << "error" << endl;
        return 1;
    }

    tnode* curr = r;
    unsigned char byte = 0;
    streamsize decoded_bytes = 0;

    if (r) {
        if (!r->left && !r->right) {
            while (decoded_bytes < sz && inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
                for(int i = 7; i >= 0; i--){
                    outFile.write(reinterpret_cast<const char*>(&r->value), sizeof(r->value));
                    decoded_bytes++;
                    if(decoded_bytes == sz) break;
                }
            }
        } else {
            while (decoded_bytes < sz && inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
                for (int i = 7; i >= 0; i--) {
                    if ((byte >> i) & 1) {
                        curr = curr->right;
                    } else {
                        curr = curr->left;
                    }

                    if (!(curr->left) && !(curr->right)) {
                        outFile.write(reinterpret_cast<const char*>(&curr->value), sizeof(curr->value));
                        decoded_bytes++;
                        curr = r;
                        if (decoded_bytes == sz) break;
                    }
                }
            }
        }
    }

    inFile.close();
    outFile.close();

    auto end_total = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration_huffman = end_huffman - start_huffman;
    chrono::duration<double, milli> duration_total = end_total - start_total;
    cout << "Tempo total (I/O de Disco + Algoritmo): " << duration_total.count() << " ms" << endl;

    return 0;
}
