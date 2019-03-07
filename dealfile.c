

/********************************************************************
copyright (C), 1995-2004, Si-Tech Information Technology Ltd. 
file_name: dealfile.c  
author: 张凡 version: （V1.00） date: （2004－08－20）
description: 处理文件, 实现剔除重单功能
others:
history: 1.date: 修改时间 version: 版本（V1.00）author: 作者
			modification: 修改内容
		 2. ... 
********************************************************************/


#include "ddef.h"


/********************************************************** 
function: GetIndexName
description: 获取索引文件名
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetIndexName( PINDEX_DATA piData )
{
	PICTRL_RECORD picRecord;
	
	picRecord = piData->picRecord;
	
	memset( piData->szIndexName, 0, sizeof( piData->szIndexName ) );

	if( INDEX_UNIT_HOUR == piData->nIndexUnit )
	{
		/* 索引文件按小时组织 */
		if( IsGlobalTime( picRecord ) )
		{
			sprintf( piData->szIndexName, "%s.%10.10s.index", picRecord->szIndexType, piData->szRecTime );
		}
		else
		{
			sprintf( piData->szIndexName, "%s.%8.8s%s%s.index", 
												picRecord->szIndexType,	piData->szRecTime,
												picRecord->szIndexStartTime, picRecord->szIndexEndTime );
		}
	}
	else if( INDEX_UNIT_DAY == piData->nIndexUnit )
	{
		/* 索引文件按天组织 */
		if( IsGlobalTime( picRecord ) )
		{
			sprintf( piData->szIndexName, "%s.%8.8s.index", picRecord->szIndexType, piData->szRecTime );
		}
		else
		{
			sprintf( piData->szIndexName, "%s.%6.6s%s%s.index", 
												picRecord->szIndexType,	piData->szRecTime,
												picRecord->szIndexStartTime, picRecord->szIndexEndTime );
		}
	}
	else if( INDEX_UNIT_MONTH == piData->nIndexUnit )
	{
		/* 索引文件按月组织 */
		if( IsGlobalTime( picRecord ) )
		{
			sprintf( piData->szIndexName, "%s.%6.6s.index", picRecord->szIndexType, piData->szRecTime );
		}
		else
		{
			sprintf( piData->szIndexName, "%s.%4.4s%s%s.index", 
												picRecord->szIndexType,	piData->szRecTime,
												picRecord->szIndexStartTime, picRecord->szIndexEndTime );
		}
	}
	else if( INDEX_UNIT_YEAR == piData->nIndexUnit )
	{
		/* 索引文件按年组织 */
		if( IsGlobalTime( picRecord ) )
		{
			sprintf( piData->szIndexName, "%s.%4.4s.index", picRecord->szIndexType, piData->szRecTime );
		}
		else
		{
			sprintf( piData->szIndexName, "%s.%s%s.index", 
												picRecord->szIndexType, 
												picRecord->szIndexStartTime, picRecord->szIndexEndTime );
		}
	}
	else
	{
		/* 索引文件组织方式无效 */
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效的 IndexFlag [%s] !\n\n", picRecord->szIndexFlag );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: CheckIndexTime
description: 匹配索引文件作用时间
Input: piData: 描述系统全局结构的结构体
	   picRecord: 索引文件配置记录
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int CheckIndexTime( PINDEX_DATA piData, PICTRL_RECORD picRecord )
{
	if( IsGlobalTime( picRecord ) )
	{
		return MY_SUCCEED;
	}

	if( INDEX_UNIT_HOUR == piData->nIndexUnit )
	{
		if( 0 > strncmp( piData->szRecTime + 8, picRecord->szIndexStartTime, DATE_HOUR_LEN )
		||  0 < strncmp( piData->szRecTime + 8, picRecord->szIndexEndTime  , DATE_HOUR_LEN ) )
		{
			return MY_FAIL;
		}
	}
	else if( INDEX_UNIT_DAY == piData->nIndexUnit )
	{
		if( 0 > strncmp( piData->szRecTime + 6, picRecord->szIndexStartTime, DATE_DAY_LEN )
		||  0 < strncmp( piData->szRecTime + 6, picRecord->szIndexEndTime  , DATE_DAY_LEN ) )
		{
			return MY_FAIL;
		}
	}
	else if( INDEX_UNIT_MONTH == piData->nIndexUnit )
	{
		if( 0 > strncmp( piData->szRecTime + 4, picRecord->szIndexStartTime, DATE_MON_LEN )
		||  0 < strncmp( piData->szRecTime + 4, picRecord->szIndexEndTime  , DATE_MON_LEN ) )
		{
			return MY_FAIL;
		}
	}
	else if( INDEX_UNIT_YEAR == piData->nIndexUnit )
	{
		if( 0 > strncmp( piData->szRecTime, picRecord->szIndexStartTime, DATE_YEAR_LEN )
		||  0 < strncmp( piData->szRecTime, picRecord->szIndexEndTime  , DATE_YEAR_LEN ) )
		{
			return MY_FAIL;
		}
	}
	else
	{
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}


/********************************************************** 
function: IsMatchIndexInfo
description: 判断索引文件配置是否符合当前记录
Input: piData: 描述系统全局结构的结构体
	   picRecord: 索引文件配置记录
Output:
Return: MY_TRUE: 是 MY_FALSE: 否
others:
***********************************************************/

int IsMatchIndexInfo( PINDEX_DATA piData, PICTRL_RECORD picRecord )
{
	/* 匹配索引文件类型 */
	if( 0 != strcmp( piData->pcRecord->szIndexType, picRecord->szIndexType ) )
	{
		return MY_FALSE;
	}

	/* 匹配索引文件生效时间 */
	if( !IsGlobalTime( picRecord ) )
	{
		if( 0 > strncmp( piData->szRecTime, picRecord->szEffectStartTime, strlen( picRecord->szEffectStartTime ) )
		||  0 < strncmp( piData->szRecTime, picRecord->szEffectEndTime, strlen( picRecord->szEffectEndTime ) ) )
		{
			return MY_FALSE;
		}
	}

	/* 获取索引文件组织方式 */
	if( MY_SUCCEED != GetIndexInfo( piData, picRecord->szIndexFlag ) )
	{
		return MY_FALSE;
	}

	/* 匹配索引文件作用时间 */
	if( MY_SUCCEED != CheckIndexTime( piData, picRecord ) )
	{
		return MY_FALSE;
	}

	return MY_TRUE;
}

/********************************************************** 
function: GetIndexRecord
description: 获取当前处理记录对应的索引文件的配置信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetIndexRecord( PINDEX_DATA piData )
{
	PICTRL_DATA picData;
	PICTRL_RECORD picRecord;
	int nLoop;
	
	if( NULL != piData->picRecord )
	{
		/* 判定当前处理记录是否符合上一条记录的配置 */
		if( IsMatchIndexInfo( piData, piData->picRecord ) )
		{
			return MY_SUCCEED;
		}
	}
	
	picData = &(piData->icData);
	picRecord = picData->picRecord;
	
	/* 获取当前记录的索引文件配置信息 */
	for( nLoop = 0; nLoop < picData->nRecCount; nLoop++, picRecord++ )
	{
		if( IsMatchIndexInfo( piData, picRecord ) )
		{
			piData->picRecord = picRecord;
			return MY_SUCCEED;
		}
	}
	
	/* 未找到匹配的记录 */
	if( nLoop >= picData->nRecCount )
	{
		/*strcpy( piData->szErrCode, ERROR_CODE_INDCRL );*/
		sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_INDCRL ) ;
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: IsMatchBlockInfo
description: 判断索引数据块配置是否符合当前记录
Input: piData: 描述系统全局结构的结构体
	   pbcRecord: 索引数据块配置记录
Output:
Return: MY_TRUE: 是 MY_FALSE: 否
others:
***********************************************************/

int IsMatchBlockInfo( PINDEX_DATA piData, PBCTRL_RECORD pbcRecord )
{
	if( 0 != strcmp( piData->pcRecord->szIndexType , pbcRecord->szIndexType )
	||  0 != strcmp( piData->picRecord->szBlockLink, pbcRecord->szBlockLink ) )
	{
		return MY_FALSE;
	}
	
	return MY_TRUE;
}

/********************************************************** 
function: GetIndexRecord
description: 获取当前处理记录对应的索引数据块的配置信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetBlockRecord( PINDEX_DATA piData )
{
	PBCTRL_DATA pbcData;
	PBCTRL_RECORD pbcRecord;
	int nLoop;
	
	if( NULL != piData->pbcRecord )
	{
		/* 判定当前处理记录是否符合上一条记录的配置 */
		if( IsMatchBlockInfo( piData, piData->pbcRecord ) )
		{
			return MY_SUCCEED;
		}
	}
	
	pbcData = &(piData->bcData);
	pbcRecord = pbcData->pbcRecord;
	
	/* 获取当前记录的索引	数据块配置信息 */
	for( nLoop = 0; nLoop < pbcData->nRecCount; nLoop++, pbcRecord++ )
	{
		if( IsMatchBlockInfo( piData, pbcRecord ) )
		{
			piData->pbcRecord = pbcRecord;
			return MY_SUCCEED;
		}
	}
	
	/* 未找到匹配的记录 */
	if( nLoop >= pbcData->nRecCount )
	{
		/*strcpy( piData->szErrCode, ERROR_CODE_BLKCRL );*/
		sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_BLKCRL ) ;
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetIndexFile
description: 获取当前处理记录对应的索引文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetIndexFile( PINDEX_DATA piData )
{
	char szIndexFile[MAX_PATH_LEN + 1];
	int nSerial;
	
	memset( piData->szRecTime, 0, sizeof( piData->szRecTime ) );
	memset( piData->szRecUser, 0, sizeof( piData->szRecUser ) );
	memset( piData->szSerial , 0, sizeof( piData->szSerial ) );
	
	strncpy( piData->szRecTime, piData->szRecord + piData->pcRecord->nTimeLoc, piData->pcRecord->nTimeLen );
	piData->szRecTime[piData->pcRecord->nTimeLoc] = 0;
	
	strncpy( piData->szRecUser, piData->szRecord + piData->pcRecord->nUserLoc, piData->pcRecord->nUserLen );
	piData->szRecUser[piData->pcRecord->nUserLen] = 0;
	
	TrimLeft( TrimRight( piData->szRecUser ) );
	
	nSerial = ( ( strlen( piData->szRecUser ) >= USER_OFFSET_LEN ) ? USER_OFFSET_LEN : ( strlen( piData->szRecUser ) ) );
	
	strncpy( piData->szSerial, piData->szRecUser + strlen( piData->szRecUser ) - nSerial, nSerial );
	piData->szSerial[nSerial] = 0;
	
	/* printf( "%s - %s - %s\n", piData->szRecTime, piData->szRecUser, piData->szSerial ); */
	
	/* 获取索引文件配置记录 */
	if( MY_SUCCEED != GetIndexRecord( piData ) )
	{
		return MY_FAIL;
	}
	
	/* 获取索引数据块配置记录 */
	if( MY_SUCCEED != GetBlockRecord( piData ) )
	{
		return MY_FAIL;
	}
	
	/* 生成索引文件名 */
	if( MY_SUCCEED != GetIndexName( piData ) )
	{
		return MY_FAIL;
	}
	
	memset( szIndexFile, 0, sizeof( szIndexFile ) );
	sprintf( szIndexFile, "%s/%s", piData->picRecord->szIndexDir, piData->szIndexName );
	
	if( 0 != strcmp( szIndexFile, piData->szIndexFile ) )
	{
		memset( piData->szIndexFile, 0, sizeof( piData->szIndexFile ) );
		strcpy( piData->szIndexFile, szIndexFile );
		
		piData->bSameIndexFile = MY_FALSE;
	}
	else
	{
		piData->bSameIndexFile = MY_TRUE;
	}

	return MY_SUCCEED;
}

