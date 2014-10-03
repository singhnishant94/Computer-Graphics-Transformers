#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

#include <list>
#include "transformer_part.hpp"

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
  //! the parameters of the function
  double t_x, t_y, t_z, speed;
  std::string order;
  
  //! the function to be called
  part_t* part;
  
  //! setting the value
  void setValue(part_t*, double, double, double, double, std::string);
  
  //! execute Event and return the outcome
  int execute(void);
};


namespace bot_t{
  
  extern group_t autoBots;
  extern std::list<std::list<event> > eventList;          //! list of events to execute
  extern GLFWwindow* window;
  extern void (*renderGL)(GLFWwindow*);
  
  //! GLFW callback
  void key_callback(GLFWwindow*, int, int, int, int);
  
  //! execute the eventList
  void executeList(void);
  
  //! append the list of events corresponding to the events related to moving bot
  void transformBot(void);

};

#endif
