#include "Seq.h"
using namespace std;

int main(int argc, char **argv) {
    // Q1
    #ifdef PCQ1
        string in_file1(argv[1]);
        string in_file2(argv[2]);
        Seq seq1(in_file1);
        seq1.display();
        Seq seq2(in_file2);
        seq2.display();
        cout << "======" << endl;
    #endif
    // Q2
    #ifdef PCQ2
        int a, b;
        cin >> a >> b;
        seq1 >> a;
        seq1.display();
        seq2 << b;
        seq2.display();
        Seq seq3 = Seq(-seq1);
        seq3.display();
        cout << "======" << endl;
    #endif
    // Q3
    #ifdef PCQ3
        Seq seq4 = seq1 * seq2;
        seq4.display();
        int M;
        cin >> M;
        Seq seq5 = seq4.mid_filter(M);
        seq5.display();
    #endif
    return 0;
}
