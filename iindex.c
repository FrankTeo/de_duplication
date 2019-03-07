

/********************************************************************
copyright (C), 1995-2004, Si-Tech Information Technology Ltd. 
file_name: iindex.c   
author: 张凡 version: （V1.00） date: （2004－08－20）
description: 实现索引文件初始化功能
others:
history: 1.date: 修改时间 version: 版本（V1.00）author: 作者
			modification: 修改内容
		 2. ... 
********************************************************************/


#include "ddef.h"


/********************************************************** 
function: IsGlobalTime
description: 判断是否为全局设置
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_TRUE: 是 MY_FALSE: 否
others:
***********************************************************/

int IsGlobalTime( PICTRL_RECORD picRecord )
{
	if( 0 == strcmp( picRecord->szIndexStartTime, "*" )
	||  0 == strcmp( picRecord->szIndexEndTime, "*" ) )
	{
		return MY_TRUE;
	}
	
	return MY_FALSE;
}

/********************************************************** 
function: GetIndexInfo
description: 获取索引文件结构信息
Input: piData: 描述系统全局结构的结构体
       szIndexFlag: 索引文件标志
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetIndexInfo( PINDEX_DATA piData, char * szIndexFlag )
{
	piData->nIndexUnit = INDEX_UNIT_DEF;
	piData->nIndexMode = INDEX_UNIT_DEF;
	
	if( 0 == strcmp( szIndexFlag, IFLAG_TIME_YEAR ) )
	{
		/* 按年按时间组织 */
		piData->nIndexUnit = INDEX_UNIT_YEAR;
		piData->nIndexMode = INDEX_MODE_TIME;
	}
	else if( 0 == strcmp( szIndexFlag, IFLAG_TIME_MONTH ) )
	{
		/* 按月按时间组织 */
		piData->nIndexUnit = INDEX_UNIT_MONTH;
		piData->nIndexMode = INDEX_MODE_TIME;
	}
	else if( 0 == strcmp( szIndexFlag, IFLAG_TIME_DAY ) )
	{
		/* 按日按时间组织 */
		piData->nIndexUnit = INDEX_UNIT_DAY;
		piData->nIndexMode = INDEX_MODE_TIME;
	}
	else if( 0 == strcmp( szIndexFlag, IFLAG_TIME_HOUR ) )
	{
		/* 按小时按时间组织 */
		piData->nIndexUnit = INDEX_UNIT_HOUR;
		piData->nIndexMode = INDEX_MODE_TIME;
	}
	else if( 0 == strcmp( szIndexFlag, IFLAG_USER_YEAR ) )
	{
		/* 按年按用户组织 */
		piData->nIndexUnit = INDEX_UNIT_YEAR;
		piData->nIndexMode = INDEX_MODE_USER;
	}
	else if( 0 == strcmp( szIndexFlag, IFLAG_USER_MONTH ) )
	{
		/* 按月按用户组织 */
		piData->nIndexUnit = INDEX_UNIT_MONTH;
		piData->nIndexMode = INDEX_MODE_USER;
	}
	else if( 0 == strcmp( szIndexFlag, IFLAG_USER_DAY ) )
	{
		/* 按日按用户组织 */
		piData->nIndexUnit = INDEX_UNIT_DAY;
		piData->nIndexMode = INDEX_MODE_USER;
	}
	else if( 0 == strcmp( szIndexFlag, IFLAG_USER_HOUR ) )
	{
		/* 按小时按用户组织 */
		piData->nIndexUnit = INDEX_UNIT_HOUR;
		piData->nIndexMode = INDEX_MODE_USER;
	}
	else
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效的 IndexFlag [%s] !\n\n", szIndexFlag );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: CreateIndexName
description: 获取索引文件结构信息
Input: piData: 描述系统全局结构的结构体
       picRecord: 索引文件控制信息
       nIndexDay: 初始化时间, 日
       nIndexHour: 初始化时间, 小时
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int CreateIndexName( PINDEX_DATA piData, PICTRL_RECORD picRecord, int nIndexDay, int nIndexHour )
{
	memset( piData->szIndexName, 0, sizeof( piData->szIndexName ) );
	
	if( INDEX_UNIT_YEAR == piData->nIndexUnit )
	{
		/* 索引文件以年为基本时间单位 */
		if( IsGlobalTime( picRecord ) )
		{
			sprintf( piData->szIndexName, "%s.%s.index", 
												picRecord->szIndexType,
												piData->szIndexYear );
		}
		else
		{
			sprintf( piData->szIndexName, "%s.%s%s.index", 
												picRecord->szIndexType,
												picRecord->szIndexStartTime, 
												picRecord->szIndexEndTime );
		}
	}
	else if( INDEX_UNIT_MONTH == piData->nIndexUnit )
	{
		/* 索引文件以月为基本时间单位 */
		if( IsGlobalTime( picRecord ) )
		{
			sprintf( piData->szIndexName, "%s.%s%s.index", 
												picRecord->szIndexType,
												piData->szIndexYear, 
												piData->szIndexMonth );
		}
		else
		{
			sprintf( piData->szIndexName, "%s.%s%s%s.index", 
												picRecord->szIndexType,
												piData->szIndexYear, 
												picRecord->szIndexStartTime, 
												picRecord->szIndexEndTime );
		}
	}
	else if( INDEX_UNIT_DAY == piData->nIndexUnit )
	{
		/* 索引文件以天为基本时间单位 */
		if( IsGlobalTime( picRecord ) )
		{
			sprintf( piData->szIndexName, "%s.%s%s%02d.index", 
												picRecord->szIndexType,
												piData->szIndexYear, 
												piData->szIndexMonth,
												nIndexDay );
		}
		else
		{
			sprintf( piData->szIndexName, "%s.%s%s%s%s.index", 
												picRecord->szIndexType,
												piData->szIndexYear, 
												piData->szIndexMonth,
												picRecord->szIndexStartTime, 
												picRecord->szIndexEndTime );
		}
	}
	else if( INDEX_UNIT_HOUR == piData->nIndexUnit )
	{
		/* 索引文件以小时为基本时间单位 */
		if( IsGlobalTime( picRecord ) )
		{
			sprintf( piData->szIndexName, "%s.%s%s%02d%02d.index", 
												picRecord->szIndexType,
												piData->szIndexYear, 
												piData->szIndexMonth,
												nIndexDay,
												nIndexHour );
		}
		else
		{
			sprintf( piData->szIndexName, "%s.%s%s%02d%s%s.index", 
												picRecord->szIndexType,
												piData->szIndexYear, 
												piData->szIndexMonth,
												nIndexDay,
												picRecord->szIndexStartTime, 
												picRecord->szIndexEndTime );
		}
	}
	else
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效的 IndexFlag [%s] !\n\n", picRecord->szIndexFlag );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetBlockSize
description: 获取索引数据块大小
Input: pbcRecord: 索引数据块控制信息
Output:
Return: 索引数据块大小
others:
***********************************************************/

int GetBlockSize( PBCTRL_RECORD pbcRecord )
{
	if( 0 == strcmp( pbcRecord->szBlockUnit, BLOCK_UNIT_KBYTE ) )
	{
		/* 以 K 为单位 */
		return ( pbcRecord->nBlockSize * 1024 );
	}
	else if( 0 == strcmp( pbcRecord->szBlockUnit, BLOCK_UNIT_MBYTE ) )
	{
		/* 以 M 为单位 */
		return ( pbcRecord->nBlockSize * 1024 * 1024 );
	}
	else if( 0 == strcmp( pbcRecord->szBlockUnit, BLOCK_UNIT_GBYTE ) )
	{
		/* 以 G 为单位 */
		/*
		return ( pbcRecord->nBlockSize * 1024 * 1024 * 1024 );
		*/
		
		return -1;
	}
	else
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效的 Block Unit [%s] !\n", pbcRecord->szBlockUnit );
		return -1;
	}
}

