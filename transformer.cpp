#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>

#include "callBacks.hpp"
group_t bot_t::autoBots;

//GLFW display callback
void renderGL(GLFWwindow* window)
{
  
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST); // Accept fragment if it closer to the camera than the former one 
  glDepthFunc(GL_LESS);


  GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] = {0.0, 1.0, 0.0, 1.0};
  GLfloat light_position[] = {3.0, 4.0, 3.0, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  );

  /*
  GLuint normalbuffer;
  glGenBuffers(1, &normalbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);*/
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  bot_t::autoBots.bodyList[0]->drawBody();
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
  glfwSetKeyCallback(window, bot_t::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, cs475::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glfwGetFramebufferSize(window, &win_width, &win_height);
  cs475::framebuffer_size_callback(window, win_width, win_height);
  //Initialize GL state
  cs475::initGL();
  bot_t::autoBots.initListAfterContext();
  bot_t::autoBots.setWindowRender(window, renderGL);
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

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
