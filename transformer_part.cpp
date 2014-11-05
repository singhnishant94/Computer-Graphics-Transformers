#include "gl_framework.hpp"
#include "transformer_part.hpp"
#include "part_drawings.hpp"
#include <math.h>
#include <iostream>


using namespace std;

// these numbers correspond to the various part numbers
#define HIPNUM  1
#define TORSONUM 2
#define SHOULDERNUM 3
#define NECKNUM 4
#define ARMNUM 5
#define HANDNUM 6
#define THIGHNUM 7
#define LEG1NUM 8
#define FOOTNUM 9
#define PALMNUM 10
#define CHESTCOVERNUM 11
#define LEG2NUM 12
#define HIPMIDNUM 13
#define PALMPER1NUM 14
#define PALMPER2NUM 15
#define WHEELFRONTNUM1 16
#define WHEELFRONTNUM2 17
#define WHEELBACKNUM1 18
#define WHEELBACKNUM2 19
#define AXLE1NUM 20
#define AXLE2NUM 21

#define TOT_PART 27


#define OK  std::cout<<"ok"<<std::endl;




string parts[27] = {"Hip","Torso","Shoulder","Neck","Arm","Hand","Thigh",
                    "Leg1","Foot","Palm","Chestcover","Leg2","HipMid","PalmPer1","PalmPer2","WheelFront1",
                    "WheelFront2","wheelBack1","WheelBack2","Axle1","Axle2"};

//! sets the vertex
void vertex_t::setVertex(double _x, double _y, double _z){
  x = _x;
  y = _y;
  z = _z;
}

//!change value
void vertex_t::updateValue(double dx, double dy, double dz){
  x += dx;
  y += dy;
  z += dz;
  //std::cout<<"up "<<dx<<" "<<dy<<" "<<dz<<std::endl;
}

//! scale value
void vertex_t::scaleValue(double m){
  x *= m;
  y *= m;
  z *= m;
}

//! constructor initialize the current part to unit length along x axis
part_t::part_t(void){
  end_A.setVertex(-1, 0, 0);
  end_B.setVertex(1, 0, 0);
  center.setVertex(0, 0, 0);
  angleMin.setVertex(-360, -360, -360);
  angleMax.setVertex(360, 360, 360);
  fullRotate = 0;
}

//! set the window and renderBody function pointers
void part_t::setWindowRender(GLFWwindow* _window, void (*renderGL)(GLFWwindow*)){
  window = _window;
  renderPart = renderGL;
}
 

//! sets the length to scale to later
void part_t::setLength(double l){
  end_A.setVertex(-l, 0, 0);
  end_B.setVertex(l, 0, 0);
}

//! returns length
double part_t::getLength(void){
  return (end_B.x);
}

//! set part number
void part_t::setPartNum(int _partNum){
  partNum = _partNum;
}

//! add child
void part_t::addChild(part_t* child){
  children.push_back(child);
}

//! establishes the connection using the parameters
void part_t::connect(vertex_t* _anchorLocal, part_t* parent, vertex_t* _anchorRemote, double _theta_x, double _theta_y, double _theta_z){
  anchorLocal = _anchorLocal;
  anchorRemote = _anchorRemote;
  parent->addChild(this);
  theta_x = _theta_x;
  theta_y = _theta_y;
  theta_z = _theta_z;
}

//! connect dependent parts here
void part_t::addConnPart(part_t* _part){
  connPart.push_back(_part);
}
  
//! draw the part and children
void part_t::drawPart(void){
  glPushMatrix();
  glTranslatef(anchorRemote->x, anchorRemote->y, anchorRemote->z);
  glRotatef(theta_x, 1, 0, 0);
  glRotatef(theta_y, 0, 1, 0);
  glRotatef(theta_z, 0, 0, 1);
  glTranslatef(-anchorLocal->x, -anchorLocal->y, -anchorLocal->z);
  
  int l = children.size();
  for(int i = 0; i < l; i++){
    children[i]->drawPart();
  }
  glPushMatrix();
  glCallList(partNum);
  glPopMatrix();
  glPopMatrix();
}

//! Print the part position and orientation details and children
void part_t::printPartDetails(ofstream &keyFramesFile){
  //keyFramesFile<<partNum<<" "<<parts[partNum-1]<<endl;
  int l = children.size();
  for(int i = 0; i < l; i++){
    children[i]->printPartDetails(keyFramesFile);
  }
  keyFramesFile<<theta_x<<" "<<theta_y<<" "<<theta_z<<" ";
}

//! set the values of the frame
void part_t::setPartFromFrame(std::vector<double> &frame, int &start){
  int l = children.size();
  for(int i = 0; i < l; i++){
    children[i]->setPartFromFrame(frame, start);
  }
  theta_x = frame[start]; 
  theta_y = frame[start + 1];
  theta_z = frame[start + 2];
  start += 3;
}


