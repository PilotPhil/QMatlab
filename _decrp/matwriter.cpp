#include "matwriter.h"

namespace QMatlab {


bool setMatrix(const QString& matFilePath, const QString& matrixName, const Eigen::MatrixXd& matrix) {
  MATFile* pmat = NULL;

  //0.check mat file
  if (isMatFileExist(matFilePath)) {
    //存在，追加模式
    pmat = matOpen(matFilePath.toStdString().c_str(), "u");
  } else {
    //不存在，自动创建，写入模式
    pmat = matOpen(matFilePath.toStdString().c_str(), "w");
  }

  const int rows = matrix.rows();
  const int cols = matrix.cols();

  double* array = new double[rows * cols];

  //mat中数组array是按列存储的!!!
  for (int c = 0; c < cols; c++) {
    for (int r = 0; r < rows; r++) {
      array[rows * c + r] = matrix(r, c);
    }
  }

  mxArray* mxArray = mxCreateDoubleMatrix(rows, cols, mxREAL);
  mxSetData(mxArray, array);
  matPutVariable(pmat, matrixName.toStdString().c_str(), mxArray);
  matClose(pmat);
  return true;
}


bool setParam(const QString& matFilePath, const QString& paramName, double param) {
  MATFile* pmat = NULL;

  //0.check mat file
  if (isMatFileExist(matFilePath)) {
    //存在，追加模式
    pmat = matOpen(matFilePath.toStdString().c_str(), "u");
  } else {
    //不存在，自动创建，写入模式
    pmat = matOpen(matFilePath.toStdString().c_str(), "w");
  }

  double* array = &param;

  mxArray* mxArray = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetData(mxArray, array);
  matPutVariable(pmat, paramName.toStdString().c_str(), mxArray);
  matClose(pmat);
  return true;
}


bool setMultiParams(const QString& matFilePath, const QMap<QString, double>& paramMap) {
  MATFile* pmat = NULL;

  //0.check mat file
  if (isMatFileExist(matFilePath)) {
    //存在，追加模式
    pmat = matOpen(matFilePath.toStdString().c_str(), "u");
  } else {
    //不存在，自动创建，写入模式
    pmat = matOpen(matFilePath.toStdString().c_str(), "w");
  }

  for (auto it = paramMap.begin(); it != paramMap.end(); it++) {
    auto paramName = it.key();
    auto value = it.value();
    double* array = &value;

    mxArray* mxArray = mxCreateDoubleMatrix(1, 1, mxREAL);
    mxSetData(mxArray, array);
    matPutVariable(pmat, paramName.toStdString().c_str(), mxArray);
  }

  return true;
}


bool isMatFileExist(const QString& matFilePath) {
  auto fileInfo = QFileInfo(matFilePath);
  if (fileInfo.exists() == false) { //校验文件是否存在
    return false;
  } else if (fileInfo.suffix() != "mat") { //校验是否为mat文件
    return false;
  }
  return true;
}


}
