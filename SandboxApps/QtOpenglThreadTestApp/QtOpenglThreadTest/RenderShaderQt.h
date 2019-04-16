/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://kodi.tv
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

#pragma once

#define RENDER_FLAG_BOT         0x01
#define RENDER_FLAG_TOP         0x02
#define RENDER_FLAG_BOTH (RENDER_FLAG_BOT | RENDER_FLAG_TOP)
#define RENDER_FLAG_FIELDMASK   0x03

#define RENDER_FLAG_FIELD0      0x80
#define RENDER_FLAG_FIELD1      0x100

// #define RENDER_FLAG_LAST        0x40

#define RENDER_FLAG_NOOSD       0x04 /* don't draw any osd */
#define RENDER_FLAG_NOOSDALPHA  0x08 /* don't allow alpha when osd is drawn */

/* these two flags will be used if we need to render same image twice (bob deinterlacing) */
#define RENDER_FLAG_NOLOCK      0x10   /* don't attempt to lock texture before rendering */
#define RENDER_FLAG_NOUNLOCK    0x20   /* don't unlock texture after rendering */

/* this defines what color translation coefficients */
#define CONF_FLAGS_YUVCOEF_MASK(a) ((a) & 0x07)
#define CONF_FLAGS_YUVCOEF_BT709 0x01
#define CONF_FLAGS_YUVCOEF_BT601 0x02
#define CONF_FLAGS_YUVCOEF_240M  0x03
#define CONF_FLAGS_YUVCOEF_EBU   0x04
#define CONF_FLAGS_YUVCOEF_BT2020 0x05

#define CONF_FLAGS_YUV_FULLRANGE 0x08
#define CONF_FLAGS_FULLSCREEN    0x10

/* defines color primaries */
#define CONF_FLAGS_COLPRI_MASK(a) ((a) & 0xe0)
#define CONF_FLAGS_COLPRI_BT709   0x20  // sRGB, HDTV (ITU-R BT.709)
#define CONF_FLAGS_COLPRI_BT470M  0x40  // NTSC (1953) (FCC 1953, ITU-R BT.470 System M)
#define CONF_FLAGS_COLPRI_BT470BG 0x60  // PAL/SECAM (1970) (EBU Tech. 3213, ITU-R BT.470 System B, G)
#define CONF_FLAGS_COLPRI_170M    0x80  // NTSC (1987) (SMPTE RP 145 "SMPTE C", SMPTE 170M)
#define CONF_FLAGS_COLPRI_240M    0xa0  // SMPTE-240M
#define CONF_FLAGS_COLPRI_BT2020  0xc0  // UHDTV (ITU-R BT.2020)

/* defines chroma subsampling sample location */
#define CONF_FLAGS_CHROMA_MASK(a) ((a) & 0x0300)
#define CONF_FLAGS_CHROMA_LEFT    0x0100
#define CONF_FLAGS_CHROMA_CENTER  0x0200
#define CONF_FLAGS_CHROMA_TOPLEFT 0x0300

/* defines 3d modes */
#define CONF_FLAGS_STEREO_MODE_MASK(a) ((a) & 0x007000)
#define CONF_FLAGS_STEREO_MODE_SBS     0x001000
#define CONF_FLAGS_STEREO_MODE_TAB     0x002000

#define CONF_FLAGS_STEREO_CADENCE(a) ((a) & 0x008000)
#define CONF_FLAGS_STEREO_CADANCE_LEFT_RIGHT 0x000000
#define CONF_FLAGS_STEREO_CADANCE_RIGHT_LEFT 0x008000

enum RENDER_STEREO_VIEW
{
  RENDER_STEREO_VIEW_OFF,
  RENDER_STEREO_VIEW_LEFT,
  RENDER_STEREO_VIEW_RIGHT,
};

