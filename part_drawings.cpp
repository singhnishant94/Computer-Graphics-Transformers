#include "part_drawings.hpp"
#include "gl_framework.hpp"
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include <string>
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <SOIL/SOIL.h>


namespace drawing_t{


  ///////////////////////////////////////////


  



  GLfloat white[] = {0.6f,0.6f,1.0f, 1.f};

  /* floats for x rotation, y rotation, z rotation */
  float xrot, yrot, zrot;

  /* storage for one texture  */
  GLuint texture[10];

  /* Image type - contains height, width, and data */

  /*
  struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
  };
  typedef struct Image Image;

  // quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
  // See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
  int ImageLoad(const char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
    	printf("File Not Found : %s\n",filename);
    	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
      printf("Error reading width from %s.\n", filename);
      return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
      printf("Error reading height from %s.\n", filename);
      return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
      printf("Error reading planes from %s.\n", filename);
      return 0;
    }
    if (planes != 1) {
      printf("Planes from %s is not 1: %u\n", filename, planes);
      return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
      printf("Error reading bpp from %s.\n", filename);
      return 0;
    }
    if (bpp != 24) {
      printf("Bpp from %s is not 24: %u\n", filename, bpp);
      return 0;
    }
  
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
      printf("Error allocating memory for color-corrected image data");
      return 0; 
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
      printf("Error reading image data from %s.\n", filename);
      return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
      temp = image->data[i];
      image->data[i] = image->data[i+2];
      image->data[i+2] = temp;
    }
    
    // we're done.
    return 1;
  }

  // Load Bitmaps And Convert To Textures
  void LoadGLTextures() { 
    // Load Texture
    Image *image1;
    Image *image2;
    Image *image3;
    Image *image4;
    Image *image5;
    Image *image6;
    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
      printf("Error allocating space for image");
      exit(0);
    }

    image2 = (Image *) malloc(sizeof(Image));
    if (image2 == NULL) {
      printf("Error allocating space for image");
      exit(0);
    }

    image3 = (Image *) malloc(sizeof(Image));
    if (image3 == NULL) {
      printf("Error allocating space for image");
      exit(0);
    }

    image4 = (Image *) malloc(sizeof(Image));
    if (image4 == NULL) {
      printf("Error allocating space for image");
      exit(0);
    }

    image5 = (Image *) malloc(sizeof(Image));
    if (image5 == NULL) {
      printf("Error allocating space for image");
      exit(0);
    }
    
    image6 = (Image *) malloc(sizeof(Image));
    if (image6 == NULL) {
      printf("Error allocating space for image");
      exit(0);
    }

    // Create Texture 
    glGenTextures(6, texture);

    if (!(ImageLoad("Data/lesson6/chest.bmp", image1))){
      exit(1);
    }     

    if (!(ImageLoad("Data/lesson6/metal.bmp", image2))){
      exit(1);
    }   
       
    if (!(ImageLoad("Data/lesson6/tyre.bmp", image3))){
      exit(1);
    }  

    if (!(ImageLoad("Data/lesson6/sky.bmp", image4))){
      exit(1);
    }  
    
    if (!(ImageLoad("Data/lesson6/ground.bmp", image5))){
      exit(1);
    } 

    */
    /*
    if (!(ImageLoad("Data/lesson6/sky.bmp", image6))){
      exit(1);
    } 
*/
    /*
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)


    

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP );
    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT );

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);


    glBindTexture(GL_TEXTURE_2D, texture[1]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP );
    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT );

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->data);



    glBindTexture(GL_TEXTURE_2D, texture[2]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP );
    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT );

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->data);




    glBindTexture(GL_TEXTURE_2D, texture[3]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP );
    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT );

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image4->data);


    glBindTexture(GL_TEXTURE_2D, texture[4]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP );
    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT );

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image5->sizeX, image5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image5->data);

    /*
    glBindTexture(GL_TEXTURE_2D, texture[5]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP );
    //glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT );

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image6->sizeX, image6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image6->data);
  }

  */

