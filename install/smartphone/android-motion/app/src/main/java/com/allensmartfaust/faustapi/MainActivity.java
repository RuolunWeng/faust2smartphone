package com.allensmartfaust.soloDemo;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.graphics.Path;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;


import com.DspFaust.DspFaust;
import com.DspFaustMotion.DspFaustMotion;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

import static android.Manifest.permission.ACCESS_NETWORK_STATE;
import static android.Manifest.permission.INTERNET;
import static android.Manifest.permission.RECORD_AUDIO;

public class MainActivity extends AppCompatActivity {
    DspFaust dspFaust;
    DspFaustMotion dspFaustMotion;

    private SensorManager sensorManager;

    private TextView cue,cueNext,tips;
    private EditText paramsValue, ipAddress, inputPort, outputPort;

    private ImageView touche;
    private Button prevCue, nextCue, initCue, setMotion , defaultParams, setOSC;


    private CheckBox setParams;
    private RadioGroup radioGroup;
    private RadioButton radioButton;


    int scrWidth = 0,scrHeight= 0;


    String[] ParamArray = {"hp","shok_thr","antirebon","lp","tacc_thr",
    "tacc_gain","tacc_up","tacc_down","tgyr_thr",
    "tgyr_gain","tgyr_up","tgyr_down","osfproj"};

    ArrayList<String> cueList = new ArrayList<String>();
    ArrayList<String> tipsList = new ArrayList<String>();


    int cueIndex,cueIndexNext;

    String totalAccelAddress, totalGyroAddress ,sxpAddress, sypAddress, szpAddress, sxnAddress, synAddress, sznAddress, ixpAddress,
            iypAddress, izpAddress, ixnAddress, iynAddress, iznAddress, pixpAddress, piypAddress, pizpAddress, pixnAddress, piynAddress,
           piznAddress, axpnAddress, aypnAddress, azpnAddress, axpAddress, aypAddress, azpAddress, axnAddress, aynAddress, aznAddress,
           gxpnAddress, gypnAddress, gzpnAddress, gxpAddress, gypAddress, gzpAddress, gxnAddress, gynAddress, gznAddress;

    String touchGateAddress;
    String screenXAddress;
    String screenYAddress;
    String magneticHeadingAddress;

    String cueAddress;
    String tipAddress;


    boolean totalAccelIsOn;
    boolean totalGyroIsOn;
    boolean sxpIsOn;
    boolean sypIsOn;
    boolean szpIsOn;
    boolean sxnIsOn;
    boolean synIsOn;
    boolean sznIsOn;
    boolean ixpIsOn;
    boolean iypIsOn;
    boolean izpIsOn;
    boolean ixnIsOn;
    boolean iynIsOn;
    boolean iznIsOn;
    boolean pixpIsOn;
    boolean piypIsOn;
    boolean pizpIsOn;
    boolean pixnIsOn;
    boolean piynIsOn;
    boolean piznIsOn;
    boolean axpnIsOn;
    boolean aypnIsOn;
    boolean azpnIsOn;
    boolean axpIsOn;
    boolean aypIsOn;
    boolean azpIsOn;
    boolean axnIsOn;
    boolean aynIsOn;
    boolean aznIsOn;
    boolean gxpnIsOn;
    boolean gypnIsOn;
    boolean gzpnIsOn;
    boolean gxpIsOn;
    boolean gypIsOn;
    boolean gzpIsOn;
    boolean gxnIsOn;
    boolean gynIsOn;
    boolean gznIsOn;

    boolean touchGateIsOn;
    boolean screenXIsOn;
    boolean screenYIsOn;
    boolean magneticHeadingIsOn;

    boolean cueIsOn;
    boolean tipIsOn;

    boolean hpIsOn;
    boolean shok_thrIsOn;
    boolean antirebonIsOn;
    boolean lpIsOn;
    boolean osfprojIsOn;
    boolean tacc_thrIsOn;
    boolean tacc_gainIsOn;
    boolean tacc_upIsOn;
    boolean tacc_downIsOn;
    boolean tgyr_thrIsOn;
    boolean tgyr_gainIsOn;
    boolean tgyr_upIsOn;
    boolean tgyr_downIsOn;


