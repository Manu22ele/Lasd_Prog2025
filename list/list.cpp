#include <iostream>
#include <utility>
namespace lasd {

// Node Methods
/* ************************************************************************** */

// Constructors

// Data copy constructor
template <typename Data>
List<Data>::Node::Node(const Data &d) : value(d) {}

// Data move constructor
template <typename Data>
List<Data>::Node::Node(Data &&d) noexcept : value(std::move(d)) {}

// Copy constructor
template <typename Data>
List<Data>::Node::Node(const Node &n) : value(n.value), next(n.next) {}

// Move constructor
template <typename Data>
List<Data>::Node::Node(Node &&n) noexcept : value(std::move(n.value)), next(n.next) {
  n.next = nullptr; // Avoid dangling pointer
}

// Destructor
template <typename Data>
List<Data>::Node::~Node() = default;

// Operators

// Comparison operators
template <typename Data>
bool List<Data>::Node::operator==(const Node &n) const noexcept {
  return (value == n.value && next == n.next);
}

template <typename Data> 
bool List<Data>::Node::operator!=(const Node &n) const noexcept {
  return !(*this == n);
}

/* ************************************************************************** */

// List Methods
/* ************************************************************************** */

// Constructors

// Copy constructor from Different DataStructures
template <typename Data>   
List<Data>::List(const TraversableContainer<Data> &con) {
  con.Traverse([this](const Data &currData) {
    InsertAtBack(currData);
  });
}


// Move constructor from Different DataStructures
template <typename Data>   
List<Data>::List(MappableContainer<Data> &&con) {
  con.Map([this](Data &currData) {
    InsertAtBack(std::move(currData));
  });
}

// Copy constructor
template <typename Data> List<Data>::List(const List<Data> &l) {
  if (!(size = l.size))
    return;

  head = new Node(*(l.head));
  tail = head;

  Node *temp = l.head->next;

  while (temp) {
    tail->next = new Node(*temp);
    tail = tail->next;
    temp = temp->next;
  }
}



// Move constructor
template <typename Data> List<Data>::List(List &&l) noexcept{
  std::swap(size, l.size);
  std::swap(head, l.head);
  std::swap(tail, l.tail);
}


// Destructor
template <typename Data>
List<Data>::~List() noexcept {
  Clear();  // Libera tutti i nodi e azzera i puntatori
}


// Operators

// Copy assignment

template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& l) {

  if (!l.size) {
    Clear();
    return *this;
  }

  if (!size) {
    List<Data> temp{l};
    std::swap(temp, *this);
    return *this;
  }

  // Se la lista di destinazione è più grande della sorgente,
  // cancella tutto e ricrea da zero:
  if (size > l.size) {
    Clear();
    for (Node* wl = l.head; wl != nullptr; wl = wl->next) {
      InsertAtBack(wl->value);
    }
    return *this;
  }

  // Copia i valori dei nodi esistenti (in numero minimo)
  Node* wl = l.head;
  Node* tl = head;

  while (wl && tl) {
    tl->value = wl->value;
    wl = wl->next;
    tl = tl->next;
  }

  // Se la lista sorgente è più lunga, aggiungi i nodi restanti
  while (wl) {
    InsertAtBack(wl->value);
    wl = wl->next;
  }

  size = l.size;
  return *this;
}

// Move assignment
template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& l) noexcept {
  std::swap(size, l.size);
  std::swap(head, l.head);
  std::swap(tail, l.tail);
  return *this;
}

// Comparison operators
template <typename Data>
bool List<Data>::operator==(const List<Data> &l) const noexcept {
  if (size != l.size)
    return false;

  Node *temp = head, *temp2 = l.head;

  while (temp != nullptr) {
    if (temp->value != temp2->value) // CORRETTO NOME CAMPO
      return false;
    temp = temp->next;
    temp2 = temp2->next;
  }

  return true;
}

template <typename Data>
bool List<Data>::operator!=(const List<Data> &l) const noexcept {
  return !(*this == l);
}

template <typename Data>
bool List<Data>::operator==(const LinearContainer<Data>& con) const noexcept {
  const List<Data>* listPtr = dynamic_cast<const List<Data>*>(&con);
  return listPtr && (*this == *listPtr);
}

template <typename Data>
bool List<Data>::operator!=(const LinearContainer<Data>& con) const noexcept {
  return !(*this == con);
}

// Specific Operators

template <typename Data>
Data& List<Data>::operator[](unsigned long index) {
  if (index >= size)
    throw std::out_of_range("Index out of range");

  Node* temp = head;
  for (unsigned long i = 0; i < index; ++i) {
    temp = temp->next;
  }
  return temp->value;
}

