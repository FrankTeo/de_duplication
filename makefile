

# FOR HP 64 BIT SYSTEM 
#CFLAGS = +DA2.0W +DS2.0 -DSS_64BIT_SERVER
#LFLAGS = -L${ORACLE_HOME}/lib/ -lclntsh `cat ${ORACLE_HOME}/lib/sysliblist` `cat ${ORACLE_HOME}/lib/ldflags`

# FOR HP 32 BIT SYSTEM
#CFLAGS = 
#LFLAGS = -L${ORACLE_HOME}/lib/ -lclntsh `cat ${ORACLE_HOME}/lib/sysliblist`

# FOR IBM 64 BIT SYSTEM
CFLAGS = -g -q64
LFLAGS = -L${ORACLE_HOME}/lib/ -lclntsh `cat ${ORACLE_HOME}/lib/sysliblist` `cat ${ORACLE_HOME}/lib/ldflags`

# DEFINE FOR SP SETTLE, WEED COMMON DUP RECORD, SET FEE OF MONTH DUP RECORD TO ZERO AND OUT RECORD

DEFS   = #-D __OUT_CLEAN_RECROD__


#CC = /usr/bin/xlC
COMPILE = ${CC} ${CFLAGS} ${DEFS}
MAKEEXE = ${CC} ${CFLAGS} ${LFLAGS}


INITOBJ = imain.o iindex.o common.o ddata.o oracall.o dlogic.o
DUPOBJ  = dmain.o iindex.o common.o ddata.o oracall.o dlogic.o dealfile.o
ANAOBJ  = amain.o iindex.o common.o ddata.o oracall.o dlogic.o

all:	init_index weed_dup ana_index

init_index:	${INITOBJ}
	 	${MAKEEXE} -o $@ ${INITOBJ}

weed_dup:	${DUPOBJ}
	 	${MAKEEXE} -o $@ ${DUPOBJ}

ana_index:	${ANAOBJ}
	 	${MAKEEXE} -o $@ ${ANAOBJ}

oracall.o:	oracall.pc
		proc oracall.pc
		${COMPILE} -c oracall.c
		rm -rf oracall.c *.lis

.c.o:
	${COMPILE} -c $<

clean:
		rm -f *.o *.lis core

