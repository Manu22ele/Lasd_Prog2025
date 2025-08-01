#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : public virtual TraversableContainer<Data> {

private:
  // ...

protected:

  // ...
  
public:
  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer &operator=(const MappableContainer &)  = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MappableContainer &operator=(MappableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible

  /* ************************************************************************ */

  // Comparison operators

  bool operator==(const MappableContainer &) const = delete; // Comparison of abstract types is not possible.
  bool operator!=(const MappableContainer &) const = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;

  virtual void Map(const MapFun) = 0;
};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : public virtual MappableContainer<Data>,
                                  public virtual PreOrderTraversableContainer<Data> {

private:
  // ...

protected:
  // Default constructor

public:
  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */
  // Copy assignment
  PreOrderMappableContainer &operator=(const PreOrderMappableContainer &) = delete;

  // Move assignment
  PreOrderMappableContainer &operator=(PreOrderMappableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer &) const = delete;
  bool operator!=(const PreOrderMappableContainer &) const = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PreOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  virtual void Map(MapFun) override = 0;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : public virtual MappableContainer<Data>,
                                   public virtual PostOrderTraversableContainer<Data> {

private:
  // ...

protected:
  // Default constructor

public:
  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */
  // Copy assignment
  PostOrderMappableContainer &operator=(const PostOrderMappableContainer &) = delete;

  // Move assignment
  PostOrderMappableContainer &operator=(PostOrderMappableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderMappableContainer &) const = delete;
  bool operator!=(const PostOrderMappableContainer &) const = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PostOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  virtual void Map(const MapFun fun) override = 0;

};

/* ************************************************************************** */
}

#include "mappable.cpp"

#endif
