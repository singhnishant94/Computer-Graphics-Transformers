#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

struct tuple{
  double v[3];
  
  //! constructor
  tuple(void);
  
  //! set the value of the current tuple
  void setValue(double, double, double);
};

struct matrix{
  double mat[3][3];
  
  //! constructor
  matrix(void);

  //! load identity matix
  void initIdentity(void);
  
  //! post multiply matrix present to this
  void multiplyPost(matrix*);
  
  //! tuple denoting init as rot along a given direction
  void initAxisRot(tuple*, double);
  
  //! apply current on tuple
  void apply(tuple*);
  
  //! copyMatrix in array
  void copyArray(double[3][3]);
  
  //! get the matrix corresponding to rotation in local axis
  void getLocalAxisRotMatrix(tuple*, double[3][3]);
};

#endif
