package com.xinlan.cubedemo;

public class NativeBridge {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    public static native void init();
    public static native void render();
    public static native void resize(int width , int height);
    public static native void free();

    public static native String stringFromJNI();
}//end class
