
#include <stdexcept>
#include <utility>

namespace lasd {

/* ************************************************************************** */

// Costruttori

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& con) {
  size = 0;
  capacity = con.Size();
  elements = new Data[capacity];

  con.Traverse([this](const Data& elem) {
    this->Insert(elem); // inserimento ordinato e senza duplicati
  });
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& con) {
  size = 0;
  capacity = con.Size();
  elements = new Data[capacity];

  con.Map([this](Data&& elem) {
    this->Insert(std::move(elem)); // inserimento ordinato e senza duplicati
  });
}

/* ************************************************************************** */

// Costruttore di copia
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) {
  size = other.size;
  capacity = other.capacity;
  elements = new Data[capacity]; // Alloca memoria per gli elementi

  // Copia gli elementi da "other" nel nuovo array
  for (size_t i = 0; i < size; ++i) {
    elements[i] = other.elements[i]; // Copia ogni elemento
  }
}

// Costruttore di move
template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept {
  size = other.size;
  capacity = other.capacity;
  elements = other.elements;  // Prendi il puntatore agli elementi di "other"

  // Imposta "other" in uno stato valido, evitando doppia deallocazione
  other.elements = nullptr;  
  other.size = 0;
  other.capacity = 0;
}


/* ************************************************************************** */

// Assegnamento di copia
template <typename Data>
inline SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
  if (this != &other) { // Evita l'auto-assegnamento
    delete[] elements; // Dealloca la memoria esistente

    size = other.size;
    capacity = other.capacity;
    elements = new Data[capacity]; // Alloca nuova memoria

    // Copia gli elementi da "other" nel nuovo array
    for (size_t i = 0; i < size; ++i) {
      elements[i] = other.elements[i]; // Copia ogni elemento
    }
  }
  return *this;
}

// Assegnamento di move
template <typename Data> 
inline SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
  if (this != &other) { // Evita l'auto-assegnamento
    delete[] elements; // Dealloca la memoria esistente

    size = other.size;
    capacity = other.capacity;
    elements = other.elements;  // Prendi il puntatore agli elementi di "other"

    // Imposta "other" in uno stato valido, evitando doppia deallocazione
    other.elements = nullptr;  
    other.size = 0;
    other.capacity = 0;
  }
  return *this;
}

/* ************************************************************************** */

// Operatori di confronto
template <typename Data>
inline bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
  if (this == &other) {
    return true;  // Se sono lo stesso oggetto, sono uguali
  }

  if (size != other.size) {
    return false;  // Se le dimensioni sono diverse, i set non sono uguali
  }

  for (size_t i = 0; i < size; ++i) {
    if (elements[i] != other.elements[i]) {
      return false;  // Se un elemento è diverso, i set non sono uguali
    }
  }

  return true;  // Se tutti gli elementi sono uguali, i set sono uguali
}

// Operatore di confronto (!=)
template <typename Data>
inline bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
  return !(*this == other);  // Inverte il risultato dell'operatore di uguaglianza
}

/* ************************************************************************** */

// Membri specifici OrderedDictionaryContainer

// Min (ritorna il minimo)
template <typename Data>
const Data& SetVec<Data>::Min() const {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }
  return elements[0]; // Poiché è ordinato, il primo elemento è il minimo
}

// MinRemove (ritorna e rimuove il minimo)
template <typename Data>
Data SetVec<Data>::MinRemove() {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }
  
  Data min = elements[0];
  Remove(min);  // Rimuove l'elemento minimo
  return min;
}

// RemoveMin (rimuove il minimo)
template <typename Data>
void SetVec<Data>::RemoveMin() {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }
  
  Data min = elements[0];
  Remove(min);  // Rimuove l'elemento minimo
  return min;
}

// Max (ritorna il massimo)
template <typename Data>
const Data& SetVec<Data>::Max() const {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }
  return elements[size - 1]; // Poiché è ordinato, l'ultimo elemento è il massimo
}

