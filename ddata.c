

/********************************************************************
copyright (C), 1995-2004, Si-Tech Information Technology Ltd. 
file_name: ddata.c   
author: 张凡 version: （V1.00） date: （2004－08－20）
description: 数据操作功能函数
others:
history: 1.date: 修改时间 version: 版本（V1.00）author: 作者
			modification: 修改内容
		 2. ... 
********************************************************************/


#include "ddef.h"


/********************************************************** 
function: DebugOutIndexControlRecord
description: 输出索引文件控制记录内容
Input:	picRecord: 索引文件控制记录
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutIndexControlRecord( PICTRL_RECORD picRecord )
{
	printf( "[%s] [%s] [%s] [%s] [%s] [%s] [%s] [%s]\n", 
						picRecord->szIndexType,
						picRecord->szIndexFlag,
						picRecord->szIndexDir,
						picRecord->szEffectStartTime,
						picRecord->szEffectEndTime,
						picRecord->szIndexStartTime,
						picRecord->szIndexEndTime,
						picRecord->szBlockLink );
						
	return MY_SUCCEED;
}

/********************************************************** 
function: DebugOutIndexControlInfo
description: 输出索引文件控制信息
Input:	picData: 索引文件控制信息
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutIndexControlInfo( PICTRL_DATA picData )
{
	PICTRL_RECORD picRecord;
	int nLoop;
	
	picRecord = picData->picRecord;

	printf( "\n\t=== index control info ===\n\n" );
	
	for( nLoop = 0; nLoop < picData->nRecCount; nLoop++, picRecord++ )
	{
		DebugOutIndexControlRecord( picRecord );
	}

	printf( "\n\t=== index control info ===\n\n" );
		
	return MY_SUCCEED;
}

/********************************************************** 
function: DebugOutBlockControlRecord
description: 输出索引数据块控制记录内容
Input:	picRecord: 索引数据块控制记录
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutBlockControlRecord( PBCTRL_RECORD pbcRecord )
{
	printf( "[%s] [%s] [%s] [%s] [%s] [%s] [%d] [%d]\n", 
						pbcRecord->szIndexType,
						pbcRecord->szBlockLink,
						pbcRecord->szBlockFlag,
						pbcRecord->szBlockStartTime,
						pbcRecord->szBlockEndTime,
						pbcRecord->szBlockUnit,
						pbcRecord->nBlockNum,
						pbcRecord->nBlockSize );
						
	return MY_SUCCEED;
}

/********************************************************** 
function: DebugOutBlockControlInfo
description: 输出索引数据块控制信息
Input:	picData: 索引数据块控制信息
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutBlockControlInfo( PBCTRL_DATA pbcData )
{
	PBCTRL_RECORD pbcRecord;
	int nLoop;
	
	pbcRecord = pbcData->pbcRecord;

	printf( "\n\t=== block control info ===\n\n" );
	
	for( nLoop = 0; nLoop < pbcData->nRecCount; nLoop++, pbcRecord++ )
	{
		DebugOutBlockControlRecord( pbcRecord );
	}

	printf( "\n\t=== block control info ===\n\n" );
		
	return MY_SUCCEED;
}

/********************************************************** 
function: DebugOutIndexFieldConfig
description: 输出索引字段配置信息
Input:	piConfig: 索引字段配置信息
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutIndexFieldConfig( PINDEX_CONFIG piConfig )
{
	PCONFIG_RECORD pcRecord;
	PCLEAN_FIELD pcField;
	PINDEX_FIELD piField;
	int nLoop, nLoop1;
	
	pcRecord = piConfig->pcRecord;
	
	printf( "\n\t=== index config info ===\n\n" );
	
	for( nLoop = 0; nLoop < piConfig->nRecCount; nLoop++, pcRecord++ )
	{
		printf( "FILEHEAD:%-6s SYSTYPE:%-3s INDEXTYPE:%-6s TIMELOC:%-3d TIMELEN:%-3d USERLOC:%-3d USERLEN:%-3d RECLEN:%-3d FIELDNUM:%-3d\n", 
														pcRecord->szFileHead, pcRecord->szSysType, pcRecord->szIndexType,
														pcRecord->nTimeLoc, pcRecord->nTimeLen, 
														pcRecord->nUserLoc, pcRecord->nUserLen, 
														pcRecord->nRecLen, pcRecord->nFieldNum );
								
		printf( "Condition  = %s\n", pcRecord->szCondition );
		
		printf( "CleanField = " );
		
		pcField = pcRecord->pcField;

		for( nLoop1 = 0; nLoop1 < pcRecord->nCleanCount; nLoop1++, pcField++ )
		{
			printf( "[ %s, %d, %d ] ", pcField->szFieldName, pcField->nFieldStart, pcField->nFieldLen );
		}

		printf( "\n\n" );
			
		piField = pcRecord->piField;
		
		for( nLoop1 = 0; nLoop1 < pcRecord->nFieldNum; nLoop1++, piField++ )
		{
			printf( "\t%-16s %3d %3d\n", piField->szFieldName, piField->nFieldStart, piField->nFieldLen );
		}
		
		printf( "\n" );
	}
	
	printf( "\t=== index config info ===\n\n" );
	
	return MY_SUCCEED;
}

/********************************************************** 
function: DebugOutDtlFmt
description: 输出详单文件格式
Input:	pfFile: 详单格式信息文件
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutDtlFmt( PFMT_FILE pfFile )
{
	int nLoop;
	PFIELD_FMT pfFmt;
	
	pfFmt = pfFile->pfFmt;

	printf( "\n\t=== Detail Format %s ===\n\n", pfFile->szFileName );
		
	for( nLoop = 0; nLoop < pfFile->nFieldCount; nLoop++, pfFmt++ )
	{
		printf( "[%3d] [%-20s] [%3d] [%3d] [%3d] [%d] [%s]\n",
					pfFmt->nFieldNo, pfFmt->szFieldName, 
					pfFmt->nStart, pfFmt->nEnd, pfFmt->nLen,
					pfFmt->nType, pfFmt->szMapNo );
	}
	
	printf( "\n\t=== Detail Format %s ===\n\n", pfFile->szFileName );
	
	return MY_SUCCEED;	
}

/********************************************************** 
function: DebugOutFmtCtrlInfo
description: 输出详单格式控制信息
Input:	piConfig: 详单格式控制信息
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutFmtCtrlInfo( PFMT_CTRL pfCtrl )
{
	int nLoop;
	PFMT_FILE pfFile;
	
	pfFile = pfCtrl->pfFile;

	printf( "\n\t=== Format Control ===\n\n" );	
	
	for( nLoop = 0; nLoop < pfCtrl->nFmtNum; nLoop++, pfFile++ )
	{
		printf( "[%s] [%s] [%s] [%s]\n",
					pfFile->szSysType, pfFile->szStartTime, 
					pfFile->szEndTime, pfFile->szFileName );
	}
	
	printf( "\n\t=== Format Control ===\n\n" );	
	
	return MY_SUCCEED;	
}

/********************************************************** 
function: GetCtrlInfo
description: 获取索引文件、数据块控制信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetCtrlInfo( PINDEX_DATA piData )
{
	/* 获取 index_control_table 数据 */
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "获取 index_control_table 数据!\n" );
	
	if( MY_SUCCEED != GetIndexCtrlInfo( piData ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取 index_control_table 数据失败!\n" );
		return MY_FAIL;
	}
	
	/* 获取 block_control_table 数据 */
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "获取 block_control_table 数据!\n\n" );
	
	if( MY_SUCCEED != GetBlockCtrlInfo( piData ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取 block_control_table 数据失败!\n" );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetRecFieldCount
description: 获取索引字段配置记录域个数
Input: piData: 描述系统全局结构的结构体
Output:
Return: 记录域个数
others:
***********************************************************/

int GetRecFieldCount( PINDEX_DATA piData )
{
	FILE * fpConfig;
	char szRecord[MAX_RECORD_LEN + 1];
	
	int nRecCount;
	
	nRecCount = 0;
	
	fpConfig = fopen( piData->dCmd.szIndexCfg, "r" );
	if( NULL == fpConfig )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "打开索引字段配置文件 %s 失败!\n", piData->dCmd.szIndexCfg );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return -1;
	}
	
	/* 遍历文件记录 */
	while( NULL != fgets( szRecord, sizeof( szRecord ), fpConfig ) )
	{
		if( 0 == strncmp( szRecord, CFG_REC_FIELD, strlen( CFG_REC_FIELD ) ) )
		{
			nRecCount++;
		}
				
		memset( szRecord, 0, sizeof( szRecord ) );
	}
	
	if( NULL != fpConfig )
	{
		fclose( fpConfig );
		fpConfig = NULL;
	}
	
	return nRecCount;
}

