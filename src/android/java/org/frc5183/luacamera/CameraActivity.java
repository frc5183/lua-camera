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

public class CameraActivity {
    private static Activity sitch;
    private static String picture;

    public static void setPicture(String pic) {
        picture = pic;
    }

    public String getPicture() {
        return picture;
    }

    private void activate() {
        sitch = GameActivity.getGameActivity();
        Intent camera_intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        sitch.startActivityForResult(camera_intent, 123);
    }

    public CameraActivity() {
        Log.d("LuaCamera", "Loading CameraActivity");
    }

    public static void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == 123) {
            Bitmap photo = (Bitmap) data.getExtras().get("data");

            if (photo != null) {
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                photo.compress(Bitmap.CompressFormat.PNG, 100, baos);
                picture = Base64.encodeToString(baos.toByteArray(), Base64.DEFAULT);
            }
        }
    }
}
