#include "callBacks.hpp"
#include <math.h>
#include <iostream>
#include <vector>


using namespace std;


#define FORWARD 1
#define BACK 2
#define TLEFT 4
#define TRIGHT 8

// (recordMode = 1) => Record mode on  
int recordMode = 0; 

//! Num lock pressed
int numLock = 0;



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
  double speedTranslate = 0.05f, speedRotate = 1.0f, dir = 1;
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
      else if (key == GLFW_KEY_UP){
	if (action == GLFW_PRESS) currBody->moveState += FORWARD;
       	else if (action == GLFW_RELEASE) currBody->moveState -= FORWARD;
      }
      else if (key == GLFW_KEY_DOWN){
	if (action == GLFW_PRESS) currBody->moveState += BACK;
       	else if (action == GLFW_RELEASE) currBody->moveState -= BACK;
      }
      else if (key == GLFW_KEY_LEFT){
	if (action == GLFW_PRESS) currBody->moveState += TLEFT;
       	else if (action == GLFW_RELEASE) currBody->moveState -= TLEFT;
      }
      else if (key == GLFW_KEY_RIGHT){
	if (action == GLFW_PRESS) currBody->moveState += TRIGHT;
       	else if (action == GLFW_RELEASE) currBody->moveState -= TRIGHT;
      }
    }
  }
}

void group_t::printKeyframe(ofstream &keyFramesFile){
  body_t* currBody = currentBody();
  currBody->printBodyDetails(keyFramesFile);
  keyFramesFile <<bot_t::camX<<" "<<bot_t::camY<<" "<<bot_t::camZ<<" ";
  keyFramesFile <<bot_t::light0<<" "<<bot_t::light1<<" "<<bot_t::spotlight<<endl;

}