enum RENDER_STEREO_MODE
{
  RENDER_STEREO_MODE_OFF,
  RENDER_STEREO_MODE_SPLIT_HORIZONTAL,
  RENDER_STEREO_MODE_SPLIT_VERTICAL,
  RENDER_STEREO_MODE_ANAGLYPH_RED_CYAN,
  RENDER_STEREO_MODE_ANAGLYPH_GREEN_MAGENTA,
  RENDER_STEREO_MODE_ANAGLYPH_YELLOW_BLUE,
  RENDER_STEREO_MODE_INTERLACED,
  RENDER_STEREO_MODE_CHECKERBOARD,
  RENDER_STEREO_MODE_HARDWAREBASED,
  RENDER_STEREO_MODE_MONO,
  RENDER_STEREO_MODE_COUNT,

  // Pseudo modes
  RENDER_STEREO_MODE_AUTO = 100,
  RENDER_STEREO_MODE_UNDEFINED = 999,
};

enum EShaderFormat
{
  SHADER_NONE,
  SHADER_YV12,
  SHADER_YV12_9,
  SHADER_YV12_10,
  SHADER_YV12_12,
  SHADER_YV12_14,
  SHADER_YV12_16,
  SHADER_NV12,
  SHADER_YUY2,
  SHADER_UYVY,
  SHADER_NV12_RRG
};


#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>


enum EShaderType
{
    eShaderGui,
    eShaderVideoFormat,
    eShaderVideoFilter,

    eMaxShaderType
};

#define HAVE_QT_GUI

enum ESHADERMETHOD
{
    SM_DEFAULT,
    SM_TEXTURE,
    SM_MULTI,
    SM_FONTS,
    SM_TEXTURE_NOBLEND,
    SM_MULTI_BLENDCOLOR,
    SM_TEXTURE_RGBA,
    SM_TEXTURE_RGBA_OES,
    SM_TEXTURE_RGBA_BLENDCOLOR,
    SM_TEXTURE_RGBA_BOB,
    SM_TEXTURE_RGBA_BOB_OES,

#ifdef HAVE_QT_GUI

    SM_VIDEO_YV12_BASIC,
    SM_VIDEO_NV12_BASIC,
    SM_VIDEO_YUY2_BASIC,
    SM_VIDEO_UYVY_BASIC,
    SM_VIDEO_NV12_RGB_BASIC,

    SM_VIDEO_YV12_BOB,
    SM_VIDEO_NV12_BOB,
    SM_VIDEO_YUY2_BOB,
    SM_VIDEO_UYVY_BOB,
    SM_VIDEO_NV12_RGB_BOB,

    SM_VID_FILTER_DEFAULT,
    SM_VID_FILTER_CONVOLUTION_4X4_RGBA,
    SM_VID_FILTER_CONVOLUTION_4X4_FLOAT,
    SM_VID_FILTER_CONVOLUTION_6X6_RGBA,
    SM_VID_FILTER_CONVOLUTION_6X6_FLOAT,

#endif // HAVE_QT_GUI

    SM_SHADER_NONE,

    SM_MAX
};


enum ESCALINGMETHOD
{
  VS_SCALINGMETHOD_NEAREST=0,
  VS_SCALINGMETHOD_LINEAR,
  VS_SCALINGMETHOD_CUBIC,
  VS_SCALINGMETHOD_LANCZOS2,
  VS_SCALINGMETHOD_LANCZOS3_FAST,
  VS_SCALINGMETHOD_LANCZOS3,
  VS_SCALINGMETHOD_SINC8,
  VS_SCALINGMETHOD_BICUBIC_SOFTWARE,
  VS_SCALINGMETHOD_LANCZOS_SOFTWARE,
  VS_SCALINGMETHOD_SINC_SOFTWARE,
  VS_SCALINGMETHOD_VDPAU_HARDWARE,
  VS_SCALINGMETHOD_DXVA_HARDWARE,
  VS_SCALINGMETHOD_AUTO,
  VS_SCALINGMETHOD_SPLINE36_FAST,
  VS_SCALINGMETHOD_SPLINE36,
  VS_SCALINGMETHOD_MAX // do not use and keep as last enum value.
};

