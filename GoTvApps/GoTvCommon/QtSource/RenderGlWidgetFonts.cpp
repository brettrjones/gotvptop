//============================================================================
// Copyright (C) 2018 Brett R. Jones
//
// You may use, copy, modify, merge, publish, distribute, sub-license, and/or sell this software
// provided this Copyright is not modified or removed and is included all copies or substantial portions of the Software
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett.jones@engineer.com
// http://www.gotvptop.net
//============================================================================

#include "RenderGlWidget.h"
#include "AppCommon.h"
#include "AppGlobals.h"
#include "AppSettings.h"
#include "MyIcons.h"
#include "GuiHelpers.h"
#include "MyIcons.h"

#include "GoTvInterface/GoTvRenderFrame.h"


#include <GoTvCore/GoTvP2P/P2PEngine/P2PEngine.h>
#include <CoreLib/VxTimeUtil.h>

#include "guilib/TextureQt.h"
#include "guilib/GUITextureQt.h"
#include "utils/GLUtils.h"

#include "ServiceBroker.h"
#include "rendering/qt/RenderSystemQt.h"
#include "rendering/MatrixGL.h"

#include "windowing/WinSystem.h"
#include "windowing/GraphicContext.h"


#define ELEMENT_ARRAY_MAX_CHAR_INDEX (1000)
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//============================================================================
bool RenderGlWidget::firstBegin( CGUIFontTTFQt * font )
{
    VerifyGLState();

    GLenum pixformat = GL_ALPHA; // deprecated

    if( font->m_textureStatus == CGUIFontTTFQt::TEXTURE_REALLOCATED )
    {
        if( m_GlF->glIsTexture( font->m_nTexture ) )
            CServiceBroker::GetGUI()->GetTextureManager().ReleaseHwTexture( font->m_nTexture );
        font->m_textureStatus = CGUIFontTTFQt::TEXTURE_VOID;
    }

    if( font->m_textureStatus == CGUIFontTTFQt::TEXTURE_VOID )
    {
        // Have OpenGL generate a texture object handle for us
        m_GlF->glGenTextures( 1, ( GLuint* )&font->m_nTexture );

        // Bind the texture object
        m_GlF->glBindTexture( GL_TEXTURE_2D, font->m_nTexture );

        // Set the texture's stretching properties
        m_GlF->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        m_GlF->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // Set the texture image -- THIS WORKS, so the pixels must be wrong.
        m_GlF->glTexImage2D( GL_TEXTURE_2D, 0, pixformat, font->m_texture->GetWidth(), font->m_texture->GetHeight(), 0,
                      pixformat, GL_UNSIGNED_BYTE, 0 );

        VerifyGLState();
        font->m_textureStatus = CGUIFontTTFQt::TEXTURE_UPDATED;
    }

    if( font->m_textureStatus == CGUIFontTTFQt::TEXTURE_UPDATED )
    {
        m_GlF->glBindTexture( GL_TEXTURE_2D, font->m_nTexture );
        m_GlF->glTexSubImage2D( GL_TEXTURE_2D, 0, 0, font->m_updateY1, font->m_texture->GetWidth(), font->m_updateY2 - font->m_updateY1, pixformat, GL_UNSIGNED_BYTE,
                         font->m_texture->GetPixels() + font->m_updateY1 * font->m_texture->GetPitch() );

        font->m_updateY1 = font->m_updateY2 = 0;
        font->m_textureStatus = CGUIFontTTFQt::TEXTURE_READY;
    }

    VerifyGLState();

    // Turn Blending On
    m_GlF->glBlendFuncSeparate( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE );
    m_GlF->glEnable( GL_BLEND );
    m_GlF->glActiveTexture( GL_TEXTURE0 );
    m_GlF->glBindTexture( GL_TEXTURE_2D, font->m_nTexture );

    VerifyGLState();

    return true;
}

