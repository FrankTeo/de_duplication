

/********************************************************************
copyright (C), 1995-2004, Si-Tech Information Technology Ltd. 
file_name: dmain.c  
author: 张凡 version: （V1.00） date: （2004－08－20）
description: 文件剔重系统调度
others:
history: 1.date: 修改时间 version: 版本（V1.00）author: 作者
			modification: 修改内容
		 2. ... 
********************************************************************/


#include "ddef.h"


/********************************************************** 
function: DebugOutDupCmd
description: 输出运行指令信息
Input:	pdCmd: 描述运行指令各项内容的结构体
Output:
Return: MY_SUCCEED 成功
others:
***********************************************************/

int DebugOutDupCmd( PDUP_CMD pdCmd )
{
	char bRunFlag;
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, 
"文件剔重系统运行参数内容如下\n\n\t=== File Dup Run Info ===\n\n\
\tProcLog   = [%s]\n\tRunLog    = [%s]\n\tLogTmp    = [%s]\n\tInDir     = [%s]\n\
\tOutDir    = [%s]\n\tBakDir    = [%s]\n\tTmpDir    = [%s]\n\tHostName  = [%s]\n\
\tLoginFile = [%s]\n\tServer    = [%s]\n\tCtrlFlag  = [%s]\n\tCfgFile   = [%s]\n\
\tInterval  = [%d]\n\n\t=== File Dup Run Info ===\n\n",
				pdCmd->szProcLog, pdCmd->szRunLog, pdCmd->szLogTmp, pdCmd->szInDir, 
				pdCmd->szOutDir, pdCmd->szBakDir, pdCmd->szTmpDir, pdCmd->szHostName,
				pdCmd->szLoginFile, pdCmd->szServer, pdCmd->szCtrlFlag, 
				pdCmd->szCfgFile, pdCmd->nInterval );

	return MY_SUCCEED;
}

/********************************************************** 
function: CheckDupCmd
description: 检验运行指令合法性
Input: pdCmd: 描述运行指令各项内容的结构体
Output:
Return: MY_SUCCEED 合法 MY_FAIL 不合法
others:
***********************************************************/

