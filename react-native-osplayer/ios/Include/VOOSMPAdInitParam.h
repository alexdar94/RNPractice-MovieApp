/************************************************************************
VisualOn Proprietary
Copyright (c) 2013, VisualOn Incorporated. All Rights Reserved

VisualOn, Inc., USA

All data and information contained in or disclosed by this document are
confidential and proprietary information of VisualOn, and all rights
therein are expressly reserved. By accepting this material, the
recipient agrees that this material and the information contained
therein are held in confidence and in trust. The material may only be
used and/or disclosed as authorized in a license agreement controlling
such use and disclosure.
************************************************************************/
#ifndef __VOOSMP_AD_INITPARAM_H__
#define __VOOSMP_AD_INITPARAM_H__

#include "VOOSMPInterface.h"
#include "VOOSMPType.h"
#include "VOOSMPString.h"

class VOCommonPlayerAPI VOOSMPAdInitParam
{
    public:
        VOOSMPAdInitParam();
        ~VOOSMPAdInitParam();
        
        /**
         * Get library directory path setting
         *
         * @return  library directory path 
         */
        VOOSMPString getLibraryPath() const;


        /**
         * Get license content array 
         *
         * @return  license content array
         */
        unsigned char* getLicenseContent() const;


        /**
         * Get length of the license content array 
         *
         * @return  length of the license content array
         */
        unsigned getLicenseContentLength() const;


        /**
         * Get license file path 
         *
         * @return  license file path
         */
        VOOSMPString getLicenseLicenseFilePath() const;


        /**
         * Get pre-agreed license string
         *
         * @return  pre-agreed license string
         */
        VOOSMPString getPreAgreedLicense() const;


        /**
         * Set library path
         *
         * @param  libPath [in] Full directory path of package library 
         *                      (for example, /data/data/package_name/lib)
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         */
        VO_OSMP_RETURN_CODE setLibraryPath(const VOOSMPString& libPath);


        /**
         * Set contents of license file. 
         *
         * If both the content of license file and a license file path is 
         * set, the content of license file will be used
         *
         * @param   data    [in] Contents of the license file in a unsigned 
         *                       char array
         * @param   length  [in] length of license content array
         *
         * @return {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
         *
         */
        VO_OSMP_RETURN_CODE setLicenseContent(unsigned char* data, 
                                              unsigned length);

        /**
         * Set the location of the license file.
         *
         * If both the content of license file and a license file path is 
         * set, the content of license file will be used
         *
         * @param   path  [in] Location of the license file.
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful
         *
         */
        VO_OSMP_RETURN_CODE setLicenseFilePath(const VOOSMPString& path);


        /**
         * Set pre-agreed license string. 
         *
         * Pre-agreed license string is not used if it is empty
         *
         * @param   str   [in] Pre-agreed license string.
         *
         * @return  {@link VO_OSMP_RETURN_CODE#VO_OSMP_ERR_NONE} if successful.
         *
         */
        VO_OSMP_RETURN_CODE setPreAgreedLicense(const VOOSMPString& str);

    private:
        VOOSMPString   _libraryPath;
        VOOSMPString   _licenseFilePath;
        VOOSMPString   _PreAgreedLicense;
        unsigned char* _licenseContent;
        unsigned       _licenseContentLength;
};

#endif
