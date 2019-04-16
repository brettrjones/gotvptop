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

#include "RenderShaderQt.h"
#include "RenderGlWidget.h"

//#include "ServiceBroker.h"
//#include "utils/log.h"
//#include "rendering/RenderSystem.h"
//#include "rendering/MatrixGL.h"
//#include "windowing/GraphicContext.h"
//#include "cores/VideoPlayer/VideoRenderers/VideoShaders/YUVMatrix.h"
//#include "cores/VideoPlayer/VideoRenderers/VideoShaders/ConvolutionKernels.h"

#include <VxDebug.h>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#define SINC(x) (sin(M_PI * (x)) / (M_PI * (x)))
namespace MathUtils
{
  // GCC does something stupid with optimization on release builds if we try
  // to assert in these functions

  /*! \brief Round to nearest integer.
   This routine does fast rounding to the nearest integer.
   In the case (k + 0.5 for any integer k) we round up to k+1, and in all other
   instances we should return the nearest integer.
   Thus, { -1.5, -0.5, 0.5, 1.5 } is rounded to { -1, 0, 1, 2 }.
   It preserves the property that round(k) - round(k-1) = 1 for all doubles k.

   Make sure MathUtils::test() returns true for each implementation.
   \sa truncate_int, test
  */
  inline int round_int(double x)
  {
    assert(x > static_cast<double>((int) (INT_MIN / 2)) - 1.0);
    assert(x < static_cast<double>((int) (INT_MAX / 2)) + 1.0);

#if defined(DISABLE_MATHUTILS_ASM_ROUND_INT)
    /* This implementation warrants some further explanation.
     *
     * First, a couple of notes on rounding:
     * 1) C casts from float/double to integer round towards zero.
     * 2) Float/double additions are rounded according to the normal rules,
     *    in other words: on some architectures, it's fixed at compile-time,
     *    and on others it can be set using fesetround()). The following
     *    analysis assumes round-to-nearest with ties rounding to even. This
     *    is a fairly sensible choice, and is the default with ARM VFP.
     *
     * What this function wants is round-to-nearest with ties rounding to
     * +infinity. This isn't an IEEE rounding mode, even if we could guarantee
     * that all architectures supported fesetround(), which they don't. Instead,
     * this adds an offset of 2147483648.5 (= 0x80000000.8p0), then casts to
     * an unsigned int (crucially, all possible inputs are now in a range where
     * round to zero acts the same as round to -infinity) and then subtracts
     * 0x80000000 in the integer domain. The 0.5 component of the offset
     * converts what is effectively a round down into a round to nearest, with
     * ties rounding up, as desired.
     *
     * There is a catch, that because there is a double rounding, there is a
     * small region where the input falls just *below* a tie, where the addition
     * of the offset causes a round *up* to an exact integer, due to the finite
     * level of precision available in floating point. You need to be aware of
     * this when calling this function, although at present it is not believed
     * that XBMC ever attempts to round numbers in this window.
     *
     * It is worth proving the size of the affected window. Recall that double
     * precision employs a mantissa of 52 bits.
     * 1) For all inputs -0.5 <= x <= INT_MAX
     *    Once the offset is applied, the most significant binary digit in the
     *    floating-point representation is +2^31.
     *    At this magnitude, the smallest step representable in double precision
     *    is 2^31 / 2^52 = 0.000000476837158203125
     *    So the size of the range which is rounded up due to the addition is
     *    half the size of this step, or 0.0000002384185791015625
     *
     * 2) For all inputs INT_MIN/2 < x < -0.5
     *    Once the offset is applied, the most significant binary digit in the
     *    floating-point representation is +2^30.
     *    At this magnitude, the smallest step representable in double precision
     *    is 2^30 / 2^52 = 0.0000002384185791015625
     *    So the size of the range which is rounded up due to the addition is
     *    half the size of this step, or 0.00000011920928955078125
     *
     * 3) For all inputs INT_MIN <= x <= INT_MIN/2
     *    The representation once the offset is applied has equal or greater
     *    precision than the input, so the addition does not cause rounding.
     */
    return ((unsigned int) (x + 2147483648.5)) - 0x80000000;

#else
    const float round_to_nearest = 0.5f;
    int i;
#if defined(HAVE_SSE2) && defined(__SSE2__)
    const float round_dn_to_nearest = 0.4999999f;
    i = (x > 0) ? _mm_cvttsd_si32(_mm_set_sd(x + round_to_nearest)) : _mm_cvttsd_si32(_mm_set_sd(x - round_dn_to_nearest));

#elif defined(TARGET_WINDOWS)
    __asm
    {
      fld x
      fadd st, st (0)
      fadd round_to_nearest
      fistp i
      sar i, 1
    }

#else
    __asm__ __volatile__ (
      "fadd %%st\n\t"
      "fadd %%st(1)\n\t"
      "fistpl %0\n\t"
      "sarl $1, %0\n"
      : "=m"(i) : "u"(round_to_nearest), "t"(x) : "st"
    );

#endif
    return i;
#endif
  }

  /*! \brief Truncate to nearest integer.
   This routine does fast truncation to an integer.
   It should simply drop the fractional portion of the floating point number.

   Make sure MathUtils::test() returns true for each implementation.
   \sa round_int, test
  */
  inline int truncate_int(double x)
  {
    assert(x > static_cast<double>(INT_MIN / 2) - 1.0);
    assert(x < static_cast<double>(INT_MAX / 2) + 1.0);
    return static_cast<int>(x);
  }

  inline int64_t abs(int64_t a)
  {
    return (a < 0) ? -a : a;
  }

  inline unsigned bitcount(unsigned v)
  {
    unsigned c = 0;
    for (c = 0; v; c++)
      v &= v - 1; // clear the least significant bit set
    return c;
  }

  inline void hack()
  {
    // stupid hack to keep compiler from dropping these
    // functions as unused
    MathUtils::round_int(0.0);
    MathUtils::truncate_int(0.0);
    MathUtils::abs(0);
  }

  /**
   * Compare two floating-point numbers for equality and regard them
   * as equal if their difference is below a given threshold.
   *
   * It is usually not useful to compare float numbers for equality with
   * the standard operator== since very close numbers might have different
   * representations.
   */
  template<typename FloatT>
  inline bool FloatEquals(FloatT f1, FloatT f2, FloatT maxDelta)
  {
    return (std::abs(f2 - f1) < maxDelta);
  }

#if 0
  /*! \brief test routine for round_int and truncate_int
   Must return true on all platforms.
   */
  inline bool test()
  {
    for (int i = -8; i < 8; ++i)
    {
      double d = 0.25*i;
      int r = (i < 0) ? (i - 1) / 4 : (i + 2) / 4;
      int t = i / 4;
      if (round_int(d) != r || truncate_int(d) != t)
        return false;
    }
    return true;
  }
#endif
} // namespace MathUtils