/********************************************************** 
function: IsMatchRecField
description: 判断当前记录是否符合记录域配置
Input: piData: 描述系统全局结构的结构体
	   pcRecord: 索引字段配置记录
Output:
Return: MY_TRUE: 是 MY_FALSE: 否
others:
***********************************************************/

int IsMatchRecField( PINDEX_DATA piData, PCONFIG_RECORD pcRecord )
{
	/* 匹配文件头 */
	if( 0 != *(pcRecord->szFileHead) )
	{
		if( 0 != strncmp( piData->szFileName, pcRecord->szFileHead, strlen( pcRecord->szFileHead ) ) )
		{
			return MY_FALSE;
		}
	}

	/* 匹配系统代码 */
	if( 0 != *(pcRecord->szSysType) )
	{
		if( 0 != strncmp( piData->szRecord, pcRecord->szSysType, strlen( pcRecord->szSysType ) ) )
		{
			return MY_FALSE;
		}
	}

	/* 匹配逻辑表达式 */
	return ( IsMatchConField( piData, pcRecord ) );
}

/********************************************************** 
function: GetConfigRecord
description: 获取当前处理记录对应的索引字段配置记录
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetConfigRecord( PINDEX_DATA piData )
{
	PINDEX_CONFIG piConfig;
	PCONFIG_RECORD pcRecord;
	int nLoop;
	
	if( NULL != piData->pcRecord )
	{
		/* 判定当前处理记录是否符合上一条记录的配置 */
		if( IsMatchRecField( piData, piData->pcRecord ) )
		{
			return MY_SUCCEED;
		}
	}
	
	piConfig = &(piData->iConfig);
	pcRecord = piConfig->pcRecord;
	
	/* 在配置文件中获取当前记录的配置项 */
	for( nLoop = 0; nLoop < piConfig->nRecCount; nLoop++, pcRecord++ )
	{
		if( IsMatchRecField( piData, pcRecord ) )
		{
			piData->pcRecord = pcRecord;
			return MY_SUCCEED;
		}
	}
	
	/* 判定是否找到匹配的配置记录 */
	if( nLoop >= piConfig->nRecCount )
	{
		/*strcpy( piData->szErrCode, ERROR_CODE_CFGREC );*/
		sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_CFGREC ) ;
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetIndexFields
description: 获取当前处理的记录的索引字段的组合
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetIndexFields( PINDEX_DATA piData )
{
	PCONFIG_RECORD pcRecord;
	PINDEX_FIELD piField;
	char szIndexField[MAX_RECORD_LEN + 1];
	int nLoop;
	
	pcRecord = piData->pcRecord;
	piField  = pcRecord->piField;
	
	memset( piData->szIndexFields, 0, sizeof( piData->szIndexFields ) );
	
	for( nLoop = 0; nLoop < pcRecord->nFieldNum; nLoop++, piField++ )
	{
		memset( szIndexField, 0, sizeof( szIndexField ) );
		
		strncpy( szIndexField, piData->szRecord + piField->nFieldStart, piField->nFieldLen );
		szIndexField[piField->nFieldLen] = 0;
		
		strcat( piData->szIndexFields, szIndexField );
		
		/* printf( "%s\n", piData->szIndexFields ); */
	}
	
	strcat( piData->szIndexFields, "\n" );

	return MY_SUCCEED;
}

