

/********************************************************************
copyright (C), 1995-2004, Si-Tech Information Technology Ltd. 
file_name: dlogic.c  
author: 张凡 version: （V1.00） date: （2004－08－20）
description: 实现逻辑判断功能
others:
history: 1.date: 修改时间 version: 版本（V1.00）author: 作者
			modification: 修改内容
		 2. ... 
********************************************************************/


#include "ddef.h"


/********************************************************** 
function: DebugOutLogicField
description: 输出逻辑表达式各项域的内容
Input: plWhere: 描述逻辑表达式的结构体
Output:
Return: RIGHT: 成功
others:
***********************************************************/

int DebugOutLogicField( PLOGIC_WHERE plWhere )
{
	PWHERE_FIELD pwField;
	int nLoop;

		
	pwField = plWhere->pwField;
	
	printf( "\t\n== LOGIC FIELD ==\n\n" );
	
	for( nLoop = 0; nLoop < plWhere->nWhereCount; nLoop++, pwField++ )
	{
		printf( "%2d: [%2d] - [%d] - [%s]\n", 
							nLoop,
							pwField->nFieldNo, 
							pwField->nOptFlag, 
							pwField->szValue );
	}
	
	printf( "\t\n== LOGIC FIELD ==\n\n" );
	
	return MY_SUCCEED;
}


/********************************************************** 
function: GetFieldNo
description: 获取字段编号
Input: piData: 描述系统全局数据的结构体
	   pcRecord: 索引字段配置信息
	   pfieldFmt: 记录详单格式的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int GetFieldNo( PINDEX_DATA piData, PCONFIG_RECORD pcRecord, PFIELD_FMT pfieldFmt )
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
		if( 0 == strcasecmp( pfieldFmt->szFieldName, pfFmt->szFieldName ) )
		{
			if( pfFmt->nLen > MAX_FIELD_LEN )
			{
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "详单字段长度 [%d] 超过最大值!\n", pfFmt->nLen );
				return MY_FAIL;
			}
			
			pfieldFmt->nFieldNo = pfFmt->nFieldNo;
			
			return MY_SUCCEED;
		}
	}
	
	return MY_FAIL;
}

/********************************************************** 
function: ChkRightValue
description: 检验字段取值合法性
Input: szValue: 字段取值
       pfieldFmt: 描述字段信息的结构体
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int ChkRightValue( char * szValue, PFIELD_FMT pfieldFmt )
{
	if( 0 == strlen( szValue ) || 0 == *(szValue) )
	{
		return MY_FAIL;
	}

	switch( pfieldFmt->nType )
	{
		case 0:	/* 字符串 */
			if( !IsStr( szValue ) )
			{
				return MY_FAIL;
			}
			break;
			
		case 1: /* 整数 */
			if( !IsNum( szValue ) )
			{
				return MY_FAIL;
			}
			break;
		 
		case 2: /* 浮点数 */
			if( !IsFloat( szValue ) )
			{
				return MY_FAIL;
			}
			
			break;
		
		default:
			return MY_FAIL;
			break;
	}
	
	return MY_SUCCEED;
}

