#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include "gradiente_coniugato.hpp"

double condA(const Eigen::MatrixXd& A) {
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
	Eigen::VectorXd singularValuesA = svd.singularValues();
	return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int main(int argc, char **argv) {
	const double tol = 1.0e-15;
	const unsigned int it_max = 10000;
	const double res_tol = 1.0e-12;
	
	for (unsigned int n = 2; n <= 20; ++n) {
		//matrice casuale 
		Eigen::MatrixXd B = Eigen::MatrixXd::Random (n,n);
		
		if (std::abs(B.determinant()) < tol)
		continue;
	
		Eigen::MatrixXd A = B.transpose() * B; // A simmetrica e definita positica
		Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n); // soluzione esatta: vettore di tutti 1
		Eigen::VectorXd b = A * x_ex; // termine noto b
		Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n); // vettore x0 di tutti zeri
	
		unsigned int it = 0;
	
		// chiamata alla funzione gradiente coniugato
		Eigen::VectorXd x = gradiente_coniugato ( A, b, x0, res_tol, it_max, it);
	
		const auto err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() : (x-x_ex).norm() / x_ex.norm();
	
		Eigen::VectorXd res_finale = b - A * x;
		Eigen::VectorXd res_iniziale = b - A * x0;
		double res_rel_finale = res_finale.norm() / res_iniziale.norm();
		
		std::cout << "\nDimensione n = " << n << std::endl;
		std::cout.precision(2);
		std::cout << std::scientific << "Matrix Cond: "<< condA(A) << std::endl;
	
		std::cout.precision(4);
		std::cout << std::scientific << "it/it_max: " << it << "/" << it_max << std::endl;
		std::cout << std::scientific << "Residuo Relativo finale: " << res_rel_finale << " (Target: " << res_tol << ")" << std::endl;
		std::cout << std::scientific << "Errore Relativo rispetto a soluzione esatta: " << err_rel << std::endl;
	
		std::cout << "\nSoluzione calcolata x:\n" << x << std::endl;
		
		}
	
		return 0;
}
	