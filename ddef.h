

/********************************************************************
Copyright (C), 1995-2004, Si-Tech Information Technology Ltd.
file_name: ddef.h  
author: 张凡 version: （V1.00） date: （2004－08－20）
description: 剔重公用变量、结构体定义
others:
history: 1.date: 修改时间 version: 版本（V1.00）author: 作者
                        modification: 修改内容
                 2. ...
********************************************************************/


#ifndef	_D_DEF_H
#define	_D_DEF_H

#include "common.h"

#define	IFLAG_TIME_YEAR			"0"								/* 按时间, 按年组织 */
#define	IFLAG_TIME_MONTH		"1"								/* 按时间, 按月组织 */
#define	IFLAG_TIME_DAY			"2"								/* 按时间, 按日组织 */
#define	IFLAG_TIME_HOUR			"3"								/* 按时间, 按小时组织 */

#define	IFLAG_USER_YEAR			"5"								/* 按用户, 按年组织 */
#define	IFLAG_USER_MONTH		"6"								/* 按用户, 按月组织 */
#define	IFLAG_USER_DAY			"7"								/* 按用户, 按日组织 */
#define	IFLAG_USER_HOUR			"8"								/* 按用户, 按小时组织 */

#define	INDEX_UNIT_DEF			-1								/* 索引单位缺省值 */
#define	INDEX_UNIT_YEAR			0								/* 索引单位: 年 */
#define	INDEX_UNIT_MONTH		1								/* 索引单位: 月 */
#define	INDEX_UNIT_DAY			2								/* 索引单位: 日 */
#define	INDEX_UNIT_HOUR			3								/* 索引单位: 小时 */

#define	INDEX_MODE_DEF			-1								/* 索引模式缺省值 */
#define	INDEX_MODE_TIME			0								/* 索引模式: 时间 */
#define	INDEX_MODE_USER			1								/* 索引模式: 用户 */

#define	BLOCK_FLAG_SEC			"0"								/* 数据块单位: 秒 */
#define	BLOCK_FLAG_MIN			"1"								/* 数据块单位: 分钟 */
#define	BLOCK_FLAG_HOUR			"2"								/* 数据块单位: 小时 */
#define	BLOCK_FLAG_DAY			"3"								/* 数据块单位: 日 */
#define	BLOCK_FLAG_MON			"4"								/* 数据块单位: 月 */

#define	BLOCK_UNIT_KBYTE		"0"								/* 数据块单位: KB */
#define	BLOCK_UNIT_MBYTE		"1"								/* 数据块单位: MB */
#define	BLOCK_UNIT_GBYTE		"2"								/* 数据块单位: GB */

#define	HEAD_USER_COUNT			10000							/* 号段用户数 */
#define	USER_OFFSET_LEN			4

#define	FIELD_NO_MAP			"*"								/* 字段映射标志 */
#define	BLOCK_FILL_CHAR			'*'								/* 索引文件初始化填充字符 */

#define	BLOCK_FLAG_AVAIL		"A"								/* 头标记: 可用 */
#define	BLOCK_FLAG_FULL			"F"								/* 头标记: 已满 */
#define	FIELD_END_FLAG			'\n'							/* 数据块头结束符 */
#define	BREAK_FIELD_SEP			"/"								/* 断点记录域分隔符 */

#define	BLOCK_TSTART_LEN		5								/* 开始时间字段长度 */
#define	BLOCK_TEND_LEN			5								/* 结束时间字段长度 */
#define	BLOOK_FLAG_LEN			1								/* 状态标志长度 */
#define	BLOCK_SIZE_LEN			8								/* 空间字段长度 */
#define	BLOCK_HEND_LEN			1								/* 结束标志长度 */

#define	BLOCK_HEAD_LEN			( BLOCK_TSTART_LEN + BLOCK_TEND_LEN + BLOOK_FLAG_LEN + BLOCK_SIZE_LEN + BLOCK_HEND_LEN )

#define	PROC_CTRL_RUN			0								/* 程序允许运行 */
#define	PROC_CTRL_EXIT			1								/* 程序停止运行 */

#define	UNI_FILE_HEAD			"d"								/*  */

