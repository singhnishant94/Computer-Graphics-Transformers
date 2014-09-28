#include "gl_framework.hpp"
#include "transformer_part.hpp"
#include "part_drawings.hpp"

// these numbers correspond to the various part numbers
#define HIPNUM  1
#define TORSONUM 2
#define SHOULDERNUM 3
#define NECKNUM 4
#define ARMNUM 5
#define HANDNUM 6
#define THIGHNUM 7
#define LEGNUM 8
#define FOOTNUM 9

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
}

//! sets the length to scale to later
void part_t::setLength(double l){
  end_A.setVertex(-l / 2, 0, 0);
  end_B.setVertex(l / 2, 0, 0);
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
  //glCallList(partNum); 
  drawing_t::drawLine();
  glPopMatrix();
}

//! function to change theta_x
void part_t::change_theta_x(double delta){
  theta_x += delta;
}

//! function to change theta_y
void part_t::change_theta_y(double delta){
  theta_y += delta;
}

//! function to change theta_z
void part_t::change_theta_z(double delta){
  theta_z += delta;
}
  


//! constructor for body
body_t::body_t(void){
  center.setVertex(0, 0, 0);
  theta_x = theta_y = theta_z = 0.0;
  hip = new part_t();       
  hip->setPartNum(HIPNUM);
  
  torso = new part_t();     
  torso->setPartNum(TORSONUM);
  
  thigh1 = new part_t();    
  thigh1->setPartNum(THIGHNUM);  
  
  thigh2 = new part_t();    
  thigh2->setPartNum(THIGHNUM);
  
  leg1 = new part_t();      
  leg1->setPartNum(LEGNUM);
  
  leg2 = new part_t();      
  leg2->setPartNum(LEGNUM);
  
  foot1 = new part_t();     
  foot1->setPartNum(FOOTNUM);
  
  foot2 = new part_t();     
  foot2->setPartNum(FOOTNUM);
  
  shoulder = new part_t();  
  shoulder->setPartNum(SHOULDERNUM);
  
  neck = new part_t();      
  neck->setPartNum(NECKNUM);
  
  arm1 = new part_t();      
  arm1->setPartNum(ARMNUM);
  
  arm2 = new part_t();      
  arm2->setPartNum(ARMNUM);
  
  hand1 = new part_t();     
  hand1->setPartNum(HANDNUM);
  
  hand2 = new part_t();     
  hand2->setPartNum(HANDNUM);
  
  // here we set the hip values specifically so as to make it at origin
  hip->anchorLocal = &(hip->center);
  hip->anchorRemote = &(hip->center);

  makeBody();
  initBodyStructure();
}


//! destructor
body_t::~body_t(void){
  delete hip;
  delete torso;
  delete thigh1, thigh2, leg1, leg2, foot1, foot2;
  delete shoulder;
  delete neck;
  delete arm1, arm2, hand1, hand2;
}


//! forms the basic structure
void body_t::makeBody(void){ 
  thigh1->connect(&(thigh1->end_A), hip, &(hip->end_A), 0, 0, -90);
  thigh2->connect(&(thigh2->end_A), hip, &(hip->end_B), 0, 0, -90);
  leg1->connect(&(leg1->end_A), thigh1, &(thigh1->end_B), 0, 0, 0);
  leg2->connect(&(leg2->end_A), thigh2, &(thigh2->end_B), 0, 0, 0);
  foot1->connect(&(foot1->end_A), leg1, &(leg1->end_B), -90, 0, -90);
  foot2->connect(&(foot2->end_A), leg2, &(leg2->end_B), 90, 0, 90);
  torso->connect(&(torso->end_A), hip, &(hip->center), 0, 0, 90);
  shoulder->connect(&(shoulder->center), torso, &(torso->end_B), 0, 0, -90);
  neck->connect(&(neck->end_A), shoulder, &(shoulder->center), 0, 0, 90);
  arm1->connect(&(arm1->end_A), shoulder, &(shoulder->end_A), 0, 0, -180);
  arm2->connect(&(arm2->end_A), shoulder, &(shoulder->end_B), 0, 0, 0);
  hand1->connect(&(hand1->end_A), arm1, &(arm1->end_B), 0, 0, 0);
  hand2->connect(&(hand2->end_A), arm2, &(arm2->end_B), 0, 0, 0);
}

//! fill the parts of the body with respective drawings
void body_t::initBodyStructure(void){
  //drawing_t::initList(9);
  glGenLists(9);
  drawing_t::drawHip(HIPNUM, 1);
  drawing_t::drawTorso(TORSONUM, 1);
  drawing_t::drawShoulder(SHOULDERNUM, 1);
  drawing_t::drawNeck(NECKNUM, 1);
  drawing_t::drawArm(ARMNUM, 1);
  drawing_t::drawHand(HANDNUM, 1);
  drawing_t::drawThigh(THIGHNUM, 1);
  drawing_t::drawLeg(LEGNUM, 1);
  drawing_t::drawFoot(FOOTNUM, 1);
}


//! draws the body
void body_t::drawBody(void){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScalef(0.1, 0.1, 0.1);
  glTranslatef(center.x, center.y, center.z);
  glRotatef(theta_z, 0, 0, 1);
  glRotatef(theta_y, 0, 1, 0);
  glRotatef(theta_x, 1, 0, 0);
  glPushMatrix();
  hip->drawPart();
  glPopMatrix();
}

//! function to move the joint
void body_t::changeOrientation(joint_t jName, vertex_t delta){
  part_t *_part = 0;
  if(jName == THIGH1HIP)  _part = thigh1;
  else if(jName == THIGH2HIP) _part = thigh2;
  else if(jName == LEG1THIGH1) _part = leg1;
  else if(jName == LEG2THIGH2) _part = leg2;
  else if(jName == FOOT1LEG1) _part = foot1;
  else if(jName == FOOT2LEG2) _part = foot2;
  else if(jName == TORSOHIP) _part = torso;
  else if(jName == SHOULDERTORSO) _part = shoulder;
  else if(jName == NECKSHOULDER) _part = neck;
  else if(jName == ARM1SHOULDER) _part = arm1;
  else if(jName == ARM2SHOULDER) _part = arm2;
  else if(jName == HAND1ARM1) _part = hand1;
  else if(jName == HAND2ARM2) _part = hand2;
  
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
  theta_y += dy;
  theta_z += dz;
}
