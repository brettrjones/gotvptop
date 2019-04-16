#if defined(SHADERS_INCLUDE)
static const char * gles_shader_vert =
"#version 120\n"
"attribute vec4 m_attrpos;\n"
"attribute vec4 m_attrcol;\n"
"attribute vec4 m_attrcord0;\n"
"attribute vec4 m_attrcord1;\n"
"varying vec4 m_cord0;\n"
"varying vec4 m_cord1;\n"
"varying vec4 m_colour;\n"
"uniform mat4 m_proj;\n"
"uniform mat4 m_model;\n"
"void main ()\n"
"{\n"
" mat4 mvp    = m_proj * m_model;\n"
"  gl_Position = mvp * m_attrpos;\n"
"  m_colour    = m_attrcol;\n"
"  m_cord0     = m_attrcord0;\n"
"  m_cord1     = m_attrcord1;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_vert_defaut =
"precision lowp float;\n"
#else
static const char * gles_shader_vert_defaut =
#endif
"attribute vec4 m_attrpos;\n"
"uniform mat4 m_proj;\n"
"uniform mat4 m_model;\n"
"void main ()\n"
"{\n"
"  mat4 mvp    = m_proj * m_model;\n"
"  gl_Position = mvp * m_attrpos;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_default_frag =
"precision lowp float;\n"
#else
static const char * gles_shader_default_frag =
#endif
"uniform vec4 m_unicol;\n"
"// SM_DEFAULT shader\n"
"void main()\n"
"{\n"
"    gl_FragColor = m_unicol;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_texture_frag =
"precision lowp float;\n"
#else
static const char * gles_shader_texture_frag =
#endif
"uniform   sampler2D m_samp0;\n"
"uniform   lowp vec4 m_unicol;\n"
"varying   vec4      m_cord0;\n"
"// SM_TEXTURE shader\n"
"void main()\n"
"{\n"
"    gl_FragColor.rgba = vec4( texture2D( m_samp0, m_cord0.xy ).rgba * m_unicol );\n"
"#if defined(KODI_LIMITED_RANGE)\n"
"   gl_FragColor.rgb *= ( 235.0 - 16.0 ) / 255.0;\n"
"   gl_FragColor.rgb += 16.0 / 255.0;\n"
"#endif\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_multi_frag =
"precision mediump   float;\n"
#else
static const char * gles_shader_multi_frag =
#endif
"uniform   sampler2D m_samp0;\n"
"uniform   sampler2D m_samp1;\n"
"varying   vec4      m_cord0;\n"
"varying   vec4      m_cord1;\n"
"// SM_MULTI shader;\n"
"void main()\n"
"{\n"
"    gl_FragColor.rgba = ( texture2D( m_samp0, m_cord0.xy ) * texture2D( m_samp1, m_cord1.xy ) ).rgba;\n"
"#if defined(KODI_LIMITED_RANGE)\n"
"   gl_FragColor.rgb *= ( 235.0 - 16.0 ) / 255.0;\n"
"   gl_FragColor.rgb += 16.0 / 255.0;\n"
"#endif\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_fonts_frag =
"precision mediump   float;\n"
#else
static const char * gles_shader_fonts_frag =
#endif
"uniform   sampler2D m_samp0;\n"
"varying   vec4      m_cord0;\n"
"varying   lowp vec4 m_colour;\n"
"// SM_FONTS shader\n"
"void main()\n"
"{\n"
"    gl_FragColor.r = m_colour.r;\n"
"    gl_FragColor.g = m_colour.g;\n"
"    gl_FragColor.b = m_colour.b;\n"
"    gl_FragColor.a = m_colour.a * texture2D( m_samp0, m_cord0.xy ).a;\n"
"#if defined(KODI_LIMITED_RANGE)\n"
"   gl_FragColor.rgb *= ( 235.0 - 16.0 ) / 255.0;\n"
"   gl_FragColor.rgb += 16.0 / 255.0;\n"
"#endif\n"
"}\n";