/********************************************************** 
function: GetBlockHeadInfo
description: 获取索引数据块头部信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetBlockHeadInfo( PINDEX_DATA piData )
{
	memset( piData->szBlockHead      , 0, sizeof( piData->szBlockHead      ) );
	memset( piData->szBlockStartTime , 0, sizeof( piData->szBlockStartTime ) );
	memset( piData->szBlockEndTime   , 0, sizeof( piData->szBlockEndTime   ) );
	memset( piData->szUserSerial     , 0, sizeof( piData->szUserSerial     ) );
	memset( piData->szBlockFlag      , 0, sizeof( piData->szBlockFlag      ) );
	memset( piData->szBlockSize      , 0, sizeof( piData->szBlockSize      ) );
	
	memcpy( piData->szBlockHead, piData->szBlock, BLOCK_HEAD_LEN );
	piData->szBlockHead[BLOCK_HEAD_LEN] = 0;

	memcpy( piData->szBlockStartTime, piData->szBlockHead, BLOCK_TSTART_LEN );
	piData->szBlockStartTime[BLOCK_TSTART_LEN] = 0;
	
	memcpy( piData->szBlockEndTime, piData->szBlockHead + BLOCK_TSTART_LEN, BLOCK_TEND_LEN );
	piData->szBlockEndTime[BLOCK_TEND_LEN] = 0;
	
	memcpy( piData->szUserSerial, piData->szBlock, BLOCK_TSTART_LEN + BLOCK_TEND_LEN );
	piData->szUserSerial[BLOCK_TSTART_LEN + BLOCK_TEND_LEN] = 0;
	
	memcpy( piData->szBlockFlag, piData->szBlockHead + BLOCK_TSTART_LEN + BLOCK_TEND_LEN, BLOOK_FLAG_LEN );
	piData->szBlockFlag[BLOOK_FLAG_LEN] = 0;
	
	memcpy( piData->szBlockSize, piData->szBlockHead + BLOCK_TSTART_LEN + BLOCK_TEND_LEN + BLOOK_FLAG_LEN, BLOCK_SIZE_LEN );
	piData->szBlockSize[BLOCK_SIZE_LEN] = 0;
		
	return MY_SUCCEED;
}

/********************************************************** 
function: CreateBlockHead
description: 生成索引数据块头信息
Input: piData: 描述系统全局结构的结构体
       picRecord: 索引文件控制信息
       pbcRecord: 索引数据块控制信息
       nBlockNum: 索引数据块序号
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int CreateBlockHead( PINDEX_DATA piData, PICTRL_RECORD picRecord, PBCTRL_RECORD pbcRecord, int nBlockNum )
{
	int nBaseNum, nBlockNo;
	int nStartTime, nEndTime, lBlockSize;
	
	lBlockSize = 0;
	
	/* 按用户分配索引数据块 */
	if( INDEX_MODE_USER == piData->nIndexMode )
	{
		sprintf( piData->szBlockHead, "%010d%1.1s%08d\n", nBlockNum, BLOCK_FLAG_AVAIL, 0 );
		
		return MY_SUCCEED;
	}
	
	/* 按时间分配索引数据块 */
	
	nBaseNum = pbcRecord->nBlockNum / piData->nTimeCount;
	
	nBlockNo = ( ( nBlockNum + 1 ) % nBaseNum ) ? ( ( nBlockNum + 1 ) % nBaseNum ) : nBaseNum ;

	nStartTime = piData->lTotalTime / nBaseNum * ( nBlockNo - 1 );
	nEndTime   = piData->lTotalTime / nBaseNum * nBlockNo - 1;

	sprintf( piData->szBlockHead, "%05d%05d%1.1s%08ld\n", nStartTime, nEndTime, BLOCK_FLAG_AVAIL, 0 );
	
	return MY_SUCCEED;
}