  int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
  {
      /* load an image file directly as a new OpenGL texture */
      texture[0] = SOIL_load_OGL_texture
          (
          "Data/lesson6/chest.bmp",
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
          );
   
      if(texture[0] == 0)
          return false;
  
      // Typical Texture Generation Using Data From The Bitmap
      glBindTexture(GL_TEXTURE_2D, texture[0]);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   
      /* load an image file directly as a new OpenGL texture */
      texture[1] = SOIL_load_OGL_texture
          (
          "Data/lesson6/metal.bmp",
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
          );
   
      if(texture[1] == 0)
          return false;
  
      // Typical Texture Generation Using Data From The Bitmap
      glBindTexture(GL_TEXTURE_2D, texture[1]);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

      /* load an image file directly as a new OpenGL texture */
      texture[2] = SOIL_load_OGL_texture
          (
          "Data/lesson6/tyre.bmp",
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
          );
   
      if(texture[2] == 0)
          return false;
  
      // Typical Texture Generation Using Data From The Bitmap
      glBindTexture(GL_TEXTURE_2D, texture[2]);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

      /* load an image file directly as a new OpenGL texture */
      texture[3] = SOIL_load_OGL_texture
          (
          "Data/lesson6/sky.bmp",
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
          );
   
      if(texture[3] == 0)
          return false;
  
      // Typical Texture Generation Using Data From The Bitmap
      glBindTexture(GL_TEXTURE_2D, texture[3]);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

      /* load an image file directly as a new OpenGL texture */
      texture[4] = SOIL_load_OGL_texture
          (
          "Data/lesson6/ground.bmp",
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
          );
   
      if(texture[4] == 0)
          return false;
  
      // Typical Texture Generation Using Data From The Bitmap
      glBindTexture(GL_TEXTURE_2D, texture[4]);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

      return true;                                        // Return Success
  }


  ///////////////////////////////////////////

  //Another method for lighting
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = { 100.0 };



