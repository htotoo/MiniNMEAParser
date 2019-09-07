
#include "nmea.h"

uint8_t NMEAHandler::GotChar(char ch)
{
    if ( '$' == ch ) { cmdstate = 0; return cmdstate; }
    if ( 0 == cmdstate ) if ('G' == ch ) { cmdstate = 1; return cmdstate; } else { cmdstate = 0; }
    if ( 1 == cmdstate ) if ('P' == ch ) { cmdstate = 2; return cmdstate; } else { cmdstate = 0; }
    if ( 2 == cmdstate ) if ('G' == ch ) { cmdstate = 3; return cmdstate; } else {
      if ('V' == ch) { cmdstate = 110; return cmdstate; }
      cmdstate = 0; 
    }
    if ( 3 == cmdstate ) if ('L' == ch ) { cmdstate = 4; return cmdstate; } else { cmdstate = 0; }
    if ( 4 == cmdstate ) if ('L' == ch ) { cmdstate = 5; return cmdstate;  } else { cmdstate = 0; }
    if ( 5 == cmdstate ) if (',' == ch ) { cmdstate = 20; return cmdstate;  } else { cmdstate = 0; }
    if (cmdstate>=20 && cmdstate<40)
    {
        if (',' == ch) {
            if (cmdstate == 20) isValid = 'N';
            cmdstate = 40;
            return cmdstate;
        }
        gpsLat[ cmdstate - 20 ] = ch;
        cmdstate++;
        return cmdstate;
    }
    if (cmdstate >= 40 && cmdstate <45)
    {
        if ( ',' == ch ) { cmdstate = 50; return cmdstate; }
        gpsLatNS = ch;
        cmdstate = 41;
        return cmdstate;
    }
    if (cmdstate >=50 && cmdstate<70)
    {
        if ( ',' == ch)
        {
            if (cmdstate == 50) isValid = 'N';
            cmdstate = 70;
            return cmdstate;
        }
        gpsLon[ cmdstate -50 ] = ch;
        cmdstate++;
        return cmdstate;
    }
    if (cmdstate >= 70 && cmdstate <75)
    {
        if ( ',' == ch ) { cmdstate = 75; return cmdstate; }
        gpsLonEW = ch;
        cmdstate = 71;
        isValid = 'I';
        return cmdstate;
    }
    if (cmdstate >=75 && cmdstate <85)
    {
        if ( '.' == ch ) { cmdstate = 85; return cmdstate; }
        if (isValid == 'I') fixTime[ cmdstate - 75 ] = ch;
        cmdstate++;
        return cmdstate;
    }

  //GPVTG V = 2, T = 110, G = 111; $GPVTG,,T,,M,0.151,N,0.280,K,A*2C
  if ( 110 == cmdstate ) if ('T' == ch ) { cmdstate = 111; return cmdstate; } else { cmdstate = 0; }
  if ( 111 == cmdstate ) if ('G' == ch ) { cmdstate = 112; return cmdstate; } else { cmdstate = 0; }
  if (112 <= cmdstate && 140 > cmdstate)
  { //waiting for N char
    if ('N' == ch) { cmdstate = 140; return cmdstate; }
    cmdstate++;
    return cmdstate;
  }
  if (140 == cmdstate) if (',' == ch) { cmdstate = 141; memset(speedKmph, 0, sizeof(speedKmph)); return cmdstate; } else { cmdstate = 0; }
  if (141 <= cmdstate && (141 + 8) > cmdstate )
  {
    if (',' == ch) { cmdstate = 160; return cmdstate; }
    speedKmph[cmdstate-141] = ch;
    cmdstate++;
  }
  return cmdstate;


}
