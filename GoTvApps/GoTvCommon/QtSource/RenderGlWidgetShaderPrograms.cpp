/*
 *      Copyright (C) 2010-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

// has GPL license because mostly copied from kodi

#ifdef INCLUDE_SHADER_PROGRAMS

    /*
    if( !m_Shader )
    {
        m_Shader = new QOpenGLShaderProgram();
    }

    const char * vertexProgram =
        "attribute highp vec4 targetVertex;\n"
        "attribute highp vec2 textureCoordinates;\n"
        "uniform highp mat4 positionMatrix;\n"
        "varying highp vec2 textureCoord;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = positionMatrix * targetVertex;\n"
        "    textureCoord = textureCoordinates;\n"
        "}\n";

    static const char * vertexShader =
        "uniform sampler2D texY;\n"
        "uniform sampler2D texU;\n"
        "uniform sampler2D texV;\n"
        "uniform mediump mat4 colorMatrix;\n"
        "varying highp vec2 textureCoord;\n"
        "uniform lowp float opacity;"
        "void main(void)\n"
        "{\n"
        "    highp vec4 color = vec4(\n"
        "           texture2D(texY, textureCoord.st).r,\n"
        "           texture2D(texV, textureCoord.st).r,\n" // !!!! mind the swp
        "           texture2D(texU, textureCoord.st).r,\n"
        "           1.0);\n"
        "    gl_FragColor = colorMatrix * color * opacity;\n"
        "}\n";
*/

static const char * gles_shader_vert =
"#version 100\n"
"attribute vec4 m_attrpos;\n"
"attribute vec4 m_attrcol;\n"
"attribute vec4 m_attrcord0;\n"
"attribute vec4 m_attrcord1;\n"
"varying vec4   m_cord0;\n"
"varying vec4   m_cord1;\n"
"varying lowp vec4 m_colour;\n"
"uniform mat4   m_proj;\n"
"uniform mat4   m_model;\n"
"uniform mat4   m_coord0Matrix;\n"
"void main()\n"
"{\n"
"    mat4 mvp = m_proj * m_model;\n"
"    gl_Position = mvp * m_attrpos;\n"
"    m_colour = m_attrcol;\n"
"    m_cord0 = m_coord0Matrix * m_attrcord0;\n"
"    m_cord1 = m_attrcord1;\n"
"}\n";



//"#if defined(KODI_LIMITED_RANGE)\n"
//"    gl_FragColor.rgb *= ( 235.0 - 16.0 ) / 255.0;\n"
//"    gl_FragColor.rgb += 16.0 / 255.0;\n"
//"#endif\n"
//"precision lowp float;\n"

static const char * gles_shader_default_frag =
"#version 100\n"
"uniform lowp vec4 m_unicol;\n"
"void main()\n"
"{\n"
"    gl_FragColor = m_unicol;\n"
"}\n";




