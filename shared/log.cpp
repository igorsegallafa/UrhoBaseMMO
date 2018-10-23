#include "stdafx.h"
#include "log.h"

#ifdef _SERVER
void LOG( char * pszLog, char * pszMessage )
{
	SYSTEMTIME sSystemTime;
	GetLocalTime( &sSystemTime );

	char szFileName[256], szErrorMessage[2048];
	if( StringCbPrintfA( szFileName, _countof( szFileName ), "Logs\\[%s]%02d-%02d-%04d.log", pszLog, sSystemTime.wMonth, sSystemTime.wDay, sSystemTime.wYear ) != S_OK )
		return;

	StringCbPrintfA( szErrorMessage, _countof( szErrorMessage ), "@ %02d:%02d:%02d -> %s\r\n", sSystemTime.wHour, sSystemTime.wMinute, sSystemTime.wSecond, pszMessage );

	FILE * pFile;
	if( fopen_s( &pFile, szFileName, "a" ) == 0 )
	{
		fputs( szErrorMessage, pFile );
		fclose( pFile );
	}
}

void LOGEx( char * pszLog, char * pszFormat, ... )
{
	va_list vl;

	char szMessage[1024];

	va_start( vl, pszFormat );
	_vsnprintf_s( szMessage, _countof( szMessage ), _TRUNCATE, pszFormat, vl );
	va_end( vl );

	LOG( pszLog, szMessage );
}

void DUMP( void * pvData, int iDataLen )
{
	SYSTEMTIME sSystemTime;
	GetLocalTime( &sSystemTime );

	char szFileName[256];
	if( StringCbPrintfA( szFileName, _countof( szFileName ), "Logs\\%03d-%02d-%02d-%02d-%02d-%02d-%04d.dmp", sSystemTime.wMilliseconds, sSystemTime.wSecond, sSystemTime.wMinute, sSystemTime.wHour, sSystemTime.wDay, sSystemTime.wMonth, sSystemTime.wYear ) != S_OK )
		return;

	FILE * pFile;
	if( fopen_s( &pFile, szFileName, "wb" ) == 0 )
	{
		fwrite( pvData, 1, iDataLen, pFile );
		fclose( pFile );
	}
}
#else
void LOGEx( char * pszLog, char * pszFormat, ... )
{
}
#endif