/********************************************************** 
function: CheckBlockRecord
description: 校验索引数据块控制记录有效性
Input: piData: 描述系统全局结构的结构体
       picRecord: 索引文件控制信息
       pbcRecord: 索引数据块控制信息
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int CheckBlockRecord( PINDEX_DATA piData, PICTRL_RECORD picRecord, PBCTRL_RECORD pbcRecord )
{
	/* 按用户分配索引数据块 */
	if( INDEX_MODE_USER == piData->nIndexMode )
	{
		if( 0 != ( HEAD_USER_COUNT % pbcRecord->nBlockNum ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "HeadCount [%s] 不是 BlockNum [%d] 的整数倍 !\n", HEAD_USER_COUNT, pbcRecord->nBlockNum );
			return MY_FAIL;
		}
		
		piData->nUserCount = HEAD_USER_COUNT / pbcRecord->nBlockNum;
		
		return MY_SUCCEED;
	}
	
	/* 按时间分配索引数据块 */
	
	if( INDEX_UNIT_HOUR == piData->nIndexUnit )
	{
		/* 按小时组织 */
		if( 0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_SEC ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_MIN ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_HOUR ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "BlockFlag [%s] 与 IndexFlag [%s] 不匹配 !\n", pbcRecord->szBlockFlag, picRecord->szIndexFlag );
			return MY_FAIL;
		}
	}
	else if( INDEX_UNIT_DAY == piData->nIndexUnit )
	{
		/* 按天组织 */
		if( 0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_SEC ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_MIN ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_HOUR ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_DAY ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "BlockFlag [%s] 与 IndexFlag [%s] 不匹配 !\n", pbcRecord->szBlockFlag, picRecord->szIndexFlag );
			return MY_FAIL;
		}
	}
	else if( INDEX_UNIT_MONTH == piData->nIndexUnit )
	{
		/* 按月组织 */
		if( 0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_SEC ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_MIN ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_HOUR ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_DAY ) 
		&&  0 != strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_MON ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "BlockFlag [%s] 与 IndexFlag [%s] 不匹配 !\n", pbcRecord->szBlockFlag, picRecord->szIndexFlag );
			return MY_FAIL;
		}
	}
	
	/* 计算基本时间单位个数 */
	
	if( IsGlobalTime( picRecord ) )
	{
		piData->nTimeCount = 1;
	}
	else
	{
		piData->nTimeCount = atoi( pbcRecord->szBlockEndTime ) - atoi( pbcRecord->szBlockStartTime ) + 1;
	}
	
	/* 校验索引数据块数目取值 */
	
	if( 0 != ( pbcRecord->nBlockNum % piData->nTimeCount ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "BlockNum [%d] 不是 TimeCount [%d] 的整数倍!\n", pbcRecord->nBlockNum, piData->nTimeCount );
		return MY_FAIL;
	}
	
	/* 校验时间数目取值 */
	
	if( 0 != ( piData->lTotalTime % ( pbcRecord->nBlockNum / piData->nTimeCount ) ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "TotalTime [%ld] 不是 BlockNum [%d] / TimeCount [%d] 的整数倍!\n", piData->lTotalTime, pbcRecord->nBlockNum, piData->nTimeCount );
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetTotalTime
description: 获取时间数目
Input: piData: 描述系统全局结构的结构体
       pbcRecord: 索引数据块控制信息
Output:
Return: 时间数目
others:
***********************************************************/

long GetTotalTime( PINDEX_DATA piData, PBCTRL_RECORD pbcRecord )
{
	long lTotalTime;
	
	lTotalTime = 0;

	/* 索引文件级时间数目 */
	if( INDEX_UNIT_HOUR == piData->nIndexUnit )
	{
		lTotalTime = 1;
	}
	else if( INDEX_UNIT_DAY == piData->nIndexUnit )
	{
		lTotalTime = 24;
	}
	else if( INDEX_UNIT_MONTH == piData->nIndexUnit )
	{
		lTotalTime = 24 * 31;
	}
	else if( INDEX_UNIT_YEAR == piData->nIndexUnit )
	{
		lTotalTime = 24 * 31 * 12;
	}

	/* 索引数据块级时间数目 */
	if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_SEC ) )
	{
		lTotalTime = lTotalTime * 3600;
	}
	else if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_MIN ) )
	{
		lTotalTime = lTotalTime * 60;
	}
	else if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_HOUR ) )
	{
		lTotalTime = lTotalTime;
	}
	else if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_DAY ) )
	{
		lTotalTime = lTotalTime / 24;
	}
	else if( 0 == strcmp( pbcRecord->szBlockFlag, BLOCK_FLAG_MON ) )
	{
		lTotalTime = lTotalTime / 24 / 31;
	}

	return lTotalTime;
}