//! function to change theta_x
void part_t::change_theta_x(double delta){
  if(checkConstraint(theta_x + delta, 'x')){
    theta_x += delta;
    if(theta_x >= 360) theta_x -= 360;
    else if(theta_x <= -360) theta_x += 360;
    changeConnPartTheta(delta, 'x');
  }
}

//! function to change theta_y
void part_t::change_theta_y(double delta){
  if(checkConstraint(theta_y + delta, 'y')){
    theta_y += delta;
    if(theta_y >= 360) theta_y -= 360;
    else if(theta_y <= -360) theta_y += 360;
    changeConnPartTheta(delta, 'y');
  }
}

//! function to change theta_z
void part_t::change_theta_z(double delta){
  if(checkConstraint(theta_z + delta, 'z')){
    theta_z += delta;
    if(theta_z >= 360) theta_z -= 360;
    else if(theta_z <= -360) theta_z += 360;
    changeConnPartTheta(delta, 'z');
  }
}

//! change connPart theta
void part_t::changeConnPartTheta(double delta, char ax){
  int l = connPart.size();
  for(int i = 0; i < l; i++){
    if(ax == 'x') connPart[i]->change_theta_x(delta);
    else if(ax == 'y') connPart[i]->change_theta_y(delta);
    else if(ax == 'z') connPart[i]->change_theta_z(delta);
  }
}

//! set orientation to a given value with a given speed
void part_t::setAngularOrientation(double t_x, double t_y, double t_z, double speed, std::string order){
  for(int i = 0; i < 3; i++){
    if(order[i] == 'x') setAngularOrientationX(t_x, speed);
    else if(order[i] == 'y') setAngularOrientationY(t_y, speed);
    else if(order[i] == 'z') setAngularOrientationZ(t_z, speed);
  }
}
 
//! set Orientation in x 
void part_t::setAngularOrientationX(double t_x, double speed){
  // changing the theta x values
  while(theta_x - t_x > speed){
    theta_x -= speed;
    changeConnPartTheta(-speed, 'x');
    renderPart(window);
    glfwSwapBuffers(window);
  }
  
  while(t_x - theta_x > speed){
    theta_x += speed;
    changeConnPartTheta(speed, 'x');
    renderPart(window);
    glfwSwapBuffers(window);
  }
  
  if(t_x != theta_x){
    theta_x = t_x;
    changeConnPartTheta(t_x - theta_x, 'x');
    renderPart(window);
    glfwSwapBuffers(window);
  }
 
}

//! set Orientation in y 
void part_t:: setAngularOrientationY(double t_y, double speed){
  // changing the theta y values
  while(theta_y - t_y > speed){
    theta_y -= speed;
    changeConnPartTheta(-speed, 'y');
    renderPart(window);
    glfwSwapBuffers(window);
  }
  
  while(t_y - theta_y > speed){
    theta_y += speed;
    changeConnPartTheta(speed, 'y');
    renderPart(window);
    glfwSwapBuffers(window);
  }
  
  if(t_y != theta_y){
    theta_y = t_y;
    changeConnPartTheta(t_y - theta_y, 'y');
    renderPart(window);
    glfwSwapBuffers(window);
  }
  
}

//! set Orientation in z
void part_t::setAngularOrientationZ(double t_z, double speed){
 // changing the theta z value
  while(theta_z - t_z > speed){
    theta_z -= speed;
    changeConnPartTheta(-speed, 'z');
    renderPart(window);
    glfwSwapBuffers(window);
  }
  
  while(t_z - theta_z > speed){
    changeConnPartTheta(speed, 'z');
    theta_z += speed;
    renderPart(window);
    glfwSwapBuffers(window);
  }
  
  if(t_z != theta_z){
    theta_z = t_z;
    changeConnPartTheta(t_z - theta_z, 'z');
    renderPart(window);
    glfwSwapBuffers(window);
  }
} 

//! function as a hole to overpass the constraints
void part_t::change_theta_sys(double dx, double dy, double dz){
  theta_x += dx, theta_y += dy; theta_z += dz;
}

//! set constraints minimum values
void part_t::setMinAngularConstraints(vertex_t c){
  angleMin = c;
}
  
//! set constraints max values
void part_t::setMaxAngularConstraints(vertex_t c){
  angleMax = c;
}

//! set constraints minimum values, overloaded
void part_t::setMinAngularConstraints(double x, double y, double z){
  angleMin.setVertex(x, y, z);
}

//! set constraints minimum values, overloaded
void part_t::setMaxAngularConstraints(double x, double y, double z){
  angleMax.setVertex(x, y, z);
}  
  
//! checking the constraints, return true/ false
int part_t::checkConstraint(double theta, char axis){
  if(fullRotate) return 1;
  if(axis == 'x'){
    if(theta <= angleMax.x && theta >= angleMin.x) return 1;
    else return 0;
  }
  else if(axis == 'y'){
    if(theta <= angleMax.y && theta >= angleMin.y) return 1;
    else return 0;
  }
  else if(axis == 'z'){
    if(theta <= angleMax.z && theta >= angleMin.z) return 1;
    else return 0;
  }
  return 0;
}

