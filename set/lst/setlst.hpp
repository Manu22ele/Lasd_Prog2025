
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : public virtual Set<Data>,
               public virtual List<Data> {
  // Must extend Set<Data>,
  //             List<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  using typename List<Data>::Node;
  using List<Data>::head;

  // ...

public:

  // Default constructor
  SetLst() = default;

  /* ************************************************************************ */

  // Specific constructors
  // A set obtained from a TraversableContainer
  SetLst(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetLst(MappableContainer<Data>&&); // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetLst(const SetLst<Data>&); 

  // Move constructor
  SetLst(SetLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SetLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  virtual SetLst<Data>& operator=(const SetLst<Data>&);

  // Move assignment
  virtual SetLst<Data>& operator=(SetLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const SetLst<Data>&) const noexcept;
  virtual bool operator!=(const SetLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual Data Min() const;
  virtual Data MinRemove() const;
  virtual Data RemoveMin() const;

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  virtual Data Max() const; 
  virtual Data MaxRemove() const;
  virtual Data RemoveMax() const;
  
  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual Data Predecessor(const Data&) const;
  virtual Data PredecessorNRemove(const Data&);
  virtual Data RemovePredecessor(const Data&);

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  virtual Data Successor(const Data&) const; 
  virtual Data SuccessorNRemove(const Data&);
  virtual Data RemoveSuccessor(const Data&);

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual void Insert(const Data&);       // Insert by copy
  virtual void Insert(Data&&);             // Insert by move
  virtual void Remove(const Data&);        // Remove an element


  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  virtual Data& operator[](size_t index);              // Access an element by index (throws std::out_of_range if out of range)
  virtual const Data& operator[](size_t index) const;   // Const access to an element by index (throws std::out_of_range if out of range)


  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  virtual bool Exists(const Data&) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() noexcept override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
