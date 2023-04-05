#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
using namespace std;
#define DEBUG 0
#define digest vector<bitset<32>>

class Parser
{
private:
    string inf, outf;

    void padding(string &s)
    {
        int size = s.size();
        while (size > 2048)
            size -= 2048;
        for (int i = size; i < 2048; i++)
            s.push_back('_');
    }
    bool *char2ASCII(char c)
    {
        // b[0] is MSB
        bool *b = new bool[8];
        if (c == '_') // padding
        {
            b[1] = b[3] = b[4] = b[5] = b[6] = b[7] = 1;
            b[0] = b[2] = 0;
        }
        else
        {
            int n = (int)c;
            for (int i = 7; i >= 0; i--, n /= 2)
                b[i] = n & 1;
        }
        return b;
    }
    void printASCII(bool *ASCII)
    {
        for (int i = 0; i < 8; i++)
            cout << ASCII[i];
        cout << endl;
    }

public:
    Parser(string _inf, string _outf) : inf(_inf), outf(_outf) {}
    vector<bitset<32>> *loadBitString()
    {
        vector<bitset<32>> *bitString = new vector<bitset<32>>;
        ifstream ifs(inf);
        string s;
        getline(ifs, s);
        padding(s);

        // convert string to ASCIIString
        int size = s.size(), cnt = 32;
        for (const auto &c : s)
        {
            if (cnt == 32)
            {
                cnt = 0;
                bitset<32> chunk;
                bitString->push_back(chunk);
            }
            bool *ASCII = char2ASCII(c);
            for (int i = 0; i < 8; i++)
                bitString->back().set(31 - cnt++, ASCII[i]);

            delete ASCII;
        }

        return bitString;
    }
    void outputDigests(vector<digest> *result)
    {
        ofstream ofs(outf);
        int size = result->size();

        // output top digest
        for (auto &chunk : result->back())
            ofs << chunk;
        ofs << endl;

        // output digests
        for (int i = 0; i < size - 1; i++)
        {
            for (auto &chunk : result->at(i))
                ofs << chunk;
            ofs << endl;
        }
        ofs.close();
    }
};

struct Operator
{
    bitset<32> NOT(bitset<32> X) { return ~X; }
    bitset<32> AND2(bitset<32> X, bitset<32> Y) { return X & Y; }
    bitset<32> XOR2(bitset<32> X, bitset<32> Y) { return X ^ Y; }
    bitset<32> XOR3(bitset<32> X, bitset<32> Y, bitset<32> Z) { return X ^ Y ^ Z; }
    bitset<32> RotR(bitset<32> X, int shift)
    {
        bool tmp;
        while (shift--)
        {
            tmp = X[0];
            X >>= 1;
            X[31] = tmp;
        }
        return X;
    }
    bitset<32> ADD2(bitset<32> X, bitset<32> Y) { return bitset<32>(X.to_ulong() + Y.to_ulong()); }
    bitset<32> ADD4(bitset<32> W, bitset<32> X, bitset<32> Y, bitset<32> Z) { return bitset<32>(W.to_ulong() + X.to_ulong() + Y.to_ulong() + Z.to_ulong()); }
    bitset<32> Ch(bitset<32> X, bitset<32> Y, bitset<32> Z)
    {
        // Ch(X, Y, Z) = (X AND Y ) XOR (~X AND Z)
        return XOR2(AND2(X, Y), AND2(NOT(X), Z));
    }
    bitset<32> Maj(bitset<32> X, bitset<32> Y, bitset<32> Z)
    {
        // Maj(X, Y, Z) = (X AND Y ) XOR (X AND Z) XOR (Y AND Z)
        return XOR3(AND2(X, Y), AND2(X, Z), AND2(Y, Z));
    }
};

class Hash
{
private:
    int index;
    Operator op;
    vector<bitset<32>> H;

    void reset_h(vector<bitset<32>> &h) { h = H; }
    digest to_digest(vector<bitset<32>> &h)
    {
        digest d;
        for (int i = 0; i < 8; i++)
            d.push_back(h[i]);
        return d;
    }
    void printIterLog(vector<bitset<32>> &h, bitset<32> &t1, bitset<32> &t2, bitset<32> &wi)
    {
        cout << endl;

        cout << "index = " << index << endl;
        cout << "w" << index << " = " << wi << endl;
        cout << "t1 = " << t1 << endl;
        cout << "t2 = " << t2 << endl;

        for (int i = 7; i >= 0; i--)
            cout << "h'[" << i << "] = " << h[i] << endl;

        cout << endl;
    }
    void iteration(vector<bitset<32>> &h, bitset<32> &wi)
    {
        bitset<32> t1 = op.ADD4(h[7], wi, op.Ch(h[4], h[5], h[6]),
                                op.XOR3(op.RotR(h[4], 6), op.RotR(h[4], 11), op.RotR(h[4], 25)));
        bitset<32> t2 = op.ADD2(op.XOR3(op.RotR(h[0], 2), op.RotR(h[0], 13), op.RotR(h[0], 22)), op.Maj(h[0], h[1], h[2]));
        h[7] = h[6];
        h[6] = h[5];
        h[5] = h[4];
        h[4] = op.ADD2(h[3], t1);
        h[3] = h[2];
        h[2] = h[1];
        h[1] = h[0];
        h[0] = op.ADD2(t1, t2);

        if (DEBUG)
            printIterLog(h, t1, t2, wi);

        index++;
    }
    void addTopDegest(vector<digest> *D)
    {
        vector<bitset<32>> h = H;
        index = 0;
        for (auto &d : *D)
            for (auto &wi : d)
                iteration(h, wi);
        D->push_back(to_digest(h));

        if (DEBUG)
        {
            cout << "digest = ";
            for (auto &it : D->back())
                cout << it;
            cout << endl;
        }
    }

public:
    Hash()
    {
        H.push_back(bitset<32>(0b01101010000010011110011001100111));
        H.push_back(bitset<32>(0b10111011011001111010111010000101));
        H.push_back(bitset<32>(0b00111100011011101111001101110010));
        H.push_back(bitset<32>(0b10100101010011111111010100111010));
        H.push_back(bitset<32>(0b01010001000011100101001001111111));
        H.push_back(bitset<32>(0b10011011000001010110100010001100));
        H.push_back(bitset<32>(0b00011111100000111101100110101011));
        H.push_back(bitset<32>(0b01011011111000001100110100011001));
    }
    vector<digest> *hashing(vector<bitset<32>> *bitString)
    {
        vector<digest> *D = new vector<digest>;
        vector<bitset<32>> h = H;
        index = 0;
        for (auto &wi : *bitString)
        {
            iteration(h, wi);
            if (index == 512)
            {
                index = 0;
                D->push_back(to_digest(h));

                if (DEBUG)
                {
                    cout << "digest = ";
                    for (auto &it : D->back())
                        cout << it;
                    cout << endl;
                }

                reset_h(h);
            }
        }
        addTopDegest(D);
        return D;
    }
};

int main(int argc, char **argv)
{
    Parser ps(argc == 1 ? "test1.txt" : argv[1], argc == 1 ? "output" : argv[2]);
    Hash hs;

    vector<bitset<32>> *bitString = ps.loadBitString();
    vector<digest> *result = hs.hashing(bitString);
    ps.outputDigests(result);

    return 0;
}