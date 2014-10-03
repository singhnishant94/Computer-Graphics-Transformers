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

//! set the window and renderBody function pointers
void group_t::setWindowRender(GLFWwindow* _window, void (*renderGL)(GLFWwindow*)){
  window = _window;
  renderGroup = renderGL;
  bodyList[0]->setWindowRender(window, renderGroup);
}


//! add a body to the List
void group_t::addBody(void){
  body_t *temp = new body_t();
  bodyList.push_back(temp);
  temp->setWindowRender(window, renderGroup);
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
  else if (key == GLFW_KEY_H) jName = TORSOHIP1;
  else if (key == GLFW_KEY_G) jName = THIGH1HIP2;
  else if (key == GLFW_KEY_J) jName = THIGH2HIP2;
  else if (key == GLFW_KEY_B) jName = LEG1THIGH1;
  else if (key == GLFW_KEY_N) jName = LEG2THIGH2;
  else if (key == GLFW_KEY_V) jName = FOOT1LEG1;
  else if (key == GLFW_KEY_M) jName = FOOT2LEG2;
  else if (key == GLFW_KEY_Y) jName = NECKSHOULDER;
  else if (key == GLFW_KEY_T) jName = ARM1SHOULDER;
  else if (key == GLFW_KEY_U) jName = ARM2SHOULDER;
  else if (key == GLFW_KEY_R) jName = HAND1ARM1;
  else if (key == GLFW_KEY_I) jName = HAND2ARM2;
  else if (key == GLFW_KEY_O) jName = PALM1HAND1;
  else if (key == GLFW_KEY_E) jName = PALM2HAND2;
  else if (key == GLFW_KEY_C) jName = CHESTCOVERHIP;
  else return 0;
  return 1;
}

