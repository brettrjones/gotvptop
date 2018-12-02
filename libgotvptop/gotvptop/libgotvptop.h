/*****************************************************************************
 * libgotvptop.h:  libgotvptop external API
 *****************************************************************************
 * Copyright (C) 1998-2009 GOTV authors and VideoLAN
 * $Id: 78afe99f1612413e671f44001df68f2b9c19e62d $
 *
 * Authors: Clément Stenac <zorglub@videolan.org>
 *          Jean-Paul Saman <jpsaman@videolan.org>
 *          Pierre d'Herbemont <pdherbemont@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/**
 * \defgroup libgotvptop LibGOTV
 * LibGOTV is the external programming interface of the GOTV media player.
 * It is used to embed GOTV into other applications or frameworks.
 * @{
 * \file
 * LibGOTV core external API
 */

#ifndef GOTV_LIBGOTV_H
#define GOTV_LIBGOTV_H 1

#if defined (_WIN32) && defined (DLL_EXPORT)
# define LIBGOTV_API __declspec(dllexport)
#elif defined (__GNUC__) && (__GNUC__ >= 4)
# define LIBGOTV_API __attribute__((visibility("default")))
#else
# define LIBGOTV_API
#endif

#ifdef __LIBGOTV__
/* Avoid unhelpful warnings from libgotvptop with our deprecated APIs */
#   define LIBGOTV_DEPRECATED
#elif defined(__GNUC__) && \
      (__GNUC__ > 3 || __GNUC__ == 3 && __GNUC_MINOR__ > 0)
# define LIBGOTV_DEPRECATED __attribute__((deprecated))
#else
# define LIBGOTV_DEPRECATED
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>


/** \defgroup libgotvptop_core LibGOTV core
 * \ingroup libgotvptop
 * Before it can do anything useful, LibGOTV must be initialized.
 * You can create one (or more) instance(s) of LibGOTV in a given process,
 * with libgotvptop_new() and destroy them with libgotvptop_release().
 *
 * \version Unless otherwise stated, these functions are available
 * from LibGOTV versions numbered 1.1.0 or more.
 * Earlier versions (0.9.x and 1.0.x) are <b>not</b> compatible.
 * @{
 */

/** This structure is opaque. It represents a libgotvptop instance */
typedef struct libgotvptop_instance_t libgotvptop_instance_t;

typedef int64_t libgotvptop_time_t;

/** \defgroup libgotvptop_error LibGOTV error handling
 * @{
 */

/**
 * A human-readable error message for the last LibGOTV error in the calling
 * thread. The resulting string is valid until another error occurs (at least
 * until the next LibGOTV call).
 *
 * @warning
 * This will be NULL if there was no error.
 */
LIBGOTV_API const char *libgotvptop_errmsg (void);

/**
 * Clears the LibGOTV error status for the current thread. This is optional.
 * By default, the error status is automatically overridden when a new error
 * occurs, and destroyed when the thread exits.
 */
LIBGOTV_API void libgotvptop_clearerr (void);

/**
 * Sets the LibGOTV error status and message for the current thread.
 * Any previous error is overridden.
 * \param fmt the format string
 * \param ap the arguments
 * \return a nul terminated string in any case
 */
LIBGOTV_API const char *libgotvptop_vprinterr (const char *fmt, va_list ap);

/**
 * Sets the LibGOTV error status and message for the current thread.
 * Any previous error is overridden.
 * \param fmt the format string
 * \param args the arguments
 * \return a nul terminated string in any case
 */
LIBGOTV_API const char *libgotvptop_printerr (const char *fmt, ...);

/**@} */

