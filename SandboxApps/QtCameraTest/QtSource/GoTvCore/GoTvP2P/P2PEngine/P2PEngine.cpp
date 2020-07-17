
#include "P2PEngine.h"

#include <CoreLib/VxGlobals.h>

//========================================================================
P2PEngine& GetP2PEngineInstance()
{
    static P2PEngine g_P2PEngine;
    return g_P2PEngine;
}

//========================================================================
P2PEngine::P2PEngine()
    : m_MediaProcessor(*this)
{
}

//========================================================================
P2PEngine::~P2PEngine()
{
}

//========================================================================
void P2PEngine::startupEngine( void )
{
}

//========================================================================
void P2PEngine::shutdownEngine( void )
{
}

//========================================================================
void P2PEngine::fromGuiVideoData( uint32_t u32FourCc, uint8_t * pu8VidDataIn, int iWidth, int iHeight, uint32_t u32VidDataLen, int iRotation )
{
}

//========================================================================
void P2PEngine::callbackVideoJpgBig( void * userData, VxGUID& vidFeedId, uint8_t * jpgData, uint32_t jpgDataLen )
{
}

//========================================================================
void P2PEngine::callbackVideoJpgSmall( void * userData, VxGUID& vidFeedId, uint8_t * jpgData, uint32_t jpgDataLen, int motion0to100000 )
{
}

//============================================================================
void P2PEngine::fromGuiWantMediaInput( EMediaInputType mediaType, MediaCallbackInterface * callback, void * userData, bool wantInput )
{
    if( false == VxIsAppShuttingDown() )
    {
        m_MediaProcessor.wantMediaInput( mediaType, callback, userData, wantInput );
    }
}

//============================================================================
void P2PEngine::fromGuiWantMediaInput( VxGUID& onlineId, EMediaInputType mediaType, bool wantInput )
{
    if( false == VxIsAppShuttingDown() )
    {
        //BigListInfo * poInfo = m_BigListMgr.findBigListInfo( onlineId );
        //if( poInfo )
        //{
        //    if( ( eMediaInputVideoJpgSmall != mediaType ) // no need to activate cam if requesting other person's video feed
        //        && ( eMediaInputVideoJpgBig != mediaType ) )
        //    {
        //        m_MediaProcessor.wantMediaInput( mediaType, this, ( VxNetIdent * )poInfo, wantInput );
        //    }
        //}
        //else
        //{
            m_MediaProcessor.wantMediaInput( mediaType, this, ( VxNetIdent * )&m_PktAnn, wantInput );
 //       }
    }
}