//! the below 4 functions are in trial
//! set orientation to a given value with a given speed
int part_t::setAngularOrientationT(double t_x, double t_y, double t_z, double speed, std::string order){
  int indicator = 0;
  for(int i = 0; i < 3; i++){
    if(order[i] == 'x') indicator = setAngularOrientationXT(t_x, speed);
    else if(order[i] == 'y') indicator = setAngularOrientationYT(t_y, speed);
    else if(order[i] == 'z') indicator = setAngularOrientationZT(t_z, speed);
    if(indicator) return 1;
  }
  return 0;
}
 
//! set Orientation in x 
int part_t::setAngularOrientationXT(double t_x, double speed){
  // changing the theta x values
  if (theta_x - t_x > speed){
    theta_x -= speed;
    changeConnPartTheta(-speed, 'x');
    return 1;
  }
  else if (t_x - theta_x > speed){
    theta_x += speed;
    changeConnPartTheta(speed, 'x');
    return 1;
  }
  else if(t_x != theta_x){
    theta_x = t_x;
    changeConnPartTheta(t_x - theta_x, 'x');
    return 1;
  }
  else return 0;
}

//! set Orientation in y 
int part_t:: setAngularOrientationYT(double t_y, double speed){
  // changing the theta y values
  if (theta_y - t_y > speed){
    theta_y -= speed;
    changeConnPartTheta(-speed, 'y');
    return 1;
  }
  else if (t_y - theta_y > speed){
    theta_y += speed;
    changeConnPartTheta(speed, 'y');
    return 1;
  }
  else if (t_y != theta_y){
    theta_y = t_y;
    changeConnPartTheta(t_y - theta_y, 'y');
    return 1;
  }
  else return 0;
}

//! set Orientation in z
int part_t::setAngularOrientationZT(double t_z, double speed){
 // changing the theta z value
  if (theta_z - t_z > speed){
    theta_z -= speed;
    changeConnPartTheta(-speed, 'z');
    return 1;
  }
  else if (t_z - theta_z > speed){
    changeConnPartTheta(speed, 'z');
    theta_z += speed;
    return 1;
  }
  else if (t_z != theta_z){
    theta_z = t_z;
    changeConnPartTheta(t_z - theta_z, 'z');
    return 1;
  }
  else return 0;
}


