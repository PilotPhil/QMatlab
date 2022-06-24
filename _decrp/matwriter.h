#ifndef MATWRITER_H
#define MATWRITER_H

#include <QString>
#include <mat.h>
#include <Eigen/Core>
#include <QMap>
#include <QFileInfo>

namespace QMatlab {

/**
 * @brief setMatrix 设置矩阵
 * @param matFilePath
 * @param matrixName
 * @param matrix
 * @return
 */
bool setMatrix(const QString& matFilePath, const QString& matrixName, const Eigen::MatrixXd& matrix);

/**
 * @brief setParam 设置单个参数
 * @param matFilePath
 * @param paramName
 * @param param
 * @return
 */
bool setParam(const QString& matFilePath, const QString& paramName, double param);

/**
 * @brief setMultiParams 设置多个参数
 * @param matFilePath
 * @param paramMap
 * @return
 */
bool setMultiParams(const QString& matFilePath, const QMap<QString, double>& paramMap);

/**
 * @brief checkMatFile 校验mat文件是否存在
 * @param matFilePath
 * @return
 */
bool isMatFileExist(const QString& matFilePath);


}

#endif // MATWRITER_H
