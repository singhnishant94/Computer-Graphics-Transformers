/* This part of the code has be written taken from the 
   code given to us by Prof. Parag Choudhary for the toyLogo Assignment. */

#include "gl_framework.hpp"

namespace cs475{
  
  int win_width;  //! window width
  int win_height; //! window height
    
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    //glClearDepth(1.0);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // This Will Clear The Background Color To Black
    glClearDepth(1.0);        // Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);       // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);      // Enables Depth Testing
    glShadeModel(GL_SMOOTH);      // Enables Smooth Color Shading

    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-20.0, 20.0, -20.0, 20.0, 0.0, 40.0);*/
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();       // Reset The Projection Matrix

    gluPerspective(45.0f,(GLfloat)win_width/(GLfloat)win_height,0.1f,2000.0f); // Calculate The Aspect Ratio Of The Window
    
    
    /*glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0, 1, 0);*/
    

  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    if  ( height == 0 ) height = 1;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Draw to the whole window
    glViewport( 0, 0, width, height );

    //Keep the aspect ratio fixed
    double aspect;
    if (width > height)
      {
	aspect = (double)width/(double)height;
	glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
      }
    else
      {
	aspect = (double)height/(double)width;
	glOrtho(-1.0, 1.0, -aspect, aspect, -1.0, 1.0);
      }
    
    win_width = width;
    win_height = height;
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
  }
};