//============================================================================
void RenderGlWidget::lastEnd( CGUIFontTTFQt * font )
{
    VerifyGLState();

    // GLES 2.0 version.
    CRenderSystemQt * renderSystem = dynamic_cast< CRenderSystemQt* >( CServiceBroker::GetRenderSystem() );
    renderSystem->EnableGUIShader( SM_FONTS );

    GLint posLoc = renderSystem->GUIShaderGetPos();
    GLint colLoc = renderSystem->GUIShaderGetCol();
    GLint tex0Loc = renderSystem->GUIShaderGetCoord0();
    GLint modelLoc = renderSystem->GUIShaderGetModel();


    font->CreateStaticVertexBuffers();

    // Enable the attributes used by this shader
    m_GlF->glEnableVertexAttribArray( posLoc );
    m_GlF->glEnableVertexAttribArray( colLoc );
    m_GlF->glEnableVertexAttribArray( tex0Loc );

    if( !font->m_vertex.empty() )
    {
        // Deal with vertices that had to use software clipping
        std::vector<SVertex> vecVertices( 6 * ( font->m_vertex.size() / 4 ) );
        SVertex *vertices = &vecVertices[ 0 ];

        for( size_t i = 0; i < font->m_vertex.size(); i += 4 )
        {
            *vertices++ = font->m_vertex[ i ];
            *vertices++ = font->m_vertex[ i + 1 ];
            *vertices++ = font->m_vertex[ i + 2 ];

            *vertices++ = font->m_vertex[ i + 1 ];
            *vertices++ = font->m_vertex[ i + 3 ];
            *vertices++ = font->m_vertex[ i + 2 ];
        }

        vertices = &vecVertices[ 0 ];

        m_GlF->glVertexAttribPointer( posLoc, 3, GL_FLOAT, GL_FALSE, sizeof( SVertex ), ( char* )vertices + offsetof( SVertex, x ) );
        m_GlF->glVertexAttribPointer( colLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( SVertex ), ( char* )vertices + offsetof( SVertex, r ) );
        m_GlF->glVertexAttribPointer( tex0Loc, 2, GL_FLOAT, GL_FALSE, sizeof( SVertex ), ( char* )vertices + offsetof( SVertex, u ) );

        m_GlF->glDrawArrays( GL_TRIANGLES, 0, vecVertices.size() );
    }

    if( !font->m_vertexTrans.empty() )
    {
        // Deal with the vertices that can be hardware clipped and therefore translated

        // Bind our pre-calculated array to GL_ELEMENT_ARRAY_BUFFER
        m_GlF-> glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, font->m_elementArrayHandle );
        // Store current scissor
        CRect scissor = CServiceBroker::GetWinSystem()->GetGfxContext().StereoCorrection( CServiceBroker::GetWinSystem()->GetGfxContext().GetScissors() );

        for( size_t i = 0; i < font->m_vertexTrans.size(); i++ )
        {
            // Apply the clip rectangle
            CRect clip = renderSystem->ClipRectToScissorRect( font->m_vertexTrans[ i ].clip );
            if( !clip.IsEmpty() )
            {
                // intersect with current scissor
                clip.Intersect( scissor );
                // skip empty clip
                if( clip.IsEmpty() )
                    continue;
                renderSystem->SetScissors( clip );
            }

            // Apply the translation to the currently active (top-of-stack) model view matrix
            glMatrixModview.Push();
            glMatrixModview.Get().Translatef( font->m_vertexTrans[ i ].translateX, font->m_vertexTrans[ i ].translateY, font->m_vertexTrans[ i ].translateZ );
            m_GlF->glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glMatrixModview.Get() );

            // Bind the buffer to the OpenGL context's GL_ARRAY_BUFFER binding point
            m_GlF->glBindBuffer( GL_ARRAY_BUFFER, font->m_vertexTrans[ i ].vertexBuffer->bufferHandle );

            // Do the actual drawing operation, split into groups of characters no
            // larger than the pre-determined size of the element array
            for( size_t character = 0; font->m_vertexTrans[ i ].vertexBuffer->size > character; character += ELEMENT_ARRAY_MAX_CHAR_INDEX )
            {
                size_t count = font->m_vertexTrans[ i ].vertexBuffer->size - character;
                count = std::min<size_t>( count, ELEMENT_ARRAY_MAX_CHAR_INDEX );

                // Set up the offsets of the various vertex attributes within the buffer
                // object bound to GL_ARRAY_BUFFER
                m_GlF->glVertexAttribPointer( posLoc, 3, GL_FLOAT, GL_FALSE, sizeof( SVertex ), ( GLvoid * )( character * sizeof( SVertex ) * 4 + offsetof( SVertex, x ) ) );
                m_GlF->glVertexAttribPointer( colLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( SVertex ), ( GLvoid * )( character * sizeof( SVertex ) * 4 + offsetof( SVertex, r ) ) );
                m_GlF->glVertexAttribPointer( tex0Loc, 2, GL_FLOAT, GL_FALSE, sizeof( SVertex ), ( GLvoid * )( character * sizeof( SVertex ) * 4 + offsetof( SVertex, u ) ) );

                m_GlF->glDrawElements( GL_TRIANGLES, 6 * count, GL_UNSIGNED_SHORT, 0 );
            }

            glMatrixModview.Pop();
        }
        // Restore the original scissor rectangle
        renderSystem->SetScissors( scissor );
        // Restore the original model view matrix
        m_GlF->glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glMatrixModview.Get() );
        // Unbind GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER
        m_GlF->glBindBuffer( GL_ARRAY_BUFFER, 0 );
        m_GlF->glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }

    // Disable the attributes used by this shader
    m_GlF->glDisableVertexAttribArray( posLoc );
    m_GlF->glDisableVertexAttribArray( colLoc );
    m_GlF->glDisableVertexAttribArray( tex0Loc );

    renderSystem->DisableGUIShader();

    VerifyGLState();

}

