namespace lasd {

/* ************************************************************************** */

// Traversable Container

template <typename Data, typename Accumulator>
using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> func, const Accumulator& base) const {
  Accumulator result = base;                  // copia modificabile
  Traverse([&result, func](const Data &currData) { 
    result = func(currData, result);          // uso result (non const)
  });
  return result;
}

// Overrided Methods

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data &data) const noexcept {
  bool exists = false;
  Traverse([data, &exists](const Data &currData) { exists |= (data == currData); });
  return exists;
}

/* ************************************************************************** */

// PreOrder Traversable Container

template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun func) const {
  PreOrderTraverse(func);
}

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> func, const Accumulator& base) const {
  Accumulator result = base;                  // copia modificabile
  PreOrderTraverse([&result, func](const Data &currData) {
    result = func(currData, result);          // uso result (non const)
  });
  return result;
}

/* ************************************************************************** */

// PostOrder Traversable Container

template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun func) const {
  PostOrderTraverse(func);
}

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> func, const Accumulator& base) const {
  Accumulator result = base;                  // copia modificabile
  PostOrderTraverse([&result, func](const Data &currData) {
    result = func(currData, result);          // uso result (non const)
  });
  return result;
}

/* ************************************************************************** */

} // namespace lasd