/********************************************************** 
function: UpdateIndexFile
description: 更新索引文件, 记录当前处理记录的索引信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int UpdateIndexFile( PINDEX_DATA piData )
{
	long lBlockLink;

	if( ( piData->lRealBlockSize - BLOCK_HEAD_LEN ) >= ( strlen( piData->szIndexFields ) + atol( piData->szBlockSize ) ) )
	{
		/* 当前索引数据块可以存储索引信息 */
		
		/* 定位索引数据块头 */
		if( 0 != fseek( piData->fpIndex, piData->lBlockOffset, SEEK_SET ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "定位索引数据块头位置失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
		
		memset( piData->szBlockHead, 0, sizeof( piData->szBlockHead ) );
		
		sprintf( piData->szBlockHead, "%5.5s%5.5s%1.1s%08ld\n", 
														piData->szBlockStartTime, piData->szBlockEndTime, piData->szBlockFlag,
														( long )atol( piData->szBlockSize ) + strlen( piData->szIndexFields ) );

		/* 修改索引数据块头内容 */
		if( strlen( piData->szBlockHead ) != fwrite( piData->szBlockHead, sizeof( char ), strlen( piData->szBlockHead ), piData->fpIndex ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "修改索引数据块头失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
		
		if( 0 != fseek( piData->fpIndex, atol( piData->szBlockSize ), SEEK_CUR ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "定位索引数据块存储位置失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
		
		/* 记录索引信息 */
		if( strlen( piData->szIndexFields ) != fwrite( piData->szIndexFields, sizeof( char ), strlen( piData->szIndexFields ), piData->fpIndex ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "记录索引信息失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
	}
	else
	{
		/* 在索引文件尾部扩展新的索引数据块 */
		
		/* 获取文件尺寸  */
		lBlockLink = GetFileSize( piData->szIndexFile );
		if( 0 >= lBlockLink || 0 != ( lBlockLink % 1024 ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "文件长度 %ld 不是基本存储单位的整数倍!\n", lBlockLink );
			return MY_FAIL;
		}

		lBlockLink = ( long ) ( lBlockLink / 1024 );
		
		/* 定位链接索引数据块头 */
		if( 0 != fseek( piData->fpIndex, piData->lBlockOffset, SEEK_SET ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "定位链接索引数据块头位置失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
		
		memset( piData->szBlockHead, 0, sizeof( piData->szBlockHead ) );
		
		sprintf( piData->szBlockHead, "%5.5s%5.5s%1.1s%08ld\n", 
														piData->szBlockStartTime, piData->szBlockEndTime, 
														BLOCK_FLAG_FULL, lBlockLink );

		/* 修改索引数据块头链接 */
		if( strlen( piData->szBlockHead ) != fwrite( piData->szBlockHead, sizeof( char ), strlen( piData->szBlockHead ), piData->fpIndex ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "修改索引数据块头链接失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}

		/* 定位至索引文件尾部 */
		if( 0 != fseek( piData->fpIndex, 0, SEEK_END ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "定位扩展索引数据块头位置失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}

		/* 申请新的索引数据块 */
		memset( piData->szBlock, BLOCK_FILL_CHAR, piData->lRealBlockSize );
		memset( piData->szBlockHead, 0, sizeof( piData->szBlockHead ) );
		
		sprintf( piData->szBlockHead, "%5.5s%5.5s%1.1s%08ld\n", 
														piData->szBlockStartTime, piData->szBlockEndTime, 
														BLOCK_FLAG_AVAIL, strlen( piData->szIndexFields ) );

		memcpy( piData->szBlock, piData->szBlockHead, BLOCK_HEAD_LEN );
		memcpy( piData->szBlock + BLOCK_HEAD_LEN, piData->szIndexFields, strlen( piData->szIndexFields ) );
		memcpy( piData->szBlock + piData->lRealBlockSize - 1, "\n", 1 );
		piData->szBlock[piData->lRealBlockSize] = 0;
		
		/* 扩展索引数据块 */
		if( piData->lRealBlockSize != fwrite( piData->szBlock, sizeof( char ), piData->lRealBlockSize, piData->fpIndex ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "扩展索引数据块失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: CleanRecordField
description: 清空详单中指定字段的内容
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int CleanRecordField( PINDEX_DATA piData )
{
	PCONFIG_RECORD pcRecord;
	PCLEAN_FIELD pcField;
	
	int nLoop;

	pcRecord = piData->pcRecord;
	pcField  = pcRecord->pcField;

	for( nLoop = 0; nLoop < pcRecord->nCleanCount; nLoop++, pcField++ )
	{
		memset( piData->szRecord + pcField->nFieldStart, '0', pcField->nFieldLen );
	}

	return MY_SUCCEED;
}

/********************************************************** 
function: SearchIndexBlock
description: 在索引数据块中搜索当前记录的索引信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int SearchIndexBlock( PINDEX_DATA piData )
{
	char szIndexFields[MAX_RECORD_LEN + 1];
	char * szEndPos;
	
	long lCurrPos;

	do
	{
		/* 在索引文件中定位索引数据块 */
		if( 0 != fseek( piData->fpIndex, piData->lBlockOffset, SEEK_SET ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "定位索引数据块位置失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}

		memset( piData->szBlock, 0, piData->lBlockSize + 1 );

		if( piData->lRealBlockSize != fread( piData->szBlock, sizeof( char ), piData->lRealBlockSize, piData->fpIndex ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引数据块读取失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}

		GetBlockHeadInfo( piData );

		lCurrPos = BLOCK_HEAD_LEN;
		
		while( ( lCurrPos + strlen( piData->szIndexFields ) <= piData->lRealBlockSize && BLOCK_FILL_CHAR != *(piData->szBlock + lCurrPos) ) )
		{
			szEndPos = NULL;
			memset( szIndexFields, 0, sizeof( szIndexFields ) );

			szEndPos = ( char * ) strchr( piData->szBlock + lCurrPos, FIELD_END_FLAG );
			if( NULL == szEndPos )
			{
				break;
			}
	
			memcpy( szIndexFields, piData->szBlock + lCurrPos, szEndPos - ( piData->szBlock + lCurrPos ) + 1 );
		
			lCurrPos = szEndPos - piData->szBlock + 1;

			/* 判断索引字段是否已存储在索引文件中 */
			if( 0 == strcmp( szIndexFields, piData->szIndexFields ) )
			{
				/*strcpy( piData->szErrCode, ERROR_CODE_DUPREC );*/
				sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_DUPREC ) ;
			
				if( 0 != piData->pcRecord->nCleanCount )
				{
					/* 清空指定项 */
					if( MY_SUCCEED != CleanRecordField( piData ) )
					{
						return MY_FAIL;
					}
				
				#ifdef	__OUT_CLEAN_RECROD__	
					/*strcpy( piData->szErrCode, ERROR_CODE_NORMAL );*/
					sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_NORMAL ) ;
				#endif
				
				}

				return MY_SUCCEED;;
			}
		}

		if( 0 != strcmp( piData->szBlockFlag, BLOCK_FLAG_AVAIL ) )
		{
			if( 0 != strcmp( piData->szBlockFlag, BLOCK_FLAG_FULL ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引数据块标志 %s 无效!\n", piData->szBlockFlag );
				return MY_FAIL;
			}
			
			piData->lBlockOffset = atol( piData->szBlockSize ) * 1024;
		}

		/* 如果数据块未满, 结束搜索 */
	} while( 0 != strcmp( piData->szBlockFlag, BLOCK_FLAG_AVAIL ) );

	/* 在索引文件中记录索引信息 */
	if( MY_SUCCEED != UpdateIndexFile( piData ) )
	{
		return MY_FAIL;
	}

	return MY_SUCCEED;
}

/********************************************************** 
function: GetBlockTime
description: 获取当前记录索引数据块时间
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetBlockTime( PINDEX_DATA piData )
{
	PBCTRL_RECORD pbcRecord;
	PTIME_DATA ptData;
	
	pbcRecord = piData->pbcRecord;
	ptData = &(piData->tData);
	
	memset( ptData, 0, sizeof( TIME_DATA ) );
	
	GetTimeData( piData->szRecTime, ptData );
	
	if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_SEC ) )
	{
		switch( piData->nIndexUnit )
		{
			case INDEX_UNIT_HOUR:
				piData->lBlockTime = atoi( ptData->szSec ) + atoi( ptData->szMin ) * 60;
				break;
			case INDEX_UNIT_DAY:
				piData->lBlockTime = atoi( ptData->szSec ) + atoi( ptData->szMin ) * 60 
														   + atoi( ptData->szHour ) * 60 * 60;
				break;
			default:
				piData->lBlockTime = -1;
				break;
		}
	}
	else if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_MIN ) )
	{
		switch( piData->nIndexUnit )
		{
			case INDEX_UNIT_HOUR:
				piData->lBlockTime = atoi( ptData->szMin );
				break;
			case INDEX_UNIT_DAY:
				piData->lBlockTime = atoi( ptData->szMin ) + atoi( ptData->szHour ) * 60;
			case INDEX_UNIT_MONTH:
				piData->lBlockTime = atoi( ptData->szMin ) + atoi( ptData->szHour ) * 60 + atoi( ptData->szDay ) * 24 * 60;
				break;
			default:
				piData->lBlockTime = -1;
				break;
		}
	}
	else if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_HOUR ) )
	{
		switch( piData->nIndexUnit )
		{
			case INDEX_UNIT_HOUR:
				piData->lBlockTime = 1;
				break;
			case INDEX_UNIT_DAY:
				piData->lBlockTime = atoi( ptData->szHour );
			case INDEX_UNIT_MONTH:
				piData->lBlockTime = atoi( ptData->szHour ) + atoi( ptData->szDay ) * 24;
				break;
			default:
				piData->lBlockTime = -1;
				break;
		}
	}
	else if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_DAY ) )
	{
		switch( piData->nIndexUnit )
		{
			case INDEX_UNIT_DAY:
				piData->lBlockTime = 1;
			case INDEX_UNIT_MONTH:
				piData->lBlockTime = atoi( ptData->szDay );
				break;
			default:
				piData->lBlockTime = -1;
				break;
		}
	}
	else if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_MON ) )
	{
		switch( piData->nIndexUnit )
		{
			case INDEX_UNIT_MONTH:
				piData->lBlockTime = 1;
				break;
			case INDEX_UNIT_YEAR:
				piData->lBlockTime = atoi( ptData->szMon );
				break;
			default:
				piData->lBlockTime = -1;
				break;
		}
	}
	else
	{
		piData->lBlockTime = -1;
	}
	
	piData->lBlockTime += 1;
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetBlockOffset
description: 获取索引数据块在索引文件中的位置
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetBlockOffset( PINDEX_DATA piData )
{
	PBCTRL_RECORD pbcRecord;
	char szIndexUnit[14 + 1];
	int nBaseNum, nBlockNo;
	long lBaseTime;
	
	pbcRecord = piData->pbcRecord;
	
	if( INDEX_MODE_TIME == piData->nIndexMode )
	{
		memset( szIndexUnit, 0, sizeof( szIndexUnit ) );

		if( INDEX_UNIT_HOUR == piData->nIndexUnit )
		{
			strncpy( szIndexUnit, piData->szRecTime + 8, DATE_HOUR_LEN );
			szIndexUnit[DATE_HOUR_LEN] = 0;
		}
		else if( INDEX_UNIT_DAY == piData->nIndexUnit )
		{
			strncpy( szIndexUnit, piData->szRecTime + 6, DATE_DAY_LEN );
			szIndexUnit[DATE_DAY_LEN] = 0;
		}
		else if( INDEX_UNIT_MONTH == piData->nIndexUnit )
		{
			strncpy( szIndexUnit, piData->szRecTime + 4, DATE_MON_LEN );
			szIndexUnit[DATE_MON_LEN] = 0;
		}
		else if( INDEX_UNIT_YEAR == piData->nIndexUnit )
		{
			strncpy( szIndexUnit, piData->szRecTime, DATE_YEAR_LEN );
			szIndexUnit[DATE_YEAR_LEN] = 0;
		}

		if( !IsNum( szIndexUnit ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%d]: 详单记录时间 [%s] 无效!\n", piData->nIndexUnit, piData->szRecTime );
			return MY_FAIL;
		}
		
		GetBlockTime( piData );
		if( 0 >= piData->lBlockTime )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "[%d] - [%s] 获取索引数据块时间失败!\n", piData->nIndexUnit, pbcRecord->szBlockFlag );
			return MY_FAIL;
		}

		nBaseNum = pbcRecord->nBlockNum / piData->nTimeCount;

		lBaseTime = piData->lTotalTime / nBaseNum;

		if( !IsGlobalTime( piData->picRecord ) )
		{
			nBlockNo = ( atoi( szIndexUnit ) - atoi( pbcRecord->szBlockStartTime ) ) * nBaseNum + ( piData->lBlockTime + lBaseTime - 1 ) / lBaseTime;
		}
		else
		{
			nBlockNo = ( piData->lBlockTime + lBaseTime - 1 ) / lBaseTime;
		}
		
		piData->lBlockOffset = ( nBlockNo - 1 ) * piData->lRealBlockSize;
	}
	else if( INDEX_MODE_USER == piData->nIndexMode )
	{
		piData->lBlockOffset = ( ( atol( piData->szSerial ) * pbcRecord->nBlockNum ) / 10000 ) * piData->lRealBlockSize;
	}
	else
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效的索引数据块组织模式 %d !\n", piData->nIndexMode );
		return MY_FAIL;
	}
	
	/* printf( "BlockOffset = %ld\n", piData->lBlockOffset ); */
	
	return MY_SUCCEED;
}

/********************************************************** 
function: SearchIndexFile
description: 搜索索引文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int SearchIndexFile( PINDEX_DATA piData )
{
	PBCTRL_RECORD pbcRecord;
	
	pbcRecord = piData->pbcRecord;

	/* 获取索引数据块时间数目 */
	piData->lTotalTime = GetTotalTime( piData, pbcRecord );
	if( 0 >= piData->lTotalTime )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引数据块时间数目失败!\n" );
		return MY_FAIL;
	}

	/* 校验索引数据块定义 */
	if( MY_SUCCEED != CheckBlockRecord( piData, piData->picRecord, piData->pbcRecord ) )
	{
		return MY_FAIL;
	}

	/* 获取数据块的大小 */
	piData->lRealBlockSize = GetBlockSize( pbcRecord );
	if( 0 >= piData->lRealBlockSize )
	{
		return MY_FAIL;
	}

	/* 申请保存索引数据块的内存空间 */
	if( piData->lRealBlockSize > piData->lBlockSize )
	{
		if( NULL != piData->szBlock )
		{
			free( piData->szBlock );
			piData->szBlock = NULL;
		}
		
		piData->lBlockSize = piData->lRealBlockSize;
		
		piData->szBlock = ( char * ) malloc( piData->lBlockSize + 1 );
		if( NULL == piData->szBlock )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "申请保存索引数据块的内存空间失败!\n" );
			return MY_FAIL;
		}
	}

	memset( piData->szBlock, 0, piData->lBlockSize + 1 );
	
	/* 获取索引数据块位置 */
	if( MY_SUCCEED != GetBlockOffset( piData ) )
	{
		return MY_FAIL;
	}

	/* 检索索引数据块 */
	if( MY_SUCCEED != SearchIndexBlock( piData ) )
	{
		return MY_FAIL;
	}

/* 
	if( NULL != piData->szBlock )
	{
		free( piData->szBlock );
		piData->szBlock = 0;
		
		piData->lRealBlockSize = 0;
		piData->lBlockSize = 0;
	}
*/
	return MY_SUCCEED;
}

/********************************************************** 
function: GetRecordType
description: 获取当前处理记录的类型
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetRecordType( PINDEX_DATA piData )
{
	/* 获取记录对应配置信息 */
	if( MY_SUCCEED != GetConfigRecord( piData ) )
	{
		return MY_SUCCEED;
	}

	/* 校验记录长度 */
	if( ( piData->pcRecord->nRecLen ) != strlen( piData->szRecord ) )
	{
		/*strcpy( piData->szErrCode, ERROR_CODE_RECLEN );*/
		sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_RECLEN ) ;
		return MY_SUCCEED;
	}

#ifdef	__NOT_WEED_CMNREC__	
	if( 0 == piData->pcRecord->nCleanCount )
	{
		strcpy( piData->szErrCode, ERROR_CODE_NORMAL );
		/*sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_NORMAL ) ;*/
		return MY_SUCCEED;
	}
#endif

	/* 获取索引文件 */
	if( MY_SUCCEED != GetIndexFile( piData ) )
	{
		return MY_SUCCEED;
	}

	/* 判断索引文件是否存在 */
	if( !FileIsExist( piData->szIndexFile ) )
	{
	/*	
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引文件 %s 不存在!\n", piData->szIndexFile );
		return MY_FAIL;
	*/
		/*strcpy( piData->szErrCode, ERROR_CODE_NOTEXT );*/
		sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_NOTEXT ) ;
		return MY_SUCCEED;
	}

	/* 生成索引字段组合 */
	if( MY_SUCCEED != GetIndexFields( piData ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "生成索引字段组合失败!\n" );
		return MY_FAIL;
	}

	if( !(piData->bSameIndexFile) )
	{
		/* 关闭上次打开的索引文件 */
		if( NULL != piData->fpIndex )
		{
			fclose( piData->fpIndex );
			piData->fpIndex = NULL;
		}

		/* 打开索引文件 */
		piData->fpIndex = fopen( piData->szIndexFile, "r+" );
		if( NULL == piData->fpIndex )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引文件 %s 打开失败!\n", piData->szIndexFile );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
	}

	/* 检索索引文件 */
	if( MY_SUCCEED != SearchIndexFile( piData ) )
	{
		return MY_FAIL;
	}

	return MY_SUCCEED;
}

/********************************************************** 
function: WeedDupRecord
description: 剔除重单记录
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int WeedDupRecord( PINDEX_DATA piData )
{
	/* 获取当前处理记录的类型 */
	if( MY_SUCCEED != GetRecordType( piData ) )
	{
		return MY_FAIL;
	}

	/*if( 0 != strcmp( piData->szErrCode, ERROR_CODE_NORMAL ) )*/
	if( 0 == strstr( piData->szErrCode, ERROR_CODE_NORMAL ) )
	{
	#ifdef	__SPECIAL_DUPFILE__
		if( 0 != strstr( piData->szErrCode, ERROR_CODE_DUPREC ) )
		{
			/* 输出重单记录 */
			if( MY_SUCCEED != WriteDupFile( piData ) )
			{
				return MY_FAIL;
			}
		}
		else
		{
			/* 输出错单记录 */
			if( MY_SUCCEED != WriteErrRecord( piData ) )
			{
				return MY_FAIL;
			}
		}
	#else
		/* 输出错单记录 */
		if( MY_SUCCEED != WriteErrRecord( piData ) )
		{
			return MY_FAIL;
		}
		
		if( 0 != strstr( piData->szErrCode, ERROR_CODE_DUPREC ) )
		{
			/* 输出重单记录 */
			if( MY_SUCCEED != WriteDupFile( piData ) )
			{
				return MY_FAIL;
			}
		}
	#endif
	}
	else
	{
		/* 输出正常记录至出口临时文件 */
		if( MY_SUCCEED != WriteTmpOutFile( piData ) )
		{
			return MY_FAIL;
		}
	}
	
	/* 更新断点文件 */
	if( MY_SUCCEED != UpdateBreakFile( piData ) )
	{				
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: IsDealFile
description: 判断指定的文件是否符合处理要求
Input: piData: 描述系统全局结构的结构体�
	   szFileName: 当前处理文件文件名
Output:
Return: MY_TRUE: 是 MY_FALSE: 不是
others:
***********************************************************/

int IsDealFile( PINDEX_DATA piData, char * szFileName )
{
	PINDEX_CONFIG piConfig;
	PCONFIG_RECORD pcRecord;
	int nLoop;

	piConfig = &(piData->iConfig);
	pcRecord = piConfig->pcRecord;

	piData->lTotalRec = 0;
	piData->lAvailRec = 0;
	piData->lErrorRec = 0;
	piData->lDupRec   = 0;
/*	
	if( 2 >= strlen( szFileName ) )
	{
		return MY_FALSE;
	}
*/
	/* 在配置文件中获取当前记录的配置项 */
	for( nLoop = 0; nLoop < piConfig->nRecCount; nLoop++, pcRecord++ )
	{
		/* 匹配文件头 */
		if( 0 == strncmp( szFileName, pcRecord->szFileHead, strlen( pcRecord->szFileHead ) ) )
		{
				return MY_TRUE;
		}
		
		if( 0 == *(pcRecord->szFileHead) )
		{
			return MY_TRUE;
		}
	}
	
	return MY_FALSE;
}

/********************************************************** 
function: GetBreakState
description: 获取系统断点状态
Input: piData: 描述系统全局结构的结构体�
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetBreakState( PINDEX_DATA piData )
{
	DIR * dirp;
	struct dirent * entry;
	
	piData->nBreakState = BREAK_STATE_NORMAL;
	
	/* 打开目录 */
	dirp = ( opendir( (piData->dCmd).szLogTmp ) );
	if( NULL == dirp )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "临时日志目录 %s 打开失败!\n", (piData->dCmd).szLogTmp );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	/* 遍历目录下的所有文件 */
	while( NULL != ( entry = readdir( dirp ) ) )
	{
		if( 0 == strncmp( entry->d_name, BREAK_LOG_HEAD, strlen( BREAK_LOG_HEAD ) ) )
		{
			if( BREAK_STATE_NORMAL != piData->nBreakState )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "临时日志目录存在多个断点文件!\n" );
				return MY_FAIL;
			}
			
			memset( piData->szFileName, 0, sizeof( piData->szFileName ) );
			
			if( 0 == strcmp( entry->d_name + strlen( entry->d_name ) - strlen( BREAK_START_TAIL ), BREAK_START_TAIL ) )
			{
				strncpy( piData->szFileName, entry->d_name + strlen( BREAK_LOG_HEAD ), strlen( entry->d_name ) - strlen( BREAK_LOG_HEAD ) - strlen( BREAK_START_TAIL ) );
				
				piData->nBreakState = BREAK_STATE_START;
				return MY_SUCCEED;
			}

			if( 0 == strcmp( entry->d_name + strlen( entry->d_name ) - strlen( BREAK_TMP_TAIL ), BREAK_TMP_TAIL ) )
			{
				strncpy( piData->szFileName, entry->d_name + strlen( BREAK_LOG_HEAD ), strlen( entry->d_name ) - strlen( BREAK_LOG_HEAD ) - strlen( BREAK_TMP_TAIL ) );
				
				piData->nBreakState = BREAK_STATE_TMP;
				return MY_SUCCEED;
			}
			
			if( 0 == strcmp( entry->d_name + strlen( entry->d_name ) - strlen( BREAK_END_TAIL ), BREAK_END_TAIL ) )
			{
				strncpy( piData->szFileName, entry->d_name + strlen( BREAK_LOG_HEAD ), strlen( entry->d_name ) - strlen( BREAK_LOG_HEAD ) - strlen( BREAK_END_TAIL ) );
				
				piData->nBreakState = BREAK_STATE_END;
				return MY_SUCCEED;
			}

			continue;
		}
	}
	
	closedir( dirp );
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetBreakRecordInfo
description: 获取断点记录内容
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetBreakRecordInfo( PINDEX_DATA piData )
{
	PBREAK_RECORD pbRecord;
	char szBreakFile[MAX_PATH_LEN + 1];
	char szRecord[MAX_RECORD_LEN + 1];
	char * szPos;
	int nFieldNum;
	
	pbRecord = &(piData->bRecord);
	
	memset( szBreakFile, 0, sizeof( szBreakFile ) );
	memset( szRecord, 0, sizeof( szRecord ) );
	
	sprintf( szBreakFile, "%s/%s%s%s", (piData->dCmd).szLogTmp, BREAK_LOG_HEAD, piData->szFileName, BREAK_START_TAIL );
	
	piData->nBreakHandle = open( szBreakFile, O_RDWR );
	if( -1 == piData->nBreakHandle )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "打开断点文件 %s 失败!\n", szBreakFile );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	if( 0 == GetFileSize( szBreakFile ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "断点文件 %s 为空!\n\n", szBreakFile );
		
		pbRecord->lRecordNo = 0;
		strcpy( pbRecord->szErrCode, ERROR_CODE_NORMAL );
		
		return MY_SUCCEED;
	}
	
	if( 0 >= read( piData->nBreakHandle, szRecord, sizeof( szRecord ) ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "读取断点记录失败!\n" );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}

	nFieldNum = 0;
	
	szPos = strtok( szRecord, BREAK_FIELD_SEP );
	while( NULL != szPos )
	{
		switch( nFieldNum )
		{
			case 0:		/* 断点记录序号 */
				
				pbRecord->lRecordNo = atoi( szPos );
				break;
				
			case 1:		/* 断点记录类型 */
				
				strcpy( pbRecord->szErrCode, szPos );
				break;
	
			default:	/* 其他 */
				
				break;
		}
			
		nFieldNum++;
		szPos = strtok( NULL, BREAK_FIELD_SEP );	
	}
	
	if( 2 != nFieldNum )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "断点记录 %s 无效!\n", szRecord );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		close( piData->nBreakHandle );
		return MY_FAIL;
	}
	
	/* printf( "%ld - %s\n", pbRecord->lRecordNo, pbRecord->szErrCode ); */
	
	return MY_SUCCEED;
}

/********************************************************** 
function: OpenDupFile
description: 打开重单记录文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int OpenDupFile( PINDEX_DATA piData )
{
	char szDupFile[MAX_PATH_LEN + 1];
	
	memset( szDupFile, 0, sizeof( szDupFile ) );
	
	sprintf( szDupFile, "%s/%s.dup", piData->dCmd.szLogTmp, piData->szFileName );

	if( !FileIsExist( szDupFile ) )
	{
		piData->bDupRecord = MY_FALSE;
		return MY_SUCCEED;
	}
	
	piData->bDupRecord = MY_TRUE;
	
	piData->fpDup = fopen( szDupFile, "r" );
	if( NULL == piData->fpDup )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "打开重单文件 %s 失败!\n", szDupFile );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}

	piData->lDupNo = 0;
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetDupRecord
description: 获取一条重单记录
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetDupRecord( PINDEX_DATA piData )
{
	char szRecord[MAX_RECORD_LEN + 1];
	char * szPos;
	int nFieldNum;
	
	if( !(piData->bDupRecord) )
	{
		return MY_SUCCEED;
	}
	
	memset( szRecord, 0, sizeof( szRecord ) );

	if( NULL == fgets( szRecord, sizeof( szRecord ), piData->fpDup ) )
	{
		piData->lDupNo     = 0;
		piData->bDupRecord = MY_FALSE;
		
		return MY_SUCCEED;
	}

	nFieldNum = 0;
	
	szPos = strtok( szRecord, ":" );
	while( NULL != szPos )
	{
		switch( nFieldNum )
		{
			case 0:		/* 断点记录序号 */
				
				piData->lDupNo = atoi( szPos );
				break;
				
			case 1:		/* 断点记录类型 */
				memset( piData->szDupRecord, 0, sizeof( piData->szDupRecord ) );
				
				strcpy( piData->szDupRecord, szPos );
				break;
	
			default:	/* 其他 */
				
				break;
		}
			
		nFieldNum++;
		szPos = strtok( NULL, ":" );	
	}
	
	if( 2 != nFieldNum )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "重单记录 %s 无效!\n", szRecord );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	/* printf( "rec: %ld - [%s]\n", piData->lDupNo, piData->szDupRecord ); */
	
	return MY_SUCCEED;
}