//============================================================================
CVertexBuffer RenderGlWidget::createVertexBuffer( CGUIFontTTFQt * font, const std::vector<SVertex>& vertices )
{
    VerifyGLState();

    // Generate a unique buffer object name and put it in bufferHandle
    GLuint bufferHandle;
    m_GlF->glGenBuffers( 1, &bufferHandle );
    // Bind the buffer to the OpenGL context's GL_ARRAY_BUFFER binding point
    m_GlF->glBindBuffer( GL_ARRAY_BUFFER, bufferHandle );
    // Create a data store for the buffer object bound to the GL_ARRAY_BUFFER
    // binding point (i.e. our buffer object) and initialise it from the
    // specified client-side pointer
    m_GlF->glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( SVertex ), &vertices[ 0 ], GL_STATIC_DRAW );
    // Unbind GL_ARRAY_BUFFER
    m_GlF->glBindBuffer( GL_ARRAY_BUFFER, 0 );

    VerifyGLState();

    return CVertexBuffer( (unsigned int)bufferHandle, vertices.size() / 4, font );
}

//============================================================================
void RenderGlWidget::destroyVertexBuffer( CGUIFontTTFQt * font, CVertexBuffer& vertBuffer )
{
    if( vertBuffer.bufferHandle != 0 )
    {
        // Release the buffer name for reuse
        m_GlF->glDeleteBuffers( 1, ( GLuint * )&vertBuffer.bufferHandle );
        vertBuffer.bufferHandle = 0;
    }
}

//============================================================================
void RenderGlWidget::deleteHardwareTexture( CGUIFontTTFQt * font )
{
    if( font->m_textureStatus != CGUIFontTTFQt::TEXTURE_VOID )
    {
        if( m_GlF->glIsTexture( font->m_nTexture ) )
            CServiceBroker::GetGUI()->GetTextureManager().ReleaseHwTexture( font->m_nTexture );

        font->m_textureStatus = CGUIFontTTFQt::TEXTURE_VOID;
        font->m_updateY1 = font->m_updateY2 = 0;
    }
}

//============================================================================
void RenderGlWidget::createStaticVertexBuffers( CGUIFontTTFQt * font )
{
    VerifyGLState();

    // Bind a new buffer to the OpenGL context's GL_ELEMENT_ARRAY_BUFFER binding point
    m_GlF->glGenBuffers( 1, &font->m_elementArrayHandle );
    m_GlF->glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, font->m_elementArrayHandle );
    // Create an array holding the mesh indices to convert quads to triangles
    GLushort index[ ELEMENT_ARRAY_MAX_CHAR_INDEX ][ 6 ];
    for( size_t i = 0; i < ELEMENT_ARRAY_MAX_CHAR_INDEX; i++ )
    {
        index[ i ][ 0 ] = 4 * i;
        index[ i ][ 1 ] = 4 * i + 1;
        index[ i ][ 2 ] = 4 * i + 2;
        index[ i ][ 3 ] = 4 * i + 1;
        index[ i ][ 4 ] = 4 * i + 3;
        index[ i ][ 5 ] = 4 * i + 2;
    }

    m_GlF->glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof index, index, GL_STATIC_DRAW );
    m_GlF->glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    font->m_staticVertexBufferCreated = true;
    VerifyGLState();

}

//============================================================================
void RenderGlWidget::destroyStaticVertexBuffers( CGUIFontTTFQt * font )
{
    m_GlF->glDeleteBuffers( 1, &font->m_elementArrayHandle );
    font->m_staticVertexBufferCreated = false;
}
