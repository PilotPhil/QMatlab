#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <QObject>
#include <QVector>
#include <Eigen/Core>

namespace QMatlab {
using vecd = QVector<double>;

////转换时行优先还是列优先
//enum major {
//  colMajor,
//  rowMajor
//};


/**
 * @brief QVector2EigenMatrix 向量转eigen矩阵
 * @param vec 输入
 * @param matrix 输出
 * @return 转换是否成功
 */
bool QVector2EigenMatrix(const vecd& vec, Eigen::MatrixXd& matrix);

/**
 * @brief EigenMatrix2QVector eigen矩阵转向量
 * @param matrix 输入
 * @param vec 输出
 * @return 转换是否成功
 */
bool EigenMatrix2QVector(const Eigen::MatrixXd& matrix, vecd& vec);

/**
 * @brief array2QVector 数组转向量
 * @param array 数组
 * @param vec 向量
 * @return 转换是否成功
 */
bool Array2QVector(double* array, vecd& vec, int length);

/**
 * @brief QVector2Array 向量转数组
 * @param vec 向量
 * @param array 数组
 * @return 转换是否成功
 */
bool QVector2Array(const vecd& vec, double* array);



}

#endif // CONVERTOR_H
