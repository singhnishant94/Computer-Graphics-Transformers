#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>

#include "gl_framework.hpp"
#include "transformer_part.hpp"

body_t *transformer1;

//GLFW display callback
void renderGL(GLFWwindow* window)
{
  transformer1->drawBody();
}

int main (int argc, char *argv[]) 
{
  
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(cs475::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  int win_width=512;
  int win_height=512;

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(win_width, win_height, "Transformer", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Keyboard Callback
  glfwSetKeyCallback(window, cs475::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, cs475::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glfwGetFramebufferSize(window, &win_width, &win_height);
  cs475::framebuffer_size_callback(window, win_width, win_height);
  //Initialize GL state
  cs475::initGL();
  
  transformer1 = new body_t();
  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL(window);

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  delete transformer1;

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
