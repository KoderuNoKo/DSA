template<class T>
int Heap<T>::size(){
    return this->size;
}

template<class T>
bool Heap<T>::isEmpty(){
    return (this->size == 0);
}

template<class T>
T Heap<T>::peek(){
    if (elements) {
        return elements[0];
    }
    return NULL;
}

template<class T>
bool Heap<T>::contains(T item){
    for (int i = 0; i < count; i++) {
        if (elements[i] == item) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Heap<T>::pop(){
    if (this->isEmpty()) {
        return false;
    }
    
    elements[0] = elements[count - 1];
    this->reHeapDown(0);
    return true;
}
