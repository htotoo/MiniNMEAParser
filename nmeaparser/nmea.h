#ifndef __NMEAHANDLER_H__
#define __NMEAHANDLER_H__

#include <stdint.h>
#include <cstring>
#include <unistd.h>

#define NMEAHandler_GPSLL_LENGTH 12

class NMEAHandler
{
  public:
    uint8_t GotChar(char ch);
    char IsValid() { return (isValid=='I')?'I':'N'; }
    char LatNS() { return (gpsLatNS=='N')?'N':'S'; }
    char LonEW() { return (gpsLonEW=='E')?'E':'W'; }
    char* Lat() { return gpsLat; }
    char* Lon() { return gpsLon; }
    char* Fix() { return fixTime; }
    char* SpeedKmph() { return speedKmph; }

  protected:
    char gpsLat[NMEAHandler_GPSLL_LENGTH] = { 0x30 };
    char gpsLon[NMEAHandler_GPSLL_LENGTH] = { 0x30 };
    char gpsLatNS = 0x30;
    char gpsLonEW = 0x30;

    char fixTime[7] = { 0x30 };
    char speedKmph[9] = { 0x30 };
    char isValid = 'N';
  private:
    uint8_t cmdstate = 0;

}; //NMEAHandler

#endif //__NMEAHANDLER_H__
