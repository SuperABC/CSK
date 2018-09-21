package supergp.cskiller;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;

import java.util.Timer;
import java.util.TimerTask;

import supergp.cskiller.Killer.GTX;
import supergp.cskiller.Killer.ZRS;

public class Main extends Activity {
    public static Activity inter;
    public static RelativeLayout layout;

    public static Surface[] card = new Surface[100];
    public static int sel = -1;

    public enum getCard {
        GC_NONE,
        GC_REF,
        GC_REGULAR,
        GC_EXAMLEAK,
        GC_SKILL,
        GC_DOWNLOAD,
        GC_REPLACE
    }
    public enum lostCard {
        LC_NONE,
        LC_USE,
        LC_HACK,
        LC_COPY,
        LC_SKILL,
        LC_WEAKSHOW,
        LC_REGULAR
    }
    public static getCard gcState = getCard.GC_NONE;
    public static lostCard lcState = lostCard.LC_NONE;

    public static Commander[] player = new Commander[8];
    public static int num = 2;
    public Deck newDeck = new Deck();
    public Deck exDeck = new Deck();
    public int state = 0;
    private static boolean inited = false;

    public Deck real = new Deck();
    public static Card action = null;
    public static int pro = -1;
    public static int obj = -1;
    public static int con = -1;
    public static int chk = -1;
    public enum Effect {
        CE_NOEFFECT,
        CE_NODENY,
        CE_DISPOSEONE,
    }
    public Effect kill = Effect.CE_NOEFFECT;
    public Effect review = Effect.CE_NOEFFECT;

    public boolean judge = true, get = true, use = true, dispose = true;
    public int dying = -1;
    public int tmpPlayer = 0;

    void init() {
        player[0] = new ZRS(1, 0);
        player[1] = new GTX(0, 1);

        newDeck.shuffleAll();
        for(int i = 0; i < 8; i++) {
            if(player[i]!=null) {
                for(int j = 0; j < 4; j++) {
                    player[i].getCard(newDeck.pop());
                }
            }
        }
        inited = true;
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        inter = Main.this;
        layout = (RelativeLayout)this.findViewById(R.id.main);

        Timer timer = new Timer();
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                tick();
            }
            void tick() {
                if(!inited)return;
                switch(state) {
                    case 0:
                        player[tmpPlayer].startTurn();
                        state = 1;
                        break;
                    case 1:
                        /*if(Main.gcState == Main.getCard.GC_REF)return;
                        Deck j = new Deck();
                        if(judge)
                            j = player[tmpPlayer].exeJudge();
                        if(j.have(Card.Content.CC_CALLROLL)) {
                            player[tmpPlayer].lessBlood(3);
                        }
                        askSave();
                        if(j.have(Card.Content.CC_REF)) {
                            Main.gcState = Main.getCard.GC_REF;
                            return;
                        }
                        if(j.have(Card.Content.CC_NONET)) {
                            get = false;
                        }
                        if(j.have(Card.Content.CC_NIGHTPLAY)) {
                            use = false;
                        }*/
                        state = 2;
                        break;
                    case 2:
                        if(get == true) {
                            gcState = getCard.GC_REGULAR;
                            return;
                        }
                        else get = true;
                        state = 3;
                        break;
                    case 3:
                        if(use == true) {
                            if(lcState==lostCard.LC_NONE)player[tmpPlayer].useCard();
                            if(lcState==lostCard.LC_NONE)exeAction();
                            if(player[tmpPlayer].endTmp == false)break;
                        }
                        else {
                            use = true;
                            player[tmpPlayer].endTmp = true;
                        }
                        state = 4;
                        break;
                    case 4:
                        if(dispose == true) {
                            if (lcState == lostCard.LC_NONE) {
                                if(!player[tmpPlayer].endUse())
                                    break;
                                else state = 4;
                            }
                        }
                        else state = 5;
                        break;
                    /*case 5:
                        do {
                            tmpPlayer = (tmpPlayer+1)%2;
                        }while(player[tmpPlayer]==null);
                        state = 0;
                        break;*/
                }
            }
            void exeAction() {
                int n, idx;
                if(action == null)return;

                pro = tmpPlayer;
                switch(action.getIdx()) {
                    case CC_PREVENT:
                        break;
                }
            }
        };
        timer.schedule(task, 0, 1);

        Button cancel = (Button)findViewById(R.id.regret);
        cancel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sel = -2;
            }
        });
        Button set = (Button)findViewById(R.id.confirm);
        set.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if(state==2&&gcState==getCard.GC_REGULAR) {
                    player[tmpPlayer].getCard(newDeck.pop());
                    player[tmpPlayer].getCard(newDeck.pop());
                    state=3;
                }

                if(state == 3 || state == 4) {
                    sel = -1;
                    for(int i = 0; card[i]!=null; i++) {
                        if(card[i].selected)sel = i;
                    }
                }

                if(state==3&&lcState== lostCard.LC_USE) {
                    player[tmpPlayer].lostCard(sel);
                    lcState = lostCard.LC_NONE;
                    sel = -1;
                }

                if(state==4&&lcState== lostCard.LC_REGULAR) {
                    player[tmpPlayer].lostCard(sel);
                    lcState = lostCard.LC_NONE;
                    sel = -1;
                }

            }
        });

        init();
    }

    static int calDist(int pro, int obj) {
        int dist = 0;
        int left = pro, right = pro;
        while(left!=obj && right!=obj) {
            while(player[left = (left+num-1)%num]==null);
            while(player[right = (right+1)%num]==null);
            dist++;
        }
        if(player[obj].equipCard.cont.get(3)!=null)dist++;
        if(player[pro].equipCard.cont.get(2)!=null)dist--;
        return dist;
    }
    static int killDist(Card c) {
        if(c==null)return 1;
        switch(c.getIdx()){
            case CC_SCRIPT:
                return 1;
            case CC_XILINX:
                return 2;
            case CC_SPINPEN:
                return 3;
            case CC_PTA:
                return 3;
            case CC_CHICKEN:
                return 4;
            case CC_CLOTHES:
                return 2;
            case CC_LINUX:
                return 2;
            case CC_GUARD:
                return 5;
            default:
                return 1;
        }
    }


}
