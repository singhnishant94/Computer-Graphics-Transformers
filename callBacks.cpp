#include "callBacks.hpp"

//! constructor
group_t::group_t(void){
  body_t *temp = new body_t();
  bodyList.push_back(temp);
  ptr = 0;
  totCount = 1;
}

//! destructor
group_t::~group_t(void){
  for(int i = 0; i < totCount; i++) delete bodyList[i];
}

//! add a body to the List
void group_t::addBody(void){
  body_t *temp = new body_t();
  bodyList.push_back(temp);
  totCount++;
}

//! changing the bot
void group_t::nextBody(void){
  ptr= (ptr+1)%totCount;
}
  
//! return current body
body_t* group_t::currentBody(void){
  return bodyList[ptr];
}

int validKeyEvent(int action){
  return (action == GLFW_PRESS || action == GLFW_REPEAT);
}

void group_t::performAction(int key, int action, int mods){
  body_t* temp = currentBody();
  double speedTranslate = 1.0f;
  double speedRotate = 1.0f;
  joint_t jname = DUMMY;
  vertex_t theta;
  theta.setVertex(0,0,0);
  int k = 1;
  if (mods == GLFW_MOD_CONTROL) k = -1;
  if(validKeyEvent(action)){
    if (key == GLFW_KEY_Q){  //!Translate along y
      if(mods == GLFW_MOD_CONTROL) temp->translateBody(0.0f,-speedTranslate,0.0f);
      else temp->translateBody(0.0f,speedTranslate,0.0f);
    }
    else if (key == GLFW_KEY_S){//!Translate along x
      if(mods == GLFW_MOD_CONTROL) temp->translateBody(-speedTranslate,0.0f,0.0f);
      else temp->translateBody(speedTranslate,0.0f,0.0f);
    }
    else if (key == GLFW_KEY_A){//!Translate along z
      if(mods == GLFW_MOD_CONTROL) temp->translateBody(0.0f,0.0f,-speedTranslate);
      else temp->translateBody(0.0f,0.0f,speedTranslate);
    }
    else if (key == GLFW_KEY_D){//!Rotate about y
      if(mods == GLFW_MOD_CONTROL) temp->rotateBody(0.0f,-speedRotate,0.0f);
      else temp->rotateBody(0.0f,speedRotate,0.0f);
    }
    else if (key == GLFW_KEY_X){//!Rotate about z
      if(mods == GLFW_MOD_CONTROL) temp->rotateBody(0.0f, 0.0f, -speedRotate);
      else temp->rotateBody(0.0f, 0.0f, speedRotate);
    }
    else if (key == GLFW_KEY_C){//!Rotate about x
      if(mods == GLFW_MOD_CONTROL) temp->rotateBody(-speedRotate, 0.0f, 0.0f);
      else temp->rotateBody(speedRotate, 0.0f, 0.0f);
    }
    //!LOWER PART
    else if (key == GLFW_KEY_H){//!Torso-hip
      jname = TORSOHIP; theta.setVertex(speedRotate,0,0);
    }
    else if (key == GLFW_KEY_F){//!Thigh1-hip, x
      jname = THIGH1HIP; theta.setVertex(speedRotate,0,0);
    }
    else if (key == GLFW_KEY_G){//!Thigh1-hip, z
      jname = THIGH1HIP; theta.setVertex(0,0,speedRotate);
    }
    else if (key == GLFW_KEY_B){//!Leg1-thigh1, x
      jname = LEG1THIGH1; theta.setVertex(speedRotate,0,0);
    }
    else if (key == GLFW_KEY_V){//!Foot1-leg1, z
      jname = FOOT1LEG1; theta.setVertex(speedRotate,0,0);
    }
    else if (key == GLFW_KEY_J){//!Thigh2-hip, x
      jname = THIGH2HIP; theta.setVertex(speedRotate,0,0);
    }
    else if (key == GLFW_KEY_K){//!Thigh2-hip, z
      jname = THIGH2HIP; theta.setVertex(0,0,speedRotate);
    }
    else if (key == GLFW_KEY_N){//!Leg2-thigh2, x
      jname = LEG2THIGH2; theta.setVertex(speedRotate,0,0);
    }
    else if (key == GLFW_KEY_M){//!Foot2-leg2, x
      jname = FOOT2LEG2; theta.setVertex(speedRotate,0,0);
    }
    //!UPPER PART
    else if (key == GLFW_KEY_Y){//!Neck-shoulder, x
      jname = NECKSHOULDER; theta.setVertex(speedRotate,0,0);
    }
    else if (key == GLFW_KEY_U){//!Neck-shoulder, z
      jname = NECKSHOULDER; theta.setVertex(0,0,speedRotate);
    }
    else if (key == GLFW_KEY_R){//!Arm1-Shoulder, z
      jname = ARM1SHOULDER; theta.setVertex(0,0,speedRotate);
    }
    else if (key == GLFW_KEY_T){//!Arm1-Shoulder, y
      jname = ARM1SHOULDER; theta.setVertex(0,speedRotate,0);
    }
    else if (key == GLFW_KEY_E){//!Hand1-Arm1
      jname = HAND1ARM1; theta.setVertex(0,speedRotate,0);
    }
    else if (key == GLFW_KEY_I){//!Arm2-shoulder, x
      jname = ARM2SHOULDER; theta.setVertex(speedRotate,0,0);
    }
    else if (key == GLFW_KEY_O){//!Arm2-shoulder, z
      jname = ARM2SHOULDER; theta.setVertex(0,0,speedRotate);
    }
    else if (key == GLFW_KEY_P){//!Hand2-Arm2
      jname = HAND2ARM2; theta.setVertex(0,speedRotate,0);
    }
  	
    theta.scaleValue(k*1.0);
    temp->changeOrientation(jname,theta);
  }	
}

namespace bot_t{
  //!GLFW keyboard callback
  extern group_t autoBots;
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_TAB && action == GLFW_PRESS) autoBots.nextBody();
    else autoBots.performAction(key, action, mods);
  }
};
