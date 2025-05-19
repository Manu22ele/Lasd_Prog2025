
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
  inline SetLst<Data>& operator=(const SetLst<Data>&);

  // Move assignment
  inline SetLst<Data>& operator=(SetLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const SetLst<Data>&) const noexcept;
  inline bool operator!=(const SetLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline Data Min() const;
  inline Data MinRemove() const;
  inline Data RemoveMin() const;

  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline Data Max() const; 
  inline Data MaxRemove() const;
  inline Data RemoveMax() const;
  
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

  inline void Insert(const Data&);       // Insert by copy
  inline void Insert(Data&&);             // Insert by move
  inline void Remove(const Data&);        // Remove an element


  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  inline Data& operator[](size_t index);              // Access an element by index (throws std::out_of_range if out of range)
  inline const Data& operator[](size_t index) const;   // Const access to an element by index (throws std::out_of_range if out of range)


  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data&) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() noexcept override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif
