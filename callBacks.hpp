#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

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

namespace bot_t{
  //!GLFW keyboard callback
  extern group_t autoBots;
  void key_callback(GLFWwindow*, int, int, int, int);
};

#endif