/********************************************************** 
function: FillIndexFile
description: 填充索引初始化文件
Input: piData: 描述系统全局结构的结构体
       picRecord: 索引文件控制信息
       nIndexDay: 初始化时间, 天
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int FillIndexFile( PINDEX_DATA piData, PICTRL_RECORD picRecord, int nIndexDay )
{
	PBCTRL_DATA pbcData;
	PBCTRL_RECORD pbcRecord;
	
	long lTotalTime;
	int nLoop, nBlockNum;
	
	pbcData = &(piData->bcData);
	pbcRecord = pbcData->pbcRecord;
	
	piData->szBlock = NULL;

	/* 遍历 block_control_table */
	for( nLoop = 0; nLoop < pbcData->nRecCount; nLoop++, pbcRecord++ )
	{
		if( 0 == strcmp( pbcRecord->szIndexType, picRecord->szIndexType )
		&&  0 == strcmp( pbcRecord->szBlockLink, picRecord->szBlockLink ) )
		{
			/* 获取时间总数 */
			piData->lTotalTime = GetTotalTime( piData, pbcRecord );
			if( 0 >= piData->lTotalTime )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引数据块时间数目失败!\n" );
				return MY_FAIL;
			}
			
			/* printf( "TotalTime = %ld\n", piData->lTotalTime ); */
			
			/* 校验索引数据块控制信息 */
			if( MY_SUCCEED != CheckBlockRecord( piData, picRecord, pbcRecord ) )
			{
				return MY_FAIL;
			}
			
			/* 获取索引数据块尺寸 */
			piData->lBlockSize = GetBlockSize( pbcRecord );
			if( 0 >= piData->lBlockSize )
			{
				return MY_FAIL;
			}

			/* 申请索引数据块 */
			piData->szBlock = ( char * ) malloc( piData->lBlockSize + 1 );
			if( NULL == piData->szBlock )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "申请保存索引数据块的内存空间失败!\n" );
				return MY_FAIL;
			}
			
			memset( piData->szBlock, BLOCK_FILL_CHAR, piData->lBlockSize );
			piData->szBlock[piData->lBlockSize] = 0;
			
			if( -1 == fseek( piData->fpIndex, 0, SEEK_END ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "定位索引文件尾部失败!\n" );
				return MY_FAIL;
			}
			
			/* 依次初始化索引文件中的每个索引数据块 */
			for( nBlockNum = 0; nBlockNum < pbcRecord->nBlockNum; nBlockNum++ )
			{
				memset( piData->szBlockHead, 0, sizeof( piData->szBlockHead ) );
				
				/* 生成索引数据块头信息 */
				if( MY_SUCCEED != CreateBlockHead( piData, picRecord, pbcRecord, nBlockNum ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引数据块头信息失败!\n" );
					return MY_FAIL;
				}
				
				/* printf( "BlockHead = %s", piData->szBlockHead ); */

				memcpy( piData->szBlock, piData->szBlockHead, BLOCK_HEAD_LEN );
				memcpy( piData->szBlock + piData->lBlockSize - 1, "\n", 1 );
				
				/* 向索引文件写入索引数据块 */
				if( piData->lBlockSize != fwrite( piData->szBlock, sizeof( char ), piData->lBlockSize, piData->fpIndex ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引数据块写入失败!\n" );
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
					return MY_FAIL;
				}
			}
			
			/* 释放申请的空间 */
			if( NULL != piData->szBlock )
			{
				free( piData->szBlock );
				piData->szBlock = NULL;
			}
			
			break;
		}
	}

	/* 未找到匹配的控制信息 */
	if( nLoop >= pbcData->nRecCount )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "未找到匹配的 Block Control Info !\n" );
		/* DebugOutIndexControlRecord( picRecord ); */
		return MY_FAIL;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: CreateIndexFile