//! for actions which are not triggered by keys
void group_t::untriggeredActions(void){
  body_t* currBody = currentBody();
  vertex_t theta; theta.setVertex(0, 0, 0);
  double factor = 0.01; double rot_factor = 1.2;
  double dsx = 0, thx = 0;
  if (currBody->moveState & FORWARD){
    if (currBody->vstate <= 0){
      currBody->level += currBody->speed1;
      
      dsx = factor * currBody->speed1;
      theta.setVertex(0, currBody->speed1 * rot_factor, 0);
      currBody->changeOrientation(WHEELFRONTPALMPER, theta);
      theta.setVertex(0, -1 * currBody->speed1 * rot_factor, 0);
      currBody->changeOrientation(WHEELBACKLEG, theta);
      
      if (currBody->level > currBody->level0) currBody->vstate = 1;
    }
    else if (currBody->vstate == 1){
      currBody->level += currBody->speed1;
      
      dsx = factor * currBody->speed1;
      theta.setVertex(0, currBody->speed1 * rot_factor, 0);
      currBody->changeOrientation(WHEELFRONTPALMPER, theta);
      theta.setVertex(0, -1 * currBody->speed1 * rot_factor, 0);
      currBody->changeOrientation(WHEELBACKLEG, theta);
	  
      if (currBody->level > currBody->level1) currBody->vstate = 2;
    }
    else if (currBody->vstate == 2){
	  
      if (currBody->level < currBody->level2){
	currBody->level += currBody->speed2;
      }
      dsx = factor * currBody->speed2;
      
      theta.setVertex(0, currBody->speed2 * rot_factor, 0);
      currBody->changeOrientation(WHEELFRONTPALMPER, theta);
      theta.setVertex(0, -1 * currBody->speed2 * rot_factor, 0);
      currBody->changeOrientation(WHEELBACKLEG, theta);
    }
  }
  else{
    int _st = currBody->vstate;
    if (_st == 1 || _st == 2){
      currBody->level -= 1;
      dsx = factor * currBody->speed0;
      
      theta.setVertex(0, currBody->speed0 * rot_factor, 0);
      currBody->changeOrientation(WHEELFRONTPALMPER, theta);
      theta.setVertex(0, -1 * currBody->speed0 * rot_factor, 0);
      currBody->changeOrientation(WHEELBACKLEG, theta);
	
      if (currBody->level <= currBody->level0){
	currBody->level = 0;
	currBody->vstate = 0;
      }
    }
  }
  
  if (currBody->moveState & BACK){
    if (currBody->vstate >= 0){
      currBody->level -= currBody->speedm1;
      dsx = factor * currBody->speed1;
      
      theta.setVertex(0, currBody->speed1 * rot_factor, 0);
      currBody->changeOrientation(WHEELFRONTPALMPER, theta);
      theta.setVertex(0, -1 * currBody->speed1 * rot_factor, 0);
      currBody->changeOrientation(WHEELBACKLEG, theta);
      
      if (currBody->level < currBody->level0) currBody->vstate = -1;
    }
    else if (currBody->vstate == -1){
      if (currBody->level > currBody->levelm1){
	currBody->level -= currBody->speedm1;
      }
      dsx = factor * -currBody->speedm1;
      
      theta.setVertex(0, -currBody->speedm1 * rot_factor, 0);
      currBody->changeOrientation(WHEELFRONTPALMPER, theta);
      theta.setVertex(0, currBody->speedm1 * rot_factor, 0);
      currBody->changeOrientation(WHEELBACKLEG, theta);
    }
  }
  else{
    int _st = currBody->vstate;
    if (_st == -1){
      currBody->level += 1;
      dsx = factor * -currBody->speed0;
      
      theta.setVertex(0, -currBody->speed0 * rot_factor, 0);
      currBody->changeOrientation(WHEELFRONTPALMPER, theta);
      theta.setVertex(0, currBody->speed0 * rot_factor, 0);
      currBody->changeOrientation(WHEELBACKLEG, theta);
      
      if (currBody->level >= currBody->level0){
	currBody->level = 0;
	currBody->vstate = 0;
      }
    }
  }
  
  
  if (currBody->moveState & TLEFT){
    if (currBody->tstate < 0){
      currBody->tval+=currBody->rot;
      thx = -currBody->rot;
      theta.setVertex(0, 0, currBody->rot);
      currBody->changeOrientation(AXLE1PALMPER1, theta);
      currBody->changeOrientation(AXLE2PALMPER2, theta);
      if (currBody->tval >= currBody->tzero) currBody->tstate = 1; 
    }
    else if (currBody->tstate == 0){
      currBody->tval+=currBody->rot;
      thx = 0;
      theta.setVertex(0, 0, currBody->rot);
      currBody->changeOrientation(AXLE1PALMPER1, theta);
      currBody->changeOrientation(AXLE2PALMPER2, theta);
      if (currBody->tval >= currBody->tzero) currBody->tstate = 1; 
    }
    else if (currBody->tstate == 1){
      if (currBody->tval < currBody->tmax){
	currBody->tval+=currBody->rot;
	theta.setVertex(0, 0, currBody->rot);
	currBody->changeOrientation(AXLE1PALMPER1, theta);
	currBody->changeOrientation(AXLE2PALMPER2, theta);
      }
      thx =  currBody->rot;     
    }
  }
  else{
    if (currBody->tstate == 1){
      thx = currBody->rot;
      theta.setVertex(0, 0, -currBody->recoil);
      currBody->changeOrientation(AXLE1PALMPER1, theta);
      currBody->changeOrientation(AXLE2PALMPER2, theta);
      currBody->tval-=currBody->recoil;
      if (currBody->tval <= currBody->tzero){
	currBody->tstate = 0;
	currBody->tval = currBody->tzero;
      }
    }
  }

  if (currBody->moveState & TRIGHT){
    if (currBody->tstate > 0){
      currBody->tval -= currBody->rot;;      
      thx = currBody->rot;
      theta.setVertex(0, 0, -currBody->rot);
      currBody->changeOrientation(AXLE1PALMPER1, theta);
      currBody->changeOrientation(AXLE2PALMPER2, theta);
      if (currBody->tval <= currBody->tzero) currBody->tstate = -1; 
    }
    else if (currBody->tstate == 0){
      currBody->tval -= currBody->rot;;      
      thx = 0;
      theta.setVertex(0, 0, -currBody->rot);
      currBody->changeOrientation(AXLE1PALMPER1, theta);
      currBody->changeOrientation(AXLE2PALMPER2, theta);
      if (currBody->tval <= currBody->tzero) currBody->tstate = -1; 
    }
    else if (currBody->tstate == -1){
      if (currBody->tval > currBody->tmin){
	currBody->tval -= currBody->rot;
	theta.setVertex(0, 0, -currBody->rot);
	currBody->changeOrientation(AXLE1PALMPER1, theta);
	currBody->changeOrientation(AXLE2PALMPER2, theta);
      }
      thx = -currBody->rot;
    }
  }
  else{
    if (currBody->tstate == -1){
      thx = -currBody->rot;
      theta.setVertex(0, 0, currBody->recoil);
      currBody->changeOrientation(AXLE1PALMPER1, theta);
      currBody->changeOrientation(AXLE2PALMPER2, theta);
      currBody->tval += currBody->recoil;
      if (currBody->tval >= currBody->tzero){
	currBody->tstate = 0;
	currBody->tval = currBody->tzero;
      }
    }
  }
  if(dsx > 0){
    currBody->translateBodyXZ(dsx, currBody->theta_y + 90.0 + currBody->tval); 
    double f = 0.6 * dsx / factor;
    if (currBody->checkBound(thx * f))
      currBody->theta_y += f * thx;
  }
  else  if(dsx < 0){
    currBody->translateBodyXZ(dsx, currBody->theta_y + 90.0 + currBody->tval); 
    double f = 0.6 * dsx / factor;
    if (currBody->checkBound(thx * f))
      currBody->theta_y += thx * f;
  }
}


