#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

#include "gl_framework.hpp"
#include "transformer_part.hpp"

struct group_t{
  
  std::vector<body_t*> bodyList;             // the body for which this call back is defined
  int ptr;                              // the current body
  int totCount;                         //  all bodies
  joint_t jName;
  
  //! constructor
  group_t(void);

  //!Destructor
  ~group_t(void);

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
};

namespace bot_t{
  //!GLFW keyboard callback
  extern group_t autoBots;
  void key_callback(GLFWwindow*, int, int, int, int);
};

#endif