description: 生成索引文件
Input: piData: 描述系统全局结构的结构体
       picRecord: 索引文件控制信息
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int CreateIndexFile( PINDEX_DATA piData, PICTRL_RECORD picRecord )
{
	PBCTRL_DATA pbcData;
	
	char szLastDay[DATE_YEAR_LEN + DATE_MON_LEN + DATE_DAY_LEN + 1];
	char szIndexFile[MAX_PATH_LEN + 1];
	
	int nMonth, nLastMonth, nDay, nLastDay, nHour, nLastHour;
	int nLoop;

	/* 生成每个月的索引文件 */
	for( nMonth = 1; nMonth <= 12; nMonth++ )
	{
		/* 如果指定月份, 仅处理指定月份 */
		if( nMonth != atoi( piData->szIndexMonth ) )
		{
			continue;
		}

		if( 0 != *(piData->szIndexDay) )
		{
			nDay = atoi( piData->szIndexDay );
			nLastDay = nDay;
		}
		else
		{
			nDay = 1;
			nLastDay = 31;
			
			/*
			GetMonthLastDay( szLastDay, piData->szIndexDate );
			nLastDay = atoi( szLastDay + DATE_YEAR_LEN + DATE_MON_LEN );
			*/
			
			if( INDEX_UNIT_DAY == piData->nIndexUnit )
			{
				if( !IsGlobalTime( picRecord ) )
				{
					nDay = atoi( picRecord->szIndexStartTime );
					nLastDay = atoi( picRecord->szIndexEndTime );
				}
			}
		}
		
		/* 如果指定天, 仅处理指定天 */
		for(  ; nDay <= nLastDay; nDay++ )
		{
			if( 0 != *(piData->szIndexDay) )
			{
				if( nDay != atoi( piData->szIndexDay ) )
				{
					continue;
				}
			}
			
			if( 0 != *(piData->szIndexHour) )
			{
				nHour = atoi( piData->szIndexHour );
				nLastHour = nHour;
			}
			else
			{
				nHour = 0;
				nLastHour = 23;
				
				if( !IsGlobalTime( picRecord ) )
				{
					nHour = atoi( picRecord->szIndexStartTime );
					nLastHour = atoi( picRecord->szIndexEndTime );
				}
			}
			
			/* printf( "Month = %d, Day = %d, LastDay = %d, Hour = %d, LastHour = %d\n", nMonth, nDay, nLastDay, nHour, nLastHour ); */
			
			for(  ; nHour <= nLastHour; nHour++ )
			{
				/* 如果指定小时, 仅处理指定小时 */
				if( 0 != *(piData->szIndexHour) )
				{
					if( nHour != atoi( piData->szIndexHour ) )
					{
						continue;
					}
				}
				
				/* 生成索引文件名 */
				if( MY_SUCCEED != CreateIndexName( piData, picRecord, nDay, nHour ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引文件名失败!\n\n" );
					return MY_FAIL;
				}
				
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "生成索引文件 %s !\n", piData->szIndexName );

				memset( szIndexFile, 0, sizeof( szIndexFile ) );
				
				/* 定位索引文件存储路径 */
				if( 0 == *(piData->iCmd.szIndexPath) )
				{
					sprintf( szIndexFile, "%s/%s", picRecord->szIndexDir, piData->szIndexName );
				}
				else
				{
					sprintf( szIndexFile, "%s/%s", piData->iCmd.szIndexPath, piData->szIndexName );
				}
/*	
				if( FileIsExist( szIndexFile ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "索引文件 %s 已存在!\n\n", szIndexFile );
					return MY_FAIL;
				}
*/
				/* 打开索引文件 */
				piData->fpIndex = fopen( szIndexFile, "w" );
				if( NULL == piData->fpIndex )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "打开索引文件 %s 失败!\n\n", szIndexFile );
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
					return MY_FAIL;
				}
				
				/* 填充索引文件 */
				if( MY_SUCCEED != FillIndexFile( piData, picRecord, nDay ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "填充索引文件失败!\n\n" );
					return MY_FAIL;
				}
				
				/* 关闭索引文件 */
				if( NULL != piData->fpIndex )
				{
					fclose( piData->fpIndex );
					piData->fpIndex = NULL;
				}
				
				/* 全局配置, 每小时一个文件 */
				if( INDEX_UNIT_HOUR == piData->nIndexUnit )
				{
					if( !IsGlobalTime( picRecord ) )
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			
			/* 全局配置, 每天一个文件 */
			if( INDEX_UNIT_DAY == piData->nIndexUnit )
			{
				if( !IsGlobalTime( picRecord ) )
				{
					break;
				}
			}
			else if( INDEX_UNIT_HOUR != piData->nIndexUnit )
			{
				break;
			}
		}
	}

	return MY_SUCCEED;
}

