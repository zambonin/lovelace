#include <iostream>
#include <valarray>
#include <fstream>
#include <omp.h>

template <class T> class Matrix {
  private:
    std::valarray<T> data;
    size_t dim1;
    size_t dim2;

  public:
    Matrix () { }
    Matrix (size_t r, size_t c) {
      dim1 = r;
      dim2 = c;
      data = std::valarray<T>(0, dim1*dim2);
    }

    std::valarray<T> row(size_t i) {return data[std::slice(dim2 * i, dim2, 1)];}
    std::valarray<T> col(size_t j) {return data[std::slice(j, dim1, dim2)];}
    inline T& operator()(size_t r, size_t c) {return data[r*dim2+c];}

    constexpr size_t rows() {return dim1;}
    constexpr size_t columns() {return dim2;}
};

int main(int argc, char *argv[]) {

  //Matrices to multiply
  Matrix<int> A, B, C;

  /*** Dealing with inputs, the silly way ***/
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0] << " [input matrix 1] [input matrix 2] [output matrix], where all matrices reside in files" << std::endl;
    return 1;
  }

  std::ifstream infile;
  infile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

  /*First input*/
  try {
    infile.open(argv[1]);
    size_t r, c, cells;
    int value;
    infile >> r >> c >> cells;
    //std::cout << r << " " << c << " " << cells << "\n";
    A = Matrix<int>(r, c);
    while (cells-- > 0) { //read all cells in the input file
      infile >> r >> c >> value;
      A(r,c) = value;
      //std::cout << r << " " << c << " " << A(r,c) << "\n";
    }
    infile.close();
  } catch (std::ifstream::failure e) {
    std::cerr << "Exception handling input file" << argv[1] << std::endl;
  }

  /*Second input*/
  try {
    infile.open(argv[2]);
    size_t r, c, cells;
    int value;
    infile >> r >> c >> cells;
    //std::cout << r << " " << c << " " << cells << "\n";
    B = Matrix<int>(r, c);
    while (cells-- > 0) { //read all cells in the input file
      infile >> r >> c >> value;
      B(r,c) = value;
      //std::cout << r << " " << c << " " << B(r,c) << "\n";
    }
    infile.close();
  } catch (std::ifstream::failure e) {
    std::cerr << "Exception handling input file" << argv[2] << std::endl;
  }

  // Checks if matrices are compatible
  if (A.columns() != B.rows()) {
    std::cerr << "Matrices must have compatible sizes" << std::endl;
    return 1;
  }

  C = Matrix<int>(A.rows(),B.columns());

  #pragma omp parallel for shared(C) schedule(dynamic)
  for (size_t i = 0; i < A.rows(); ++i)
    for (size_t k = 0; k < A.columns(); ++k) {
      int a = A(i, k);
      for (size_t j = 0; j < B.columns(); ++j)
        C(i,j) += a * B(k,j);
    }

// #pragma omp parallel for schedule(dynamic)
//   for (size_t i = 0; i < A.rows(); ++i) {
//     auto r = A.row(i);
//     for (size_t j = 0; j < B.columns(); ++j)
//       C(i,j) = (r * B.col(j)).sum();
//   }	

  std::ofstream outfile;
  outfile.exceptions (std::ofstream::failbit | std::ofstream::badbit);

  /*Write output*/
  try {
    outfile.open(argv[3]);
    size_t cells = 0;       //number of non-zero cells
    size_t i, k;
    //computes number of non-zero cells
    for (i = 0; i < C.rows(); ++i)
      for (k = 0; k < C.columns(); ++k)
	if (C(i,k) != 0) ++cells;

    outfile << C.rows() << " " << C.columns() << " " << cells << "\n";
    for (i = 0; i < C.rows(); ++i)
      for (k = 0; k < C.columns(); ++k)
	if (C(i,k) != 0)
	  outfile << i << " " << k << " " << C(i,k) << "\n";

    outfile.close();
  } catch (std::ifstream::failure e) {
    std::cerr << "Exception handling output file" << argv[1];
  }

}
