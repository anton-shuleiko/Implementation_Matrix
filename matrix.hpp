#pragma once

#include <algorithm>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 private:
  std::vector<std::vector<T>> arr_ =
      std::vector<std::vector<T>>(N, std::vector<T>(M, T()));

 public:
  //////////////////Constructors/////////////////
  Matrix() = default;
  Matrix(const std::vector<std::vector<T>>& vec);
  Matrix(const T& elem);
  Matrix(const Matrix<N, M, T>& matr);
  ////////////////////Операторы//////////////////////////
  Matrix& operator+=(const Matrix<N, M, T>& matr);
  Matrix& operator-=(const Matrix<N, M, T>& matr);
  Matrix& operator=(const Matrix<N, M, T>& matr);

  template <size_t A, size_t B>
  bool operator==(const Matrix<A, B, T>& matr);

  Matrix operator+(const Matrix<N, M, T>& matr) const;
  Matrix operator-(const Matrix<N, M, T>& matr) const;
  Matrix operator*(const T& elem) const;

  template <size_t L>
  Matrix<N, L, T> operator*(const Matrix<M, L, T>& matr) const;

  T operator()(size_t indi, size_t indj) const;
  T& operator()(size_t indi, size_t indj);

  ////////////////Методы//////////////////////////////////
  Matrix<M, N, T> Transposed();
  T Trace() const;
};

////////////////////////////Конструкторы////////////////////////////////
template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const std::vector<std::vector<T>>& vec) {
  arr_ = vec;
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const T& elem) {
  arr_ = std::vector<std::vector<T>>(N, std::vector<T>(M, elem));
}
template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const Matrix<N, M, T>& matr) {
  this->arr_ = matr.arr_;
}
//////////////Операторы////////////////////////////////////////////////
template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& matr) {
  for (size_t indi = 0; indi < N; indi++) {
    for (size_t indj = 0; indj < M; indj++) {
      arr_[indi][indj] += matr.arr_[indi][indj];
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix<N, M, T>& matr) {
  for (size_t indi = 0; indi < N; indi++) {
    for (size_t indj = 0; indj < M; indj++) {
      arr_[indi][indj] -= matr.arr_[indi][indj];
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
template <size_t A, size_t B>
bool Matrix<N, M, T>::operator==(const Matrix<A, B, T>& matr2) {
  return (N == A && M == B && arr_ == matr2.arr_);
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator=(const Matrix<N, M, T>& matr) {
  this->arr_ = matr.arr_;
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator+(const Matrix<N, M, T>& matr) const {
  Matrix<N, M, T> res = *this;
  res += matr;
  return res;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator-(const Matrix<N, M, T>& matr) const {
  Matrix<N, M, T> res = *this;
  res -= matr;
  return res;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator*(const T& elem) const {
  Matrix<N, M, T> res = *this;
  for (size_t indi = 0; indi < N; indi++) {
    for (size_t indj = 0; indj < M; indj++) {
      res.arr_[indi][indj] *= elem;
    }
  }
  return res;
}

template <size_t N, size_t M, typename T>
template <size_t L>
Matrix<N, L, T> Matrix<N, M, T>::operator*(const Matrix<M, L, T>& matr) const {
  Matrix<N, L, T> res;
  for (size_t indi = 0; indi < N; indi++) {
    for (size_t indj = 0; indj < L; indj++) {
      for (size_t indm = 0; indm < M; indm++) {
        res(indi, indj) += (*this)(indi, indm) * matr(indm, indj);
      }
    }
  }
  return res;
}

template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::operator()(size_t indi, size_t indj) const {
  return this->arr_[indi][indj];
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t indi, size_t indj) {
  return this->arr_[indi][indj];
}

//////////////////////////////Методы////////////////////////////
template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() {
  Matrix<M, N, T> res;
  for (size_t indi = 0; indi < N; indi++) {
    for (size_t indj = 0; indj < M; indj++) {
      res(indj, indi) = arr_[indi][indj];
    }
  }
  return res;
}

template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::Trace() const {
  Matrix<N, M, T> tmp = *this;
  return AnotherTrace(tmp);
}

/////////////////Functions///////////////////////
template <size_t N, typename T>
T AnotherTrace(Matrix<N, N>& matr) {
  T res;
  res = matr(0, 0);
  for (size_t indi = 1; indi < N; indi++) {
    res += matr(indi, indi);
  }
  return res;
}

template <size_t N, typename T = int64_t>
T AnotherTrace(Matrix<N, N, T>& matr) {
  T res;
  res = matr(0, 0);
  for (size_t indi = 1; indi < N; indi++) {
    res += matr(indi, indi);
  }
  return res;
}