//! constructor for body
body_t::body_t(void){
  center.setVertex(0, 0, 0);
  tPoint.setVertex(0, 0, 0);
  theta_x = theta_y = theta_z = 0.0;
  state = 0;

  boxL = 1.0, boxW = 2.0;
  X1 = -5; X2 = 5;
  Z1 = -5; Z2 = 5;
  
  // wheel vaiables for forward back movements
  vstate = 0;
  level0 = 0;
  level1 = 50;
  level2 = 100;
  levelm1 = -40;
  level = 0;
  
  speed0 = 2;
  speed1 = 2;
  speed2 = 4;
  speedm1 = 2;
  moveState = 0;
  
  // wheel turning parts
  tstate = 0;
  tmin = -40;
  tmax = 40;
  tval = 0;
  tzero = 0;
  rot = 1;
  recoil = 1;
  
  hip1 = new part_t();       
  hip1->setPartNum(HIPNUM);
  
  hip2 = new part_t();       
  hip2->setPartNum(HIPNUM);
  
  hipmid = new part_t();       
  hipmid->setPartNum(HIPMIDNUM);
  hipmid->setLength(0.5f);
  
  torso = new part_t();     
  torso->setPartNum(TORSONUM);
  torso->setLength(2.0f);
  
  thigh1 = new part_t();    
  thigh1->setPartNum(THIGHNUM);  
  thigh1->setLength(1.6f);
  
  thigh2 = new part_t();    
  thigh2->setPartNum(THIGHNUM);
  thigh2->setLength(1.6f);
  
  leg1 = new part_t();      
  leg1->setPartNum(LEG1NUM);
  leg1->setLength(1.6f);
  leg1->customPoint.setVertex(0.5f, -0.45f, -0.2f);
   
  leg2 = new part_t();      
  leg2->setPartNum(LEG2NUM);
  leg2->setLength(1.6f);
  leg2->customPoint.setVertex(0.5f, 1.25f, -0.2f);
  
  foot1 = new part_t();     
  foot1->setPartNum(FOOTNUM);
  
  foot2 = new part_t();     
  foot2->setPartNum(FOOTNUM);
  
  shoulder = new part_t();  
  shoulder->setPartNum(SHOULDERNUM);
  shoulder->setLength(2.1f);
  
  neck = new part_t();      
  neck->setPartNum(NECKNUM);
  
  arm1 = new part_t();      
  arm1->setPartNum(ARMNUM);
  arm1->setLength(1.4f);
  
  arm2 = new part_t();      
  arm2->setPartNum(ARMNUM);
  arm2->setLength(1.4f);
  
  hand1 = new part_t();     
  hand1->setPartNum(HANDNUM);
  hand1->setLength(1.3f);
  
  hand2 = new part_t();     
  hand2->setPartNum(HANDNUM);
  hand2->setLength(1.3f);
  
   palm1 = new part_t();
  palm1->setPartNum(PALMNUM);
  
  palm2 = new part_t();
  palm2->setPartNum(PALMNUM);
  
  palmPer1 = new part_t();
  palmPer1->setPartNum(PALMPER1NUM);
  
  palmPer2 = new part_t();
  palmPer2->setPartNum(PALMPER2NUM);
  
  chestCover = new part_t();
  chestCover->setPartNum(CHESTCOVERNUM);
  chestCover->setLength(2.0f);

  wheelFront = new part_t();
  wheelFront->setPartNum(-1);
  wheelFront->fullRotate = 1;
  
  wheelBack = new part_t();
  wheelBack->setPartNum(-1);
  wheelBack->fullRotate = 1;
  
  wheelFront1 = new part_t();
  wheelFront1->setPartNum(WHEELFRONTNUM1);
  wheelFront1->fullRotate = 1;
 
  wheelBack1 = new part_t();
  wheelBack1->setPartNum(WHEELBACKNUM1);
  wheelBack1->fullRotate = 1;
 
  wheelFront2 = new part_t();
  wheelFront2->setPartNum(WHEELFRONTNUM2);
  wheelFront2->fullRotate = 1;
  
  wheelBack2 = new part_t();
  wheelBack2->setPartNum(WHEELBACKNUM2);
  wheelBack2->fullRotate = 1;  

  axle1 = new part_t();
  axle1->setPartNum(AXLE1NUM);
  axle1->fullRotate = 1;
  axle1->setLength(0.5f);
  axle1->customPoint.setVertex(axle1->getLength(), 0.15f, 0.0f);

  axle2 = new part_t();
  axle2->setPartNum(AXLE1NUM);
  axle2->fullRotate = 1;
  axle2->setLength(0.5f);
  axle2->customPoint.setVertex(axle2->getLength(), -0.15f, 0.0f);
  
  // here we set the hip values specifically so as to make it at origin
  hip1->anchorLocal = &(hip1->center);
  hip1->anchorRemote = &(hip1->center);

  torso->addConnPart(chestCover);
  palm1->addConnPart(palmPer1);
  palm2->addConnPart(palmPer2);
  
  wheelFront->addConnPart(wheelFront1);
  wheelFront->addConnPart(wheelFront2);
  
  wheelBack->addConnPart(wheelBack1);
  wheelBack->addConnPart(wheelBack2);
  
  makeBody();
  addConstraints();
}


//! destructor
body_t::~body_t(void){
  delete hip1, hip2, hipmid;
  delete torso;
  delete thigh1, thigh2, leg1, leg2, foot1, foot2;
  delete shoulder;
  delete neck;
  delete arm1, arm2, hand1, hand2;
  delete palm1, palm2;
  delete chestCover;
  delete palmPer1, palmPer2;
  delete wheelFront, wheelBack;
  delete wheelFront1, wheelFront2, wheelBack1, wheelBack2;
  delete axle1, axle2;
}

//! set the window and renderBody function pointers
void body_t::setWindowRender(GLFWwindow* _window, void (*renderGL)(GLFWwindow*)){
  window = _window;
  renderBody = renderGL;
  hip1->setWindowRender(window, renderGL);
  hip2->setWindowRender(window, renderGL);
  hipmid->setWindowRender(window, renderGL);
  torso->setWindowRender(window, renderGL);
  thigh1->setWindowRender(window, renderGL);
  thigh2->setWindowRender(window, renderGL);
  leg1->setWindowRender(window, renderGL);
  leg2->setWindowRender(window, renderGL);
  foot1->setWindowRender(window, renderGL);
  foot2->setWindowRender(window, renderGL);
  shoulder->setWindowRender(window, renderGL);
  neck->setWindowRender(window, renderGL);
  arm1->setWindowRender(window, renderGL);
  arm2->setWindowRender(window, renderGL);
  hand1->setWindowRender(window, renderGL);
  hand2->setWindowRender(window, renderGL);
  palm1->setWindowRender(window, renderGL);
  palm2->setWindowRender(window, renderGL);
  palmPer1->setWindowRender(window, renderGL);
  palmPer2->setWindowRender(window, renderGL);
  chestCover->setWindowRender(window, renderGL);
  wheelFront->setWindowRender(window, renderGL);
  wheelBack->setWindowRender(window, renderGL);
  wheelFront1->setWindowRender(window, renderGL);
  wheelBack1->setWindowRender(window, renderGL);
  wheelFront2->setWindowRender(window, renderGL);
  wheelBack2->setWindowRender(window, renderGL);
  axle1->setWindowRender(window, renderGL);
  axle2->setWindowRender(window, renderGL);
}