#define	CFG_REC_FIELD			"[REC_FIELD]"					/* 剔重索引字段配置文件记录域标识 */
#define	CFG_CON_FIELD			"[CON_FIELD]"					/* 剔重索引字段配置文件条件域标识 */
#define	CFG_CLN_FIELD			"[CLN_FIELD]"					/* 剔重索引字段配置文件清空域标识 */
#define	CFG_IND_FIELD			"[IND_FIELD]"					/* 剔重索引字段配置文件索引域标识 */

#define	SYS_TYPE_LEN			8								/* 业务类型字段长度 */
#define	MAX_COND_NUM			100								/* 条件表达式最大项 */
#define	MAX_FIELD_LEN			32								/* 字段最大长度 */

#define	BREAK_LOG_HEAD			"break."						/* 断点日志文件前缀 */
#define	BREAK_START_TAIL		".start"						/* 断点日志文件后缀 */
#define	BREAK_TMP_TAIL			".tmp"							/* 断点日志文件后缀 */
#define	BREAK_END_TAIL			".end"							/* 断点日志文件后缀 */

#define	BREAK_STATE_NORMAL		0								/* 断点状态: 没有断点文件 */
#define	BREAK_STATE_START		1								/* 断点状态: 开始处理文件 */
#define	BREAK_STATE_TMP			2								/* 断点状态: 输出临时文件 */
#define	BREAK_STATE_END			3								/* 断点状态: 文件处理完毕 */

#define ERROR_CODE_PREFIX	"Ed"								/* 前缀 */
#define	ERROR_CODE_NORMAL	"tc000"								/* 正确记录 */
#define	ERROR_CODE_CFGREC	"tc001"								/* 在配置文件汇中未找到匹配的记录 */
#define	ERROR_CODE_RECLEN	"tc002"								/* 记录长度错误 */
#define	ERROR_CODE_INDCRL	"tc003"								/* 未找到匹配的索引文件控制信息  */
#define	ERROR_CODE_BLKCRL	"tc004"								/* 未找到匹配的索引数据块控制信息 */
#define	ERROR_CODE_IDNULL	"tc005"								/* 号码字段为空 */
#define	ERROR_CODE_NOTEXT	"tc006"								/* 索引文件不存在 */

#define	ERROR_CODE_DUPREC	"tc010"						/* 重单记录 */

typedef	struct _INIT_CMD
{
	char szLogDir[MAX_PATH_LEN + 1];							/* 运行日志目录 */
	char szHostName[32 + 1];									/* 主机标识 */
	char szInitDate[14 + 1];									/* 初始化日期 */
	char szIndexType[16 + 1];									/* 索引文件类型 */
	char szIndexPath[MAX_PATH_LEN + 1];							/* 索引文件位置 */
	char szLoginFile[MAX_PATH_LEN + 1];							/* 登陆口令文件 */
	char szServer[32];											/* 数据库服务名 */
	
	char szUserName[128 + 1];									/* 登陆用户名 */
	char szPassWord[128 + 1];									/* 登陆口令 */
	
} INIT_CMD;
typedef INIT_CMD * PINIT_CMD;

typedef	struct _DUP_CMD
{
	char szProcLog[MAX_PATH_LEN + 1];							/* 处理日志目录 */
	char szRunLog[MAX_PATH_LEN + 1];							/* 运行日志目录 */
	char szDupLog[MAX_PATH_LEN + 1];							/* 重单日志 */
	char szLogTmp[MAX_PATH_LEN + 1];							/* 日志临时目录 */
	
	char szInDir[MAX_PATH_LEN + 1];								/* 入口目录 */
	char szOutDir[MAX_PATH_LEN + 1];							/* 出口目录 */
	char szBakDir[MAX_PATH_LEN + 1];							/* 备份目录 */
	char szTmpDir[MAX_PATH_LEN + 1];							/* 出口临时目录 */
	
	char szHostName[32 + 1];									/* 主机标识 */
	char szLoginFile[MAX_PATH_LEN + 1];							/* 登陆口令文件 */
	char szServer[32];											/* 数据库服务名 */
	
	char szUserName[128 + 1];									/* 登陆用户名 */
	char szPassWord[128 + 1];									/* 登陆口令 */
	
	char szCfgFile[MAX_PATH_LEN + 1];							/* 配置文件 */
	char szIndexCfg[MAX_PATH_LEN + 1];							/* 索引字段配置信息 */
	char szFmtCtrl[MAX_PATH_LEN + 1];							/* 详单格式控制文件 */
	char szCtrlFlag[128];										/* 控制标志 */
	int nInterval;												/* 处理日志生成时间间隔 */
	
} DUP_CMD;
typedef DUP_CMD * PDUP_CMD;

