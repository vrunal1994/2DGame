#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  framesAreCapped(Gamedata::getInstance().getXmlBool("framesAreCapped")), 
  frameCap(Gamedata::getInstance().getXmlInt("frameCap")), 
  ticks(0),
  totalTicks(0),
  
  started(false), 
   paused(false),   
 sloMo(false), 
  sumOfTicks(SDL_GetTicks()),
  pos( Gamedata::getInstance().getXmlInt("clock/locX"),
       Gamedata::getInstance().getXmlInt("clock/locY"))
  {
  start();
}

void Clock::draw() const { 
  IOManager::getInstance().
    printMessageValueAt("Seconds: ", getSeconds(), pos[0], pos[1]);
  IOManager::getInstance().
    printMessageValueAt("fps: ", getFps(), pos[0], pos[1]+20);
}

void Clock::update() { 

  
  totalTicks = SDL_GetTicks();
  ticks = totalTicks - sumOfTicks;
  if(framesAreCapped && ticks<1000/frameCap)
  SDL_Delay( 1000/frameCap - ticks);
 
  sumOfTicks += ticks;
}

unsigned int Clock::getTicksSinceLastFrame() const {
  return ticks;
}

void Clock::toggleSloMo() {
  sloMo = ! sloMo;
}

int Clock::getFps() const { 
  if ( ticks > 0 ) return 1000/ticks;
  return 0;
}

void Clock::start() { 
  started = true; 
  paused = false; 
}

void Clock::pause() { 
  std::cout << "pause: Not implemented yet" << std::endl;
}

void Clock::unpause() { 
  std::cout << "unpause: Not implemented yet" << std::endl;
}