/**
 * Create and initialize a libgotvptop instance.
 * This functions accept a list of "command line" arguments similar to the
 * main(). These arguments affect the LibGOTV instance default configuration.
 *
 * \note
 * LibGOTV may create threads. Therefore, any thread-unsafe process
 * initialization must be performed before calling libgotvptop_new(). In particular
 * and where applicable:
 * - setlocale() and textdomain(),
 * - setenv(), unsetenv() and putenv(),
 * - with the X11 display system, XInitThreads()
 *   (see also libgotvptop_media_player_set_xwindow()) and
 * - on Microsoft Windows, SetErrorMode().
 * - sigprocmask() shall never be invoked; pthread_sigmask() can be used.
 *
 * On POSIX systems, the SIGCHLD signal <b>must not</b> be ignored, i.e. the
 * signal handler must set to SIG_DFL or a function pointer, not SIG_IGN.
 * Also while LibGOTV is active, the wait() function shall not be called, and
 * any call to waitpid() shall use a strictly positive value for the first
 * parameter (i.e. the PID). Failure to follow those rules may lead to a
 * deadlock or a busy loop.
 * Also on POSIX systems, it is recommended that the SIGPIPE signal be blocked,
 * even if it is not, in principles, necessary, e.g.:
 * @code
   sigset_t set;

   signal(SIGCHLD, SIG_DFL);
   sigemptyset(&set);
   sigaddset(&set, SIGPIPE);
   pthread_sigmask(SIG_BLOCK, &set, NULL);
 * @endcode
 *
 * On Microsoft Windows, setting the default DLL directories to SYSTEM32
 * exclusively is strongly recommended for security reasons:
 * @code
   SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32);
 * @endcode
 *
 * \version
 * Arguments are meant to be passed from the command line to LibGOTV, just like
 * GOTV media player does. The list of valid arguments depends on the LibGOTV
 * version, the operating system and platform, and set of available LibGOTV
 * plugins. Invalid or unsupported arguments will cause the function to fail
 * (i.e. return NULL). Also, some arguments may alter the behaviour or
 * otherwise interfere with other LibGOTV functions.
 *
 * \warning
 * There is absolutely no warranty or promise of forward, backward and
 * cross-platform compatibility with regards to libgotvptop_new() arguments.
 * We recommend that you do not use them, other than when debugging.
 *
 * \param argc the number of arguments (should be 0)
 * \param argv list of arguments (should be NULL)
 * \return the libgotvptop instance or NULL in case of error
 */
LIBGOTV_API libgotvptop_instance_t *
libgotvptop_new( int argc , const char *const *argv );

/**
 * Decrement the reference count of a libgotvptop instance, and destroy it
 * if it reaches zero.
 *
 * \param p_instance the instance to destroy
 */
LIBGOTV_API void libgotvptop_release( libgotvptop_instance_t *p_instance );

/**
 * Increments the reference count of a libgotvptop instance.
 * The initial reference count is 1 after libgotvptop_new() returns.
 *
 * \param p_instance the instance to reference
 */
LIBGOTV_API void libgotvptop_retain( libgotvptop_instance_t *p_instance );

/**
 * Try to start a user interface for the libgotvptop instance.
 *
 * \param p_instance the instance
 * \param name interface name, or NULL for default
 * \return 0 on success, -1 on error.
 */
LIBGOTV_API
int libgotvptop_add_intf( libgotvptop_instance_t *p_instance, const char *name );

/**
 * Registers a callback for the LibGOTV exit event. This is mostly useful if
 * the GOTV playlist and/or at least one interface are started with
 * libgotvptop_playlist_play() or libgotvptop_add_intf() respectively.
 * Typically, this function will wake up your application main loop (from
 * another thread).
 *
 * \note This function should be called before the playlist or interface are
 * started. Otherwise, there is a small race condition: the exit event could
 * be raised before the handler is registered.
 *
 * \param p_instance LibGOTV instance
 * \param cb callback to invoke when LibGOTV wants to exit,
 *           or NULL to disable the exit handler (as by default)
 * \param opaque data pointer for the callback
 * \warning This function and libgotvptop_wait() cannot be used at the same time.
 */
LIBGOTV_API
void libgotvptop_set_exit_handler( libgotvptop_instance_t *p_instance,
                              void (*cb) (void *), void *opaque );