/********************************************************** 
function: RollbackRecord
description: 回滚记录
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int RollbackRecord( PINDEX_DATA piData )
{
	/* 正常处理断点记录后的记录 */
	if( piData->lTotalRec > piData->bRecord.lRecordNo )
	{
		/* 判断当前处理记录是否为重单记录 */
		if( MY_SUCCEED != WeedDupRecord( piData ) )
		{
			return MY_FAIL;
		}
		
		piData->bRollback = MY_FALSE;
		
		return MY_SUCCEED;
	}

	if( piData->bDupRecord )
	{
		/* 重单记录不检索索引文件 */
		if( piData->lTotalRec == piData->lDupNo )
		{
			/*strcpy( piData->szErrCode, ERROR_CODE_DUPREC );*/
			sprintf( piData->szErrCode, "%s%2.2s%s", ERROR_CODE_PREFIX, piData->szRecord, ERROR_CODE_DUPREC );
			
			/* 输出重单记录 */
			/*
			if( MY_SUCCEED != WriteDupFile( piData ) )
			{
				return MY_FAIL;
			}
			*/
			
			piData->lErrorRec++;
			piData->lDupRec++;
			
			if( MY_SUCCEED != GetDupRecord( piData ) )
			{
				return MY_FAIL;
			}
			
			return MY_SUCCEED;
		}
	}

	/* 回滚详单索引信息 */
	if( MY_SUCCEED != GetRecordType( piData ) )
	{
		return MY_FAIL;
	}

	if( 0 != strstr( piData->szErrCode, ERROR_CODE_NORMAL ) )
	{
		/* 输出正常记录至出口临时文件 */
		if( MY_SUCCEED != WriteTmpOutFile( piData ) )
		{
			return MY_FAIL;
		}
	}
	else
	{
		/* 输出错单记录 */
		if( MY_SUCCEED != WriteErrRecord( piData ) )
		{
			return MY_FAIL;
		}
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: RollbackIndexInfo
description: 恢复索引文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int RollbackIndexInfo( PINDEX_DATA piData )
{
	char szInFile[MAX_PATH_LEN + 1];
	FILE * fpSrc;
	
	piData->bRollback = MY_TRUE;
	
	/* 获取断点记录内容 */
	if( MY_SUCCEED != GetBreakRecordInfo( piData ) )
	{
		return MY_FAIL;
	}
	
	/* 获取重单记录 */
	if( MY_SUCCEED != OpenDupFile( piData ) )
	{
		return MY_FAIL;
	}
	
	/* 获取文件开始处理时间 */
	memset( piData->szStartTime, 0, sizeof( piData->szStartTime ) );
	GetCurrTime( piData->szStartTime );
		
	memset( szInFile, 0, sizeof( szInFile ) );
	
	sprintf( szInFile, "%s/%s", piData->dCmd.szInDir, piData->szFileName );

	/* 打开入口文件 */
	fpSrc = fopen( szInFile, "r" );
	if( NULL == fpSrc )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "入口文件 %s 打开失败!\n", szInFile );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}

	if( MY_SUCCEED != OpenTmpOutFile( piData ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "出口临时文件打开失败!\n" );
		return MY_FAIL;
	}
	
	IsDealFile( piData, piData->szFileName );

	memset( piData->szRecord, 0, sizeof( piData->szRecord ) );

	if( MY_SUCCEED != GetDupRecord( piData ) )
	{
		return MY_FAIL;
	}
	
	piData->nRecordLen = 0;
	
	/* 回滚文件中所有记录 */
	while( NULL != fgets( piData->szRecord, sizeof( piData->szRecord ), fpSrc ) )
	{
		piData->nRecordLen = strlen( piData->szRecord );
		
		piData->lTotalRec++;

		memset( piData->szErrCode, 0, sizeof( piData->szErrCode ) );
		strcpy( piData->szErrCode, ERROR_CODE_NORMAL );

		/* 回滚记录 */
		if( MY_SUCCEED != RollbackRecord( piData ) )
		{
			fclose( fpSrc );
			return MY_FAIL;
		}

		memset( piData->szRecord, 0, sizeof( piData->szRecord ) );
	} 

	/* 关闭入口文件指针 */
	if( NULL != fpSrc )
	{
		fclose( fpSrc );
		fpSrc = NULL;
	}
	
	if( NULL != piData->fpDup )
	{
		fclose( piData->fpDup );
		piData->fpDup = NULL;
	}

	/* 获取文件结束处理时间 */
	memset( piData->szEndTime, 0, sizeof( piData->szEndTime ) );
	GetCurrTime( piData->szEndTime );
	
	/* 写处理日志 */
	if( MY_SUCCEED != WriteProcLog( piData ) )
	{
		return MY_FAIL;
	}
	
	if( MY_SUCCEED != MoveAndBakFile( piData ) )
	{
		return MY_FAIL;
	}
		
	return MY_SUCCEED;
}

