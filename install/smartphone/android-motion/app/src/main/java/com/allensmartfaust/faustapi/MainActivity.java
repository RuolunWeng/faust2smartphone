package com.allensmartfaust.faustapi;

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
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    DspFaust dspFaust;
    DspFaustMotion dspFaustMotion;
    
    private SensorManager sensorManager;
    
    private TextView cue,cueNext,cueText, cueNextText,tips;
    private EditText paramsValue, ipAddress, inputPort, outputPort;
    
    private ImageView touche;
    private Button prevCue, nextCue, initCue, setMotion , defaultParams, setOSC, setRef;
    
    
    private CheckBox setParams;
    private RadioGroup radioGroup;
    
    int scrWidth = 0,scrHeight= 0;
    
    
    String[] ParamArray = {"hp","shok_thr","antirebon","lp","tacc_thr",
    "tacc_gain","tacc_up","tacc_down","tgyr_thr",
    "tgyr_gain","tgyr_up","tgyr_down","osfproj"};
    
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
        
        setRef.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                initFrame();
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
                } else if (Str.endsWith("/brasG_cour")) {
                    brasGcourIsOn = true;
                    brasGcourAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasG_courOn", 1);
                } else if (Str.endsWith("/brasG_rear")) {
                    brasGrearIsOn = true;
                    brasGrearAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasG_rearOn", 1);
                } else if (Str.endsWith("/brasG_jardin")) {
                    brasGjardinIsOn = true;
                    brasGjardinAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasG_jardinOn", 1);
                } else if (Str.endsWith("/brasG_front")) {
                    brasGfrontIsOn = true;
                    brasGfrontAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasG_frontOn", 1);
                } else if (Str.endsWith("/brasG_down")) {
                    brasGdownIsOn = true;
                    brasGdownAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasG_downOn", 1);
                } else if (Str.endsWith("/brasG_up")) {
                    brasGupIsOn = true;
                    brasGupAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasG_upOn", 1);
                } else if (Str.endsWith("/pieds_cour")) {
                    piedscourIsOn = true;
                    piedscourAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/pieds_courOn", 1);
                } else if (Str.endsWith("/pieds_rear")) {
                    piedsrearIsOn = true;
                    piedsrearAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/pieds_rearOn", 1);
                } else if (Str.endsWith("/pieds_jardin")) {
                    piedsjardinIsOn = true;
                    piedsjardinAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/pieds_jardinOn", 1);
                } else if (Str.endsWith("/pieds_front")) {
                    piedsfrontIsOn = true;
                    piedsfrontAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/pieds_frontOn", 1);
                } else if (Str.endsWith("/pieds_down")) {
                    piedsdownIsOn = true;
                    piedsdownAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/pieds_downOn", 1);
                } else if (Str.endsWith("/pieds_up")) {
                    piedsupIsOn = true;
                    piedsupAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/pieds_upOn", 1);
                } else if (Str.endsWith("/dos_cour")) {
                    doscourIsOn = true;
                    doscourAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/dos_courOn", 1);
                } else if (Str.endsWith("/dos_rear")) {
                    dosrearIsOn = true;
                    dosrearAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/dos_rearOn", 1);
                } else if (Str.endsWith("/dos_jardin")) {
                    dosjardinIsOn = true;
                    dosjardinAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/dos_jardinOn", 1);
                } else if (Str.endsWith("/dos_front")) {
                    dosfrontIsOn = true;
                    dosfrontAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/dos_frontOn", 1);
                } else if (Str.endsWith("/dos_down")) {
                    dosdownIsOn = true;
                    dosdownAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/dos_downOn", 1);
                } else if (Str.endsWith("/dos_up")) {
                    dosupIsOn = true;
                    dosupAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/dos_upOn", 1);
                } else if (Str.endsWith("/brasD_cour")) {
                    brasDcourIsOn = true;
                    brasDcourAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasD_courOn", 1);
                } else if (Str.endsWith("/brasD_rear")) {
                    brasDrearIsOn = true;
                    brasDrearAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasD_rearOn", 1);
                } else if (Str.endsWith("/brasD_jardin")) {
                    brasDjardinIsOn = true;
                    brasDjardinAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasD_jardinOn", 1);
                } else if (Str.endsWith("/brasD_front")) {
                    brasDfrontIsOn = true;
                    brasDfrontAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasD_frontOn", 1);
                } else if (Str.endsWith("/brasD_down")) {
                    brasDdownIsOn = true;
                    brasDdownAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasD_downOn", 1);
                } else if (Str.endsWith("/brasD_up")) {
                    brasDupIsOn = true;
                    brasDupAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/brasD_upOn", 1);
                } else if (Str.endsWith("/tete_cour")) {
                    tetecourIsOn = true;
                    tetecourAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/tete_courOn", 1);
                } else if (Str.endsWith("/tete_rear")) {
                    teterearIsOn = true;
                    teterearAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/tete_rearOn", 1);
                } else if (Str.endsWith("/tete_jardin")) {
                    tetejardinIsOn = true;
                    tetejardinAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/tete_jardinOn", 1);
                } else if (Str.endsWith("/tete_front")) {
                    tetefrontIsOn = true;
                    tetefrontAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/tete_frontOn", 1);
                } else if (Str.endsWith("/tete_down")) {
                    tetedownIsOn = true;
                    tetedownAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/tete_downOn", 1);
                } else if (Str.endsWith("/tete_up")) {
                    teteupIsOn = true;
                    teteupAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/tete_upOn", 1);
                } else if (Str.endsWith("/ventre_cour")) {
                    ventrecourIsOn = true;
                    ventrecourAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/ventre_courOn", 1);
                } else if (Str.endsWith("/ventre_rear")) {
                    ventrerearIsOn = true;
                    ventrerearAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/ventre_rearOn", 1);
                } else if (Str.endsWith("/ventre_jardin")) {
                    ventrejardinIsOn = true;
                    ventrejardinAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/ventre_jardinOn", 1);
                } else if (Str.endsWith("/ventre_front")) {
                    ventrefrontIsOn = true;
                    ventrefrontAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/ventre_frontOn", 1);
                } else if (Str.endsWith("/ventre_down")) {
                    ventredownIsOn = true;
                    ventredownAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/ventre_downOn", 1);
                } else if (Str.endsWith("/ventre_up")) {
                    ventreupIsOn = true;
                    ventreupAddress = dspFaust.getParamAddress(i);
                    dspFaustMotion.setParamValue("/Motion/ventre_upOn", 1);
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
    
    if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
    // Update acc at sensor rate
    if (dspFaust != null) {
    dspFaust.propagateAcc(0, event.values[0] * (-1));
    dspFaust.propagateAcc(1, event.values[1] * (-1));
    dspFaust.propagateAcc(2, event.values[2]);
}

if (dspFaustMotion != null) {
dspFaustMotion.propagateAcc(0, event.values[0] * (-1));
dspFaustMotion.propagateAcc(1, event.values[1] * (-1));
dspFaustMotion.propagateAcc(2, event.values[2]);
}
}

