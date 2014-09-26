#include "callBacks.hpp"

//! constructor
group_t::group_t(void){
  body_t *temp = new body_t();
  bodyList.push_back(temp);
  ptr = 0;
  totCount = 1;
  jName = ROOT;
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

//! check if either press of repeat
int keyValidEvent(int action){
  return (action == GLFW_PRESS || action == GLFW_REPEAT);
}


//! to select a given joint
int group_t::selectJoint(int key){
  if(key == GLFW_KEY_SPACE) jName = ROOT;
  else if (key == GLFW_KEY_H) jName = TORSOHIP;
  else if (key == GLFW_KEY_G) jName = THIGH1HIP;
  else if (key == GLFW_KEY_J) jName = THIGH2HIP;
  else if (key == GLFW_KEY_B) jName = LEG1THIGH1;
  else if (key == GLFW_KEY_N) jName = LEG2THIGH2;
  else if (key == GLFW_KEY_V) jName = FOOT1LEG1;
  else if (key == GLFW_KEY_M) jName = FOOT2LEG2;
  else if (key == GLFW_KEY_Y) jName = NECKSHOULDER;
  else if (key == GLFW_KEY_T) jName = ARM1SHOULDER;
  else if (key == GLFW_KEY_U) jName = ARM2SHOULDER;
  else if (key == GLFW_KEY_R) jName = HAND1ARM1;
  else if (key == GLFW_KEY_I) jName = HAND2ARM2;
  else return 0;
  return 1;
}

//! to do the key press action
void group_t::performAction(int key, int action, int mods){

  body_t* currBody = currentBody();
  double speedTranslate = 1.0f, speedRotate = 1.0f, dir = 1;
  vertex_t theta; theta.setVertex(0, 0, 0);
  
  if (mods == GLFW_MOD_CONTROL) dir = -1;
  if (keyValidEvent(action)){
    if (!selectJoint(key)){
      if (jName == ROOT){
	if (key == GLFW_KEY_Q) currBody->rotateBody(0, 0, dir * speedRotate);
	else if (key == GLFW_KEY_W) currBody->rotateBody(dir  * speedRotate, 0, 0);
	else if (key == GLFW_KEY_A) currBody->rotateBody(0, dir  * speedRotate, 0);
	else if (key == GLFW_KEY_S) currBody->translateBody(0, dir * speedTranslate, 0);
	else if (key == GLFW_KEY_Z) currBody->translateBody(0, 0, dir * speedTranslate);
	else if (key == GLFW_KEY_X) currBody->translateBody(dir * speedTranslate, 0, 0);
      }
      else if(jName == HAND1ARM1 || jName == HAND2ARM2 || jName == LEG1THIGH1 || jName == LEG2THIGH2){
	if (key == GLFW_KEY_A) theta.setVertex(0, dir * speedRotate, 0);
	currBody->changeOrientation(jName, theta);
      }
      else {
	if (key == GLFW_KEY_Q) theta.setVertex(0, 0, dir * speedRotate);
	else if (key == GLFW_KEY_W) theta.setVertex(dir * speedRotate, 0, 0);
	else if (key == GLFW_KEY_A) theta.setVertex(0, dir * speedRotate, 0);
	currBody->changeOrientation(jName, theta);
      }
    }
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