class CConvolutionKernel
{
  public:
    CConvolutionKernel( ESCALINGMETHOD method, int size );
    ~CConvolutionKernel();

    int      GetSize()           { return m_size; }
    float*   GetFloatPixels()    { return m_floatpixels; }
    uint8_t* GetIntFractPixels() { return m_intfractpixels; }
    uint8_t* GetUint8Pixels()    { return m_uint8pixels; }

  private:
    CConvolutionKernel(const CConvolutionKernel&) = delete;
    CConvolutionKernel& operator=(const CConvolutionKernel&) = delete;
    void Lanczos2();
    void Lanczos3Fast();
    void Lanczos3();
    void Spline36Fast();
    void Spline36();
    void Bicubic(double B, double C);

    static double LanczosWeight(double x, double radius);
    static double Spline36Weight(double x);
    static double BicubicWeight(double x, double B, double C);

    void ToIntFract();
    void ToUint8();

    int      m_size;
    float*   m_floatpixels;
    uint8_t* m_intfractpixels;
    uint8_t* m_uint8pixels;
};

CConvolutionKernel::CConvolutionKernel( ESCALINGMETHOD method, int size )
{
    m_size = size;
    m_floatpixels = new float[ m_size * 4 ];
    memset( m_floatpixels, 0, m_size * 4 * sizeof(float) );

    if( method == VS_SCALINGMETHOD_LANCZOS2 )
        Lanczos2();
    else if( method == VS_SCALINGMETHOD_SPLINE36_FAST )
        Spline36Fast();
    else if( method == VS_SCALINGMETHOD_LANCZOS3_FAST )
        Lanczos3Fast();
    else if( method == VS_SCALINGMETHOD_SPLINE36 )
        Spline36();
    else if( method == VS_SCALINGMETHOD_LANCZOS3 )
        Lanczos3();
    else if( method == VS_SCALINGMETHOD_CUBIC )
        Bicubic( 1.0 / 3.0, 1.0 / 3.0 );

    ToIntFract();
    ToUint8();
}

CConvolutionKernel::~CConvolutionKernel()
{
    delete[] m_floatpixels;
    delete[] m_intfractpixels;
    delete[] m_uint8pixels;
}

//generate a lanczos2 kernel which can be loaded with RGBA format
//each value of RGBA has one tap, so a shader can load 4 taps with a single pixel lookup
void CConvolutionKernel::Lanczos2()
{
    for( int i = 0; i < m_size; i++ )
    {
        double x = ( double )i / ( double )m_size;

        //generate taps
        for( int j = 0; j < 4; j++ )
            m_floatpixels[ i * 4 + j ] = ( float )LanczosWeight( x + ( double )( j - 2 ), 2.0 );

        //any collection of 4 taps added together needs to be exactly 1.0
        //for lanczos this is not always the case, so we take each collection of 4 taps
        //and divide those taps by the sum of the taps
        float weight = 0.0;
        for( int j = 0; j < 4; j++ )
            weight += m_floatpixels[ i * 4 + j ];

        for( int j = 0; j < 4; j++ )
            m_floatpixels[ i * 4 + j ] /= weight;
    }
}

//generate a lanczos3 kernel which can be loaded with RGBA format
//each value of RGBA has one tap, so a shader can load 4 taps with a single pixel lookup
//the two outer lobes of the lanczos3 kernel are added to the two lobes one step to the middle
//this basically looks the same as lanczos3, but the kernel only has 4 taps,
//so it can use the 4x4 convolution shader which is twice as fast as the 6x6 one
void CConvolutionKernel::Lanczos3Fast()
{
    for( int i = 0; i < m_size; i++ )
    {
        double a = 3.0;
        double x = ( double )i / ( double )m_size;

        //generate taps
        m_floatpixels[ i * 4 + 0 ] = ( float )( LanczosWeight( x - 2.0, a ) + LanczosWeight( x - 3.0, a ) );
        m_floatpixels[ i * 4 + 1 ] = ( float )LanczosWeight( x - 1.0, a );
        m_floatpixels[ i * 4 + 2 ] = ( float )LanczosWeight( x, a );
        m_floatpixels[ i * 4 + 3 ] = ( float )( LanczosWeight( x + 1.0, a ) + LanczosWeight( x + 2.0, a ) );

        //any collection of 4 taps added together needs to be exactly 1.0
        //for lanczos this is not always the case, so we take each collection of 4 taps
        //and divide those taps by the sum of the taps
        float weight = 0.0;
        for( int j = 0; j < 4; j++ )
            weight += m_floatpixels[ i * 4 + j ];

        for( int j = 0; j < 4; j++ )
            m_floatpixels[ i * 4 + j ] /= weight;
    }
}

//generate a lanczos3 kernel which can be loaded with RGBA format
//each value of RGB has one tap, so a shader can load 3 taps with a single pixel lookup
void CConvolutionKernel::Lanczos3()
{
    for( int i = 0; i < m_size; i++ )
    {
        double x = ( double )i / ( double )m_size;

        //generate taps
        for( int j = 0; j < 3; j++ )
            m_floatpixels[ i * 4 + j ] = ( float )LanczosWeight( x * 2.0 + ( double )( j * 2 - 3 ), 3.0 );

        m_floatpixels[ i * 4 + 3 ] = 0.0;
    }

    //any collection of 6 taps added together needs to be exactly 1.0
    //for lanczos this is not always the case, so we take each collection of 6 taps
    //and divide those taps by the sum of the taps
    for( int i = 0; i < m_size / 2; i++ )
    {
        float weight = 0.0;
        for( int j = 0; j < 3; j++ )
        {
            weight += m_floatpixels[ i * 4 + j ];
            weight += m_floatpixels[ ( i + m_size / 2 ) * 4 + j ];
        }
        for( int j = 0; j < 3; j++ )
        {
            m_floatpixels[ i * 4 + j ] /= weight;
            m_floatpixels[ ( i + m_size / 2 ) * 4 + j ] /= weight;
        }
    }
}

