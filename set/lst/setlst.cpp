
#include <stdexcept>
#include <cstddef>
#include <new>

namespace lasd {

/* ************************************************************************** */

// Costruttori

template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& con) {
  con.Travers([this](const Data& currData) {
    this->Insert(currData);
  });
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& con) {
  con.Map([this](Data&& currData) {
    this->Insert(std::move(currData));
  });
}

/* ************************************************************************** */

// Costruttore di copia
template <typename Data>
SetLst<Data>::SetLst(const SetLst<Data>& other) : List<Data>(other){}

// Costruttore di move 
template <typename Data>
SetLst<Data>::SetLst(SetLst<Data>&& other) noexcept : List<Data>(std::move(other)) {}

/* ************************************************************************** */

// Assegnamento di copia
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other) {
  if (this != &other) {
    List<Data>::operator=(other);
  }
  return *this;
}

// Assegnamendo di move
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept {
    List<Data>::operator=(std::move(other));
    return *this;
}

/* ************************************************************************** */

// Operatori di confronto

template <typename Data>
bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept {
    return List<Data>::operator==(other);
}

template <typename Data>
bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */

// Membri Specifici OrderedDictionaryContainer


// Min
template <typename Data>
Data SetLst<Data>::Min() const {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }
  Node* temp = head;
  Data minValue = temp->value;
  temp = temp->next;

  while (temp) {
    if (temp->value < minValue) {
      minValue = temp->value;
    }
    temp = temp->next;
  }

  return minValue;
}

// MinRemove
template <typename Data>
Data SetLst<Data>::MinRemove() const {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;
  Data minValue = temp->value;
  Node* prev = nullptr;
  Node* minNode = temp;

  while (temp) {
    if (temp->value < minValue) {
      minValue = temp->value;
      minNode = temp;
      prev = prev ? prev->next : nullptr;
    }
    temp = temp->next;
  }

  if (prev) {
    prev->next = minNode->next;
  } else {
    head = minNode->next;
  }

  delete minNode;
  return minValue;
}

// RemoveMin
template <typename Data>
Data SetLst<Data>::RemoveMin() const {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;
  Data minValue = temp->value;
  Node* prev = nullptr;
  Node* minNode = temp;

  while (temp) {
    if (temp->value < minValue) {
      minValue = temp->value;
      minNode = temp;
      prev = prev ? prev->next : nullptr;
    }
    temp = temp->next;
  }

  if (prev) {
    prev->next = minNode->next;
  } else {
    head = minNode->next;
  }

  delete minNode;
  return minValue;
}

// Max
template <typename Data>
Data SetLst<Data>::Max() const {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }
  Node* temp = head;
  Data maxValue = temp->value;
  temp = temp->next;

  while (temp) {
    if (temp->value > maxValue) {
      maxValue = temp->value;
    }
    temp = temp->next;
  }

  return maxValue;
}

// MaxRemove
template <typename Data>
Data SetLst<Data>::MaxRemove() const {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;
  Data maxValue = temp->value;
  Node* prev = nullptr;
  Node* maxNode = temp;

  while (temp) {
    if (temp->value > maxValue) {
      maxValue = temp->value;
      maxNode = temp;
      prev = prev ? prev->next : nullptr;
    }
    temp = temp->next;
  }

  if (prev) {
    prev->next = maxNode->next;
  } else {
    head = maxNode->next;
  }

  delete maxNode;
  return maxValue;
}

// RemoveMax
template <typename Data>
Data SetLst<Data>::RemoveMax() const {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;
  Data maxValue = temp->value;
  Node* prev = nullptr;
  Node* maxNode = temp;

  while (temp) {
    if (temp->value > maxValue) {
      maxValue = temp->value;
      maxNode = temp;
      prev = prev ? prev->next : nullptr;
    }
    temp = temp->next;
  }

  if (prev) {
    prev->next = maxNode->next;
  } else {
    head = maxNode->next;
  }

  delete maxNode;
  return maxValue;
}

// Predecessor
template <typename Data>
Data SetLst<Data>::Predecessor(const Data& value) const {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;
  Node* prev = nullptr;

  while (temp) {
    if (temp->value == value) {
      if (prev) {
        return prev->value;
      } else {
        throw std::length_error("No predecessor found");
      }
    }
    prev = temp;
    temp = temp->next;
  }

  throw std::length_error("Value not found");
}

// PredecessorNRemove
template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& value) {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;
  Node* prev = nullptr;

  while (temp) {
    if (temp->value == value) {
      if (prev) {
        Data predecessorValue = prev->value;
        if (prev == head) {
          head = temp;
        } else {
          prev->next = temp->next;
        }
        delete temp;
        return predecessorValue;
      } else {
        throw std::length_error("No predecessor found");
      }
    }
    prev = temp;
    temp = temp->next;
  }

  throw std::length_error("Value not found");
}

