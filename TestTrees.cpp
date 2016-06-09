#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SequenceMap.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
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
void PopulateTestTree(TreeType &a_tree, string &db_filename) {
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

template<typename TreeType>
void displayLogistics(TreeType &a_tree) {
    int size = a_tree.size();
    int depth = a_tree.depth();
    double average_depth = (double) depth / size;
    cout << "Size: " << size << endl;
    cout << "Average Depth: " << average_depth << endl;
    cout << "Average Depth to Log2N Ratio: " << average_depth / log2(size) << endl;
    cout << endl;
}

void readSequences(vector<SequenceMap> &sequences, const string &sequence_file) {
    fstream fin(sequence_file.c_str());
    string line;
    while (getline(fin, line)) {
        SequenceMap s(line, "");
        sequences.push_back(s);
    }
    fin.close();
}

template <typename TreeType>
void TestTestTree(TreeType &a_tree, const string &sequence_file) {
    vector<SequenceMap> sequences;
    readSequences(sequences, sequence_file);

    displayLogistics(a_tree);

    // (Successes, Queries)
    int successful_query = 0;
    int total_query = 0;
    int successful_removal = 0;
    int total_removal = 0;

    for (size_t i = 0; i < sequences.size(); i++) {
        pair<SequenceMap*, int> result = a_tree.find_count(sequences[i]);
        if (result.first != nullptr) {
            successful_query++;
        }
        total_query += result.second;
    }
    cout << "Total Successful Queries: " << successful_query << endl;
    cout << "Total Recursive Calls: " << total_query << endl;
    cout << "Average Number of Recursion Calls: " << (double) total_query / sequences.size() << endl;
    cout << endl;

    for (size_t i = 1; i < sequences.size(); i += 2) {
        bool result = a_tree.remove_count(sequences[i]);
        if (result) {
            successful_removal++;
        }
        total_removal += a_tree.get_remove_calls();
    }

    cout << "Total Successful Removes: " << successful_removal << endl;
    cout << "Total Recursive Calls: " << total_removal << endl;
    cout << "Average Number of Recursion Calls: " << (double) total_removal / sequences.size() << endl;
    cout << endl;

    displayLogistics(a_tree);
}

// Sample main for program testTrees
int
main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
        return 0;
    }
    string db_filename(argv[1]);
    string query_filename(argv[2]);
    string param_tree(argv[3]);
    cout << "Input file is " << db_filename << ", and query file is " << query_filename << endl;
    if (param_tree == "BST") {
        cout << "I will run the BST code " << endl;
        // Insert code for testing a BST tree.
        BinarySearchTree<SequenceMap> a_tree;
        PopulateTestTree(a_tree, db_filename);
        TestTestTree(a_tree, query_filename);
    } else if (param_tree == "AVL") {
        cout << "I will run the AVL code " << endl;
        // Insert code for testing an AVL tree.
        AvlTree<SequenceMap> a_tree;
        PopulateTestTree(a_tree, db_filename);
        TestTestTree(a_tree, query_filename);
    } else {
        cout << "Unknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
    }
    return 0;
}