void CConvolutionKernel::Spline36Fast()
{
    for( int i = 0; i < m_size; i++ )
    {
        double x = ( double )i / ( double )m_size;

        //generate taps
        m_floatpixels[ i * 4 + 0 ] = ( float )( Spline36Weight( x - 2.0 ) + Spline36Weight( x - 3.0 ) );
        m_floatpixels[ i * 4 + 1 ] = ( float )Spline36Weight( x - 1.0 );
        m_floatpixels[ i * 4 + 2 ] = ( float )Spline36Weight( x );
        m_floatpixels[ i * 4 + 3 ] = ( float )( Spline36Weight( x + 1.0 ) + Spline36Weight( x + 2.0 ) );

        float weight = 0.0;
        for( int j = 0; j < 4; j++ )
            weight += m_floatpixels[ i * 4 + j ];

        for( int j = 0; j < 4; j++ )
            m_floatpixels[ i * 4 + j ] /= weight;
    }
}

void CConvolutionKernel::Spline36()
{
    for( int i = 0; i < m_size; i++ )
    {
        double x = ( double )i / ( double )m_size;

        //generate taps
        for( int j = 0; j < 3; j++ )
            m_floatpixels[ i * 4 + j ] = ( float )Spline36Weight( x * 2.0 + ( double )( j * 2 - 3 ) );

        m_floatpixels[ i * 4 + 3 ] = 0.0;
    }

    for( int i = 0; i < m_size / 2; i++ )
    {
        float weight = 0.0;
        for( int j = 0; j < 3; j++ )
        {
            weight += m_floatpixels[ i * 4 + j ];
            weight += m_floatpixels[ ( i + m_size / 2 ) * 4 + j ];
        }
        for( int j = 0; j < 3; j++ )
        {
            m_floatpixels[ i * 4 + j ] /= weight;
            m_floatpixels[ ( i + m_size / 2 ) * 4 + j ] /= weight;
        }
    }
}

//generate a bicubic kernel which can be loaded with RGBA format
//each value of RGBA has one tap, so a shader can load 4 taps with a single pixel lookup
void CConvolutionKernel::Bicubic( double B, double C )
{
    for( int i = 0; i < m_size; i++ )
    {
        double x = ( double )i / ( double )m_size;

        //generate taps
        for( int j = 0; j < 4; j++ )
            m_floatpixels[ i * 4 + j ] = ( float )BicubicWeight( x + ( double )( j - 2 ), B, C );
    }
}

double CConvolutionKernel::LanczosWeight( double x, double radius )
{
    double ax = fabs( x );

    if( ax == 0.0 )
        return 1.0;
    else if( ax < radius )
        return SINC( ax ) * SINC( ax / radius );
    else
        return 0.0;
}

double CConvolutionKernel::BicubicWeight( double x, double B, double C )
{
    double ax = fabs( x );

    if( ax < 1.0 )
    {
        return ( ( 12 - 9 * B - 6 * C ) * ax * ax * ax +
            ( -18 + 12 * B + 6 * C ) * ax * ax +
                 ( 6 - 2 * B ) ) / 6;
    }
    else if( ax < 2.0 )
    {
        return ( ( -B - 6 * C ) * ax * ax * ax +
            ( 6 * B + 30 * C ) * ax * ax + ( -12 * B - 48 * C ) *
                 ax + ( 8 * B + 24 * C ) ) / 6;
    }
    else
    {
        return 0.0;
    }
}

double CConvolutionKernel::Spline36Weight( double x )
{
    double ax = fabs( x );

    if( ax < 1.0 )
        return ( ( 13.0 / 11.0 * ( ax )-453.0 / 209.0 ) * ( ax )-3.0 / 209.0 ) * ( ax )+1.0;
    else if( ax < 2.0 )
        return ( ( -6.0 / 11.0 * ( ax - 1.0 ) + 270.0 / 209.0 ) * ( ax - 1.0 ) - 156.0 / 209.0 ) * ( ax - 1.0 );
    else if( ax < 3.0 )
        return ( ( 1.0 / 11.0 * ( ax - 2.0 ) - 45.0 / 209.0 ) * ( ax - 2.0 ) + 26.0 / 209.0 ) * ( ax - 2.0 );
    return 0.0;
}

//convert float to high byte/low byte, so the kernel can be loaded into an 8 bit texture
//with height 2 and converted back to real float in the shader
//it only works when the kernel texture uses nearest neighbour, but there's almost no difference
//between that and linear interpolation
void CConvolutionKernel::ToIntFract()
{
    m_intfractpixels = new uint8_t[ m_size * 8 ];

    for( int i = 0; i < m_size * 4; i++ )
    {
        int value = MathUtils::round_int( ( m_floatpixels[ i ] + 1.0 ) / 2.0 * 65535.0 );
        if( value < 0 )
            value = 0;
        else if( value > 65535 )
            value = 65535;

        int integer = value / 256;
        int fract = value % 256;

        m_intfractpixels[ i ] = ( uint8_t )integer;
        m_intfractpixels[ i + m_size * 4 ] = ( uint8_t )fract;
    }
}

//convert to 8 bits unsigned
void CConvolutionKernel::ToUint8()
{
    m_uint8pixels = new uint8_t[ m_size * 4 ];

    for( int i = 0; i < m_size * 4; i++ )
    {
        int value = MathUtils::round_int( ( m_floatpixels[ i ] * 0.5 + 0.5 ) * 255.0 );
        if( value < 0 )
            value = 0;
        else if( value > 255 )
            value = 255;

        m_uint8pixels[ i ] = ( uint8_t )value;
    }
}


//
// Transformation matrixes for different colorspaces.
//
static float yuv_coef_bt601[ 4 ][ 4 ] =
{
   { 1.0f,      1.0f,     1.0f,     0.0f },
   { 0.0f,     -0.344f,   1.773f,   0.0f },
   { 1.403f,   -0.714f,   0.0f,     0.0f },
   { 0.0f,      0.0f,     0.0f,     0.0f }
};

static float yuv_coef_bt709[ 4 ][ 4 ] =
{
   { 1.0f,      1.0f,     1.0f,     0.0f },
   { 0.0f,     -0.1870f,  1.8556f,  0.0f },
   { 1.5701f,  -0.4664f,  0.0f,     0.0f },
   { 0.0f,      0.0f,     0.0f,     0.0f }
};

static float yuv_coef_bt2020[ 4 ][ 4 ] =
{
   { 1.0f,     1.0f,     1.0f,    0.0f },
   { 0.0f,    -0.1645f,  1.8814f, 0.0f },
   { 1.4745f, -0.5713f,  0.0f,    0.0f },
   { 0.0f,     0.0f,     0.0f,    0.0f }
};

static float yuv_coef_ebu[ 4 ][ 4 ] =
{
   { 1.0f,      1.0f,     1.0f,     0.0f },
   { 0.0f,     -0.3960f,  2.029f,   0.0f },
   { 1.140f,   -0.581f,   0.0f,     0.0f },
   { 0.0f,      0.0f,     0.0f,     0.0f }
};

