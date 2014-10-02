#include "part_drawings.hpp"
#include "gl_framework.hpp"
#include <math.h>


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
  

  void drawChest(void){
    
          // Reset The Current Modelview Matrix
          //glLoadIdentity();
          //glScalef(1/4.0, 1/4.0, 1/4.0);
          //NEW//////////////////NEW//////////////////NEW//////////////////NEW/////////////
 
          //glTranslatef(0.0f, 0.0f,-7.0f);       // Translate Into The Screen 7.0 Units
          //glRotatef(rotqube,0.0f,1.0f,0.0f);    // Rotate The cube around the Y axis
          //glRotatef(rotqube,1.0f,1.0f,1.0f);
          glBegin(GL_QUADS);            // Draw The Cube Using quads
            //glColor3f(_r,_g,_b);
            double y_val = 1.4f;
            glVertex3f( 1.0f, y_val,-1.0f);      // Top Right Of The Quad (Top)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Top)
            glVertex3f(-1.0f, 1.0f, 1.0f);      // Bottom Left Of The Quad (Top)
            glVertex3f( 1.0f, y_val, 1.0f);      // Bottom Right Of The Quad (Top)
            //glColor3f(1.0f,0.5f,0.0f);  // Color Orange
            glVertex3f( 1.0f,-y_val, 1.0f);      // Top Right Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f, 1.0f);      // Top Left Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Bottom)
            glVertex3f( 1.0f,-y_val,-1.0f);      // Bottom Right Of The Quad (Bottom)
            //glColor3f(1.0f,0.0f,0.0f);  // Color Red
            glVertex3f( 1.0f, y_val, 1.0f);      // Top Right Of The Quad (Front)
            glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Front)
            glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Front)
            glVertex3f( 1.0f,-y_val, 1.0f);      // Bottom Right Of The Quad (Front)
            //glColor3f(1.0f,1.0f,0.0f);  // Color Yellow
            glVertex3f( 1.0f,-y_val,-1.0f);      // Top Right Of The Quad (Back)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Top Left Of The Quad (Back)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Bottom Left Of The Quad (Back)
            glVertex3f( 1.0f, y_val,-1.0f);      // Bottom Right Of The Quad (Back)
            //glColor3f(1.0f,1.0f,1.0f);  // Color white
            glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Left)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Left)
            //glColor3f(1.0f,0.0f,1.0f);  // Color Violet
            glVertex3f( 1.0f, y_val,-1.0f);      // Top Right Of The Quad (Right)
            glVertex3f( 1.0f, y_val, 1.0f);      // Top Left Of The Quad (Right)
            glVertex3f( 1.0f,-y_val, 1.0f);      // Bottom Left Of The Quad (Right)
            glVertex3f( 1.0f,-y_val,-1.0f);      // Bottom Right Of The Quad (Right)
            //glColor3f(1.0f,0.0f,0.0f);
          glEnd();                      // End Drawing The Cube
 
          //rotqube +=0.9f;                       // Increase Angle

  }

    void drawTorsoChest(void){
    
          // Reset The Current Modelview Matrix
          //glLoadIdentity();
          //glScalef(1/4.0, 1/4.0, 1/4.0);
          //NEW//////////////////NEW//////////////////NEW//////////////////NEW/////////////
 
          //glTranslatef(0.0f, 0.0f,-7.0f);       // Translate Into The Screen 7.0 Units
          //glRotatef(rotqube,0.0f,1.0f,0.0f);    // Rotate The cube around the Y axis
          //glRotatef(rotqube,1.0f,1.0f,1.0f);
          glBegin(GL_QUADS);            // Draw The Cube Using quads
            //glColor3f(_r,_g,_b);
            double y_val = 1.4f;
            glVertex3f( 1.0f, y_val,-1.0f);      // Top Right Of The Quad (Top)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Top)
            glVertex3f(-1.0f, 1.0f, 1.0f);      // Bottom Left Of The Quad (Top)
            glVertex3f( 1.0f, y_val, 1.0f);      // Bottom Right Of The Quad (Top)
            //glColor3f(1.0f,0.5f,0.0f);  // Color Orange
            glVertex3f( 1.0f,-y_val, 1.0f);      // Top Right Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f, 1.0f);      // Top Left Of The Quad (Bottom)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Bottom)
            glVertex3f( 1.0f,-y_val,-1.0f);      // Bottom Right Of The Quad (Bottom)
            
            glColor3f(0.1f,0.1f,0.5f);  // Color Yellow
            glVertex3f( 1.0f,-y_val,-1.0f);      // Top Right Of The Quad (Back)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Top Left Of The Quad (Back)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Bottom Left Of The Quad (Back)
            glVertex3f( 1.0f, y_val,-1.0f);      // Bottom Right Of The Quad (Back)
            //glColor3f(1.0f,1.0f,1.0f);  // Color white
            glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Left)
            glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Left)
            glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Left)
            //glColor3f(1.0f,0.0f,1.0f);  // Color Violet
            glVertex3f( 1.0f, y_val,-1.0f);      // Top Right Of The Quad (Right)
            glVertex3f( 1.0f, y_val, 1.0f);      // Top Left Of The Quad (Right)
            glVertex3f( 1.0f,-y_val, 1.0f);      // Bottom Left Of The Quad (Right)
            glVertex3f( 1.0f,-y_val,-1.0f);      // Bottom Right Of The Quad (Right)
            //glColor3f(1.0f,0.0f,0.0f);
          glEnd();                      // End Drawing The Cube
 
          //rotqube +=0.9f;                       // Increase Angle

  }

  void DrawCircle(float cx, float cy, float r, int num_segments)
  {
      glBegin(GL_TRIANGLE_FAN);
      for(int ii = 0; ii < num_segments; ii++)
      {
          float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

          float x = r * cosf(theta);//calculate the x component
          float y = r * sinf(theta);//calculate the y component

          glVertex2f(x + cx, y + cy);//output vertex

      }
      glEnd();
  }

  void DrawCylinder(float cx, float cy, float r, int num_segments, float width){

    glPushMatrix();
    glTranslatef(0.0f,0.0f,width);
    DrawCircle(cx, cy, r, num_segments);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    DrawCircle(cx, cy, r, num_segments);
    glPopMatrix();
    /*
    for (int i = 0; i < 100; ++i)
    {
      glPushMatrix();
      glTranslatef(0.0f,0.0f,0.0f+i/300.0f);
      DrawCircle(cx, cy, r, num_segments);
      glPopMatrix();
    }*/

    glBegin(GL_TRIANGLE_STRIP);
      for(int ii = 0; ii < num_segments; ii++)
      {
          float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

          float x = r * cosf(theta);//calculate the x component
          float y = r * sinf(theta);//calculate the y component

          glVertex3f(x + cx, y + cy, 0.0f);//output vertex
          glVertex3f(x + cx, y + cy, width);

      }
      glEnd();


  }
  void drawCover(void){

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
    glScalef(1.5f,0.3f,0.5f);
    glColor3f(0.2f,0.2f,0.2f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for torso
  void drawTorso(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.5f,0.0f,0.0f);
    glScalef(1.0f,1.5f,0.5f);
    glColor3f(0.4f,0.4f,0.9f);
    drawTorsoChest();
    glPopMatrix();

    for (int i = 0; i < 3; ++i)
    {
      glPushMatrix();
      glTranslatef(-1.55f+i/2.2,0.0f,0.0f);
      glScalef(0.2f,0.4f,0.3f);
      glColor3f(0.3f,0.3f,0.3f);
      glRotatef(0,0,1,0);
      drawChest();
      glPopMatrix();
    }
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for shoulder
  void drawShoulder(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glScalef(2.1f,0.5f,0.5f);
    glColor3f(0.4f,0.4f,0.4f);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.4f,0.4f,0.0f);
    glRotatef(-90,0,0,1);
    glScalef(0.2f,0.4f,0.4f);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.4f,0.4f,0.0f);
    glRotatef(-90,0,0,1);
    glScalef(0.2f,0.4f,0.4f);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();

    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for neck
  void drawNeck(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glColor3f(0.3f,0.3f,0.6f);
    for (int i = 0; i < 3; ++i)
    {
      glPushMatrix();
      glTranslatef(-0.8f+i/2.2,0.0f,0.0f);
      glScalef(0.2f,0.2f,0.3f);
      glColor3f(0.3f,0.3f,0.3f);
      glRotatef(0,0,1,0);
      drawChest();
      glPopMatrix();
    }

    glPushMatrix();
    glColor3f(0.3f,0.3f,0.6f);
    glTranslatef(0.8f,0.0f,0.0f);
    glScalef(0.4f,0.6f,0.3f);
    drawChest();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3f,0.3f,0.6f);
    glTranslatef(1.35f,0.0f,0.0f);
    glScalef(0.1f,0.6f,0.3f);
    glRotatef(180,0,0,1);
    drawChest();
    glPopMatrix();

    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for arm
  void drawArm(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glScalef(1.0f,0.40f,0.4f);
    glColor3f(0.3f,0.3f,0.7f);
    drawCube();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-1.0f,0.0f,0.0f);
    glScalef(0.4f,0.4f,0.4f);
    glColor3f(0.3f,0.3f,0.3f);
    glRotatef(180,0,1,0);
    drawChest();
    glPopMatrix();

    glColor3f(1.0f,1.0f,1.0f);
    glEndList();  
  }
  
  //! for Hand
  void drawHand(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.3f,0.0f,0.0f);
    glScalef(1.0f,0.30f,0.30f);
    glColor3f(0.5f,0.5f,0.9f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f,0.0f,0.0f);
    glScalef(0.3f,0.3f,0.3f);
    glColor3f(0.3f,0.3f,0.3f);
    glRotatef(180,0,1,0);
    drawChest();
    glPopMatrix();

    glEndList();
  }
  
  //! for Palm 
  void drawPalm(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    
    glPushMatrix();
    glColor3f(0.3f,0.3f,0.9f);
    glTranslatef(-0.6f,0.0f,0.0f);
    glScalef(0.4f,0.3f,0.2f);
    drawChest();
    glPopMatrix();

    for (int i = 0; i < 5; ++i)
    {
      glPushMatrix();
      glRotatef(-5+i*3,0,0,1);
      glTranslatef(0.0f,-0.4f+i/5.0,0.0f);
      glScalef(0.4f,0.05f,0.05f);
      drawCube();
      glPopMatrix();
    }
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for Thigh
  void drawThigh(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glScalef(1.2f,0.6f,0.6f);
    glColor3f(0.4f,0.4f,0.8f);
    drawCube();
    glPopMatrix();

    

    glPushMatrix();
    glTranslatef(-1.2f,0,0);
    glRotatef(0,0,1,0);
    glScalef(0.4f,0.4f,0.4f);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for Leg
  void drawLeg1(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glScalef(1.2f,0.4f,0.4f);
    glColor3f(0.45f,0.45f,0.76f);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f,0,0);
    glRotatef(180,0,1,0);
    glScalef(0.4f,0.4f,0.4f);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0f,-0.45f,0.0f);
    glRotatef(90,1,0,0);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.6f);
    glPopMatrix();

    glColor3f(1.0f,1.0f,1.0f);
    glEndList();  
  }

  void drawLeg2(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glScalef(1.2f,0.4f,0.4f);
    glColor3f(0.45f,0.45f,0.76f);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f,0,0);
    glRotatef(180,0,1,0);
    glScalef(0.4f,0.4f,0.4f);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.0f,1.05f,0.0f);
    glRotatef(90,1,0,0);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.6f);
    glPopMatrix();

    glColor3f(1.0f,1.0f,1.0f);
    glEndList();  
  }
  
  //! for Foot 
  void drawFoot(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(-0.2f,-0.0f,-0.25f);
    glScalef(1.0f,0.5f,0.3f);
    glColor3f(0.6f,0.6f,1.0f);
    drawCube();
    glColor3f(1.0f,1.0f,1.0f);
    glPopMatrix();
    glEndList();
  }
  
  //! for Chest Cover
  void drawChestCover(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);

    glPushMatrix();

    glTranslatef(0.0f,0.0f,0.5f);
    glRotatef(90,0,1,0);
    glScalef(0.1f,1.0f,1.0f);
    drawLine();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(-1.0f,0.0f,0.4f);
    glColor3f(0.1f,0.1f,0.1f);
    for (int i = 0; i < 3; ++i)
    {
      glPushMatrix();
      glTranslatef(-1.55f+i/2.2,0.0f,0.3f);
      glScalef(0.2f,0.4f,0.1f);
      glColor3f(0.3f,0.3f,0.3f);
      glRotatef(0,0,1,0);
      drawChest();
      glPopMatrix();
    }
    //drawLine();
    
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8f,0.0f,0.6f);
    glScalef(1.2f,1.5f,0.1f);
    glColor3f(0.4f,0.4f,0.7f);
    drawChest();
    glColor3f(1.0f,1.0f,1.0f);
    glPopMatrix();
    
    glEndList();
  }
  
  
  //! for HipMid 
  void drawHipMid(int p_num, double len){ //! part number, length
     glNewList(p_num, GL_COMPILE);
     glScalef(0.20f,0.5f,0.5f);
     glColor3f(0.5f,0.5f,0.5f);
     drawChest();
     glEndList();
  }

  //! for PalmPer
  void drawPalmPer1(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
     drawLine();
     glEndList();
  }

    //! for PalmPer
  void drawPalmPer2(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    drawLine();
    glEndList();
  }


};

