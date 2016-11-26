
#include "nmea.h"

void NMEAHandler::GotChar(char ch)
{
    if ( '$' == ch ) { cmdstate = 0; return; }
    if ( 0 == cmdstate ) if ('G' == ch ) { cmdstate = 1; return; } else { cmdstate = 0; }
    if ( 1 == cmdstate ) if ('P' == ch ) { cmdstate = 2; return; } else { cmdstate = 0; }
    if ( 2 == cmdstate ) if ('G' == ch ) { cmdstate = 3; return; } else { cmdstate = 0; }
    if ( 3 == cmdstate ) if ('L' == ch ) { cmdstate = 4; return; } else { cmdstate = 0; }
    if ( 4 == cmdstate ) if ('L' == ch ) { cmdstate = 5; return;  } else { cmdstate = 0; }
    if ( 5 == cmdstate ) if (',' == ch ) { cmdstate = 20; return;  } else { cmdstate = 0; }
    if (cmdstate>=20 && cmdstate<40)
    {
        if (',' == ch) {
            if (cmdstate == 20) isValid = 'N';
            cmdstate = 40;
            return;
        }
        gpsLat[ cmdstate - 20 ] = ch;
        cmdstate++;
        return;
    }
    if (cmdstate >= 40 && cmdstate <45)
    {
        if ( ',' == ch ) { cmdstate = 50; return; }
        gpsLatNS = ch;
        cmdstate = 41;
        return;
    }
    if (cmdstate >=50 && cmdstate<70)
    {
        if ( ',' == ch)
        {
            if (cmdstate == 50) isValid = 'N';
            cmdstate = 70;
            return;
        }
        gpsLon[ cmdstate -50 ] = ch;
        cmdstate++;
        return;
    }
    if (cmdstate >= 70 && cmdstate <75)
    {
        if ( ',' == ch ) { cmdstate = 75; return; }
        gpsLonEW = ch;
        cmdstate = 71;
        isValid = 'I';
        return;
    }
    if (cmdstate >=75 && cmdstate <85)
    {
        if ( '.' == ch ) { cmdstate = 85; return; }
        if (isValid == 'I') fixTime[ cmdstate - 75 ] = ch;
        cmdstate++;
        return;
    }

}
