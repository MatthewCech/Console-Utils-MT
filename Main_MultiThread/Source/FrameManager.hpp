///////////////////////////////////////////////////////////
// Handles all creation and destruction of frame objects,
// and hides all of the threading from the user.
///////////////////////////////////////////////////////////
#pragma once
#include "Frame.hpp"
#include "Canvas.hpp"
#include "Containers/Semaphore.hpp"
#include <unordered_map>
#include <thread>
#include <vector>
#include <mutex>



class FrameManager
{
  friend Frame;
public:
  // Constructor
  FrameManager(int adjustmentX = 0, int adjustmentY = 0, int threadCount = 1);
  ~FrameManager();
  Frame *CreateFrame(int x, int y, int width, int height, int layer = 0);
  Frame *GetFrame(int id);
  void DeleteFrame(int id);
  void Update();

  // Thread related
  void Thread_UpdateFrame(const Frame *f, int tid);
  void Thread_WaitYourTurn();
  Frame *Thread_GetNextFrame();

  // Information
  int ScreenWidth() const;
  int ScreenHeight() const;
  int GetFrameCount() const;
private:
  

  // Private Member functions
  bool updateDimensions();
  void initOrderingBuffer();
  void updateOrderingBuffer();
  
  // Variables
  std::unordered_map<int, Frame *> _frames; //maps IDs to frames. 
  std::mutex _frameLock;
  int _frameIterOffset; 
  Semaphore _frameSem;
  
  int _bufferSize;
  int _next_id;
  int _width;
  int _height;
  int _adjustmentX;
  int _adjustmentY;
  int _threadCount;

  struct LayerInfo
  {
    LayerInfo() : ID(0), Layer(0) { }
    LayerInfo(int i, int l) : ID(i), Layer(l) { } 
    int ID;
    int Layer;
  };
  LayerInfo *_ordering; // For each index, has the ID of the frame that can draw there.
  Canvas _canvas;
  std::vector<std::thread> _threads;
};