//! forms the basic structure
void body_t::makeBody(void){ 
  hipmid->connect(&(hipmid->end_A), hip1, &(hip1->center), 0, 0, -90);
  hip2->connect(&(hip2->center), hipmid, &(hipmid->end_B), 0, 0, 90);
  thigh1->connect(&(thigh1->end_A), hip2, &(hip2->end_A), 0, 0, -90);
  thigh2->connect(&(thigh2->end_A), hip2, &(hip2->end_B), 0, 0, -90);
  leg1->connect(&(leg1->end_A), thigh1, &(thigh1->end_B), 0, 0, 0);
  leg2->connect(&(leg2->end_A), thigh2, &(thigh2->end_B), 0, 0, 0);
  foot1->connect(&(foot1->end_A), leg1, &(leg1->end_B), 0, -90, 0);
  foot2->connect(&(foot2->end_A), leg2, &(leg2->end_B), 0, -90, 0);
  torso->connect(&(torso->end_A), hip1, &(hip1->center), 0, 0, 90);
  shoulder->connect(&(shoulder->center), torso, &(torso->end_B), 0, 0, -90);
  neck->connect(&(neck->end_A), shoulder, &(shoulder->center), 0, 0, 90);
  arm1->connect(&(arm1->end_A), shoulder, &(shoulder->end_A), 0, 0, -180);
  arm2->connect(&(arm2->end_A), shoulder, &(shoulder->end_B), 0, 0, 0);
  hand1->connect(&(hand1->end_A), arm1, &(arm1->end_B), 0, 0, 0);
  hand2->connect(&(hand2->end_A), arm2, &(arm2->end_B), 0, 0, 0);
  palm1->connect(&(palm1->end_A), hand1, &(hand1->end_B), 0, 0, 0);
  palm2->connect(&(palm2->end_A), hand2, &(hand2->end_B), 0, 0, 0);
  chestCover->connect(&(chestCover->end_A), hip1, &(hip1->center), 0, 0, 90);
  palmPer1->connect(&(palmPer1->end_A), hand1, &(hand1->end_B), 0, 0, -90);
  palmPer2->connect(&(palmPer2->end_A), hand2, &(hand2->end_B), 0, 0, 90);
  wheelFront1->connect(&(wheelFront1->center), axle1, &(axle1->customPoint), 0, 0, 0);  // --------- the 4 below are not done
  wheelFront2->connect(&(wheelFront2->center), axle2, &(axle2->customPoint), 0, 0, 0);
  wheelBack1->connect(&(wheelBack1->center), leg1, &(leg1->customPoint), 0, 0, 0);
  wheelBack2->connect(&(wheelBack2->center), leg2, &(leg2->customPoint), 0, 0, 0);
  axle1->connect(&(axle1->end_A), palmPer1, &(palmPer1->end_B), 0, 0, 0);
  axle2->connect(&(axle2->end_A), palmPer2, &(palmPer2->end_B), 0, 0, 0);
}

//! fill the parts of the body with respective drawings
void body_t::initBodyStructure(void){
  drawing_t::initList(TOT_PART);
  drawing_t::drawHip(HIPNUM, hip1->getLength());
  drawing_t::drawHipMid(HIPMIDNUM, hipmid->getLength());
  drawing_t::drawTorso(TORSONUM, torso->getLength());
  drawing_t::drawShoulder(SHOULDERNUM, shoulder->getLength());
  drawing_t::drawNeck(NECKNUM, neck->getLength());
  drawing_t::drawArm(ARMNUM, arm1->getLength());
  drawing_t::drawHand(HANDNUM, hand1->getLength());
  drawing_t::drawThigh(THIGHNUM, thigh1->getLength());
  drawing_t::drawLeg1(LEG1NUM, leg1->getLength());
  drawing_t::drawLeg2(LEG2NUM, leg2->getLength());
  drawing_t::drawFoot(FOOTNUM, foot1->getLength());
  drawing_t::drawPalm(PALMNUM, palm1->getLength());
  drawing_t::drawChestCover(CHESTCOVERNUM, chestCover->getLength());
  drawing_t::drawPalmPer1(PALMPER1NUM, palmPer1->getLength());
  drawing_t::drawPalmPer2(PALMPER2NUM, palmPer1->getLength());
  drawing_t::drawWheelFront1(WHEELFRONTNUM1, wheelFront1->getLength());
  drawing_t::drawWheelBack1(WHEELBACKNUM1, wheelBack1->getLength());
  drawing_t::drawWheelFront2(WHEELFRONTNUM2, wheelFront2->getLength());
  drawing_t::drawWheelBack2(WHEELBACKNUM2, wheelBack2->getLength());
  drawing_t::drawAxle1(AXLE1NUM, axle1->getLength());
}


