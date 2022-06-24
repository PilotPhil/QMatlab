#include <QCoreApplication>
#include <QDebug>

#include "QMatlab.h"

#define TEST 1


int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

#if TEST
  {
    using namespace QMatlab::MatUtil;

    QVector<double> vec {1, 2, 3, 4, 5, 6};
    Eigen::MatrixXd matrix;
    auto flag = QMatlab::QVector2EigenMatrix(vec, matrix);

    QVector<double> vec2;
    auto flag2 = QMatlab::EigenMatrix2QVector(matrix, vec2);


    auto path = R"(C:\Users\dwb\Desktop\input.mat)";
    Eigen::MatrixXd m1;
    getMatrix(path, "Ei", m1);

    double e0;
    getParam(path, "Ei", e0);

    Cell cell;
    auto flag3 = getCell(R"(C:\Users\dwb\Desktop\result.mat)", "F_hull", cell);
    auto aa = cell(0, 0);
    auto bb = cell(90, 0);


    setMatrix(R"(C:\Users\dwb\Desktop\result.mat)", "test_matrix", aa);
    setParam(R"(C:\Users\dwb\Desktop\result.mat)", "test_param", 114514);

    QMap<QString, double> map;
    map["a"] = 1;
    map["b"] = 2;
    map["c"] = 3;
    setMultiParams(R"(C:\Users\dwb\Desktop\result.mat)", map);
  }
#endif

  return a.exec();
}
