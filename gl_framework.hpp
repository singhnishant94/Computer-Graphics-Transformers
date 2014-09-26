/* This part of the code has been written using the help of
   code given to us by Prof. Parag Choudhary for the toyLogo Assignment. */

#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

//! the namespace defines the basic functions related the glfw window
namespace cs475{
  
  //! initialize the window
  void initGL(void);
  
  //! GLFW error call back
    void error_callback(int error, const char* description);
  
  //! GLFW framebuffer resize call back to resize the window
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);

  //! GLFW keyboard callback for handling the key press events
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

#endif