    public static final int RequestPermissionCode = 1;

    private boolean permissionToRecordAccepted = false;
    private String [] permissions = {Manifest.permission.RECORD_AUDIO,Manifest.permission.INTERNET,Manifest.permission.ACCESS_NETWORK_STATE};

    private void requestPermission() {

        ActivityCompat.requestPermissions(this, permissions,RequestPermissionCode);

    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {

            case RequestPermissionCode:

                if (grantResults.length > 0) {

                    boolean AudioPermission = grantResults[0] == PackageManager.PERMISSION_GRANTED;
                    boolean InternetPermission = grantResults[1] == PackageManager.PERMISSION_GRANTED;
                    boolean NetworkPermission = grantResults[2] == PackageManager.PERMISSION_GRANTED;

                    permissionToRecordAccepted = AudioPermission && InternetPermission && NetworkPermission;
                    if (permissionToRecordAccepted) {

                        Toast.makeText(MainActivity.this, "Permission Granted", Toast.LENGTH_LONG).show();

                        createFaust();
                    }
                    else {
                        Toast.makeText(MainActivity.this,"Permission Denied",Toast.LENGTH_LONG).show();
                        finish();
                    }
                }

                break;
        }
    }


    private void createFaust() {

        int SR = 44100;
        int blockSize = 256;

        if (dspFaustMotion == null) {
            dspFaustMotion = new DspFaustMotion(SR / blockSize, 1);

            // PRINT ALL PARAMETRE ADDRESS
            for (int i = 0; i < dspFaustMotion.getParamsCount(); i++) {
                System.out.println(dspFaustMotion.getParamAddress(i));
            }
        }

        if (dspFaust == null) {

            dspFaust = new DspFaust(SR, blockSize);
            // PRINT ALL PARAMETRE ADDRESS
            for (int i = 0; i < dspFaust.getParamsCount(); i++) {
                System.out.println(dspFaust.getParamAddress(i));
            }
        }



    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getSupportActionBar().hide();
        setContentView(R.layout.activity_main);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        if (Build.VERSION.SDK_INT >= 23) {
            requestPermission();
        } else {
            permissionToRecordAccepted = true;
            createFaust();
        }

        try {
            InputStream stream = getAssets().open("cuenums.txt");

            if (stream != null) {
                // prepare the file for reading
                InputStreamReader input = new InputStreamReader(stream);
                BufferedReader br = new BufferedReader(input);
                String line = null;
                while ((line=br.readLine()) != null)
                {
                    cueList.add(line);
                }
                stream.close();
            }else{
                System.out.println("It's the assests");
            }


        } catch (IOException x) {
            System.err.println(x);
        }

        try {
            InputStream stream = getAssets().open("cuetips.txt");

            if (stream != null) {
                // prepare the file for reading
                InputStreamReader input = new InputStreamReader(stream);
                BufferedReader br = new BufferedReader(input);
                String line = null;
                while ((line=br.readLine()) != null)
                {
                    tipsList.add(line);
                }
                stream.close();
            }else{
                System.out.println("It's the assests");
            }

        } catch (IOException x) {
            System.err.println(x);
        }

        //String[] inpStrArr = tContents.split(";");
        //list.add(tContents);
        System.out.println(cueList);
        System.out.println(tipsList);


        Display display = getWindowManager().getDefaultDisplay();
        DisplayMetrics outMetrics = new DisplayMetrics();
        display.getMetrics(outMetrics);

        scrWidth  = getWindowManager().getDefaultDisplay().getWidth();
        scrHeight = getWindowManager().getDefaultDisplay().getHeight();

        float density  = getResources().getDisplayMetrics().density;
        float dpHeight = outMetrics.heightPixels / density;
        float dpWidth  = outMetrics.widthPixels / density;

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);


        nextCue = (Button) findViewById(R.id.nextCue);
        prevCue = (Button) findViewById(R.id.prevCue);
        initCue = (Button) findViewById(R.id.initCue);
        cue = (TextView) findViewById(R.id.cue);
        cueNext = (TextView) findViewById(R.id.cueNext);
        cueIndex = 0;
        cueIndexNext = 1;
        tips = (TextView) findViewById(R.id.tips);

