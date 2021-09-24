// Main program for problem 7

#include "functions.hpp"


int main(){
  arma::vec n_values = vec(2);
  n_values(0) = 10;
  n_values(1) = 100;
  for (int i = 0; i < n_values.size(); i++){
  double n = n_values(i);
  int N = n-2;
  double h = 1/n;
  vec x = linspace(0, 1, n);
  double a = -1/(h*h);
  double d = 2/(h*h);
  mat A = make_tridiagonal(N, a, d);
  mat R = make_tridiagonal(N, 0, 1);
  int k;
  int l;
  double maxA = max_offdiag_symmetric(A, &k, &l);
  vec eigenvalues(N);
  mat eigenvectors(N,N);
  int maxiter, iterations;
  maxiter = 100000000;
  bool converged;
  double tol = 1e-10;
  jacobi_eigensolver(A, R, tol, eigenvalues, eigenvectors, maxiter, 0, converged, k,l);

  vec lambda;  // Analytic eigenvalues
  mat v;       // Analytic eigenvectors
  analytic_eigprob(N, a, d, &lambda, &v);


  uvec index_analytic = sort_index(lambda);

  uvec index = sort_index(eigenvalues);

  ofstream file1;
  file1.open("eigvecs_and_x_values_n" + to_string(int(n_values(i))) + ".txt", ios::out); //opens file1 in out/write mode

  file1 << setw(25) << 0 << setw(25) << 0 << setw(25) << 0 << setw(25) << 0 << endl;
    for (int i = 0; i < N; i++){
      file1 << setw(25) << setprecision(3) << x(i+1);
      for (int k = 0; k < 3; k++){
      file1 << setw(25) << setprecision(8) << eigenvectors(i,index(k));
      }
      file1 << endl;
    }
  file1 << setw(25) << 1 << setw(25) << 0 << setw(25) << 0 << setw(25) << 0 << endl;
  file1.close();

  ofstream file2;
  file2.open("analytical_eigvecs_n" + to_string(int(n_values(i))) + ".txt", ios::out); //opens file2 in out/write mode
  file2 << setw(25) << 0 << setw(25) << 0 << setw(25) << 0 << setw(25) << 0 << endl;
    for (int i = 0; i < N; i++){
      file2 << setw(25) << setprecision(3) << x(i+1);
      for (int k = 0; k < 3; k++){
      file2 << setw(25) << setprecision(8) << v(i,index_analytic(k));
      }
      file2 << endl;
    }
  file2 << setw(25) << 1 << setw(25) << 0 << setw(25) << 0 << setw(25) << 0 << endl;
  file2.close();
}
   return 0;
}