/*
m_pShader[ SM_DEFAULT ] = new CGLESShader( "gles_shader.vert", "gles_shader_default.frag", defines );
if( !m_pShader[ SM_DEFAULT ]->CompileAndLink() )
{
    m_pShader[ SM_DEFAULT ]->Free();
    delete m_pShader[ SM_DEFAULT ];
    m_pShader[ SM_DEFAULT ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_default.frag - compile and link failed" );
}

m_pShader[ SM_TEXTURE ] = new CGLESShader( "gles_shader_texture.frag", defines );
if( !m_pShader[ SM_TEXTURE ]->CompileAndLink() )
{
    m_pShader[ SM_TEXTURE ]->Free();
    delete m_pShader[ SM_TEXTURE ];
    m_pShader[ SM_TEXTURE ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_texture.frag - compile and link failed" );
}

m_pShader[ SM_MULTI ] = new CGLESShader( "gles_shader_multi.frag", defines );
if( !m_pShader[ SM_MULTI ]->CompileAndLink() )
{
    m_pShader[ SM_MULTI ]->Free();
    delete m_pShader[ SM_MULTI ];
    m_pShader[ SM_MULTI ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_multi.frag - compile and link failed" );
}

m_pShader[ SM_FONTS ] = new CGLESShader( "gles_shader_fonts.frag", defines );
if( !m_pShader[ SM_FONTS ]->CompileAndLink() )
{
    m_pShader[ SM_FONTS ]->Free();
    delete m_pShader[ SM_FONTS ];
    m_pShader[ SM_FONTS ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_fonts.frag - compile and link failed" );
}

m_pShader[ SM_TEXTURE_NOBLEND ] = new CGLESShader( "gles_shader_texture_noblend.frag", defines );
if( !m_pShader[ SM_TEXTURE_NOBLEND ]->CompileAndLink() )
{
    m_pShader[ SM_TEXTURE_NOBLEND ]->Free();
    delete m_pShader[ SM_TEXTURE_NOBLEND ];
    m_pShader[ SM_TEXTURE_NOBLEND ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_texture_noblend.frag - compile and link failed" );
}

m_pShader[ SM_MULTI_BLENDCOLOR ] = new CGLESShader( "gles_shader_multi_blendcolor.frag", defines );
if( !m_pShader[ SM_MULTI_BLENDCOLOR ]->CompileAndLink() )
{
    m_pShader[ SM_MULTI_BLENDCOLOR ]->Free();
    delete m_pShader[ SM_MULTI_BLENDCOLOR ];
    m_pShader[ SM_MULTI_BLENDCOLOR ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_multi_blendcolor.frag - compile and link failed" );
}

m_pShader[ SM_TEXTURE_RGBA ] = new CGLESShader( "gles_shader_rgba.frag", defines );
if( !m_pShader[ SM_TEXTURE_RGBA ]->CompileAndLink() )
{
    m_pShader[ SM_TEXTURE_RGBA ]->Free();
    delete m_pShader[ SM_TEXTURE_RGBA ];
    m_pShader[ SM_TEXTURE_RGBA ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_rgba.frag - compile and link failed" );
}

m_pShader[ SM_TEXTURE_RGBA_BLENDCOLOR ] = new CGLESShader( "gles_shader_rgba_blendcolor.frag", defines );
if( !m_pShader[ SM_TEXTURE_RGBA_BLENDCOLOR ]->CompileAndLink() )
{
    m_pShader[ SM_TEXTURE_RGBA_BLENDCOLOR ]->Free();
    delete m_pShader[ SM_TEXTURE_RGBA_BLENDCOLOR ];
    m_pShader[ SM_TEXTURE_RGBA_BLENDCOLOR ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_rgba_blendcolor.frag - compile and link failed" );
}

m_pShader[ SM_TEXTURE_RGBA_BOB ] = new CGLESShader( "gles_shader_rgba_bob.frag", defines );
if( !m_pShader[ SM_TEXTURE_RGBA_BOB ]->CompileAndLink() )
{
    m_pShader[ SM_TEXTURE_RGBA_BOB ]->Free();
    delete m_pShader[ SM_TEXTURE_RGBA_BOB ];
    m_pShader[ SM_TEXTURE_RGBA_BOB ] = nullptr;
    CLog::Log( LOGERROR, "GUI Shader gles_shader_rgba_bob.frag - compile and link failed" );
}
*/

//============================================================================
void RenderGlWidget::compileShader( int shaderIdx )
{
    const char * vertexShaderCode = nullptr;
    const char * fragmentShaderCode = nullptr;
    QString shaderName = "SM_UNKNOWN";
    switch( shaderIdx )
    {
    case SM_DEFAULT:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_default_frag;
        shaderName = "SM_DEFAULT";
        break;

    }

    if( vertexShaderCode && fragmentShaderCode )
    {
        ShaderQt * shader = new ShaderQt( shaderName, this );
        if( shader->compileAndLink( vertexShaderCode, fragmentShaderCode ) )
        {
            // success
            LogMsg( LOG_INFO, "Success compile shader %s", shaderName.toUtf8().constData() );
           m_Shaders[ shaderIdx ] = shader;
        }
        else
        {
            LogMsg( LOG_ERROR, "Failed to compile shader %s", shaderName.toUtf8().constData() );
        }

    }
}

#endif // INCLUDE_SHADER_PROGRAMS
