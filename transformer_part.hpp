#ifndef _TRANSFORMER_PART_
#define _TRANSFORMER_PART_

#include <vector>

// helper class to 
struct vertex_t{
  double x, y, z;
  
  //! sets the vertex value
  void setVertex(double, double, double);
  
  //! change value
  void updateValue(double, double, double);
  
  //! scale the vertices
  void scaleValue(double);
};

struct part_t{
  
  int partNum;                             //! the part number for denoting the list numebr
  std::vector<part_t*> children;           //! pointer to children connected to this
  vertex_t end_A, end_B, center;           //! three points for joining
  vertex_t *anchorLocal, *anchorRemote;    //! anchorLocal -> pointer local anchor, anchorRemote -> anchor to the parent
  double theta_x, theta_y, theta_z;        //! theta_y , theta_z denote the angle relative to parent
  vertex_t angleMin, angleMax;             //! the angular constraints 
  
  //!contructor
  part_t(void);

  //! set to a given length
  void setLength(double);
  
  //! set part number
  void setPartNum(int);
  
  //! add child
  void addChild(part_t*);
  
  //! connects this to the parent, 
  void connect(vertex_t*, part_t*, vertex_t*, double, double, double);
  
  //! draw part function to draw it and the children
  void drawPart(void);
  
  //! function to change theta_x
  void change_theta_x(double);
  
  //! function to change theta_y
  void change_theta_y(double);
  
  //! function to change theta_z
  void change_theta_z(double);
  
  //! function as a hole to overpass the constraints
  void change_theta_sys(double, double, double);
  
  //! function to complete frame
  void (*completeFrame)(void);
  
  //! set constraints minimum values
  void setMinAngularConstraints(vertex_t);
  
  //! set constraints max values
  void setMaxAngularConstraints(vertex_t);
  
    //! set constraints minimum values, overloaded
  void setMinAngularConstraints(double, double, double);
  
  //! set constraints max values , overloaded
  void setMaxAngularConstraints(double, double, double);

  //! checking the constraints, return true/ false, value, axis
  int checkConstraint(double, char);
};

enum joint_t{
  THIGH1HIP, 
  THIGH2HIP, 
  LEG1THIGH1,
  LEG2THIGH2,
  FOOT1LEG1,
  FOOT2LEG2,
  TORSOHIP,
  SHOULDERTORSO,
  NECKSHOULDER,
  ARM1SHOULDER,
  ARM2SHOULDER,
  HAND1ARM1,
  HAND2ARM2,
  DUMMY,
  ROOT
};

struct body_t{
  //! the various parts of a transformer
  part_t *hip;    // the hip is the root
  part_t *torso;
  part_t *thigh1, *thigh2, *leg1, *leg2, *foot1, *foot2;
  part_t *shoulder;
  part_t *neck;
  part_t *arm1, *arm2, *hand1, *hand2;
  
  //! body parameters
  vertex_t center;                        // the center of entire body
  double theta_x, theta_y, theta_z;       // orientation
  
  //!constructor
  body_t(void);
  
  //!destructor to free memory
  ~body_t(void);
  
  //! formBasicFrame
  void makeBody(void);
  
  //! doing dfs to make the given object
  void drawBody(void);

  //! translate the entire body
  void translateBody(double, double, double);
  
  //! rotate the entire body
  void rotateBody(double, double, double);
  
  //! function to move the joint here
  void changeOrientation(joint_t, vertex_t);

  //! fill the parts of the body with respective drawings
  void initBodyStructure(void);
  
  //! add the constraints to the various parts
  void addConstraints(void);
};


#endif
