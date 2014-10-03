#include "gl_framework.hpp"
#include "transformer_part.hpp"
#include "part_drawings.hpp"
#include "matrix.hpp"

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

#define TOT_PART 15

#define OK  std::cout<<"ok"<<std::endl;

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



//! constructor for body
body_t::body_t(void){
  center.setVertex(0, 0, 0);
  theta_x = theta_y = theta_z = 0.0;
  state = 0;
  
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
  
  leg2 = new part_t();      
  leg2->setPartNum(LEG2NUM);
  leg2->setLength(1.6f);
  
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

  // here we set the hip values specifically so as to make it at origin
  hip1->anchorLocal = &(hip1->center);
  hip1->anchorRemote = &(hip1->center);

  torso->addConnPart(chestCover);
  palm1->addConnPart(palmPer1);
  palm2->addConnPart(palmPer2);
  
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
  
}


//! draws the body
void body_t::drawBody(void){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glTranslatef(0,0,-5.0f);
  glScalef(0.1, 0.1, 0.1);
  glTranslatef(center.x, center.y, center.z);
  glRotatef(theta_z, 0, 0, 1);
  glRotatef(theta_y, 0, 1, 0);
  glRotatef(theta_x, 1, 0, 0);
  glPushMatrix();
  hip1->drawPart();
  glPopMatrix();
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
  
  if(_part != 0){
    _part->change_theta_x(delta.x);
    _part->change_theta_y(delta.y);
    _part->change_theta_z(delta.z);
  }
}

//! translate the given body
void body_t::translateBody(double dx, double dy, double dz){
  center.updateValue(dx, dy, dx);
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
