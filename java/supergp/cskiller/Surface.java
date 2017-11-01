package supergp.cskiller;

import android.content.Context;
import android.util.DisplayMetrics;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;

public class Surface extends RelativeLayout {
    private int cont, num, color;
    ImageView icont, inum, icolor;
    public int idx;
    public boolean selected = false;

    public Surface(Context context, final int idx) {
        super(context);
        LayoutInflater.from(context).inflate(R.layout.element_card, this);

        this.idx = idx;
        icont = (ImageView) findViewById(R.id.cont);
        inum = (ImageView) findViewById(R.id.num);
        icolor = (ImageView) findViewById(R.id.color);

        OnClickListener click = new OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!selected) {
                    icont.setY(icont.getY() - 100);
                    inum.setY(inum.getY() - 100);
                    icolor.setY(icolor.getY() - 100);
                    selected = true;
                }
                else {
                    icont.setY(icont.getY() + 100);
                    inum.setY(inum.getY() + 100);
                    icolor.setY(icolor.getY() + 100);
                    selected = false;
                }
                Toast.makeText(Main.inter, "You clicked " + idx, Toast.LENGTH_SHORT).show();
            }
        };
        icont.setOnClickListener(click);
    }

    public void set(int cont, int num, int color) {
        this.cont = cont;
        this.num = num;
        this.color = color;
        switch(cont) {
            case 0:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.prevent);
                break;
            case 1:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.deny);
                break;
            case 2:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.study);
                break;
            case 3:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.stayup);
                break;
            case 4:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.nonet);
                break;
            case 5:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.weakshow);
                break;
            case 6:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.nightplay);
                break;
            case 7:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.worship);
                break;
            case 8:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.toeat);
                break;
            case 9:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.toreview);
                break;
            case 10:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.copy);
                break;
            case 11:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.callroll);
                break;
            case 12:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.steam);
                break;
            case 13:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.download);
                break;
            case 14:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.hack);
                break;
            case 15:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.examleak);
                break;
            case 16:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.noproblem);
                break;
            case 17:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.reexam);
                break;
            case 18:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.ref);
                break;
            case 19:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.fuck);
                break;
            case 20:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.script);
                break;
            case 21:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.xilinx);
                break;
            case 22:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.spinpen);
                break;
            case 23:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.pta);
                break;
            case 24:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.chicken);
                break;
            case 25:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.clothes);
                break;
            case 26:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.linux);
                break;
            case 27:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.guard);
                break;
            case 28:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.keyboard);
                break;
            case 29:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.gtxv);
                break;
            case 30:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.dbelephant);
                break;
            case 31:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.glasses);
                break;
            case 32:
                break;
            case 33:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.motor);
                break;
            case 34:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.bus);
                break;
            case 35:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.lake);
                break;
            case 36:
                ((ImageView) this.findViewById(R.id.cont)).setImageResource(R.drawable.mountain);
                break;
        }
        switch(num) {
            case 1:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n1);
                break;
            case 2:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n2);
                break;
            case 3:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n3);
                break;
            case 4:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n4);
                break;
            case 5:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n5);
                break;
            case 6:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n6);
                break;
            case 7:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n7);
                break;
            case 8:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n8);
                break;
            case 9:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n9);
                break;
            case 10:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n10);
                break;
            case 11:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n11);
                break;
            case 12:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n12);
                break;
            case 13:
                ((ImageView) this.findViewById(R.id.num)).setImageResource(R.drawable.n13);
                break;
        }
        switch(color) {
            case 0:
                ((ImageView) this.findViewById(R.id.color)).setImageResource(R.drawable.heart);
                break;
            case 1:
                ((ImageView) this.findViewById(R.id.color)).setImageResource(R.drawable.square);
                break;
            case 2:
                ((ImageView) this.findViewById(R.id.color)).setImageResource(R.drawable.spade);
                break;
            case 3:
                ((ImageView) this.findViewById(R.id.color)).setImageResource(R.drawable.club);
                break;
        }
    }
    public void position(int x) {
        MarginLayoutParams margin = new MarginLayoutParams(this.getLayoutParams());
        int left = dppx(x);

        margin.setMargins(left, 0, 0, 0);

        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(margin);
        this.setLayoutParams(layoutParams);
    }
    public int dppx(float dpValue){
        final float scale = Main.inter.getResources().getDisplayMetrics().density;
        return (int)(dpValue*scale+0.5f);
    }
}

