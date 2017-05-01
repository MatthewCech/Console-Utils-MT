#pragma once
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
  void Write(char c, int x, int y, ColorRGB fg = ColorRGB(), ColorRGB bg = ColorRGB());
  void Write(const char *c, int size, int x, int y, ColorRGB fg = ColorRGB(), ColorRGB bg = ColorRGB());
  void AddBorder(ColorRGB fg = ColorRGB(), ColorRGB bg = ColorRGB());
  void Dump() const;
  int ID() const;
  ~Frame();

  // Variable access
  void SetLocation(int x, int y);
  void SetSize(int width, int height);
  void SetLayer(int newLayer);
  int PosX() const;
  int PosY() const;
  int Width() const;
  int Height() const;
  int Layer() const;

private:
  // Private Ctor
  Frame(int id, FrameManager *m, int x, int y, int width, int height, int layer);

  // Private member functions
  void translateToCanvas() const;
  void initBuffers();
  void clearBuffers();
  bool inRange(int val, int min, int max);
  int wrap(int val, int max);

  // Variables
  int _posX;
  int _posY;
  int _width;
  int _height;
  int _layer;
  const int _id;
  int _bufferSize;
  char *_bufferChar;
  Attribute *_bufferAttributes; 
  FrameManager *_manager;
};
