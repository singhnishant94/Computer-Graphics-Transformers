#ifndef _TRANSFORMER_PART_
#define _TRANSFORMER_PART_

#include <vector>
#include <string.h>
#include "gl_framework.hpp"

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
  
  //! current window for passing swapping buffers
  GLFWwindow *window;
  
  //! the renderPart is the renderGL function pointer. part denotes the struct it is in 
  void (*renderPart)(GLFWwindow*);

  //! connecting body like torso - cover
  std::vector<part_t*> connPart;
  
  //!contructor
  part_t(void);

  //! set the window and renderBody function pointers
  void setWindowRender(GLFWwindow*, void (*)(GLFWwindow*));
  
  //! set to a given length
  void setLength(double);

  //! returns length
  double getLength(void);
  
  //! set part number
  void setPartNum(int);
  
  //! add child
  void addChild(part_t*);
  
  //! connects this to the parent, 
  void connect(vertex_t*, part_t*, vertex_t*, double, double, double);
  
  //! connect dependent parts here
  void addConnPart(part_t*);
  
  //! draw part function to draw it and the children
  void drawPart(void);
  
  //! function to change theta_x
  void change_theta_x(double);
  
  //! function to change theta_y
  void change_theta_y(double);
  
  //! function to change theta_z
  void change_theta_z(double);
  
  //! change connPart theta
  void changeConnPartTheta(double, char);

  //! set orientation to a given value with a given speed
  void setAngularOrientation(double, double, double, double, std::string);
  
  //! set Orientation in x 
  void setAngularOrientationX(double, double);
  
  //! set Orientation in y 
  void setAngularOrientationY(double, double);
    
  //! set Orientation in z
  void setAngularOrientationZ(double, double);
  
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
  
  //! shift the rotation point / remote anchor by a given offset
  void shiftRemoteAnchor(double, double, double);
};

enum joint_t{
  THIGH1HIP2, 
  THIGH2HIP2, 
  LEG1THIGH1,
  LEG2THIGH2,
  FOOT1LEG1,
  FOOT2LEG2,
  TORSOHIP1,
  SHOULDERTORSO,
  NECKSHOULDER,
  ARM1SHOULDER,
  ARM2SHOULDER,
  HAND1ARM1,
  HAND2ARM2,
  PALM1HAND1,
  PALM2HAND2,
  CHESTCOVERHIP,
  HIPMIDHIP1,
  HIP2HIPMID,
  DUMMY,
  ROOT
};

struct body_t{
  //! the various parts of a transformer
  part_t *hip1, *hip2, *hipmid;    // the hip1 is the root
  part_t *torso;
  part_t *thigh1, *thigh2, *leg1, *leg2, *foot1, *foot2;
  part_t *shoulder;
  part_t *neck;
  part_t *arm1, *arm2, *hand1, *hand2;
  part_t *palm1, *palm2;
  part_t *chestCover;
  
  //! body parameters
  vertex_t center;                        // the center of entire body
  double theta_x, theta_y, theta_z;       // orientation
  
  //! state , 0 -> bot, 1 -> vehice
  int state;
  
  //! current window for passing swapping buffers
  GLFWwindow *window;
  
  //! the renderPart is the renderGL function pointer. body denotes the struct it is in 
  void (*renderBody)(GLFWwindow*);

  //!constructor
  body_t(void);
  
  //!destructor to free memory
  ~body_t(void);
  
  //! set the window and renderBody function pointers
  void setWindowRender(GLFWwindow*, void (*)(GLFWwindow*));
  
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

  //! changes the bot to vehicle
  void transformToVehicle(void);
  
  //! changes the vehicle to bot
  void transformToBot(void);
};


#endif
