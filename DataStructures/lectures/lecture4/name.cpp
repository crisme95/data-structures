#include "name.h"


Name::Name(const std::string& fst, const std::string& lst) {
  first_ = fst;
  last_ = lst;
}


// operator<
bool operator< (const Name& left, const Name& right) {
  return left.last()<right.last() ||
    (left.last()==right.last() && left.first()<right.first());
}
// The output stream operator takes two arguments: the stream (e.g., cout) and the object
// to print.  It returns a reference to the output stream to allow a chain of output.
std::ostream& operator<< (std::ostream& ostr, const Name& n) {
  ostr << n.first() << " " << n.last();
  return ostr;
}