#include <math.h>
#include <memory>
#include <string.h>
#include <algorithm>

class TransformMatrix
{
public:

    float m[3][4];
    float alpha;
    bool identity;

  TransformMatrix()
  {
    Reset();
  };

  void Reset()
  {
    m[0][0] = 1.0f; m[0][1] = m[0][2] = m[0][3] = 0.0f;
    m[1][0] = m[1][2] = m[1][3] = 0.0f; m[1][1] = 1.0f;
    m[2][0] = m[2][1] = m[2][3] = 0.0f; m[2][2] = 1.0f;
    alpha = 1.0f;
    identity = true;
  };

  static TransformMatrix CreateTranslation(float transX, float transY, float transZ = 0)
  {
    TransformMatrix translation;
    translation.SetTranslation(transX, transY, transZ);
    return translation;
  }
  void SetTranslation(float transX, float transY, float transZ)
  {
    m[0][1] = m[0][2] = 0.0f; m[0][0] = 1.0f; m[0][3] = transX;
    m[1][0] = m[1][2] = 0.0f; m[1][1] = 1.0f; m[1][3] = transY;
    m[2][0] = m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = transZ;
    alpha = 1.0f;
    identity = (transX == 0 && transY == 0 && transZ == 0);
  }
  static TransformMatrix CreateScaler(float scaleX, float scaleY, float scaleZ = 1.0f)
  {
    TransformMatrix scaler;
    scaler.m[0][0] = scaleX;
    scaler.m[1][1] = scaleY;
    scaler.m[2][2] = scaleZ;
    scaler.identity = (scaleX == 1 && scaleY == 1 && scaleZ == 1);
    return scaler;
  };
  void SetScaler(float scaleX, float scaleY, float centerX, float centerY)
  {
    // Trans(centerX,centerY,centerZ)*Scale(scaleX,scaleY,scaleZ)*Trans(-centerX,-centerY,-centerZ)
    float centerZ = 0.0f, scaleZ = 1.0f;
    m[0][0] = scaleX;  m[0][1] = 0.0f;    m[0][2] = 0.0f;    m[0][3] = centerX*(1-scaleX);
    m[1][0] = 0.0f;    m[1][1] = scaleY;  m[1][2] = 0.0f;    m[1][3] = centerY*(1-scaleY);
    m[2][0] = 0.0f;    m[2][1] = 0.0f;    m[2][2] = scaleZ;  m[2][3] = centerZ*(1-scaleZ);
    alpha = 1.0f;
    identity = (scaleX == 1 && scaleY == 1);
  };
  void SetXRotation(float angle, float y, float z, float ar = 1.0f)
  { // angle about the X axis, centered at y,z where our coordinate system has aspect ratio ar.
    // Trans(0,y,z)*Scale(1,1/ar,1)*RotateX(angle)*Scale(ar,1,1)*Trans(0,-y,-z);
    float c = cos(angle); float s = sin(angle);
    m[0][0] = ar;    m[0][1] = 0.0f;  m[0][2] = 0.0f;   m[0][3] = 0.0f;
    m[1][0] = 0.0f;  m[1][1] = c/ar;  m[1][2] = -s/ar;  m[1][3] = (-y*c+s*z)/ar + y;
    m[2][0] = 0.0f;  m[2][1] = s;     m[2][2] = c;      m[2][3] = (-y*s-c*z) + z;
    alpha = 1.0f;
    identity = (angle == 0);
  }
  void SetYRotation(float angle, float x, float z, float ar = 1.0f)
  { // angle about the Y axis, centered at x,z where our coordinate system has aspect ratio ar.
    // Trans(x,0,z)*Scale(1/ar,1,1)*RotateY(angle)*Scale(ar,1,1)*Trans(-x,0,-z);
    float c = cos(angle); float s = sin(angle);
    m[0][0] = c;     m[0][1] = 0.0f;  m[0][2] = -s/ar;  m[0][3] = -x*c + s*z/ar + x;
    m[1][0] = 0.0f;  m[1][1] = 1.0f;  m[1][2] = 0.0f;   m[1][3] = 0.0f;
    m[2][0] = ar*s;  m[2][1] = 0.0f;  m[2][2] = c;      m[2][3] = -ar*x*s - c*z + z;
    alpha = 1.0f;
    identity = (angle == 0);
  }
  static TransformMatrix CreateZRotation(float angle, float x, float y, float ar = 1.0f)
  { // angle about the Z axis, centered at x,y where our coordinate system has aspect ratio ar.
    // Trans(x,y,0)*Scale(1/ar,1,1)*RotateZ(angle)*Scale(ar,1,1)*Trans(-x,-y,0)
    TransformMatrix rot;
    rot.SetZRotation(angle, x, y, ar);
    return rot;
  }
  void SetZRotation(float angle, float x, float y, float ar = 1.0f)
  { // angle about the Z axis, centered at x,y where our coordinate system has aspect ratio ar.
    // Trans(x,y,0)*Scale(1/ar,1,1)*RotateZ(angle)*Scale(ar,1,1)*Trans(-x,-y,0)
    float c = cos(angle); float s = sin(angle);
    m[0][0] = c;     m[0][1] = -s/ar;  m[0][2] = 0.0f;  m[0][3] = -x*c + s*y/ar + x;
    m[1][0] = s*ar;  m[1][1] = c;      m[1][2] = 0.0f;  m[1][3] = -ar*x*s - c*y + y;
    m[2][0] = 0.0f;  m[2][1] = 0.0f;   m[2][2] = 1.0f;  m[2][3] = 0.0f;
    alpha = 1.0f;
    identity = (angle == 0);
  }
  static TransformMatrix CreateFader(float a)
  {
    TransformMatrix fader;
    fader.SetFader(a);
    return fader;
  }
  void SetFader(float a)
  {
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    alpha = a;
    identity = (a == 1.0f);
  }