#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_texture_noblend_frag =
"precision mediump   float;\n"
#else
static const char * gles_shader_texture_noblend_frag =
#endif
"uniform   sampler2D m_samp0;\n"
"varying   vec4      m_cord0;\n"
"// SM_TEXTURE_NOBLEND shader\n"
"void main()\n"
"{\n"
"    gl_FragColor.rgba = vec4( texture2D( m_samp0, m_cord0.xy ).rgba );\n"
"#if defined(KODI_LIMITED_RANGE)\n"
"   gl_FragColor.rgb *= ( 235.0 - 16.0 ) / 255.0;\n"
"   gl_FragColor.rgb += 16.0 / 255.0;\n"
"#endif\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_multi_blendcolor_frag =
"precision mediump   float;\n"
#else
static const char * gles_shader_multi_blendcolor_frag =
#endif
"uniform   sampler2D m_samp0;\n"
"uniform   sampler2D m_samp1;\n"
"varying   vec4      m_cord0;\n"
"varying   vec4      m_cord1;\n"
"uniform   lowp vec4 m_unicol;\n"
"// SM_MULTI BLEND shader\n"
"void main()\n"
"{\n"
"    gl_FragColor.rgba = m_unicol * texture2D( m_samp0, m_cord0.xy ) * texture2D( m_samp1, m_cord1.xy );\n"
"#if defined(KODI_LIMITED_RANGE)\n"
"   gl_FragColor.rgb *= ( 235.0 - 16.0 ) / 255.0;\n"
"   gl_FragColor.rgb += 16.0 / 255.0;\n"
"#endif\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_rgba_frag =
"precision mediump   float;\n"
#else
static const char * gles_shader_rgba_frag =
#endif
"uniform sampler2D m_samp0;\n"
"uniform sampler2D m_samp1;\n"
"varying vec4      m_cord0;\n"
"varying vec4      m_cord1;\n"
"varying lowp vec4 m_colour;\n"
"uniform int       m_method;\n"
"uniform float     m_brightness;\n"
"uniform float     m_contrast;\n"
"void main()\n"
"{\n"
"    vec4 color = texture2D( m_samp0, m_cord0.xy ).rgba;\n"
"#if defined(KODI_LIMITED_RANGE)\n"
"   gl_FragColor.rgb *= ( 235.0 - 16.0 ) / 255.0;\n"
"   gl_FragColor.rgb += 16.0 / 255.0;\n"
"#endif\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_rgba_oes_frag =
"precision mediump   float;\n"
#else
static const char * gles_shader_rgba_oes_frag =
#endif
"#extension GL_OES_EGL_image_external : require\n"
"uniform samplerExternalOES m_samp0;\n"
"varying vec4      m_cord0;\n"
"uniform float     m_brightness;\n"
"uniform float     m_contrast;\n"
"void main()\n"
"{\n"
"    vec4 color = texture2D( m_samp0, m_cord0.xy ).rgba;\n"
"    color = color * m_contrast;\n"
"    color = color + m_brightness;\n"
"    gl_FragColor.rgba = color;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_rgba_blendcolor_frag =
"precision mediump   float;\n"
#else
static const char * gles_shader_rgba_blendcolor_frag =
#endif
"uniform sampler2D m_samp0;\n"
"uniform sampler2D m_samp1;\n"
"varying vec4      m_cord0;\n"
"varying vec4      m_cord1;\n"
"varying lowp vec4 m_colour;\n"
"uniform int       m_method;\n"
"// SM_TEXTURE_RGBA_BLENDCOLOR\n"
"void main()\n"
"{\n"
"    gl_FragColor.rgba = vec4( texture2D( m_samp0, m_cord0.xy ).rgba * m_colour );\n"
"#if defined(KODI_LIMITED_RANGE)\n"
"   gl_FragColor.rgb *= ( 235.0 - 16.0 ) / 255.0;\n"
"   gl_FragColor.rgb += 16.0 / 255.0;\n"
"#endif\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_rgba_bob_frag =
"precision highp   float;\n"
#else
static const char * gles_shader_rgba_bob_frag =
#endif
"uniform sampler2D m_samp0;\n"
"uniform sampler2D m_samp1;\n"
"varying vec4      m_cord0;\n"
"varying vec4      m_cord1;\n"
"varying lowp vec4 m_colour;\n"
"uniform int       m_method;\n"
"uniform int       m_field;\n"
"uniform float     m_step;\n"
"uniform float     m_brightness;\n"
"uniform float     m_contrast;\n"
"void main()\n"
"{\n"
"    vec2 source;\n"
"    source = m_cord0.xy;\n"
"    float temp1 = mod( source.y, 2.0*m_step );\n"
"    float temp2 = source.y - temp1;\n"
"    source.y = temp2 + m_step / 2.0 - float( m_field )*m_step;\n"
"    // Blend missing line\n"
"    vec2 below;\n"
"    float bstep = step( m_step, temp1 );\n"
"    below.x = source.x;\n"
"    below.y = source.y + ( 2.0*m_step*bstep );\n"
"    vec4 color = mix( texture2D( m_samp0, source ), texture2D( m_samp0, below ), 0.5 );\n"
"    color = color * m_contrast;\n"
"    color = color + m_brightness;\n"
"    gl_FragColor.rgba = color;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_shader_rgba_bob_oes_frag =
"precision highp   float;\n"
#else
static const char * gles_shader_rgba_bob_oes_frag =
#endif
"#extension GL_OES_EGL_image_external : require\n"
"uniform samplerExternalOES m_samp0;\n"
"uniform samplerExternalOES m_samp1;\n"
"varying vec4      m_cord0;\n"
"varying vec4      m_cord1;\n"
"varying lowp vec4 m_colour;\n"
"uniform int       m_method;\n"
"uniform int       m_field;\n"
"uniform float     m_step;\n"
"uniform float     m_brightness;\n"
"uniform float     m_contrast;\n"
"void main()\n"
"{\n"
"    vec2 source;\n"
"    source = m_cord0.xy;\n"
"    float temp1 = mod( source.y, 2.0*m_step );\n"
"    float temp2 = source.y - temp1;\n"
"    source.y = temp2 + m_step / 2.0 - float( m_field )*m_step;\n"
"    // Blend missing line\n"
"    vec2 below;\n"
"    float bstep = step( m_step, temp1 );\n"
"    below.x = source.x;\n"
"    below.y = source.y + ( 2.0*m_step*bstep );\n"
"    vec4 color = mix( texture2D( m_samp0, source ), texture2D( m_samp0, below ), 0.5 );\n"
"    color = color * m_contrast;\n"
"    color = color + m_brightness;\n"
"    gl_FragColor.rgba = color;\n"
"}\n";
//============================================================================
// video format
//============================================================================
#if defined(TARGET_OS_WINDOWS)
static const char * gles_yuv2rgb_yv12_vert =
#else
static const char * gles_yuv2rgb_yv12_vert =
"#version 120\n"
#endif
"attribute vec4 m_attrpos;\n"
"attribute vec2 m_attrcordY;\n"
"attribute vec2 m_attrcordU;\n"
"attribute vec2 m_attrcordV;\n"
"varying vec2 m_cordY;\n"
"varying vec2 m_cordU;\n"
"varying vec2 m_cordV;\n"
"uniform mat4 m_proj;\n"
"uniform mat4 m_model;\n"
"void main()\n"
"{\n"
"    mat4 mvp = m_proj * m_model;\n"
"    gl_Position = mvp * m_attrpos;\n"
"    m_cordY = m_attrcordY;\n"
"    m_cordU = m_attrcordU;\n"
"    m_cordV = m_attrcordV;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_yuv2rgb_basic_frag =
"precision mediump float;\n"
#else
static const char * gles_yuv2rgb_basic_frag =
#endif
"uniform sampler2D m_sampY;\n"
"uniform sampler2D m_sampU;\n"
"uniform sampler2D m_sampV;\n"
"varying vec2      m_cordY;\n"
"varying vec2      m_cordU;\n"
"varying vec2      m_cordV;\n"
"uniform vec2      m_step;\n"
"uniform mat4      m_yuvmat;\n"
"uniform float     m_alpha;\n"
"void main()\n"
"{\n"
"  vec4 rgb;\n"
"#if defined(XBMC_YV12) || defined(XBMC_NV12)\n"
"  vec4 yuv;\n"
"  yuv.rgba = vec4( texture2D(m_sampY, m_cordY).r\n"
"                 , texture2D(m_sampU, m_cordU).g\n"
"                 , texture2D(m_sampV, m_cordV).a\n"
"                 , 1.0 );\n"
"  rgb   = m_yuvmat * yuv;\n"
"  rgb.a = m_alpha;\n"
"#elif defined(XBMC_NV12_RRG)\n"
"  vec4 yuv;\n"
"  yuv.rgba = vec4( texture2D(m_sampY, m_cordY).r\n"
"                 , texture2D(m_sampU, m_cordU).r\n"
"                 , texture2D(m_sampV, m_cordV).g\n"
"                 , 1.0 );\n"
"  rgb   = m_yuvmat * yuv;\n"
"  rgb.a = m_alpha;\n"
"#elif defined(XBMC_YUY2) || defined(XBMC_UYVY)\n"
"  vec2 stepxy = m_step;\n"
"  vec2 pos    = m_cordY;\n"
"  pos         = vec2(pos.x - stepxy.x * 0.25, pos.y);\n"
"  vec2 f      = fract(pos / stepxy);\n"
"  //y axis will be correctly interpolated by opengl\n"
"  //x axis will not, so we grab two pixels at the center of two columns and interpolate ourselves\n"
"  vec4 c1 = texture2D(m_sampY, vec2(pos.x + (0.5 - f.x) * stepxy.x, pos.y));\n"
"  vec4 c2 = texture2D(m_sampY, vec2(pos.x + (1.5 - f.x) * stepxy.x, pos.y));\n"
"  /* each pixel has two Y subpixels and one UV subpixel\n"
"     YUV  Y  YUV\n"
"     check if we're left or right of the middle Y subpixel and interpolate accordingly*/\n"
"#ifdef XBMC_YUY2 //BGRA = YUYV\n"
"  float leftY   = mix(c1.b, c1.r, f.x * 2.0);\n"
"  float rightY  = mix(c1.r, c2.b, f.x * 2.0 - 1.0);\n"
"  vec2  outUV   = mix(c1.ga, c2.ga, f.x);\n"
"#else //BGRA = UYVY\n"
"  float leftY   = mix(c1.g, c1.a, f.x * 2.0);\n"
"  float rightY  = mix(c1.a, c2.g, f.x * 2.0 - 1.0);\n"
"  vec2  outUV   = mix(c1.br, c2.br, f.x);\n"
"#endif //XBMC_YUY2\n"
"  float outY    = mix(leftY, rightY, step(0.5, f.x));\n"
"  vec4  yuv     = vec4(outY, outUV, 1.0);\n"
"  rgb           = m_yuvmat * yuv;\n"
"  rgb.a = m_alpha;\n"
"#endif\n"
"  gl_FragColor = rgb;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_yuv2rgb_nv12_vert =
"#version 100\n"
#else
static const char * gles_yuv2rgb_nv12_vert =
"#version 120\n"
#endif
"#define XBMC_NV12\n"
"attribute vec4 m_attrpos;\n"
"attribute vec2 m_attrcordY;\n"
"attribute vec2 m_attrcordU;\n"
"attribute vec2 m_attrcordV;\n"
"varying vec2 m_cordY;\n"
"varying vec2 m_cordU;\n"
"varying vec2 m_cordV;\n"
"uniform mat4 m_proj;\n"
"uniform mat4 m_model;\n"
"void main()\n"
"{\n"
"    mat4 mvp = m_proj * m_model;\n"
"    gl_Position = mvp * m_attrpos;\n"
"    m_cordY = m_attrcordY;\n"
"    m_cordU = m_attrcordU;\n"
"    m_cordV = m_attrcordV;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_yuv2rgb_yuy2_vert =
"#version 100\n"
#else
static const char * gles_yuv2rgb_yuy2_vert =
"#version 120\n"
#endif
"#define XBMC_YUY2\n"
"attribute vec4 m_attrpos;\n"
"attribute vec2 m_attrcordY;\n"
"attribute vec2 m_attrcordU;\n"
"attribute vec2 m_attrcordV;\n"
"varying vec2 m_cordY;\n"
"varying vec2 m_cordU;\n"
"varying vec2 m_cordV;\n"
"uniform mat4 m_proj;\n"
"uniform mat4 m_model;\n"
"void main()\n"
"{\n"
"    mat4 mvp = m_proj * m_model;\n"
"    gl_Position = mvp * m_attrpos;\n"
"    m_cordY = m_attrcordY;\n"
"    m_cordU = m_attrcordU;\n"
"    m_cordV = m_attrcordV;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_yuv2rgb_uyvy_vert =
"#version 100\n"
#else
static const char * gles_yuv2rgb_uyvy_vert =
"#version 120\n"
#endif
"#define XBMC_UYVY\n"
"attribute vec4 m_attrpos;\n"
"attribute vec2 m_attrcordY;\n"
"attribute vec2 m_attrcordU;\n"
"attribute vec2 m_attrcordV;\n"
"varying vec2 m_cordY;\n"
"varying vec2 m_cordU;\n"
"varying vec2 m_cordV;\n"
"uniform mat4 m_proj;\n"
"uniform mat4 m_model;\n"
"void main()\n"
"{\n"
"    mat4 mvp = m_proj * m_model;\n"
"    gl_Position = mvp * m_attrpos;\n"
"    m_cordY = m_attrcordY;\n"
"    m_cordU = m_attrcordU;\n"
"    m_cordV = m_attrcordV;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_yuv2rgb_nv12_rgb_vert =
"#version 100\n"
#else
static const char * gles_yuv2rgb_nv12_rgb_vert =
"#version 120\n"
#endif
"#define XBMC_NV12_RRG\n"
"attribute vec4 m_attrpos;\n"
"attribute vec2 m_attrcordY;\n"
"attribute vec2 m_attrcordU;\n"
"attribute vec2 m_attrcordV;\n"
"varying vec2 m_cordY;\n"
"varying vec2 m_cordU;\n"
"varying vec2 m_cordV;\n"
"uniform mat4 m_proj;\n"
"uniform mat4 m_model;\n"
"void main()\n"
"{\n"
"    mat4 mvp = m_proj * m_model;\n"
"    gl_Position = mvp * m_attrpos;\n"
"    m_cordY = m_attrcordY;\n"
"    m_cordU = m_attrcordU;\n"
"    m_cordV = m_attrcordV;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_yuv2rgb_bob_frag =
"precision highp float;\n"
#else
static const char * gles_yuv2rgb_bob_frag =
#endif
"uniform sampler2D m_sampY;\n"
"uniform sampler2D m_sampU;\n"
"uniform sampler2D m_sampV;\n"
"varying vec2      m_cordY;\n"
"varying vec2      m_cordU;\n"
"varying vec2      m_cordV;\n"
"uniform float     m_alpha;\n"
"uniform mat4      m_yuvmat;\n"
"uniform float     m_stepX;\n"
"uniform float     m_stepY;\n"
"uniform int       m_field;\n"
"void main()\n"
"{\n"
"    vec4 yuv, rgb;\n"
"    vec2 offsetY;\n"
"    vec2 offsetU;\n"
"    vec2 offsetV;\n"
"    float temp1 = mod( m_cordY.y, 2.0*m_stepY );\n"
"    offsetY = m_cordY;\n"
"    offsetU = m_cordU;\n"
"    offsetV = m_cordV;\n"
"    offsetY.y -= ( temp1 - m_stepY / 2.0 + float( m_field )*m_stepY );\n"
"    offsetU.y -= ( temp1 - m_stepY / 2.0 + float( m_field )*m_stepY ) / 2.0;\n"
"    offsetV.y -= ( temp1 - m_stepY / 2.0 + float( m_field )*m_stepY ) / 2.0;\n"
"    float bstep = step( m_stepY, temp1 );\n"
"    // Blend missing line\n"
"    vec2 belowY, belowU, belowV;\n"
"    belowY.x = offsetY.x;\n"
"    belowY.y = offsetY.y + ( 2.0*m_stepY*bstep );\n"
"    belowU.x = offsetU.x;\n"
"    belowU.y = offsetU.y + ( m_stepY*bstep );\n"
"    belowV.x = offsetV.x;\n"
"    belowV.y = offsetV.y + ( m_stepY*bstep );\n"
"    vec4 yuvBelow, rgbBelow;\n"
"    yuv.rgba = vec4( texture2D( m_sampY, offsetY ).r, texture2D( m_sampU, offsetU ).g, texture2D( m_sampV, offsetV ).a, 1.0 );\n"
"    rgb = m_yuvmat * yuv;\n"
"    rgb.a = m_alpha;\n"
"    yuvBelow.rgba = vec4( texture2D( m_sampY, belowY ).r, texture2D( m_sampU, belowU ).g, texture2D( m_sampV, belowV ).a, 1.0 );\n"
"    rgbBelow = m_yuvmat * yuvBelow;\n"
"    rgbBelow.a = m_alpha;\n"
"    gl_FragColor.rgba = mix( rgb, rgbBelow, 0.5 );\n"
"}\n";
//============================================================================
// video filter
//============================================================================
#if defined(TARGET_OS_WINDOWS)
static const char * gles_videofilter_vert =
"#version 100\n"
#else
static const char * gles_videofilter_vert =
#endif
"attribute vec4 m_attrpos;\n"
"attribute vec2 m_attrcord;\n"
"varying vec2 cord;\n"
"uniform mat4 m_proj;\n"
"uniform mat4 m_model;\n"
"void main()\n"
"{\n"
"    mat4 mvp = m_proj * m_model;\n"
"    gl_Position = mvp * m_attrpos;\n"
"    cord = m_attrcord.xy;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_videofilter_frag =
"precision mediump float;\n"
#else
static const char * gles_videofilter_frag =
#endif
"uniform sampler2D img;\n"
"varying vec2 cord;\n"
"void main()\n"
"{\n"
"    gl_FragColor = texture2D( img, cord );\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_convolution_4x4_rgba_frag =
"precision highp float;\n"
#else
static const char * gles_convolution_4x4_rgba_frag =
#endif
"#define HAS_FLOAT_TEXTURE 0\n"
"uniform sampler2D img;\n"
"uniform vec2      stepxy;\n"
"varying vec2      cord;\n"
"uniform float     m_alpha;\n"
"uniform sampler2D kernelTex;\n"
"vec4 weight( float pos )\n"
"{\n"
"#if (HAS_FLOAT_TEXTURE)\n"
"    return texture2D( kernelTex, vec2( pos - 0.5 ) );\n"
"#else\n"
"    return texture2D( kernelTex, vec2( pos - 0.5 ) ) * 2.0 - 1.0;\n"
"#endif\n"
"}\n"
"vec3 pixel( float xpos, float ypos )\n"
"{\n"
"    return texture2D( img, vec2( xpos, ypos ) ).rgb;\n"
"}\n"
"vec3 line( float ypos, vec4 xpos, vec4 linetaps )\n"
"{\n"
"    return\n"
"        pixel( xpos.r, ypos ) * linetaps.r +\n"
"        pixel( xpos.g, ypos ) * linetaps.g +\n"
"        pixel( xpos.b, ypos ) * linetaps.b +\n"
"        pixel( xpos.a, ypos ) * linetaps.a;\n"
"}\n"
"void main()\n"
"{\n"
"    vec4 rgb;\n"
"    vec2 pos = cord + stepxy * 0.5;\n"
"    vec2 f = fract( pos / stepxy );\n"
"    vec4 linetaps = weight( 1.0 - f.x );\n"
"    vec4 columntaps = weight( 1.0 - f.y );\n"
"    //make sure all taps added together is exactly 1.0, otherwise some (very small) distortion can occur\n"
"    linetaps /= linetaps.r + linetaps.g + linetaps.b + linetaps.a;\n"
"    columntaps /= columntaps.r + columntaps.g + columntaps.b + columntaps.a;\n"
"    vec2 xystart = ( -1.5 - f ) * stepxy + pos;\n"
"    vec4 xpos = vec4( xystart.x, xystart.x + stepxy.x, xystart.x + stepxy.x * 2.0, xystart.x + stepxy.x * 3.0 );\n"
"    rgb.rgb =\n"
"        line( xystart.y, xpos, linetaps ) * columntaps.r +\n"
"        line( xystart.y + stepxy.y, xpos, linetaps ) * columntaps.g +\n"
"        line( xystart.y + stepxy.y * 2.0, xpos, linetaps ) * columntaps.b +\n"
"        line( xystart.y + stepxy.y * 3.0, xpos, linetaps ) * columntaps.a;\n"
"    rgb.a = m_alpha;\n"
"    gl_FragColor = rgb;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_convolution_4x4_float_frag =
"precision highp float;\n"
#else
static const char * gles_convolution_4x4_float_frag =
#endif
"#define HAS_FLOAT_TEXTURE 1\n"
"uniform sampler2D img;\n"
"uniform vec2      stepxy;\n"
"varying vec2      cord;\n"
"uniform float     m_alpha;\n"
"uniform sampler2D kernelTex;\n"
"vec4 weight( float pos )\n"
"{\n"
"#if (HAS_FLOAT_TEXTURE)\n"
"    return texture2D( kernelTex, vec2( pos - 0.5 ) );\n"
"#else\n"
"    return texture2D( kernelTex, vec2( pos - 0.5 ) ) * 2.0 - 1.0;\n"
"#endif\n"
"}\n"
"vec3 pixel( float xpos, float ypos )\n"
"{\n"
"    return texture2D( img, vec2( xpos, ypos ) ).rgb;\n"
"}\n"
"vec3 line( float ypos, vec4 xpos, vec4 linetaps )\n"
"{\n"
"    return\n"
"        pixel( xpos.r, ypos ) * linetaps.r +\n"
"        pixel( xpos.g, ypos ) * linetaps.g +\n"
"        pixel( xpos.b, ypos ) * linetaps.b +\n"
"        pixel( xpos.a, ypos ) * linetaps.a;\n"
"}\n"
"void main()\n"
"{\n"
"    vec4 rgb;\n"
"    vec2 pos = cord + stepxy * 0.5;\n"
"    vec2 f = fract( pos / stepxy );\n"
"    vec4 linetaps = weight( 1.0 - f.x );\n"
"    vec4 columntaps = weight( 1.0 - f.y );\n"
"    //make sure all taps added together is exactly 1.0, otherwise some (very small) distortion can occur\n"
"    linetaps /= linetaps.r + linetaps.g + linetaps.b + linetaps.a;\n"
"    columntaps /= columntaps.r + columntaps.g + columntaps.b + columntaps.a;\n"
"    vec2 xystart = ( -1.5 - f ) * stepxy + pos;\n"
"    vec4 xpos = vec4( xystart.x, xystart.x + stepxy.x, xystart.x + stepxy.x * 2.0, xystart.x + stepxy.x * 3.0 );\n"
"    rgb.rgb =\n"
"        line( xystart.y, xpos, linetaps ) * columntaps.r +\n"
"        line( xystart.y + stepxy.y, xpos, linetaps ) * columntaps.g +\n"
"        line( xystart.y + stepxy.y * 2.0, xpos, linetaps ) * columntaps.b +\n"
"        line( xystart.y + stepxy.y * 3.0, xpos, linetaps ) * columntaps.a;\n"
"    rgb.a = m_alpha;\n"
"    gl_FragColor = rgb;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_convolution_6x6_rgba_frag =
"precision highp float;\n"
#else
static const char * gles_convolution_6x6_rgba_frag =
#endif
"#define HAS_FLOAT_TEXTURE 0\n"
"uniform sampler2D img;\n"
"uniform vec2      stepxy;\n"
"varying vec2      cord;\n"
"uniform float     m_alpha;\n"
"uniform sampler2D kernelTex;\n"
"vec3 weight( float pos )\n"
"{\n"
"#if (HAS_FLOAT_TEXTURE)\n"
"    return texture2D( kernelTex, vec2( pos - 0.5 ) ).rgb;\n"
"#else\n"
"    return texture2D( kernelTex, vec2( pos - 0.5 ) ).rgb * 2.0 - 1.0;\n"
"#endif\n"
"}\n"
"vec3 pixel( float xpos, float ypos )\n"
"{\n"
"    return texture2D( img, vec2( xpos, ypos ) ).rgb;\n"
"}\n"
"vec3 line( float ypos, vec3 xpos1, vec3 xpos2, vec3 linetaps1, vec3 linetaps2 )\n"
"{\n"
"    return\n"
"        pixel( xpos1.r, ypos ) * linetaps1.r +\n"
"        pixel( xpos1.g, ypos ) * linetaps2.r +\n"
"        pixel( xpos1.b, ypos ) * linetaps1.g +\n"
"        pixel( xpos2.r, ypos ) * linetaps2.g +\n"
"        pixel( xpos2.g, ypos ) * linetaps1.b +\n"
"        pixel( xpos2.b, ypos ) * linetaps2.b;\n"
"}\n"
"void main()\n"
"{\n"
"    vec4 rgb;\n"
"    vec2 pos = cord + stepxy * 0.5;\n"
"    vec2 f = fract( pos / stepxy );\n"
"    vec3 linetaps1 = weight( ( 1.0 - f.x ) / 2.0 );\n"
"    vec3 linetaps2 = weight( ( 1.0 - f.x ) / 2.0 + 0.5 );\n"
"    vec3 columntaps1 = weight( ( 1.0 - f.y ) / 2.0 );\n"
"    vec3 columntaps2 = weight( ( 1.0 - f.y ) / 2.0 + 0.5 );\n"
"    //make sure all taps added together is exactly 1.0, otherwise some (very small) distortion can occur\n"
"    float sum = linetaps1.r + linetaps1.g + linetaps1.b + linetaps2.r + linetaps2.g + linetaps2.b;\n"
"    linetaps1 /= sum;\n"
"    linetaps2 /= sum;\n"
"    sum = columntaps1.r + columntaps1.g + columntaps1.b + columntaps2.r + columntaps2.g + columntaps2.b;\n"
"    columntaps1 /= sum;\n"
"    columntaps2 /= sum;\n"
"    vec2 xystart = ( -2.5 - f ) * stepxy + pos;\n"
"    vec3 xpos1 = vec3( xystart.x, xystart.x + stepxy.x, xystart.x + stepxy.x * 2.0 );\n"
"    vec3 xpos2 = vec3( xystart.x + stepxy.x * 3.0, xystart.x + stepxy.x * 4.0, xystart.x + stepxy.x * 5.0 );\n"
"    rgb.rgb =\n"
"        line( xystart.y, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps1.r +\n"
"        line( xystart.y + stepxy.y, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps2.r +\n"
"        line( xystart.y + stepxy.y * 2.0, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps1.g +\n"
"        line( xystart.y + stepxy.y * 3.0, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps2.g +\n"
"        line( xystart.y + stepxy.y * 4.0, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps1.b +\n"
"        line( xystart.y + stepxy.y * 5.0, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps2.b;\n"
"    rgb.a = m_alpha;\n"
"    gl_FragColor = rgb;\n"
"}\n";