/********************************************************** 
function: GetRecFieldValue
description: 获取索引字段配置记录域内容
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetRecFieldValue( PCONFIG_RECORD pcRecord, char * szRecord )
{
	char * szPos;
	char szField[128];
	int nFieldNum;

	nFieldNum = 0;
	
	szPos = strtok( szRecord, FILE_FIELD_SEP );
	while( NULL != szPos )
	{
		memset( szField, 0, sizeof( szField ) );
		
		strcpy( szField, szPos );
		
		TrimLeft( TrimRight( szField ) );
		
		switch( nFieldNum )
		{
			case 0:		/* 文件头 */
				
				if( 0 != strncmp( szField, "FILEHEAD:", strlen( "FILEHEAD:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "File Head Flag Error!\n" );
					return MY_FAIL;
				}
				
				strcpy( pcRecord->szFileHead, szField + strlen( "FILEHEAD:" ) );
				TrimLeft( TrimRight( pcRecord->szFileHead ) );
				
				break;
				
			case 1:		/* 系统类型 */
			
				if( 0 != strncmp( szField, "SYSTYPE:", strlen( "SYSTYPE:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "Sys Type Flag Error!\n" );
					return MY_FAIL;
				}
				
				strcpy( pcRecord->szSysType, szField + strlen( "SYSTYPE:" ) );
				TrimLeft( TrimRight( pcRecord->szSysType ) );
				
				break;
				
			case 2:		/* 索引文件类型 */
		
				if( 0 != strncmp( szField, "INDEXTYPE:", strlen( "INDEXTYPE:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "Index Type Flag Error!\n" );
					return MY_FAIL;
				}
				
				strcpy( pcRecord->szIndexType, szField + strlen( "INDEXTYPE:" ) );
				TrimLeft( TrimRight( pcRecord->szIndexType ) );
				
				break;
				
			case 3:		/* 时间字段偏移 */
				
				if( 0 != strncmp( szField, "TIMELOC:", strlen( "TIMELOC:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "Time Loc Flag Error!\n" );
					return MY_FAIL;
				}
				
				pcRecord->nTimeLoc = atoi( szField + strlen( "TIMELOC:" ) );
				
				break;
			
			case 4:		/* 时间字段长度 */
				
				if( 0 != strncmp( szField, "TIMELEN:", strlen( "TIMELEN:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "Time Len Flag Error!\n" );
					return MY_FAIL;
				}
				
				pcRecord->nTimeLen = atoi( szField + strlen( "TIMELEN:" ) );
				
				break;
			
			case 5:		/* 用户字段偏移 */
				
				if( 0 != strncmp( szField, "USERLOC:", strlen( "USERLOC:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "User Loc Flag Error!\n" );
					return MY_FAIL;
				}
				
				pcRecord->nUserLoc = atoi( szField + strlen( "USERLOC:" ) );
				
				break;
			
			case 6:		/* 用户字段长度 */
				
				if( 0 != strncmp( szField, "USERLEN:", strlen( "USERLEN:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "User Len Flag Error!\n" );
					return MY_FAIL;
				}
				
				pcRecord->nUserLen = atoi( szField + strlen( "USERLEN:" ) );
				
				break;
						
			case 7:		/* 记录长度 */
				
				if( 0 != strncmp( szField, "RECLEN:", strlen( "RECLEN:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "Rec Len Flag Error!\n" );
					return MY_FAIL;
				}
				
				pcRecord->nRecLen = atoi( szField + strlen( "RECLEN:" ) );
				
				break;
				
			case 8:		/* 索引字段数目 */
				
				if( 0 != strncmp( szField, "FIELDNUM:", strlen( "FIELDNUM:" ) ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "Field Num Flag Error!\n" );
					return MY_FAIL;
				}
				
				pcRecord->nFieldNum = atoi( szField + strlen( "FIELDNUM:" ) );
				
				break;
				
			default:	/* 无效字段 */
				
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "记录域字段数超出定义值!\n" );
				return MY_FAIL;
		}
			
		nFieldNum++;
		szPos = strtok( NULL, FILE_FIELD_SEP );
	}
	
	/* 字段数不足 */
	if( 9 != nFieldNum )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "记录域字段数不足!\n" );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetFieldInfo
description: 获取字段位置信息
Input: piData: 描述系统全局数据的结构体
	   pcRecord: 索引字段配置信息
	   pcField: 字段配置信息
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetFieldInfo( PINDEX_DATA piData, PCONFIG_RECORD pcRecord, PCLEAN_FIELD pcField )
{
	PFMT_CTRL pfCtrl;
	PFMT_FILE pfFile;
	PFIELD_FMT pfFmt;
	int nLoop;
	
	pfCtrl = &(piData->fCtrl);
	pfFile = pfCtrl->pfFile;

	for( nLoop = 0; nLoop < pfCtrl->nFmtNum; nLoop++, pfFile++ )
	{
		if( 0 == strcmp( pcRecord->szSysType, pfFile->szSysType ) )
		{
			pcRecord->pfFile = pfFile;
			break;
		}
	}
	
	if( nLoop >= pfCtrl->nFmtNum )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "没有匹配详单格式信息文件!\n" );
		return MY_FAIL;
	}
	
	pfFmt = pfFile->pfFmt;
	
	for( nLoop = 0; nLoop < pfFile->nFieldCount; nLoop++, pfFmt++ )
	{
		if( 0 == strcasecmp( pcField->szFieldName, pfFmt->szFieldName ) )
		{
			if( pfFmt->nLen > MAX_FIELD_LEN )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "详单字段长度 [%d] 超过最大值!\n", pfFmt->nLen );
				return MY_FAIL;
			}
			
			pcField->nFieldStart = pfFmt->nStart;
			pcField->nFieldLen   = pfFmt->nLen;

			return MY_SUCCEED;
		}
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetCleanField
description: 获取清空字段组合
Input: piData: 描述系统全局数据的结构体
	   pcRecord: 索引字段配置信息
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetCleanField( PINDEX_DATA piData, PCONFIG_RECORD pcRecord )
{
	PCLEAN_FIELD pcField;
	char szRecord[MAX_RECORD_LEN + 1];
	char * szPos;
	int nCount;
	
	nCount = 0;
	pcRecord->nCleanCount = 0;
	
	if( 0 == *(pcRecord->szCleanFields) )
	{
		return MY_SUCCEED;
	}
	
	memset( szRecord, 0, sizeof( szRecord ) );
	strcpy( szRecord, pcRecord->szCleanFields );
	
	szPos = strtok( szRecord, FILE_FIELD_SEP );
	while( NULL != szPos )
	{
		nCount++;
		szPos = strtok( NULL, FILE_FIELD_SEP );
	}
	
	pcRecord->nCleanCount = nCount;
	
	pcRecord->pcField = ( PCLEAN_FIELD ) malloc( pcRecord->nCleanCount * sizeof( CLEAN_FIELD ) );
	if( NULL == pcRecord->pcField )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "申请保存清空域的内存空间失败!\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	memset( pcRecord->pcField, 0, sizeof( pcRecord->nCleanCount * sizeof( CLEAN_FIELD ) ) );
	
	pcField = pcRecord->pcField;
	
	memset( szRecord, 0, sizeof( szRecord ) );
	strcpy( szRecord, pcRecord->szCleanFields );
	
	szPos = strtok( szRecord, FILE_FIELD_SEP );
	while( NULL != szPos )
	{
		nCount--;
		
		if( 0 > nCount )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "清空域空间溢出!\n" );
			return MY_FAIL;
		}
		
		memset( pcField->szFieldName, 0, sizeof( pcField->szFieldName ) );
		strcpy( pcField->szFieldName, szPos );
		TrimLeft( TrimRight( pcField->szFieldName ) );

		if( MY_SUCCEED != GetFieldInfo( piData, pcRecord, pcField ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "字段 [%s] 未定义!\n", pcField->szFieldName );
			return MY_FAIL;
		}
		
		pcField++;
		
		szPos = strtok( NULL, FILE_FIELD_SEP );
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetIndFieldValue
description: 获取索引字段配置索引域内容
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetIndFieldValue( PCONFIG_RECORD pcRecord, char * szRecord, int nLoc )
{
	PINDEX_FIELD piField;
	char * szPos;
	char szField[128];
	int nFieldNum;

	piField = pcRecord->piField + nLoc;
	
	nFieldNum = 0;
	
	szPos = strtok( szRecord, FILE_FIELD_SEP );
	while( NULL != szPos )
	{
		switch( nFieldNum )
		{
			case 0:		/* 字段名 */
				
				strcpy( piField->szFieldName, szPos );
				break;
				
			case 1:		/* 字段开始位置 */
				
				piField->nFieldStart = atoi( szPos );
				break;
				
			case 2:		/* 字段长度 */
				
				piField->nFieldLen = atoi( szPos );
				break;
				
			default:	/* 无效字段 */
				
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引域记录字段数超出定义值!\n" );
				return MY_FAIL;
		}
			
		nFieldNum++;
		szPos = strtok( NULL, FILE_FIELD_SEP );	
	}
	
	/* 字段数不足 */
	if( 3 != nFieldNum )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引域记录字段数不足!\n" );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetIndexFieldConfig
description: 获取索引字段配置信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetIndexFieldConfig( PINDEX_DATA piData )
{
	PINDEX_CONFIG piConfig;
	PCONFIG_RECORD pcRecord;
	
	FILE * fpConfig;
	
	char szRecord[MAX_RECORD_LEN + 1];
	
	char bRecField;
	char bConField;
	char bIndField;
	
	int nRecField;
	int nFieldNum;
	
	bRecField = MY_FALSE;
	bConField = MY_FALSE;
	bIndField = MY_FALSE;
	nRecField = 0;
	nFieldNum = 0;
	
	piConfig = &(piData->iConfig);
	
	/* 获取记录域个数 */
	piConfig->nRecCount = GetRecFieldCount( piData );
	if( 0 >= piConfig->nRecCount )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引字段配置文件中没有有效的记录域!\n" );
		return MY_FAIL;
	}

	/* 申请保存配置信息的内存空间 */
	piConfig->pcRecord = ( PCONFIG_RECORD ) malloc( piConfig->nRecCount * sizeof( CONFIG_RECORD ) );
	if( NULL == piConfig->pcRecord )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "申请保存索引字段配置文件记录域的内存空间失败!\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	memset( piConfig->pcRecord, 0, piConfig->nRecCount * sizeof( CONFIG_RECORD ) );
	
	pcRecord = piConfig->pcRecord;
	
	/* 打开配置文件 */
	fpConfig = fopen( piData->dCmd.szIndexCfg, "r" );
	if( NULL == fpConfig )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "打开索引字段配置文件失败!\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	memset( szRecord, 0, sizeof( szRecord ) );
	
	/* 遍历配置文件 */
	while( NULL != fgets( szRecord, sizeof( szRecord ), fpConfig ) )
	{
		if( !IsRecordLine( szRecord ) )
		{
			memset( szRecord, 0, sizeof( szRecord ) );
			continue;
		}

		/* 记录域配置记录 */
		if( 0 == strncmp( szRecord, CFG_REC_FIELD, strlen( CFG_REC_FIELD ) ) )
		{
			if( bRecField )
			{
				if( nFieldNum != pcRecord->nFieldNum )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%s] 索引字段数 %d 与配置 %d 不符!\n", pcRecord->szFileHead, nFieldNum, pcRecord->nFieldNum );
					return MY_FAIL;
				}
				
				pcRecord++;
			}
			
			bRecField = MY_TRUE;
			nFieldNum = 0;
			nRecField++;
			
			/* 校验记录域个数 */
			if( nRecField > piConfig->nRecCount )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "记录域数 %d 与预定义 %d 不符!\n", nRecField, piConfig->nRecCount );
				return MY_FAIL;
			}
			
			/* 获取记录域各项配置内容 */
			if( MY_SUCCEED != GetRecFieldValue( pcRecord, szRecord + strlen( CFG_REC_FIELD ) ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%d] 索引字段配置文件记录域格式错误!\n", nRecField );
				return MY_FAIL;
			}
			
			/* 申请保存索引字段的内存空间 */
			pcRecord->piField = ( PINDEX_FIELD ) malloc( pcRecord->nFieldNum * sizeof( INDEX_DATA ) );
			if( NULL == pcRecord->piField )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%d] 申请保存索引字段信息的内存空间失败!\n", nRecField );
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
				return MY_FAIL;
			}
			
			memset( pcRecord->piField, 0, pcRecord->nFieldNum * sizeof( INDEX_DATA ) );
			
			continue;
		}
		
		if( bRecField )
		{
			/* 条件域 */
			if( 0 == strncmp( szRecord, CFG_CON_FIELD, strlen( CFG_CON_FIELD ) ) )
			{
				memset( pcRecord->szCondition, 0, sizeof( pcRecord->szCondition ) );
				
				strcpy( pcRecord->szCondition, szRecord + strlen( CFG_CON_FIELD ) );
				TrimLeft( TrimRight( pcRecord->szCondition ) );
				
				if( MY_SUCCEED != RebuildCondExpr( piData, pcRecord ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%d] 定义的条件表达式 [%s] 格式错误!\n", nRecField, pcRecord->szCondition );
					return MY_FAIL;
				}
				
				/* printf( "%s\n%s\n", pcRecord->szCondition, pcRecord->szLogicExpr ); */

				continue;
			}
			
			/* 清空域 */
			if( 0 == strncmp( szRecord, CFG_CLN_FIELD, strlen( CFG_CLN_FIELD ) ) )
			{
				memset( pcRecord->szCleanFields, 0, sizeof( pcRecord->szCleanFields ) );
				
				strcpy( pcRecord->szCleanFields, szRecord + strlen( CFG_CLN_FIELD ) );
				TrimLeft( TrimRight( pcRecord->szCleanFields ) );
				
				if( MY_SUCCEED != GetCleanField( piData, pcRecord ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%d] 定义的清空域 [%s] 格式错误!\n", nRecField, pcRecord->szCleanFields );
					return MY_FAIL;
				}
				
				continue;
			}
			
			/* 索引域 */
			if( 0 == strncmp( szRecord, CFG_IND_FIELD, strlen( CFG_IND_FIELD ) ) )
			{
				continue;
			}

			nFieldNum++;
			
			/* 记录域定义索引字段数与索引域定义数不符 */
			if( nFieldNum > pcRecord->nFieldNum )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%d] 定义的索引字段 [%d] 超出配置值 [%d] !\n", nRecField, nFieldNum, pcRecord->nFieldNum );
				return MY_FAIL;
			}
			
			/* 获取索引字段配置信息 */
			if( MY_SUCCEED != GetIndFieldValue( pcRecord, szRecord, nFieldNum - 1 ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%d] [%d] 索引字段配置文件索引域格式错误!\n", nRecField, nFieldNum );
				return MY_FAIL;
			}
		}
		
		memset( szRecord, 0, sizeof( szRecord ) );
	}
	
	/* 关闭配置文件 */
	if( NULL != fpConfig )
	{
		fclose( fpConfig );
		fpConfig = NULL;
	}
	
	/* DebugOutIndexFieldConfig( piConfig ); */
	
	return MY_SUCCEED;
}

int CtrlCmp( PFMT_FILE pfFile1, PFMT_FILE pfFile2 )
{
	char szKey1[SYS_TYPE_LEN + 14 + 14 + 1];
	char szKey2[SYS_TYPE_LEN + 14 + 14 + 1];
	
	sprintf( szKey1, "%s%s%s", pfFile1->szSysType, pfFile1->szStartTime, pfFile1->szEndTime );
	sprintf( szKey2, "%s%s%s", pfFile2->szSysType, pfFile2->szStartTime, pfFile2->szEndTime );
	
	return ( strcmp( szKey1, szKey2 ) );
}

/********************************************************** 
function: GetDetailFmt
description: 获取详单格式文件信息
Input: pfFile: 详单格式文件
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetDetailFmt( PFMT_FILE pfFile )
{
	PFIELD_FMT pfFmt;
	FILE * fpFmt;
	char szRecord[MAX_RECORD_LEN + 1];
	char * szPos;
	int nFieldNum;
	
	pfFmt = pfFile->pfFmt;

	pfFile->nFieldCount = GetFileCount( pfFile->szFileName );
	if( 0 >= pfFile->nFieldCount )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "详单格式描述文件 %s 内容为空\n", pfFile->szFileName );
		return MY_FAIL;
	}

	pfFile->pfFmt = ( PFIELD_FMT ) malloc( ( pfFile->nFieldCount ) * sizeof(FIELD_FMT) );
	if( NULL == pfFile->pfFmt  )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "申请保存详单格式描述文件内容的内存空间失败\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	memset( pfFile->pfFmt , 0, ( pfFile->nFieldCount ) * sizeof(FIELD_FMT) );
	
	fpFmt = fopen( pfFile->szFileName, "r" );
	if( NULL == fpFmt )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "详单格式描述文件 %s 打开失败\n", pfFile->szFileName );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}

	szPos = NULL;
	pfFmt = pfFile->pfFmt;
	pfFile->nFieldCount = 0;

	memset( szRecord, 0, sizeof( szRecord ) );
		
	while( NULL != fgets( szRecord, sizeof( szRecord ), fpFmt ) )
	{
		if( !IsRecordLine( szRecord ) )
		{
			memset( szRecord, 0, sizeof( szRecord ) );
			continue;
		}
		
		nFieldNum = 0;
		memset( pfFmt, 0, sizeof( FIELD_FMT ) );
		
		szPos = strtok( szRecord, FILE_FIELD_SEP );
		while( NULL != szPos )
		{
			switch( nFieldNum )
			{
				case 0:		/* 字段编号 */
				
					pfFmt->nFieldNo = atoi( szPos );
					break;
					
				case 1:		/* 字段名 */
				
					strcpy( pfFmt->szFieldName, szPos );
					break;
					
				case 2:		/* 字段开始位置 */
				
					pfFmt->nStart = atoi( szPos );
					break;
				
				case 3:		/* 字段结束位 */
					
					pfFmt->nEnd = atoi( szPos );
					break;
					
				case 4:		/* 字段长度 */
				
					pfFmt->nLen = atoi( szPos );
					break;
					
				case 5:		/* 字段类型 */
				
					pfFmt->nType = atoi( szPos );
					break;
					
				case 6:		/* 映射文件编号 */
				
					strcpy( pfFmt->szMapNo, szPos );
					if( 0 != strncmp( pfFmt->szMapNo, FIELD_NO_MAP, strlen( FIELD_NO_MAP ) )
					&&  !IsNum( pfFmt->szMapNo ) )
					{
						MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "错误的映射文件编号 [%s]\n", pfFmt->szMapNo );
						fclose( fpFmt );
						return MY_FAIL;
					}	
					break;
			}
			
			nFieldNum++;
			szPos = strtok( NULL, FILE_FIELD_SEP );
		}
		
		if( 7 != nFieldNum )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "详单格式描述文件记录格式错误\n" );
			fclose( fpFmt );
			return MY_FAIL;
		}
	
		pfFmt++;		
		pfFile->nFieldCount++;
		
		memset( szRecord, 0, sizeof( szRecord ) );
	}

	fclose( fpFmt );
	
	/* DebugOutDtlFmt( pfFile ); */
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetFmtCtrlInfo
description: 获取详单格式控制信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetFmtCtrlInfo( PINDEX_DATA piData )
{
	PFMT_CTRL pfCtrl;
	PFMT_FILE pfFile;
	char szRecord[MAX_RECORD_LEN + 1];
	char * szPos;
	FILE * fpCtrl;
	
	int nFieldNum;
	
	pfCtrl = &(piData->fCtrl);
	
	/* 获取详单格式文件数目 */
	pfCtrl->nFmtNum = GetFileCount( piData->dCmd.szFmtCtrl );
	if( 0 >= pfCtrl->nFmtNum )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "详单格式控制文件 %s 内容为空\n", piData->dCmd.szFmtCtrl );
		return MY_FAIL;
	}

	/* 申请保存详单格式信息的内存空间 */
	pfCtrl->pfFile = ( PFMT_FILE ) malloc( ( pfCtrl->nFmtNum ) * sizeof(FMT_FILE) );
	if( NULL == pfCtrl->pfFile  )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "申请保存详单格式控制文件的内存空间失败!\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	memset( pfCtrl->pfFile, 0, ( pfCtrl->nFmtNum ) * sizeof(FMT_FILE) );
	
	fpCtrl = fopen( piData->dCmd.szFmtCtrl, "r" );
	if( NULL == fpCtrl )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "打开详单格式控制文件 %s 失败!\n", piData->dCmd.szFmtCtrl );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}

	szPos = NULL;
	pfFile = pfCtrl->pfFile;
	pfCtrl->nFmtNum = 0;

	memset( szRecord, 0, sizeof( szRecord ) );
		
	while( NULL != fgets( szRecord, sizeof( szRecord ), fpCtrl ) )
	{
		if( !IsRecordLine( szRecord ) )
		{
			memset( szRecord, 0, sizeof( szRecord ) );
			continue;
		}
		
		nFieldNum = 0;

		memset( pfFile, 0, sizeof( FMT_FILE ) );
		
		szPos = strtok( szRecord, FILE_FIELD_SEP );
		while( NULL != szPos )
		{
			switch( nFieldNum )
			{
				case 0:		/* 文件头 */
					
					strcpy( pfFile->szFileHead, szPos );
					break;
					
				case 1:		/* 系统代码 */
				
					strcpy( pfFile->szSysType, szPos );
					break;
					
				case 2:		/* 开始生效时间 */
				
					strcpy( pfFile->szStartTime, szPos );
					break;
					
				case 3:		/* 结束生效时间 */
				
					strcpy( pfFile->szEndTime, szPos );
					break;
					
				case 4:		/* 详单格式文件 */
				
					strcpy( pfFile->szFileName, szPos );
					break;
			}
			
			nFieldNum++;
			szPos = strtok( NULL, FILE_FIELD_SEP );
		}
		
		if( 5 != nFieldNum )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "详单格式控制文件记录格式错误\n" );
			fclose( fpCtrl );
			return MY_FAIL;
		}

		if( GetDetailFmt( pfFile ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "详单格式控制文件内容错误\n" );
			fclose( fpCtrl );
			return MY_FAIL;
		}
		
		pfFile++;		
		pfCtrl->nFmtNum++;
		
		memset( szRecord, 0, sizeof( szRecord ) );
	}

	fclose( fpCtrl );
	
	qsort( pfCtrl->pfFile, pfCtrl->nFmtNum, sizeof( FMT_FILE ), (int (*) (const void *,const void *))CtrlCmp );
	
	/* DebugOutFmtCtrlInfo( pfCtrl ); */
	
	return MY_SUCCEED;	
}

