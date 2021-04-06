#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <eigen3/Eigen/Dense>
#include <memory>

namespace function
{
/**
 *  Class storing the data to solve the problem (0.5 x*Q*x + 2*qx) s.t. Ax = b
*/
class ProblemData 
{
public:
    ProblemData(std::shared_ptr<Eigen::MatrixXd> Q, std::shared_ptr<Eigen::VectorXd> q, 
                std::shared_ptr<Eigen::MatrixXd> A, std::shared_ptr<Eigen::VectorXd> b,
                std::shared_ptr<Eigen::VectorXd> P_k, std::shared_ptr<int> n, 
                std::shared_ptr<double> rho);

    ProblemData(Eigen::MatrixXd Q, Eigen::VectorXd q,
                Eigen::MatrixXd A, Eigen::VectorXd b);

    //Compute cost function for given x
    double compute_obj(const Eigen::VectorXd& x);

    //Compute cost function for given x. Temp. functionality for pybind testing
    double compute_obj_pybind(const Eigen::VectorXd& x);

    //Compute gradient of cost function for a given x
    Eigen::VectorXd compute_grad_obj(const Eigen::VectorXd& x);

    //Compute gradient of objective function for a given x. Temp. functionality for pybind testing
    Eigen::VectorXd compute_grad_obj_pybind(const Eigen::VectorXd& x);

    void set_bounds(Eigen::VectorXd lb, Eigen::VectorXd ub) {lb_ = lb; ub_ = ub;}

    /**
     * The following data should be moved to private with getters and setters
     */
    std::shared_ptr<Eigen::MatrixXd> Q_;
    std::shared_ptr<Eigen::VectorXd> q_;
    std::shared_ptr<Eigen::MatrixXd> A_;
    std::shared_ptr<Eigen::MatrixXd> ATA_;
    std::shared_ptr<Eigen::VectorXd> b_;
    std::shared_ptr<Eigen::VectorXd> Pk_;
    std::shared_ptr<Eigen::VectorXd> bPk_;
    
    std::shared_ptr<Eigen::VectorXd> ATbPk_;
    
    Eigen::VectorXd lb_;
    Eigen::VectorXd ub_;
    std::shared_ptr<double> rho;
    std::shared_ptr<int> n;
    //Temporary PyBind variables to get around Eigen::Ref issues
    Eigen::MatrixXd Q_e;
    Eigen::VectorXd q_e;
    Eigen::MatrixXd A_e;
    Eigen::VectorXd b_e;

    //FISTA related optimization variables
    Eigen::VectorXd y_k;
    Eigen::VectorXd y_k_1;
    Eigen::VectorXd x_k;
    Eigen::VectorXd x_k_1;
    double G_k_norm;

private:
};

} //namespace function

#endif