/**
 * Sets the application name. LibGOTV passes this as the user agent string
 * when a protocol requires it.
 *
 * \param p_instance LibGOTV instance
 * \param name human-readable application name, e.g. "FooBar player 1.2.3"
 * \param http HTTP User Agent, e.g. "FooBar/1.2.3 Python/2.6.0"
 * \version LibGOTV 1.1.1 or later
 */
LIBGOTV_API
void libgotvptop_set_user_agent( libgotvptop_instance_t *p_instance,
                            const char *name, const char *http );

/**
 * Sets some meta-information about the application.
 * See also libgotvptop_set_user_agent().
 *
 * \param p_instance LibGOTV instance
 * \param id Java-style application identifier, e.g. "com.acme.foobar"
 * \param version application version numbers, e.g. "1.2.3"
 * \param icon application icon name, e.g. "foobar"
 * \version LibGOTV 2.1.0 or later.
 */
LIBGOTV_API
void libgotvptop_set_app_id( libgotvptop_instance_t *p_instance, const char *id,
                        const char *version, const char *icon );

/**
 * Retrieve libgotvptop version.
 *
 * Example: "1.1.0-git The Luggage"
 *
 * \return a string containing the libgotvptop version
 */
LIBGOTV_API const char * libgotvptop_get_version(void);

/**
 * Retrieve libgotvptop compiler version.
 *
 * Example: "gcc version 4.2.3 (Ubuntu 4.2.3-2ubuntu6)"
 *
 * \return a string containing the libgotvptop compiler version
 */
LIBGOTV_API const char * libgotvptop_get_compiler(void);

/**
 * Retrieve libgotvptop changeset.
 *
 * Example: "aa9bce0bc4"
 *
 * \return a string containing the libgotvptop changeset
 */
LIBGOTV_API const char * libgotvptop_get_changeset(void);

/**
 * Frees an heap allocation returned by a LibGOTV function.
 * If you know you're using the same underlying C run-time as the LibGOTV
 * implementation, then you can call ANSI C free() directly instead.
 *
 * \param ptr the pointer
 */
LIBGOTV_API void libgotvptop_free( void *ptr );

/** \defgroup libgotvptop_event LibGOTV asynchronous events
 * LibGOTV emits asynchronous events.
 *
 * Several LibGOTV objects (such @ref libgotvptop_instance_t as
 * @ref libgotvptop_media_player_t) generate events asynchronously. Each of them
 * provides @ref libgotvptop_event_manager_t event manager. You can subscribe to
 * events with libgotvptop_event_attach() and unsubscribe with
 * libgotvptop_event_detach().
 * @{
 */

/**
 * Event manager that belongs to a libgotvptop object, and from whom events can
 * be received.
 */
typedef struct libgotvptop_event_manager_t libgotvptop_event_manager_t;

struct libgotvptop_event_t;

/**
 * Type of a LibGOTV event.
 */
typedef int libgotvptop_event_type_t;

/**
 * Callback function notification
 * \param p_event the event triggering the callback
 */
typedef void ( *libgotvptop_callback_t )( const struct libgotvptop_event_t *p_event, void *p_data );

/**
 * Register for an event notification.
 *
 * \param p_event_manager the event manager to which you want to attach to.
 *        Generally it is obtained by gotvptop_my_object_event_manager() where
 *        my_object is the object you want to listen to.
 * \param i_event_type the desired event to which we want to listen
 * \param f_callback the function to call when i_event_type occurs
 * \param user_data user provided data to carry with the event
 * \return 0 on success, ENOMEM on error
 */
LIBGOTV_API int libgotvptop_event_attach( libgotvptop_event_manager_t *p_event_manager,
                                        libgotvptop_event_type_t i_event_type,
                                        libgotvptop_callback_t f_callback,
                                        void *user_data );