/********************************************************** 
function: GetConfigInfo
description: 获取系统运行配置信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetConfigInfo( PINDEX_DATA piData )
{
	/* 初始化系统变量 */
	piData->pcRecord  = NULL;
	piData->picRecord = NULL;
	piData->pbcRecord = NULL;
	
	piData->nProcHandle  = -1;
	piData->nErrHandle   = -1;
	piData->nDupHandle   = -1;
	piData->nBreakHandle = -1;
	
	piData->fpIndex  = NULL;
	piData->fpTmpOut = NULL;
	piData->fpDup    = NULL;
	
	piData->szBlock = NULL;
	
	piData->lBlockSize = 0;
	
	piData->bSameIndexFile = MY_FALSE;
	piData->bDupRecord     = MY_FALSE;
	piData->bRollback      = MY_FALSE;
	
	memset( piData->szIndexFile, 0, sizeof( piData->szIndexFile ) );
	
	/* 获取索引文件控制信息 */
	if( MY_SUCCEED != GetCtrlInfo( piData ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引文件控制信息失败!\n" );
		return MY_FAIL;
	}
	
	/* 获取详单格式控制信息 */
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "获取详单格式控制信息!\n" );
	if( MY_SUCCEED != GetFmtCtrlInfo( piData ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取详单格式控制信息失败!\n" );
		return MY_FAIL;
	}
	
	/* 获取索引字段配置信息 */
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "获取索引字段配置信息!\n\n" );
	if( MY_SUCCEED != GetIndexFieldConfig( piData ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引字段配置信息失败!\n" );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: FreeCtrlData
description: 释放索引控制信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int FreeCtrlData( PINDEX_DATA piData )
{
	if( NULL != piData->icData.picRecord )
	{
		free( piData->icData.picRecord );
		piData->icData.picRecord = NULL;
	}
	
	if( NULL != piData->bcData.pbcRecord )
	{
		free( piData->bcData.pbcRecord );
		piData->bcData.pbcRecord = NULL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: FreeMemoryData
description: 释放系统运行申请的内存空间
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int FreeMemoryData( PINDEX_DATA piData )
{
	PCONFIG_RECORD pcRecord;
	int nLoop;
	
	pcRecord = piData->iConfig.pcRecord;
	
	for( nLoop = 0; nLoop < piData->iConfig.nRecCount; nLoop++, pcRecord++ )
	{
		if( NULL != pcRecord->piField )
		{
			free( pcRecord->piField );
			pcRecord->piField = NULL;
		}
	}
	
	if( NULL != piData->iConfig.pcRecord )
	{
		free( piData->iConfig.pcRecord );
		piData->iConfig.pcRecord = NULL;
	}

	if( NULL != piData->szBlock )
	{
		free( piData->szBlock );
		piData->szBlock = NULL;
	}
	
	FreeCtrlData( piData );
	
	/* 关闭索引文件指针 */
	if( NULL != piData->fpIndex )
	{
		fclose( piData->fpIndex );
		piData->fpIndex = NULL;
	}
	
	/* 关闭出口临时文件指针 */
	if( NULL != piData->fpTmpOut )
	{
		fclose( piData->fpTmpOut );
		piData->fpTmpOut = NULL;
	}
	
	/* 关闭处理日志 */
	if( -1 != piData->nProcHandle )
	{
		close( piData->nProcHandle );
		piData->nProcHandle = -1;
	}
	
	/* 关闭错单日志 */
	if( -1 != piData->nErrHandle )
	{
		close( piData->nErrHandle );
		piData->nErrHandle = -1;
	}
	
	/* 关闭重单日志 */
	if( -1 != piData->nDupHandle )
	{
		close( piData->nDupHandle );
		piData->nDupHandle = -1;
	}
	
	/* 关闭重单文件 */
	if( NULL != piData->fpDup )
	{
		fclose( piData->fpDup );
		piData->fpDup = NULL;
	}
	
	if( -1 != piData->nBreakHandle )
	{
		close( piData->nBreakHandle );
		piData->nBreakHandle = -1;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetCurrBatch
description: 获取系统当前所处批次
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetCurrBatch( PINDEX_DATA piData )
{
	struct tm * tmTime;
	
	tmTime = localtime( &tmStartTime );
	
	memset( piData->szCurrBatch, 0, sizeof( piData->szCurrBatch ) );
	
	sprintf( piData->szCurrBatch, "%04d%02d%02d%02d%02d%02d", 
						tmTime->tm_year + 1900,	tmTime->tm_mon + 1,	tmTime->tm_mday,
						tmTime->tm_hour, tmTime->tm_min,	tmTime->tm_sec );

	return MY_SUCCEED;
}

/********************************************************** 
function: OpenLogFile
description: 打开系统当前批次的处理日志、错单日志
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int OpenLogFile( PINDEX_DATA piData )
{
	char szFilePath[MAX_PATH_LEN + 1];
	
	/* 关闭上次打开的, 打开当前的文件 */
	/*
	if( -1 != piData->nProcHandle )
	{
		close( piData->nProcHandle );
		piData->nProcHandle = -1;
	}
	*/

	memset( szFilePath, 0, sizeof( szFilePath ) );

	/* CUT BY Zhangf 2005-01-25
	sprintf( szFilePath, "%s/log%2.2s/dtc%8.8s.%s.log", (piData->dCmd).szProcLog, piData->szCurrBatch + 6, piData->szCurrBatch + 4, szSrcDir );
	*/
	/* ADD BY Zhangf 2005-01-25 BEGIN */
	/*
	sprintf( szFilePath, "%s/log%2.2s/d%s%8.8s.log", (piData->dCmd).szProcLog, piData->szCurrBatch + 6, szSrcDir, piData->szCurrBatch + 4 );
	*/
	/* ADD BY Zhangf 2005-01-25 END */
	sprintf( szFilePath, "%s/d.%s.log", (piData->dCmd).szLogTmp, szSrcDir ) ;
		
	piData->nProcHandle = open( szFilePath, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH );
	if( -1 == piData->nProcHandle )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "处理日志 %s 打开失败\n", szFilePath );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	/* 关闭上次打开的, 打开当前的文件 */
	/*
	if( -1 != piData->nErrHandle )
	{
		close( piData->nErrHandle );
		piData->nErrHandle = -1;
	}
	*/

	memset( szFilePath, 0, sizeof( szFilePath ) );

	/* CUT BY Zhangf 2005-01-25
	sprintf( szFilePath, "%s/log%2.2s/dtc%8.8s.%s.err", (piData->dCmd).szProcLog, piData->szCurrBatch + 6, piData->szCurrBatch + 4, szSrcDir );
	*/
	/* ADD BY Zhangf 2005-01-25 BEGIN */
	/*
	sprintf( szFilePath, "%s/log%2.2s/d%s%8.8s.err", (piData->dCmd).szProcLog, piData->szCurrBatch + 6, szSrcDir, piData->szCurrBatch + 4 );
	*/
	/* ADD BY Zhangf 2005-01-25 END */
	sprintf( szFilePath, "%s/d.%s.err", (piData->dCmd).szLogTmp, szSrcDir );
		
	piData->nErrHandle = open( szFilePath, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH );
	if( -1 == piData->nErrHandle )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "错单日志 %s 打开失败\n", szFilePath );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: WriteProcLog
description: 写处理日志
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int WriteProcLog( PINDEX_DATA piData )
{
	char szLogInfo[MAX_RECORD_LEN + 1];
	char szSysType[SYS_TYPE_LEN + 1];
	
	memset( szLogInfo, 0, sizeof( szLogInfo ) );
	bzero( szSysType, sizeof( szSysType ) ) ;

	strncpy( szSysType, piData->szFileName+1, 2 ) ;
	sprintf( szLogInfo, "%s:%s:%s:%s:T %ld:A %ld:E %ld:D %ld\n", 
					piData->szFileName, szSysType, piData->szStartTime, piData->szEndTime,
					piData->lTotalRec, piData->lAvailRec, piData->lErrorRec, piData->lDupRec );
					
	if( strlen( szLogInfo ) != write( piData->nProcHandle, szLogInfo, strlen( szLogInfo ) ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "处理日志写失败\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: WriteErrRecord
description: 写错单日志
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int WriteErrRecord( PINDEX_DATA piData )
{
	char szErrorInfo[MAX_RECORD_LEN + 1];
	
	if( piData->nRecordLen != strlen( piData->szRecord ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "话单记录内容变化[ %d - %d ]!\n", piData->nRecordLen, strlen( piData->szRecord ) );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%s]!\n", piData->szRecord );
		return MY_FAIL;
	}
	
	memset( szErrorInfo, 0, sizeof( szErrorInfo ) );
	
	sprintf( szErrorInfo, "%s:%s:%s", piData->szFileName, piData->szErrCode, piData->szRecord );
	
	if( strlen( szErrorInfo ) != write( piData->nErrHandle, szErrorInfo, strlen( szErrorInfo ) ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "错单文件写失败!\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	piData->lErrorRec++;
	
	return MY_SUCCEED;
}

/********************************************************** 
function: WriteDupFile(
description: 写重单日志
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int WriteDupFile( PINDEX_DATA piData )
{
	char szFilePath[MAX_PATH_LEN + 1];
	char szRecord[MAX_RECORD_LEN + 1];
	
	/* 打开当前文件*/
	if( -1 == piData->nDupHandle )
	{
		memset( szFilePath, 0, sizeof( szFilePath ) );
		
		sprintf( szFilePath, "%s/%s.dup", piData->dCmd.szLogTmp, piData->szFileName );
		
		piData->nDupHandle = open( szFilePath, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH );
		if( -1 == piData->nDupHandle )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "重单文件 %s 打开失败\n", szFilePath );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
	}
	
	if( piData->nRecordLen != strlen( piData->szRecord ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "话单记录内容变化[ %d - %d ]!\n", piData->nRecordLen, strlen( piData->szRecord ) );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%s]!\n", piData->szRecord );
		return MY_FAIL;
	}
	
	memset( szRecord, 0, sizeof( szRecord ) );
	
	sprintf( szRecord, "%ld:%s", piData->lTotalRec, piData->szRecord );
	
	/* 写重单日志 */
	if( strlen( szRecord ) != write( piData->nDupHandle, szRecord, strlen( szRecord ) ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "重单文件写失败\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	piData->lDupRec++;
	
	return MY_SUCCEED;
}

/********************************************************** 
function: OpenTmpOutFile(
description: 打开出口临时文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int OpenTmpOutFile( PINDEX_DATA piData )
{
	char szFilePath[MAX_PATH_LEN + 1];

	/* 打开当前文件*/
	if( NULL == piData->fpTmpOut )
	{
		memset( szFilePath, 0, sizeof( szFilePath ) );
		
		sprintf( szFilePath, "%s/%s.tmp", piData->dCmd.szTmpDir, piData->szFileName );
		
		piData->fpTmpOut = fopen( szFilePath, "w" );
		if( NULL == piData->fpTmpOut  )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "出口临时文件 %s 打开失败\n", szFilePath );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
	}
	
	return MY_SUCCEED;
}


/********************************************************** 
function: WriteTmpOutFile
description: 写出口临时文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int WriteTmpOutFile( PINDEX_DATA piData )
{
	if( piData->nRecordLen != strlen( piData->szRecord ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "话单记录内容变化[ %d - %d ]!\n", piData->nRecordLen, strlen( piData->szRecord ) );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%s]!\n", piData->szRecord );
		return MY_FAIL;
	}
	
	/* 写临时出口文件 */
	if( strlen( piData->szRecord ) != fwrite( piData->szRecord, sizeof( char ), strlen( piData->szRecord ), piData->fpTmpOut ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "出口临时文件写失败\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	piData->lAvailRec++;
	
	return MY_SUCCEED;
}

/********************************************************** 
function: DeleteBreakLog
description: 删除断点日志文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int DeleteBreakLog( PINDEX_DATA piData )
{
	char szBreakFile[MAX_PATH_LEN + 1];
	
	memset( szBreakFile, 0, sizeof( szBreakFile ) );
	sprintf( szBreakFile, "%s/%s%s%s", (piData->dCmd).szLogTmp, BREAK_LOG_HEAD, piData->szFileName, BREAK_END_TAIL );
	
	if( 0 != remove( szBreakFile ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "删除断点日志文件 %s 失败\n", szBreakFile );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: UpdateBreakFile
description: 更新断点记录
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int UpdateBreakFile( PINDEX_DATA piData )
{
	char szBreakRecord[MAX_RECORD_LEN + 1];
	
	/* if( 6 == piData->lTotalRec ) exit(0); */
	
	if( piData->bRollback )
	{
		return MY_SUCCEED;
	}

	if( -1 == lseek( piData->nBreakHandle, 0, SEEK_SET ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "定位断点记录位置失败!\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}

	memset( szBreakRecord, 0, sizeof( szBreakRecord ) );
/*	
	sprintf( szBreakRecord, "%ld%c%s%c%s%c", piData->lTotalRec, BREAK_FIELD_SEP, piData->szErrCode, BREAK_FIELD_SEP, piData->szRecord, BREAK_FIELD_SEP );
*/
	sprintf( szBreakRecord, "%ld%s%s%s", piData->lTotalRec, BREAK_FIELD_SEP, piData->szErrCode, BREAK_FIELD_SEP );

	if( strlen( szBreakRecord ) != write( piData->nBreakHandle, szBreakRecord, strlen( szBreakRecord ) ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "断点记录更新失败\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: CreateBreakFile
description: 创建断点日志文件
Input: piData: 描述系统全局结构的结构体
	   nState: 断点状态
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int CreateBreakFile( PINDEX_DATA piData, int nState )
{
	char szSrcFile[MAX_PATH_LEN + 1];
	char szDstFile[MAX_PATH_LEN + 1];
	FILE * fpBreak;
	
	memset( szSrcFile, 0, sizeof( szSrcFile ) );
	memset( szDstFile, 0, sizeof( szDstFile ) );

	switch( nState )
	{
		case BREAK_STATE_START:	/* 开始处理文件 */
			
			sprintf( szSrcFile, "%s/%s%s%s", (piData->dCmd).szLogTmp, BREAK_LOG_HEAD, piData->szFileName, BREAK_START_TAIL );

			piData->nBreakHandle = open( szSrcFile, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH );
			if( -1 == piData->nBreakHandle )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "生成开始状态断点文件 %s 失败\n", szSrcFile );
				return MY_FAIL;
			}
			
			break;
			
		case BREAK_STATE_TMP:	/* 已关闭索引文件、临时文件, 临时文件已移至出口目录 */
			
			sprintf( szSrcFile, "%s/%s%s%s", (piData->dCmd).szLogTmp, BREAK_LOG_HEAD, piData->szFileName, BREAK_START_TAIL );
			sprintf( szDstFile, "%s/%s%s%s", (piData->dCmd).szLogTmp, BREAK_LOG_HEAD, piData->szFileName, BREAK_TMP_TAIL );
			
			if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "生成临时状态断点文件 %s 失败\n", szDstFile );
				return MY_FAIL;
			}
			
			break;
		
		case BREAK_STATE_END:	/* 入口文件已移至备份目录 */
			
			sprintf( szSrcFile, "%s/%s%s%s", (piData->dCmd).szLogTmp, BREAK_LOG_HEAD, piData->szFileName, BREAK_TMP_TAIL );
			sprintf( szDstFile, "%s/%s%s%s", (piData->dCmd).szLogTmp, BREAK_LOG_HEAD, piData->szFileName, BREAK_END_TAIL );
			
			if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "生成结束状态断点文件 %s 失败\n", szDstFile );
				return MY_FAIL;
			}
			
			break;
			
		default:				/* 未定义的断点状态 */
			
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "断点状态 %d 无效!\n\n", nState );
			return MY_FAIL;
			
			break;
	}
	
	return MY_SUCCEED;
}


/********************************************************** 
function: MoveAndBakFile
description: 移动出口临时文件、备份入口文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int MoveAndBakFile( PINDEX_DATA piData )
{
	char szSrcFile[MAX_PATH_LEN + 1];
	char szDstFile[MAX_PATH_LEN + 1];
	
	/* 关闭索引文件指针 */
	if( NULL != piData->fpIndex )
	{
		fclose( piData->fpIndex );
		piData->fpIndex = NULL;
	}
	
	memset( piData->szIndexFile, 0, sizeof( piData->szIndexFile ) );
	
	/* 关闭出口临时文件指针 */
	if( NULL != piData->fpTmpOut )
	{
		fclose( piData->fpTmpOut );
		piData->fpTmpOut = NULL;
	}
	
	/* 关闭重单文件指针 */
	if( -1 != piData->nDupHandle )
	{
		close( piData->nDupHandle );
		piData->nDupHandle = -1;
	}
	
	/* 关闭断点文件指针 */
	if( -1 != piData->nBreakHandle )
	{
		close( piData->nBreakHandle );
		piData->nBreakHandle = -1;
	}
	
	/* 出口临时文件移入正式出口目录 */
	memset( szSrcFile, 0, sizeof( szSrcFile ) );
	memset( szDstFile, 0, sizeof( szDstFile ) );
	
	sprintf( szSrcFile, "%s/%s.tmp", piData->dCmd.szTmpDir, piData->szFileName );
	sprintf( szDstFile, "%s/%s%s.uni", piData->dCmd.szOutDir, UNI_FILE_HEAD, piData->szFileName + strlen( UNI_FILE_HEAD ) );
	
	if( 0 == piData->lAvailRec )
	{
		if( 0 != remove( szSrcFile ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "删除出口临时文件 %s 失败\n", szSrcFile );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
	}
	else
	{
		if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "移动出口临时文件失败\n" );
			return MY_FAIL;
		}
	}
	
	if( MY_SUCCEED != CreateBreakFile( piData, BREAK_STATE_TMP ) )
	{
		return MY_FAIL;
	}
		
	/* 重单日志移入日志目录 */
	if( 0 < piData->lDupRec )
	{

		memset( szSrcFile, 0, sizeof( szSrcFile ) );
		memset( szDstFile, 0, sizeof( szDstFile ) );
	
		sprintf( szSrcFile, "%s/%s.dup", piData->dCmd.szLogTmp, piData->szFileName );
		sprintf( szDstFile, "%s/%s.dup", piData->dCmd.szRunLog, piData->szFileName );
	/*
		if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "移动重单文件失败\n" );
			return MY_FAIL;
		}
	*/
		if( 0 != remove( szSrcFile ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "删除重单临时文件 %s 失败\n", szSrcFile );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
	}
	
	/* 入口文件移入备份目录 */
	memset( szSrcFile, 0, sizeof( szSrcFile ) );
	memset( szDstFile, 0, sizeof( szDstFile ) );
	
	sprintf( szSrcFile, "%s/%s", piData->dCmd.szInDir , piData->szFileName );
	sprintf( szDstFile, "%s/%s", piData->dCmd.szBakDir, piData->szFileName );
	
	if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "备份入口文件失败\n" );
		return MY_FAIL;
	}

	if( MY_SUCCEED != CreateBreakFile( piData, BREAK_STATE_END ) )
	{
		return MY_FAIL;
	}

	/* 删除断点文件 */
	if( MY_SUCCEED != DeleteBreakLog( piData ) )
	{
		return MY_FAIL;
	}
			
	return MY_SUCCEED;
}

