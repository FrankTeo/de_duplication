

/********************************************************************
copyright (C), 1995-2004, Si-Tech Information Technology Ltd. 
file_name: imain.c  
author: 张凡 version: （V1.00） date: （2004－08－20）
description: 索引文件初始化系统调度
others:
history: 1.date: 修改时间 version: 版本（V1.00）author: 作者
			modification: 修改内容
		 2. ... 
********************************************************************/


#include "ddef.h"


/********************************************************** 
function: DebugOutInitCmd
description: 输出运行指令信息
Input:	psCmd: 描述运行指令各项内容的结构体
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutInitCmd( PINIT_CMD piCmd )
{
	char bRunFlag;
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, 
"索引文件初始化运行参数内容如下\n\n\t=== Init Index Run Info ===\n\n\
\tLogDir    = [%s]\n\tHostName  = [%s]\n\tInitDate  = [%s]\n\tLoginFile = [%s]\n\
\tServer    = [%s]\n\tIndexType = [%s]\n\tIndexPath = [%s]\n\n\t=== Init Index Run Info ===\n\n",
				piCmd->szLogDir, piCmd->szHostName, piCmd->szInitDate, piCmd->szLoginFile, 
				piCmd->szServer, piCmd->szIndexType, piCmd->szIndexPath );

	return MY_SUCCEED;
}

/********************************************************** 
function: CheckInitCmd
description: 检验运行指令合法性
Input: piCmd: 描述运行指令各项内容的结构体
Output:
Return: MY_SUCCEED 合法 MY_FAIL 不合法
others:
***********************************************************/

int CheckInitCmd( PINIT_CMD piCmd )
{
	/* 校验日志目录 */
	if( !IsDir( piCmd->szLogDir ) )
	{
		fprintf( stderr, "gen\texit\t无效的运行日志文件路径\n" );
		return MY_FAIL;
	}
	
	/* 校验初始化时间 */
	if( !IsMonthDate( piCmd->szInitDate ) && !IsDayDate( piCmd->szInitDate ) && !IsHourDate( piCmd->szInitDate ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的初始化时间 [%s] !\n\n", piCmd->szInitDate );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "初始化时间 FORMAT: YYYYMM / YYYYMMDD / YYYYMMDDHH !\n\n" );
		return MY_FAIL;
	}
	
	/* 获取登陆口令信息 */
	if( MY_SUCCEED != GetLoginInfo( piCmd->szLoginFile, piCmd->szUserName, piCmd->szPassWord ) )
	{
		return MY_FAIL;
	}
	
	/* 初始化索引文件类型 */
	if( 0 == *( piCmd->szIndexType ) )
	{
		strcpy( piCmd->szIndexType, "*" );
	}

	/* 校验索引文件输出目录 */
	if( 0 != *( piCmd->szIndexPath ) )
	{
		if( !IsDir( piCmd->szIndexPath ) )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的索引文件输出目录!\n\n" );
			return MY_FAIL;
		}
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: GetInitCmd
description: 获取运行指令信息
Input: piCmd: 描述运行指令各项内容的结构体
       argc: 运行指令个数
       argv: 保存运行指令内容
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetInitCmd( PINIT_CMD piCmd, int argc, char * argv[] )
{
	extern char * optarg;
	int opt, lflag, hflag, dflag, fflag, sflag;
		
	lflag = 0;
	hflag = 0;
	dflag = 0;
	fflag = 0;
	sflag = 0;
	
	/* 获取运行程序名称 */
	memset( szBinName, 0, sizeof( szBinName ) );
	GetInDirName( szBinName, argv[0] );
	
	/* 获取运行命令 */
	while( -1 != ( opt = getopt( argc, argv, "L:l:H:h:D:d:F:f:S:s:T:t:P:p:" ) ) )
	{
		/* 分析运行命令 */
		switch( opt )
		{
			case 'L':
			case 'l':
				lflag = 1;
				strcpy( piCmd->szLogDir, optarg );
				
				strcpy( szLogPath, optarg );
				strcpy( szLogPrefix, "dti" );
				strcpy( szSrcDir, "init" );
				break;
				
			case 'H':
			case 'h':
				hflag = 1;
				strcpy( piCmd->szHostName, optarg );
				break;
			
			case 'D':
			case 'd':
				dflag = 1;
				strcpy( piCmd->szInitDate, optarg );
				break;
						
			case 'F':
			case 'f':
				fflag = 1;
				strcpy( piCmd->szLoginFile, optarg );
				break;
				
			case 'S':
			case 's':
				sflag = 1;
				strcpy( piCmd->szServer, optarg );
				break;
				
			case 'T':
			case 't':
				strcpy( piCmd->szIndexType, optarg );
				printf("[%s][%s]\n",piCmd->szIndexType,optarg);
				break;
					
			case 'P':
			case 'p':
				strcpy( piCmd->szIndexPath, optarg );
				break;

			default:
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的索引文件初始化运行参数 %c !\n", opt );
				break;
		}
	}

	/* 参数有效性检测 */
	if( !( lflag && hflag && dflag && fflag && sflag ) )
	{
		fprintf( stderr, "\n\n\t[usage]: %s -l Logdir -h Hostname -d initDate -f loginFile -s Server [-t indexType] [-p indexPath]\n\n", szBinName );
   		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "索引文件初始化运行参数不足!\n\n" );
   		exit(0);
	}
	
	/* 检查运行指令合法性 */
	if( MY_SUCCEED != CheckInitCmd( piCmd ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的索引文件初始化运行参数!\n\n" );
		exit(0);
	}

	DebugOutInitCmd( piCmd );
	
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
	memset( &(iData.iCmd), 0, sizeof( INIT_CMD ) );
	
	/* 获取运行指令信息 */
	GetInitCmd( &(iData.iCmd), argc, argv );
	
	strcpy( iData.szHostName, iData.iCmd.szHostName );
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "启动索引文件初始化系统!\n\n" );
	
	/* 连接数据库 */
	ConnectDataBase( (iData.iCmd).szUserName, (iData.iCmd).szPassWord, (iData.iCmd).szServer );
	
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
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "初始化 [%s] 的 [%s] 索引文件!\n\n", iData.iCmd.szInitDate, iData.iCmd.szIndexType );
	
	/* 初始化索引文件 */
	if( MY_SUCCEED != InitIndexFile( &iData ) )
	{
		FreeCtrlData( &iData );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "初始化索引文件失败!\n\n" );
	}
	
	/* 释放申请的内存空间 */
	FreeCtrlData( &iData );
		
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "索引文件初始化完毕, 成功退出!\n\n" );
	
	return 0;
}
