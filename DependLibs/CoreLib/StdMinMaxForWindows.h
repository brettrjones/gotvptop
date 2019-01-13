#pragma once
#if defined(TARGET_OS_WINDOWS) && defined(_MSC_VER)
// crazy microsoft does not have std::min
#if defined __cplusplus
namespace std
{
    template<typename _Tp, typename _Tp2>
    inline const _Tp&
        min( const _Tp& __a, const _Tp2& __b )
    {
        if( __b < __a )
            return __b;
        return __a;
    }

    template<typename _Tp, typename _Tp2>
    inline const _Tp&
        max( const _Tp& __a, const _Tp2& __b )
    {
        if( __b > __a )
            return __b;
        return __a;
    }
};
#endif // #if defined __cplusplus
#endif // defined(TARGET_OS_WINDOWS) && defined(_MSC_VER)
