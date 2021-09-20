#ifndef jagged_array_h_
#define jagged_array_h_

template <class T>
class JaggedArray
{
public:
  // Constructor
  JaggedArray(int i);
  JaggedArray(const JaggedArray &v) { copy(v); };
  JaggedArray &operator=(const JaggedArray &v);
  ~JaggedArray()
  {
    for (int i = 9; i < numBins_; ++i)
    {
      if (numElementsInBin_[i] > 1)
      {
        delete[] bins_[i];
      }
    }
    delete bins_;
  }

  // Accessors
  int numElements() const { return numElements_; };
  int numBins() const { return numBins_; };
  int numElementsInBin(int i) const { return numElementsInBin_[i]; };
  T getElement(int i, int n) const { return bins_[i][n]; };
  bool isPacked() const { return isPacked_; };

  // Modifiers
  void addElement(int i, const T &t);
  void removeElement(int i, int n);
  void clear();
  void print();
  void pack() { isPacked_ = true; };
  void unpack() { isPacked_ = false; };

private:
  // Member functions
  void copy(const JaggedArray<T> &v);

  // Member variables
  T **bins_;
  int numBins_;
  int numElements_;
  int *numElementsInBin_;
  bool isPacked_;
};

// Initializes empty array with specified number of bins
// and also sets the default values of the variables
template <class T>
JaggedArray<T>::JaggedArray(int i)
{
  numBins_ = i;
  numElements_ = 0;
  isPacked_ = false;
  bins_ = new T *[i];
  numElementsInBin_ = new int[i]{0};
}

// Creates a copy of the given array
template <class T>
void JaggedArray<T>::copy(const JaggedArray<T> &v)
{
  this->numBins_ = v.numBins_;
  this->numElements_ = v.numElements_;
  this->isPacked_ = v.isPacked_;
  this->bins_ = new T *[this->numBins_];
  this->numElementsInBin_ = new int[this->numBins_]{0};

  // Copies all the data
  for (int i = 0; i < this->numBins_; ++i)
  {
    this->bins_[i] = v.bins_[i];
    this->numElementsInBin_[i] = v.numElementsInBin_[i];
  }
}

// Assigns one array to another, avoids duplicates
template <class T>
JaggedArray<T> &JaggedArray<T>::operator=(const JaggedArray<T> &v)
{
  if (this != &v)
  {
    for (int i = 0; i < numBins_; ++i){
      if (numElementsInBin_[i] > 1){
        delete[] bins_[i];
      }
    }
    delete bins_;
    this->copy(v);
  }
  return *this;
}

// Adds element to specified bin
template <class T>
void JaggedArray<T>::addElement(int i, const T &t)
{
  if (isPacked_ == false)
  {
    // If the bin hasn't been filled yet
    // this creates one then adds the element
    if (numElementsInBin_[i] == 0)
    {
      numElements_ += 1;
      numElementsInBin_[i] += 1;
      bins_[i] = new T[numElementsInBin_[i]]{t};
    }

    // Creates a temp array that replaces
    // the previous array to fit new element
    else
    {
      numElements_ += 1;
      numElementsInBin_[i] += 1;
      T *new_bins_ = new T[numElementsInBin_[i]];

      // Copies each element from previous array
      // into the temp array
      for (int n = 0; n < numElementsInBin_[i] - 1; ++n)
      {
        new_bins_[n] = bins_[i][n];
      }
      delete[] bins_[i];                      // Delete old array
      bins_[i] = new_bins_;                   // Copy new array
      bins_[i][numElementsInBin_[i] - 1] = t; // Insert element at end of array
    }
  }
  else
  {
    std::cerr << "Tried editing JaggedArray in packed mode." << std::endl;
    exit(1);
  }
}

// Removes element in the specified bin and
// and position in that bin
template <class T>
void JaggedArray<T>::removeElement(int i, int n)
{
  if (isPacked_ == false)
  {
    // If there are more than one element
    // in the bin, everything gets shifted over
    if (numElementsInBin_[i] > 1)
    {
      numElements_ -= 1;
      numElementsInBin_[i] -= 1;

      // Shifts all the items down, copying
      // over the element that needs to be removed
      for (int j = n; n < numElementsInBin_[i] + 1; ++n)
      {
        bins_[i][j] = bins_[i][j + 1];
      }
      T *new_bins_ = new T[numElementsInBin_[i]];

      // Copies all elements from edited array into
      // temp array with the right size
      for (int k = 0; k < numElementsInBin_[i]; ++k)
      {
        new_bins_[k] = bins_[i][k];
      }
      delete[] bins_[i];    // Delete old array
      bins_[i] = new_bins_; // Copy new array
    }

    // If the number of elements in the bin
    // is equal to one, just delete the
    else if (numElementsInBin_[i] == 1)
    {
      delete[] bins_[i]; // Just deletes the array since nothing is in there
      numElements_ -= 1;
      numElementsInBin_[i] = 0;
    }
  }
  else
  {
    std::cerr << "Tried editing JaggedArray in packed mode." << std::endl;
    exit(1);
  }
}

// Clears the array and sets everything
// to their default values except if
// it's packed or unpacked
template <class T>
void JaggedArray<T>::clear()
{
  if (isPacked_ == false)
  {
    delete[] bins_;
    bins_ = new T *[numBins_];
    delete[] numElementsInBin_;
    numElementsInBin_ = new int[numBins_]{0};
    numElements_ = 0;
  }
  else
  {
    std::cerr << "Tried editing JaggedArray in packed mode." << std::endl;
    exit(1);
  }
}

// Prints out the array depending on
// if it's packed or unpacked
template <class T>
void JaggedArray<T>::print()
{
  if (isPacked_ == true)
  {
    std::cout << "packed JaggedArray" << std::endl;
    std::cout << "num_bins: " << numBins_ << std::endl;
    std::cout << "num_elements: " << numElements_ << std::endl;
    unsigned int offsets = 0;
    std::cout << "offsets: " << offsets << " ";

    // Prints out the offsets
    for (int i = 0; i < numBins_; ++i)
    {
      offsets += numElementsInBin_[i];
      std::cout << offsets << " ";
    }
    std::cout << std::endl;

    std::cout << " values: ";
    // Prints out the values
    for (int i = 0; i < numBins_; ++i)
    {
      for (int n = 0; n < numElementsInBin_[i]; ++n)
      {
        std::cout << bins_[i][n] << " ";
      }
    }
    std::cout << std::endl;
  }
  else if (isPacked_ == false)
  {
    std::cout << "unpacked JaggedArray" << std::endl;
    std::cout << "num_bins: " << numBins_ << std::endl;
    std::cout << "num_elements: " << numElements_ << std::endl;

    // Prints out the counts
    std::cout << "counts: ";
    for (int i = 0; i < numBins_; ++i)
    {
      std::cout << numElementsInBin_[i] << " ";
    }
    std::cout << std::endl;

    // Prints out the values
    for (int i = 0; i < numBins_; ++i)
    {
      if (numElementsInBin_[i] > 0)
      {
        std::cout << " Bin " << (i + 1) << ": ";
        for (int n = 0; n < numElementsInBin_[i]; ++n)
        {
          std::cout << bins_[i][n] << " ";
        }
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

#endif