// MaxRemove (ritorna e rimuove il massimo)
template <typename Data>
Data SetVec<Data>::MaxRemove() {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }
  
  Data max = elements[size - 1];
  Remove(max);  // Rimuove l'elemento massimo
  return max;
}

// RemoveMax (rimuove il massimo)
template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }
  
  Data max = elements[size - 1];
  Remove(max);  // Rimuove l'elemento massimo
  return max;
}

// Predecessor (ritorna il predecessore dell'elemento, lancia eccezione se non trovato)
template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& elem) const {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }
  
  // Ricerca binaria per trovare l'elemento
  int index = BinarySearch(elem);
  if (index <= 0) {
    throw std::length_error("No predecessor found.");
  }

  return elements[index - 1]; // Restituisce l'elemento precedente
}

// PredecessorNRemove (ritorna il predecessore e lo rimuove)
template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& elem) {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }

  // Ricerca binaria per trovare l'elemento
  int index = BinarySearch(elem);
  if (index <= 0) {
    throw std::length_error("No predecessor found.");
  }

  Data predecessor = elements[index - 1];
  Remove(predecessor); // Rimuove il predecessore
  return predecessor;
}

// RemovePredecessor (rimuove il predecessore dell'elemento)
template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& elem) {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }

  // Ricerca binaria per trovare l'elemento
  int index = BinarySearch(elem);
  if (index <= 0) {
    throw std::length_error("No predecessor found.");
  }

  Data predecessor = elements[index - 1];
  Remove(predecessor); // Rimuove il predecessore
  return predecessor;
}

// Successor (ritorna il successore dell'elemento, lancia eccezione se non trovato)
template <typename Data>
const Data& SetVec<Data>::Successor(const Data& elem) const {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }

  // Ricerca binaria per trovare l'elemento
  int index = BinarySearch(elem);
  if (index < 0 || index >= size - 1) {
    throw std::length_error("No successor found.");
  }

  return elements[index + 1]; // Restituisce il successore
}

// SuccessorNRemove (ritorna il successore e lo rimuove)
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& elem) {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }

  // Ricerca binaria per trovare l'elemento
  int index = BinarySearch(elem);
  if (index < 0 || index >= size - 1) {
    throw std::length_error("No successor found.");
  }

  Data successor = elements[index + 1];
  Remove(successor); // Rimuove il successore
  return successor;
}

// RemoveSuccessor (rimuove il successore dell'elemento)
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& elem) {
  if (size == 0) {
    throw std::length_error("Set is empty.");
  }

  // Ricerca binaria per trovare l'elemento
  int index = BinarySearch(elem);
  if (index < 0 || index >= size - 1) {
    throw std::length_error("No successor found.");
  }

  Data successor = elements[index + 1];
  Remove(successor); // Rimuove il successore
  return successor;
}


/* ************************************************************************** */

// Membri specifici DictionaryContainer

template <typename Data>
bool SetVec<Data>::Insert(const Data& elem) {
  // Ricerca binaria per determinare se l'elemento esiste già nel set
  int index = BinarySearch(elem);
  
  // Se l'elemento esiste già, non fare nulla
  if (index >= 0) {
    return;
  }

  // Se l'elemento non esiste, dobbiamo inserirlo nell'ordine corretto
  // Spostiamo gli elementi per fare spazio per il nuovo elemento
  if (size == capacity) {
    Resize(); // Se il vettore è pieno, lo ridimensioniamo
  }

  index = -index - 1;  // Otteniamo l'indice dove inserire l'elemento

  // Spostiamo gli elementi successivi per fare spazio all'elemento
  for (size_t i = size; i > index; --i) {
    elements[i] = elements[i - 1];
  }

  // Inseriamo l'elemento
  elements[index] = elem;
  ++size; // Aumentiamo la dimensione del set
}