static float yuv_coef_smtp240m[ 4 ][ 4 ] =
{
   { 1.0f,      1.0f,     1.0f,     0.0f },
   { 0.0f,     -0.2253f,  1.8270f,  0.0f },
   { 1.5756f,  -0.5000f,  0.0f,     0.0f },
   { 0.0f,      0.0f,     0.0f,     0.0f }
};

static float** PickYUVConversionMatrix( unsigned flags )
{
   // Pick the matrix.

   switch( CONF_FLAGS_YUVCOEF_MASK( flags ) )
   {
   case CONF_FLAGS_YUVCOEF_240M:
       return reinterpret_cast< float** >( yuv_coef_smtp240m );
   case CONF_FLAGS_YUVCOEF_BT2020:
       return reinterpret_cast< float** >( yuv_coef_bt2020 );
   case CONF_FLAGS_YUVCOEF_BT709:
       return reinterpret_cast< float** >( yuv_coef_bt709 );
   case CONF_FLAGS_YUVCOEF_BT601:
       return reinterpret_cast< float** >( yuv_coef_bt601 );
   case CONF_FLAGS_YUVCOEF_EBU:
       return reinterpret_cast< float** >( yuv_coef_ebu );
   }

   return reinterpret_cast< float** >( yuv_coef_bt601 );
}
void CalculateYUVMatrix( TransformMatrix &matrix
                         , unsigned int  flags
                         , EShaderFormat format
                         , float         black
                         , float         contrast
                         , bool          limited )
{
    TransformMatrix coef;

    matrix *= TransformMatrix::CreateScaler( contrast, contrast, contrast );
    matrix *= TransformMatrix::CreateTranslation( black, black, black );

    float( *conv )[ 4 ] = ( float( *)[ 4 ] )PickYUVConversionMatrix( flags );
    for( int row = 0; row < 3; row++ )
        for( int col = 0; col < 4; col++ )
            coef.m[ row ][ col ] = conv[ col ][ row ];
    coef.identity = false;

    if( limited )
    {
        matrix *= TransformMatrix::CreateTranslation( +16.0f / 255
                                                      , +16.0f / 255
                                                      , +16.0f / 255 );
        matrix *= TransformMatrix::CreateScaler( ( 235 - 16 ) / 255.0f
                                                 , ( 235 - 16 ) / 255.0f
                                                 , ( 235 - 16 ) / 255.0f );
    }

    matrix *= coef;
    matrix *= TransformMatrix::CreateTranslation( 0.0, -0.5, -0.5 );

    if( !( flags & CONF_FLAGS_YUV_FULLRANGE ) )
    {
        matrix *= TransformMatrix::CreateScaler( 255.0f / ( 235 - 16 )
                                                 , 255.0f / ( 240 - 16 )
                                                 , 255.0f / ( 240 - 16 ) );
        matrix *= TransformMatrix::CreateTranslation( -16.0f / 255
                                                      , -16.0f / 255
                                                      , -16.0f / 255 );
    }

    int effectiveBpp;
    switch( format )
    {
    case SHADER_YV12_9:
        effectiveBpp = 9;
        break;
    case SHADER_YV12_10:
        effectiveBpp = 10;
        break;
    case SHADER_YV12_12:
        effectiveBpp = 12;
        break;
    case SHADER_YV12_14:
        effectiveBpp = 14;
        break;
    default:
        effectiveBpp = 0;
    }

    if( effectiveBpp > 8 && effectiveBpp < 16 )
    {
        // Convert range to 2 bytes
        float scale = 65535.0f / ( ( 1 << effectiveBpp ) - 1 );
        matrix *= TransformMatrix::CreateScaler( scale, scale, scale );
    }
}


 //============================================================================
static void CalculateYUVMatrixGLES( GLfloat      res[ 4 ][ 4 ]
                                    , unsigned int flags
                                    , EShaderFormat format
                                    , float        black
                                    , float         contrast
                                    , bool          limited )
{
    TransformMatrix matrix;
    CalculateYUVMatrix( matrix, flags, format, black, contrast, limited );

    for( int row = 0; row < 3; row++ )
        for( int col = 0; col < 4; col++ )
            res[ col ][ row ] = matrix.m[ row ][ col ];

    res[ 0 ][ 3 ] = 0.0f;
    res[ 1 ][ 3 ] = 0.0f;
    res[ 2 ][ 3 ] = 0.0f;
    res[ 3 ][ 3 ] = 1.0f;
}

//============================================================================
RenderShaderQt::RenderShaderQt(  ESHADERMETHOD shaderMethod, EShaderType shaderType, QString shaderName, RenderGlWidget * renderWidget )
    : QOpenGLShaderProgram()
    , m_ShaderMethod( shaderMethod )
    , m_ScalingMethod( VS_SCALINGMETHOD_LINEAR )
    , m_ShaderType( shaderType )
    , m_ShaderName( shaderName )
    , m_RenderWidget( renderWidget )
    , m_validated( false )
    , m_proj( nullptr )
    , m_model( nullptr )
    , m_clipPossible( false )
{
 #ifdef GL_RGBA16F_EXT
    if( CServiceBroker::GetRenderSystem()->IsExtSupported( "GL_EXT_color_buffer_float" ) )
    {
        m_floattex = true;
        m_internalformat = GL_RGBA16F_EXT;
    }
    else
    {
        m_floattex = false;
        m_internalformat = GL_RGBA;
    }
#else
    m_floattex = false;
    m_internalformat = GL_RGBA;
#endif // GL_RGBA16F_EXT
}

//============================================================================
bool RenderShaderQt::compileAndLink( const char * vertexShaderCode, const char *fragmentShaderCode )
{
    bool result = true;
    m_proj = nullptr;
    m_model = nullptr;
    m_clipPossible = false;
    m_RenderWidget->VerifyGLStateQt();

    if( vertexShaderCode )
    {
        if( !addShaderFromSourceCode( QOpenGLShader::Vertex, vertexShaderCode ) )
        {
            LogMsg( LOG_ERROR, "could not add vertex shader" );
            result = false;
        }
    }
    
    if( result && !addShaderFromSourceCode( QOpenGLShader::Fragment, fragmentShaderCode ) )
    {
        LogMsg( LOG_ERROR, "could not add fragment shader" );
        result = false;
    }
    
    if( result && !link() )
    {
        LogMsg( LOG_ERROR, "could not link shader" );
    }

    m_RenderWidget->VerifyGLStateQt();
    
    if( result )
    {
        // success
        m_validated = true;
        onCompiledAndLinked();
    }

    m_RenderWidget->VerifyGLStateQt();

    return result;
}

