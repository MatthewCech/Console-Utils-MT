#include <iostream>
#include <cstring>

#include <vector>
#include <thread>


struct GlobalData
{
  int width;
  int height;
  int elementCount;
  char *cleanBuff;
  char *buffer;

  bool threadsCanRun;

  GlobalData(int w=80, int h=10)
    : width(w)
    , height(h)
    , elementCount(width*height)
    , cleanBuff(nullptr)
    , buffer(nullptr)
    , threadsCanRun(false)
  {
    // Create the clean buffer
    cleanBuff = new char[elementCount+1];
    cleanBuff[elementCount] = '\0'; // null term
    for(int index = 0; index < elementCount; ++index)
    {
      if(index%width == width-1) cleanBuff[index] = '\n';
      else cleanBuff[index] = '_';
    }
    resetBuffer();
  }

  inline int CoordToIndex(int x, int y) { return x + width*y; }

  inline void Set(int x, int y, char c) { Set(CoordToIndex(x,y), c); }
  inline void Set(int index, char c) { buffer[index] = c; }

  inline void Set(int x, int y, const char* str) { Set(CoordToIndex(x, y), str); }
  inline void Set(int index, const char* str) 
  {
    int remain = elementCount - index;
    for(int i = 0; i < remain; ++i)
    {
      if((index+i)%width == width-1)
      {
        --remain;
        continue;
      }
      // return if we hit the end of the string
      if(str[i] == '\0') return;
      buffer[index+i] = str[i];
    }
  }

  ~GlobalData()
  {
    if(cleanBuff) delete cleanBuff;
    if(buffer) delete buffer;
  }

  void resetBuffer()
  {
    if(buffer) delete buffer;
    buffer = new char[elementCount+1];
    memcpy(buffer, cleanBuff, elementCount+1);
  }
};

struct ThreadData
{
  int id;

  ThreadData(int id)
    : id(id)
  {}
};


void Clear()
{
#ifdef _WIN32
  system("cls");
#else 
  printf("\033[2J\033[H");
#endif
}



void ThreadFunc(ThreadData* data, GlobalData* global)
{
  while(global->threadsCanRun == false)
  {}

  int count = 0;
  while(global->threadsCanRun)
  {
    global->Set(0, data->id, '0' + data->id);
    global->Set(1, data->id, ':');

    for(int i = 2; i<global->width-2; ++i)
      global->Set(i, data->id, 'A' + count%26);

    count++;
  }
}


int main()
{
  Clear();

  GlobalData globals(120,30);
  globals.Set(1,1, "Hello");

  int threadCount = globals.height;

  std::vector<ThreadData> threadData;
  threadData.reserve(threadCount);
  for(int i = 0; i < threadCount; ++i)
    threadData.push_back(ThreadData(i));

  std::vector<std::thread> threads;
  threads.reserve(threadCount);
  for(ThreadData& data : threadData)
    threads.push_back(std::thread(ThreadFunc, &data, &globals));

  globals.threadsCanRun = true;

  while(true)
  {
    const char* format = "\033[0;0H%s\n";
    printf(format, globals.buffer);
  }

  for(std::thread &thread : threads)
    thread.join();

  return 0;
}