  void drawSky(void){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture[3]); 
    //GLfloat col1[] = {0.0f,0.0f,1.0f, 1.f};
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.4f,0.8f,0.95f);
    glScalef(1000.0f, 1000.0f, 1000.0f);
    glBegin(GL_QUADS);            // Draw The Cube Using quads
    //glColor3f(_r,_g,_b);
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Top)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Top)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Bottom Left Of The Quad (Top)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Bottom Right Of The Quad (Top)
    //glColor3f(1.0f,0.5f,0.0f);  // Color Orange
    glNormal3f( 0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Top Right Of The Quad (Bottom)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Top Left Of The Quad (Bottom)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Bottom)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Bottom)
    //glColor3f(1.0f,0.0f,0.0f);  // Color Red
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Front)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Front)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Front)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Front)
    //glColor3f(1.0f,1.0f,0.0f);  // Color Yellow
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Top Right Of The Quad (Back)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Top Left Of The Quad (Back)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Bottom Left Of The Quad (Back)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Bottom Right Of The Quad (Back)
    //glColor3f(1.0f,1.0f,1.0f);  // Color white
    glNormal3f( -1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Left)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Left)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Left)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Left)
    //glColor3f(1.0f,0.0f,1.0f);  // Color Violet
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Right)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Right)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Right)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Right)
    //glColor3f(1.0f,0.0f,0.0f);
    glEnd();                      // End Drawing The Cube
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
 
  }

  void drawQuad(double side, double y_off){
    glNewList(22, GL_COMPILE);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture[4]); 
        glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f( 0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( side, -y_off,-side);      // Top Right Of The Quad (Top)
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-side, -y_off,-side);      // Top Left Of The Quad (Top)
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-side, -y_off, side);      // Bottom Left Of The Quad (Top)
        glTexCoord2f(0.0f, 1.0f); glVertex3f( side, -y_off, side);      // Bottom Right Of The Quad (Top)
        glEnd();
        glPopMatrix();
    glPopMatrix();
    glEndList();
  }

  void drawGround(double side, double y_off, int l, int m){
    glNewList(23, GL_COMPILE);
    
    
    glPushMatrix();
    glTranslatef(-side*l, 0, -side*m);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    

    
    GLfloat col1[] = {0.0f,1.0f,0.0f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col1);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0f,1.0f,0.0f);
    for(int i = 0; i < l; i++)
      for(int j = 0; j < m; j++){
        glPushMatrix();
        glTranslatef(i*side*2, 0, j*side*2);
        glPushMatrix();
        glCallList(22);
        glPopMatrix();
        glPopMatrix();
      }

    //glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
    glEndList();
  }


  
  
  //! to draw a line -1, 1 along x axis
  void drawLine(void){
    glBegin(GL_LINES);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();
  }

    //! to draw a line of a given length along x axis
  void drawLine(double len){
    glBegin(GL_LINES);
    glVertex3f(-len / 2.0, 0, 0);
    glVertex3f(len / 2.0, 0, 0);
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
    glBindTexture(GL_TEXTURE_2D, texture[1]);   // choose the texture to use.
    glBegin(GL_QUADS);            // Draw The Cube Using quads
    //glColor3f(_r,_g,_b);
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Top)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Top)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Bottom Left Of The Quad (Top)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Bottom Right Of The Quad (Top)
    //glColor3f(1.0f,0.5f,0.0f);  // Color Orange
    glNormal3f( 0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Top Right Of The Quad (Bottom)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Top Left Of The Quad (Bottom)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Bottom)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Bottom)
    //glColor3f(1.0f,0.0f,0.0f);  // Color Red
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Front)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Front)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Front)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Front)
    //glColor3f(1.0f,1.0f,0.0f);  // Color Yellow
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Top Right Of The Quad (Back)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Top Left Of The Quad (Back)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Bottom Left Of The Quad (Back)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Bottom Right Of The Quad (Back)
    //glColor3f(1.0f,1.0f,1.0f);  // Color white
    glNormal3f( -1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Left)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Left)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Left)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Left)
    //glColor3f(1.0f,0.0f,1.0f);  // Color Violet
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Right)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Right)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Right)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Right)
    //glColor3f(1.0f,0.0f,0.0f);
    glEnd();                      // End Drawing The Cube
 
    //rotqube +=0.9f;                       // Increase Angle
  }
  

  void drawChestText(void){

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear The Screen And The Depth Buffer
    //glPushMatrix();
    //glLoadIdentity();       // Reset The View

    //glTranslatef(0.0f,0.0f,-5.0f);              // move 5 units into the screen.
    
    //glRotatef(xrot,1.0f,0.0f,0.0f);   // Rotate On The X Axis
    //glRotatef(yrot,0.0f,1.0f,0.0f);   // Rotate On The Y Axis
    //glRotatef(zrot,0.0f,0.0f,1.0f);   // Rotate On The Z Axis

    glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
    glBegin(GL_QUADS);                    // begin drawing a cube
    double y_val = 1.4f;
    // Front Face (note that the texture's corners have to match the quad's corners)
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.15f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -y_val,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  y_val,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.85f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    
    // Back Face
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  y_val, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -y_val, -1.0f);  // Bottom Left Of The Texture and Quad
  
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  y_val,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  y_val, -1.0f);  // Top Right Of The Texture and Quad
    
    // Bottom Face  
    glNormal3f( 0.0f, -1.0f, 0.0f);     
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -y_val, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -y_val,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    
    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -y_val, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,  y_val, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  y_val,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, -y_val,  1.0f);  // Bottom Left Of The Texture and Quad
    
    // Left Face
    glNormal3f( -1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    
    glEnd();                                    // done with the polygon.
    //glPopMatrix();
    
    //xrot+=1.0f;                    // X Axis Rotation  
    //yrot+=1.0f;                    // Y Axis Rotation
    //zrot+=1.0f;                    // Z Axis Rotation

    // since this is double buffered, swap the buffers to display what just got drawn.
    //glutSwapBuffers();


  }

  void drawChest(void){
    
    // Reset The Current Modelview Matrix
    //glLoadIdentity();
    //glScalef(1/4.0, 1/4.0, 1/4.0);
    //NEW//////////////////NEW//////////////////NEW//////////////////NEW/////////////
 
    //glTranslatef(0.0f, 0.0f,-7.0f);       // Translate Into The Screen 7.0 Units
    //glRotatef(rotqube,0.0f,1.0f,0.0f);    // Rotate The cube around the Y axis
    //glRotatef(rotqube,1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D, texture[3]);   // choose the texture to use.
    glBegin(GL_QUADS);            // Draw The Cube Using quads
    //glColor3f(_r,_g,_b);
    double y_val = 1.4f;
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, y_val,-1.0f);      // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);      // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, y_val, 1.0f);      // Bottom Right Of The Quad (Top)
    //glColor3f(1.0f,0.5f,0.0f);  // Color Orange
    glNormal3f( 0.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f,-y_val, 1.0f);      // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);      // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-y_val,-1.0f);      // Bottom Right Of The Quad (Bottom)
    //glColor3f(1.0f,0.0f,0.0f);  // Color Red
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.8f); glVertex3f( 1.0f, y_val, 1.0f);      // Top Right Of The Quad (Front)
    glTexCoord2f(0.0f, 0.6f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Front)
    glTexCoord2f(0.0f, 0.4f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Front)
    glTexCoord2f(1.0f, 0.2f); glVertex3f( 1.0f,-y_val, 1.0f);      // Bottom Right Of The Quad (Front)
    //glColor3f(1.0f,1.0f,0.0f);  // Color Yellow
    glNormal3f( 0.0f, 0.0f, -1.0f);
    glVertex3f( 1.0f,-y_val,-1.0f);      // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);      // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);      // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, y_val,-1.0f);      // Bottom Right Of The Quad (Back)
    //glColor3f(1.0f,1.0f,1.0f);  // Color white
    glNormal3f( -1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Left)
    //glColor3f(1.0f,0.0f,1.0f);  // Color Violet
    glNormal3f( 1.0f, 0.0f, 0.0f);
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
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    for(int ii = 0; ii <= num_segments+1; ii++)
      {

      GLfloat col1[] = {ii%2,ii%2,ii%2, 1.f};
      glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    	glColor3f(ii%2,ii%2,ii%2);
    	float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

    	float x = r * cosf(theta);//calculate the x component
    	float y = r * sinf(theta);//calculate the y component
    	if(ii==0) glVertex2f(cx, cy);
    	else glVertex2f(x + cx, y + cy);//output vertex

      }
    glEnd();
    glPopMatrix();
  }

  void DrawCylinder(float cx, float cy, float r, int num_segments, float width){

    glPushMatrix();
    glTranslatef(0.0f,0.0f,width);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    DrawCircle(cx, cy, r, num_segments);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    glNormal3f( 0.0f, 0.0f, -1.0f);
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
    glBindTexture(GL_TEXTURE_2D, texture[2]);   // choose the texture to use.
    glPushMatrix();
    GLfloat col1[] = {0.4f,0.4f,0.4f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.4f,0.4f,0.4f);
    glBegin(GL_TRIANGLE_STRIP);
    for(int ii = 0; ii <= num_segments + 1; ii++)
      {
    	float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

    	float x = r * cosf(theta);//calculate the x component
    	float y = r * sinf(theta);//calculate the y component
      glNormal3f( x + cx, y + cy, 0.0f);
    	glTexCoord2f((ii)%2, (ii)%2); glVertex3f(x + cx, y + cy, 0.0f);//output vertex
    	glTexCoord2f((ii)%2, (1+ii)%2); glVertex3f(x + cx, y + cy, width);

      }
    glEnd();
    glPopMatrix();


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
    GLfloat col1[] = {0.2f,0.2f,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.2f,0.2f,0.2f);
    drawCube();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);

    glScalef(100.0f, 0.01f, 100.0f);
    GLfloat col2[] = {0.0f,1.0f,0.0f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0f,1.0f,0.0f);

    
    
    
    //GLfloat col3[] = {0.2f,0.2f,0.2f, 1.f};
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col3);
    //glEnable(GL_COLOR_MATERIAL);
    //glColor3f(0.2f,0.2f,0.2f);

    /*
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glVertex3f( 1000.0f, -10.0f,-1000.0f);      // Top Right Of The Quad (Top)
    glVertex3f(-1000.0f, -10.0f,-1000.0f);      // Top Left Of The Quad (Top)
    glVertex3f(-1000.0f, -10.0f, 1000.0f);      // Bottom Left Of The Quad (Top)
    glVertex3f( 1000.0f, -10.0f, 1000.0f);      // Bottom Right Of The Quad (Top)
    glEnd();*/
    //drawCube();
    /*
    GLfloat amb[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat dif[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat spec[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat emm[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat shin[] = { 0 };
    
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, amb );
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, dif );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, spec );
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 0 );*/

    /*
    glEnable(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, texture[4]);   // choose the texture to use.
    glBegin(GL_QUADS);            // Draw The Cube Using quads
    //glColor3f(_r,_g,_b);
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Top)
    glTexCoord2f(100.0f, 0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Top)
    glTexCoord2f(100.0f, 100.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Bottom Left Of The Quad (Top)
    glTexCoord2f(0.0f, 100.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Bottom Right Of The Quad (Top)

    */


    //glColor3f(1.0f,0.5f,0.0f);  // Color Orange
    /*glNormal3f( 0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Top Right Of The Quad (Bottom)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Top Left Of The Quad (Bottom)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Bottom)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Bottom)
    //glColor3f(1.0f,0.0f,0.0f);  // Color Red
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Front)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Front)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Front)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Front)
    //glColor3f(1.0f,1.0f,0.0f);  // Color Yellow
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Top Right Of The Quad (Back)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Top Left Of The Quad (Back)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Bottom Left Of The Quad (Back)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Bottom Right Of The Quad (Back)
    //glColor3f(1.0f,1.0f,1.0f);  // Color white
    glNormal3f( -1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Left)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Left)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Left)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Left)
    //glColor3f(1.0f,0.0f,1.0f);  // Color Violet
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Right)
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Right)
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Right)
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Right)
    //glColor3f(1.0f,0.0f,0.0f);*/
    //glEnd();                      // End Drawing The Cube
    //glDisable(GL_TEXTURE_2D);


    
    glEndList();


  }
  
  //! for torso
  void drawTorso(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.5f,0.0f,0.0f);
    glScalef(1.0f,1.5f,0.5f);
    GLfloat col1[] = {0.4f,0.4f,0.9f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.4f,0.4f,0.9f);
    //drawTorsoChest();
    drawTorsoChest();
    glPopMatrix();

    for (int i = 0; i < 3; ++i)
    {
    	glPushMatrix();
    	glTranslatef(-1.55f+i/2.2,0.0f,0.0f);
    	glScalef(0.2f,0.4f,0.3f);
      GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
      glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    	glColor3f(0.3f,0.3f,0.3f);
    	glRotatef(0,0,1,0);
    	drawChest();
    	glPopMatrix();
    }
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for shoulder
  void drawShoulder(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glScalef(2.1f,0.5f,0.5f);
    GLfloat col1[] = {0.4f,0.4f,0.4f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.4f,0.4f,0.4f);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.4f,0.4f,0.0f);
    glRotatef(-90,0,0,1);
    glScalef(0.2f,0.4f,0.4f);
    GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.4f,0.4f,0.0f);
    glRotatef(-90,0,0,1);
    glScalef(0.2f,0.4f,0.4f);
    GLfloat col3[] = {0.3f,0.3f,0.3f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col3);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for neck
  void drawNeck(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    GLfloat col1[] = {0.3f,0.3f,0.6f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.3f,0.3f,0.6f);
    for (int i = 0; i < 3; ++i)
      {
    	glPushMatrix();
    	glTranslatef(-0.8f+i/2.2,0.0f,0.0f);
    	glScalef(0.2f,0.2f,0.3f);
      GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
      glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    	glColor3f(0.3f,0.3f,0.3f);
    	glRotatef(0,0,1,0);
    	drawChest();
    	glPopMatrix();
      }

    glPushMatrix();
    GLfloat col3[] = {0.3f,0.3f,0.6f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col3);
    glColor3f(0.3f,0.3f,0.6f);
    glTranslatef(0.8f,0.0f,0.0f);
    glScalef(0.4f,0.6f,0.3f);
    //glEnable(GL_TEXTURE_2D);
    drawChest();
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    GLfloat col4[] = {0.3f,0.3f,0.6f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col4);
    glColor3f(0.3f,0.3f,0.6f);
    glTranslatef(1.35f,0.0f,0.0f);
    glScalef(0.1f,0.6f,0.3f);
    glRotatef(180,0,0,1);
    drawChest();
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for arm
  void drawArm(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glScalef(1.0f,0.40f,0.4f);
    GLfloat col1[] = {0.3f,0.3f,0.7f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.3f,0.3f,0.7f);
    glEnable(GL_TEXTURE_2D);
    drawCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-1.0f,0.0f,0.0f);
    glScalef(0.4f,0.4f,0.4f);
    GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.3f,0.3f,0.3f);
    glRotatef(180,0,1,0);
    drawChest();
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();  
  }
  
  //! for Hand
  void drawHand(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.3f,0.0f,0.0f);
    glScalef(1.0f,0.30f,0.30f);
    GLfloat col1[] = {0.5f,0.5f,0.9f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.5f,0.5f,0.9f);
    glEnable(GL_TEXTURE_2D);
    drawCube();
    glDisable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f,0.0f,0.0f);
    glScalef(0.3f,0.3f,0.3f);
    GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
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
    GLfloat col1[] = {0.3f,0.3f,0.9f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
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
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  //! for Thigh
  void drawThigh(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glScalef(1.2f,0.6f,0.6f);
    GLfloat col1[] = {0.4f,0.4f,0.8f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.4f,0.4f,0.8f);
    glEnable(GL_TEXTURE_2D);
    drawCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    

    glPushMatrix();
    glTranslatef(-1.2f,0,0);
    glRotatef(0,0,1,0);
    glScalef(0.4f,0.4f,0.4f);
    GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for Leg
  void drawLeg1(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glScalef(1.2f,0.4f,0.4f);
    GLfloat col1[] = {0.45f,0.45f,0.76f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.45f,0.45f,0.76f);
    glEnable(GL_TEXTURE_2D);
    drawCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f,0,0);
    glRotatef(180,0,1,0);
    glScalef(0.4f,0.4f,0.4f);
    GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();


    /*    glPushMatrix();
    glTranslatef(0.5f,-0.45f,-0.2f);
    glRotatef(90,1,0,0);
    GLfloat col3[] = {0.2f,0.2,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col3);
    glColor3f(0.2f,0.2,0.2f);
    glEnable(GL_TEXTURE_2D);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.8f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    */
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();  
  }

  void drawLeg2(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.4f,0.0f,0.0f);
    glScalef(1.2f,0.4f,0.4f);
    GLfloat col1[] = {0.45f,0.45f,0.76f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.45f,0.45f,0.76f);
    glEnable(GL_TEXTURE_2D);
    drawCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f,0,0);
    glRotatef(180,0,1,0);
    glScalef(0.4f,0.4f,0.4f);
    GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.3f,0.3f,0.3f);
    drawChest();
    glPopMatrix();

    /*
    glPushMatrix();
    glTranslatef(0.5f,1.25f,-0.2f);
    glRotatef(90,1,0,0);
    GLfloat col3[] = {0.2f,0.2,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col3);
    glColor3f(0.2f,0.2,0.2f);
    glEnable(GL_TEXTURE_2D);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.8f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();  
  }
  
  //! for Foot 
  void drawFoot(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glTranslatef(-0.2f,-0.0f,-0.25f);
    glScalef(1.0f,0.5f,0.3f);
    GLfloat col[] = {0.6f,0.6f,1.0f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
    glColor3f(0.6f,0.6f,1.0f);
    drawCube();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
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
    GLfloat col1[] = {0.1f,0.1f,0.1f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.1f,0.1f,0.1f);
    for (int i = 0; i < 3; ++i)
      {
    	glPushMatrix();
    	glTranslatef(-1.55f+i/2.2,0.0f,0.3f);
    	glScalef(0.2f,0.4f,0.1f);
      GLfloat col2[] = {0.3f,0.3f,0.3f, 1.f};
      glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
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
    //glColor3f(0.4f,0.4f,0.7f);
    //drawChest();
    GLfloat col3[] = {0.3f,0.3f,0.3f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col3);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(0.3f,0.3f,0.3f);
    glPushMatrix();
    //glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

    drawChestText();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //glColor3f(1.0f,1.0f,1.0f);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    
    glEndList();
  }
  
  
  //! for HipMid 
  void drawHipMid(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glScalef(0.20f,0.5f,0.5f);
    GLfloat col[] = {0.5f,0.5f,0.5f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
    glColor3f(0.5f,0.5f,0.5f);
    drawChest();
    glEndList();
  }

  //! for PalmPer
  void drawPalmPer1(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glScalef(1.0f,0.1f,0.1f);
    GLfloat col1[] = {0.4f,0.4f,0.8f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.4f,0.4f,0.8f);
    drawCube();
    glPopMatrix();

    /*    glPushMatrix();
    glTranslatef(1.0f,0.1f,0.0f);
    glRotatef(-90,1,0,0);
    GLfloat col2[] = {0.2f,0.2,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.2f,0.2,0.2f);
    glEnable(GL_TEXTURE_2D);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.6f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();


  }

  //! for PalmPer
  void drawPalmPer2(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glScalef(1.0f,0.1f,0.1f);
    GLfloat col1[] = {0.4f,0.4f,0.8f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.4f,0.4f,0.8f);
    drawCube();
    glPopMatrix();
    /*
    glPushMatrix();
    glTranslatef(1.0f,-0.1f,0.0f);
    glRotatef(90,1,0,0);
    GLfloat col2[] = {0.2f,0.2,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.2f,0.2,0.2f);
    glEnable(GL_TEXTURE_2D);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.6f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();*/
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }

  
  //! for Front Wheel
  void drawWheelFront1(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    
    glPushMatrix();
    //glTranslatef(1.0f,0.1f,0.0f);
    glRotatef(-90,1,0,0);
    GLfloat col2[] = {0.2f,0.2,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.2f,0.2,0.2f);
    glEnable(GL_TEXTURE_2D);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.6f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    
    glEndList();
  }

  //! for Front Wheel
  void drawWheelBack1(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);

    glPushMatrix();
    //glTranslatef(0.5f,-0.45f,-0.2f);
    glRotatef(90,1,0,0);
    GLfloat col3[] = {0.2f,0.2,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col3);
    glColor3f(0.2f,0.2,0.2f);
    glEnable(GL_TEXTURE_2D);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.8f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);    
    
    glEndList();
  }

  //! for Front Wheel
  void drawWheelFront2(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
 
    glRotatef(90,1,0,0);
    GLfloat col2[] = {0.2f,0.2,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col2);
    glColor3f(0.2f,0.2,0.2f);
    glEnable(GL_TEXTURE_2D);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.6f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    
    glEndList();
  }

  //! for Front Wheel
  void drawWheelBack2(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    
    glPushMatrix();
    //glTranslatef(0.5f,1.25f,-0.2f);
    glRotatef(90,1,0,0);
    GLfloat col3[] = {0.2f,0.2,0.2f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col3);
    glColor3f(0.2f,0.2,0.2f);
    glEnable(GL_TEXTURE_2D);
    DrawCylinder(0.0f,0.0f,1.0f,50,0.8f);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    
    glEndList();
  }


  //! for Axle1 
  void drawAxle1(int p_num, double len){ //! part number, length
    glNewList(p_num, GL_COMPILE);
    glPushMatrix();
    glScalef(len, 0.1f,0.1f);
    GLfloat col1[] = {0.4f,0.4f,0.8f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, col1);
    glColor3f(0.4f,0.4f,0.8f);
    drawCube();
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glColor3f(1.0f,1.0f,1.0f);
    glEndList();
  }
  
  //! for Axle2 
  void drawAxle2(int p_num, double len){ //! part number, length
  
  }


  /* A general OpenGL initialization function.  Sets all of the initial parameters. */
  void InitGL(int Width, int Height)          // We call this right after our OpenGL window is created.
  {
    LoadGLTextures();       // Load The Texture(s) 
    //glEnable(GL_TEXTURE_2D);      // Enable Texture Mapping
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f); // Clear The Background Color To Blue 
    glClearDepth(1.0);        // Enables Clearing Of The Depth Buffer

    int l = 100, m = 100;
    double side = 0.05;
    double y_off = 0.8;

    drawQuad(side, y_off);
    drawGround(side, y_off, l, m);
    
  }


};