//! init all the body parts after the context creation
void group_t::initListAfterContext(void){
  for (int i = 0; i < totCount; i++){
    bodyList[0]->initBodyStructure();
  }
}

//! constructor
event::event(void){
  type = 0;
  isRoot = 0;
}


//! setvalue
void event::setValue(part_t* _part, double _t_x, double _t_y, double _t_z, double _speed, std::string _order){
  isRoot = 0;
  part = _part;
  t_x = _t_x;
  t_y = _t_y;
  t_z = _t_z;
  speed = _speed;
  order = _order;
}

//! setting for the root
void event::setValue(body_t *_body, double _para_x, double _para_y, double _para_z, double _speed, std::string _type){
  isRoot = 1;
  body = _body;
  if (_type == "pos"){
    p_x = _para_x;
    p_y = _para_y;
    p_z = _para_z;
    pos_speed = _speed;
    type += 1;
  }
}
  

//! execute Event and return the outcome
int event::execute(void){
  if (!isRoot) return part->setAngularOrientationT(t_x, t_y, t_z, speed, order);
  else if (type == 1) return body->setPosition(p_x, p_y, p_z, pos_speed); 
}


namespace bot_t{
  
  //!GLFW keyboard callback
  extern group_t autoBots;
  extern std::list<std::list<event> > eventList;          //! list of events to execute
  extern GLFWwindow* window;
  extern void (*renderGL)(GLFWwindow*);

  extern int light0;
  extern int light1;
  extern int spotlight;
  
  extern int camera1;
  extern int camera2;
  extern int camera3;

  extern int moveUp;
  extern int moveDown;
  extern int moveRight;
  extern int moveLeft;
  extern int moveIn;
  extern int moveOut;

  extern double camX, camY, camZ;

  extern int recMovie;

  extern ofstream keyFramesFile;

  extern vector<vector<double> > animationFrames;
  extern int playIndicator;
  extern int stop;

  void openFile(void){
  keyFramesFile.open("keyFrames.txt");
  }

  void closeFile(void){
    keyFramesFile.close();
  }