/********************************************************** 
function: RebuildField
description: 重组逻辑表达式的一个域
Input: piData: 描述系统全局数据的结构体
	   pcRecord: 索引字段配置信息
       szField: 域值
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int RebuildField( PINDEX_DATA piData, PCONFIG_RECORD pcRecord, char * szField )
{
	PLOGIC_WHERE plWhere;
	PWHERE_FIELD pwField;
	FIELD_FMT fFmt;
	char szLValue[128], szRValue[128];
	char * szEnd;
	int nOptLen;
		
	plWhere = &(pcRecord->lWhere);
	pwField = &(plWhere->pwField[plWhere->nWhereCount]);
	nOptLen = 0;
		
	memset( szLValue, 0, sizeof( szLValue ) );
	memset( szRValue, 0, sizeof( szRValue ) );
	memset( &fFmt, 0, sizeof( FIELD_FMT ) );

	if( NULL != ( szEnd = ( char * ) strstr( szField, "!=" ) ) )
	{
		nOptLen = 2;
		pwField->nOptFlag = 3;
	}
	else if( NULL != ( szEnd = ( char * ) strstr( szField, ">=" ) ) )
	{
		nOptLen = 2;
		pwField->nOptFlag = 4;
	}
	else if( NULL != ( szEnd = ( char * ) strstr( szField, "<=" ) ) )
	{
		nOptLen = 2;
		pwField->nOptFlag = 5;
	}
	else if( NULL != ( szEnd = ( char * ) strchr( szField, '=' ) ) )
	{
		nOptLen = 1;
		pwField->nOptFlag = 0;
	}
	else if( NULL != ( szEnd = ( char * ) strchr( szField, '>' ) ) )
	{
		nOptLen = 1;
		pwField->nOptFlag = 1;
	}
	else if( NULL != ( szEnd = ( char * ) strchr( szField, '<' ) ) )
	{
		nOptLen = 1;
		pwField->nOptFlag = 2;
	}
	else
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "缺少操作运算符\n" );
		return MY_FAIL;
	}

	strncpy( szLValue, szField, szEnd - szField ); 
	szLValue[szEnd - szField] = 0;
	TrimLeft( TrimRight( szLValue ) );
	
	strcpy( szRValue, szEnd + nOptLen ); 
	TrimLeft( TrimRight( szRValue ) );
	
	strcpy( fFmt.szFieldName, szLValue );

	if( GetFieldNo( piData, pcRecord, &fFmt ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效的字段 [%s]\n", szLValue );
		return MY_FAIL;
	}

	if( ChkRightValue( szRValue, &fFmt ) )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效的取值 [%s]\n", szRValue );
		return MY_FAIL;
	}

	pwField->nFieldNo = fFmt.nFieldNo;
	strcpy( pwField->szValue, szRValue );
	
	memset( szField, 0, sizeof( szField ) );
	sprintf( szField, "%d", plWhere->nWhereCount );

	return MY_SUCCEED;
}

/********************************************************** 
function: RebuildCondExpr
description: 重组逻辑表达式
Input: piData: 描述系统全局数据的结构体
	   pcRecord: 索引字段配置信息
Output:
Return: MY_SUCCEED: 成功 MY_FAIL: 失败
others:
***********************************************************/

int RebuildCondExpr( PINDEX_DATA piData, PCONFIG_RECORD pcRecord )
{
	PLOGIC_WHERE plWhere;
	char szField[MAX_FIELD_LEN + 1];
	char * szEnd;
	int nLeftP, nRightP;
	int nLen;

	if( 0 == *( pcRecord->szCondition ) )
	{
		return MY_SUCCEED;
	}
	
	plWhere = &(pcRecord->lWhere);
	
	nLen    = 0;	
	nLeftP  = 0;
	nRightP = 0;
	plWhere->nWhereCount = 0;
	
	while( nLen < strlen( pcRecord->szCondition ) )
	{
		if( plWhere->nWhereCount > MAX_COND_NUM )
		{
			MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "逻辑表达式字段个数超过最大值!\n" );
			return MY_FAIL;
		}
		
		switch( pcRecord->szCondition[nLen] )
		{
			case '&':
			case '|':
				
				strncat( pcRecord->szLogicExpr, pcRecord->szCondition + nLen, 1 );
				nLen++;
				break;
				
			case '(':
				
				nLeftP++;
				strncat( pcRecord->szLogicExpr, pcRecord->szCondition + nLen, 1 );
				nLen++;
				break;
				
			case ')':
				
				nRightP++;
				strncat( pcRecord->szLogicExpr, pcRecord->szCondition + nLen, 1 );
				nLen++;
				break;
				
			case '[':
				
				szEnd = ( char * ) strchr( pcRecord->szCondition + nLen + 1, ']' );
				if( NULL == szEnd )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "方括号不匹配!\n" );
					return MY_FAIL;	
				}
	
				memset( szField, 0, sizeof( szField ) );
				strncpy( szField, pcRecord->szCondition + nLen + 1, 
							szEnd - (pcRecord->szCondition + nLen + 1) );

				nLen += strlen(szField) + 2;	

				if( RebuildField( piData, pcRecord, szField ) )
				{
					return MY_FAIL;
				}

				strcat( pcRecord->szLogicExpr, "[" );
				strcat( pcRecord->szLogicExpr, szField );
				strcat( pcRecord->szLogicExpr, "]" );
				
				plWhere->nWhereCount++;
				
				break;

			case ' ':
				
				nLen++;
				break;
				
			default:
			
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效字符 [%c]\n", pcRecord->szCondition[nLen] );
				return MY_FAIL;
				
				break;
		}
		
	}
	
	if( nLeftP != nRightP )
	{
		MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "逻辑表达式圆括号不匹配\n" );
		return MY_FAIL;
	}
	
	/* DebugOutLogicField( plWhere ); */
	
	return MY_SUCCEED;
}

/********************************************************** 
function: CompLogicVal
description: 计算逻辑表达式值
Input: szLeft: 左值
       szRight: 右值
       nOptFlag: 操作标志
       nType: 字段数据类型
Output:
Return: MY_TRUE: 真值 MY_FALSE: 假值
others:
***********************************************************/

