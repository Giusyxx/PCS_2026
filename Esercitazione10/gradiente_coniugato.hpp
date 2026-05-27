#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>

Eigen::VectorXd gradiente_coniugato (
	const Eigen::MatrixXd& A,
	const Eigen::VectorXd& b,
	const Eigen::VectorXd& x0,
	double res_tol,
	unsigned int it_max,
	unsigned int& it)
	
{
	Eigen::VectorXd x = x0;
	Eigen::VectorXd res = b - A * x;
	Eigen::VectorXd p = res;
	
	double res_norm_0 = res.norm();
	
	it = 0;
	
	while (it < it_max && res.norm() > res_tol * res_norm_0) {
		
		Eigen::VectorXd Ap = A * p; // calcolo A * p una sola volta
		
		double den = (p.transpose() * Ap).value(); // calcolo denominatore comune
		double alpha_k = ((p.transpose() * res).value()) / den; // calcolo alpha_k
		
		x = x + alpha_k * p; // aggiorno x
		
		res = res - alpha_k * Ap; // aggiorno il residuo
		
		double beta_k = ((Ap.transpose() * res).value()) / den; //calcolo beta_k con il nuovo residuo
		
		p = res - beta_k * p; // aggiorno la direzione p
		
		it++;
	}
	
	return x;
}

