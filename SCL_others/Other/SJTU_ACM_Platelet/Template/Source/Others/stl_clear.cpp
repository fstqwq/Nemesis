template <typename T>
__inline void clear(T &container) {
    container.clear();
    T(container).swap(container);
}
