
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : public virtual Set<Data>,
               public virtual ResizableContainer {
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // ...
  size_t front_index = 0;  // Indice per il vettore circolare 

protected:

  // using Container::???;
  using Container::size;

public:

  // Default constructor
  SetVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  // A set obtained from a TraversableContainer
  SetVec(const TraversableContainer<Data>& con);

  // A set obtained from a MappableContainer
  SetVec(MappableContainer<Data>&& con);

  /* ************************************************************************ */

  // Copy constructor
  SetVec(const SetVec<Data>& other);

  // Move constructor
  SetVec(SetVec<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SetVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline SetVec<Data>& operator=(const SetVec<Data>& other);

  // Move assignment
  inline SetVec<Data>& operator=(SetVec<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const SetVec<Data>& other) const noexcept;
  inline bool operator!=(const SetVec<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline Data Min() const;
  inline Data MinRemove();
  inline Data RemoveMin();

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline Data Max() const;
  inline Data MaxRemove();
  inline Data RemoveMax();

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  inline Data Predecessor(const Data&) const;
  inline Data PredecessorNRemove(const Data&);
  inline Data RemovePredecessor(const Data&);

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  inline Data Successor(const Data&) const;
  inline Data SuccessorNRemove(const Data&);
  inline Data RemoveSuccessor(const Data&); 

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  inline void Insert(const Data&);  // Override DictionaryContainer member (copy of the value)
  inline void Insert(Data&&);       // Override DictionaryContainer member (move of the value)
  inline void Remove(const Data&);  // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  inline Data& operator[](size_t) override;
  inline const Data& operator[](size_t) const override;

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() noexcept override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
