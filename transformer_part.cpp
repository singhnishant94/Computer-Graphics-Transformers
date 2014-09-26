#include "gl_framework.hpp"
#include "transformer_part.hpp"

//! sets the vertex
void vertex_t::setVertex(double _x, double _y, double _z){
  x = _x;
  y = _y;
  z = _z;
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

//! add child
void part_t::addChild(part_t* child){
  children.push_back(child);
}

//! establishes the connection using the parameters
void part_t::connect(vertex_t* _anchorLocal, part_t* parent, vertex_t* _anchorRemote, double _theta_y, double _theta_z){
  anchorLocal = _anchorLocal;
  anchorRemote = _anchorRemote;
  parent->addChild(this);
  theta_y = _theta_y;
  theta_z = _theta_z;
}

//! draw the part and children
void part_t::drawPart(void){
  glPushMatrix();
  glTranslatef(anchorRemote->x, anchorRemote->y, anchorRemote->z);
  glRotatef(theta_y, 0, 1, 0);
  glRotatef(theta_z, 0, 0, 1);
  glTranslatef(-anchorLocal->x, -anchorLocal->y, -anchorLocal->z);
  
  int l = children.size();
  for(int i = 0; i < l; i++){
    children[i]->drawPart();
  }
  
  glBegin(GL_LINES);
  glVertex3f(end_A.x, end_A.y, end_A.z);
  glVertex3f(end_B.x, end_B.y, end_B.z);
  glEnd();
  glPopMatrix();
}

//! function to change theta_y
void part_t::change_theta_y(int val){
  theta_y += val;
}

//! function to change theta_z
void part_t::change_theta_z(int val){
  theta_z += val;
}
  


//! constructor for body
body_t::body_t(void){
  center.setVertex(0, 0, 0);
  theta_x = theta_y = theta_z = 0.0;
  hip = new part_t();
  torso = new part_t();
  thigh1 = new part_t();
  thigh2 = new part_t();
  leg1 = new part_t();
  leg2 = new part_t();
  foot1 = new part_t();
  foot2 = new part_t();
  shoulder = new part_t();
  neck = new part_t();
  arm1 = new part_t();
  arm2 = new part_t();
  hand1 = new part_t();
  hand2 = new part_t();
  
  // here we set the hip values specifically so as to make it at origin
  hip->anchorLocal = &(hip->center);
  hip->anchorRemote = &(hip->center);

  makeBody();
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
  thigh1->connect(&(thigh1->end_A), hip, &(hip->end_A), 0, -90);
  thigh2->connect(&(thigh2->end_A), hip, &(hip->end_B), 0, -90);
  leg1->connect(&(leg1->end_A), thigh1, &(thigh1->end_B), 0, 0);
  leg2->connect(&(leg2->end_A), thigh2, &(thigh2->end_B), 0, 0);
  foot1->connect(&(foot1->end_A), leg1, &(leg1->end_B), 0, -90);
  foot2->connect(&(foot2->end_A), leg2, &(leg2->end_B), 0, 90);
  torso->connect(&(torso->end_A), hip, &(hip->center), 0, 90);
  shoulder->connect(&(shoulder->center), torso, &(torso->end_B), 0, -90);
  neck->connect(&(neck->end_A), shoulder, &(shoulder->center), 0, 90);
  arm1->connect(&(arm1->end_A), shoulder, &(shoulder->end_A), 0, -180);
  arm2->connect(&(arm2->end_A), shoulder, &(shoulder->end_B), 0, 0);
  hand1->connect(&(hand1->end_A), arm1, &(arm1->end_B), 0, 0);
  hand2->connect(&(hand2->end_A), arm2, &(arm2->end_B), 0, 0);
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