//! add the constraints to the various parts
void body_t::addConstraints(void){
  torso->setMinAngularConstraints(-180, -90, 0);
  torso->setMaxAngularConstraints(180, 90, 180);
  
  thigh1->setMinAngularConstraints(-90, -90, -180);
  thigh1->setMaxAngularConstraints(90, 90, -90);
  
  thigh2->setMinAngularConstraints(-90, -90, -90);
  thigh2->setMaxAngularConstraints(90, 90, 0);
  
  leg1->setMinAngularConstraints(0, 0, 0);
  leg1->setMaxAngularConstraints(0, 180, 0);
  
  leg2->setMinAngularConstraints(0, 0, 0);
  leg2->setMaxAngularConstraints(0, 180, 0);
  
  foot1->setMinAngularConstraints(0, -135, -40);
  foot1->setMaxAngularConstraints(0, -45, 40);
  
  foot2->setMinAngularConstraints(0, -135, -40);
  foot2->setMaxAngularConstraints(0, -45, 40);
  
  neck->setMinAngularConstraints(-90, 180, 0);      // one direction unsure, detected after head putting , left right nodding
  neck->setMaxAngularConstraints(180, -45, 180);
  
  arm1->setMinAngularConstraints(-90, -90, -270); //x  , y , z 
  arm1->setMaxAngularConstraints(90, 135, -90);

  arm2->setMinAngularConstraints(-90, -135, -90);
  arm2->setMaxAngularConstraints(90, 90, 90);

  hand1->setMinAngularConstraints(0, -180, 0);
  hand1->setMaxAngularConstraints(0, 0, 0);

  hand2->setMinAngularConstraints(0, -180, 0);
  hand2->setMaxAngularConstraints(0, 0, 0);
  
  palm1->setMinAngularConstraints(-360, -360, -360);
  palm1->setMaxAngularConstraints(360, 360, 360);

  palm2->setMinAngularConstraints(-360, -360, -360);
  palm2->setMaxAngularConstraints(360, 360, 360); 
  
  chestCover->setMinAngularConstraints(-360, -360, -360);
  chestCover->setMaxAngularConstraints(360, 360, 360); 
  
  palmPer1->setMinAngularConstraints(-360, -360, -360);
  palmPer1->setMaxAngularConstraints(360, 360, 360);

  palmPer2->setMinAngularConstraints(-360, -360, -360);
  palmPer2->setMaxAngularConstraints(360, 360, 360); 
 
  wheelFront->setMinAngularConstraints(-360, -360, -360);
  wheelFront->setMaxAngularConstraints(360, 360, 360); 
  
  wheelBack->setMinAngularConstraints(-360, -360, -360);
  wheelBack->setMaxAngularConstraints(360, 360, 360); 
  
  wheelFront1->setMinAngularConstraints(-360, -360, -360);
  wheelFront1->setMaxAngularConstraints(360, 360, 360); 
 
  wheelFront2->setMinAngularConstraints(-360, -360, -360);
  wheelFront2->setMaxAngularConstraints(360, 360, 360); 
  
  wheelBack1->setMinAngularConstraints(-360, -360, -360);
  wheelBack1->setMaxAngularConstraints(360, 360, 360); 

  wheelBack2->setMinAngularConstraints(-360, -360, -360);
  wheelBack2->setMaxAngularConstraints(360, 360, 360); 

  axle1->setMinAngularConstraints(-360, -360, -360);
  axle1->setMaxAngularConstraints(360, 360, 360); 

  axle2->setMinAngularConstraints(-360, -360, -360);
  axle2->setMaxAngularConstraints(360, 360, 360); 
}

float delt = 0.02f;

//! draws the body
void body_t::drawBody(void){
  //std::cout<<"center "<<center.x<<" "<<center.y<<" "<<center.z<<std::endl;
  glTranslatef(center.x, center.y, center.z);
  //glTranslatef(-tPoint.x, -tPoint.y, -tPoint.z);
  glRotatef(theta_z, 0, 0, 1);
  glRotatef(theta_y, 0, 1, 0);
  glRotatef(theta_x, 1, 0, 0);
  glTranslatef(tPoint.x, tPoint.y, tPoint.z);
  glScalef(0.1, 0.1, 0.1);
  glPushMatrix();
  hip1->drawPart();
  glPopMatrix();
  delt += 0.02f;
}

/*
part_t *hip1, *hip2, *hipmid;    // the hip1 is the root
  part_t *torso;
  part_t *thigh1, *thigh2, *leg1, *leg2, *foot1, *foot2;
  part_t *shoulder;
  part_t *neck;
  part_t *arm1, *arm2, *hand1, *hand2;
  part_t *palm1, *palm2;
  part_t *chestCover;
  part_t *palmPer1, *palmPer2;
  part_t *wheelFront, *wheelBack;
  part_t *wheelFront1, *wheelFront2, *wheelBack1, *wheelBack2;
  part_t *axle1, *axle2;

*/


