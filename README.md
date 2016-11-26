# MiniNMEAParser

Parses NMEA $GPGLL command, with minimal footprint, or processing requirement.
Simply pass the NMEA communication to it char by char, then query for the result at any time.

Can get:
- Is there currently a valid GPS coordinate?
- Last got coordinates (Lat, Lon)
- When was the coordinates got? (last valid time)