int CompLogicVal( char * szLeft, char * szRight, int nOptFlag, int nType )
{
	if( 0 == nType )
	{
		if( strlen( szRight ) > strlen( szLeft ) )
		{
			return MY_FALSE;
		}
	}
	
	if( 0 == nOptFlag )		/* = */
	{
		if( 0 == nType )		/* 字符串 */
		{
			if( strcmp( szLeft, szRight ) == 0 )
			{
				return MY_TRUE;
			}
		}
		else if( 1 == nType )	/* 整数 */
		{
			if( atoi( szLeft ) == atoi( szRight ) )
			{
				return MY_TRUE;
			}
		}
		else if( 2 == nType )	/* 浮点数 */
		{
			if( atof( szLeft ) == atof( szRight ) )
			{
				return MY_TRUE;
			}
		}
	}
	else if( 1 == nOptFlag )	/* > */
	{
		if( 0 == nType )		/* 字符串 */
		{
			if( strncmp( szLeft, szRight, strlen( szRight ) ) > 0 )
			{
				return MY_TRUE;
			}
		}
		else if( 1 == nType )	/* 整数 */
		{
			if( atoi( szLeft ) > atoi( szRight ) )
			{
				return MY_TRUE;
			}
		}
		else if( 2 == nType )	/* 浮点数 */
		{
			if( atof( szLeft ) > atof( szRight ) )
			{
				return MY_TRUE;
			}
		}
	}
	else if( 2 == nOptFlag )	/* < */
	{
		if( 0 == nType )		/* 字符串 */
		{
			if( strncmp( szLeft, szRight, strlen( szRight ) ) < 0 )
			{
				return MY_TRUE;
			}
		}
		else if( 1 == nType )	/* 整数 */
		{
			if( atoi( szLeft ) < atoi( szRight ) )
			{
				return MY_TRUE;
			}
		}
		else if( 2 == nType )	/* 浮点数 */
		{
			if( atof( szLeft ) < atof( szRight ) )
			{
				return MY_TRUE;
			}
		}
	}
	else if( 3 == nOptFlag )	/* != */
	{
		if( 0 == nType )		/* 字符串 */
		{
			if( strcmp( szLeft, szRight ) != 0 )
			{
				return MY_TRUE;
			}
		}
		else if( 1 == nType )	/* 整数 */
		{
			if( atoi( szLeft ) != atoi( szRight ) )
			{
				return MY_TRUE;
			}
		}
		else if( 2 == nType )	/* 浮点数 */
		{
			if( atof( szLeft ) != atof( szRight ) )
			{
				return MY_TRUE;
			}
		}
	}
	else if( 4 == nOptFlag )	/* >= */
	{
		if( 0 == nType )		/* 字符串 */
		{
			if( strncmp( szLeft, szRight, strlen( szRight ) ) >= 0 )
			{
				return MY_TRUE;
			}
		}
		else if( 1 == nType )	/* 整数 */
		{
			if( atoi( szLeft ) >= atoi( szRight ) )
			{
				return MY_TRUE;
			}
		}
		else if( 2 == nType )	/* 浮点数 */
		{
			if( atof( szLeft ) >= atof( szRight ) )
			{
				return MY_TRUE;
			}
		}
	}
	else if( 5 == nOptFlag )	/* <= */
	{
		if( 0 == nType )		/* 字符串 */
		{
			if( strncmp( szLeft, szRight, strlen( szRight ) ) <= 0 )
			{
				return MY_TRUE;
			}
		}
		else if( 1 == nType )	/* 整数 */
		{
			if( atoi( szLeft ) <= atoi( szRight ) )
			{
				return MY_TRUE;
			}
		}
		else if( 2 == nType )	/* 浮点数 */
		{
			if( atof( szLeft ) <= atof( szRight ) )
			{
				return MY_TRUE;
			}
		}
	}
	
	return MY_FALSE;
}

/********************************************************** 
function: GetLogicVal
description: 获取逻辑表达式的逻辑值
Input: piData: 描述系统全局数据的结构体
	   pcRecord: 索引字段配置记录
       szExpr: 逻辑表达式
Output:
Return: MY_TRUE: 真值 MY_FALSE: 假值
others:
***********************************************************/

