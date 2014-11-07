#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

#include "transformer_part.hpp"

#include <list>
#include <vector>
#include <fstream>

struct group_t{
  
  std::vector<body_t*> bodyList;             // the body for which this call back is defined
  int ptr;                              // the current body
  int totCount;                         //  all bodies
  joint_t jName;
  
  //! current window for passing swapping buffers
  GLFWwindow *window;
  
  //! the renderPart is the renderGL function pointer. body denotes the struct it is in 
  void (*renderGroup)(GLFWwindow*);
  
  //! constructor
  group_t(void);

  //!Destructor
  ~group_t(void);

  //! set the window and renderBody function pointers
  void setWindowRender(GLFWwindow*, void (*)(GLFWwindow*));
  
  //!Perform Action
  void performAction(int, int, int);

  //!Print orientation and position
  void printKeyframe(ofstream&);

  //! for actions which are not triggered by keys
  void untriggeredActions(void);
  
  //! add a body to the List
  void addBody(void);
  
  //! changing the bot
  void nextBody(void);
  
  //! return current body
  body_t* currentBody(void);

  //! to select a given joint
  int selectJoint(int);

  //! init all the body parts after the context creation
  void initListAfterContext(void);
  
};


//! the struct handles transformation of one part
struct event{
  
  //! to differentiate event for root Root
  int isRoot;
  
  int type;  // type of operation
  
  //! for the root
  body_t *body;
  double p_x, p_y, p_z, pos_speed;
  
  //! for the part_t case
  //! the parameters of the function
  double t_x, t_y, t_z, speed;
  std::string order;
  
  //! the function to be called
  part_t* part;
  
  //! constructor
  event(void);
  
  //! setting the value for part_t
  void setValue(part_t*, double, double, double, double, std::string);
  
  //! setting for the root. 1 = pos
  void setValue(body_t*, double, double, double, double, std::string);
  
  //! execute Event and return the outcome
  int execute(void);
};

namespace bot_t{
  
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

  extern ofstream keyFramesFile;

  extern double camX, camY, camZ;
  extern int recMovie;
  
  extern int playIndicator;

  extern vector<vector<double> > animationFrames;
  extern int stop;

  void openFile(void);
  void closeFile(void);

  void InitGL(void);
  
  //! GLFW callback
  void key_callback(GLFWwindow*, int, int, int, int);
  
  //! execute the eventList
  void executeList(void);
  
  //! append the list of events corresponding to the events related to moving bot
  void transformBot(void);

  //! create the animation frames
  void interpolateFrames(void);

  //! creates necessary animation between 2 frames
  void interpolateBetweenFrames(vector<double>&, vector<double>&);

  //!  sets the values of one frame
  void setFrameValues(vector<double> &);
  
};

#endif