typedef	struct _ANA_CMD
{
	char szLogDir[MAX_PATH_LEN + 1];							/* 运行日志目录 */
	char szHostName[32 + 1];									/* 主机标识 */
	char szAnaDate[14 + 1];										/* 初始化日期 */
	char szIndexType[16 + 1];									/* 索引文件类型 */
	char szRetFile[MAX_PATH_LEN + 1];							/* 分析结果文件 */
	char szIndexPath[MAX_PATH_LEN + 1];							/* 索引文件位置 */
	char szLoginFile[MAX_PATH_LEN + 1];							/* 登陆口令文件 */
	char szServer[32];											/* 数据库服务名 */
	
	char szUserName[128 + 1];									/* 登陆用户名 */
	char szPassWord[128 + 1];									/* 登陆口令 */
	
} ANA_CMD;
typedef ANA_CMD * PANA_CMD;

typedef struct _ICTRL_RECORD
{
	char szHostName[16 + 1];									/* 主机标识 */
	char szIndexType[8 + 1];									/* 索引文件类型 */
	char szIndexFlag[1 + 1];									/* 索引文件标志 */
	char szIndexDir[128 + 1];									/* 索引文件位置 */
	char szEffectStartTime[8 + 1];								/* 开始生效时间 */
	char szEffectEndTime[8 + 1];								/* 结束生效时间 */
	char szIndexStartTime[8 + 1];								/* 开始作用时间 */
	char szIndexEndTime[8 + 1];									/* 结束作用时间 */
	char szBlockLink[8 + 1];									/* 数据块链接 */
	
} ICTRL_RECORD;
typedef ICTRL_RECORD * PICTRL_RECORD;

typedef struct _ICTRL_DATA
{
	PICTRL_RECORD picRecord;

	int nRecCount;
	
}ICTRL_DATA;
typedef	ICTRL_DATA * PICTRL_DATA;

typedef	struct _BCTRL_RECORD
{
	char szIndexType[8 + 1];									/* 索引文件类型 */
	char szBlockLink[8 + 1];									/* 数据块链接 */
	char szBlockFlag[1 + 1];									/* 数据块标志 */
	char szBlockStartTime[8 + 1];								/* 开始作用时间 */
	char szBlockEndTime[8 + 1];									/* 结束作用时间 */
	char szBlockUnit[1 + 1];									/* 数据块单位 */
	
	int nBlockNum;												/* 数据块数目 */
	int nBlockSize;												/* 数据块尺寸 */
	
} BCTRL_RECORD;
typedef BCTRL_RECORD * PBCTRL_RECORD;

typedef	struct _BCTRL_DATA
{
	PBCTRL_RECORD pbcRecord;

	int nRecCount;												/* 记录数 */
	
}BCTRL_DATA;
typedef	BCTRL_DATA * PBCTRL_DATA;

typedef	struct _CLEAN_FIELD
{
	char szFieldName[32 + 1];									/* 索引字段名 */
	
	int nFieldStart;											/* 开始位置 */
	int nFieldLen;												/* 长度 */
	
}CLEAN_FIELD;
typedef	CLEAN_FIELD * PCLEAN_FIELD;

typedef	struct _INDEX_FIELD
{
	char szFieldName[32 + 1];									/* 索引字段名 */
	
	int nFieldStart;											/* 开始位置 */
	int nFieldLen;												/* 长度 */
	
}INDEX_FIELD;
typedef	INDEX_FIELD * PINDEX_FIELD;

typedef	struct _WHERE_FIELD
{
	int nFieldNo;												/* 字段编号 */
	int nOptFlag;												/* 操作标志 */
	char szValue[128];											/* 操作值 */
	
} WHERE_FIELD;
typedef	WHERE_FIELD * PWHERE_FIELD;

