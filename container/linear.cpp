
namespace lasd {

// Linear Container
/* ************************************************************************** */

// Operators

template <typename Data>
inline bool LinearContainer<Data>::operator==(
    const LinearContainer<Data> &con) const noexcept {
  if (this->size != con.size) {
    return false;
  }

  for (unsigned long i = 0; i < this->size; ++i) {
    if ((*this)[i] != con[i]) {
      return false;
    }
  }
  return true;
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(
    const LinearContainer<Data> &con) const noexcept {
  return !(*this == con);
}

// Specific Methods

template <typename Data>
inline const Data &LinearContainer<Data>::Front() const {
  if (this->size == 0) {
    throw std::length_error("Empty structure.");
  }
  return (*this)[0];
}

template <typename Data> 
inline  Data &MutableLinearContainer<Data>::Front() {
  if (this->size == 0) {
    throw std::length_error("Empty structure.");
  }
  return (*this)[0];
}

template <typename Data>
inline const Data &LinearContainer<Data>::Back() const {
  if (this->size == 0) {
    throw std::length_error("Empty structure.");
  }
  return (*this)[this->size - 1];
}

template <typename Data> 
inline Data &MutableLinearContainer<Data>::Back() {
  if (this->size == 0) {
    throw std::length_error("Empty structure.");
  }
  return (*this)[this->size - 1];
}
// Overrided Methods

template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun func) const {
  PreOrderTraverse(func);
}

template <typename Data>
inline void
LinearContainer<Data>::PreOrderTraverse(const TraverseFun func) const {
  for (unsigned long i = 0; i < this->size; ++i) {
    func((*this)[i]);
  }
}

template <typename Data>
inline void
LinearContainer<Data>::PostOrderTraverse(const TraverseFun func) const {

  for (unsigned long i = this->size; i > 0;) {
    func((*this)[--i]);
  }
}

template <typename Data> 
inline void MutableLinearContainer<Data>::Map(MapFun func) {
  PreOrderMap(func);
}

template <typename Data>
inline void MutableLinearContainer<Data>::PreOrderMap(MapFun func) {
  for (unsigned long i = 0; i < this->size; ++i) {
    func((*this)[i]);
  }
}

template <typename Data>
inline void MutableLinearContainer<Data>::PostOrderMap(MapFun func) {
  for (unsigned long i = this->size; i > 0;) {
    func((*this)[--i]);
  }
}

/* ************************************************************************** */

// Sortable Linear Container
/* ************************************************************************** */

// Operators

template <typename Data>
inline bool SortableLinearContainer<Data>::operator==(
    const SortableLinearContainer<Data> &con) const noexcept {
  return LinearContainer<Data>::operator==(con);
}

template <typename Data>
inline bool SortableLinearContainer<Data>::operator!=(
    const SortableLinearContainer<Data> &con) const noexcept {
  return !(*this == con);
}

// Specific Methods

template <typename Data>
inline void SortableLinearContainer<Data>::Sort() noexcept {
  insertionSort(0, this->size - 1);
}

template <typename Data>
void SortableLinearContainer<Data>::insertionSort(unsigned long p,
                                                  unsigned long r) noexcept {
  Data currVal;
  unsigned long t;

  for (unsigned long i = p + 1; i <= r; i++) {

    currVal = (*this)[i];
    t = i;
    while (t > p && (*this)[t - 1] > currVal) {
      (*this)[t] = (*this)[t - 1];
      --t;
    }
    (*this)[t] = currVal;
  }
}

/* ************************************************************************** */
} // namespace lasd