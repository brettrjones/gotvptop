#pragma once
// uncomment flags for enabling debug message
#if defined(DEBUG) || defined(_DEBUG) || defined(debug)
//=== audio ===//
//# define DEBUG_QT_AUDIO

//=== render ===//

//# define DEBUG_OPENGL
//# define DEBUG_QT_RENDER

//=== network ===//
//# define DEBUG_PTOP_NETWORK_STATE // PtoP networking
//# define DEBUG_VXSERVER_MGR
//# define DEBUG_SKT_CONNECTIONS
//# define DEBUG_SKTS
//# define DEBUG_NETLIB
//# define DEBUG_PKT_LIB

//=== kodi ===//
//=== kodi audio ===//
//# define DEBUG_AUDIO_DECODE_KODI
//# define DEBUG_KODI_AUDIO

//=== kodi render ===//
# define DEBUG_KODI_RENDER
//# define DEBUG_KODI_SHADERS

//=== kodi other ===//
# define DEBUG_KODI_ENABLE_DEBUG_LOGGING    // log anything debug level and higher
# define DEBUG_KODI_EXTRA_LOGGING // enable logging of all kodi extra modules

# define DEBUG_KODI_ADDONS
# define DEBUG_KODI_PLUGINS

# define DEBUG_KODI_CURL
# define DEBUG_KODI_UPDATER // NOTE: forces kodi to update every run
# define DEBUG_KODI_PYTHON

//=== threads ===//
//# define DEBUG_THREADS

//=== other ===//
//# define DEBUG_BIGLIST_DB
//# define DEBUG_FFMPEG_ENABLE_LOGGING // enable verbose ffmpeg logging

#endif // defined(DEBUG) || defined(_DEBUG)
