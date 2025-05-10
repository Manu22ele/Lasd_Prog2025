
namespace lasd {

// PreOrderMappableContainer
/* ************************************************************************** */

// Overrided methods

template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// PostOrderMappableContainer
/* ************************************************************************** */

// Overrided methods

template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun fun) {
  PostOrderMap(fun);
}

/* ************************************************************************** */

} // namespace lasd