#if defined(TARGET_OS_WINDOWS)
static const char * gles_convolution_6x6_float_frag =
"precision highp float;\n"
#else
static const char * gles_convolution_6x6_float_frag =
#endif
"#define HAS_FLOAT_TEXTURE 1\n"
"uniform sampler2D img;\n"
"uniform vec2      stepxy;\n"
"varying vec2      cord;\n"
"uniform float     m_alpha;\n"
"uniform sampler2D kernelTex;\n"
"vec3 weight( float pos )\n"
"{\n"
"#if (HAS_FLOAT_TEXTURE)\n"
"    return texture2D( kernelTex, vec2( pos - 0.5 ) ).rgb;\n"
"#else\n"
"    return texture2D( kernelTex, vec2( pos - 0.5 ) ).rgb * 2.0 - 1.0;\n"
"#endif\n"
"}\n"
"vec3 pixel( float xpos, float ypos )\n"
"{\n"
"    return texture2D( img, vec2( xpos, ypos ) ).rgb;\n"
"}\n"
"vec3 line( float ypos, vec3 xpos1, vec3 xpos2, vec3 linetaps1, vec3 linetaps2 )\n"
"{\n"
"    return\n"
"        pixel( xpos1.r, ypos ) * linetaps1.r +\n"
"        pixel( xpos1.g, ypos ) * linetaps2.r +\n"
"        pixel( xpos1.b, ypos ) * linetaps1.g +\n"
"        pixel( xpos2.r, ypos ) * linetaps2.g +\n"
"        pixel( xpos2.g, ypos ) * linetaps1.b +\n"
"        pixel( xpos2.b, ypos ) * linetaps2.b;\n"
"}\n"
"void main()\n"
"{\n"
"    vec4 rgb;\n"
"    vec2 pos = cord + stepxy * 0.5;\n"
"    vec2 f = fract( pos / stepxy );\n"
"    vec3 linetaps1 = weight( ( 1.0 - f.x ) / 2.0 );\n"
"    vec3 linetaps2 = weight( ( 1.0 - f.x ) / 2.0 + 0.5 );\n"
"    vec3 columntaps1 = weight( ( 1.0 - f.y ) / 2.0 );\n"
"    vec3 columntaps2 = weight( ( 1.0 - f.y ) / 2.0 + 0.5 );\n"
"    //make sure all taps added together is exactly 1.0, otherwise some (very small) distortion can occur\n"
"    float sum = linetaps1.r + linetaps1.g + linetaps1.b + linetaps2.r + linetaps2.g + linetaps2.b;\n"
"    linetaps1 /= sum;\n"
"    linetaps2 /= sum;\n"
"    sum = columntaps1.r + columntaps1.g + columntaps1.b + columntaps2.r + columntaps2.g + columntaps2.b;\n"
"    columntaps1 /= sum;\n"
"    columntaps2 /= sum;\n"
"    vec2 xystart = ( -2.5 - f ) * stepxy + pos;\n"
"    vec3 xpos1 = vec3( xystart.x, xystart.x + stepxy.x, xystart.x + stepxy.x * 2.0 );\n"
"    vec3 xpos2 = vec3( xystart.x + stepxy.x * 3.0, xystart.x + stepxy.x * 4.0, xystart.x + stepxy.x * 5.0 );\n"
"    rgb.rgb =\n"
"        line( xystart.y, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps1.r +\n"
"        line( xystart.y + stepxy.y, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps2.r +\n"
"        line( xystart.y + stepxy.y * 2.0, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps1.g +\n"
"        line( xystart.y + stepxy.y * 3.0, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps2.g +\n"
"        line( xystart.y + stepxy.y * 4.0, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps1.b +\n"
"        line( xystart.y + stepxy.y * 5.0, xpos1, xpos2, linetaps1, linetaps2 ) * columntaps2.b;\n"
"    rgb.a = m_alpha;\n"
"    gl_FragColor = rgb;\n"
"}\n";

