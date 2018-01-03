package com.persistentsecurity.safeguardlm;

/**
 *
 * @author mark
 */

public class byteSys {

    public static int byteLen(byte[] BYTE) {
        int pos;
        int ret = 0;

        for (pos = 0; pos < BYTE.length; pos ++) {
            if (BYTE[pos] == 0) {
                ret = pos;
                break;
            }
            ret = pos + 1;
        }
        return(ret);
    }

}
