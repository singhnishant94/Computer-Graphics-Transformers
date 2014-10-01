#ifndef _PART_DRAWINGS_
#define _PART_DRAWINGS_

namespace drawing_t{
  
  //! to draw a line
  void drawLine(void);
  
  //! to draw a cube
  void drawCube(void);
  
  //! Now the functions to draw various diff body parts
  //! these functions push the various things in a list
  
  //! initList
  void initList(int); //! count of objects to be passed
  
  //! for Hip 
  void drawHip(int, double); //! part number, length
  
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
  void drawLeg(int, double); //! part number, length
  
  //! for Foot 
  void drawFoot(int, double); //! part number, length
  
  //! for Chest Cover
  void drawChestCover(int, double); //! part number, length
};

#endif