//============================================================================
void RenderGlShaders::getShaderSourceCode( int shaderIdx, EShaderType& shaderType, std::string& shaderName, std::string& vertexShaderCode, std::string& fragmentShaderCode )
{
    vertexShaderCode.clear();
    fragmentShaderCode.clear();

    shaderName = "SM_UNKNOWN";
    shaderType = eShaderGui;
    std::string defines = "";

    switch( shaderIdx )
    {
    case SM_DEFAULT:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_default_frag;
        shaderName = "SM_DEFAULT";
        break;

    case SM_TEXTURE:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_texture_frag;
        shaderName = "SM_TEXTURE";
        break;

    case SM_MULTI:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_multi_frag;
        shaderName = "SM_MULTI";
        break;

    case SM_FONTS:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_fonts_frag;
        shaderName = "SM_FONTS";
        break;

    case SM_TEXTURE_NOBLEND:
        vertexShaderCode = gles_shader_vert;
       fragmentShaderCode = gles_shader_texture_noblend_frag;
        shaderName = "SM_TEXTURE_NOBLEND";
        break;

    case SM_MULTI_BLENDCOLOR:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_multi_blendcolor_frag;
        shaderName = "SM_MULTI_BLENDCOLOR";
        break;

    case SM_TEXTURE_RGBA:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_rgba_frag;
        shaderName = "SM_TEXTURE_RGBA";
        break;
#ifdef TARGET_OS_WINDOWS
    case SM_TEXTURE_RGBA_OES:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_rgba_oes_frag;
        shaderName = "SM_TEXTURE_RGBA_OES";
        break;
#endif // TARGET_OS_WINDOWS
    case SM_TEXTURE_RGBA_BLENDCOLOR:
        vertexShaderCode = gles_shader_vert;
       fragmentShaderCode = gles_shader_rgba_blendcolor_frag;
        shaderName = "SM_TEXTURE_RGBA_BLENDCOLOR";
        break;

    case SM_TEXTURE_RGBA_BOB:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_rgba_bob_frag;
        shaderName = "SM_TEXTURE_RGBA_BOB";
        break;
#ifdef TARGET_OS_WINDOWS
    case SM_TEXTURE_RGBA_BOB_OES:
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_rgba_bob_oes_frag;
        shaderName = "SM_TEXTURE_RGBA_BOB_OES";
        break;
#endif // TARGET_OS_WINDOWS

    //=== video format ===//
    case SM_VIDEO_YV12_BASIC:
        vertexShaderCode = gles_yuv2rgb_yv12_vert;
        fragmentShaderCode = gles_yuv2rgb_basic_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_YV12_BASIC";
        defines = "#define XBMC_YV12\n";
        break;
    case SM_VIDEO_NV12_BASIC:
        vertexShaderCode = gles_yuv2rgb_nv12_vert;
        fragmentShaderCode = gles_yuv2rgb_basic_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_NV12_BASIC";
        defines = "#define XBMC_NV12\n";
        break;
    case SM_VIDEO_YUY2_BASIC:
        vertexShaderCode = gles_yuv2rgb_yuy2_vert;
        fragmentShaderCode = gles_yuv2rgb_basic_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_YUY2_BASIC";
        defines = "#define XBMC_YUY2\n";
        break;
    case SM_VIDEO_UYVY_BASIC:
        vertexShaderCode = gles_yuv2rgb_uyvy_vert;
        fragmentShaderCode = gles_yuv2rgb_basic_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_UYVY_BASIC";
        defines = "#define XBMC_UYVY\n";
        break;
    case SM_VIDEO_NV12_RGB_BASIC:
        vertexShaderCode = gles_yuv2rgb_nv12_rgb_vert;
        fragmentShaderCode = gles_yuv2rgb_basic_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_NV12_RGB_BASIC";
        defines = "#define XBMC_UYVY\n";
        break;

    case SM_VIDEO_YV12_BOB:
        vertexShaderCode = gles_yuv2rgb_yv12_vert;
        fragmentShaderCode = gles_yuv2rgb_bob_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_YV12_BOB";
        break;
    case SM_VIDEO_NV12_BOB:
        vertexShaderCode = gles_yuv2rgb_nv12_vert;
        fragmentShaderCode = gles_yuv2rgb_bob_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_NV12_BOB";
        break;
    case SM_VIDEO_YUY2_BOB:
        vertexShaderCode = gles_yuv2rgb_yuy2_vert;
        fragmentShaderCode = gles_yuv2rgb_bob_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_YUY2_BOB";
        break;
    case SM_VIDEO_UYVY_BOB:
        vertexShaderCode = gles_yuv2rgb_uyvy_vert;
        fragmentShaderCode = gles_yuv2rgb_bob_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_UYVY_BOB";
        break;
    case SM_VIDEO_NV12_RGB_BOB:
        vertexShaderCode = gles_yuv2rgb_nv12_rgb_vert;
        fragmentShaderCode = gles_yuv2rgb_bob_frag;
        shaderType = eShaderVideoFormat;
        shaderName = "SM_VIDEO_NV12_RGB_BOB";
        break;

    //=== video filter ===//
    case SM_VID_FILTER_DEFAULT:
        vertexShaderCode = gles_videofilter_vert;
        fragmentShaderCode = gles_videofilter_frag;
        shaderType = eShaderVideoFilter;
        shaderName = "SM_VID_FILTER_DEFAULT";
        break;
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
        vertexShaderCode = gles_videofilter_vert;
        fragmentShaderCode = gles_convolution_4x4_rgba_frag;
        shaderType = eShaderVideoFilter;
        shaderName = "SM_VID_FILTER_CONVOLUTION_4X4_RGBA";
        break;
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
        vertexShaderCode = gles_videofilter_vert;
        fragmentShaderCode = gles_convolution_4x4_float_frag;
        shaderType = eShaderVideoFilter;
        shaderName = "SM_VID_FILTER_CONVOLUTION_4X4_FLOAT";
        break;
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
        vertexShaderCode = gles_videofilter_vert;
        fragmentShaderCode = gles_convolution_6x6_rgba_frag;
        shaderType = eShaderVideoFilter;
        shaderName = "SM_VID_FILTER_CONVOLUTION_6X6_RGBA";
        break;
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
        vertexShaderCode = gles_videofilter_vert;
        fragmentShaderCode = gles_convolution_6x6_float_frag;
        shaderType = eShaderVideoFilter;
        shaderName = "SM_VID_FILTER_CONVOLUTION_6X6_FLOAT";
        break;

    case SM_SHADER_NONE:
        m_Shaders[ shaderIdx ] = nullptr;
        return;

    default:
        LogMsg( LOG_ERROR, "Unknown shader type %d",  shaderIdx );
    }

    if( vertexShaderCode.empty() || fragmentShaderCode.empty() )
    {
        //LogMsg( LOG_INFO, "Compiling shader %s", shaderName.toUtf8().constData() );
        //VerifyGLStateQt();
        vertexShaderCode = gles_shader_vert;
        fragmentShaderCode = gles_shader_default_frag;
    }
    else
    {
#ifndef TARGET_OS_WINDOWS
        // version must be first line of code on linux
        fragmentShaderCode = "#version 120\n" + defines + fragmentShaderCode;
#else
        fragmentShaderCode = defines + fragmentShaderCode;
#endif // TARGET_OS_WINDOWS
    }
}



#endif // TARGET_OS_WINDOWS
