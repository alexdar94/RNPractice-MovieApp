/************************************************************************
VisualOn Proprietary
Copyright (c) 2012-2016, VisualOn, Inc. All Rights Reserved
 
All data and information contained in or disclosed by this document are 
confidential and proprietary information of VisualOn, Inc, and all rights 
therein are expressly reserved. By accepting this material, the recipient 
agrees that this material and the information contained therein are held 
in confidence and in trust. The material may only be used and/or disclosed 
as authorized in a license agreement controlling such use and disclosure.
 ************************************************************************/

#ifndef __VO_OSMP_INTERFACE__
#define __VO_OSMP_INTERFACE__

#ifdef VOCommonPlayerAPI_EXPORTS
#define VOCommonPlayerAPI __declspec(dllexport)
#elif defined (VOCommonPlayerAPI_IMPORTS)
#define VOCommonPlayerAPI __declspec(dllimport)
#else
#define VOCommonPlayerAPI 
#endif

#define VOOSMP_INTERFACE(VOOSMP_INTERFACE_NAME, VOOSMP_INTERFACE_NAMEIMPL) public: \
/** \
 * Get the status of object. \
 * \
 * @return    true if valid. \
 */ \
bool isValid() const; \
\
/** \
* create object \
*/ \
VOOSMP_INTERFACE_NAME(); \
\
/** \
 * destory object \
 */ \
~VOOSMP_INTERFACE_NAME(); \
\
/** \
 * copy object \
 */ \
VOOSMP_INTERFACE_NAME(const VOOSMP_INTERFACE_NAME& toCopy); \
\
/** \
 * copy object \
 */ \
VOOSMP_INTERFACE_NAME& operator=(const VOOSMP_INTERFACE_NAME& toCopy); \
\
private: \
\
friend class VOCommonPlayerImpl; \
friend class VOOSMPStreamingDownloaderImpl; \
\
VOOSMP_INTERFACE_NAME(VOOSMP_INTERFACE_NAMEIMPL& impl); \
\
private: \
VOOSMP_INTERFACE_NAMEIMPL* _impl;


#endif // __VO_OSMP_INTERFACE__