//! Print the Body position and orientation details and children
void body_t::printBodyDetails(ofstream &keyFramesFile){
  hip1->printPartDetails(keyFramesFile);
  keyFramesFile <<center.x<<" "<<center.y<<" "<<center.z<<" ";
  keyFramesFile <<theta_x<<" "<<theta_y<<" "<<theta_z<<" ";

  /*
  hip1->printPartDetails();
  hip2->printPartDetails();
  hipmid->printPartDetails();
  torso->printPartDetails();
  thigh1->printPartDetails();
  thigh2->printPartDetails();
  leg1->printPartDetails();
  leg2->printPartDetails();
  foot1->printPartDetails();
  foot2->printPartDetails();
  shoulder->printPartDetails();
  neck->printPartDetails();
  arm1->printPartDetails();
  arm2->printPartDetails();
  hand1->printPartDetails();
  hand2->printPartDetails();
  palm1->printPartDetails();
  palm2->printPartDetails();
  chestCover->printPartDetails();
  palmPer1->printPartDetails();
  palmPer2->printPartDetails();
  wheelFront1->printPartDetails();
  wheelFront2->printPartDetails();
  wheelBack1->printPartDetails();
  wheelBack2->printPartDetails();
  axle1->printPartDetails();
  axle2->printPartDetails();*/
}

//! function to move the joint
void body_t::changeOrientation(joint_t jName, vertex_t delta){
  part_t *_part = 0;
  if(jName == THIGH1HIP2)  _part = thigh1;
  else if(jName == THIGH2HIP2) _part = thigh2;
  else if(jName == LEG1THIGH1) _part = leg1;
  else if(jName == LEG2THIGH2) _part = leg2;
  else if(jName == FOOT1LEG1) _part = foot1;
  else if(jName == FOOT2LEG2) _part = foot2;
  else if(jName == TORSOHIP1) _part = torso;
  else if(jName == SHOULDERTORSO) _part = shoulder;
  else if(jName == NECKSHOULDER) _part = neck;
  else if(jName == ARM1SHOULDER) _part = arm1;
  else if(jName == ARM2SHOULDER) _part = arm2;
  else if(jName == HAND1ARM1) _part = hand1;
  else if(jName == HAND2ARM2) _part = hand2;
  else if(jName == PALM1HAND1) _part = palm1; 
  else if(jName == PALM2HAND2) _part = palm2;
  else if(jName == CHESTCOVERHIP) _part = chestCover;
  else if(jName == WHEELFRONTPALMPER) _part = wheelFront;
  else if(jName == WHEELBACKLEG) _part = wheelBack;
  else if(jName == PALMPER1HAND1) _part = palmPer1;
  else if(jName == PALMPER2HAND2) _part = palmPer2;
  else if(jName == AXLE1PALMPER1) _part = axle1;
  else if(jName == AXLE2PALMPER2) _part = axle2;
  
  if(_part != 0){
    _part->change_theta_x(delta.x);
    _part->change_theta_y(delta.y);
    _part->change_theta_z(delta.z);
  }
}

//! translate the given body
void body_t::translateBody(double dx, double dy, double dz){
  if (checkBound(dx, dz))
    this->center.updateValue(dx, dy, dz);
}

//! translate the body in xz plane
void body_t::translateBodyXZ(double dist, double theta){
  double param = theta * M_PI / 180.0;
  double dx = dist * cos(param);
  double dz = dist * sin(param);
  translateBody(dx, 0, -dz);
  //std::cout<<"dir "<<theta<<" "<<dx<<" "<<dz<<" "<<theta<<std::endl;
}

//! rotate the given body
void body_t::rotateBody(double dx, double dy, double dz){
  theta_x += dx;
  if(theta_x >= 360) theta_x -= 360;
  else if(theta_x <= -360) theta_x += 360;
  
  theta_y += dy;
  if(theta_y >= 360) theta_y -= 360;
  else if(theta_y <= -360) theta_y += 360;
  
  theta_z += dz;
  if(theta_z >= 360) theta_z -= 360;
  else if(theta_z <= -360) theta_z += 360;
}

//! change the bot position to a given position
int body_t::setPosition(double _x, double _y, double _z, double speed){
  double x = center.x, y = center.y, z = center.z;
  int indicator = 0;

  if (x - _x > speed){
    indicator = 1;
    center.x -= speed;
  }
  else if (_x - x > speed){
    indicator = 1;
    center.x += speed;
  }
  else if (_x != x){
    indicator = 1;
    center.x = _x;
  }
  
  if (y - _y > speed){
    indicator = 1;
    center.y -= speed;
  }
  else if (_y - y > speed){
    indicator = 1;
    center.y += speed;
  }
  else if (_y != y){
    indicator = 1;
    center.y = _y;
  }
  
  if (z - _z > speed){
    indicator = 1;
    center.z -= speed;
  }
  else if (_z - z > speed){
    indicator = 1;
    center.z += speed;
  }
  else if (_z != z){
    indicator = 1;
    center.z = _z;
  }
  
  return indicator;
}