  // multiplication operators
  const TransformMatrix &operator *=(const TransformMatrix &right)
  {
    if (right.identity)
      return *this;
    if (identity)
    {
      *this = right;
      return *this;
    }
    float t00 = m[0][0] * right.m[0][0] + m[0][1] * right.m[1][0] + m[0][2] * right.m[2][0];
    float t01 = m[0][0] * right.m[0][1] + m[0][1] * right.m[1][1] + m[0][2] * right.m[2][1];
    float t02 = m[0][0] * right.m[0][2] + m[0][1] * right.m[1][2] + m[0][2] * right.m[2][2];
    m[0][3] = m[0][0] * right.m[0][3] + m[0][1] * right.m[1][3] + m[0][2] * right.m[2][3] + m[0][3];
    m[0][0] = t00; m[0][1] = t01; m[0][2] = t02;
    t00 = m[1][0] * right.m[0][0] + m[1][1] * right.m[1][0] + m[1][2] * right.m[2][0];
    t01 = m[1][0] * right.m[0][1] + m[1][1] * right.m[1][1] + m[1][2] * right.m[2][1];
    t02 = m[1][0] * right.m[0][2] + m[1][1] * right.m[1][2] + m[1][2] * right.m[2][2];
    m[1][3] = m[1][0] * right.m[0][3] + m[1][1] * right.m[1][3] + m[1][2] * right.m[2][3] + m[1][3];
    m[1][0] = t00; m[1][1] = t01; m[1][2] = t02;
    t00 = m[2][0] * right.m[0][0] + m[2][1] * right.m[1][0] + m[2][2] * right.m[2][0];
    t01 = m[2][0] * right.m[0][1] + m[2][1] * right.m[1][1] + m[2][2] * right.m[2][1];
    t02 = m[2][0] * right.m[0][2] + m[2][1] * right.m[1][2] + m[2][2] * right.m[2][2];
    m[2][3] = m[2][0] * right.m[0][3] + m[2][1] * right.m[1][3] + m[2][2] * right.m[2][3] + m[2][3];
    m[2][0] = t00; m[2][1] = t01; m[2][2] = t02;
    alpha *= right.alpha;
    identity = false;
    return *this;
  }

