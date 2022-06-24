#ifndef MATUTIL_H
#define MATUTIL_H

#include <QString>
#include <mat.h>
#include <Eigen/Core>
#include <QMap>
#include <QFileInfo>

namespace QMatlab {

namespace MatUtil {

/*--------------------reader--------------------*/

using Cell = Eigen::Matrix<Eigen::MatrixXd, Eigen::Dynamic, Eigen::Dynamic>;

/**
 * @brief getMatrix 获取矩阵
 * @param matFilePath mat文件路径
 * @param varName 变量名
 * @param matrix 返回的cell
 * @return 是否获取成功
 */
bool getMatrix(const QString& matFilePath, const QString& matrixName, Eigen::MatrixXd& matrix);

/**
 * @brief getMatrix
 * @param matFilePath
 * @param matrixName
 * @param matrix
 * @return
 */
bool getMatrix(const QString& matFilePath, const QString& matrixName, Eigen::Matrix<double, 6, 6>& matrix);

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

/*--------------------writer--------------------*/
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
}


#endif // MATUTIL_H