typedef	struct _LOGIC_WHERE
{
	WHERE_FIELD pwField[MAX_COND_NUM];
	
	int nWhereCount;											/* 逻辑字段个数 */
	
} LOGIC_WHERE;
typedef	LOGIC_WHERE * PLOGIC_WHERE;

typedef	struct	_FIELD_FMT
{
	int nFieldNo;												/* 字段编号 */
	char szFieldName[128 + 1];									/* 字段名 */
	int nStart;													/* 字段在详单中的开始位置 */
	int nEnd;													/* 字段在详单中的结束位置 */
	int nLen;													/* 字段在详单中的长度 */
	int nType;													/* 字段数据类型 */
	char szMapNo[3 + 1];										/* 映射文件编号 */
	
} FIELD_FMT;
typedef	FIELD_FMT * PFIELD_FMT;

typedef	struct _FMT_FILE
{
	PFIELD_FMT pfFmt;
	int nFieldCount;											/* 详单字段数目 */
	
	char szFileHead[32 + 1];									/* 文件头 */
	char szSysType[SYS_TYPE_LEN + 1];							/* 业务类型 */
	char szStartTime[14 + 1];									/* 生效开始时间 */
	char szEndTime[14 + 1];										/* 生效结束时间 */
	char szFileName[MAX_PATH_LEN + 1];							/* 详单格式描述文件 */
	
} FMT_FILE;
typedef FMT_FILE * PFMT_FILE;

typedef struct _FMT_CTRL
{
	PFMT_FILE pfFile;
	
	int nFmtNum;
	
} FMT_CTRL;
typedef FMT_CTRL * PFMT_CTRL;

typedef	struct _CONFIG_RECORD
{
	PCLEAN_FIELD pcField;
	
	char szCleanFields[MAX_RECORD_LEN + 1];						/* 清空域字段组合 */
	int nCleanCount;											/* 清空字段个数 */
	
	
	PINDEX_FIELD piField;
	
	char szFileHead[32 + 1];									/* 文件头 */
	char szSysType[8 + 1];										/* 系统代码 */
	char szIndexType[8 + 1];									/* 索引文件类型 */
	
	int nTimeLoc;												/* 时间字段位置 */
	int nTimeLen;												/* 时间字段长度 */
	int nUserLoc;												/* 用户字段位置 */
	int nUserLen;												/* 用户字段长度 */
	int nRecLen;												/* 记录长度 */
	int nFieldNum;												/* 索引字段个数 */
	
	char szCondition[MAX_RECORD_LEN + 1];						/* 条件逻辑表达式 */
	char szLogicExpr[MAX_RECORD_LEN + 1];						/* 条件逻辑表达式 */
	
	PFMT_FILE pfFile;
	LOGIC_WHERE  lWhere;
	
}CONFIG_RECORD;
typedef	CONFIG_RECORD * PCONFIG_RECORD;

typedef	struct _INDEX_CONFIG
{
	PCONFIG_RECORD pcRecord;

	int nRecCount;												/* 记录数 */
	
}INDEX_CONFIG;
typedef	INDEX_CONFIG * PINDEX_CONFIG;

typedef	struct _BREAK_RECORED
{
	char szErrCode[16 + 1];										/* 错误代码 */
	
	long lRecordNo;												/* 断点记录序号 */
	
} BREAK_RECORD;
typedef BREAK_RECORD * PBREAK_RECORD;

