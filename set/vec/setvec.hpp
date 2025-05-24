
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
  size_t capacity = 0;
  Data* elements = nullptr;
  size_t front_index = 0;
  
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
  SetVec<Data>& operator=(const SetVec<Data>& other);

  // Move assignment
  SetVec<Data>& operator=(SetVec<Data>&& other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const SetVec<Data>& other) const noexcept;
  virtual bool operator!=(const SetVec<Data>& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual const Data& Min() const override;
  Data MinRemove();
  virtual void RemoveMin() override;

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual const Data& Max() const override;
  Data MaxRemove();
  virtual void RemoveMax() override;

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  const Data& Predecessor(const Data&) const;
  Data PredecessorNRemove(const Data&);
  Data RemovePredecessor(const Data&);

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  const Data& Successor(const Data&) const;
  Data SuccessorNRemove(const Data&);
  Data RemoveSuccessor(const Data&); 

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual void Insert(const Data&) override;  // Override DictionaryContainer member (copy of the value)
  virtual void Insert(Data&&) override;       // Override DictionaryContainer member (move of the value)
  virtual void Remove(const Data&) override;  // Override DictionaryContainer member

  void Resize() override;  // Override ResizableContainer member (resizes the container)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](size_t) override;
  const Data& operator[](size_t) const override;

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data&) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() noexcept override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif
