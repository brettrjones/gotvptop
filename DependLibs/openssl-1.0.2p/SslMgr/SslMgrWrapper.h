#ifndef SSL_MGR_WRAPPER_H
#define SSL_MGR_WRAPPER_H

#include "SslMgrCmdBase.h"
#include "SslWrapper.h"

#include <CoreLib/VxFileUtil.h>
#include <CoreLib/VxTimer.h>



class SslMgrWrapperCallback
{
public:
	virtual void				LogMsg( unsigned long u32LogMsgType, const char * pMsg, ... ) = 0;

	virtual void				connectedToSslMgrServer( void ) = 0;
	virtual void				disconnectedFromSslMgrServer( void ) = 0;

	virtual void				sslMgrCmdComplete( ESslMgrCmdType cmdType ) = 0;
	virtual void				sslMgrCmdError( ESslMgrCmdType cmdType, int errCode, const char * errorText ) = 0;
	virtual void				sslMgrWentIdle( void ) = 0;

	virtual void				sslMgrListFile( const char * fileName ) = 0;

	virtual void				sslMgrFileGetBegin( const char * fileName ) = 0;
	virtual void				sslMgrFileGetProgress( const char * fileName, int percentComplete ) = 0;
	virtual void				sslMgrFileGetComplete( const char * fileName ) = 0;

	virtual void				sslMgrFileSendBegin( const char * fileName ) = 0;
	virtual void				sslMgrFileSendProgress( const char * fileName, int percentComplete ) = 0;
	virtual void				sslMgrFileSendComplete( const char * fileName ) = 0;

};


class SslMgrWrapper : public ISslCallback
{
public:
	SslMgrWrapper( SslMgrWrapperCallback& sslMgrCallback );
	virtual ~SslMgrWrapper();

	virtual void				LogMsg( unsigned long u32LogMsgType, const char * logMsg );

	virtual void				connectedToSslMgrServer( void );
	virtual void				disconnectedFromSslMgrServer( void );

	virtual void				sslMgrCmdComplete( ESslMgrCmdType cmdType );
	virtual void				sslMgrCmdError( ESslMgrCmdType cmdType, int errCode, const char * errorText );
	virtual void				sslMgrWentIdle( void );

	virtual void				sslMgrListFile( const char * fileName );

	virtual void				sslMgrFileGetBegin( const char * fileName );
	virtual void				sslMgrFileGetProgress( const char * fileName, int percentComplete );
	virtual void				sslMgrFileGetComplete( const char * fileName );

	virtual void				sslMgrFileSendBegin( const char * fileName );
	virtual void				sslMgrFileSendProgress( const char * fileName, int percentComplete );
	virtual void				sslMgrFileSendComplete( const char * fileName );

	///////////////////////////
	virtual void				setCertFileName( const char * certFileName );
	virtual void				setKeyFileName( const char * keyFileName );
	virtual void				setSslMgrServerIpAddr( const char * ipAddr );
	virtual void				setSslMgrServerPort( uint16_t port );
	virtual void				setSslMgrConnectRetryIntervalMs( int intervalMs );

	virtual void				connectToSslMgrServer( void );
	virtual void				disconnectFromSslMgrServer( void );
	virtual bool				isConnectedToSslMgrServer( void );

	virtual void				sslMgrCmdLogOn( const char * userName, const char * pass );
	virtual void				sslMgrCmdLogOff(  bool logOffRightNow = false, bool fromSslMgrThread = false );
	virtual void				sslMgrCmdSendFile( const char * userFileName );
	virtual void				sslMgrCmdListFiles( void );
	virtual void				sslMgrCmdGetFile( const char * userFileName, bool deleteFromSslMgrIfSuccess = true );
	virtual void				sslMgrCmdDeleteFile( const char * userFileName, uint32_t u32CheckSum );
	virtual void				sslMgrCmdSendText( const char * textToSendToServer );
	virtual bool				haveAllSslMgrCmdsCompleted( void );

protected:
	VxFileUtil					m_FileUtil;
	SslWrapper					m_SslWrapper;
	SslMgrWrapperCallback&		m_SslMgrCallback;
};

#endif // SSL_MGR_WRAPPER_H

