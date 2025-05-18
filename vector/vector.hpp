
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : public virtual ResizableContainer<Data>,
               public virtual MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size;

  Data *elements = nullptr;

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const unsigned long initSize) { // A vector with a given initial dimension
   size = initSize;
   elements = new Data[initSize]();
};

  Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data> &);

  // Move constructor
  Vector(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector() noexcept { delete[] elements; };

  /* ************************************************************************ */

  // Copy assignment
  inline Vector<Data>& operator=(const Vector<Data> &);

  // Move assignment
  inline Vector<Data>& operator=(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data> &) const noexcept;
  inline bool operator!=(const Vector<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
  inline Data& operator[](unsigned long index) override;              

  // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data& Front() override;              

  // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data& Back() override;              

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // Override LinearContainer member (must throw std::out_of_range when out of range)
  inline const Data &operator[](unsigned long) const override;

  // Override LinearContainer member (must throw std::length_error when empty)
  inline const Data &Front() const override;

  // Override LinearContainer member (must throw std::length_error when empty)
  inline const Data &Back() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  // Override ResizableContainer member
  void Resize(unsigned long new_size) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // Override ClearableContainer member
  inline void Clear() override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : public virtual Vector<Data>,
                       public virtual SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  // A vector with a given initial dimension
  inline SortableVector(unsigned long initSize) : Vector<Data>(initSize) {};

  // A vector obtained from a TraversableContainer
  inline SortableVector(const TraversableContainer<Data> &container) : Vector<Data>(container) {};

  // A vector obtained from a MappableContainer
  inline SortableVector(MappableContainer<Data> &&container) 
     : Vector<Data>::Vector(std::move(container)) {};

  /* ************************************************************************ */

  // Copy constructor
  inline SortableVector(const SortableVector<Data>& con)
    : Vector<Data>(con) {};  

  // Move constructor
  inline SortableVector(SortableVector<Data>&& con) noexcept
    : Vector<Data>(std::move(con)) {};  

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline SortableVector<Data>& operator=(const SortableVector<Data>& con);

  // Move assignment
  inline SortableVector<Data>& operator=(SortableVector<Data>&& con) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */


}

#include "vector.cpp"

#endif