  void InitGL(void){
    
    // set up light number 1.
    /*
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
      glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);  // add lighting. (ambient)
      glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);  // add lighting. (diffuse).
      glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); // set light position.
      //glEnable(GL_LIGHT1);*/
  }
  
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_TAB && action == GLFW_PRESS) stop = !stop;
    else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS){
      transformBot();
    }
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS){
      if (light0 == 1) {
        std::cout<<"Light 0 disabled"<<std::endl;
        light0 = 0;
      }
      else{
        std::cout<<"Light 0 Enabled"<<std::endl;
        light0 = 1;
      }
      //if(light0) glEnable(GL_LIGHT0);
      //else glDisable(GL_LIGHT0);
    }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS){
      if (light1 == 1) {
	std::cout<<"Light 1 disabled"<<std::endl;
        light1 = 0;
      }
      else{
	std::cout<<"Light 1 Enabled"<<std::endl;
        light1 = 1;
      }
      //if(light1) glEnable(GL_LIGHT1);
      //else glDisable(GL_LIGHT1);
    }
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS){
      if(camera1) {
        camera1 = 0;
        camera2 = 1;
      }
      else if(camera2){
        camera2 = 0;
        camera3 = 1;
      }
      else if(camera3){
        camera3 = 0;
        camera1 = 1;
      } 
    }
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS){
      if(spotlight) 
        spotlight = 0;
      else spotlight = 1;
    }
    else if(key == GLFW_KEY_5 && action == GLFW_PRESS){
      if(recordMode){
        closeFile();
        recordMode = 0;
        cout<<"Record Mode OFF"<<endl;
      }
      else{
        openFile();
        recordMode = 1;
        cout<<"Record Mode ON"<<endl;
      }
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS){
      if(recordMode) {
        autoBots.printKeyframe(keyFramesFile);
        cout<<"Frame Captured"<<endl;
      }
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS){
      if(!recordMode){
        if(playIndicator){
          playIndicator = 0;
          cout<<"Animation Mode Ended"<<endl;
        }
        else{
          playIndicator = 1;
          interpolateFrames();
          cout<<"Animation Mode Enabled"<<endl;
        }
      }
    }
    else if(key == GLFW_KEY_NUM_LOCK && action == GLFW_PRESS){
      if(numLock){
        cout<<"numlock now off"<<endl;
        numLock = 0;
      }
      else{
        cout<<"numlock now on"<<endl;
        numLock = 1;
      }
    }
    else if(key == GLFW_KEY_3 && action == GLFW_PRESS){
      if(recMovie == 0){
        recMovie = 1;
        cout<<"Recording Movie"<<endl;
      }
      else{
        recMovie = 0;
        cout<<"Movie recording turned off"<<endl;
      }
    }
    else if(key == GLFW_KEY_KP_8 && (action == GLFW_PRESS || action == GLFW_REPEAT) ){
      moveUp = 1;
      camY += 0.2;
    }
    else if(key == GLFW_KEY_KP_4 && (action == GLFW_PRESS || action == GLFW_REPEAT)){
      moveLeft = 1;
      camX -= 0.2;
    }
    else if(key == GLFW_KEY_KP_6 && (action == GLFW_PRESS || action == GLFW_REPEAT)){
      moveRight = 1;
      camX += 0.2;
    }
    else if(key == GLFW_KEY_KP_2 && (action == GLFW_PRESS || action == GLFW_REPEAT)){
      moveDown = 1;
      camY -= 0.2;
    }
    else if(key == GLFW_KEY_KP_1 && (action == GLFW_PRESS || action == GLFW_REPEAT)){
      moveIn = 1;
      camZ -= 0.2;
    }
    else if(key == GLFW_KEY_KP_3 && (action == GLFW_PRESS || action == GLFW_REPEAT)){
      moveOut = 1;
      camZ += 0.2;
    }

    else autoBots.performAction(key, action, mods);
  }
  
  //! execute event list
  void executeList(void){
    if(!eventList.empty()){
      std::list<std::list<event> >::iterator itr;
      std::list<event>::iterator itr_in;
      itr = eventList.begin();
      
      int indicator = 0;
      for(itr_in = itr->begin(); itr_in != itr->end(); itr_in++){
	indicator |= itr_in->execute();
      }
      if(!indicator) eventList.erase(itr);
    }
  }
  
  void transformBot(void){
    body_t* curr = autoBots.currentBody();
    double speed = 5.0;
    if(!curr->state){

      curr->tPoint.setVertex(0, 0, 0);
      autoBots.jName = ROOT;
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
      e.setValue(curr, curr->center.x, curr->center.y - 0.584, curr->center.z, speed * 0.004, "pos");
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
      e.setValue(curr->axle1, 0, -15, 0, speed, "yzx");
      le.push_back(e);
      e.setValue(curr->axle2, 0, -15, 0, speed, "yzx");
      le.push_back(e);
      eventList.push_back(le);
      spotlight = 1;
    }
    else{
      spotlight = 0;
      //curr->tPoint.setVertex(0, 0, -1.0);
      curr->state = 0;
      event e;
      std::list<event> le;
         
      //tilting hands
      le.clear();
      e.setValue(curr->hand1, 0, 0, 0, speed, "yzx");
      le.push_back(e);
      e.setValue(curr->hand2, 0, 0, 0, speed, "yzx");
      le.push_back(e);
      e.setValue(curr->axle1, 0, 0, 0, speed, "yzx");
      le.push_back(e);
      e.setValue(curr->axle2, 0, 0, 0, speed, "yzx");
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
      e.setValue(curr, curr->center.x, curr->center.y + 0.584, curr->center.z, speed * 0.008, "pos");
      le.push_back(e);
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
  
  
  void interpolateFrames(void){
    animationFrames.clear();
    vector<vector<double> > kFrames;
    ifstream kfile;
    kfile.open("keyFrames.txt");
    int FRAMECOUNT = 27 * 3 + 3 + 3 + 3 + 3;
    vector<double> tkey(FRAMECOUNT);
    
    while(kfile.good()){
      for(int i = 0; i < FRAMECOUNT; i++) kfile>>tkey[i];
      kFrames.push_back(tkey);
    }
    kfile.close();
    int l = kFrames.size();
    cout<<"LSIZE "<<l<<endl;
    animationFrames.push_back(kFrames[0]);
    for(int i = 0; i < l - 1; i++){
      interpolateBetweenFrames(kFrames[i], kFrames[i + 1]);
    }
  }
  
  
  //! creates necessary animation between 2 frames
  void interpolateBetweenFrames(std::vector<double>& start, std::vector<double>& end){
    int NFRAMES = 100;
    double dt = 1.0 / (1.0 * NFRAMES);
    int EL = 3*27 + 3 + 3 + 3;
    double t = dt;
    int l = start.size();
    vector<double> tframe(l);
    for(int i = 1; i < NFRAMES; i++){
      for(int j = 0; j < EL; j++){
	       tframe[j] = (1 - t) * start[j] + t * end[j];
      }
     
      for (int j = EL; j < l; ++j)
      {
        if((1 - t) * start[j] + t * end[j] < 0.5){
          tframe[j] = 0;
        }
        else tframe[j] = 1;
      }
      t += dt;
      animationFrames.push_back(tframe);
    }
    
  }
  
  //!  sets the values of one frame
  void setFrameValues(vector<double> &frame){
    int start = 0;
    body_t *curr = autoBots.currentBody();
    curr->setBodyFromFrame(frame, start);
    int fLen = frame.size();
    camX = frame[start];
    camY = frame[start + 1];
    camZ = frame[start + 2];
    start+=3;

    if(frame[start] == 0) light0 = 0;
    else light0 = 1;
    if(frame[start + 1] == 0) light1 = 0;
    else light1 = 1;
    if(frame[start + 2] == 0) spotlight = 0;
    else spotlight = 1;
    start+=3;
  }
};