//============================================================================
void RenderShaderQt::onCompiledAndLinked()
{
    // This is called after CompileAndLink()

    if( !m_RenderWidget || !m_RenderWidget->getGlFunctions() )
    {
        LogMsg( LOG_ERROR, "onCompiledAndLinked has no render widget" );
        return;
    }

     QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
     if( !glf )
     {
         LogMsg( LOG_ERROR, "onCompiledAndLinked could not get gl functions" );
         return;
     }

     switch( m_ShaderType )
     {
     case eShaderVideoFilter:
         onCompiledAndLinkedVideoFilter( glf );
         break;

     case eShaderVideoFormat:
         onCompiledAndLinkedVideoFormat( glf );
         break;

     case eShaderGui:
     default:
         onCompiledAndLinkedGui( glf );
         break;
     }
}

//============================================================================
void RenderShaderQt::onCompiledAndLinkedGui( QOpenGLFunctions * glf )
{
    // Variables passed directly to the Fragment shader
    m_hTex0         = glf->glGetUniformLocation( programId(), "m_samp0" );
    m_hTex1         = glf->glGetUniformLocation( programId(), "m_samp1" );
    m_hUniCol       = glf->glGetUniformLocation( programId(), "m_unicol" );
    m_hField        = glf->glGetUniformLocation( programId(), "m_field" );
    m_hStep         = glf->glGetUniformLocation( programId(), "m_step" );
    m_hContrast     = glf->glGetUniformLocation( programId(), "m_contrast" );
    m_hBrightness   = glf->glGetUniformLocation( programId(), "m_brightness" );

    // Variables passed directly to the Vertex shader
    m_hProj         = glf->glGetUniformLocation( programId(), "m_proj" );
    m_hModel        = glf->glGetUniformLocation( programId(), "m_model" );
    m_hCoord0Matrix = glf->glGetUniformLocation( programId(), "m_coord0Matrix" );

    // Vertex attributes
    m_hPos          = glf->glGetAttribLocation( programId(), "m_attrpos" );
    m_hCol          = glf->glGetAttribLocation( programId(), "m_attrcol" );
    m_hCord0        = glf->glGetAttribLocation( programId(), "m_attrcord0" );
    m_hCord1        = glf->glGetAttribLocation( programId(), "m_attrcord1" );

    // It's okay to do this only one time. Textures units never change.
    glf->glUseProgram( programId() );
    glf->glUniform1i( m_hTex0, 0 );
    glf->glUniform1i( m_hTex1, 1 );
    glf->glUniform4f( m_hUniCol, 1.0, 1.0, 1.0, 1.0 );

    static const float identity[ 16 ] = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };

    glf->glUniformMatrix4fv( m_hCoord0Matrix, 1, GL_FALSE, identity );

    glf->glUseProgram( 0 );
}

//============================================================================
void RenderShaderQt::onCompiledAndLinkedVideoFormat( QOpenGLFunctions * glf )
{
    if( SM_VIDEO_YV12_BASIC == m_ShaderMethod )
    {
        LogMsg( LOG_ERROR, "onShaderVideoFormatEnabled %s", describeShader( m_ShaderMethod ) );
    }

    /*
    "#define XBMC_YV12\n"
        "attribute vec4 m_attrpos;\n"
        "attribute vec2 m_attrcordY;\n"
        "attribute vec2 m_attrcordU;\n"
        "attribute vec2 m_attrcordV;\n"
        "varying vec2 m_cordY;\n"
        "varying vec2 m_cordU;\n"
        "varying vec2 m_cordV;\n"
        "uniform mat4 m_proj;\n"
        "uniform mat4 m_model;\n"
        */
    /*
    "precision mediump float;\n"
        "uniform sampler2D m_sampY;\n"
        "uniform sampler2D m_sampU;\n"
        "uniform sampler2D m_sampV;\n"
        "varying vec2      m_cordY;\n"
        "varying vec2      m_cordU;\n"
        "varying vec2      m_cordV;\n"
        "uniform vec2      m_step;\n"
        "uniform mat4      m_yuvmat;\n"
        "uniform float     m_alpha;\n"
        */

     // Variables passed directly to the Vertex shader
    m_hVertex   = glf->glGetAttribLocation( programId(), "m_attrpos" );
    m_hYcoord   = glf->glGetAttribLocation( programId(), "m_attrcordY" );
    m_hUcoord   = glf->glGetAttribLocation( programId(), "m_attrcordU" );
    m_hVcoord   = glf->glGetAttribLocation( programId(), "m_attrcordV" );
    m_hProj     = glf->glGetUniformLocation( programId(), "m_proj" );
    m_hModel    = glf->glGetUniformLocation( programId(), "m_model" );

    // Variables passed directly to the Fragment shader
    m_hAlpha    = glf->glGetUniformLocation( programId(), "m_alpha" );
    m_hYTex     = glf->glGetUniformLocation( programId(), "m_sampY" );
    m_hUTex     = glf->glGetUniformLocation( programId(), "m_sampU" );
    m_hVTex     = glf->glGetUniformLocation( programId(), "m_sampV" );
    m_hMatrix   = glf->glGetUniformLocation( programId(), "m_yuvmat" );
    m_hStep     = glf->glGetUniformLocation( programId(), "m_step" );
    //VerifyGLStateQt();

    switch( m_ShaderMethod )
    {
    case SM_VIDEO_YV12_BOB:
    case SM_VIDEO_NV12_BOB:
    case SM_VIDEO_YUY2_BOB:
    case SM_VIDEO_UYVY_BOB:
    case SM_VIDEO_NV12_RGB_BOB:
        m_hStepX = glf->glGetUniformLocation( programId(), "m_stepX" );
        m_hStepY = glf->glGetUniformLocation( programId(), "m_stepY" );
        m_hField = glf->glGetUniformLocation( programId(), "m_field" );
       // VerifyGLStateQt();
        break;
    default:
        break;
    }

}

