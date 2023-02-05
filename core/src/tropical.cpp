#include "../include/tropical.h"



using std::string;
std::ostream& operator<<(std::ostream & stream, const MaxAlgMatrixXd& matrixXd) {
    return stream << matrixXd.cast<double>();
}


double spectral_radius(const MaxAlgMatrixXd &matrixXd) {
    int n = 1;
    double current_det = static_cast<double>(matrixXd.trace());
    MaxAlgMatrixXd temp = matrixXd;

    for (int i = 1; i < matrixXd.rows(); ++i){
        temp *= matrixXd;
        current_det = std::max(current_det,pow(static_cast<double>(temp.trace()), d(1,++n)));
    }
    return current_det;
}

MaxAlgMatrixXd clini(const MaxAlgMatrixXd &matrixXd) {
    size_t n = matrixXd.rows();

    MaxAlgMatrixXd A(n,n);
    MaxAlgMatrixXd temp = matrixXd;

    A.setIdentity();
    A += temp;

    for (int i = 1; i < n - 1; ++i) {
        temp *= matrixXd;
        A += temp;
    }
    return A;
}


MaxAlgMatrixXd power(const MaxAlgMatrixXd &matrixXd, int n) {
    MaxAlgMatrixXd temp = matrixXd;
    for (int i = 1; i < n; ++i) {
        temp *= matrixXd;
    }
    return temp;
}
double Tr(const MaxAlgMatrixXd& matrixXd) {
    double current_det = static_cast<double>(matrixXd.trace());
    MaxAlgMatrixXd temp = matrixXd;
    for (int i = 1; i < matrixXd.rows(); ++i){
        temp *= matrixXd;
        current_det = std::max(current_det,static_cast<double>(temp.trace()));
    }

    return current_det;
}

double SpectralRadiusAdvance(const MaxAlgMatrixXd &matrixXd) {

    std::vector<MaxAlgMatrixXd> matrices;

    return 0;
}
