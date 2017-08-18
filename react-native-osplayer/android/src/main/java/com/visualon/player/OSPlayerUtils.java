package com.visualon.player;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;

import com.visualon.OSMPPlayer.VOOSMPType;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class OSPlayerUtils {

    // Get user path for Jelly Bean 4.2
    public static String getUserPath(Context context) {
        PackageManager m = context.getPackageManager();
        String path = context.getPackageName();
        String userPath = "/data/data/" + path;
        try {
            PackageInfo p = m.getPackageInfo(path, 0);
            userPath = p.applicationInfo.dataDir;
        } catch (PackageManager.NameNotFoundException e) {
        }

        return userPath;
    }

    // Copy file from Assets directory to destination
    // Used for licenses and processor-specific configurations
    public static void copyFile(Context context, String filename,
                                 String desName) {
        try {
            InputStream is = context.getAssets().open(filename);
            File desFile = new File(getUserPath(context) + "/" + desName);
            desFile.createNewFile();
            FileOutputStream fos = new FileOutputStream(desFile);
            int bytesRead;
            byte[] buf = new byte[4 * 1024]; // 4K buffer

            while ((bytesRead = is.read(buf)) != -1) {
                fos.write(buf, 0, bytesRead);
            }
            fos.flush();
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static boolean isErrorCode(VOOSMPType.VO_OSMP_RETURN_CODE code) {
        return code != VOOSMPType.VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE;
    }

    public static boolean isErrorCode(int code) {
        return code != VOOSMPType.VO_OSMP_RETURN_CODE.VO_OSMP_ERR_NONE.getValue();
    }

    public static boolean isValidUri(String uri) {

        if (uri == null || uri.trim().length() <= 0) {
            return false;
        }

        return true;
    }
}
