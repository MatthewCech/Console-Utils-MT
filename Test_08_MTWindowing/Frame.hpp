#include <memory>
#include <string>
#include "Color.hpp"



  /////////////////
 // Frame class //
/////////////////
class FrameManager;
class Frame
{
  friend FrameManager;
public:
  // Functions
  void Write(char c, int x, int y, ColorRGB fg, ColorRGB bg);
  void Write(char *c, int size, int x, int y, ColorRGB fg, ColorRGB bg);
  int ID() const;
  ~Frame();

  // Variable access
  void Relocate(int x, int y);
  void SetSize(int width, int height);
  int Width() const;
  int Height() const;
  int PosX() const;
  int PosY() const;

private:
  // Private Ctor
  Frame(int id, int x, int y, int width, int height);
  
  // Private member functions
  void translateToCanvas() const;
  void initBuffers();
  bool inRange(int val, int min, int max);
  int wrap(int val, int max);

  // Variables
  int _width;
  int _height;
  int _posX;
  int _posY;
  const int _id;
  int _bufferSize;
  char *_bufferChar;
  Attribute *_bufferAttributes; 
};
