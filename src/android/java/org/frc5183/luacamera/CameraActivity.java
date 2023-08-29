package org.frc5183.luacamera;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.provider.MediaStore;
import android.util.Base64;

import java.io.ByteArrayOutputStream;

public class CameraActivity extends Activity {
    private String picture;
    private String getPicture() {
        return picture;
    }
    private void activate() {
        Intent camera_intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        startActivityForResult(camera_intent, 123);
    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == 123) {
            Bitmap photo = (Bitmap) data.getExtras().get("data");

            if (photo!=null) {
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                photo.compress(Bitmap.CompressFormat.PNG, 100, baos);
                byte[] bytes = baos.toByteArray();
                picture = Base64.encodeToString(bytes, Base64.DEFAULT);
            }
        }
    }
}