

/********************************************************************
copyright (C), 1995-2004, Si-Tech Information Technology Ltd. 
file_name: amain.c   
author: 张凡 version: （V1.00） date: （2004－08－20）
description: 索引文件分析系统调度
others:
history: 1.date: 修改时间 version: 版本（V1.00）author: 作者
			modification: 修改内容
		 2. ... 
********************************************************************/


#include "ddef.h"


/********************************************************** 
function: DebugOutAnaCmd
description: 输出运行指令信息
Input:	psCmd: 描述运行指令各项内容的结构体
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutAnaCmd( PANA_CMD paCmd )
{
	char bRunFlag;
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, 
"索引文件初始化运行参数内容如下\n\n\t=== Ana Index Run Info ===\n\n\
\tLogDir    = [%s]\n\tHostName  = [%s]\n\tAnaDate   = [%s]\n\tLoginFile = [%s]\n\
\tServer    = [%s]\n\tIndexType = [%s]\n\tRetFile   = [%s]\n\tIndexPath = [%s]\n\
\n\t=== Ana Index Run Info ===\n\n",
				paCmd->szLogDir, paCmd->szHostName, paCmd->szAnaDate, 
				paCmd->szRetFile, paCmd->szLoginFile, paCmd->szServer, 
				paCmd->szIndexType, paCmd->szIndexPath );

	return MY_SUCCEED;
}

/********************************************************** 
function: CheckAnaCmd
description: 检验运行指令合法性
Input: paCmd: 描述运行指令各项内容的结构体
Output:
Return: MY_SUCCEED 合法 MY_FAIL 不合法
others:
***********************************************************/

