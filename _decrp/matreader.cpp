#include "matreader.h"

namespace QMatlab {


bool getMatrix(const QString& matFilePath, const QString& matrixName, Eigen::MatrixXd& matrix) {
  //1.open mat file
  MATFile* pmat = matOpen(matFilePath.toStdString().c_str(), "r");
  if (pmat == NULL)
    return false;

  //2.get variable
  mxArray* mxArray = matGetVariable(pmat, matrixName.toStdString().c_str());
  if (mxArray == NULL)
    return false;

  //3.get data
  double* data = (double*)mxGetData(mxArray);
  if (data == NULL)
    return false;

  //4.convert 2 matrix
  auto rows = mxGetM(mxArray);//row
  auto cols = mxGetN(mxArray);//col
  matrix.resize(rows, cols);

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      matrix(r, c) = data[rows * c + r];
    }
  }

  //5.free
  matClose(pmat);
  mxFree(data);

  return true;
}


bool getParam(const QString& matFilePath, const QString& paramName, double& param) {
  //using getMatrix to modify
  Eigen::MatrixXd matrix;
  auto flag = getMatrix(matFilePath, paramName, matrix);

  if (flag) {
    if (matrix.rows() < 1 || matrix.cols() < 1) {
      return false;
    }
    param = matrix(0, 0);
    return true;
  } else {
    return false;
  }
}


bool getMultiParams(const QString& matFilePath, QMap<QString, double>& paramMap) {
  //1.open mat file
  MATFile* pmat = matOpen(matFilePath.toStdString().c_str(), "r");
  if (pmat == NULL)
    return false;

  mxArray* mxArray = NULL;
  double* data = NULL;
  for (auto it = paramMap.begin(); it != paramMap.end(); it++) {
    //2.get variable
    mxArray = matGetVariable(pmat, it.key().toStdString().c_str());
    if (mxArray == NULL)
      return false;

    //3.get data
    data = (double*)mxGetData(mxArray);
    if (data == NULL)
      return false;

    //4.convert 2 matrix
    auto rows = mxGetM(mxArray);//row
    auto cols = mxGetN(mxArray);//col

    if (rows <= 0 || cols <= 0)
      return false;
    paramMap.insert(it.key(), *data);
  }

  //5.free
  matClose(pmat);
  mxFree(data);

  return true;
}


bool getCell(const QString& matFilePath, const QString& cellName, Cell& cell) {
  //1.open mat file
  MATFile* pmat = matOpen(matFilePath.toStdString().c_str(), "r");
  if (pmat == NULL)
    return false;

  //2.get variable
  mxArray* mxArray = matGetVariable(pmat, cellName.toStdString().c_str());
  if (mxArray == NULL)
    return false;

  //3.get cell
  auto rows = mxGetM(mxArray);
  auto cols = mxGetN(mxArray);

  cell.resize(rows, cols);

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      //get contents;
      auto cl = mxGetCell(mxArray, r * cols + c);

      auto cell_rows = mxGetM(cl);
      auto cell_cols = mxGetN(cl);

      cell(r, c).resize(cell_rows, cell_cols);

      double* cell_contents = mxGetPr(cl);

      //cell 取是按列来取的（cell_contents是按列存在数组内的）
      for (size_t cc = 0; cc < cell_cols; cc++) {
        for (size_t rr = 0; rr < cell_rows; rr++) {
          cell(r, c)(rr, cc) = *(cell_contents + cell_rows * cc + rr);
        }
      }
    }
  }

  return true;
}


}