//============================================================================
void RenderShaderQt::onCompiledAndLinkedVideoFilter( QOpenGLFunctions * glf )
{
    m_hVertex = glf->glGetAttribLocation( programId(), "m_attrpos" );
    m_hcoord = glf->glGetAttribLocation( programId(), "m_attrcord" );
    m_hAlpha = glf->glGetUniformLocation( programId(), "m_alpha" );
    m_hProj = glf->glGetUniformLocation( programId(), "m_proj" );
    m_hModel = glf->glGetUniformLocation( programId(), "m_model" );

    switch( m_ShaderMethod )
    {
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
    {
        m_RenderWidget->VerifyGLStateQt();

        // obtain shader attribute handles on successful compilation
        m_hSourceTex    = glf->glGetUniformLocation( programId(), "img" );
        m_hStepXY       = glf->glGetUniformLocation( programId(), "stepxy" );
        m_hKernTex      = glf->glGetUniformLocation( programId(), "kernelTex" );

        m_RenderWidget->VerifyGLStateQt();
        CConvolutionKernel kernel( m_ScalingMethod, 256 );
        m_RenderWidget->VerifyGLStateQt();

        if( m_kernelTex1 )
        {
            glf->glDeleteTextures( 1, &m_kernelTex1 );
            m_kernelTex1 = 0;
        }

        m_RenderWidget->VerifyGLStateQt();

        glf->glGenTextures( 1, &m_kernelTex1 );
        m_RenderWidget->VerifyGLStateQt();

        if( ( m_kernelTex1 <= 0 ) )
        {
            LogMsg( LOG_ERROR, "GL: ConvolutionFilterShader: Error creating kernel texture" );
            return;
        }

        m_RenderWidget->VerifyGLStateQt();

        //make a kernel texture on GL_TEXTURE2 and set clamping and interpolation
        glf-> glActiveTexture( GL_TEXTURE2 );
        glf->glBindTexture( GL_TEXTURE_2D, m_kernelTex1 );
        glf->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glf->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glf->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glf->glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

        //if float textures are supported, we can load the kernel as a float texture
        //if not we load it as 8 bit unsigned which gets converted back to float in the shader
        GLenum  format;
        GLvoid* data;
        if( m_floattex )
        {
            format = GL_FLOAT;
            data = ( GLvoid* )kernel.GetFloatPixels();
        }
        else
        {
            format = GL_UNSIGNED_BYTE;
            data = ( GLvoid* )kernel.GetUint8Pixels();
        }
        m_RenderWidget->VerifyGLStateQt();

        //upload as 2D texture with height of 1
        glf->glTexImage2D( GL_TEXTURE_2D, 0, m_internalformat, kernel.GetSize(), 1, 0, GL_RGBA, format, data );

        glf->glActiveTexture( GL_TEXTURE0 );

        m_RenderWidget->VerifyGLStateQt();
        break;
    }

    default:
        break;
    }
}

//============================================================================
bool RenderShaderQt::onEnabled()
{
    // This is called after glUseProgram()

    if( !m_RenderWidget || !m_RenderWidget->getGlFunctions() )
    {
        LogMsg( LOG_ERROR, "onEnabled has no render widget" );
        return false;
    }

    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();

    switch( m_ShaderType )
    {
    case eShaderVideoFilter:
        return onShaderVideoFilterEnabled( glf );
        break;

    case eShaderVideoFormat:
        return onShaderVideoFormatEnabled( glf );
        break;

    case eShaderGui:
    default:
        return onShaderGuiEnabled( glf );
        break;
    }
}
    
//============================================================================
bool RenderShaderQt::onShaderGuiEnabled( QOpenGLFunctions * glf )
{

 /*
    const GLfloat *projMatrix = glMatrixProject.Get();
    const GLfloat *modelMatrix = glMatrixModview.Get();
    glf->glUniformMatrix4fv( m_hProj, 1, GL_FALSE, projMatrix );
    glf->glUniformMatrix4fv( m_hModel, 1, GL_FALSE, modelMatrix );

    const TransformMatrix &guiMatrix = CServiceBroker::GetWinSystem()->GetGfxContext().GetGUIMatrix();
    CRect viewPort; // absolute positions of corners
    CServiceBroker::GetRenderSystem()->GetViewPort( viewPort );
*/
    /* glScissor operates in window coordinates. In order that we can use it to
     * perform clipping, we must ensure that there is an independent linear
     * transformation from the coordinate system used by CGraphicContext::ClipRect
     * to window coordinates, separately for X and Y (in other words, no
     * rotation or shear is introduced at any stage). To do, this, we need to
     * check that zeros are present in the following locations:
     *
     * GUI matrix:
     * / * 0 * * \
     * | 0 * * * |
     * \ 0 0 * * /
     *       ^ TransformMatrix::TransformX/Y/ZCoord are only ever called with
     *         input z = 0, so this column doesn't matter
     * Model-view matrix:
     * / * 0 0 * \
     * | 0 * 0 * |
     * | 0 0 * * |
     * \ * * * * /  <- eye w has no influence on window x/y (last column below
     *                                                       is either 0 or ignored)
     * Projection matrix:
     * / * 0 0 0 \
     * | 0 * 0 0 |
     * | * * * * |  <- normalised device coordinate z has no influence on window x/y
     * \ 0 0 * 0 /
     *
     * Some of these zeros are not strictly required to ensure this, but they tend
     * to be zeroed in the common case, so by checking for zeros here, we simplify
     * the calculation of the window x/y coordinates further down the line.
     *
     * (Minor detail: we don't quite deal in window coordinates as defined by
     * OpenGL, because CRenderSystemGLES::SetScissors flips the Y axis. But all
     * that's needed to handle that is an effective negation at the stage where
     * Y is in normalized device coordinates.)
     */
    /*
    m_clipPossible = guiMatrix.m[ 0 ][ 1 ] == 0 &&
        guiMatrix.m[ 1 ][ 0 ] == 0 &&
        guiMatrix.m[ 2 ][ 0 ] == 0 &&
        guiMatrix.m[ 2 ][ 1 ] == 0 &&
        modelMatrix[ 0 + 1 * 4 ] == 0 &&
        modelMatrix[ 0 + 2 * 4 ] == 0 &&
        modelMatrix[ 1 + 0 * 4 ] == 0 &&
        modelMatrix[ 1 + 2 * 4 ] == 0 &&
        modelMatrix[ 2 + 0 * 4 ] == 0 &&
        modelMatrix[ 2 + 1 * 4 ] == 0 &&
        projMatrix[ 0 + 1 * 4 ] == 0 &&
        projMatrix[ 0 + 2 * 4 ] == 0 &&
        projMatrix[ 0 + 3 * 4 ] == 0 &&
        projMatrix[ 1 + 0 * 4 ] == 0 &&
        projMatrix[ 1 + 2 * 4 ] == 0 &&
        projMatrix[ 1 + 3 * 4 ] == 0 &&
        projMatrix[ 3 + 0 * 4 ] == 0 &&
        projMatrix[ 3 + 1 * 4 ] == 0 &&
        projMatrix[ 3 + 3 * 4 ] == 0;

    m_clipXFactor = 0.0;
    m_clipXOffset = 0.0;
    m_clipYFactor = 0.0;
    m_clipYOffset = 0.0;

    if( m_clipPossible )
    {
        m_clipXFactor = guiMatrix.m[ 0 ][ 0 ] * modelMatrix[ 0 + 0 * 4 ] * projMatrix[ 0 + 0 * 4 ];
        m_clipXOffset = ( guiMatrix.m[ 0 ][ 3 ] * modelMatrix[ 0 + 0 * 4 ] + modelMatrix[ 0 + 3 * 4 ] ) * projMatrix[ 0 + 0 * 4 ];
        m_clipYFactor = guiMatrix.m[ 1 ][ 1 ] * modelMatrix[ 1 + 1 * 4 ] * projMatrix[ 1 + 1 * 4 ];
        m_clipYOffset = ( guiMatrix.m[ 1 ][ 3 ] * modelMatrix[ 1 + 1 * 4 ] + modelMatrix[ 1 + 3 * 4 ] ) * projMatrix[ 1 + 1 * 4 ];
        float clipW = ( guiMatrix.m[ 2 ][ 3 ] * modelMatrix[ 2 + 2 * 4 ] + modelMatrix[ 2 + 3 * 4 ] ) * projMatrix[ 3 + 2 * 4 ];
        float xMult = ( viewPort.x2 - viewPort.x1 ) / ( 2 * clipW );
        float yMult = ( viewPort.y1 - viewPort.y2 ) / ( 2 * clipW ); // correct for inverted window coordinate scheme
        m_clipXFactor = m_clipXFactor * xMult;
        m_clipXOffset = m_clipXOffset * xMult + ( viewPort.x2 + viewPort.x1 ) / 2;
        m_clipYFactor = m_clipYFactor * yMult;
        m_clipYOffset = m_clipYOffset * yMult + ( viewPort.y2 + viewPort.y1 ) / 2;
    }

    glf->glUniform1f( m_hBrightness, 0.0f );
    glf->glUniform1f( m_hContrast, 1.0f );
    */

    return true;
}