// RemovePredecessor
template <typename Data>
Data SetLst<Data>::RemovePredecessor(const Data& value) {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;
  Node* prev = nullptr;

  while (temp) {
    if (temp->value == value) {
      if (prev) {
        Data predecessorValue = prev->value;
        if (prev == head) {
          head = temp;
        } else {
          prev->next = temp->next;
        }
        delete temp;
        return predecessorValue;
      } else {
        throw std::length_error("No predecessor found");
      }
    }
    prev = temp;
    temp = temp->next;
  }

  throw std::length_error("Value not found");
}

// Successor
template <typename Data>
Data SetLst<Data>::Successor(const Data& value) const {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;

  while (temp) {
    if (temp->value == value) {
      if (temp->next) {
        return temp->next->value;
      } else {
        throw std::length_error("No successor found");
      }
    }
    temp = temp->next;
  }

  throw std::length_error("Value not found");
}

// SuccessorNRemove
template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& value) {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;
  Node* prev = nullptr;

  while (temp) {
    if (temp->value == value) {
      if (temp->next) {
        Data successorValue = temp->next->value;
        Node* successorNode = temp->next;
        temp->next = temp->next->next;
        delete successorNode;
        return successorValue;
      } else {
        throw std::length_error("No successor found");
      }
    }
    temp = temp->next;
  }

  throw std::length_error("Value not found");
}

// RemoveSuccessor
template <typename Data>
Data SetLst<Data>::RemoveSuccessor(const Data& value) {
  if (size == 0) {
    throw std::length_error("Container is empty");
  }

  Node* temp = head;

  while (temp) {
    if (temp->value == value) {
      if (temp->next) {
        Data successorValue = temp->next->value;
        Node* successorNode = temp->next;
        temp->next = temp->next->next;
        delete successorNode;
        return successorValue;
      } else {
        throw std::length_error("No successor found");
      }
    }
    temp = temp->next;
  }

  throw std::length_error("Value not found");
}


/* ************************************************************************** */

// Membri specifici DictionaryContainer

template <typename Data>
void SetLst<Data>::Insert(const Data& value) {
  if (Exists(value)) return;

  Node* newNode = new Node(value);

  if (!head || value < head->value) {
    newNode->next = head;
    head = newNode;
  } else {
    Node* curr = head;
    while (curr->next && curr->next->value < value) {
      curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
  }

  ++size;
}


template <typename Data>
void SetLst<Data>::Insert(Data&& value) {
  if (Exists(value)) return;

  Node* newNode = new Node(std::move(value));

  if (!head || newNode->value < head->value) {
    newNode->next = head;
    head = newNode;
  } else {
    Node* curr = head;
    while (curr->next && curr->next->value < newNode->value) {
      curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
  }

  ++size;
}

template <typename Data>
void SetLst<Data>::Remove(const Data& value) {
  // Controlla se l'elemento esiste prima di rimuoverlo
  if (Exists(value)) {
    // Rimuovi l'elemento dalla lista
    Node* temp = head;
    Node* prev = nullptr;
    while (temp) {
      if (temp->value == value) {
        if (prev) {
          prev->next = temp->next;
        } else {
          head = temp->next;  // Se è il primo elemento
        }
        delete temp;
        --size;
        return;
      }
      prev = temp;
      temp = temp->next;
    }
  } else {
    throw std::out_of_range("Element not found in the set");
  }
}


/* ************************************************************************** */

// Membri specifici LinearContainer
template <typename Data>
Data& SetLst<Data>::operator[](size_t index) {
    if(index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return List<Data>::operator[](index);
}

template <typename Data>
const Data& SetLst<Data>::operator[](size_t index) const {
    if(index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return List<Data>::operator[](index);
}

/* ************************************************************************** */

// Membri specific TestableContainer
template <typename Data>
bool SetLst<Data>::Exists(const Data& value) const noexcept {
  if (size == 0) return false;

  size_t left = 0;
  size_t right = size - 1;

  while (left <= right) {
    size_t mid = left + (right - left) / 2;
    const Data& midVal = (*this)[mid];

    if (midVal == value) {
      return true;
    } else if (midVal < value) {
      left = mid + 1;
    } else {
      if (mid == 0) break; // Evita underflow
      right = mid - 1;
    }
  }

  return false;
}


/* ************************************************************************** */

// Membri specifici ClearableContainer
template <typename Data>
void SetLst<Data>::Clear() noexcept {
    List<Data>::Clear();
}

/* ************************************************************************** */

}
