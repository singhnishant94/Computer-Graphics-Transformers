#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>


#include "callBacks.hpp"
#include "part_drawings.hpp"
using namespace std;

int win_width=512;
int win_height=512;

int SCREEN_WIDTH = 512;
int SCREEN_HEIGHT = 512;

unsigned int framenum=0;
unsigned char *pRGB;

double PI  = M_PI;

int bot_t::light0 = 1, bot_t::light1 = 1;
int bot_t::camera1 = 1, bot_t::camera2 = 0, bot_t::camera3 = 0;
int bot_t::spotlight = 0;
int bot_t::playIndicator = 0;
int bot_t::stop = 0;
int bot_t::recMovie = 0;

int bot_t::moveUp = 0, bot_t::moveDown = 0, 
    bot_t::moveLeft = 0, bot_t::moveRight = 0, bot_t::moveIn = 0, bot_t::moveOut = 0; 

double bot_t::camX = 0.0, bot_t::camY = 0.0, bot_t::camZ = 4.0;

ofstream bot_t::keyFramesFile;

int count = 0;

group_t bot_t::autoBots;
std::list<std::list<event> > bot_t::eventList;          //! list of events to execute
vector<vector<double> > bot_t::animationFrames;
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
GLfloat light_position[] = { 0.0, 10.0, 0.0, 1.0};

GLfloat  spotDir[] = { 0.0f, -1.0f, 0.0f };


void capture_frame(unsigned int framenum)
{
  //global pointer float *pRGB
  pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
  
  glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"./frames/frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}


int spot(double a, double b, double c, double d, double e, double f){

    /*

    a, b and c -- x, y and z co-ordinates for light position

    d, e and f -- x, y and z co-ordinates for spot light position

    */

    GLfloat mat_specular[] = { 0.3, 1.0, 0.3, 1.0 };

    GLfloat mat_shininess[] = { 50.0 };

    GLfloat light_position[] = { a,b,c, 1.0 };

    GLfloat spotDir[] = { d,e,f };

    //glClearColor (0.5, 0.5, 0.5, 0.0);

    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular);

    glLightfv(GL_LIGHT0,GL_POSITION,light_position);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Definig spotlight attributes

    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,30.0);

    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,2.0);

    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);

    return 0;

}
  

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
  if(bot_t::camera1){
    /*
    if(bot_t::moveUp){
      camY += 0.2f;
      bot_t::moveUp = 0;
    }
    if(bot_t::moveDown){
      camY -= 0.2f;
      bot_t::moveDown = 0;
    }
    if(bot_t::moveRight){
      camX += 0.2f;
      bot_t::moveRight = 0;
    }
    if(bot_t::moveLeft){
      camX -= 0.2f;
      bot_t::moveLeft = 0;
    }
    if(bot_t::moveIn){
      camZ -= 0.2f;
      bot_t::moveIn = 0;
    }
    if(bot_t::moveOut){
      camZ += 0.2f;
      bot_t::moveOut = 0;
    }*/
    gluLookAt( bot_t::camX, bot_t::camY, bot_t::camZ,
      0,0,0,
      0.0f, 1.0f,  0.0f);
  }
  else if(bot_t::camera2)
    gluLookAt(center.x - 2.0f*sin(theta_y*PI/180) , center.y,  center.z - 2.0f*cos(theta_y*PI/180),
      center.x - 4.0f*sin(theta_y*PI/180) , center.y,  center.z - 4.0f*cos(theta_y*PI/180),//0,-0.7f,0,
      0.0f, 1.0f,  0.0f);
  else if(bot_t::camera3)  
    gluLookAt(center.x + 4.0f*sin(theta_y*PI/180) , center.y + 2.0f,  center.z+ 4.0f*cos(theta_y*PI/180),
      center.x,center.y,center.z,//0,-0.7f,0,
      0.0f, 1.0f,  0.0f);
  /*
  gluLookAt( 0, 0, 4.0f,
      0,0,0,
      0.0f, 1.0f,  0.0f);*/
    
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glLightfv (GL_LIGHT0, GL_SPECULAR, mat_specular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);  // add lighting. (ambient)
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);

 
  
  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);  // add lighting. (ambient)
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);

  GLfloat HeadLightPosition1[] = { center.x - 0.1f, center.y, center.z, 1.0 };
  GLfloat HeadLightPosition2[] = { center.x + 0.1f, center.y, center.z, 1.0 };

  double param = (90.0 + theta_y)*PI/180;

  GLfloat  HeadLightDir[] = { cos(param), -0.1f, -sin(param) };


  glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);  // add lighting. (ambient)
  glLightfv(GL_LIGHT2, GL_POSITION, HeadLightPosition1);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);

  glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,10.0);
  glLightf(GL_LIGHT2,GL_SPOT_EXPONENT,100.0);
  glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,HeadLightDir);

  glLightfv(GL_LIGHT3, GL_AMBIENT, LightAmbient);  // add lighting. (ambient)
  glLightfv(GL_LIGHT3, GL_POSITION, HeadLightPosition2);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);

  glLightf(GL_LIGHT3,GL_SPOT_CUTOFF,10.0);
  glLightf(GL_LIGHT3,GL_SPOT_EXPONENT,100.0);
  glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,HeadLightDir);




  
  if(bot_t::light0)
    glEnable(GL_LIGHT0);
  else 
    glDisable(GL_LIGHT0);



  if(bot_t::light1)
    glEnable(GL_LIGHT1);
  else 
    glDisable(GL_LIGHT1);

  if(bot_t::spotlight){
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
  }
  else{
  glDisable(GL_LIGHT2);
  glDisable(GL_LIGHT3);
  }
  //glutSolidSphere (2, 20, 20);
  //drawing_t::drawGround();

  glPushMatrix();
  glCallList(23);
  glPopMatrix();
  drawing_t::drawSky();
  drawing_t::drawWalls();
  if(bot_t::playIndicator){
    if(count < bot_t::animationFrames.size()){
      bot_t::setFrameValues(bot_t::animationFrames[count]);
      count++;
      cout<<"IN "<<count<<endl;
    }

  }
  bot_t::autoBots.bodyList[0]->drawBody();
  if (!bot_t::stop) bot_t::executeList();
  if (bot_t::playIndicator) 
    if (bot_t::recMovie) capture_frame(framenum++);
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
      if (!bot_t::stop){
	// look after usual operations
	bot_t::autoBots.untriggeredActions();
      }
    }

  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