//============================================================================
bool RenderShaderQt::onShaderVideoFormatEnabled( QOpenGLFunctions * glf )
{
    //LogMsg( LOG_ERROR, "onShaderVideoFormatEnabled %s", describeShader( m_ShaderMethod ) );

    // set shader attributes once enabled
    m_RenderWidget->VerifyGLStateQt();
    glf->glUniform1i( m_hYTex, 0 );
    glf->glUniform1i( m_hUTex, 1 );
    glf->glUniform1i( m_hVTex, 2 );
    glf->glUniform2f( m_hStep, 1.0 / m_width, 1.0 / m_height );

    GLfloat matrix[ 4 ][ 4 ];
    // keep video levels
    CalculateYUVMatrixGLES( matrix, m_flags, m_format, m_black, m_contrast, !m_convertFullRange );

    glf->glUniformMatrix4fv( m_hMatrix, 1, GL_FALSE, ( GLfloat* )matrix );
    glf->glUniformMatrix4fv( m_hProj, 1, GL_FALSE, m_proj );
    glf->glUniformMatrix4fv( m_hModel, 1, GL_FALSE, m_model );
    glf->glUniform1f( m_hAlpha, m_alpha );
    m_RenderWidget->VerifyGLStateQt();

    switch( m_ShaderMethod )
    {
    case SM_VIDEO_YV12_BOB:
    case SM_VIDEO_NV12_BOB:
    case SM_VIDEO_YUY2_BOB:
    case SM_VIDEO_UYVY_BOB:
    case SM_VIDEO_NV12_RGB_BOB:
        glf->glUniform1i( m_hField, m_field );
        glf->glUniform1f( m_hStepX, 1.0f / ( float )m_width );
        glf->glUniform1f( m_hStepY, 1.0f / ( float )m_height );
        m_RenderWidget->VerifyGLStateQt();
        break;

    default:
        break;
    }

    return true;
}

//============================================================================
bool RenderShaderQt::onShaderVideoFilterEnabled( QOpenGLFunctions * glf )
{
    LogMsg( LOG_ERROR, "onShaderVideoFormatEnabled %s", describeShader( m_ShaderMethod ) );

    m_RenderWidget->VerifyGLStateQt();
    glf->glUniformMatrix4fv( m_hProj, 1, GL_FALSE, m_proj );
    glf->glUniformMatrix4fv( m_hModel, 1, GL_FALSE, m_model );
    glf->glUniform1f( m_hAlpha, m_alpha );

    switch( m_ShaderMethod )
    {
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
    {
        // set shader attributes once enabled
        glf->glActiveTexture( GL_TEXTURE2 );
        glf->glBindTexture( GL_TEXTURE_2D, m_kernelTex1 );

        glf->glActiveTexture( GL_TEXTURE0 );
        glf->glUniform1i( m_hSourceTex, m_sourceTexUnit );
        glf->glUniform1i( m_hKernTex, 2 );
        glf->glUniform2f( m_hStepXY, m_stepX, m_stepY );
        m_RenderWidget->VerifyGLStateQt();
        break;
    }

    default:
        break;
    }

    return true;
}

//============================================================================
const char * RenderShaderQt::describeShader( ESHADERMETHOD shaderType )
{
    switch( shaderType )
    {
    case SM_DEFAULT:
        return "SM_DEFAULT";
    case SM_TEXTURE:
        return "SM_TEXTURE";
    case SM_MULTI:
        return "SM_MULTI";
    case SM_FONTS:
        return "SM_FONTS";
    case SM_TEXTURE_NOBLEND:
        return "SM_TEXTURE_NOBLEND";
    case SM_MULTI_BLENDCOLOR:
        return "SM_MULTI_BLENDCOLOR";
    case SM_TEXTURE_RGBA:
        return "SM_TEXTURE_RGBA";
    case SM_TEXTURE_RGBA_OES:
        return "SM_TEXTURE_RGBA_OES";
    case SM_TEXTURE_RGBA_BLENDCOLOR:
        return "SM_TEXTURE_RGBA_BLENDCOLOR";
    case SM_TEXTURE_RGBA_BOB:
        return "SM_TEXTURE_RGBA_BOB";
    case SM_TEXTURE_RGBA_BOB_OES:
        return "SM_TEXTURE_RGBA_BOB_OES";
    case SM_VIDEO_YV12_BASIC:
        return "SM_VIDEO_YV12_BASIC";
    case SM_VIDEO_NV12_BASIC:
        return "SM_VIDEO_NV12_BASIC";
    case SM_VIDEO_YUY2_BASIC:
        return "SM_VIDEO_YUY2_BASIC";
    case SM_VIDEO_UYVY_BASIC:
        return "SM_VIDEO_UYVY_BASIC";
    case SM_VIDEO_NV12_RGB_BASIC:
        return "SM_VIDEO_NV12_RGB_BASIC";
    case SM_VIDEO_YV12_BOB:
        return "SM_VIDEO_YV12_BOB";
    case SM_VIDEO_NV12_BOB:
        return "SM_VIDEO_NV12_BOB";
    case SM_VIDEO_YUY2_BOB:
        return "SM_VIDEO_YUY2_BOB";
    case SM_VIDEO_UYVY_BOB:
        return "SM_VIDEO_UYVY_BOB";
    case SM_VIDEO_NV12_RGB_BOB:
        return "SM_VIDEO_NV12_RGB_BOB";
    case SM_VID_FILTER_DEFAULT:
        return "SM_VID_FILTER_DEFAULT";
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
        return "SM_VID_FILTER_CONVOLUTION_4X4_RGBA";
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
        return "SM_VID_FILTER_CONVOLUTION_4X4_FLOAT";
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
        return "SM_VID_FILTER_CONVOLUTION_6X6_RGBA";
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
        return "SM_VID_FILTER_CONVOLUTION_6X6_FLOAT";
    case SM_SHADER_NONE:
        return "SM_SHADER_NONE";
    default:
        return "SM_UNKNOWN";
    }
}

