/* ************************************************************************** */

#include <stdexcept>
#include <utility>

/* ************************************************************************** */

namespace lasd {

// Vector
/* ************************************************************************** */

// Constructors and Destructors

template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& container)
    : Vector(container.Size()) {  // delegating constructor
  unsigned long i = 0;
  container.Traverse([this, &i](const Data& data) {
    elements[i++] = data;
  });
}


template <typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& container)
    : Vector(container.Size()) {
  unsigned long i = 0;
  container.Map([this, &i](Data& data) {
    elements[i++] = std::move(data);
  });
}

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vec)
    : Vector(vec.size) {
  for (unsigned long i = 0; i < size; ++i) {
    elements[i] = vec.elements[i];
  }
}


template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
  std::swap(size, vec.size);
  std::swap(elements, vec.elements);
}

// Operators

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
  Vector<Data> temp{vec};       // Costruttore di copia
  std::swap(temp, *this);       // Scambia contenuti
  return *this;
}

template <typename Data>
Vector<Data> &Vector<Data>::operator=(Vector<Data> &&vec) noexcept {
  std::swap(size, vec.size);
  std::swap(elements, vec.elements);
  return *this;
}

template <typename Data>
bool Vector<Data>::operator==(const Vector<Data> &vec) const noexcept {
  if (size != vec.size) {
    return false;
  }

  for (unsigned long i = 0; i < size; i++) {
    if (elements[i] != vec[i]) {
      return false;
    }
  }
  return true;
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector<Data> &vec) const noexcept {
  return !(*this == vec);
}

template <typename Data>
const Data &Vector<Data>::operator[](unsigned long i) const {
  if (i >= size) {
    throw std::out_of_range("This Vector has not that many elements");
  }
  return elements[i];
}

template <typename Data>
Data &Vector<Data>::operator[](unsigned long i) {
  if (i >= size) {
    throw std::out_of_range("This Vector has not that many elements");
  }
  return elements[i];
}


// Overrided Methods

template <typename Data> inline void Vector<Data>::Clear() {
  delete[] elements;
  size = 0;
  elements = nullptr;
}

template <typename Data> void Vector<Data>::Resize(unsigned long s) {
  if (s == size) {
    return;
  }

  if (s == 0) {
    Clear();
    return;
  }

  Data *temp{new Data[s]{}};

  unsigned long min{std::min(s, size)};

  for (unsigned long i{0}; i < min; ++i)
    std::swap(elements[i], temp[i]);

  std::swap(elements, temp);
  delete[] temp;

  size = s;
}

template <typename Data> inline const Data &Vector<Data>::Front() const {
  if (size != 0)
    return elements[0];
  throw std::length_error("The Vector is empty");
}

template <typename Data> inline Data &Vector<Data>::Front() {
  if (size != 0)
    return elements[0];
  throw std::length_error("The Vector is empty");
}
template <typename Data> inline const Data &Vector<Data>::Back() const {
  if (size != 0)
    return elements[size - 1];
  throw std::length_error("The Vector is empty");
}
template <typename Data> inline Data &Vector<Data>::Back() {
  if (size != 0)
    return elements[size - 1];
  throw std::length_error("The Vector is empty");
}


/* ************************************************************************** */

template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& con) {
  if (this != &con) {
    SortableVector<Data> temp(con);  // Crea un oggetto temporaneo
    std::swap(*this, temp);  // Scambia i dati
  }
  return *this;
}

template <typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& con) noexcept {
  if (this != &con) {
    std::swap(this->size, con.size);
    std::swap(this->elements, con.elements);
  }
  return *this;
}

template <typename Data>
void Vector<Data>::Traverse(typename TraversableContainer<Data>::TraverseFun fun) const {
  for (unsigned long i = 0; i < size; ++i) {
    fun(elements[i]);
  }
}

template <typename Data>
void Vector<Data>::Map(typename MappableContainer<Data>::MapFun fun) {
  for (unsigned long i = 0; i < size; ++i) {
    fun(elements[i]);
  }
}


} // namespace lasd