#include "convertor.h"

namespace QMatlab {


bool QVector2EigenMatrix(const vecd& vec, Eigen::MatrixXd& matrix) {
  if (vec.isEmpty() == true)
    return false;

  auto len = vec.length();

  matrix.resize(len, 1);

  for (size_t i = 0; i < len; i++) {
    matrix(i, 0) = vec[i];
  }
  return true;
}


bool EigenMatrix2QVector(const Eigen::MatrixXd& matrix, vecd& vec) {
  auto len = matrix.rows();

  if (len <= 0)
    return false;

  vec.resize(len);

  for (size_t i = 0; i < len; i++) {
    vec[i] = matrix(i, 0);
  }

  return true;
}


bool Array2QVector(double* array, vecd& vec, int length) {
  vec.resize(length);

  for (size_t i = 0; i < length; i++) {
    vec[i] = array[i];
  }

  return true;
}


bool QVector2Array(const vecd& vec, double* array) {
  auto len = vec.length();

  array = new double[len];

  for (size_t i = 0; i < len; i++) {
    array[i] = vec[i];
  }

  return true;
}


}