/********************************************************** 
function: AlterLogFile
description: 变更系统当前批次的处理日志、错单日志
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int AlterLogFile( PINDEX_DATA piData )
{
	if( MY_SUCCEED != CloseLogFile( piData ) )
	{
		return MY_FAIL;
	}

	if( MY_SUCCEED != MoveLogFile( piData ) )
	{
		return MY_FAIL;
	}

	/* 获取当前批次 */
	GetCurrBatch( piData );

	if( MY_SUCCEED != OpenLogFile( piData ) )
	{
		return MY_FAIL;
	}

	return MY_SUCCEED;
}

/********************************************************** 
function: CloseLogFile
description: 关闭系统当前批次的处理日志、错单日志
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int CloseLogFile( PINDEX_DATA piData )
{
	if( -1 != piData->nProcHandle )
	{
		close( piData->nProcHandle );
		piData->nProcHandle = -1;
	}

	if( -1 != piData->nErrHandle )
	{
		close( piData->nErrHandle );
		piData->nErrHandle = -1;
	}
									
	return MY_SUCCEED;
}


/********************************************************** 
function: MoveLogFile
description: 移动系统当前批次的处理日志、错单日志
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int MoveLogFile( PINDEX_DATA piData )
{
	char szSrcFile[MAX_PATH_LEN + 1];
	char szDstFile[MAX_PATH_LEN + 1];

	memset( szSrcFile, 0, sizeof( szSrcFile ) );
	memset( szDstFile, 0, sizeof( szDstFile ) );

	sprintf( szSrcFile, "%s/d.%s.log", (piData->dCmd).szLogTmp, szSrcDir );
	/*
	sprintf( szDstFile, "%s/log%2.2s/d%8.8s.%s.log", (piData->dCmd).szProcLog, piData->szCurrBatch + 6, piData->szCurrBatch + 4, szSrcDir );
	*/
	sprintf( szDstFile, "%s/log%2.2s/d%8.8s.%s.log", (piData->dCmd).szProcLog, piData->szCurrBatch + 6, piData->szCurrBatch + 4, szSrcDir ) ;

	if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "移动临时日志文件 %s 失败\n", szSrcFile );
		return MY_FAIL;
	}

	memset( szSrcFile, 0, sizeof( szSrcFile ) );
	memset( szDstFile, 0, sizeof( szDstFile ) );

	sprintf( szSrcFile, "%s/d.%s.err", (piData->dCmd).szLogTmp, szSrcDir );
	sprintf( szDstFile, "%s/log%2.2s/d%8.8s.%s.err", (piData->dCmd).szProcLog, piData->szCurrBatch + 6, piData->szCurrBatch + 4, szSrcDir );
	/*
	sprintf( szDstFile, "%s/log%2.2s/d%s%8.8s.err", (piData->dCmd).szProcLog, piData->szCurrBatch + 6, szSrcDir, piData->szCurrBatch + 4 ) ;
	*/

	if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "移动临时错单文件 %s 失败\n", szSrcFile );
		return MY_FAIL;
	}

	return MY_SUCCEED;
}
