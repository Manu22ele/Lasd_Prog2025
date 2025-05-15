
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : public virtual ClearContainer<Data>,
             public virtual MutableLinearContainer<Data> {
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // using Container::???;
  using  Container::size;

  struct Node {

    // Data
    Data value{};      
    Node* next{nullptr};

    Node() = default;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data &);

    Node(Data &&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node &);

    // Move constructor
    Node(Node &&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node &) const noexcept;

    bool operator!=(const Node &) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  // ...
  Node *head{nullptr}; // Pointer to the first node
  Node *tail{nullptr}; // Pointer to the last node

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
  virtual ~List() noexcept;

  /* ************************************************************************ */

  // Copy assignment
  inline List &operator=(const List &);

  // Move assignment
  inline List &operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const List &) const noexcept;
  inline bool operator!=(const List &) const noexcept;

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
  
  // Override MutableLinearContainer's operator[] (must throw std::out_of_range when out of range)
  inline Data& operator[](unsigned long) override; 
  inline const Data& operator[](unsigned long) const override;

  // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data& Front() override;
  inline const Data& Front() const override;

  // type Back() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  inline Data& Back() override;
  inline const Data& Back() const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // Override LinearContainer member (must throw std::out_of_range when out of range)
  inline Data& operator[](unsigned long index) override;
  inline const Data& operator[](unsigned long index) const override;  

  // Override LinearContainer member (must throw std::length_error when empty)
  inline Data& Front() override;
  inline const Data& Front() const override;

  // Override LinearContainer member (must throw std::length_error when empty)
  inline Data& Back() override;
  inline const Data& Back() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // using typename MappableContainer<Data>::MapFun;
  using typename MappableContainer<Data>::MapFun;

  // Override MappableContainer member
  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // Override PreOrderMappableContainer member
  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // Override PostOrderMappableContainer member
  inline void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // using typename TraversableContainer<Data>::TraverseFun;
  using typename TraversableContainer<Data>::TraverseFun;

  // Override TraversableContainer member
  inline void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // Override PreOrderTraversableContainer member
  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // Override PostOrderTraversableContainer member
  inline void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // Override ClearableContainer member
  inline void Clear() noexcept override;

protected:

    void PreOrderMap(MapFun, Node*) const;

    void PostOrderMap(MapFun, Node*) const;

    void PreOrderTraverse(TraverseFun, Node*) const;

    void PostOrderTraverse(TraverseFun, Node*) const;

    inline void clear(Node*) noexcept;

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
