
namespace lasd {

// Traversable Container
/* ************************************************************************** */

// Specific Methods

template <typename Data, typename Accumulator>
using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(typename TraversableContainer<Data>::template FoldFun<Accumulator> func, const Accumulator& base) const {
  Traverse([&base, func](const Data &currData) { base = func(currData, base); });
  return base;
};

// Overrided Methods

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data &data) const noexcept {
  bool exists = false;
  Traverse([data, &exists](const Data &currData) { exists |= (data == currData); });
  return exists;
}

/* ************************************************************************** */

// PreOrder Traversable Container
/* ************************************************************************** */

// Specific Methods

template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun func) const {
  PreOrderTraverse(func);
}

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(typename PreOrderTraversableContainer<Data>::template FoldFun<Accumulator> func, const Accumulator& base) const {
  PreOrderTraverse([&base, func](const Data &currData) { base = func(currData, base); });
  return base;
};

/* ************************************************************************** */

// PostOrder Traversable Container
/* ************************************************************************** */

// Specific Methods

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun func) const {
  PostOrderTraverse(func);
}

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(typename PostOrderTraversableContainer<Data>::template FoldFun<Accumulator> func, const Accumulator& base) const {
  PostOrderTraverse([&base, &func](const Data &currData) { base = func(currData, base); });
  return base;
};

/* ************************************************************************** */

} // namespace lasd