if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
// Update gyr at sensor rate
if (dspFaust != null) {
dspFaust.propagateGyr(0, event.values[0] * (-1));
dspFaust.propagateGyr(1, event.values[1] * (-1));
dspFaust.propagateGyr(2, event.values[2]);
}

if (dspFaustMotion != null) {
dspFaustMotion.propagateGyr(0, event.values[0] * (-1));
dspFaustMotion.propagateGyr(1, event.values[1] * (-1));
dspFaustMotion.propagateGyr(2, event.values[2]);
}
}

if (event.sensor.getType() == Sensor.TYPE_ROTATION_VECTOR) {
// Update rotation matrix at sensor rate
SensorManager.getRotationMatrixFromVector(rotationMatrix, event.values);
SensorManager.remapCoordinateSystem(rotationMatrix, SensorManager.AXIS_X,
SensorManager.AXIS_Y, adjustedRotationMatrix);

//matrixA =rotationMatrix;
matrixA[0][0] =rotationMatrix[0];
matrixA[0][1] =rotationMatrix[3];
matrixA[0][2] =rotationMatrix[6];

matrixA[1][0] =rotationMatrix[1];
matrixA[1][1] =rotationMatrix[4];
matrixA[1][2] =rotationMatrix[7];

matrixA[2][0] =rotationMatrix[2];
matrixA[2][1] =rotationMatrix[5];
matrixA[2][2] =rotationMatrix[8];

matrixC = matrixMultiplication(matrixA,matrixB);

if (dspFaustMotion != null) {
dspFaustMotion.setParamValue("/Motion/brasD_x", (-1) * matrixC[0][0]);
dspFaustMotion.setParamValue("/Motion/brasD_y", (-1) * matrixC[0][1]);
dspFaustMotion.setParamValue("/Motion/brasD_z", (-1) * matrixC[0][2]);

dspFaustMotion.setParamValue("/Motion/pieds_x", (-1) * matrixC[1][0]);
dspFaustMotion.setParamValue("/Motion/pieds_y", (-1) * matrixC[1][1]);
dspFaustMotion.setParamValue("/Motion/pieds_z", (-1) * matrixC[1][2]);

dspFaustMotion.setParamValue("/Motion/dos_x", (-1) * matrixC[2][0]);
dspFaustMotion.setParamValue("/Motion/dos_y", (-1) * matrixC[2][1]);
dspFaustMotion.setParamValue("/Motion/dos_z", (-1) * matrixC[2][2]);

dspFaustMotion.setParamValue("/Motion/brasG_x", matrixC[0][0]);
dspFaustMotion.setParamValue("/Motion/brasG_y", matrixC[0][1]);
dspFaustMotion.setParamValue("/Motion/brasG_z", matrixC[0][2]);

dspFaustMotion.setParamValue("/Motion/tete_x", matrixC[1][0]);
dspFaustMotion.setParamValue("/Motion/tete_y", matrixC[1][1]);
dspFaustMotion.setParamValue("/Motion/tete_z", matrixC[1][2]);

dspFaustMotion.setParamValue("/Motion/ventre_x", matrixC[2][0]);
dspFaustMotion.setParamValue("/Motion/ventre_y", matrixC[2][1]);
dspFaustMotion.setParamValue("/Motion/ventre_z", matrixC[2][2]);
}
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
if (brasGcourIsOn) {
dspFaust.setParamValue(brasGcourAddress, dspFaustMotion.getParamValue("/Motion/brasG_cour"));
}
if (brasGrearIsOn) {
dspFaust.setParamValue(brasGrearAddress, dspFaustMotion.getParamValue("/Motion/bras_Grear"));
}
if (brasGjardinIsOn) {
dspFaust.setParamValue(brasGjardinAddress, dspFaustMotion.getParamValue("/Motion/brasG_jardin"));
}
if (brasGfrontIsOn) {
dspFaust.setParamValue(brasGfrontAddress, dspFaustMotion.getParamValue("/Motion/brasG_front"));
}
if (brasGdownIsOn) {
dspFaust.setParamValue(brasGdownAddress, dspFaustMotion.getParamValue("/Motion/brasG_down"));
}
if (brasGupIsOn) {
dspFaust.setParamValue(brasGupAddress, dspFaustMotion.getParamValue("/Motion/brasG_up"));
}
if (piedscourIsOn) {
dspFaust.setParamValue(piedscourAddress, dspFaustMotion.getParamValue("/Motion/pieds_cour"));
}
if (piedsrearIsOn) {
dspFaust.setParamValue(piedsrearAddress, dspFaustMotion.getParamValue("/Motion/pieds_Grear"));
}
if (piedsjardinIsOn) {
dspFaust.setParamValue(piedsjardinAddress, dspFaustMotion.getParamValue("/Motion/pieds_jardin"));
}
if (piedsfrontIsOn) {
dspFaust.setParamValue(piedsfrontAddress, dspFaustMotion.getParamValue("/Motion/pieds_front"));
}
if (piedsdownIsOn) {
dspFaust.setParamValue(piedsdownAddress, dspFaustMotion.getParamValue("/Motion/pieds_down"));
}
if (piedsupIsOn) {
dspFaust.setParamValue(piedsupAddress, dspFaustMotion.getParamValue("/Motion/pieds_up"));
}
if (doscourIsOn) {
dspFaust.setParamValue(doscourAddress, dspFaustMotion.getParamValue("/Motion/dos_cour"));
}
if (dosrearIsOn) {
dspFaust.setParamValue(dosrearAddress, dspFaustMotion.getParamValue("/Motion/dos_Grear"));
}
if (dosjardinIsOn) {
dspFaust.setParamValue(dosjardinAddress, dspFaustMotion.getParamValue("/Motion/dos_jardin"));
}
if (dosfrontIsOn) {
dspFaust.setParamValue(dosfrontAddress, dspFaustMotion.getParamValue("/Motion/dos_front"));
}
if (dosdownIsOn) {
dspFaust.setParamValue(dosdownAddress, dspFaustMotion.getParamValue("/Motion/dos_down"));
}
if (dosupIsOn) {
dspFaust.setParamValue(dosupAddress, dspFaustMotion.getParamValue("/Motion/dos_up"));
}
if (brasDcourIsOn) {
dspFaust.setParamValue(brasDcourAddress, dspFaustMotion.getParamValue("/Motion/brasD_cour"));
}
if (brasDrearIsOn) {
dspFaust.setParamValue(brasDrearAddress, dspFaustMotion.getParamValue("/Motion/brasD_Grear"));
}
if (brasDjardinIsOn) {
dspFaust.setParamValue(brasDjardinAddress, dspFaustMotion.getParamValue("/Motion/brasD_jardin"));
}
if (brasDfrontIsOn) {
dspFaust.setParamValue(brasDfrontAddress, dspFaustMotion.getParamValue("/Motion/brasD_front"));
}
if (brasDdownIsOn) {
dspFaust.setParamValue(brasDdownAddress, dspFaustMotion.getParamValue("/Motion/brasD_down"));
}
if (brasDupIsOn) {
dspFaust.setParamValue(brasDupAddress, dspFaustMotion.getParamValue("/Motion/brasD_up"));
}
if (tetecourIsOn) {
dspFaust.setParamValue(tetecourAddress, dspFaustMotion.getParamValue("/Motion/tete_cour"));
}
if (teterearIsOn) {
dspFaust.setParamValue(teterearAddress, dspFaustMotion.getParamValue("/Motion/tete_Grear"));
}
if (tetejardinIsOn) {
dspFaust.setParamValue(tetejardinAddress, dspFaustMotion.getParamValue("/Motion/tete_jardin"));
}
if (tetefrontIsOn) {
dspFaust.setParamValue(tetefrontAddress, dspFaustMotion.getParamValue("/Motion/tete_front"));
}
if (tetedownIsOn) {
dspFaust.setParamValue(tetedownAddress, dspFaustMotion.getParamValue("/Motion/tete_down"));
}
if (teteupIsOn) {
dspFaust.setParamValue(teteupAddress, dspFaustMotion.getParamValue("/Motion/tete_up"));
}
if (ventrecourIsOn) {
dspFaust.setParamValue(ventrecourAddress, dspFaustMotion.getParamValue("/Motion/ventre_cour"));
}
if (ventrerearIsOn) {
dspFaust.setParamValue(ventrerearAddress, dspFaustMotion.getParamValue("/Motion/ventre_Grear"));
}
if (ventrejardinIsOn) {
dspFaust.setParamValue(ventrejardinAddress, dspFaustMotion.getParamValue("/Motion/ventre_jardin"));
}
if (ventrefrontIsOn) {
dspFaust.setParamValue(ventrefrontAddress, dspFaustMotion.getParamValue("/Motion/ventre_front"));
}
if (ventredownIsOn) {
dspFaust.setParamValue(ventredownAddress, dspFaustMotion.getParamValue("/Motion/ventre_down"));
}
if (ventreupIsOn) {
dspFaust.setParamValue(ventreupAddress, dspFaustMotion.getParamValue("/Motion/ventre_up"));
}

}

};