/**
 * Unregister an event notification.
 *
 * \param p_event_manager the event manager
 * \param i_event_type the desired event to which we want to unregister
 * \param f_callback the function to call when i_event_type occurs
 * \param p_user_data user provided data to carry with the event
 */
LIBGOTV_API void libgotvptop_event_detach( libgotvptop_event_manager_t *p_event_manager,
                                         libgotvptop_event_type_t i_event_type,
                                         libgotvptop_callback_t f_callback,
                                         void *p_user_data );

/**
 * Get an event's type name.
 *
 * \param event_type the desired event
 */
LIBGOTV_API const char * libgotvptop_event_type_name( libgotvptop_event_type_t event_type );

/** @} */

/** \defgroup libgotvptop_log LibGOTV logging
 * libgotvptop_log_* functions provide access to the LibGOTV messages log.
 * This is used for logging and debugging.
 * @{
 */

/**
 * Logging messages level.
 * \note Future LibGOTV versions may define new levels.
 */
enum libgotvptop_log_level
{
    LIBGOTV_DEBUG=0,   /**< Debug message */
    LIBGOTV_NOTICE=2,  /**< Important informational message */
    LIBGOTV_WARNING=3, /**< Warning (potential error) message */
    LIBGOTV_ERROR=4    /**< Error message */
};

typedef struct gotvptop_log_t libgotvptop_log_t;

/**
 * Gets log message debug infos.
 *
 * This function retrieves self-debug information about a log message:
 * - the name of the GOTV module emitting the message,
 * - the name of the source code module (i.e. file) and
 * - the line number within the source code module.
 *
 * The returned module name and file name will be NULL if unknown.
 * The returned line number will similarly be zero if unknown.
 *
 * \param ctx message context (as passed to the @ref libgotvptop_log_cb callback)
 * \param module module name storage (or NULL) [OUT]
 * \param file source code file name storage (or NULL) [OUT]
 * \param line source code file line number storage (or NULL) [OUT]
 * \warning The returned module name and source code file name, if non-NULL,
 * are only valid until the logging callback returns.
 *
 * \version LibGOTV 2.1.0 or later
 */
LIBGOTV_API void libgotvptop_log_get_context(const libgotvptop_log_t *ctx,
                       const char **module, const char **file, unsigned *line);

/**
 * Gets log message info.
 *
 * This function retrieves meta-information about a log message:
 * - the type name of the GOTV object emitting the message,
 * - the object header if any, and
 * - a temporaly-unique object identifier.
 *
 * This information is mainly meant for <b>manual</b> troubleshooting.
 *
 * The returned type name may be "generic" if unknown, but it cannot be NULL.
 * The returned header will be NULL if unset; in current versions, the header
 * is used to distinguish for VLM inputs.
 * The returned object ID will be zero if the message is not associated with
 * any GOTV object.
 *
 * \param ctx message context (as passed to the @ref libgotvptop_log_cb callback)
 * \param name object name storage (or NULL) [OUT]
 * \param header object header (or NULL) [OUT]
 * \param line source code file line number storage (or NULL) [OUT]
 * \warning The returned module name and source code file name, if non-NULL,
 * are only valid until the logging callback returns.
 *
 * \version LibGOTV 2.1.0 or later
 */
LIBGOTV_API void libgotvptop_log_get_object(const libgotvptop_log_t *ctx,
                        const char **name, const char **header, uintptr_t *id);

/**
 * Callback prototype for LibGOTV log message handler.
 *
 * \param data data pointer as given to libgotvptop_log_set()
 * \param level message level (@ref libgotvptop_log_level)
 * \param ctx message context (meta-information about the message)
 * \param fmt printf() format string (as defined by ISO C11)
 * \param args variable argument list for the format
 * \note Log message handlers <b>must</b> be thread-safe.
 * \warning The message context pointer, the format string parameters and the
 *          variable arguments are only valid until the callback returns.
 */
typedef void (*libgotvptop_log_cb)(void *data, int level, const libgotvptop_log_t *ctx,
                              const char *fmt, va_list args);

