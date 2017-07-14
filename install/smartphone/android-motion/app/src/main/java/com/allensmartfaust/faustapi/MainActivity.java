package com.allensmartfaust.faustapi;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
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
import com.DspFaust.DspFaustMotion;

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
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    DspFaust dspFaust;
    DspFaustMotion dspFaustMotion;
    
    private SensorManager sensorManager;

    private SharedPreferences mSharedPref;
    
    private TextView cue,cueNext,cueText, cueNextText,tips;
    private EditText paramsValue, ipAddress, inputPort, outputPort;
    
    private ImageView touche;
    private Button prevCue, nextCue, initCue, setMotion , defaultParams, setOSC, setRef;
    
    
    private CheckBox setParams;
    private RadioGroup radioGroup;
    
    int scrWidth = 0,scrHeight= 0;

    long lastDate=0;
    
    
    String[] ParamArray = {"hp","shok_thr","antirebon","lp","tacc_thr",
    "tacc_gain","tacc_up","tacc_down","tgyr_thr",
    "tgyr_gain","tgyr_up","tgyr_down","osfproj"};

    float hpValue, shok_thrValue, antirebonValue, lpValue, osfprojValue, tacc_thrValue, tacc_gainValue,
     tacc_upValue, tacc_downValue, tgyr_thrValue, tgyr_gainValue, tgyr_upValue, tgyr_downValue;
    
    ArrayList<String> cueList = new ArrayList<String>();
    ArrayList<String> tipsList = new ArrayList<String>();
    
    
    int cueIndex,cueIndexNext;
    
    float[] rotationMatrix = new float[9];
    float[] adjustedRotationMatrix = new float[9];
    float[][] matrixA = new float[3][3];
    float[][] matrixB = new float[3][3];
    float[][] matrixC = new float[3][3];
    
    String totalAccelAddress, totalGyroAddress ,sxpAddress, sypAddress, szpAddress, sxnAddress, synAddress, sznAddress, ixpAddress,
    iypAddress, izpAddress, ixnAddress, iynAddress, iznAddress, pixpAddress, piypAddress, pizpAddress, pixnAddress, piynAddress,
    piznAddress, axpnAddress, aypnAddress, azpnAddress, axpAddress, aypAddress, azpAddress, axnAddress, aynAddress, aznAddress,
    gxpnAddress, gypnAddress, gzpnAddress, gxpAddress, gypAddress, gzpAddress, gxnAddress, gynAddress, gznAddress, brasGcourAddress,
    brasGrearAddress, brasGjardinAddress, brasGfrontAddress, brasGdownAddress, brasGupAddress, piedscourAddress, piedsrearAddress,
    piedsjardinAddress, piedsfrontAddress, piedsdownAddress, piedsupAddress, doscourAddress, dosrearAddress, dosjardinAddress,
    dosfrontAddress, dosdownAddress, dosupAddress, brasDcourAddress, brasDrearAddress, brasDjardinAddress, brasDfrontAddress,
    brasDdownAddress, brasDupAddress, tetecourAddress, teterearAddress, tetejardinAddress, tetefrontAddress, tetedownAddress,
    teteupAddress, ventrecourAddress, ventrerearAddress, ventrejardinAddress, ventrefrontAddress, ventredownAddress, ventreupAddress;

    String oscAddress;
    int oscInPort;
    int oscOutPort;
    
    String touchGateAddress;
    String screenXAddress;
    String screenYAddress;
    String magneticHeadingAddress;
    
    String cueAddress;
    String tipAddress;
    
    
    boolean totalAccelIsOn, totalGyroIsOn, sxpIsOn, sypIsOn, szpIsOn, sxnIsOn, synIsOn, sznIsOn, ixpIsOn, iypIsOn, izpIsOn, ixnIsOn,
    iynIsOn, iznIsOn, pixpIsOn, piypIsOn, pizpIsOn, pixnIsOn, piynIsOn, piznIsOn, axpnIsOn, aypnIsOn, azpnIsOn, axpIsOn,
    aypIsOn, azpIsOn, axnIsOn, aynIsOn, aznIsOn, gxpnIsOn, gypnIsOn, gzpnIsOn, gxpIsOn, gypIsOn, gzpIsOn, gxnIsOn, gynIsOn,
    gznIsOn, brasGcourIsOn, brasGrearIsOn, brasGjardinIsOn, brasGfrontIsOn, brasGdownIsOn, brasGupIsOn, piedscourIsOn,
    piedsrearIsOn, piedsjardinIsOn, piedsfrontIsOn, piedsdownIsOn, piedsupIsOn, doscourIsOn, dosrearIsOn, dosjardinIsOn,
    dosfrontIsOn, dosdownIsOn, dosupIsOn, brasDcourIsOn, brasDrearIsOn, brasDjardinIsOn, brasDfrontIsOn, brasDdownIsOn,
    brasDupIsOn, tetecourIsOn, teterearIsOn, tetejardinIsOn, tetefrontIsOn, tetedownIsOn, teteupIsOn, ventrecourIsOn,
    ventrerearIsOn, ventrejardinIsOn, ventrefrontIsOn, ventredownIsOn, ventreupIsOn;
    
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
                        
                        //Toast.makeText(MainActivity.this, "Permission Granted", Toast.LENGTH_LONG).show();
                        
                        createFaust();
                    }
                    else {
                        //Toast.makeText(MainActivity.this,"Permission Denied",Toast.LENGTH_LONG).show();
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

            //long a = DspFaustMotion.getCPtr(dspFaustMotion);
            //dspFaustMotionSWIG = SWIGTYPE_p_DspFaustMotion(a,false);

            dspFaust = new DspFaust(dspFaustMotion,SR, blockSize);
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
        
        if (sensorManager == null) {
            sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        }
        
        nextCue = (Button) findViewById(R.id.nextCue);
        prevCue = (Button) findViewById(R.id.prevCue);
        initCue = (Button) findViewById(R.id.initCue);
        cue = (TextView) findViewById(R.id.cue);
        cueNext = (TextView) findViewById(R.id.cueNext);
        cueText = (TextView) findViewById(R.id.cueText);
        cueNextText = (TextView) findViewById(R.id.cueNextText);
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
        
        setRef =(Button) findViewById(R.id.setRef);

        
        setParams.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            
            @Override
            public void onCheckedChanged(CompoundButton buttonView,boolean isChecked) {
                
                if (isChecked) {
                    
                    radioGroup.setVisibility(View.VISIBLE);
                    paramsValue.setVisibility(View.VISIBLE);
                    setMotion.setVisibility(View.VISIBLE);
                    defaultParams.setVisibility(View.VISIBLE);
                    setRef.setVisibility(View.VISIBLE);
                    if (dspFaust.getOSCIsOn()) {
                        ipAddress.setVisibility(View.VISIBLE);
                        ipAddress.setText(SharedPrefRead("oscAddress","192.168.1.5"));
                        inputPort.setVisibility(View.VISIBLE);
                        inputPort.setText(SharedPrefRead("oscInPort","5510"));
                        outputPort.setVisibility(View.VISIBLE);
                        outputPort.setText(SharedPrefRead("oscOutPort","5511"));
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
                    setRef.setVisibility(View.INVISIBLE);
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
                    SharedPreWriteFloat("/Motion/lp",Float.valueOf(paramsValue.getText().toString()));
                }else if (hpIsOn) {
                    dspFaustMotion.setParamValue("/Motion/hp", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/hp",Float.valueOf(paramsValue.getText().toString()));
                }else if (shok_thrIsOn) {
                    dspFaustMotion.setParamValue("/Motion/shok_thr", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/shok_thr",Float.valueOf(paramsValue.getText().toString()));
                }else if (antirebonIsOn) {
                    dspFaustMotion.setParamValue("/Motion/antirebon", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/antirebon",Float.valueOf(paramsValue.getText().toString()));
                }else if (tacc_thrIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tacc_thr", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/tacc_thr",Float.valueOf(paramsValue.getText().toString()));
                }else if (tacc_gainIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tacc_gain", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/tacc_gain",Float.valueOf(paramsValue.getText().toString()));
                }else if (tacc_upIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tacc_up", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/tacc_up",Float.valueOf(paramsValue.getText().toString()));
                }else if (tacc_downIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tacc_down", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/tacc_down",Float.valueOf(paramsValue.getText().toString()));
                }else if (tgyr_thrIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tgyr_thr", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/tgyr_thr",Float.valueOf(paramsValue.getText().toString()));
                }else if (tgyr_gainIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tgyr_gain", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/tgyr_gain",Float.valueOf(paramsValue.getText().toString()));
                }else if (tgyr_upIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tgyr_up", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/tgyr_up",Float.valueOf(paramsValue.getText().toString()));
                }else if (tgyr_downIsOn) {
                    dspFaustMotion.setParamValue("/Motion/tgyr_down", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/tgyr_down",Float.valueOf(paramsValue.getText().toString()));
                }else if (osfprojIsOn) {
                    dspFaustMotion.setParamValue("/Motion/osfproj", Float.valueOf(paramsValue.getText().toString()));
                    SharedPreWriteFloat("/Motion/osfproj",Float.valueOf(paramsValue.getText().toString()));
                    
                }
                
                
            }
        });
        
        
        
        defaultParams.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                
                for (int i=0; i<dspFaustMotion.getParamsCount(); i++) {
                    dspFaustMotion.setParamValue(i, dspFaustMotion.getParamInit(i));
                }

                paramsValue.setText("Done");
                Toast.makeText(MainActivity.this, "Reset Defaults(restart to use new OSC)", Toast.LENGTH_LONG).show();
                checkAddress();
                dspFaust.checkAdress();

                resetParams();
                
            }
        });
        
        
        setOSC.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                dspFaust.setOSCValue(ipAddress.getText().toString(),
                        Integer.parseInt(inputPort.getText().toString()),
                        Integer.parseInt(outputPort.getText().toString()));
                SharedPrefWriteString("oscAddress",ipAddress.getText().toString());
                SharedPrefWriteString("oscInPort",inputPort.getText().toString());
                SharedPrefWriteString("oscOutPort",outputPort.getText().toString());

                Toast.makeText(MainActivity.this, "Restart to use new OSC", Toast.LENGTH_LONG).show();

            }
        });
        
        setRef.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                initFrame();
                Toast.makeText(MainActivity.this, "Reset Frame", Toast.LENGTH_LONG).show();
            }
        });
        
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                initFrame();
            }
        }, 2000);
        
    }
    
    
    public void checkAddress() {
        
        if (dspFaust != null) {
            // PRINT ALL PARAMETRE ADDRESS
            for (int i = 0; i < dspFaust.getParamsCount(); i++) {
                System.out.println(dspFaust.getParamAddress(i));
                
                String Str = dspFaust.getParamAddress(i);
                
                if (Str.endsWith("/touchgate")) {
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
                    tipAddress = dspFaust.getParamAddress(i);
                }
                
            }
        }
        
        
        if(cueIsOn) {
            nextCue.setVisibility(View.VISIBLE);
            prevCue.setVisibility(View.VISIBLE);
            initCue.setVisibility(View.VISIBLE);
            cue.setVisibility(View.VISIBLE);
            cueNext.setVisibility(View.VISIBLE);
            cueText.setVisibility(View.VISIBLE);
            cueNextText.setVisibility(View.VISIBLE);
            tips.setVisibility(View.VISIBLE);
        } else {
            nextCue.setVisibility(View.INVISIBLE);
            prevCue.setVisibility(View.INVISIBLE);
            initCue.setVisibility(View.INVISIBLE);
            cue.setVisibility(View.INVISIBLE);
            cueNext.setVisibility(View.INVISIBLE);
            cueText.setVisibility(View.INVISIBLE);
            cueNextText.setVisibility(View.INVISIBLE);
            tips.setVisibility(View.INVISIBLE);
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
                        if (cueIsOn) {
                            
                            if (touchGateIsOn) {
                                touche.setVisibility(View.VISIBLE);
                                dspFaust.setParamValue(touchGateAddress, 1);
                                
                                cueIndex = cueIndexNext;
                                cue.setText(cueList.get(cueIndex));
                                tips.setText(tipsList.get(cueIndexNext));
                                
                                dspFaust.setParamValue(cueAddress,Float.valueOf(cueList.get(cueIndex)));
                                
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
                }
                
                break;
            }
                
            case MotionEvent.ACTION_MOVE: {
                
                if (touchCounter == 1) {
                    float pointerIndex = event.getX(0);
                    float pointerIndey = event.getY(0);
                    
                    if (pointerIndey <= scrHeight / 2) {
                        if (cueIsOn) {
                            if (screenXIsOn) {
                                dspFaust.setParamValue(screenXAddress, pointerIndex / scrWidth);
                            }
                            if (screenYIsOn) {
                                dspFaust.setParamValue(screenYAddress, pointerIndey / scrHeight / 2.0f);
                            }
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
                        if (cueIsOn) {
                            if (touchGateIsOn) {
                                touche.setVisibility(View.INVISIBLE);
                                dspFaust.setParamValue(touchGateAddress, 0);
                            }
                            
                            if (screenXIsOn) {
                                dspFaust.setParamValue(screenXAddress, pointerIndex / scrWidth);
                            }
                            if (screenYIsOn) {
                                dspFaust.setParamValue(screenYAddress, pointerIndey / scrHeight / 2.0f);
                            }
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

            long currentTime= System.currentTimeMillis();
            long updateInterval = 10;


            if ((currentTime-lastDate) > updateInterval) {

                if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                    // Update acc at sensor rate

                        dspFaust.propagateAcc(0, event.values[0] * (-1));
                        dspFaust.propagateAcc(1, event.values[1] * (-1));
                        dspFaust.propagateAcc(2, event.values[2]);

                        dspFaustMotion.propagateAcc(0, event.values[0] * (-1));
                        dspFaustMotion.propagateAcc(1, event.values[1] * (-1));
                        dspFaustMotion.propagateAcc(2, event.values[2]);

                }

                if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
                // Update gyr at sensor rate

                        dspFaust.propagateGyr(0, event.values[0] * (-1));
                        dspFaust.propagateGyr(1, event.values[1] * (-1));
                        dspFaust.propagateGyr(2, event.values[2]);

                        dspFaustMotion.propagateGyr(0, event.values[0] * (-1));
                        dspFaustMotion.propagateGyr(1, event.values[1] * (-1));
                        dspFaustMotion.propagateGyr(2, event.values[2]);

                }

                if (event.sensor.getType() == Sensor.TYPE_ROTATION_VECTOR) {
                    // Update rotation matrix at sensor rate
                    SensorManager.getRotationMatrixFromVector(rotationMatrix, event.values);
                    SensorManager.remapCoordinateSystem(rotationMatrix, SensorManager.AXIS_X,
                            SensorManager.AXIS_Y, adjustedRotationMatrix);


                    dspFaust.motionRender(rotationMatrix[0], rotationMatrix[3], rotationMatrix[6],
                            rotationMatrix[1], rotationMatrix[4], rotationMatrix[7],
                            rotationMatrix[2], rotationMatrix[5], rotationMatrix[8]);

                }

                lastDate = currentTime;
            }

        }
};




// set Ref function
private void initFrame () {

if (sensorManager!=null){

    dspFaust.initFrame();

}

}

private void SharedPrefInit(Context name) {
    if(mSharedPref == null)
        mSharedPref = getSharedPreferences(name.getPackageName(), 0);
}

private  String SharedPrefRead(String key, String defValue) {
        return mSharedPref.getString(key, defValue);
}
private  void SharedPrefWriteString(String key, String value) {
        SharedPreferences.Editor prefsEditor = mSharedPref.edit();
        prefsEditor.putString(key, value);
        prefsEditor.commit();
}
private  Float SharedPrefRead(String key, float defValue) {
        return mSharedPref.getFloat(key, defValue);
}
private void SharedPreWriteFloat(String key, Float value) {
        SharedPreferences.Editor prefsEditor = mSharedPref.edit();
        prefsEditor.putFloat(key, value).commit();
}

private void SharedPreClear() {
        SharedPreferences.Editor prefsEditor = mSharedPref.edit();
        prefsEditor.clear().commit();
}




private void loadDefaultParams() {

    hpValue = SharedPrefRead("/Motion/hp",dspFaustMotion.getParamInit("/Motion/hp"));
    shok_thrValue = SharedPrefRead("/Motion/shok_thr",dspFaustMotion.getParamInit("/Motion/shok_thr"));
    antirebonValue = SharedPrefRead("/Motion/antirebon",dspFaustMotion.getParamInit("/Motion/antirebon"));
    lpValue = SharedPrefRead("/Motion/lp",dspFaustMotion.getParamInit("/Motion/lp"));
    tacc_thrValue = SharedPrefRead("/Motion/tacc_thr",dspFaustMotion.getParamInit("/Motion/tacc_thr"));
    tacc_gainValue = SharedPrefRead("/Motion/tacc_gain",dspFaustMotion.getParamInit("/Motion/tacc_gain"));
    tacc_upValue = SharedPrefRead("/Motion/tacc_up",dspFaustMotion.getParamInit("/Motion/tacc_up"));
    tacc_downValue = SharedPrefRead("/Motion/tacc_down",dspFaustMotion.getParamInit("/Motion/tacc_down"));
    tgyr_thrValue = SharedPrefRead("/Motion/tgyr_thr",dspFaustMotion.getParamInit("/Motion/tgyr_thr"));
    tgyr_gainValue = SharedPrefRead("/Motion/tgyr_gain",dspFaustMotion.getParamInit("/Motion/tgyr_gain"));
    tgyr_upValue = SharedPrefRead("/Motion/tgyr_up",dspFaustMotion.getParamInit("/Motion/tgyr_up"));
    tgyr_downValue = SharedPrefRead("/Motion/tgyr_down",dspFaustMotion.getParamInit("/Motion/tgyr_down"));
    osfprojValue = SharedPrefRead("/Motion/osfproj",dspFaustMotion.getParamInit("/Motion/osfproj"));

    dspFaustMotion.setParamValue("/Motion/hp", hpValue);
    dspFaustMotion.setParamValue("/Motion/shok_thr", shok_thrValue);
    dspFaustMotion.setParamValue("/Motion/antirebon", antirebonValue);
    dspFaustMotion.setParamValue("/Motion/tacc_thr", tacc_thrValue);
    dspFaustMotion.setParamValue("/Motion/tacc_gain", tacc_gainValue);
    dspFaustMotion.setParamValue("/Motion/tacc_up", tacc_upValue);
    dspFaustMotion.setParamValue("/Motion/tacc_down", tacc_downValue);
    dspFaustMotion.setParamValue("/Motion/tgyr_thr", tgyr_thrValue);
    dspFaustMotion.setParamValue("/Motion/tgyr_gain", tgyr_gainValue);
    dspFaustMotion.setParamValue("/Motion/tgyr_up", tgyr_upValue);
    dspFaustMotion.setParamValue("/Motion/tgyr_down", tgyr_downValue);
    dspFaustMotion.setParamValue("/Motion/lp", lpValue);
    dspFaustMotion.setParamValue("/Motion/osfproj", osfprojValue);


}

private void resetParams() {

        SharedPreClear();

        SharedPreWriteFloat("/Motion/hp", dspFaustMotion.getParamInit("/Motion/hp"));
        SharedPreWriteFloat("/Motion/shok_thr", dspFaustMotion.getParamInit("/Motion/shok_thr"));
        SharedPreWriteFloat("/Motion/antirebon", dspFaustMotion.getParamInit("/Motion/antirebon"));
        SharedPreWriteFloat("/Motion/tacc_thr", dspFaustMotion.getParamInit("/Motion/tacc_thr"));
        SharedPreWriteFloat("/Motion/tacc_gain", dspFaustMotion.getParamInit("/Motion/tacc_gain"));
        SharedPreWriteFloat("/Motion/tacc_up", dspFaustMotion.getParamInit("/Motion/tacc_up"));
        SharedPreWriteFloat("/Motion/tacc_down", dspFaustMotion.getParamInit("/Motion/tacc_down"));
        SharedPreWriteFloat("/Motion/tgyr_thr", dspFaustMotion.getParamInit("/Motion/tgyr_thr"));
        SharedPreWriteFloat("/Motion/tgyr_gain", dspFaustMotion.getParamInit("/Motion/tgyr_gain"));
        SharedPreWriteFloat("/Motion/tgyr_up", dspFaustMotion.getParamInit("/Motion/tgyr_up"));
        SharedPreWriteFloat("/Motion/tgyr_down", dspFaustMotion.getParamInit("/Motion/tgyr_down"));
        SharedPreWriteFloat("/Motion/osfproj", dspFaustMotion.getParamInit("/Motion/osfproj"));
        SharedPreWriteFloat("/Motion/lp", dspFaustMotion.getParamInit("/Motion/lp"));

        SharedPrefWriteString("oscAddress", "192.168.1.5");
        SharedPrefWriteString("oscInPort", "5510");
        SharedPrefWriteString("oscOutPort", "5511");

        if (dspFaust.getOSCIsOn()) {
            oscAddress = SharedPrefRead("oscAddress","192.168.1.5");
            oscInPort = Integer.parseInt(SharedPrefRead("oscInPort","5510"));
            oscOutPort = Integer.parseInt(SharedPrefRead("oscOutPort","5511"));

            dspFaust.setOSCValue(oscAddress, oscInPort, oscOutPort);

            ipAddress.setText(oscAddress);
            inputPort.setText(SharedPrefRead("oscInPort","5510"));
            outputPort.setText(SharedPrefRead("oscOutPort","5511"));
        }

}


@Override
protected void onPause() {
Log.d("Faust", "onPause");
super.onPause();
if(permissionToRecordAccepted) {

dspFaustMotion.stop();
dspFaust.stop();

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

if (!dspFaustMotion.isRunning()) {

    dspFaustMotion.start();
}

if (!dspFaust.isRunning()) {

    SharedPrefInit(getApplicationContext());

    if (dspFaust.getOSCIsOn()) {
        oscAddress = SharedPrefRead("oscAddress","192.168.1.5");
        oscInPort = Integer.parseInt(SharedPrefRead("oscInPort","5510"));
        oscOutPort = Integer.parseInt(SharedPrefRead("oscOutPort","5511"));

        dspFaust.setOSCValue(oscAddress, oscInPort, oscOutPort);

    }

    dspFaust.start();

    checkAddress();
    dspFaust.checkAdress();
    loadDefaultParams();


sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);

sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
Sensor.TYPE_GYROSCOPE), SensorManager.SENSOR_DELAY_FASTEST);

sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
Sensor.TYPE_ROTATION_VECTOR), SensorManager.SENSOR_DELAY_FASTEST);

}


}
}

@Override
public void onDestroy() {
Log.d("Faust", "onDestroy");

super.onDestroy();

if (dspFaustMotion != null) {
dspFaustMotion = null;
}

if (dspFaust != null) {
dspFaust = null;
}

if (sensorManager!=null){sensorManager.unregisterListener(mSensorListener);}

sensorManager= null;


}
}
