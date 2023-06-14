#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>

template <typename T>
class DataBlob
{
private:
    size_t rows;
    size_t cols;
    size_t channels;
    size_t *refcount;
    T *data;

public:
    size_t getRows() const
    {
        return rows;
    }

    size_t getCols() const
    {
        return cols;
    }

    size_t getChannels() const
    {
        return channels;
    }

    size_t getRefCount() const
    {
        return *refcount;
    }

    DataBlob(size_t _cols = 0, size_t _rows = 0, size_t _channels = 0)
        : rows(_rows),
          cols(_cols),
          channels(_channels),
          refcount(new size_t(1))

    {

        int ret1 = posix_memalign((void **)&data, 256, _rows * _cols * _channels * sizeof(T));

        if (ret1 != 0)
        {
            std::cerr << "memory aligned failed" << std::endl;
            return;
        }
        std::memset(data, 0, _rows * _cols * _channels * sizeof(T));
    }
    DataBlob(const DataBlob &other)
    {

        rows = other.rows;
        cols = other.cols;
        channels = other.channels;
        data = other.data;
        refcount = other.refcount;

        // Increment the reference count
        (*refcount)++;
    }
    void generateRandomMatrix();
    ~DataBlob()
    {

        if (--(*refcount) == 0)
        {
            free(data);
            delete refcount;
        }
    }
    DataBlob<T> &operator+=(const DataBlob<T> &other)
    {
        if (isEmpty() || other.isEmpty())
        {
            std::cerr << "data blob is empty" << std::endl;
            return *this;
        }
        *(this) = *(this) + other;
        return *this;
    }

    DataBlob<T> &operator=(const DataBlob &other)
    {

        if (this != &other)
        {
            this->~DataBlob();
            rows = other.rows;
            cols = other.cols;
            channels = other.channels;
            data = other.data;
            refcount = other.refcount;
            (*refcount)++;
        }
        return *this;
    }
    // DataBlob &operator=(DataBlob &&other);\

    bool operator==(const DataBlob &other) const
    {

        if (rows != other.rows || cols != other.cols || channels != other.channels)
        {
            return false;
        }
        return std::memcmp(data, other.data, rows * cols * channels * sizeof(T)) == 0;
    }
    bool operator!=(const DataBlob &other) const
    {

        return !(*this == other);
    }

    template <typename V>
    operator DataBlob<V>() const
    {
        DataBlob<V> result(rows, cols, channels);
        // Perform the type conversion here
        for (size_t i = 0; i < rows * cols * channels; ++i)
        {
            result(i) = static_cast<V>(this->data[i]);
        }
        return result;
    }

    DataBlob<T> operator-(const DataBlob<T> &other) const
    {
        if (isEmpty() || other.isEmpty())
        {
            std::cerr << "DataBlob is empty" << std::endl;
            return DataBlob<T>();
        }

        if (rows != other.rows || cols != other.cols || channels != other.channels)
        {
            std::cerr << "size is not the same!" << std::endl;
            return DataBlob<T>();
        }

        size_t n = rows * cols * channels;
        DataBlob<T> result(cols, rows, channels);
        size_t startIndex = 0;

        for (size_t i = startIndex; i < n; i++)
        {
            result.data[i] = data[i] - other.data[i]; // subtraction instead of addition
        }

        return result;
    }

