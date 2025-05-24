#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : public virtual MutableLinearContainer<Data>,
               public virtual ResizableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size;

  Data *elements = nullptr;

public:

  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const unsigned long initSize) { // A vector with a given initial dimension
    size = initSize;
    elements = new Data[initSize]();
  };

  Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data> &&);          // A vector obtained from a MappableContainer

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
  virtual Vector<Data> &operator=(const Vector<Data> &);

  // Move assignment
  virtual Vector<Data> &operator=(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data> &) const noexcept;
  virtual bool operator!=(const Vector<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
  virtual Data &operator[](unsigned long index) override;

  // Override MutableLinearContainer member (must throw std::length_error when empty)
  virtual Data &Front() override;

  // Override MutableLinearContainer member (must throw std::length_error when empty)
  virtual Data &Back() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // Override LinearContainer member (must throw std::out_of_range when out of range)
  virtual const Data &operator[](unsigned long) const override;

  // Override LinearContainer member (must throw std::length_error when empty)
  virtual const Data &Front() const override;

  // Override LinearContainer member (must throw std::length_error when empty)
  virtual const Data &Back() const override;

  // Override TraversableContainer member
  virtual void Traverse(typename TraversableContainer<Data>::TraverseFun) const override;

  // Override MappableContainer member
  virtual void Map(typename MappableContainer<Data>::MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  // Override ResizableContainer member
  void Resize(unsigned long new_size) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // Override ClearableContainer member
  virtual void Clear() override;

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

  // Porta in visibilità gli operator= della base Vector per evitare hiding
  using Vector<Data>::operator=;

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  // A vector with a given initial dimension
  SortableVector(unsigned long initSize) : Vector<Data>(initSize) {};

  // A vector obtained from a TraversableContainer
  SortableVector(const TraversableContainer<Data> &container) : Vector<Data>(container) {};

  // A vector obtained from a MappableContainer
  SortableVector(MappableContainer<Data> &&container)
      : Vector<Data>::Vector(std::move(container)) {};

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector<Data> &con)
      : Vector<Data>(con) {};

  // Move constructor
  SortableVector(SortableVector<Data> &&con) noexcept
      : Vector<Data>(std::move(con)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment override che chiama l’operatore base per chiarezza e per evitare warning
  SortableVector<Data> &operator=(const SortableVector<Data> &con);

  // Move assignment override che chiama l’operatore base per chiarezza e per evitare warning
  SortableVector<Data> &operator=(SortableVector<Data> &&con) noexcept;

  void Sort() noexcept override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

} // namespace lasd

#include "vector.cpp"

#endif
