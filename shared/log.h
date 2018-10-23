#pragma once

#ifdef _SERVER
inline void LOG( char * pszLog, char * pszMessage );
void LOGEx( char * pszLog, char * pszFormat, ... );
void DUMP( void * pvData, int iDataLen );
#endif