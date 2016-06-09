#include "SequenceMap.h"

SequenceMap::SequenceMap(const string &a_rec_seq, const string &an_enz_acro) {
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
}

bool SequenceMap::operator<(const SequenceMap &rhs) const {
    return recognition_sequence_ < rhs.recognition_sequence_;
}

ostream& operator<<(ostream &stream, SequenceMap &to_display) {
    stream << to_display.recognition_sequence_ << " : ";
    for (size_t i = 0; i < to_display.enzyme_acronyms_.size(); i++) {
        stream << to_display.enzyme_acronyms_[i] << " ";
    }
    return stream;
}

void SequenceMap::merge(const SequenceMap &other_sequence) {
    enzyme_acronyms_.insert(enzyme_acronyms_.end(),
                            other_sequence.enzyme_acronyms_.begin(),
                            other_sequence.enzyme_acronyms_.end());
}