int CheckDupCmd( PDUP_CMD pdCmd )
{
	/* 校验处理日志目录 */
	if( !IsDir( pdCmd->szProcLog ) )
	{
		fprintf( stderr, "gen\texit\t无效的处理日志目录!\n" );
		return MY_FAIL;
	}
	
	/* 校验运行日志目录 */
	if( !IsDir( pdCmd->szRunLog ) )
	{
		fprintf( stderr, "gen\texit\t无效的运行日志目录!\n" );
		return MY_FAIL;
	}
	
	/* 校验临时日志目录 */
	if( !IsDir( pdCmd->szLogTmp ) )
	{
		fprintf( stderr, "gen\texit\t无效的临时日志目录!\n" );
		return MY_FAIL;
	}
	
	/* 校验入口目录 */
	if( !IsDir( pdCmd->szInDir ) )
	{
		fprintf( stderr, "gen\texit\t无效的入口文件存放目录!\n" );
		return MY_FAIL;
	}
	
	/* 校验出口目录 */
	if( !IsDir( pdCmd->szOutDir ) )
	{
		fprintf( stderr, "gen\texit\t无效的出口文件输出目录!\n" );
		return MY_FAIL;
	}
	
	/* 校验备份目录 */
	if( !IsDir( pdCmd->szBakDir ) )
	{
		fprintf( stderr, "gen\texit\t无效的入口文件备份目录!\n" );
		return MY_FAIL;
	}
	
	/* 校验出口临时目录 */
	if( !IsDir( pdCmd->szTmpDir ) )
	{
		fprintf( stderr, "gen\texit\t无效的出口临时文件存放目录!\n" );
		return MY_FAIL;
	}
	
	/* 获取数据库登陆用户名、口令 */
	if( MY_SUCCEED != GetLoginInfo( pdCmd->szLoginFile, pdCmd->szUserName, pdCmd->szPassWord ) )
	{
		return MY_FAIL;
	}
	
	/* 初始化日志生成时间间隔 */
	if( 0 >= pdCmd->nInterval )
	{
		pdCmd->nInterval = 900;	
	}
	
	/* 检验处理日志与日志临时目录是否在同一个文件系统 */
	if( !IsSameFileSystem( pdCmd->szProcLog, pdCmd->szLogTmp ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "处理日志目录和日志临时日志目录不在同一个文件系统!\n\n" );
		return MY_FAIL;
	}
	
	/* 检验运行日志与日志临时目录是否在同一个文件系统 */
	if( !IsSameFileSystem( pdCmd->szRunLog, pdCmd->szLogTmp ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "运行日志目录和日志临时日志目录不在同一个文件系统!\n\n" );
		return MY_FAIL;
	}
	
	/* 检验入口与备份目录是否在同一个文件系统 */
	if( !IsSameFileSystem( pdCmd->szInDir, pdCmd->szBakDir ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "文件入口目录和入口文件备份目录不在同一个文件系统!\n\n" );
		return MY_FAIL;
	}
	
	/* 检验出口与出口临时目录是否在同一个文件系统 */
	if( !IsSameFileSystem( pdCmd->szOutDir , pdCmd->szTmpDir ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "文件出口目录和出口临时日志目录不在同一个文件系统!\n\n" );
		return MY_FAIL;
	}
	
	/* 获取索引字段配置信息文件 */
	if( GetIniInfo( pdCmd->szCfgFile, "INDEXCFG", pdCmd->szIndexCfg ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取索引字段配置信息文件失败!\n" );
		return MY_FAIL;
	}

	/* 获取详单格式控制信息文件 */
	if( GetIniInfo( pdCmd->szCfgFile, "FMTCTRL" , pdCmd->szFmtCtrl ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "获取详单格式控制信息文件失败!\n" );
		return MY_FAIL;
	}

	return MY_SUCCEED;
}

/********************************************************** 
function: GetDupCmd
description: 获取运行指令信息
Input: pdCmd: 描述运行指令各项内容的结构体
       argc: 运行指令个数
       argv: 保存运行指令内容
Output:
Return: 0 MY_SUCCEED 1 MY_FAIL
others:
***********************************************************/

int GetDupCmd( PDUP_CMD pdCmd, int argc, char * argv[] )
{
	extern char * optarg;
	int opt, pflag, rflag, mflag, iflag, oflag, bflag, tflag, hflag, lflag, sflag, cflag, fflag, vflag;

	pflag = 0;
	rflag = 0;
	mflag = 0;
	iflag = 0;
	oflag = 0;
	bflag = 0;
	tflag = 0;
	hflag = 0;
	lflag = 0;
	sflag = 0;
	cflag = 0;
	fflag = 0;
	vflag = 0;
	
	/* 获取运行程序名称 */
	memset( szBinName, 0, sizeof( szBinName ) );
	GetInDirName( szBinName, argv[0] );
	
	/* 获取运行命令 */
	while( -1 != ( opt = getopt( argc, argv, "P:p:R:r:M:m:I:i:O:o:B:b:T:t:H:h:L:l:S:s:C:c:F:f:V:v:" ) ) )
	{
		/* 分析运行命令 */
		switch( opt )
		{
			case 'P':
			case 'p':
				pflag = 1;
				strcpy( pdCmd->szProcLog, optarg );
				break;
				
			case 'R':
			case 'r':
				rflag = 1;
				strcpy( pdCmd->szRunLog, optarg );

				strcpy( szLogPath, optarg );
				strcpy( szLogPrefix, "d" );
				break;
			
			case 'M':
			case 'm':
				mflag = 1;
				strcpy( pdCmd->szLogTmp, optarg );
				break;
				
			case 'I':
			case 'i':
				iflag = 1;
				strcpy( pdCmd->szInDir, optarg );
				
				memset( szSrcDir, 0, sizeof( szSrcDir ) );
				GetInDirName( szSrcDir, pdCmd->szInDir );
				break;
				
			case 'O':
			case 'o':
				oflag = 1;
				strcpy( pdCmd->szOutDir, optarg );
				break;
				
			case 'B':
			case 'b':
				bflag = 1;
				strcpy( pdCmd->szBakDir, optarg );
				break;
				
			case 'T':
			case 't':
				tflag = 1;
				strcpy( pdCmd->szTmpDir, optarg );
				break;
			
			case 'H':
			case 'h':
				hflag = 1;
				strcpy( pdCmd->szHostName, optarg );
				break;
				
			case 'L':
			case 'l':
				lflag = 1;
				strcpy( pdCmd->szLoginFile, optarg );
				break;
				
			case 'S':
			case 's':
				sflag = 1;
				strcpy( pdCmd->szServer, optarg );
				break;
				
			case 'C':
			case 'c':
				cflag = 1;
				strcpy( pdCmd->szCtrlFlag, optarg );
				break;
			
			case 'F':
			case 'f':
				fflag = 1;
				strcpy( pdCmd->szCfgFile, optarg );
				break;
					
			case 'V':
			case 'v':
				vflag = 1;
				pdCmd->nInterval = atoi( optarg );
				break;
				
			default:
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的文件剔重运行参数 %c !\n", opt );
				break;
		}
	}
	
	/* 参数有效性检测 */
	if( !( pflag && rflag && mflag && iflag && oflag && bflag && tflag && hflag && lflag && sflag && cflag && fflag && vflag ) )
	{
		fprintf( stderr, "\n\n\t[usage]: %s -p Proclog  -r Runlog    -m logtMp -i Indir    -o Outdir  -b Bakdir   -t Tmpdir\n", szBinName );
		fprintf( stderr, "\t                  -h Hostname -l Loginfile -s Server -c Ctrlflag -f cfgFile -v interVal\n\n");
   		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "文件剔重运行参数不足!\n\n" );
   		exit(0);
	}
	
	/* 检查运行指令合法性 */
	if( MY_SUCCEED != CheckDupCmd( pdCmd ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "无效的文件剔重运行参数!\n\n" );
		exit(0);
	}

	/* DebugOutDupCmd( pdCmd ); */
	
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
	memset( &(iData.dCmd), 0, sizeof( DUP_CMD ) );
	
	/* 获取运行指令 */
	GetDupCmd( &(iData.dCmd), argc, argv );
	
	strcpy( iData.szHostName, iData.dCmd.szHostName );
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "启动文件剔重系统!\n\n" );
	
	/* 连接数据库 */
	ConnectDataBase( (iData.dCmd).szUserName, (iData.dCmd).szPassWord, (iData.dCmd).szServer );
	
	/* 获取系统运行控制标志 */
	if( PROC_CTRL_RUN != GetProcCtrlFlag( iData.dCmd.szCtrlFlag ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "系统运行标志设置为禁止运行, 系统停止运行!\n\n" );
		DisConnectDataBase( );
		FreeMemoryData( &iData );
		
		exit(0);
	}
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "获取索引文件控制信息!\n\n" );
	
	/* 获取系统配置信息 */
	if( MY_SUCCEED != GetConfigInfo( &iData ) )
	{
		DisConnectDataBase( );
		FreeMemoryData( &iData );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "获取系统配置信息失败!\n\n" );
	}
	
	tmStartTime = time( NULL );
	tmStartTime = tmStartTime - tmStartTime % (iData.dCmd).nInterval + (iData.dCmd).nInterval;
	
	/* 获取当前批次 */
	GetCurrBatch( &iData );

	/* 打开当前批次的处理日志、错单日志 */
	if( MY_SUCCEED != OpenLogFile( &iData ) )
	{
		DisConnectDataBase( );
		FreeMemoryData( &iData );
		exit(0);
	}
		
	if( MY_SUCCEED != RecoverBreakPoint( &iData ) )
	{
		DisConnectDataBase( );
		FreeMemoryData( &iData );
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "断点数据恢复失败!\n\n" );
	}
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "对 [%s] 目录下的文件进行剔重处理!\n\n", iData.dCmd.szInDir );
	
	while( PROC_CTRL_RUN == GetProcCtrlFlag( iData.dCmd.szCtrlFlag ) )
	{
		/* 处理入口目录下的文件 */
		if( MY_SUCCEED != DealSrcFile( &iData ) )
		{
			DisConnectDataBase( );
			FreeMemoryData( &iData );
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_EXIT, "对入口目录下的文件 %s 进行剔重处理失败!\n\n", iData.szFileName );
		}
		
		tmEndTime = time( NULL );
		tmEndTime = tmEndTime - tmEndTime % (iData.dCmd).nInterval + (iData.dCmd).nInterval;
		
		if( tmEndTime > tmStartTime )
		{
			tmStartTime = tmEndTime;
			
			/* 获取当前批次 */
			GetCurrBatch( &iData );
			
			/* 变更处理日志,错单日志 */
			if( MY_SUCCEED != AlterLogFile( &iData ) ) { 
				DisConnectDataBase( ); 
				FreeMemoryData( &iData ); 
				exit(0); 
			} 

			/* 打开当前批次的处理日志、错单日志 
			if( MY_SUCCEED != OpenLogFile( &iData ) )
			{
				DisConnectDataBase( );
				FreeMemoryData( &iData );
				exit(0);
			}
			*/
		}
		
		sleep( 1 );
		
		/* break; */
	}
	
	/* 断开数据库连接 */
	DisConnectDataBase( );
	
	/* 释放系统申请的内存空间 */
	FreeMemoryData( &iData );
	
	MyLog( INFO_SOURCE_APP, INFO_LEVEL_GEN, "文件剔重系统运行完毕, 成功退出!\n\n" );
	
	return 0;
}
