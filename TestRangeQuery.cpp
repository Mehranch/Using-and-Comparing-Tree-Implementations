#include "AvlTree.h"
#include "SequenceMap.cpp"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Get enzyme acronym
string GetEnzymeAcronym(string &db_line) {
    size_t loc = db_line.find("/");
    string ret = db_line.substr(0, loc);
    //remove acronym
    db_line = db_line.substr(loc + 1);
    return ret;
}

// Get recognition sequence
bool GetNextRecognitionSequence(string &db_line, string &a_reco_seq) {
    size_t loc = db_line.find("/");
    if (loc == string::npos || loc == db_line.size() - 1) {
        return false;
    }

    a_reco_seq = db_line.substr(0, loc);
    //remove sequence
    db_line = db_line.substr(loc + 1);

    return true;
}

template<typename TreeType>
void PopulateRangeTree(TreeType &a_tree, string &db_filename) {
    string db_line;
    fstream fin(db_filename.c_str());
    for (int i = 0; i < 10; i++)
        getline(fin, db_line);
    // read file line by line
    while (getline(fin, db_line)) {
        string an_enz_acro = GetEnzymeAcronym(db_line);

        string a_reco_seq;
        while (GetNextRecognitionSequence(db_line, a_reco_seq)) {
            SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
            a_tree.insert(new_sequence_map);
        }
    }
    fin.close();
}

template <typename TreeType>
void TestRangeTree(TreeType &a_tree, const string &str1, const string &str2) {
    SequenceMap s1(str1, "");
    SequenceMap s2(str2, "");

    a_tree.range(s1, s2);
}

// Sample main for program testTrees
int
main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <databasefilename> <string> <string2>" << endl;
        return 0;
    }
    string db_filename(argv[1]);
    string str1(argv[2]);
    string str2(argv[3]);
    cout << "Input file is " << db_filename << " ";
    cout << "String 1 is " << str1 << "   and string 2 is " << str2 << endl;

    AvlTree<SequenceMap> a_tree;
    PopulateRangeTree(a_tree, db_filename);

    TestRangeTree(a_tree, str1, str2);

    return 0;
}
