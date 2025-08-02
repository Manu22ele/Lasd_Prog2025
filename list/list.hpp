
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : public virtual MutableLinearContainer<Data>,
             public virtual ClearableContainer {
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // using Container::???;

  struct Node {

    // Data
    Data element;      
    Node* next = nullptr;

    Node() = default;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data &);

    Node(Data &&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node &) const;
    bool operator!=(const Node &) const;

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  
  Node *head = nullptr; // Pointer to the first node
  Node *tail = nullptr; // Pointer to the last node
  using Container::size;


  Node* CopyList(const Node*);
  void ClearList();
  void RemoveAt(unsigned long);


public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> &);
  List(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List &);

  // Move constructor
  List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~List();
  /* ************************************************************************ */

  // Copy assignment
  virtual List &operator=(const List &);

  // Move assignment
  virtual List &operator=(List &&) noexcept;

  /* ************************************************************************ */

  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;

  // Comparison operators
  bool operator==(const List &) const noexcept;
  bool operator!=(const List &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&); // Move of the value
  void RemoveFromBack(); // (must throw std::length_error when empty)
  Data BackNRemove(); // (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)
  
  using typename MappableContainer<Data>::MapFun;
  Data& operator[](unsigned long) override;
  Data& Front() override;
  Data& Back() override;
  void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](unsigned long) const override;
  const Data& Front() const override;
  const Data& Back() const override;

  /* ************************************************************************ */


  // Specific member function (inherited from PreOrderMappableContainer)

  // Override PreOrderMappableContainer member
  void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // Override PostOrderMappableContainer member
  void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun;

  // Override TraversableContainer member
  void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // Override PreOrderTraversableContainer member
  void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // Override PostOrderTraversableContainer member
  void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // Override ClearableContainer member
  void Clear() override;


protected:


};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
