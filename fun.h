#ifndef _FUN_H 
#define _FUN_H

int MyLog( char * , char * , char * , ... );
int IsDir( char * );
int IsMonthDate( char * );
int IsDayDate( char * );
int IsHourDate( char * );
int GetLoginInfo( char * , char * , char * );
int GetInDirName( char * szDirName, char * szFullDir );
void ConnectDataBase( char * , char * , char * );
int GetCtrlInfo( PINDEX_DATA );
void DisConnectDataBase(void);
int FreeCtrlData( PINDEX_DATA );
int InitIndexFile( PINDEX_DATA );
int GetCurrTime( char * );
int GetIndexCtrlInfo( PINDEX_DATA );
int GetBlockCtrlInfo( PINDEX_DATA );
char * TrimRight( char * );
char * TrimLeft( char * );
int IsRecordLine( char * );
int RebuildCondExpr( PINDEX_DATA , PCONFIG_RECORD );
long GetFileCount( char * );
int IsRecordLine( char * );
int IsNum( char * );
int MoveFile( char * , char * );
int IsStr( char * );
int IsFloat( char * );

#endif