int GetLogicVal( PINDEX_DATA piData, PCONFIG_RECORD pcRecord, char * szExpr )
{
	PFMT_FILE pfFile;
	PLOGIC_WHERE plWhere;
	PWHERE_FIELD pwField;
	PFIELD_FMT pfFmt;
	char szField[MAX_FIELD_LEN + 1];	
	int nlfNo, nFieldNo;
	
	pfFile = pcRecord->pfFile;
	plWhere = &(pcRecord->lWhere);
	
	nlfNo = atoi( szExpr );
	pwField = (plWhere->pwField + nlfNo);
	nFieldNo = pwField->nFieldNo;
	pfFmt = pfFile->pfFmt + nFieldNo;

	memcpy( szField, piData->szRecord + pfFmt->nStart, pfFmt->nLen );
	szField[pfFmt->nLen] = 0;
	TrimLeft( TrimRight( szField ) );

	if( 0 == *(szField) )	/* NULL or IS NULL ? */
	{
		return MY_FALSE;
	}
	else
	{
		return CompLogicVal( szField, pwField->szValue, pwField->nOptFlag, pfFmt->nType );
	}	
}

/********************************************************** 
function: ComLogicExpr
description: 计算逻辑表达式的逻辑值
Input: szLeft: 左值
       szRight: 右值
       bOper: 逻辑运算符
Output:
Return: MY_TRUE: 真值 MY_FALSE: 假值
others:
***********************************************************/

int ComLogicExpr( char * szLeft, char * szRight, char bOper )
{
	if( '&' == bOper )
	{
		return ( atoi(szLeft) && atoi(szRight) );
	}
	else if( '|' == bOper )
	{
		return ( atoi(szLeft) || atoi(szRight) );
	}

	return MY_FALSE;
}

/********************************************************** 
function: IsMatchConField
description: 判断当前记录是否符合条件域配置
Input: piData: 描述系统全局结构的结构体
	   pcRecord: 索引字段配置记录
Output:
Return: MY_TRUE: 是 MY_FALSE: 否
others:
***********************************************************/

int IsMatchConField( PINDEX_DATA piData, PCONFIG_RECORD pcRecord )
{
	PLOGIC_WHERE plWhere;
	char bOptStack[1024];
	char szParaStack[1024][1024];
	char szResult[MAX_RECORD_LEN + 1];
	char * szExpr;
	char * szEnd;
	int nLoop, nLen;
	int nOptTop, nParaTop;
	
	plWhere = &(pcRecord->lWhere);
	
	nLen = 0;
	nOptTop = 0;
	nParaTop = 0;
	
	if( 0 == *(pcRecord->szCondition) )
	{
		return MY_TRUE;
	}
	
	szExpr = pcRecord->szLogicExpr;

	while( nLen < strlen( szExpr ) )
	{
		switch( (szExpr[nLen]) )
		{
			case '&':
			case '|':
			case '(':
				bOptStack[nOptTop] = szExpr[nLen];
				nOptTop++;
				nLen++;

				break;

			case ')':
				while( '(' != bOptStack[nOptTop - 1] )
				{
					memset( szResult, 0, sizeof( szResult ) );
					sprintf( szResult, "%d", 
									ComLogicExpr( szParaStack[nParaTop - 1], 
													szParaStack[nParaTop - 2],
													bOptStack[nOptTop - 1] ) );
					strcpy( szParaStack[nParaTop - 2 ], szResult );

					nParaTop--;
					nOptTop--;
				}
				
				nOptTop--;
				nLen++;
				
				break;
			
			case '[':
				szEnd = strchr( szExpr + nLen + 1, ']' );
				if( NULL == szEnd )
				{
					MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "不匹配的方括号!\n" );
					return MY_FALSE;	
				}
				
				memset( szParaStack[nParaTop], 0, sizeof( szParaStack[nParaTop] ) );
				strncpy( szParaStack[nParaTop], szExpr + nLen + 1, 
							szEnd - (szExpr + nLen + 1) );
				nLen += strlen(szParaStack[nParaTop]) + 2;	

				sprintf( szParaStack[nParaTop], "%d", 
								GetLogicVal( piData, pcRecord, szParaStack[nParaTop] ) );

				nParaTop++;
				
				break;
			
			case ' ':
				nLen++;
				break;
				
			default:
				MyLog( INFO_SOURCE_APP, INFO_LEVEL_WARN, "无效的字符!\n" );
				return MY_FALSE;	
				break;  
		}
	}

	memset( szResult, 0, sizeof( szResult ) );
	strcpy( szResult, szParaStack[nParaTop - 1] );
	nParaTop--;
	
	while( nOptTop )
	{
		sprintf( szResult, "%d", 
						ComLogicExpr( szResult,
										szParaStack[nParaTop - 1],
										bOptStack[nOptTop - 1] ) );
			
		nParaTop--;
		nOptTop--;
	}

	/* printf("result = [%s]\n", szResult ); */

	return ( atoi( szResult ) );
}