/********************************************************** 
function: RecoverBreakPoint
description: 恢复断点文件处理信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int RecoverBreakPoint( PINDEX_DATA piData )
{
	char szSrcFile[MAX_PATH_LEN + 1];
	char szDstFile[MAX_PATH_LEN + 1];
	
	if( MY_SUCCEED != GetBreakState( piData ) )
	{
		return MY_FAIL;
	}
	
	switch( piData->nBreakState )
	{
		case BREAK_STATE_NORMAL:
			
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "没有需要恢复的断点文件!\n\n" );
			return MY_SUCCEED;
			
			break;
			
		case BREAK_STATE_START:	/* 开始处理文件 */
			
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "恢复断点文件 %s 的索引信息!\n\n", piData->szFileName );
			
			/* 放弃出口临时文件内容, 恢复断点文件数据 */
			if( MY_SUCCEED != RollbackIndexInfo( piData ) )
			{
				return MY_FAIL;
			}
			
			return MY_SUCCEED;
			
			break;
			
		case BREAK_STATE_TMP:	/* 已关闭索引文件、临时文件, 临时文件已移至出口目录 */
			
			memset( szSrcFile, 0, sizeof( szSrcFile ) );
			memset( szDstFile, 0, sizeof( szDstFile ) );
	
			sprintf( szSrcFile, "%s/%s.dup", piData->dCmd.szLogTmp, piData->szFileName );
			sprintf( szDstFile, "%s/%s.dup", piData->dCmd.szRunLog, piData->szFileName );
		
			/* 存在重单文件 */
			if( FileIsExist( szSrcFile ) )
			{
				/* 重单文件移至重单目录 */
			/*
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "将重单文件 %s 移入重单目录下!\n", szSrcFile );
				
				if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "移动重单文件失败\n" );
					return MY_FAIL;
				}
			*/
				/* 删除重单临时文件 */
				
				if( 0 != remove( szSrcFile ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "删除重单临时文件 %s 失败\n", szSrcFile );
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
					return MY_FAIL;
				}
			}
			
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "将入口文件 %s 移入备份目录下!\n\n", szSrcFile );
			
			memset( szSrcFile, 0, sizeof( szSrcFile ) );
			memset( szDstFile, 0, sizeof( szDstFile ) );
			
			sprintf( szSrcFile, "%s/%s", piData->dCmd.szInDir , piData->szFileName );
			sprintf( szDstFile, "%s/%s", piData->dCmd.szBakDir, piData->szFileName );
		
			/* 入口文件不在入口目录 */
			if( !FileIsExist( szSrcFile ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "入口文件 %s 不在 %s 目录下!\n", szSrcFile, piData->dCmd.szInDir );
			}
			else
			{
				/* 入口文件移入备份目录 */
				if( MY_SUCCEED != MoveFile( szSrcFile, szDstFile ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "备份入口文件失败\n" );
					return MY_FAIL;
				}
			}
			
			if( MY_SUCCEED != CreateBreakFile( piData, BREAK_STATE_END ) )
			{
				return MY_FAIL;
			}
			
			break;
		
		case BREAK_STATE_END:	/* 入口文件已移至备份目录 */
			
			break;
			
		default:				/* 未定义的断点状态 */
			
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "断点状态 %d 无法判定!\n\n", piData->nBreakState );
			return MY_FAIL;
			
			break;
	}
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "删除断点文件!\n" );
			
	if( MY_SUCCEED != DeleteBreakLog( piData ) )
	{
		return MY_FAIL;
	}
			
	return MY_SUCCEED;
}