// 3 rows * 3 columns
public static float[][] matrixMultiplication (float[][] m1, float[][] m2) {

int x= 3;
int y= 3;
float m[][] = new float[3][3];

for(int i = 0; i < x; i++) {
for(int j = 0; j < y; j++) {
for(int k = 0; k < y; k++){
m[i][j] += m1[i][k]*m2[k][j];
}
}
}

return m;
}

// set Ref function
private void initFrame () {

if (sensorManager!=null){
// inverse matrix the matrix reference
float a11 = rotationMatrix[0];
float a12 = rotationMatrix[3];
float a13 = rotationMatrix[6];
float a21 = rotationMatrix[1];
float a22 = rotationMatrix[4];
float a23 = rotationMatrix[7];
float a31 = rotationMatrix[2];
float a32 = rotationMatrix[5];
float a33 = rotationMatrix[8];

float detA=a11*a22*a33+a21*a32*a13+a31*a12*a23-a11*a32*a23-a31*a22*a13-a21*a12*a33;

matrixB[0][0] =(1/detA)*(a22*a33-a23*a32);
matrixB[0][1] =(1/detA)*(a13*a32-a12*a33);
matrixB[0][2] =(1/detA)*(a12*a23-a13*a22);

matrixB[1][0] =(1/detA)*(a23*a31-a21*a33);
matrixB[1][1] =(1/detA)*(a11*a33-a13*a31);
matrixB[1][2] =(1/detA)*(a13*a21-a11*a23);

matrixB[2][0] =(1/detA)*(a21*a32-a22*a31);
matrixB[2][1] =(1/detA)*(a12*a31-a11*a32);
matrixB[2][2] =(1/detA)*(a11*a22-a12*a21);
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

checkAddress();

dspFaust.start();

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
