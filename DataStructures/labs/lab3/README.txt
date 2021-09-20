Checkpoint 2:
- Added "#include <algorithm>" to fix "std::sort" not being recognized, roads.cpp was then able to compile
- point.cpp was able to compile with no changes
- line.cpp wasn't able to compile because point.h was being redefined so I commented it out of line.cpp, it was then able to compile
- While running through all the input files, they all gave back "Segmentation fault (core dumped)"

Checkpoint 3:
- Changed unsigned int to int in line 38 of roads.cpp because the answer could never be negative because of that
- Changed int to unsigned int in line 32 of roads.cpp because of the compiler warning
- Changed the if statements in line.cpp to just return false if the first if statement wasn't true
- Changed the return for compute_slope function of point.cpp to answer variable because it was going unused
- Changed gradient *-1 to gradient = -gradient because of compiler warning saying it did nothing


