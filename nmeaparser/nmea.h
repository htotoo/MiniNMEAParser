#ifndef __NMEAHANDLER_H__
#define __NMEAHANDLER_H__

#include <stdint.h>
#include <unistd.h>

#define NMEAHandler_GPSLL_LENGTH 12

class NMEAHandler
{
  public:
    void GotChar(char ch);
    char IsValid() { return isValid; }
    char LatNS() { return gpsLatNS; }
    char LonEW() { return gpsLonEW; }
    char* Lat() { return gpsLat; }
    char* Lon() { return gpsLon; }
    char* Fix() { return fixTime; }

  protected:
    char gpsLat[NMEAHandler_GPSLL_LENGTH] = { '\0' };
    char gpsLon[NMEAHandler_GPSLL_LENGTH] = { '\0' };
    char gpsLatNS = '\0';
    char gpsLonEW = '\0';

    char fixTime[7] = { '\0' };
    char isValid = 'N';
  private:
    uint8_t cmdstate = 0;

}; //NMEAHandler

#endif //__NMEAHANDLER_H__
