template <typename T>
class Example
{
private:
    int size;
    T *parray;
    T _min;
    T _max;

public:
    Example(T min, T max);
    Example(const T *array, int size);
    double &operator[](int index);
    bool operator==(const Example &) const;
    bool insert(const T *, int);
    bool insert(T);
    T min() const;
    T max() const;
    void min(T);
    void max(T);
    ~Example();
};