        cue.setText(cueList.get(cueIndex));
        cueNext.setText(cueList.get(cueIndexNext));
        tips.setText(tipsList.get(cueIndex));


        nextCue.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if (cueIndexNext < cueList.size() -1) {
                    cueIndexNext++;
                    cueNext.setText(cueList.get(cueIndexNext));
                    tips.setText(tipsList.get(cueIndexNext));
                }
            }
        });

        prevCue.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if (cueIndexNext > 0) {
                    cueIndexNext--;
                    cueNext.setText(cueList.get(cueIndexNext));
                    tips.setText(tipsList.get(cueIndexNext));
                }
            }
        });

        initCue.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                    cueIndex = 0;
                    cueIndexNext = 1;
                    cue.setText(cueList.get(cueIndex));
                    cueNext.setText(cueList.get(cueIndexNext));
                    tips.setText(tipsList.get(cueIndex));

            }
        });

        setOSC = (Button) findViewById(R.id.setOSC);
        ipAddress = (EditText) findViewById(R.id.ipAddress);
        inputPort = (EditText) findViewById(R.id.inputPort);
        outputPort = (EditText) findViewById(R.id.outputPort);

        setParams = (CheckBox) findViewById(R.id.SetParams);
        radioGroup=(RadioGroup)findViewById(R.id.radioGroup);
        paramsValue = (EditText) findViewById(R.id.paramValue);
        setMotion = (Button) findViewById(R.id.setMotion);
        defaultParams =(Button) findViewById(R.id.defaultParams);

        setParams.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView,boolean isChecked) {

                    if (isChecked) {

                        radioGroup.setVisibility(View.VISIBLE);
                        paramsValue.setVisibility(View.VISIBLE);
                        setMotion.setVisibility(View.VISIBLE);
                        defaultParams.setVisibility(View.VISIBLE);
                        if (dspFaust.getOSCIsOn()) {
                            ipAddress.setVisibility(View.VISIBLE);
                            inputPort.setVisibility(View.VISIBLE);
                            outputPort.setVisibility(View.VISIBLE);
                            setOSC.setVisibility(View.VISIBLE);
                        }
                    } else {

                        radioGroup.setVisibility(View.INVISIBLE);
                        paramsValue.setVisibility(View.INVISIBLE);
                        setMotion.setVisibility(View.INVISIBLE);
                        defaultParams.setVisibility(View.INVISIBLE);
                        ipAddress.setVisibility(View.INVISIBLE);
                        inputPort.setVisibility(View.INVISIBLE);
                        outputPort.setVisibility(View.INVISIBLE);
                        setOSC.setVisibility(View.INVISIBLE);
                    }
                }
            }
        );

        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener()
        {
            public void onCheckedChanged(RadioGroup group, int checkedId)
            {
                // This will get the radiobutton that has changed in its check state
                RadioButton checkedRadioButton = (RadioButton)group.findViewById(checkedId);
                // This puts the value (true/false) into the variable
                boolean isChecked = checkedRadioButton.isChecked();
                // If the radiobutton that has changed in check state is now checked...
                if (isChecked)
                {

                    if ("lp".equals(checkedRadioButton.getText().toString())) {
                    lpIsOn = true;
                    hpIsOn = false;
                    shok_thrIsOn= false;
                    antirebonIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/lp")) );
                    } else if ("shok_thr".equals(checkedRadioButton.getText().toString())) {
                    lpIsOn = false;
                    hpIsOn = false;
                    shok_thrIsOn= true;
                    antirebonIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/shok_thr")));
                } else if ("hp".equals(checkedRadioButton.getText().toString())) {
                    hpIsOn = true;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    antirebonIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/hp")));
                } else if ("antirebon".equals(checkedRadioButton.getText().toString())) {
                    antirebonIsOn = true;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/antirebon")));
                } else if ("tacc_thr".equals(checkedRadioButton.getText().toString())) {
                    tacc_thrIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/tacc_thr")));
                } else if ("tacc_gain".equals(checkedRadioButton.getText().toString())) {
                    tacc_gainIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/tacc_gain")));
                } else if ("tacc_up".equals(checkedRadioButton.getText().toString())) {
                    tacc_upIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/tacc_up")));
                } else if ("tacc_down".equals(checkedRadioButton.getText().toString())) {
                    tacc_downIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/tacc_down")));
                } else if ("tgyr_thr".equals(checkedRadioButton.getText().toString())) {
                    tgyr_thrIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/tgyr_thr")));
                } else if ("tgyr_gain".equals(checkedRadioButton.getText().toString())) {
                    tgyr_gainIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/tgyr_gain")));
                } else if ("tgyr_up".equals(checkedRadioButton.getText().toString())) {
                    tgyr_upIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/tgyr_up")));
                } else if ("tgyr_down".equals(checkedRadioButton.getText().toString())) {
                    tgyr_downIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    osfprojIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/tgyr_down")));
                } else if ("osfproj".equals(checkedRadioButton.getText().toString())) {
                    osfprojIsOn = true;
                    antirebonIsOn = false;
                    hpIsOn = false;
                    lpIsOn = false;
                    shok_thrIsOn= false;
                    tacc_thrIsOn= false;
                    tacc_gainIsOn= false;
                    tacc_upIsOn= false;
                    tacc_downIsOn= false;
                    tgyr_thrIsOn= false;
                    tgyr_gainIsOn= false;
                    tgyr_upIsOn= false;
                    tgyr_downIsOn= false;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue("/Motion/osfproj")));
                }



                }
            }
        });


        setMotion.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                if (lpIsOn) {
                    dspFaustMotion.setParamValue("/Motion/lp", Float.valueOf(paramsValue.getText().toString()));
                }else if (hpIsOn) {
                    dspFaustMotion.setParamValue("/Motion/hp", Float.valueOf(paramsValue.getText().toString()));
                }else if (shok_thrIsOn) {
                    dspFaustMotion.setParamValue("/Motion/shok_thr", Float.valueOf(paramsValue.getText().toString()));
                }else if (antirebonIsOn) {
                    dspFaustMotion.setParamValue("/Motion/antirebon", Float.valueOf(paramsValue.getText().toString()));
                }else if (tacc_thrIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tacc_thr", Float.valueOf(paramsValue.getText().toString()));
                }else if (tacc_gainIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tacc_gain", Float.valueOf(paramsValue.getText().toString()));
                }else if (tacc_upIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tacc_up", Float.valueOf(paramsValue.getText().toString()));
                }else if (tacc_downIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tacc_down", Float.valueOf(paramsValue.getText().toString()));
                }else if (tgyr_thrIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tgyr_thr", Float.valueOf(paramsValue.getText().toString()));
                }else if (tgyr_gainIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tgyr_gain", Float.valueOf(paramsValue.getText().toString()));
                }else if (tgyr_upIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tgyr_up", Float.valueOf(paramsValue.getText().toString()));
                }else if (tgyr_downIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tgyr_down", Float.valueOf(paramsValue.getText().toString()));
                }else if (osfprojIsOn) {
                    dspFaustMotion.setParamValue("/Motion/osfproj", Float.valueOf(paramsValue.getText().toString()));

                }


            }
        });



        defaultParams.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                for (int i=0; i<dspFaustMotion.getParamsCount(); i++) {
                    dspFaustMotion.setParamValue(i, dspFaustMotion.getParamInit(i));
                }

                checkAddress();

            }
        });


        setOSC.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                dspFaust.setOSCValue(ipAddress.getText().toString(),inputPort.getText().toString(),outputPort.getText().toString());

            }
        });


    }


    public void checkAddress() {

        // PRINT ALL PARAMETRE ADDRESS
        for(int i=0; i < dspFaust.getParamsCount(); i++){
            System.out.println(dspFaust.getParamAddress(i));

            String Str = dspFaust.getParamAddress(i);

            if (Str.endsWith("/totalaccel")) {
                totalAccelIsOn = true;
                totalAccelAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/totalaccelOn", 1);
            } else if (Str.endsWith("/totalgyro")) {
                totalGyroIsOn = true;
                totalGyroAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/totalgyroOn", 1);
            } else if (Str.endsWith("/sxp")) {
                sxpIsOn = true;
                sxpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/sxpOn", 1);
            } else if (Str.endsWith("/syp")) {
                sypIsOn = true;
                sypAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/sypOn", 1);
            } else if (Str.endsWith("/szp")) {
                szpIsOn = true;
                szpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/szpOn", 1);
            } else if (Str.endsWith("/sxn")) {
                sxnIsOn = true;
                sxnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/sxnOn", 1);
            } else if (Str.endsWith("/syn")) {
                synIsOn = true;
                synAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/synOn", 1);
            } else if (Str.endsWith("/szn")) {
                sznIsOn = true;
                sznAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/sznOn", 1);
            } else if (Str.endsWith("/ixp")) {
                ixpIsOn = true;
                ixpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/ixpOn", 1);
            } else if (Str.endsWith("/iyp")) {
                iypIsOn = true;
                iypAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/iypOn", 1);
            } else if (Str.endsWith("/izp")) {
                izpIsOn = true;
                izpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/izpOn", 1);
            } else if (Str.endsWith("/ixn")) {
                ixnIsOn = true;
                ixnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/ixnOn", 1);
            } else if (Str.endsWith("/iyn")) {
                iynIsOn = true;
                iynAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/iynOn", 1);
            } else if (Str.endsWith("/izn")) {
                iznIsOn = true;
                iznAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/iznOn", 1);
            } else if (Str.endsWith("/pixp")) {
                pixpIsOn = true;
                pixpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/pixpOn", 1);
            } else if (Str.endsWith("/piyp")) {
                piypIsOn = true;
                piypAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/piypOn", 1);
            } else if (Str.endsWith("/pizp")) {
                pizpIsOn = true;
                pizpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/pizpOn", 1);
            } else if (Str.endsWith("/pixn")) {
                pixnIsOn = true;
                pixnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/pixnOn", 1);
            } else if (Str.endsWith("/piyn")) {
                piynIsOn = true;
                piynAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/piynOn", 1);
            } else if (Str.endsWith("/pizn")) {
                piznIsOn = true;
                piznAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/piznOn", 1);
            } else if (Str.endsWith("/axpn")) {
                axpnIsOn = true;
                axpnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/axpnOn", 1);
            } else if (Str.endsWith("/aypn")) {
                aypnIsOn = true;
                aypnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/aypnOn", 1);
            } else if (Str.endsWith("/azpn")) {
                azpnIsOn = true;
                azpnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/azpnOn", 1);
            } else if (Str.endsWith("/axp")) {
                axpIsOn = true;
                axpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/axpOn", 1);
            } else if (Str.endsWith("/ayp")) {
                aypIsOn = true;
                aypAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/aypOn", 1);
            } else if (Str.endsWith("/azp")) {
                azpIsOn = true;
                azpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/azpOn", 1);
            } else if (Str.endsWith("/axn")) {
                axnIsOn = true;
                axnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/axnOn", 1);
            } else if (Str.endsWith("/ayn")) {
                aynIsOn = true;
                aynAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/aynOn", 1);
            } else if (Str.endsWith("/azn")) {
                aznIsOn = true;
                aznAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/aznOn", 1);
            } else if (Str.endsWith("/gxpn")) {
                gxpnIsOn = true;
                gxpnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gxpnOn", 1);
            } else if (Str.endsWith("/gypn")) {
                gypnIsOn = true;
                gypnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gypnOn", 1);
            } else if (Str.endsWith("/gzpn")) {
                gzpnIsOn = true;
                gzpnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gzpnOn", 1);
            } else if (Str.endsWith("/gxp")) {
                gxpIsOn = true;
                gxpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gxpOn", 1);
            } else if (Str.endsWith("/gyp")) {
                gypIsOn = true;
                gypAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gypOn", 1);
            } else if (Str.endsWith("/gzp")) {
                gzpIsOn = true;
                gzpAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gzpOn", 1);
            } else if (Str.endsWith("/gxn")) {
                gxnIsOn = true;
                gxnAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gxnOn", 1);
            } else if (Str.endsWith("/gyn")) {
                gynIsOn = true;
                gynAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gynOn", 1);
            } else if (Str.endsWith("/gzn")) {
                gznIsOn = true;
                gznAddress = dspFaust.getParamAddress(i);
                dspFaustMotion.setParamValue("/Motion/gznOn", 1);
            } else if (Str.endsWith("/touchgate")) {
                touchGateIsOn = true;
                touchGateAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/screenx")) {
                screenXIsOn = true;
                screenXAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/screeny")) {
                screenYIsOn = true;
                screenYAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/compass")) {
                magneticHeadingIsOn = true;
                magneticHeadingAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/cue")) {
                cueIsOn = true;
                cueAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/tip")) {
                tipIsOn = true;
                //[self startUpdateGUI];
                tipAddress = dspFaust.getParamAddress(i);
            }

        }

    }


    @Override

    public boolean onTouchEvent(MotionEvent event) {
        int action = event.getAction() & MotionEvent.ACTION_MASK;
        int touchCounter = event.getPointerCount();
        touche = (ImageView) findViewById(R.id.touche);


        switch(action) {

            case MotionEvent.ACTION_DOWN: {


                if (touchCounter == 1) {
                    float pointerIndex = event.getX(0);
                    float pointerIndey = event.getY(0);
                    if (pointerIndey <= scrHeight / 2) {

                        if (touchGateIsOn) {
                            touche.setVisibility(View.VISIBLE);
                            dspFaust.setParamValue(touchGateAddress, 1);

                            cueIndex = cueIndexNext;
                            cue.setText(cueList.get(cueIndex));
                            tips.setText(tipsList.get(cueIndexNext));

                            if (cueIsOn) {
                             dspFaust.setParamValue(cueAddress,Float.valueOf(cueList.get(cueIndex)));
                            }

                            if (cueIndexNext < cueList.size() - 1) {
                                cueIndexNext++;
                                cueNext.setText(cueList.get(cueIndexNext));
                            }
                        }

                        if (screenXIsOn) {
                            dspFaust.setParamValue(screenXAddress, pointerIndex/scrWidth);
                        }
                        if (screenYIsOn) {
                            dspFaust.setParamValue(screenYAddress, pointerIndey/scrHeight/2.0f);
                        }

                    }
                }

                break;
            }

            case MotionEvent.ACTION_MOVE: {

                if (touchCounter == 1) {
                    float pointerIndex = event.getX(0);
                    float pointerIndey = event.getY(0);

                    if (pointerIndey <= scrHeight / 2) {

                        if (screenXIsOn) {
                            dspFaust.setParamValue(screenXAddress, pointerIndex/scrWidth);
                        }
                        if (screenYIsOn) {
                            dspFaust.setParamValue(screenYAddress, pointerIndey/scrHeight / 2.0f);
                        }

                    }
                }

                break;
            }

            case MotionEvent.ACTION_POINTER_DOWN: {



                break;
            }

            case MotionEvent.ACTION_POINTER_UP: {



                break;
            }

            case MotionEvent.ACTION_UP: {

                if (touchCounter == 1) {

                    float pointerIndex = event.getX(0);
                    float pointerIndey = event.getY(0);
                    if (pointerIndey <= scrHeight / 2) {
                        if (touchGateIsOn) {
                            touche.setVisibility(View.INVISIBLE);
                            dspFaust.setParamValue(touchGateAddress, 0);
                        }

                        if (screenXIsOn) {
                            dspFaust.setParamValue(screenXAddress, pointerIndex/scrWidth);
                        }
                        if (screenYIsOn) {
                            dspFaust.setParamValue(screenYAddress, pointerIndey/scrHeight/2.0f);
                        }
                    }
                }

                    break;

            }
        }
        return true;
    }


    private final SensorEventListener mSensorListener = new SensorEventListener() {

        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }


        public void onSensorChanged(SensorEvent event) {


            if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                // Update mapping at sensor rate
                dspFaust.propagateAcc(0, event.values[0]*(-1));
                dspFaust.propagateAcc(1, event.values[1]*(-1));
                dspFaust.propagateAcc(2, event.values[2]);
    
                dspFaustMotion.propagateAcc(0, event.values[0]*(-1));
                dspFaustMotion.propagateAcc(1, event.values[1]*(-1));
                dspFaustMotion.propagateAcc(2, event.values[2]);
                }

            if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
                // Update mapping at sensor rate
                dspFaust.propagateGyr(0, event.values[0]*(-1));
                dspFaust.propagateGyr(1, event.values[1]*(-1));
                dspFaust.propagateGyr(2, event.values[2]);

                dspFaustMotion.propagateGyr(0, event.values[0]*(-1));
                dspFaustMotion.propagateGyr(1, event.values[1]*(-1));
                dspFaustMotion.propagateGyr(2, event.values[2]);
                }


            dspFaustMotion.render();

            if (totalAccelIsOn) {
                dspFaust.setParamValue(totalAccelAddress, dspFaustMotion.getParamValue("/Motion/Mtotalaccel"));
            }
            if (totalGyroIsOn) {
                dspFaust.setParamValue(totalGyroAddress, dspFaustMotion.getParamValue("/Motion/Mtotalgyro"));
            }
            if (sxpIsOn) {
                dspFaust.setParamValue(sxpAddress, dspFaustMotion.getParamValue("/Motion/Msxp"));
            }
            if (sypIsOn) {
                dspFaust.setParamValue(sypAddress, dspFaustMotion.getParamValue("/Motion/Msyp"));
            }
            if (szpIsOn) {
                dspFaust.setParamValue(szpAddress, dspFaustMotion.getParamValue("/Motion/Mszp"));
            }
            if (sxnIsOn) {
                dspFaust.setParamValue(sxnAddress, dspFaustMotion.getParamValue("/Motion/Msxn"));
            }
            if (synIsOn) {
                dspFaust.setParamValue(synAddress, dspFaustMotion.getParamValue("/Motion/Msyn"));
            }
            if (sznIsOn) {
                dspFaust.setParamValue(sznAddress, dspFaustMotion.getParamValue("/Motion/Mszn"));
            }
            if (ixpIsOn) {
                dspFaust.setParamValue(ixpAddress, dspFaustMotion.getParamValue("/Motion/Mixp"));
            }
            if (iypIsOn) {
                dspFaust.setParamValue(iypAddress, dspFaustMotion.getParamValue("/Motion/Miyp"));
            }
            if (izpIsOn) {
                dspFaust.setParamValue(izpAddress, dspFaustMotion.getParamValue("/Motion/Mizp"));
            }
            if (ixnIsOn) {
                dspFaust.setParamValue(ixnAddress, dspFaustMotion.getParamValue("/Motion/Mixn"));
            }
            if (iynIsOn) {
                dspFaust.setParamValue(iynAddress, dspFaustMotion.getParamValue("/Motion/Miyn"));
            }
            if (iznIsOn) {
                dspFaust.setParamValue(iznAddress, dspFaustMotion.getParamValue("/Motion/Mizn"));
            }
            if (pixpIsOn) {
                dspFaust.setParamValue(pixpAddress, dspFaustMotion.getParamValue("/Motion/Mpixp"));
            }
            if (piypIsOn) {
                dspFaust.setParamValue(piypAddress, dspFaustMotion.getParamValue("/Motion/Mpiyp"));
            }
            if (pizpIsOn) {
                dspFaust.setParamValue(pizpAddress, dspFaustMotion.getParamValue("/Motion/Mpizp"));
            }
            if (pixnIsOn) {
                dspFaust.setParamValue(pixnAddress, dspFaustMotion.getParamValue("/Motion/Mpixn"));
            }
            if (piynIsOn) {
                dspFaust.setParamValue(piynAddress, dspFaustMotion.getParamValue("/Motion/Mpiyn"));
            }
            if (piznIsOn) {
                dspFaust.setParamValue(piznAddress, dspFaustMotion.getParamValue("/Motion/Mpizn"));
            }
            if (axpnIsOn) {
                dspFaust.setParamValue(axpnAddress, dspFaustMotion.getParamValue("/Motion/Maxpn"));
            }
            if (aypnIsOn) {
                dspFaust.setParamValue(aypnAddress, dspFaustMotion.getParamValue("/Motion/Maypn"));
            }
            if (azpnIsOn) {
                dspFaust.setParamValue(azpnAddress, dspFaustMotion.getParamValue("/Motion/Mazpn"));
            }
            if (axpIsOn) {
                dspFaust.setParamValue(axpAddress, dspFaustMotion.getParamValue("/Motion/Maxp"));
            }
            if (aypIsOn) {
                dspFaust.setParamValue(aypAddress, dspFaustMotion.getParamValue("/Motion/Mayp"));
            }
            if (azpIsOn) {
                dspFaust.setParamValue(azpAddress, dspFaustMotion.getParamValue("/Motion/Mazp"));
            }
            if (axnIsOn) {
                dspFaust.setParamValue(axnAddress, dspFaustMotion.getParamValue("/Motion/Maxn"));
            }
            if (aynIsOn) {
                dspFaust.setParamValue(aynAddress, dspFaustMotion.getParamValue("/Motion/Mayn"));
            }
            if (aznIsOn) {
                dspFaust.setParamValue(aznAddress, dspFaustMotion.getParamValue("/Motion/Mazn"));
            }
            if (gxpnIsOn) {
                dspFaust.setParamValue(gxpnAddress, dspFaustMotion.getParamValue("/Motion/Mgxpn"));
            }
            if (gypnIsOn) {
                dspFaust.setParamValue(gypnAddress, dspFaustMotion.getParamValue("/Motion/Mgypn"));
            }
            if (gzpnIsOn) {
                dspFaust.setParamValue(gzpnAddress, dspFaustMotion.getParamValue("/Motion/Mgzpn"));
            }
            if (gxpIsOn) {
                dspFaust.setParamValue(gxpAddress, dspFaustMotion.getParamValue("/Motion/Mgxp"));
            }
            if (gypIsOn) {
                dspFaust.setParamValue(gypAddress, dspFaustMotion.getParamValue("/Motion/Mgyp"));
            }
            if (gzpIsOn) {
                dspFaust.setParamValue(gzpAddress, dspFaustMotion.getParamValue("/Motion/Mgzp"));
            }
            if (gypIsOn) {
                dspFaust.setParamValue(gypAddress, dspFaustMotion.getParamValue("/Motion/Mgyp"));
            }
            if (gxnIsOn) {
                dspFaust.setParamValue(gxnAddress, dspFaustMotion.getParamValue("/Motion/Mgxn"));
            }
            if (gynIsOn) {
                dspFaust.setParamValue(gynAddress, dspFaustMotion.getParamValue("/Motion/Mgyn"));
            }
            if (gznIsOn) {
                dspFaust.setParamValue(gznAddress, dspFaustMotion.getParamValue("/Motion/Mgzn"));
            }
    }



    };

    @Override
    protected void onPause() {
        Log.d("Faust", "onPause");
        super.onPause();
        if(permissionToRecordAccepted) {
            dspFaust.stop();
            dspFaustMotion.stop();
            if (sensorManager!=null) {
                sensorManager.unregisterListener(mSensorListener);
            }
        }

    }

    @Override
    protected void onResume() {
        Log.d("Faust", "onResume");
        super.onResume();
        if(permissionToRecordAccepted) {

            if (!dspFaust.isRunning()) {

                dspFaust.start();

                checkAddress();

                sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                        Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);

                sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                        Sensor.TYPE_GYROSCOPE), SensorManager.SENSOR_DELAY_FASTEST);
            }

            if (!dspFaustMotion.isRunning()) {

                dspFaustMotion.start();
            }


        }
    }

    @Override
    public void onDestroy() {
        Log.d("Faust", "onDestroy");

        super.onDestroy();

        if (sensorManager!=null){sensorManager.unregisterListener(mSensorListener);}
        dspFaust = null;
        dspFaustMotion = null;
    }
}