int CheckAnaCmd( PANA_CMD paCmd )
{
	/* 校验日志目录 */
	if( !IsDir( paCmd->szLogDir ) )
	{
		fprintf( stderr, "gen\texit\t无效的运行日志文件路径\n" );
		return MY_FAIL;
	}
	
	/* 校验索引文件分析时间 */
	if( !IsMonthDate( paCmd->szAnaDate ) && !IsDayDate( paCmd->szAnaDate ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的索引文件分析时间 [%s] !\n\n", paCmd->szAnaDate );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "索引文件分析时间 FORMAT: YYYYMM / YYYYMMDD !\n\n" );
		return MY_FAIL;
	}
	
	/* 获取登陆口令信息 */
	if( MY_SUCCEED != GetLoginInfo( paCmd->szLoginFile, paCmd->szUserName, paCmd->szPassWord ) )
	{
		return MY_FAIL;
	}
	
	/* 初始化索引文件类型 */
	if( 0 == *( paCmd->szIndexType ) )
	{
		strcpy( paCmd->szIndexType, "*" );
	}

	/* 校验索引文件输出目录 */
	if( 0 != *( paCmd->szIndexPath ) )
	{
		if( !IsDir( paCmd->szIndexPath ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的索引文件存放目录!\n\n" );
			return MY_FAIL;
		}
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetAnaCmd
description: 获取运行指令信息
Input: paCmd: 描述运行指令各项内容的结构体
       argc: 运行指令个数
       argv: 保存运行指令内容
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetAnaCmd( PANA_CMD paCmd, int argc, char * argv[] )
{
	extern char * optarg;
	int opt, lflag, hflag, dflag, fflag, sflag, rflag;
		
	lflag = 0;
	hflag = 0;
	dflag = 0;
	fflag = 0;
	sflag = 0;
	rflag = 0;
	
	/* 获取运行程序名称 */
	memset( szBinName, 0, sizeof( szBinName ) );
	GetInDirName( szBinName, argv[0] );
	
	/* 获取运行命令 */
	while( -1 != ( opt = getopt( argc, argv, "L:l:H:h:D:d:F:f:S:s:T:t:P:p:R:r:" ) ) )
	{
		/* 分析运行命令 */
		switch( opt )
		{
			case 'L':
			case 'l':
				lflag = 1;
				strcpy( paCmd->szLogDir, optarg );
				
				strcpy( szLogPath, optarg );
				strcpy( szLogPrefix, "dta" );
				strcpy( szSrcDir, "ana" );
				break;
				
			case 'H':
			case 'h':
				hflag = 1;
				strcpy( paCmd->szHostName, optarg );
				break;
			
			case 'D':
			case 'd':
				dflag = 1;
				strcpy( paCmd->szAnaDate, optarg );
				break;
						
			case 'F':
			case 'f':
				fflag = 1;
				strcpy( paCmd->szLoginFile, optarg );
				break;
				
			case 'S':
			case 's':
				sflag = 1;
				strcpy( paCmd->szServer, optarg );
				break;
				
			case 'T':
			case 't':
				strcpy( paCmd->szIndexType, optarg );
				break;
					
			case 'P':
			case 'p':
				strcpy( paCmd->szIndexPath, optarg );
				break;
			
			case 'R':
			case 'r':
				rflag = 1;
				strcpy( paCmd->szRetFile, optarg );
				break;
				
			default:
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的索引文件分析运行参数 %c !\n", opt );
				break;
		}
	}

	/* 参数有效性检测 */
	if( !( lflag && hflag && dflag && fflag && sflag && rflag ) )
	{
		fprintf( stderr, "\n\n\t[usage]: %s -l Logdir -h Hostname -d anaDate -r Result -f loginFile -s Server [-t indexType] [-p indexPath]\n\n", szBinName );
   		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "索引文件分析运行参数不足!\n\n" );
   		exit(0);
	}
	
	/* 检查运行指令合法性 */
	if( MY_SUCCEED != CheckAnaCmd( paCmd ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的索引文件分析运行参数!\n\n" );
		exit(0);
	}

	DebugOutAnaCmd( paCmd );
	
	return MY_SUCCEED;
}


/********************************************************** 
function: GetBlockInfo
description: 获取索引文件数据块信息
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetBlockInfo( PINDEX_DATA piData )
{
	long lOffset;
	
	piData->nExtend = 0;
	lOffset = piData->lBlockNo * piData->lBlockSize;
	
	GetBlockHeadInfo( piData );
	
	do
	{
		if( -1 == fseek( piData->fpIndex, lOffset, SEEK_SET ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "定位索引数据块位置失败!\n" );
			return MY_FAIL;
		}

		memset( piData->szBlock, 0, piData->lBlockSize * sizeof( char ) );
			
		if( piData->lBlockSize != fread( piData->szBlock, sizeof( char ), piData->lBlockSize, piData->fpIndex ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "读取索引文件数据块失败!\n" );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
			return MY_FAIL;
		}
		
		/* 如果数据块未满, 结束搜索 */
		if( 0 == strcmp( piData->szBlockFlag, BLOCK_FLAG_AVAIL ) )
		{
			piData->lfSpaceUse = (double) (double) atof( piData->szBlockSize ) / (double) piData->lBlockSize;
			break;
		}
		else
		{
			lOffset = atol( piData->szBlockSize ) * 1024;
			piData->nExtend++;
		}
	} while( 0 == strcmp( piData->szBlockFlag, BLOCK_FLAG_FULL ) );
	
	return MY_SUCCEED;
}

/********************************************************** 
function: AnaBlockInfo
description: 分析索引文件数据块信息
Input: piData: 描述系统全局结构的结构体
       picRecord: 索引文件控制信息
       nIndexDay: 索引文件时间, 天
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int AnaBlockInfo( PINDEX_DATA piData, PICTRL_RECORD picRecord, int nIndexDay )
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
			piData->szBlock = ( char * ) malloc( piData->lBlockSize * sizeof( char ) );
			if( NULL == piData->szBlock )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "申请保存索引数据块的内存空间失败!\n" );
				return MY_FAIL;
			}
			
			/* 依次分析索引文件中的每个索引数据块 */
			for( nBlockNum = 0; nBlockNum < pbcRecord->nBlockNum; nBlockNum++ )
			{
				piData->lBlockNo = nBlockNum;
				
				if( MY_SUCCEED != GetBlockInfo( piData ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引文件数据块信息失败!\n" );
				}
				

				/* 输出索引数据块分析结果 */	
				if( -1 == fprintf( piData->fpResult, "%s %02d %s %6d %d %3.2lf\n", 
															pbcRecord->szIndexType, nIndexDay, pbcRecord->szBlockLink, 
															nBlockNum + 1, piData->nExtend, piData->lfSpaceUse ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "输出索引数据块分析结果失败!\n" );
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
function: AnaSpecIndexFile
description: 分析索引文件
Input: piData: 描述系统全局结构的结构体
       picRecord: 索引文件控制信息
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int AnaSpecIndexFile( PINDEX_DATA piData, PICTRL_RECORD picRecord )
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
			
			nHour = 0;
			nLastHour = 23;
				
			if( !IsGlobalTime( picRecord ) )
			{
				nHour = atoi( picRecord->szIndexStartTime );
				nLastHour = atoi( picRecord->szIndexEndTime );
			}
			
			/* printf( "Month = %d, Day = %d, LastDay = %d, Hour = %d, LastHour = %d\n", nMonth, nDay, nLastDay, nHour, nLastHour ); */
	
			for(  ; nHour <= nLastHour; nHour++ )
			{
				/* 生成索引文件名 */
				if( MY_SUCCEED != CreateIndexName( piData, picRecord, nDay, nHour ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引文件名失败!\n\n" );
					return MY_FAIL;
				}
	
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "分析索引文件 %s !\n", piData->szIndexName );
	
				memset( szIndexFile, 0, sizeof( szIndexFile ) );
				
				/* 定位索引文件存储路径 */
				if( 0 == *(piData->aCmd.szIndexPath) )
				{
					sprintf( szIndexFile, "%s/%s", picRecord->szIndexDir, piData->szIndexName );
				}
				else
				{
					sprintf( szIndexFile, "%s/%s", piData->aCmd.szIndexPath, piData->szIndexName );
				}
	
				/* 打开索引文件 */
				piData->fpIndex = fopen( szIndexFile, "r" );
				if( NULL == piData->fpIndex )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "打开索引文件 %s 失败!\n\n", szIndexFile );
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
					return MY_FAIL;
				}
				
				/* 填充索引文件 */
				if( MY_SUCCEED != AnaBlockInfo( piData, picRecord, nDay ) )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "分析索引文件数据块失败!\n\n" );
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
function: AnaIndexFile
description: 分析指定的索引文件
Input: piData: 描述系统全局结构的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int AnaIndexFile( PINDEX_DATA piData )
{
	PANA_CMD paCmd;
	PICTRL_DATA picData;
	PICTRL_RECORD picRecord;

	int nLoop;
	
	paCmd = &(piData->aCmd);
	picData = &(piData->icData);
	
	piData->fpIndex = NULL;
	
	memset( piData->szIndexYear, 0, sizeof( piData->szIndexYear ) );
	memset( piData->szIndexMonth, 0, sizeof( piData->szIndexMonth ) );
	memset( piData->szIndexDay, 0, sizeof( piData->szIndexDay ) );
	
	/* 分析时间精确至天 */
	if( IsDayDate( paCmd->szAnaDate ) )
	{
		strncpy( piData->szIndexDay, paCmd->szAnaDate + DATE_YEAR_LEN + DATE_MON_LEN, DATE_DAY_LEN );
		piData->szIndexDay[DATE_DAY_LEN] = 0;
	}

	strncpy( piData->szIndexMonth, paCmd->szAnaDate + DATE_YEAR_LEN, DATE_MON_LEN );
	piData->szIndexDay[DATE_MON_LEN] = 0;

	strncpy( piData->szIndexYear, paCmd->szAnaDate, DATE_YEAR_LEN );
	piData->szIndexYear[DATE_YEAR_LEN] = 0;
	
	memset( piData->szIndexDate, 0, sizeof( piData->szIndexDate ) );
	
	/* 生成索引文件分析时间 */
	sprintf( piData->szIndexDate, "%s%s%s", piData->szIndexYear, piData->szIndexMonth, piData->szIndexDay );
	
	printf( "IndexDate = [%s]\n\n", piData->szIndexDate );
	
	/* 打开分析结果文件 */
	printf("======[%s]\n",piData->aCmd.szRetFile);
	piData->fpResult = fopen( piData->aCmd.szRetFile, "w" );
	if( NULL == piData->fpResult )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "分析结果文件 %s 打开失败!\n", piData->fpResult );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "ErrorInfo: %d : %s\n", errno, strerror( errno ) );
		return MY_FAIL;	
	}
	
	picRecord = picData->picRecord;
	
	/* 遍历 index_control_table */
	for( nLoop = 0; nLoop < picData->nRecCount; nLoop++, picRecord++ )
	{
		if( 0 != strcmp( paCmd->szIndexType, "*" ) )
		{
			if( 0 != strcmp( picRecord->szIndexType, paCmd->szIndexType ) )
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
			
			/* 分析指定索引文件 */
			if( MY_SUCCEED != AnaSpecIndexFile( piData, picRecord ) )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "分析索引文件失败!\n\n" );
				return MY_FAIL;	
			}
		}
	}
	
	if( NULL != piData->fpResult )
	{
		fclose( piData->fpResult );
		piData->fpResult = NULL;
	}
	
	return MY_SUCCEED;
}