template <typename Data>
const Data& List<Data>::operator[](unsigned long index) const {
  if (index >= size)
    throw std::out_of_range("Index out of range");

  Node* temp = head;
  for (unsigned long i = 0; i < index; ++i) {
    temp = temp->next;
  }
  return temp->value;
}

// Specific methods

template <typename Data>
void List<Data>::InsertAtFront(const Data& d) {
  Node* newNode = new Node(d);   
  newNode->next = head;          
  head = newNode;                
  if (tail == nullptr)          
    tail = head;
  ++size;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& d) {
  Node* newNode = new Node(std::move(d)); 
  newNode->next = head;
  head = newNode;
  if (tail == nullptr)
    tail = head;
  ++size;
}


template <typename Data>
void List<Data>::RemoveFromFront() {
  if (!size)
    throw std::length_error("Cannot remove from empty list");

  Node* temp = head;

  if (head == tail) {
    head = nullptr;
    tail = nullptr;
  } else {
    head = head->next;
  }

  temp->next = nullptr; // Non strettamente necessario, ma pulito
  delete temp;
  --size;
}


template <typename Data>
Data List<Data>::FrontNRemove() {
  if (!size)
    throw std::length_error("Cannot remove from empty list");

  Node* temp = head;
  Data d = std::move(temp->value); // Sposta il dato

  if (head == tail) {
    head = nullptr;
    tail = nullptr;
  } else {
    head = head->next;
  }

  temp->next = nullptr;
  delete temp;
  --size;
  return d;
}


template <typename Data>
void List<Data>::InsertAtBack(const Data& d) {
  Node* newNode = new Node(d);
  if (tail == nullptr) { // Lista vuota
    head = tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  ++size;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& d) {
  Node* newNode = new Node(std::move(d));
  if (tail == nullptr) {
    head = tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  ++size;
}

template <typename Data>
void List<Data>::RemoveFromBack() {
  if (size == 0)
    throw std::length_error("Cannot remove from empty list");

  if (head == tail) {
    delete head;
    head = tail = nullptr;
  } else {
    Node* prev = head;
    while (prev->next != tail) {
      prev = prev->next;
    }
    delete tail;
    tail = prev;
    tail->next = nullptr;
  }

  --size;
}

template <typename Data>
Data List<Data>::BackNRemove() {
  if (size == 0)
    throw std::length_error("Cannot remove from empty list");

  Data data = std::move(tail->value);
  RemoveFromBack();
  return data;
}



template <typename Data>
Data& List<Data>::Front() {
  if (size == 0)
    throw std::length_error("Cannot access Front from empty list");

  return head->value;
}

template <typename Data>
const Data& List<Data>::Front() const {
  if (size == 0)
    throw std::length_error("Cannot access Front from empty list");

  return head->value;
}

template <typename Data>
Data& List<Data>::Back() {
  if (size == 0)
    throw std::length_error("Cannot access Back from empty list");

  return tail->value;
}

template <typename Data>
const Data& List<Data>::Back() const {
  if (size == 0)
    throw std::length_error("Cannot access Back from empty list");

  return tail->value;
}


// Overrided Methods

template <typename Data>
void List<Data>::Map(MapFun mapFunc) {
  Node* temp = head;
  while (temp) {
    mapFunc(temp->value);  // Applica la funzione mappante all'elemento
    temp = temp->next;
  }
}


template <typename Data>
void List<Data>::Traverse(TraverseFun traverseFunc) const {
  Node* temp = head;
  while (temp) {
    traverseFunc(temp->value);  // Applica la funzione di traversamento all'elemento
    temp = temp->next;
  }
}



// Internal Methods


template <typename Data>
void List<Data>::PreOrderMap(MapFun mapFunc) {
  Node* current = head;
  while (current != nullptr) {
    mapFunc(current->value);
    current = current->next;
  }
}


template <typename Data>
void List<Data>::PostOrderMap(MapFun mapFunc) {
  // Puoi usare uno stack o ricorsione con una lista ausiliaria
  std::vector<Data*> temp;
  Node* current = head;
  while (current != nullptr) {
    temp.push_back(&(current->value));
    current = current->next;
  }
  for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
    mapFunc(**it);
  }
}

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun traverseFunc) const {
  Node* current = head;
  while (current != nullptr) {
    traverseFunc(current->value);
    current = current->next;
  }
}


template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun traverseFunc) const {
  std::vector<const Data*> temp;
  Node* current = head;
  while (current != nullptr) {
    temp.push_back(&(current->value));
    current = current->next;
  }
  for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
    traverseFunc(**it);
  }
}

template <typename Data>
void List<Data>::Clear() noexcept {
  while (head != nullptr) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
  tail = nullptr;
  size = 0;
}

/* **************************************************************************
 */

} // namespace lasd