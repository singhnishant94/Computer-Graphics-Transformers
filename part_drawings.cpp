#include "part_drawings.hpp"
#include "gl_framework.hpp"


namespace drawing_t{
  
  //! to draw a line -1, 1 along x axis
  void drawLine(void){
    glBegin(GL_LINES);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();
  }
  
  //! to draw a cube with unity vertices
  void drawCube(void){
    
          // Reset The Current Modelview Matrix
          //glLoadIdentity();
          //glScalef(1/4.0, 1/4.0, 1/4.0);
          //NEW//////////////////NEW//////////////////NEW//////////////////NEW/////////////
 
          //glTranslatef(0.0f, 0.0f,-7.0f);       // Translate Into The Screen 7.0 Units
          //glRotatef(rotqube,0.0f,1.0f,0.0f);    // Rotate The cube around the Y axis
          //glRotatef(rotqube,1.0f,1.0f,1.0f);
          glBegin(GL_QUADS);            // Draw The Cube Using quads
            //glColor3f(_r,_g,_b);
            glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Top)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Top)
            glVertex3f(-1.0f, 1.0f, 1.0f);      // Bottom Left Of The Quad (Top)
            glVertex3f( 1.0f, 1.0f, 1.0f);      // Bottom Right Of The Quad (Top)
            //glColor3f(1.0f,0.5f,0.0f);  // Color Orange
            glVertex3f( 1.0f,-1.0f, 1.0f);      // Top Right Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f, 1.0f);      // Top Left Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Bottom)
            glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Bottom)
            //glColor3f(1.0f,0.0f,0.0f);  // Color Red
            glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Front)
            glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Front)
            glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Front)
            glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Front)
            //glColor3f(1.0f,1.0f,0.0f);  // Color Yellow
            glVertex3f( 1.0f,-1.0f,-1.0f);      // Top Right Of The Quad (Back)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Top Left Of The Quad (Back)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Bottom Left Of The Quad (Back)
            glVertex3f( 1.0f, 1.0f,-1.0f);      // Bottom Right Of The Quad (Back)
            //glColor3f(1.0f,1.0f,1.0f);  // Color white
            glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Left)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Left)
            //glColor3f(1.0f,0.0f,1.0f);  // Color Violet
            glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Right)
            glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Right)
            glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Right)
            glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Right)
            //glColor3f(1.0f,0.0f,0.0f);
          glEnd();                      // End Drawing The Cube
 
          //rotqube +=0.9f;                       // Increase Angle
  }
  
  //! Now the functions to draw various diff body parts
  //! these functions push the various things in a list
  
  //! initList
  void initList(int listItems){ //! count of objects to be passed
    glGenLists(listItems);
  }
  
  //! for Hip 
  void drawHip(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.25f,0.5f);
    glColor3f(0.2f,0.2f,0.2f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for torso
  void drawTorso(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.85f,0.5f);
    glColor3f(0.6f,0.6f,0.6f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for shoulder
  void drawShoulder(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.25f,0.5f);
    glColor3f(0.2f,0.2f,0.2f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for neck
  void drawNeck(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.2f,0.2f);
    glColor3f(0.9f,0.9f,0.9f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for arm
  void drawArm(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.20f,0.20f);
    glColor3f(0.2f,0.2f,0.2f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();  
  }
  
  //! for Hand
  void drawHand(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.18f,0.18f);
    glColor3f(0.7f,0.7f,0.7f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for Thigh
  void drawThigh(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.25f,0.25f);
    glColor3f(0.4f,0.4f,0.4f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for Leg
  void drawLeg(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.2f,0.2f);
    glColor3f(0.65f,0.65f,0.76f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();  
  }
  
  //! for Foot 
  void drawFoot(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(1.0f,0.2f,0.2f);
    glColor3f(0.2f,0.2f,0.2f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
};