/********************************************************** 
function: IsInitRecord
description: 是否为索引文件控制记录
Input: piData: 描述系统全局结构的结构体
	   picRecord: 索引文件控制信息
Output:
Return: MY_TRUE: 是 MY_FALSE: 否
others:
***********************************************************/

int IsInitRecord( PINDEX_DATA piData, PICTRL_RECORD picRecord )
{
	/* 全局配置 */
	if( IsGlobalTime( picRecord ) )
	{
		return MY_TRUE;
	}
	
	/* 检验时间跨度 */	
	if( INDEX_UNIT_YEAR == piData->nIndexUnit )
	{
		/* 按年组织 */
		if( 0 < strcmp( picRecord->szIndexStartTime, piData->szIndexYear )
		||  0 > strcmp( picRecord->szIndexEndTime, piData->szIndexYear ) )
		{
			return MY_FALSE;
		}
	}
	else if( INDEX_UNIT_MONTH == piData->nIndexUnit )
	{
		/* 按月组织 */
		if( 0 < strcmp( picRecord->szIndexStartTime, piData->szIndexMonth )
		||  0 > strcmp( picRecord->szIndexEndTime, piData->szIndexMonth ) )
		{
			return MY_FALSE;
		}
	}
	else if( INDEX_UNIT_DAY == piData->nIndexUnit )
	{
		/* 按天组织 */
		if( 0 != *(piData->szIndexDay) )
		{
			if( 0 < strcmp( picRecord->szIndexStartTime, piData->szIndexDay )
			||  0 > strcmp( picRecord->szIndexEndTime, piData->szIndexDay ) )
			{
				return MY_FALSE;
			}
		}
	}
	else if( INDEX_UNIT_HOUR == piData->nIndexUnit )
	{
		/* 按小时组织 */
		if( 0 != *(piData->szIndexHour) )
		{
			if( 0 < strcmp( picRecord->szIndexStartTime, piData->szIndexHour )
			||  0 > strcmp( picRecord->szIndexEndTime, piData->szIndexHour ) )
			{
				return MY_FALSE;
			}
		}
	}
	
	return MY_TRUE;;
}