/********************************************************** 
function: DealSrcFile
description: 处理入口目录下的文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int DealSrcFile( PINDEX_DATA piData )
{
	DIR * dirp;
	struct dirent * entry;
	
	FILE * fpSrc;
	char szInFile[MAX_PATH_LEN + 1];

	/* 打开入口目录 */
	dirp = ( opendir( (piData->dCmd).szInDir ) );
	if( NULL == dirp )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "入口目录 %s 打开失败!\n", (piData->dCmd).szInDir );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;
	}
	
	/* 处理入口目录下所有符合条件的文件 */
	while( NULL != ( entry = readdir( dirp ) ) )
	{
		/* 获取系统运行控制标志 */
		if( PROC_CTRL_RUN != GetProcCtrlFlag( piData->dCmd.szCtrlFlag ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "系统运行标志设置为禁止运行, 系统停止运行!\n\n" );
			closedir( dirp );
			DisConnectDataBase( );
			FreeMemoryData( piData );
		
			exit(0);
		}
		
		tmEndTime = time( NULL );
		tmEndTime = tmEndTime - tmEndTime % (piData->dCmd).nInterval + (piData->dCmd).nInterval;
		
		if( tmEndTime > tmStartTime )
		{
			tmStartTime = tmEndTime;
			
			/* 获取当前批次 */
			GetCurrBatch( piData );
			
			if( MY_SUCCEED != AlterLogFile( piData ) ) { 
				DisConnectDataBase( ); 
				FreeMemoryData( piData ); 
				exit(0); 
			}

			/* 打开当前批次的处理日志、错单日志 
			if( MY_SUCCEED != OpenLogFile( piData ) )
			{
				DisConnectDataBase( );
				FreeMemoryData( piData );
				exit(0);
			}
			*/
		}
		
		/* 判断文件是否符合处理条件 */
		if( !IsDealFile( piData, entry->d_name ) )
		{
			continue;
		}
		
		printf( "deal file %s\n", entry->d_name );
		
		/* 获取文件开始处理时间 */
		memset( piData->szStartTime, 0, sizeof( piData->szStartTime ) );
		GetCurrTime( piData->szStartTime );

		memset( szInFile, 0, sizeof( szInFile ) );
		memset( piData->szFileName, 0, sizeof( piData->szFileName ) );
		
		strcpy( piData->szFileName, entry->d_name );
		sprintf( szInFile, "%s/%s", piData->dCmd.szInDir, piData->szFileName );
		
		if( MY_SUCCEED != CreateBreakFile( piData, BREAK_STATE_START ) )
		{
			return MY_FAIL;
		}

		/* 打开入口文件 */
		fpSrc = fopen( szInFile, "r" );
		if( NULL == fpSrc )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "入口文件 %s 打开失败!\n", szInFile );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			closedir( dirp );
			return MY_FAIL;
		}

		if( MY_SUCCEED != OpenTmpOutFile( piData ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "出口临时文件打开失败!\n" );
			closedir( dirp );
			return MY_FAIL;
		}
		
		piData->nRecordLen = 0;
		
		memset( piData->szRecord, 0, sizeof( piData->szRecord ) );

		/* 处理文件中所有记录 */
		while( NULL != fgets( piData->szRecord, sizeof( piData->szRecord ), fpSrc ) )
		{
			piData->nRecordLen = strlen( piData->szRecord );
			
			piData->lTotalRec++;

			memset( piData->szErrCode, 0, sizeof( piData->szErrCode ) );
			
			strcpy( piData->szErrCode, ERROR_CODE_NORMAL );

			/* 判断当前处理记录是否为重单记录 */
			if( MY_SUCCEED != WeedDupRecord( piData ) )
			{
				closedir( dirp );
				return MY_FAIL;
			}

			memset( piData->szRecord, 0, sizeof( piData->szRecord ) );
		} 
		
		/* 关闭入口文件指针 */
		if( NULL != fpSrc )
		{
			fclose( fpSrc );
			fpSrc = NULL;
		}
		
		/* 获取文件结束处理时间 */
		memset( piData->szEndTime, 0, sizeof( piData->szEndTime ) );
		GetCurrTime( piData->szEndTime );
		
		/* 写处理日志 */
		if( MY_SUCCEED != WriteProcLog( piData ) )
		{
			closedir( dirp );
			return MY_FAIL;
		}
		
		if( MY_SUCCEED != MoveAndBakFile( piData ) )
		{
			closedir( dirp );
			return MY_FAIL;
		}
	}
	
	closedir( dirp );

	return MY_SUCCEED;
}