typedef	struct _INDEX_DATA
{
	/* 公共数据区 */

	ICTRL_DATA icData;
	BCTRL_DATA bcData;
	
	char szHostName[32 + 1];									/* 主机标识 */
	char szIndexName[MAX_PATH_LEN + 1];							/* 索引文件名 */
	
	/* 索引数据块头信息 */
	char szBlockHead[BLOCK_HEAD_LEN + 1];						/* 索引数据块头 */
	char szBlockStartTime[BLOCK_TSTART_LEN + 1];				/* 索引数据块开始时间 */
	char szBlockEndTime[BLOCK_TEND_LEN + 1];					/* 索引数据块结束时间 */
	char szUserSerial[BLOCK_TSTART_LEN + BLOCK_TEND_LEN + 1];	/* 索引数据块用户序列号 */
	char szBlockFlag[BLOOK_FLAG_LEN + 1];						/* 索引数据块标志 */
	char szBlockSize[BLOCK_SIZE_LEN + 1];						/* 索引数据块尺寸 */
	
	char szIndexYear[DATE_YEAR_LEN + 1];						/* 初始化日期: 年 */
	char szIndexMonth[DATE_MON_LEN + 1];						/* 初始化日期: 月 */
	char szIndexDay[DATE_DAY_LEN + 1];							/* 初始化日期: 日 */
	char szIndexHour[DATE_HOUR_LEN + 1];						/* 初始化日期: 分 */
	char szIndexDate[DATE_STD_LEN + 1];							/* 初始化日期 */
	
	char * szBlock;												/* 索引数据块 */
	
	long lBlockSize;											/* 数据块尺寸 */
	long lTotalTime;											/* 时间总数 */
	
	int nIndexUnit;												/* 索引单位 */
	int nIndexMode;												/* 索引模式 */
	
	int nTimeCount;												/* 基本时间单位个数 */
	int nUserCount;												/* 基本用户单位个数 */
	
	int nBreakState;											/* 断点状态 */
	
	FILE * fpIndex;												/* 索引文件指针 */
	
	/* 索引初始化数据区 */	

	INIT_CMD iCmd;
	
	/* 剔重数据区 */
	
	DUP_CMD dCmd;
	TIME_DATA tData;
	INDEX_CONFIG iConfig;
	PCONFIG_RECORD pcRecord;
	FMT_CTRL fCtrl;												/* 保存详单格式控制信息 */
	PICTRL_RECORD picRecord;
	PBCTRL_RECORD pbcRecord;
	BREAK_RECORD bRecord;
	
	char szFileName[MAX_PATH_LEN + 1];							/* 处理文件名 */
	char szRecord[MAX_RECORD_LEN + 1];							/* 处理记录 */
	char szErrCode[16 + 1];										/* 错误代码 */
	char szDupRecord[MAX_RECORD_LEN + 1];						/* 重单记录 */
	
	char szCurrBatch[14 + 1];									/* 当前处理批次 */

	/* 山西移动精确到MicroSecond */
	char szStartTime[14 + 6 + 1];								/* 开始时间 */
	char szEndTime[14 + 6 + 1];									/* 结束时间 */
	
	char szRecTime[14 + 1];										/* 记录时间 */
	char szRecUser[64 + 1];										/* 记录用户 */
	char szSerial[USER_OFFSET_LEN + 1];							/* 用户序号 */
	
	char szIndexFile[MAX_PATH_LEN + 1];							/* 索引文件 */
	char szIndexFields[MAX_RECORD_LEN + 1];						/* 索引字段组合 */
	
	char bSameIndexFile;										/* 是否为同一个索引文件 */
	char bDupRecord;											/* 是否有重单记录 */
	char bRollback;												/* 是否进行回滚处理 */
	
	long lTotalRec;												/* 总记录数 */
	long lAvailRec;												/* 有效记录数 */
	long lErrorRec;												/* 错单记录数 */
	long lDupRec;												/* 重单记录数 */
	long lDupNo;												/* 重单记录序号 */
	
	long lRealBlockSize;										/* 索引数据块实际定义大小 */
	long lBlockOffset;											/* 索引数据块偏移 */
	long lBlockTime;											/* 索引数据块时间 */
	
	int nProcHandle;											/* 处理日志句柄 */
	int nErrHandle;												/* 错单日志句柄 */
	int nDupHandle;												/* 重单文件句柄 */
	int nBreakHandle;											/* 断点文件句柄 */
	
	int nRecordLen;												/* 记录长度 */
	
	FILE * fpTmpOut;											/* 出口临时文件指针 */	
	FILE * fpDup;												/* 重单文件指针 */
	
	/* 索引文件分析数据区 */
	
	ANA_CMD aCmd;
	
	long lBlockNo;												/* 索引数据块编号 */
	
	int nExtend;												/* 索引块扩展次数 */
	
	double lfSpaceUse;											/* 空间使用率 */
	
	FILE * fpResult;											/* 分析结果文件 */
	
} INDEX_DATA;
typedef INDEX_DATA * PINDEX_DATA;

#include "fun.h"
#endif