/********************************************************** 
function: InitIndexFile
description: 初始化指定的索引文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int InitIndexFile( PINDEX_DATA piData )
{
	PINIT_CMD piCmd;
	PICTRL_DATA picData;
	PICTRL_RECORD picRecord;
	
	int nLoop;
	
	piCmd = &(piData->iCmd);
	picData = &(piData->icData);
	
	piData->fpIndex = NULL;
	
	memset( piData->szIndexYear, 0, sizeof( piData->szIndexYear ) );
	memset( piData->szIndexMonth, 0, sizeof( piData->szIndexMonth ) );
	memset( piData->szIndexDay, 0, sizeof( piData->szIndexDay ) );
	memset( piData->szIndexHour, 0, sizeof( piData->szIndexHour ) );
	
	/* 获取初始化时间类型 */
	
	/* 初始化时间精确至小时 */
	if( IsHourDate( piCmd->szInitDate ) )
	{
		strncpy( piData->szIndexHour, piCmd->szInitDate + DATE_YEAR_LEN + DATE_MON_LEN + DATE_DAY_LEN, DATE_HOUR_LEN );
		piData->szIndexHour[DATE_HOUR_LEN] = 0;
		
		strncpy( piData->szIndexDay, piCmd->szInitDate + DATE_YEAR_LEN + DATE_MON_LEN, DATE_DAY_LEN );
		piData->szIndexDay[DATE_DAY_LEN] = 0;
	}
	
	/* 初始化时间精确至天 */
	if( IsDayDate( piCmd->szInitDate ) )
	{
		strncpy( piData->szIndexDay, piCmd->szInitDate + DATE_YEAR_LEN + DATE_MON_LEN, DATE_DAY_LEN );
		piData->szIndexDay[DATE_DAY_LEN] = 0;
	}

	strncpy( piData->szIndexMonth, piCmd->szInitDate + DATE_YEAR_LEN, DATE_MON_LEN );
	piData->szIndexDay[DATE_MON_LEN] = 0;

	strncpy( piData->szIndexYear, piCmd->szInitDate, DATE_YEAR_LEN );
	piData->szIndexYear[DATE_YEAR_LEN] = 0;
	
	memset( piData->szIndexDate, 0, sizeof( piData->szIndexDate ) );
	
	/* 生成索引文件初始化时间 */
	sprintf( piData->szIndexDate, "%s%s%s%s", piData->szIndexYear, piData->szIndexMonth, piData->szIndexDay, piData->szIndexHour );
	
	printf( "IndexDate = [%s]\n\n", piData->szIndexDate );

	picRecord = picData->picRecord;

	/* 遍历 index_control_table */
	for( nLoop = 0; nLoop < picData->nRecCount; nLoop++, picRecord++ )
	{
		if( 0 != strcmp( piCmd->szIndexType, "*" ) )
		{
			if( 0 != strcmp( picRecord->szIndexType, piCmd->szIndexType ) )
			{
				continue;
			}
		}
		
		/* 校验配置生效时间 */
		if( 0 >= strncmp( picRecord->szEffectStartTime, piData->szIndexDate, 
										min( strlen( picRecord->szEffectStartTime ), strlen( piData->szIndexDate ) ) )
		&&  0 <= strncmp( picRecord->szEffectEndTime, piData->szIndexDate, 
										min( strlen( picRecord->szEffectEndTime ), strlen( piData->szIndexDate ) ) ) )
		{
			/* printf( "%s - %s - %s\n", picRecord->szEffectStartTime, piData->szIndexDate, picRecord->szEffectEndTime ); */
			
			/* 获取索引文件信息 */
			if( MY_SUCCEED != GetIndexInfo( piData, picRecord->szIndexFlag ) )
			{
				continue;
			}
			
			/* 校验索引文件控制记录 */
			if( !IsInitRecord( piData, picRecord ) )
			{
				continue;
			}
			
			/* 生成索引文件 */
			if( MY_SUCCEED != CreateIndexFile( piData, picRecord ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "生成索引文件失败!\n\n" );
				return MY_FAIL;	
			}
		}
	}
	
	return MY_SUCCEED;
}
