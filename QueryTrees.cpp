#include "BinarySearchTree.h"
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
void PopulateQueryTree(TreeType &a_tree, string &db_filename) {
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
void TestQueryTree(TreeType &a_tree) {
    cout << "To exit the program type in quit." << endl;
    cout << "Sequence: ";
    string input;
    getline(cin, input);
    while (input != "quit") {
       SequenceMap to_find(input, "");
       SequenceMap *search_result = a_tree.find(to_find);
        if (search_result != nullptr) {
            cout << *search_result << endl;
        } else {
            cout << "Error: " + input + " was not found in the tree" << endl;
        }
        cout << "Sequence: ";
        getline(cin, input);
    }
}
// Sample main for program queryTrees
int
main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
        return 0;
    }
    string db_filename(argv[1]);
    string param_tree(argv[2]);
    cout << "Input filename is " << db_filename << endl;
    if (param_tree == "BST") {
        cout << "I will run the BST code" << endl;
        BinarySearchTree<SequenceMap> a_tree;
        PopulateQueryTree(a_tree, db_filename);
        TestQueryTree(a_tree);
    } else if (param_tree == "AVL") {
        cout << "I will run the AVL code" << endl;
        AvlTree<SequenceMap> a_tree;
        PopulateQueryTree(a_tree, db_filename);
        TestQueryTree(a_tree);
    } else {
        cout << "Unknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
    }
    return 0;
}