/**
 * Unsets the logging callback.
 *
 * This function deregisters the logging callback for a LibGOTV instance.
 * This is rarely needed as the callback is implicitly unset when the instance
 * is destroyed.
 *
 * \note This function will wait for any pending callbacks invocation to
 * complete (causing a deadlock if called from within the callback).
 *
 * \param p_instance libgotvptop instance
 * \version LibGOTV 2.1.0 or later
 */
LIBGOTV_API void libgotvptop_log_unset( libgotvptop_instance_t *p_instance );

/**
 * Sets the logging callback for a LibGOTV instance.
 *
 * This function is thread-safe: it will wait for any pending callbacks
 * invocation to complete.
 *
 * \param cb callback function pointer
 * \param data opaque data pointer for the callback function
 *
 * \note Some log messages (especially debug) are emitted by LibGOTV while
 * is being initialized. These messages cannot be captured with this interface.
 *
 * \warning A deadlock may occur if this function is called from the callback.
 *
 * \param p_instance libgotvptop instance
 * \version LibGOTV 2.1.0 or later
 */
LIBGOTV_API void libgotvptop_log_set( libgotvptop_instance_t *p_instance,
                                libgotvptop_log_cb cb, void *data );


/**
 * Sets up logging to a file.
 * \param p_instance libgotvptop instance
 * \param stream FILE pointer opened for writing
 *         (the FILE pointer must remain valid until libgotvptop_log_unset())
 * \version LibGOTV 2.1.0 or later
 */
LIBGOTV_API void libgotvptop_log_set_file( libgotvptop_instance_t *p_instance, FILE *stream );

/** @} */

/**
 * Description of a module.
 */
typedef struct libgotvptop_module_description_t
{
    char *psz_name;
    char *psz_shortname;
    char *psz_longname;
    char *psz_help;
    struct libgotvptop_module_description_t *p_next;
} libgotvptop_module_description_t;

/**
 * Release a list of module descriptions.
 *
 * \param p_list the list to be released
 */
LIBGOTV_API
void libgotvptop_module_description_list_release( libgotvptop_module_description_t *p_list );

/**
 * Returns a list of audio filters that are available.
 *
 * \param p_instance libgotvptop instance
 *
 * \return a list of module descriptions. It should be freed with libgotvptop_module_description_list_release().
 *         In case of an error, NULL is returned.
 *
 * \see libgotvptop_module_description_t
 * \see libgotvptop_module_description_list_release
 */
LIBGOTV_API
libgotvptop_module_description_t *libgotvptop_audio_filter_list_get( libgotvptop_instance_t *p_instance );

/**
 * Returns a list of video filters that are available.
 *
 * \param p_instance libgotvptop instance
 *
 * \return a list of module descriptions. It should be freed with libgotvptop_module_description_list_release().
 *         In case of an error, NULL is returned.
 *
 * \see libgotvptop_module_description_t
 * \see libgotvptop_module_description_list_release
 */
LIBGOTV_API
libgotvptop_module_description_t *libgotvptop_video_filter_list_get( libgotvptop_instance_t *p_instance );

/** @} */

/** \defgroup libgotvptop_clock LibGOTV time
 * These functions provide access to the LibGOTV time/clock.
 * @{
 */

/**
 * Return the current time as defined by LibGOTV. The unit is the microsecond.
 * Time increases monotonically (regardless of time zone changes and RTC
 * adjustements).
 * The origin is arbitrary but consistent across the whole system
 * (e.g. the system uptim, the time since the system was booted).
 * \note On systems that support it, the POSIX monotonic clock is used.
 */
LIBGOTV_API
int64_t libgotvptop_clock(void);

/**
 * Return the delay (in microseconds) until a certain timestamp.
 * \param pts timestamp
 * \return negative if timestamp is in the past,
 * positive if it is in the future
 */
static inline int64_t libgotvptop_delay(int64_t pts)
{
    return pts - libgotvptop_clock();
}


#endif /** @} */
