package org.frc5183.luacamera;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.provider.MediaStore;
import android.util.Base64;
import android.util.Log;

import org.love2d.android.*;
import java.io.ByteArrayOutputStream;

public class CameraActivity implements GameActivity.Adapter {
    private static int code;
    Activity sitch;
    private static String picture;
    public CameraActivity() {
        super();
        code = GameActivity.registerAdapter(this);
        Log.d("LuaCamera", "Loading CameraActivity");
    }
    public static void setPicture(String pic) {
        picture = pic;
    }

    public String getPicture() {
        return picture;
    }

    private void activate() {
        if (sitch==null) {
            sitch = GameActivity.getGameActivity();
        }
        Intent camera_intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        sitch.startActivityForResult(camera_intent, code);
    }
    public void handle(int resultCode, Intent data) {
        onActivityResult(code, resultCode, data);
    }
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        Bitmap photo = (Bitmap) data.getExtras().get("data");
        if (photo!=null) {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            photo.compress(Bitmap.CompressFormat.PNG, 100, baos);
            byte[] bytes = baos.toByteArray();
            picture = Base64.encodeToString(bytes, Base64.DEFAULT);
        }
    }
}