#include <memory>
#include "Color.hpp"


class FrameManager;
const char example[] = "\033[22;30ma";
const int StepSize = sizeof(example) / sizeof(example[0]);

  /////////////////
 // Frame class //
/////////////////
class Frame
{
  friend FrameManager;
public:
  // Functions;
  void Write(unsigned char c, int x, int y, ColorRGB color);
  int ID() const;

  // Variables
  int PosX;
  int PosY;
  int FrameWidth;
  int FrameHeight;

private:
  // Private member functions
  void translateToCanvas() const;
  Frame(int id, int x, int y, int width, int height);

  // Variables
  const int _id;
  const int _bufferSize;
  char *_buffer; 
};
