#ifndef MATREADER_H
#define MATREADER_H

#include <QString>
#include <mat.h>
#include <Eigen/Core>
#include <QMap>

namespace QMatlab {



/**
 * @brief getMatrix 获取矩阵
 * @param matFilePath mat文件路径
 * @param varName 变量名
 * @param matrix 返回的cell
 * @return 是否获取成功
 */
bool getMatrix(const QString& matFilePath, const QString& matrixName, Eigen::MatrixXd& matrix);

/**
 * @brief getParam 获取参数
 * @param matFilePath mat文件路径
 * @param paramName 参数名
 * @param param 返回的参数
 * @return 是否获取成功
 */
bool getParam(const QString& matFilePath, const QString& paramName, double& param);

/**
 * @brief getMultiParams
 * @param matFilePath
 * @param paramMap
 * @return
 */
bool getMultiParams(const QString& matFilePath, QMap<QString, double>& paramMap);

/**
 * @brief getCell 获取cell
 * @param matFilePath mat文件路径
 * @param cellName cell名
 * @param cell 返回的cell
 * @return 是否获取成功
 */
bool getCell(const QString& matFilePath, const QString& cellName, Cell& cell);

}

#endif // MATREADER_H