  TransformMatrix operator *(const TransformMatrix &right) const
  {
    if (right.identity)
      return *this;
    if (identity)
      return right;
    TransformMatrix result;
    result.m[0][0] = m[0][0] * right.m[0][0] + m[0][1] * right.m[1][0] + m[0][2] * right.m[2][0];
    result.m[0][1] = m[0][0] * right.m[0][1] + m[0][1] * right.m[1][1] + m[0][2] * right.m[2][1];
    result.m[0][2] = m[0][0] * right.m[0][2] + m[0][1] * right.m[1][2] + m[0][2] * right.m[2][2];
    result.m[0][3] = m[0][0] * right.m[0][3] + m[0][1] * right.m[1][3] + m[0][2] * right.m[2][3] + m[0][3];
    result.m[1][0] = m[1][0] * right.m[0][0] + m[1][1] * right.m[1][0] + m[1][2] * right.m[2][0];
    result.m[1][1] = m[1][0] * right.m[0][1] + m[1][1] * right.m[1][1] + m[1][2] * right.m[2][1];
    result.m[1][2] = m[1][0] * right.m[0][2] + m[1][1] * right.m[1][2] + m[1][2] * right.m[2][2];
    result.m[1][3] = m[1][0] * right.m[0][3] + m[1][1] * right.m[1][3] + m[1][2] * right.m[2][3] + m[1][3];
    result.m[2][0] = m[2][0] * right.m[0][0] + m[2][1] * right.m[1][0] + m[2][2] * right.m[2][0];
    result.m[2][1] = m[2][0] * right.m[0][1] + m[2][1] * right.m[1][1] + m[2][2] * right.m[2][1];
    result.m[2][2] = m[2][0] * right.m[0][2] + m[2][1] * right.m[1][2] + m[2][2] * right.m[2][2];
    result.m[2][3] = m[2][0] * right.m[0][3] + m[2][1] * right.m[1][3] + m[2][2] * right.m[2][3] + m[2][3];
    result.alpha = alpha * right.alpha;
    result.identity = false;
    return result;
  }

  inline void TransformPosition(float &x, float &y, float &z) const
  {
    float newX = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    float newY = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    z = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
    y = newY;
    x = newX;
  }

#define XBMC_FORCE_INLINE
  inline void TransformPositionUnscaled(float &x, float &y, float &z) const XBMC_FORCE_INLINE
  {
    float n;
    // calculate the norm of the transformed (but not translated) vectors involved
    n = sqrt(m[0][0]*m[0][0] + m[0][1]*m[0][1] + m[0][2]*m[0][2]);
    float newX = (m[0][0] * x + m[0][1] * y + m[0][2] * z)/n + m[0][3];
    n = sqrt(m[1][0]*m[1][0] + m[1][1]*m[1][1] + m[1][2]*m[1][2]);
    float newY = (m[1][0] * x + m[1][1] * y + m[1][2] * z)/n + m[1][3];
    n = sqrt(m[2][0]*m[2][0] + m[2][1]*m[2][1] + m[2][2]*m[2][2]);
    float newZ = (m[2][0] * x + m[2][1] * y + m[2][2] * z)/n + m[2][3];
    z = newZ;
    y = newY;
    x = newX;
  }

  inline void InverseTransformPosition(float &x, float &y) const XBMC_FORCE_INLINE
  { // used for mouse - no way to find z
    x -= m[0][3]; y -= m[1][3];
    float detM = m[0][0]*m[1][1] - m[0][1]*m[1][0];
    float newX = (m[1][1] * x - m[0][1] * y)/detM;
    y = (-m[1][0] * x + m[0][0] * y)/detM;
    x = newX;
  }

