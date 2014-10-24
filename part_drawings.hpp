#ifndef _PART_DRAWINGS_
#define _PART_DRAWINGS_

namespace drawing_t{

  //! to draw 4 walls
  void drawWalls(void);

  //! to draw the wall
  void drawWall(void);

  //! to draw the sky
  void drawSky(void);

  //! to draw the ground on which the car runs
  void drawGround(void);
  
  //! to draw a line
  void drawLine(void);

  //! to draw a line of a given length
  void drawLine(double);
  
  //! to draw a cube
  void drawCube(void);
  
  //! Now the functions to draw various diff body parts
  //! these functions push the various things in a list
  
  //! initList
  void initList(int); //! count of objects to be passed
  
  //! for Hip 
  void drawHip(int, double); //! part number, length
      
  //! for Hip 
  void drawHipMid(int, double); //! part number, length

  //! for torso
  void drawTorso(int, double); //! part number, length
  
  //! for shoulder
  void drawShoulder(int, double); //! part number, length
  
  //! for neck
  void drawNeck(int, double); //! part number, length
  
  //! for arm
  void drawArm(int, double); //! part number, length
  
  //! for Hand
  void drawHand(int, double); //! part number, length
  
  //! for Palm 
  void drawPalm(int, double); //! part number, length

  //! for Thigh
  void drawThigh(int, double); //! part number, length
  
  //! for Leg
  void drawLeg1(int, double); //! part number, length

  //! for Leg
  void drawLeg2(int, double); //! part number, length
  
  //! for Foot 
  void drawFoot(int, double); //! part number, length
  
  //! for Chest Cover
  void drawChestCover(int, double); //! part number, length
  
  //! for PalmPer 
  void drawPalmPer1(int, double); //! part number, length
  
  //! for PalmPer 
  void drawPalmPer2(int, double); //! part number, length

  
  //! for Front Wheel 
  void drawWheelFront1(int, double); //! part number, length

  //! for BackWheel 
  void drawWheelBack1(int, double); //! part number, length
  
  //! for Front Wheel 
  void drawWheelFront2(int, double); //! part number, length

  //! for BackWheel 
  void drawWheelBack2(int, double); //! part number, length

  //! for Axle1 
  void drawAxle1(int, double); //! part number, length

  //! for Axle2 
  void drawAxle2(int, double); //! part number, length
  
  void InitGL(int, int);

  void drawChestText(void);

};

#endif