/**********************************************************
function: main
description: 主控函数
Input: argc: 参数数目
       argv: 参数值
Output:
Return:
others:
***********************************************************/

int main( int argc, char * argv[ ] )
{
	INDEX_DATA iData;
	
	memset( &iData, 0, sizeof( INDEX_DATA ) );
	memset( &(iData.aCmd), 0, sizeof( ANA_CMD ) );
	
	/* 获取运行指令 */
	GetAnaCmd( &(iData.aCmd), argc, argv );
	
	strcpy( iData.szHostName, iData.aCmd.szHostName );
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "启动索引文件分析系统 !\n\n" );
	
	/* 连接数据库 */
	ConnectDataBase( (iData.aCmd).szUserName, (iData.aCmd).szPassWord, (iData.aCmd).szServer );
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "获取索引文件控制信息!\n\n" );
	
	/* 获取索引文件控制信息 */
	if( MY_SUCCEED != GetCtrlInfo( &iData ) )
	{
		DisConnectDataBase( );
		FreeCtrlData( &iData );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "获取索引文件控制信息失败!\n\n" );
	}
	
	/* 断开数据库连接 */
	DisConnectDataBase( );
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "分析 [%s] 的 [%s] 索引文件!\n\n", iData.aCmd.szAnaDate, iData.aCmd.szIndexType );
	
	/* 分析索引文件 */
	if( MY_SUCCEED != AnaIndexFile( &iData ) )
	{
		FreeCtrlData( &iData );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "分析索引文件失败!\n\n" );
	}
	
	/* 释放申请的内存空间 */
	FreeCtrlData( &iData );
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "索引文件分析系统运行完毕, 成功退出 !\n\n" );
	
	return 0;
}
