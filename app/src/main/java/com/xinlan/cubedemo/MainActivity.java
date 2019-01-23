package com.xinlan.cubedemo;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity {
    private MySurface mGlView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGlView = new MySurface(this);
        setContentView(mGlView);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mGlView != null) {
            mGlView.onFree();
        }
    }

    private final class MySurface extends GLSurfaceView implements GLSurfaceView.Renderer {
        public MySurface(Context context) {
            super(context);

            setEGLContextClientVersion(3);
            setEGLConfigChooser(8, 8, 8, 8, 16, 0);

            setRenderer(this);
            setRenderMode(RENDERMODE_CONTINUOUSLY);
        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            NativeBridge.init();
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            NativeBridge.resize(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            NativeBridge.render();
        }

        public void onFree() {
            NativeBridge.free();
        }
    }//end inner class

}
