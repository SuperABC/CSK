package supergp.cskiller;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import supergp.cskiller.Util.GifView;

public class Load extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_load);

        GifView gif = (GifView) findViewById(R.id.loading);
        // 设置背景gif图片资源
        gif.setMovieResource(R.drawable.load);

        gif.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setClass(Load.this, Main.class);
                Load.this.startActivity(intent);
            }
        });
    }
}