// Insert (inserisce un elemento nel set, evitando duplicati, versione di move)
template <typename Data>
bool SetVec<Data>::Insert(Data&& elem) {
  // Ricerca binaria per determinare se l'elemento esiste già nel set
  int index = BinarySearch(elem);
  
  // Se l'elemento esiste già, non fare nulla
  if (index >= 0) {
    return;
  }

  // Se l'elemento non esiste, dobbiamo inserirlo nell'ordine corretto
  // Spostiamo gli elementi per fare spazio per il nuovo elemento
  if (size == capacity) {
    Resize(); // Se il vettore è pieno, lo ridimensioniamo
  }

  index = -index - 1;  // Otteniamo l'indice dove inserire l'elemento

  // Spostiamo gli elementi successivi per fare spazio all'elemento
  for (size_t i = size; i > index; --i) {
    elements[i] = std::move(elements[i - 1]);
  }

  // Inseriamo l'elemento
  elements[index] = std::move(elem);
  ++size; // Aumentiamo la dimensione del set
}


// Remove (rimuove un elemento dal set)
template <typename Data>
bool SetVec<Data>::Remove(const Data& elem) {
  // Ricerca binaria per determinare se l'elemento esiste nel set
  int index = BinarySearch(elem);

  // Se l'elemento non esiste, lanciamo un'eccezione
  if (index < 0) {
    throw std::length_error("Element not found.");
  }

  // Spostiamo gli elementi successivi per colmare il vuoto
  for (size_t i = index; i < size - 1; ++i) {
    elements[i] = elements[i + 1];
  }

  --size; // Decrementiamo la dimensione del set
}

// BinarySearch (ricerca binaria per trovare l'indice dell'elemento nel vettore)
template <typename Data>
int SetVec<Data>::BinarySearch(const Data& elem) const {
  int left = 0;
  int right = size - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (elements[mid] == elem) {
      return mid;  // Elemento trovato
    } else if (elements[mid] < elem) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -(left + 1);  // Elemento non trovato, ritorna l'indice dove dovrebbe essere
}

// Resize (raddoppia la capacità del vettore quando è pieno)
template <typename Data>
void SetVec<Data>::Resize() {
  capacity *= 2;
  Data* new_elements = new Data[capacity];

  // Copia gli elementi nel nuovo array
  for (size_t i = 0; i < size; ++i) {
    new_elements[i] = std::move(elements[i]);
  }

  delete[] elements;
  elements = new_elements;
}


/* ************************************************************************** */

// Membri specifici LinearContainer

template <typename Data>
Data& SetVec<Data>::operator[](size_t index) {
  if (index >= size) {
    throw std::out_of_range("Index out of range.");
  }

  // Per il vettore circolare, l'elemento a [index] si trova
  // all'interno del range del vettore
  return elements[(front_index + index) % capacity];
}

// Operatore [] per l'accesso a un elemento const
template <typename Data>
const Data& SetVec<Data>::operator[](size_t index) const {
  if (index >= size) {
    throw std::out_of_range("Index out of range.");
  }

  // Per il vettore circolare, l'elemento a [index] si trova
  // all'interno del range del vettore
  return elements[(front_index + index) % capacity];
}

/* ************************************************************************** */

// Membri specifici TestableContainer

template <typename Data>
bool SetVec<Data>::Exists(const Data& elem) const noexcept {
  // Utilizziamo la ricerca binaria per cercare l'elemento
  size_t low = 0;
  size_t high = size - 1;

  while (low <= high) {
    size_t mid = low + (high - low) / 2;
    size_t index = (front_index + mid) % capacity;  // Vettore circolare

    if (elements[index] == elem) {
      return true;  // Elemento trovato
    } else if (elements[index] < elem) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return false;  // Elemento non trovato
}

/* ************************************************************************** */

// Membri specifici ClearableContainer

template <typename Data>
void SetVec<Data>::Clear() noexcept {
  size = 0;  // Ripristina la dimensione a 0
  // Non è necessario liberare la memoria, poiché la capacità non cambia
  // La memoria resterà allocata per la futura crescita del container.
}

/* ************************************************************************** */

}
