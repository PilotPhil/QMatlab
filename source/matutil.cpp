#include "matutil.h"

namespace QMatlab {
namespace MatUtil {

/*--------------------reader--------------------*/
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


bool getMatrix(const QString& matFilePath, const QString& matrixName, Eigen::Matrix<double, 6, 6>& matrix) {
  Eigen::MatrixXd matrixxd;
  auto flag = getMatrix(matFilePath, matrixName, matrixxd);

  if (flag) {
    matrix = matrixxd;
    return true;
  } else
    return false;
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

      //cell ????????????????????????cell_contents??????????????????????????????
      for (size_t cc = 0; cc < cell_cols; cc++) {
        for (size_t rr = 0; rr < cell_rows; rr++) {
          cell(r, c)(rr, cc) = *(cell_contents + cell_rows * cc + rr);
        }
      }
    }
  }

  return true;
}

/*--------------------writer--------------------*/
bool setMatrix(const QString& matFilePath, const QString& matrixName, const Eigen::MatrixXd& matrix) {
  MATFile* pmat = NULL;

  //0.check mat file
  if (isMatFileExist(matFilePath)) {
    //?????????????????????
    pmat = matOpen(matFilePath.toStdString().c_str(), "u");
  } else {
    //???????????????????????????????????????
    pmat = matOpen(matFilePath.toStdString().c_str(), "w");
  }

  const int rows = matrix.rows();
  const int cols = matrix.cols();

  double* array = new double[rows * cols];

  //mat?????????array??????????????????!!!
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
    //?????????????????????
    pmat = matOpen(matFilePath.toStdString().c_str(), "u");
  } else {
    //???????????????????????????????????????
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
    //?????????????????????
    pmat = matOpen(matFilePath.toStdString().c_str(), "u");
  } else {
    //???????????????????????????????????????
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
  if (fileInfo.exists() == false) { //????????????????????????
    return false;
  } else if (fileInfo.suffix() != "mat") { //???????????????mat??????
    return false;
  }
  return true;
}

}
}
