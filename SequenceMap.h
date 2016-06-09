#ifndef SEQUENCE_MAP_H_
#define SEQUENCE_MAP_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SequenceMap {
private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;
public:
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro);
    bool operator<(const SequenceMap &rhs) const;
    friend ostream& operator<<(ostream &stream, SequenceMap &to_display);
    void merge(const SequenceMap &other_sequence);
};

#endif // SEQUENCE_MAP_H_