//! check the bound current
int body_t::checkBound(double dx, double dz){
  double x = center.x + dx, z = center.z + dz, th = (theta_y + 90) * M_PI / 180.0;
  double tx, tz;
  for (int i = -1; i <= 1; i += 2){
    for (int j = -1; j <= 1; j += 2){
      double tx1 = x + i * boxL / 2.0;
      double tz1 = z + i * boxW / 2.0;
      tx = tx1 * cos(th) - tz1 * sin(th);
      tz = tx1 * sin(th) + tz1 * cos(th);
      if (tx < X1 || tx > X2 || tz < Z1 || tz > Z2) return 0; 
    }
  }
  return 1;
}

//! checkBound angle
int body_t::checkBound(double dy){
  double x = center.x, z = center.z, th = (theta_y + dy + 90) * M_PI / 180.0;
  double tx, tz;
  for (int i = -1; i <= 1; i += 2){
    for (int j = -1; j <= 1; j += 2){
      double tx1 = x + i * boxL / 2.0;
      double tz1 = z + i * boxW / 2.0;
      tx = tx1 * cos(th) - tz1 * sin(th);
      tz = tx1 * sin(th) + tz1 * cos(th);
      if (tx < X1 || tx > X2 || tz < Z1 || tz > Z2) return 0; 
    }
  }
  return 1;
}

//! set the frame values
void body_t::setBodyFromFrame(std::vector<double> &frame, int &start){
  hip1->setPartFromFrame(frame, start);
  center.setVertex(frame[start], frame[start + 1], frame[start + 2]);
  start += 3;
  theta_x = frame[start];
  theta_y = frame[start + 1];
  theta_z = frame[start + 2];
  start += 3;
}
  

//! changes the bot to vehicle
void body_t::transformBot(void){
  double speed = 1;
  if(!state){
    state = 1;
    
    // bringing the torso to correct position
    torso->setAngularOrientation(0, 0, 90, 2 * speed, "yxz");
    
    // putting hands in position
    arm1->setAngularOrientation(0, 0, -90, speed, "zxy");
    arm2->setAngularOrientation(0, 0, -90, speed, "zxy");
  
    // pushing the head into the chest
    chestCover->setAngularOrientation(30, 0, 90, speed, "xyz");
    neck->setAngularOrientation(180, 0, 90, speed, "yzx");
    chestCover->setAngularOrientation(0, 0, 90, speed, "xyz");
    
    // torso converting to body
    torso->setAngularOrientation(-90, 0, 270, speed, "yxz");
    
    // lifting the thighs
    thigh1->setAngularOrientation(-90, 0, -90, speed, "zxy");
    thigh2->setAngularOrientation(-90, 0, -90, speed, "zxy");
    
    // turning the foot
    foot1->setAngularOrientation(0, -90, -90, speed, "yzx");
    foot2->setAngularOrientation(0, -90, 90, speed, "yzx");

    //rotating the palm
    palm1->setAngularOrientation(0, 0, 90, speed, "zxy");
    palm2->setAngularOrientation(0, 0, -90, speed, "zxy");

    //tilting hands
    hand1->setAngularOrientation(0, 15, 0, speed, "yzx");
    hand2->setAngularOrientation(0, 15, 0, speed, "yzx");
  }
  else{
    state = 0;
    
    //tilting hands
    hand1->setAngularOrientation(0, 0, 0, speed, "yzx");
    hand2->setAngularOrientation(0, 0, 0, speed, "yzx");

    //rotating the palm
    palm1->setAngularOrientation(0, 0, 0, speed, "zxy");
    palm2->setAngularOrientation(0, 0, 0, speed, "zxy");

    // turning the foot
    foot1->setAngularOrientation(0, -90, 0, speed, "yzx");
    foot2->setAngularOrientation(0, -90, 0, speed, "yzx");

    // lifting the thighs
    thigh1->setAngularOrientation(0, 0, -90, speed, "zxy");
    thigh2->setAngularOrientation(0, 0, -90, speed, "zxy");

    
    // torso converting to body
    torso->setAngularOrientation(0, 0, 90, speed, "zxy");

    // pushing the head into the chest
    chestCover->setAngularOrientation(30, 0, 90, speed, "xyz");
    neck->setAngularOrientation(0, 0, 90, speed, "yzx");
    chestCover->setAngularOrientation(0, 0, 90, speed, "xyz");

    // putting hands in position
    arm1->setAngularOrientation(0, 0, -180, speed, "zxy");
    arm2->setAngularOrientation(0, 0, 0, speed, "zxy");
  }
}
