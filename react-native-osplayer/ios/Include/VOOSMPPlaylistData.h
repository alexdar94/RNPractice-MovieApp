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

#import <Foundation/Foundation.h>

@protocol VOOSMPPlaylistData <NSObject>

/**
 * Get the root URL of parent playlist
 *
 * @return root URL
 */
@property (readonly, retain, getter=getRootURL) NSString* rootURL;

/**
 * Get the URL of the playlist ,it can be relative URL.
 *
 * @return playlist URL
 */
@property (readonly, retain, getter=getURL) NSString* URL;

/**
 * Get the URL after download( can be redirect forever ), you should always use this url after get this struct.
 *
 * @return new URL
 */
@property (readonly, retain, getter=getNewURL) NSString* newURL;

/**
 * Get the data in the playlist.
 *
 * @return data
 */
@property (readonly, retain, getter=getData) NSData* data;

/**
 * Get the playlist size
 *
 * @return data size
 */
@property (readonly, assign, getter=getDataSize) int dataSize;

/**
 * Get the playlist type.
 *
 * @return chunk type
 */
@property (readonly, assign, getter=getPlaylistType) int playlistType;

/**
 * Get the error code of this chunk.
 *
 * @return error code
 */
@property (readonly, assign, getter=getErrorCode) int errorCode;

/**
 * Get the error type of this chunk.
 *
 * @return error type
 */
@property (readonly, assign,getter=getErrorType) VO_OSMP_STREAMING_ERROR_TYPE errorType;

@end


