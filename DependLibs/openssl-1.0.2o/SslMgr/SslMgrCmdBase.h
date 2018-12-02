#ifndef SSL_CMD_BASE_H
#define SSL_CMD_BASE_H

enum ESslMgrCmdType
{
	eSslMgrCmdIdle = 0,
	eSslMgrCmdLogOn = 1,
	eSslMgrCmdSendFile = 2,
	eSslMgrCmdListFiles = 3,
	eSslMgrCmdGetFile = 4,
	eSslMgrCmdSendText = 5,
	eSslMgrCmdLogOff = 6,
	eSslMgrCmdDeleteFile = 7,
	eSslMgrCmdError,
	eSslMgrCmdUnknown,
	eMaxSslMgrCmd
};

#include <CoreLib/VxTimer.h>

#include <string>

#define CMD_ERR_NONE							0
#define CMD_ERR_GENERIC							1
#define CMD_ERR_CMD_TIMEOUT						2
#define CMD_ERR_LOGON_UNASSIGNED				3
#define CMD_ERR_GET_FILE_IO						4
#define CMD_ERR_SEND_FILE_IO					5
#define CMD_ERR_SEND_FILE_BAD_RESPONSE			6


class SslMgrCmdMgr;
class SslWrapper;
class VxFileUtil;

typedef enum
{
	DS_NOT_WAITING   ,
	DS_WAITING       ,
	DS_TIME_EXCEEDED  
} delayState_e;

class SslMgrCmdBase
{
public:
	SslMgrCmdBase( SslMgrCmdMgr& cmdMgr );
	virtual ~SslMgrCmdBase();

	virtual void				setCmdType( ESslMgrCmdType eCmdType )	{ m_eCmdType = eCmdType; }
	virtual ESslMgrCmdType		getCmdType( void )						{ return m_eCmdType; }
	virtual void				setIsCmdComplete( bool isComplete )		{ m_bIsCmdComplete = isComplete; }
	virtual bool				getIsCmdComplete( void )				{ return m_bIsCmdComplete; }
	virtual void				setErrorCode( int errCode );
	virtual int					getErrorCode( void );

	virtual void				enterState( void );
	virtual void				updateState( void )						{}
	virtual void				exitState( void )						{}

	virtual int					getDataToWriteToSslMgrServer( char * buf, int bufLen );
	virtual void				handleDataFromSslMgrServer( char * data, int dataLen );
	virtual delayState_e		handleDelays( void );

	virtual void				setErrorMsg( const char * msg, ... );
	virtual std::string&		getErrorMsg( void );
	virtual bool				hasError( void );

	virtual void				completeCommandWithError( int errCode, const char * msg, ... );


	static const char *			describeSslMgrCmdType( ESslMgrCmdType cmdNum );

	virtual void				LogMsg( unsigned long u32LogMsgType, const char * logMsg, ... );

protected:	
	virtual void				doTimeoutError( const char * timeoutErrMsg );
	virtual bool				accumulateData( char * data, int dataLen );
	virtual bool				accumulateOk( char * data, int dataLen );
	virtual bool				clearOkFromAccumulator( void );
	virtual void				clearDataAccum( void );
	virtual bool				getAccumulatedCmd( std::string& retCmd );
	virtual bool				checkAccumForAsciiDecimalNum( int& retDecNum, int& retLenOfParse, int startOffs = 0 );	
	virtual int					countWhitespace( int curIdx );
	virtual void				removeFromFrontOfDataAccum( int byteCnt );
	


	ESslMgrCmdType				m_eCmdType;
	SslMgrCmdMgr&				m_CmdMgr;
	SslWrapper&					m_SslWrapper;
	VxFileUtil&					m_FileUtil;

	bool						m_bIsCmdComplete;
	std::string					m_strErrorMsg;
	VxTimer						m_Timer;
	char						m_as8AccumBuf[512];
	int							m_iAccumIdx;
	int							m_ErrorCode;
};


#endif // SSL_CMD_BASE_H