//! to do the key press action
void group_t::performAction(int key, int action, int mods){

  body_t* currBody = currentBody();
  double speedTranslate = 0.5f, speedRotate = 1.0f, dir = 1;
  vertex_t theta; theta.setVertex(0, 0, 0);
  if (mods == GLFW_MOD_CONTROL) dir = -1;
  if(!currBody->state){
    
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
  else{
    if (jName == ROOT){
      if (key == GLFW_KEY_Q) currBody->rotateBody(0, 0, dir * speedRotate);
      else if (key == GLFW_KEY_W) currBody->rotateBody(dir  * speedRotate, 0, 0);
      else if (key == GLFW_KEY_A) currBody->rotateBody(0, dir  * speedRotate, 0);
      else if (key == GLFW_KEY_S) currBody->translateBody(0, dir * speedTranslate, 0);
      else if (key == GLFW_KEY_Z) currBody->translateBody(0, 0, dir * speedTranslate);
      else if (key == GLFW_KEY_X) currBody->translateBody(dir * speedTranslate, 0, 0);
    }
  }
}

//! init all the body parts after the context creation
void group_t::initListAfterContext(void){
  for (int i = 0; i < totCount; i++){
    bodyList[0]->initBodyStructure();
  }
}


//! setvalue
void event::setValue(part_t* _part, double _t_x, double _t_y, double _t_z, double _speed, std::string _order){
  part = _part;
  t_x = _t_x;
  t_y = _t_y;
  t_z = _t_z;
  speed = _speed;
  order = _order;
}

//! execute Event and return the outcome
int event::execute(void){
  return part->setAngularOrientationT(t_x, t_y, t_z, speed, order);
}


namespace bot_t{
  
  //!GLFW keyboard callback
  extern group_t autoBots;
  extern std::list<std::list<event> > eventList;          //! list of events to execute
  extern GLFWwindow* window;
  extern void (*renderGL)(GLFWwindow*);
  
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_TAB && action == GLFW_PRESS) autoBots.nextBody();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS){
      transformBot();
      executeList();
    }
    else autoBots.performAction(key, action, mods);
  }
  
  //! execute event list
  void executeList(void){
    std::list<std::list<event> >::iterator itr;
    std::list<event>::iterator itr_in;
    itr = eventList.begin();
    while(!eventList.empty()){
      int indicator = 0;
      for(itr_in = itr->begin(); itr_in != itr->end(); itr_in++){
	indicator |= itr_in->execute();
      }
      renderGL(window);
      glfwSwapBuffers(window);
      if(!indicator) itr = eventList.erase(itr);
    }
  }
  
  void transformBot(void){
    body_t* curr = autoBots.currentBody();
    double speed = 1.0;
    if(!curr->state){
      curr->state = 1;
      event e;
      std::list<event> le;
      // bringing the torso to correct position
      e.setValue(curr->torso, 0, 0, 90, 2 * speed, "yxz");
      le.push_back(e);
      eventList.push_back(le);
      
      // putting hands in position
      le.clear();
      e.setValue(curr->arm1, 0, 0, -90, speed, "zxy");
      le.push_back(e);
      e.setValue(curr->arm2, 0, 0, -90, speed, "zxy");
      le.push_back(e);
      eventList.push_back(le);
      
      // pushing the head into the chest
      le.clear();
      e.setValue(curr->chestCover, 30, 0, 90, speed, "xyz");
      le.push_back(e);
      eventList.push_back(le);
      
      le.clear();
      e.setValue(curr->neck, 180, 0, 90, speed, "yzx");
      le.push_back(e);
      eventList.push_back(le);
      
      le.clear();
      e.setValue(curr->chestCover, 0, 0, 90, speed, "xyz");
      le.push_back(e);
      eventList.push_back(le);
      
      // torso converting to body
      le.clear();
      e.setValue(curr->torso, -90, 0, 270, speed, "yxz");
      le.push_back(e);
      eventList.push_back(le);
      
      // lifting the thighs
      le.clear();
      e.setValue(curr->thigh1, -90, 0, -90, speed, "zxy");
      le.push_back(e);
      e.setValue(curr->thigh2, -90, 0, -90, speed, "zxy");
      le.push_back(e);
      eventList.push_back(le);
      
      // turning the foot
      le.clear();
      e.setValue(curr->foot1, 0, -90, -90, speed, "yzx");
      le.push_back(e);
      e.setValue(curr->foot2, 0, -90, 90, speed, "yzx");
      le.push_back(e);
      eventList.push_back(le);
      
      //rotating the palm
      le.clear();
      e.setValue(curr->palm1, 0, 0, 90, speed, "zxy");
      le.push_back(e);
      e.setValue(curr->palm2, 0, 0, -90, speed, "zxy");
      le.push_back(e);
      eventList.push_back(le);
      
      //tilting hands
      le.clear();
      e.setValue(curr->hand1, 0, 15, 0, speed, "yzx");
      le.push_back(e);
      e.setValue(curr->hand2, 0, 15, 0, speed, "yzx");
      le.push_back(e);
      eventList.push_back(le);
    }
    else{
      curr->state = 0;
      event e;
      std::list<event> le;
         
      //tilting hands
      le.clear();
      e.setValue(curr->hand1, 0, 0, 0, speed, "yzx");
      le.push_back(e);
      e.setValue(curr->hand2, 0, 0, 0, speed, "yzx");
      le.push_back(e);
      eventList.push_back(le);
      
      //rotating the palm
      le.clear();
      e.setValue(curr->palm1, 0, 0, 0, speed, "zxy");
      le.push_back(e);
      e.setValue(curr->palm2, 0, 0, 0, speed, "zxy");
      le.push_back(e);
      eventList.push_back(le);
      
      // turning the foot
      le.clear();
      e.setValue(curr->foot1, 0, -90, 0, speed, "yzx");
      le.push_back(e);
      e.setValue(curr->foot2, 0, -90, 0, speed, "yzx");
      le.push_back(e);
      eventList.push_back(le);
            
      // lifting the thighs
      le.clear();
      e.setValue(curr->thigh1, 0, 0, -90, speed, "zxy");
      le.push_back(e);
      e.setValue(curr->thigh2, 0, 0, -90, speed, "zxy");
      le.push_back(e);
      eventList.push_back(le);
          
      // torso converting to body
      le.clear();
      e.setValue(curr->torso, 0, 0, 90, speed, "zxy");
      le.push_back(e);
      eventList.push_back(le);
      
      // pushing the head into the chest
      le.clear();
      e.setValue(curr->chestCover, 30, 0, 90, speed, "xyz");
      le.push_back(e);
      eventList.push_back(le);
      
      le.clear();
      e.setValue(curr->neck, 0, 0, 90, speed, "yzx");
      le.push_back(e);
      eventList.push_back(le);
      
      le.clear();
      e.setValue(curr->chestCover, 0, 0, 90, speed, "xyz");
      le.push_back(e);
      eventList.push_back(le);
      
      // putting hands in position
      le.clear();
      e.setValue(curr->arm1, 0, 0, -180, speed, "zxy");
      le.push_back(e);
      e.setValue(curr->arm2, 0, 0, 0, speed, "zxy");
      le.push_back(e);
      eventList.push_back(le);
    }
  }
};
