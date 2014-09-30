#include <math.h>
#include "matrix.hpp"
#include <iostream>
using namespace std;
//! constructor
tuple::tuple(void){
  v[0] = v[1] = v[2] = 0;
}
  
//! set the value of the current tuple
void tuple::setValue(double x, double y, double z){
  v[0] = x, v[1] = y, v[2] = z;
}


  
//! constructor
matrix::matrix(void){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++) 
      mat[i][j] = 0;
  }
}

//! load identity matix
void matrix::initIdentity(void){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(i == j) mat[i][j] = 1;
      else mat[i][j] = 0;
    }
  }
}
  
//! post multiply matrix present to this
void matrix::multiplyPost(matrix* _mat){
  double temp[3][3];
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      temp[i][j] = 0;
      for(int k = 0; k < 3; k++) temp[i][j] += mat[i][k] * _mat->mat[k][j];
    }
  }
 
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++) mat[i][j] = temp[i][j];
  }
}
  
//! tuple denoting init as rot along a given direction
void matrix::initAxisRot(tuple* u, double theta){
  double rad = theta * M_PI / 180.0;
  double s = sin(rad);
  double c = cos(rad);
  double ux = u->v[0], uy = u->v[1], uz = u->v[2];
  mat[0][0] = c + ux * ux * (1 - c); 
  mat[0][1] = ux * uy * (1 - c) - uz * s;
  mat[0][2] = ux * uz * (1 - c) + uy * s;
  
  mat[1][0] = uy * ux * (1 - c) + uz * s;
  mat[1][1] = c + uy * uy * (1 - c);
  mat[1][2] = uy * uz * (1 - c) - ux * s;
  
  mat[2][0] = uz * ux * (1 - c) - uy * s;
  mat[2][1] = uz * uy * (1 - c) + ux * s;
  mat[2][2] = c + uz * uz * (1 - c);

}
  
//! apply current on tuple
void matrix::apply(tuple* u){
  int a[3];
  for(int i = 0; i < 3; i++) a[i] = u->v[i];
  for(int i = 0; i < 3; i++){
    double s = 0;
    for(int j = 0; j < 3; j++){
      s += mat[i][j] * a[j];
    }
    u->v[i] = s;
  }
}

//! copyMatrix in array
void matrix::copyArray(double ans[3][3]){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      ans[i][j] = mat[i][j];
    }
  }
}
/*
void print(double a[3][3]){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++) cout<<a[i][j]<<" "; cout<<endl;
  }
}

void print(tuple t){
  for(int i = 0; i < 3; i++) cout<<t.v[i]<<" "; cout<<endl;
}
*/
//! get the matrix corresponding to rotation in local axis
void matrix::getLocalAxisRotMatrix(tuple* theta, double ans[3][3]){
  tuple tx, ty, tz;
  tx.setValue(1, 0, 0);
  ty.setValue(0, 1, 0);
  tz.setValue(0, 0, 1);
  matrix rx, ry, rz;
  rx.initAxisRot(&tx, theta->v[0]);
  rx.apply(&ty);
  rx.apply(&tz);
    
  ry.initAxisRot(&ty, theta->v[1]);
  ry.apply(&tz);
  
  rz.initAxisRot(&tz, theta->v[2]);
  
  rz.multiplyPost(&ry);
  rz.multiplyPost(&rx);
  
  rz.copyArray(ans);
}

/*
int main(){
  tuple t;
  t.setValue(90, 0, 0);
  matrix m;
  double a[3][3];
  m.getLocalAxisRotMatrix(&t, a);
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++) cout<<a[i][j]<<" ";
    cout<<endl;
  }
}*/