    DataBlob<T> operator+(const DataBlob &other) const
    {
        if (isEmpty() || other.isEmpty())
        {
            std::cerr << "DataBlob is empty" << std::endl;
            return DataBlob<T>();
        }

        if (rows != other.rows || cols != other.cols || channels != other.channels)
        {
            std::cerr << "size is not the same!" << std::endl;
            return DataBlob<T>();
        }
        size_t n = rows * cols * channels;
        DataBlob<T> result(cols, rows, channels);
        size_t startIndex = 0;
        for (size_t i = startIndex; i < n; i++)
        {

            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    DataBlob<T> operator/(const DataBlob &other) const
    {
        if (isEmpty() || other.isEmpty())
        {
            std::cerr << "DataBlob is empty" << std::endl;
            return DataBlob<T>();
        }

        if (rows != other.rows || cols != other.cols || channels != other.channels)
        {
            std::cerr << "size is not the same!" << std::endl;
            return DataBlob<T>();
        }

        size_t n = rows * cols * channels;
        DataBlob<T> result(cols, rows, channels);
        size_t startIndex = 0;
        for (size_t i = startIndex; i < n; i++)
        {
            result.data[i] = data[i] / other.data[i];
        }

        return result;
    }

    DataBlob<T> operator*(const DataBlob &other) const
    {
        if (isEmpty() || other.isEmpty())
        {
            std::cerr << "DataBlob is empty" << std::endl;
            return DataBlob();
        }
        if (rows != other.rows || cols != other.cols || channels != other.channels)
        {
            std::cerr << "size is not the same!" << std::endl;
            return DataBlob();
        }
        DataBlob result(cols, rows, channels);
        size_t n = rows * cols * channels;
        size_t startIndex = 0;

        for (size_t i = startIndex; i < n; i++)
        {

            result.data[i] = data[i] * other.data[i];
        }
        return result;
    }

    T &operator()(size_t row, size_t col, size_t channel)
    {
        return data[row * cols * channels + col * channels + channel];
    }
    T *operator+(size_t i)
    {
        return data + i;
    }
    const T *operator+(size_t i) const
    {
        return data + i;
    }
    T &operator()(size_t ind)
    {
        return data[ind];
    }
    const T &operator()(size_t ind) const
    {
        return data[ind];
    }

    const T &operator()(size_t row, size_t col, size_t channel) const
    {
        return data[row * cols * channels + col * channels + channel];
    }
    friend std::ostream &operator<<(std::ostream &output, DataBlob &dataBlob)
    {
        if (dataBlob.isEmpty())
        {
            output << "Datablob is empty" << std::endl;
            return output;
        }
        size_t mSize = dataBlob.rows * dataBlob.cols * dataBlob.channels;
        for (size_t i = 0; i < mSize; i++)
        {

            output << dataBlob.data[i] << " ";
            if ((i + 1) % dataBlob.cols == 0)
            {
                output << std::endl;
            }
        }
        return output;
    }
    inline bool isEmpty() const
    {
        return (rows <= 0 || cols <= 0 || channels == 0 || data == nullptr || refcount == nullptr);
    }
    DataBlob<T> &add_padding(size_t padding)
    {
        if (isEmpty())
        {
            return DataBlob();
        }
        size_t padded_cols = this->cols + 2 * padding;
        size_t padded_rows = this->rows + 2 * padding;
        size_t ch = this->channels;
        size_t padded_size = padded_cols * padded_rows * ch;
        DataBlob<T> padded(padded_cols, padded_rows, ch);

        for (size_t c = 0; c < ch; c++)
        {
            for (size_t y = 0; y < this->rows; y++)
            {
                for (size_t x = 0; x < this->cols; x++)
                {
                    size_t index = (c * this->rows + y) * this->cols + x;
                    size_t padded_index = ((c * padded_rows) + (y + padding)) * padded_cols + (x + padding);
                    padded(padded_index) = (*this)(index);
                }
            }
        }

        *(this) = padded;

        return *this;
    }
    DataBlob<T> &relu()
    {
        if (isEmpty())
        {
            std::cerr << "data blob is empty" << std::endl;
            return *this;
        }
        size_t len = this->cols * this->rows * this->channels;

        // prsize_tf("WITH_NORMAL\n");
        for (size_t i = 0; i < len; i++)
            (*this)(i) = (*this)(i) > 0 ? (*this)(i) : 0;
        return *this;
    }
};
template <typename T>
T dotproduct(const DataBlob<T> &p1, const DataBlob<T> &p2, size_t n);
// for not float dot product
template <typename T>
T dotproduct(const DataBlob<T> &p1, const DataBlob<T> &p2, size_t n)
{
    T sum = 0.0f;
    size_t startIndex = 0;

    for (size_t i = startIndex; i < n; i++)
        sum += (p1(i) * p2(i));
    return sum;
}

template <typename T>
DataBlob<T> convolutional(const DataBlob<T> &inputMatrix, const DataBlob<T> &kernel)
{
    if (inputMatrix.isEmpty() || kernel.isEmpty())
    {
        std::cerr << "Input Matrix or kernel is empty" << std::endl;
        return DataBlob<T>();
    }
    if (inputMatrix.getRows() < kernel.getRows() || inputMatrix.getCols() < kernel.getCols())
    {
        std::cerr << "The input of matrix size cannot be smaller than the kernal size" << std::endl;
        return DataBlob<T>();
    }

    size_t outputcols = inputMatrix.getCols() - kernel.getCols() + 1;
    size_t outputrows = inputMatrix.getRows() - kernel.getRows() + 1;
    size_t outputSize = outputrows * outputcols;
    size_t tempMatrixSize = kernel.getCols() * kernel.getRows() * kernel.getChannels();
    size_t onedtempMatrixSize = kernel.getCols() * kernel.getRows();
    DataBlob<T> outputMatrix(outputcols, outputrows, 1);
    DataBlob<T> tempMatrix(kernel.getCols(), kernel.getRows(), kernel.getChannels());

    size_t temp_matrix_index = 0;

    size_t output_matrix_index = 0;
    size_t start = 0;

    for (size_t k = 1; k <= outputrows; start++)
    {
        // take the temp matrix

        for (size_t i = start; i < (inputMatrix.getCols() * inputMatrix.getRows() * inputMatrix.getChannels()) + start;)
        {
            for (size_t j = i; j < kernel.getCols() + i; j++)
            {

                // tempMatrix.data[temp_matrix_index++] = inputMatrix.data[j];
                tempMatrix(temp_matrix_index++) = inputMatrix(j);
            }

            if (temp_matrix_index == tempMatrixSize)
            {

                temp_matrix_index = 0;
                break;
            }
            else if (temp_matrix_index % onedtempMatrixSize == 0)
            {

                i += inputMatrix.getCols() * inputMatrix.getRows() - ((kernel.getRows() - 1) * inputMatrix.getCols());
            }
            else
            {
                i += inputMatrix.getCols();
            }
        }

        // the dot product is here
        outputMatrix(output_matrix_index++) = dotproduct(tempMatrix, kernel, tempMatrixSize);
        if (start == (inputMatrix.getCols() * k) - kernel.getCols())
        {

            start += kernel.getCols() - 1;
            k++;
        }
    }
    return outputMatrix;
}