//============================================================================
void RenderShaderQt::onDisabled()
{
}

//============================================================================
void RenderShaderQt::onFree()
{
    if( m_kernelTex1 )
    {
        glDeleteTextures( 1, &m_kernelTex1 );
    }

    m_kernelTex1 = 0;

    removeAllShaders();
    deleteLater();
}

//============================================================================
bool RenderShaderQt::enableShader()
{
    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glUseProgram( programId() );
    if( onEnabled() )
    {
        if( !m_validated )
        {
            // validate the program
            GLint params[ 4 ];
            glf->glValidateProgram( programId() );
            glf->glGetProgramiv( programId(), GL_VALIDATE_STATUS, params );
            if( params[ 0 ] != GL_TRUE )
            {
                #define LOG_SIZE 1024

                GLchar log[ LOG_SIZE ];
                LogMsg( LOG_ERROR, "GL: Error validating shader" );
                glf->glGetProgramInfoLog( programId(), LOG_SIZE, NULL, log );
                LogMsg( LOG_ERROR, "%s", log );
            }

            m_validated = true;
        }

        //VerifyGLStateQt();
        return true;
    }
    else
    {
        glf->glUseProgram( 0 );
        return false;
    }

    return true;
}

//============================================================================
bool RenderShaderQt::disableShader()
{
    switch( m_ShaderMethod )
    {
    case SM_VID_FILTER_CONVOLUTION_4X4_RGBA:
    case SM_VID_FILTER_CONVOLUTION_4X4_FLOAT:
    case SM_VID_FILTER_CONVOLUTION_6X6_RGBA:
    case SM_VID_FILTER_CONVOLUTION_6X6_FLOAT:
        return true; 
    }

    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glUseProgram( 0 );
    onDisabled();
    return true;
}

// yuv shader
//============================================================================
void RenderShaderQt::shaderSetField( int field )
{
    m_field = field;
    //VerifyGLStateQt();
}

//============================================================================
void RenderShaderQt::shaderSetWidth( int w )
{
    m_width = w;
    //VerifyGLStateQt();
}

//============================================================================
void RenderShaderQt::shaderSetHeight( int h )
{
    m_height = h;

   // VerifyGLStateQt();
}

//============================================================================
void RenderShaderQt::shaderSetBlack( float black )
{
    m_black = black;

    //VerifyGLStateQt();
}

//============================================================================
void RenderShaderQt::shaderSetContrast( float contrast )
{
    m_contrast = contrast;
    //VerifyGLStateQt();
}

//============================================================================
void RenderShaderQt::shaderSetConvertFullColorRange( bool convertFullRange )
{
    m_convertFullRange = convertFullRange;
    //VerifyGLStateQt();
}

//============================================================================
int RenderShaderQt::shaderGetVertexLoc(  )
{
    //VerifyGLStateQt();
    return m_hVertex;
}

//============================================================================
int RenderShaderQt::shaderGetYcoordLoc(  )
{
    //VerifyGLStateQt();
    return m_hYcoord;
}

//============================================================================
int RenderShaderQt::shaderGetUcoordLoc(  )
{
    //VerifyGLStateQt();
    return m_hUcoord;
}

//============================================================================
int RenderShaderQt::shaderGetVcoordLoc(  )
{
    //VerifyGLStateQt();
    return m_hVcoord;
}

//============================================================================
void RenderShaderQt::shaderSetMatrices( const float *p, const float *m )
{
    m_proj = p; 
    m_model = m;
}

//============================================================================
void RenderShaderQt::shaderSetAlpha( float alpha )
{
    m_alpha = alpha;
}

//============================================================================
void RenderShaderQt::shaderSetFlags( unsigned int flags )
{
    m_flags = flags;
}

//============================================================================
void RenderShaderQt::shaderSetFormat(  EShaderFormat format )
{
    m_format = format;
}

//============================================================================
void RenderShaderQt::shaderSourceTexture( int ytex )
{
    m_sourceTexUnit = ytex;
}

//============================================================================
void RenderShaderQt::shaderSetStepX( float stepX )
{
    m_stepX = stepX;
}

//============================================================================
void RenderShaderQt::shaderSetStepY( float stepY )
{
    m_stepY = stepY;
}

//============================================================================
// filter shader
bool RenderShaderQt::shaderGetTextureFilter(  int& filter )
{
    return false;
}

//============================================================================
int RenderShaderQt::shaderGetcoordLoc(  )
{
    //VerifyGLStateQt();
    return m_hcoord;
}

//============================================================================
int RenderShaderQt::shaderVertexAttribPointer( unsigned int index, int size, int type, bool normalized, int stride, const void * pointer )
{
    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glVertexAttribPointer( index, size, type, normalized, stride, pointer );
    //VerifyGLStateQt();
    return 0; // return value not needed .. should be void
}

//============================================================================
void RenderShaderQt::shaderEnableVertexAttribArray( int arrayId )
{
    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glEnableVertexAttribArray( arrayId );
    //VerifyGLStateQt();
}

//============================================================================
void RenderShaderQt::shaderDisableVertexAttribArray( int arrayId )
{
    QOpenGLFunctions * glf = m_RenderWidget->getGlFunctions();
    glf->glDisableVertexAttribArray( arrayId );
    //VerifyGLStateQt();
}