  inline float TransformXCoord(float x, float y, float z) const XBMC_FORCE_INLINE
  {
    return m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
  }

  inline float TransformYCoord(float x, float y, float z) const XBMC_FORCE_INLINE
  {
    return m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
  }

  inline float TransformZCoord(float x, float y, float z) const XBMC_FORCE_INLINE
  {
    return m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
  }
};

inline bool operator==(const TransformMatrix &a, const TransformMatrix &b)
{
  return a.alpha == b.alpha && ((a.identity && b.identity) ||
      (!a.identity && !b.identity && std::equal(&a.m[0][0], &a.m[0][0] + sizeof (a.m) / sizeof (a.m[0][0]), &b.m[0][0])));
}

inline bool operator!=(const TransformMatrix &a, const TransformMatrix &b)
{
  return !operator==(a, b);
}

class RenderGlWidget;

class RenderShaderQt : public QOpenGLShaderProgram
{
public:
    RenderShaderQt() = delete;
    RenderShaderQt( ESHADERMETHOD shaderMethod, EShaderType shaderType, QString shaderName, RenderGlWidget * renderWidget );

    bool                        compileAndLink( const char * vertexShaderCode, const char * fragmentShaderCode );

    bool                        isShaderValid( ) { return m_validated; }
    EShaderType                 getShaderType( ) { return m_ShaderType; }

    bool                        enableShader();
    bool                        disableShader();

    bool                        onEnabled();
    bool                        onShaderGuiEnabled( QOpenGLFunctions * glf );
    bool                        onShaderVideoFormatEnabled( QOpenGLFunctions * glf );
    bool                        onShaderVideoFilterEnabled( QOpenGLFunctions * glf );

    void                        onDisabled();
    void                        onFree();

    void                        setShaderFlags(  unsigned int flags )                   { m_flags = flags; }
    void                        setShaderScalingMethod( ESCALINGMETHOD scaling )        { m_ScalingMethod = scaling; }

    GLint                       GetPosLoc() { return m_hPos; }
    GLint                       GetColLoc() { return m_hCol; }
    GLint                       GetCord0Loc() { return m_hCord0; }
    GLint                       GetCord1Loc() { return m_hCord1; }
    GLint                       GetUniColLoc() { return m_hUniCol; }
    GLint                       GetCoord0MatrixLoc() { return m_hCoord0Matrix; }
    GLint                       GetFieldLoc() { return m_hField; }
    GLint                       GetStepLoc() { return m_hStep; }
    GLint                       GetContrastLoc() { return m_hContrast; }
    GLint                       GetBrightnessLoc() { return m_hBrightness; }
    GLint                       GetModelLoc() { return m_hModel; }
    bool                        HardwareClipIsPossible() { return m_clipPossible; }
    GLfloat                     GetClipXFactor() { return m_clipXFactor; }
    GLfloat                     GetClipXOffset() { return m_clipXOffset; }
    GLfloat                     GetClipYFactor() { return m_clipYFactor; }
    GLfloat                     GetClipYOffset() { return m_clipYOffset; }

    // yuv shader
    virtual void                shaderSetField( int field );
    virtual void                shaderSetWidth( int w );
    virtual void                shaderSetHeight( int h );

    virtual void                shaderSetBlack( float black );
    virtual void                shaderSetContrast( float contrast );
    virtual void                shaderSetConvertFullColorRange( bool convertFullRange );

    virtual int                 shaderGetVertexLoc(  );
    virtual int                 shaderGetYcoordLoc(  );
    virtual int                 shaderGetUcoordLoc(  );
    virtual int                 shaderGetVcoordLoc(  );

    virtual void                shaderSetMatrices( const float *p, const float *m );
    virtual void                shaderSetAlpha( float alpha );

