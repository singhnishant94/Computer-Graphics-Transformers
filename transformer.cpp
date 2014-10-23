#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <string>


#include "callBacks.hpp"
#include "part_drawings.hpp"
using namespace std;

double PI  = M_PI;

int bot_t::light0 = 1, bot_t::light1 = 1;

group_t bot_t::autoBots;
std::list<std::list<event> > bot_t::eventList;          //! list of events to execute
GLFWwindow* bot_t::window;
void (*bot_t::renderGL)(GLFWwindow*);


/* white ambient light at half intensity (rgba) */
GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };

/* super bright, full intensity diffuse light. */
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

/* position of light (x, y, z, (position of light)) */
GLfloat LightPosition[] = { -1.0, 1.0, 1.0, 1.0 };

//Another method for lighting
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = { 100.0 };
GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0};
  

//GLFW display callback
void renderGL(GLFWwindow* window)
{
  
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST); // Accept fragment if it closer to the camera than the former one 
  glDepthFunc(GL_LESS);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // Set the camera

  vertex_t center = bot_t::autoBots.bodyList[0]->center;
  float theta_x = bot_t::autoBots.bodyList[0]->theta_x;
  float theta_y = bot_t::autoBots.bodyList[0]->theta_y;
  float theta_z = bot_t::autoBots.bodyList[0]->theta_z;
  //cout<<theta_x<<endl;
  /*
  gluLookAt(center.x + 4.0f*sin(theta_y*PI/180) , center.y,  center.z+ 4.0f*cos(theta_y*PI/180),
      center.x,center.y,center.z,//0,-0.7f,0,
      0.0f, 1.0f,  0.0f);
  */
  gluLookAt( 0, 0, 4.0f,
      0,0,0,
      0.0f, 1.0f,  0.0f);
    
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);  // add lighting. (ambient)
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
  if(bot_t::light0)
    glEnable(GL_LIGHT0);
  else 
    glDisable(GL_LIGHT0);
  
  drawing_t::drawGround();
  drawing_t::drawSky();
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
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);

  glfwSetFramebufferSizeCallback(window, cs475::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glfwGetFramebufferSize(window, &win_width, &win_height);
  cs475::framebuffer_size_callback(window, win_width, win_height);
  //Initialize GL state
  cs475::initGL();
  drawing_t::InitGL(512, 512);
  bot_t::InitGL();
  bot_t::autoBots.initListAfterContext();
  bot_t::autoBots.setWindowRender(window, renderGL);
  bot_t::window = window;
  bot_t::renderGL = renderGL;
  
  // Loop until the user closes the window



  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL(window);

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
      
      // look after usual operations
      bot_t::autoBots.untriggeredActions();
    }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