    virtual void                shaderSetFlags( unsigned int flags );
    virtual void                shaderSetFormat( EShaderFormat format );
    virtual void                shaderSourceTexture( int ytex );
    virtual void                shaderSetStepX( float stepX );
    virtual void                shaderSetStepY( float stepY );

    // filter shader
    virtual bool                shaderGetTextureFilter( int& filter );
    virtual int                 shaderGetcoordLoc(  );

    // renderqt
    virtual int                 shaderVertexAttribPointer( unsigned int index, int size, int type, bool normalized, int stride, const void * pointer );
    virtual void                shaderEnableVertexAttribArray( int arrayId ) ;
    virtual void                shaderDisableVertexAttribArray( int arrayId );

protected:
    void                        onCompiledAndLinked();
    void                        onCompiledAndLinkedGui( QOpenGLFunctions * glf );
    void                        onCompiledAndLinkedVideoFormat( QOpenGLFunctions * glf );
    void                        onCompiledAndLinkedVideoFilter( QOpenGLFunctions * glf );

    const char *                describeShader( ESHADERMETHOD shaderMethod );

    //=== common to all shaders ===//
    ESHADERMETHOD               m_ShaderMethod;
    ESCALINGMETHOD              m_ScalingMethod;
    EShaderType                 m_ShaderType;
    QString                     m_ShaderName;
    RenderGlWidget *            m_RenderWidget;
    bool                        m_validated;

    const GLfloat *             m_proj = nullptr;
    const GLfloat *             m_model = nullptr;
    GLint                       m_hProj = -1;
    GLint                       m_hModel = -1;

    //=== gui shader ===//
    GLint                       m_hTex0 = 0;
    GLint                       m_hTex1 = 0;
    GLint                       m_hUniCol = 0;
    GLint                       m_hPos = 0;
    GLint                       m_hCol = 0;
    GLint                       m_hCord0 = 0;
    GLint                       m_hCord1 = -1;
    GLint                       m_hCoord0Matrix = 0;

    GLint                       m_hField = 0;
    GLint                       m_hContrast = 0;
    GLint                       m_hBrightness = 0;

    bool                        m_clipPossible;
    GLfloat                     m_clipXFactor;
    GLfloat                     m_clipXOffset;
    GLfloat                     m_clipYFactor;
    GLfloat                     m_clipYOffset;

    //=== gui and format common ===//
    GLint                       m_hStep = 0;

    //=== video format shader ===//
    unsigned int                m_flags = 0;
    EShaderFormat               m_format = SHADER_YV12;
    int                         m_field = 0;

    float                       m_black = 0.0f;
    float                       m_contrast = 0.0f;

    // shader attribute handles
    GLint                       m_hYTex = 0;
    GLint                       m_hUTex = 0;
    GLint                       m_hVTex = 0;
    GLint                       m_hMatrix = 0;

    GLint                       m_hYcoord = -1;
    GLint                       m_hUcoord = -1;
    GLint                       m_hVcoord = -1;

    bool                        m_convertFullRange = false;

    //=== format and filter common ===//
    int                         m_width = 1;
    int                         m_height = 1;
    GLint                       m_hVertex = -1;
    GLint                       m_hAlpha = -1;
    GLfloat                     m_alpha  = 1;

    //=== video filter shader ===//
    float                       m_stepX = 0;
    float                       m_stepY = 0;
    GLint                       m_sourceTexUnit = 0;

    // shader attribute handles
    GLint                       m_hSourceTex = 0;
    GLint                       m_hStepXY = 0;

    GLint                       m_hStepX = 0;
    GLint                       m_hStepY = 0;

    GLint                       m_hcoord = 0;

    // shader handles to kernel textures
    GLint                       m_hKernTex = -1;

    GLuint                      m_kernelTex1 = 0;

    bool                        m_floattex = false; // if float textures are supported
    GLint                       m_internalformat = 0;

};

