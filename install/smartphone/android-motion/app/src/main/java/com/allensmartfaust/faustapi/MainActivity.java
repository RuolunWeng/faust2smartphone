package com.allensmartfaust.faustapi;

import com.allensmartfaust.faustapi.CustomButton;
import com.allensmartfaust.faustapi.CustomButtonFactory;
import com.allensmartfaust.faustapi.CustomTabView;

import android.Manifest;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.opengl.Matrix;
import android.os.Build;
import android.renderscript.Matrix4f;
import androidx.core.app.ActivityCompat;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.TextUtils;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewTreeObserver;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.Spinner;
import android.widget.ArrayAdapter;
import android.widget.AdapterView;
import android.text.InputType;
import android.view.ViewGroup;


import com.DspFaust.DspFaust;
import com.DspFaust.DspFaustMotion;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

import static android.R.color.white;
import static java.lang.Math.sqrt;

// For audio input request permission
//import android.support.v4.app.ActivityCompat;
import android.Manifest;
import android.widget.Toast;
import androidx.annotation.NonNull;

import android.content.pm.PackageManager;

public class MainActivity extends AppCompatActivity
implements ActivityCompat.OnRequestPermissionsResultCallback {

    public static DspFaust dspFaust;
    DspFaustMotion dspFaustMotion;

    private SensorManager sensorManager;

    private SharedPreferences mSharedPref;

    private TextView cue,cueNext,cueText, cueNextText, appName;
    public static TextView tips;
    private EditText paramsValue, ipAddress, inputPort, outputPort;

    private ImageView touche;
    private Button prevCue, nextCue, initCue, setMotion , defaultParams, setOSC, setRef;

    ScrollView scrollView;
    CustomTabView touchUItabView;
    private List<CustomButton> customBargraphs = new ArrayList<>(); // Declare CustomButton list
    boolean newCueIsOn, newCounterIsOn;

    private CheckBox setParams, settings;
    private RadioGroup radioGroup;

    int scrWidth = 0,scrHeight= 0;

    int SR = 44100;
    int blockSize = 256;
    long lastDate=0;
    int updateInterval = (int)(1000.f/(SR/blockSize));
    int sensorUpdateIntervalMicros;  // Sensor update interval in microseconds (matches iOS)

    ArrayList<String> cueList = new ArrayList<String>();
    ArrayList<String> tipsList = new ArrayList<String>();

    ArrayList<String>  motionParamArray = new ArrayList<String>();
    ArrayList<String>  motionParamAddress = new ArrayList<String>();

    // Settings panel selected indices
    private int motionLibSelectedIdx = 0;
    private int dspParamSelectedIdx = 0;

    int cueIndex,cueIndexNext;

    float[] rotationMatrix = new float[9];
    float[] mOrientation = new float[3];
    float[] mQuaternion = new float[4];
    float[] referenceRotationMatrix = new float[9];

    String oscAddress;
    int oscInPort;
    int oscOutPort;

    String touchGateAddress;
    String screenXAddress;
    String screenYAddress;
    String magneticHeadingAddress;
    String yawAddress;
    String pitchAddress;
    String rollAddress;
    String useraccxAddress;
    String useraccyAddress;
    String useracczAddress;
    String quaternionwAddress;
    String quaternionxAddress;
    String quaternionyAddress;
    String quaternionzAddress;

    String cueAddress;
    String tipAddress;
    String stateAddress;

    String setref_compAddress;
    String setref_rotaAddress;

    boolean[] paramsOn;
    boolean touchGateIsOn;
    boolean screenXIsOn;
    boolean screenYIsOn;
    boolean magneticHeadingIsOn;
    boolean yawIsOn;
    boolean pitchIsOn;
    boolean rollIsOn;
    boolean useraccxIsOn;
    boolean useraccyIsOn;
    boolean useracczIsOn;
    boolean quaternionwIsOn;
    boolean quaternionxIsOn;
    boolean quaternionyIsOn;
    boolean quaternionzIsOn;

    float magnetic;
    float magneticNormal;
    float magneticNew;
    float magneticDeg;
    float magneticBinaural;
    float offset;

    boolean cueIsOn;
    boolean tipIsOn;
    boolean stateIsOn;

    boolean setref_compIsOn;
    boolean setref_rotaIsOn;

    int cnt;
    int cnt2;


    // For audio input request permission
    private static final int AUDIO_ECHO_REQUEST = 0;
    private boolean permissionToRecordAccepted = false;

    private void createFaust() {


        if (dspFaustMotion == null) {
            //dspFaustMotion = new DspFaustMotion(SR / blockSize, 1);
            dspFaustMotion = new DspFaustMotion(SR, blockSize);

            // PRINT ALL PARAMETRE ADDRESS
            for (int i = 0; i < dspFaustMotion.getParamsCount(); i++) {
                System.out.println(dspFaustMotion.getParamAddress(i));
            }

        }

        if (dspFaust == null) {

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

        // Lock orientation to portrait
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        
        getSupportActionBar().hide();
        setContentView(R.layout.activity_main);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                             WindowManager.LayoutParams.FLAG_FULLSCREEN);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        if (Build.VERSION.SDK_INT >= 23 && !isRecordPermissionGranted()){
            requestRecordPermission();
        } else {
            permissionToRecordAccepted = true;
            createFaust();
        }

        // check if audio files were saved in internal storage
          String[] internalStorageList = getFilesDir().list();
          boolean fileWereCopied = false;
          for(int i=0; i<internalStorageList.length; i++){
              if(internalStorageList[i].contains(".aif") || internalStorageList[i].contains(".wav") || internalStorageList[i].contains(".flac")) {
                  fileWereCopied = true;
                  break;
              }
          }

          // if audio files were not saved in internal storage, then transfer them
          if(!fileWereCopied) {
              AssetManager assets = getAssets();
              try {
                  String[] assetsList = assets.list("");

                  for (int i = 0; i < assetsList.length; i++) {
                      if (assetsList[i].contains(".aif") || assetsList[i].contains(".wav") || assetsList[i].contains(".flac")) {

                          InputStream in = null;
                          OutputStream out = null;
                          in = assets.open(assetsList[i]);
                          File outFile = new File(getFilesDir().getPath(), assetsList[i]);
                          out = new FileOutputStream(outFile);

                          // copy content
                          byte[] buffer = new byte[1024];
                          int read;
                          while ((read = in.read(buffer)) != -1) {
                              out.write(buffer, 0, read);
                          }
                          in.close();
                          in = null;
                          out.flush();
                          out.close();
                          out = null;

                      }

                  }

              } catch (IOException e) {
                  e.printStackTrace();
              }
          }


        // Load cues from file
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

        // Calculate sensor update interval to match iOS behavior
        calculateSensorUpdateInterval();

        if (sensorManager!=null) {
            sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                    Sensor.TYPE_ACCELEROMETER), sensorUpdateIntervalMicros);

            sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                    Sensor.TYPE_GYROSCOPE), sensorUpdateIntervalMicros);

            sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                    Sensor.TYPE_ROTATION_VECTOR), sensorUpdateIntervalMicros);
        }

        touche = (ImageView) findViewById(R.id.touche);

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
        appName = (TextView) findViewById(R.id.appName);

        cue.setText(cueList.get(cueIndex));
        cueNext.setText(cueList.get(cueIndexNext));
        tips.setText(tipsList.get(cueIndex));

        //appName.setText(getApplicationContext().getPackageName().replace("com."," ").concat(" | Grame"));
        displayTitle();

        nextCue.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                nextCue();
            }
        });

        prevCue.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                prevCue();
            }
        });

        initCue.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                initCue();

            }
        });


        // Create a ScrollView
        scrollView = (ScrollView) findViewById(R.id.transparent_scrollview);

        final View settingsLayoutRoot = findViewById(R.id.settings_layout_root);
        settingsLayoutRoot.setBackgroundColor(Color.argb(100,0,0,0));
        settingsLayoutRoot.setVisibility(View.INVISIBLE);

        setOSC = (Button) settingsLayoutRoot.findViewById(R.id.setOSC);
        ipAddress = (EditText) settingsLayoutRoot.findViewById(R.id.ipAddress);
        inputPort = (EditText) settingsLayoutRoot.findViewById(R.id.inputPort);
        outputPort = (EditText) settingsLayoutRoot.findViewById(R.id.outputPort);

        radioGroup=(RadioGroup)settingsLayoutRoot.findViewById(R.id.radioGroup);
        paramsValue = (EditText) settingsLayoutRoot.findViewById(R.id.paramValue);
        setMotion = (Button) settingsLayoutRoot.findViewById(R.id.setMotion);
        defaultParams =(Button) settingsLayoutRoot.findViewById(R.id.defaultParams);
        setRef =(Button) settingsLayoutRoot.findViewById(R.id.setRef);

        final RadioGroup radioGroupMotionLib =(RadioGroup)settingsLayoutRoot.findViewById(R.id.radioGroupMotionLib);
        final EditText paramsValueMotionLib = (EditText) settingsLayoutRoot.findViewById(R.id.paramValueMotionLib);
        Button setMotionLib = (Button) settingsLayoutRoot.findViewById(R.id.setMotionLib);
        Button defaultParamsMotionLib =(Button) settingsLayoutRoot.findViewById(R.id.defaultParamsMotionLib);

        final ArrayList<String>  motionLibParamArray = new ArrayList<String>();
        final ArrayList<String>  motionLibParamAddress = new ArrayList<String>();

        for (int i = 0; i < dspFaustMotion.getParamsCount(); i++) {
            String Str = dspFaustMotion.getMetadata(i, "showName");
            if (Str != null) {
                if (!Str.equals("")){
                    motionLibParamArray.add(Str);
                    motionLibParamAddress.add(dspFaustMotion.getParamAddress(i));
                }
            }
        }

        final boolean[] paramsLibOn = new boolean[motionLibParamArray.size()];
        for(int i = 0; i < motionLibParamArray.size(); i++) {
            RadioButton rdbtn = new RadioButton(this);
            rdbtn.setId(i);
            rdbtn.setTextColor(Color.WHITE);
            rdbtn.setText(motionLibParamArray.get(i));
            radioGroupMotionLib.addView(rdbtn);
        }

        radioGroupMotionLib.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener()
        {
            public void onCheckedChanged(RadioGroup group, int checkedId)
            {
                // This will get the radiobutton that has changed in its check state
                RadioButton checkedRadioButton = (RadioButton)group.findViewById(checkedId);
                boolean isChecked = checkedRadioButton.isChecked();
                if (isChecked)
                {
                    for (int i=0; i< motionLibParamArray.size(); i++) {
                        paramsLibOn[i]=false;
                    }
                    paramsLibOn[checkedId]=true;
                    paramsValueMotionLib.setText( String.valueOf(dspFaustMotion.getParamValue(motionLibParamAddress.get(checkedId))));
                }
            }
        });


        setMotionLib.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                // Find the label index of the edited parameter
                int ii = -1;
                for (ii=0; ii<motionLibParamArray.size(); ii++) {
                    if (paramsLibOn[ii]) {

                        break;
                    }
                }

                String param =  motionLibParamArray.get(ii);

                for (int i=0; i< motionLibParamArray.size(); i++) {

                    if (motionLibParamArray.get(i).equals(param) ){
                        dspFaustMotion.setParamValue(motionLibParamAddress.get(i), Float.valueOf(paramsValueMotionLib.getText().toString()));
                        SharedPreWriteFloat(motionLibParamArray.get(i),Float.valueOf(paramsValueMotionLib.getText().toString()));
                    }

                }

            }
        });



        defaultParamsMotionLib.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                for (int i=0; i<motionLibParamAddress.size(); i++){
                    dspFaustMotion.setParamValue(motionLibParamAddress.get(i), dspFaustMotion.getParamInit(motionLibParamAddress.get(i)));
                    SharedPreWriteFloat(motionLibParamArray.get(i), dspFaustMotion.getParamInit((motionLibParamAddress.get(i))));
                }

                // Check if the RadioGroup is found
                if (radioGroupMotionLib != null) {
                    // Get the first RadioButton in the RadioGroup
                    RadioButton firstRadioButton = (RadioButton) radioGroupMotionLib.getChildAt(0);
                    // Check if the first RadioButton is found
                    if (firstRadioButton != null) {
                        // Set the first RadioButton as checked
                        firstRadioButton.setChecked(true);
                        paramsValueMotionLib.setText( String.valueOf(dspFaustMotion.getParamValue(motionLibParamAddress.get(0))));
                    }
                }
                Toast.makeText(MainActivity.this, "Reset MotionLib Defaults Params", Toast.LENGTH_LONG).show();


            }
        });


        final Button initOSC =(Button) settingsLayoutRoot.findViewById(R.id.initOSC);

        settings = (CheckBox) findViewById(R.id.SetParamsNew);
        settings.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                                                @Override
                                                public void onCheckedChanged(CompoundButton buttonView,boolean isChecked) {
                                                    if (isChecked) {
                                                        showSettingView();
                                                        // Uncheck immediately so it can be checked again
                                                        buttonView.setChecked(false);
                                                    }
                                                }
                                            });

        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener()
                                              {
            public void onCheckedChanged(RadioGroup group, int checkedId)
            {
                // This will get the radiobutton that has changed in its check state
                RadioButton checkedRadioButton = (RadioButton)group.findViewById(checkedId);
                boolean isChecked = checkedRadioButton.isChecked();
                if (isChecked)
                {
                    for (int i=0; i< motionParamArray.size(); i++) {
                        paramsOn[i]=false;
                    }
                    paramsOn[checkedId]=true;
                    paramsValue.setText( String.valueOf(dspFaust.getParamValue(motionParamAddress.get(checkedId))));
                    //paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue(motionParamAddress.get(checkedId))));

                }
            }
        });


        setMotion.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

               /*
                for (int i=0; i< motionParamArray.size(); i++) {
                    if (paramsOn[i]){
                        dspFaustMotion.setParamValue(motionParamAddress.get(i), Float.valueOf(paramsValue.getText().toString()));
                        SharedPreWriteFloat(motionParamArray.get(i),Float.valueOf(paramsValue.getText().toString()));
                    }

                }
             */

                // Find the label index of the edited parameter
                int ii = -1;
                for (ii=0; ii<motionParamArray.size(); ii++) {
                    if (paramsOn[ii]) {

                        break;
                    }
                }


                String param =  motionParamArray.get(ii);


                for (int i=0; i< motionParamArray.size(); i++) {

                    if (motionParamArray.get(i).equals(param) ){
                        dspFaust.setParamValue(motionParamAddress.get(i), Float.valueOf(paramsValue.getText().toString()));
                        SharedPreWriteFloat(motionParamArray.get(i),Float.valueOf(paramsValue.getText().toString()));
                    }

                }

            }
        });



        defaultParams.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                //for (int i=0; i<dspFaust.getParamsCount(); i++) {
                    //dspFaust.setParamValue(i, dspFaust.getParamInit(i));
                    //dspFaustMotion.setParamValue(i, dspFaustMotion.getParamInit(i));
                //}

                resetParams();

                // Check if the RadioGroup is found
                if (radioGroup != null) {
                    // Get the first RadioButton in the RadioGroup
                    RadioButton firstRadioButton = (RadioButton) radioGroup.getChildAt(0);
                    // Check if the first RadioButton is found
                    if (firstRadioButton != null) {
                        // Set the first RadioButton as checked
                        firstRadioButton.setChecked(true);
                        paramsValue.setText( String.valueOf(dspFaust.getParamValue(motionParamAddress.get(0))));
                    }
                }
                Toast.makeText(MainActivity.this, "Reset Defaults Params", Toast.LENGTH_LONG).show();
                //checkAddress();
                dspFaust.checkAdress();



            }
        });

        initOSC.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                resetOSCParams();

                //paramsValue.setText("Done");
                Toast.makeText(MainActivity.this, "Restart to use new OSC", Toast.LENGTH_LONG).show();


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


        // Add a view tree observer to your view
        scrollView.getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                // Remove the listener to avoid multiple calls
                scrollView.getViewTreeObserver().removeOnGlobalLayoutListener(this);

                // Get the width of the view
                int widthView = scrollView.getWidth();
                // Get the width of the view
                int heightView = scrollView.getHeight();
                int buttonHeight = 130;

                heightView = heightView - buttonHeight;

                // Do something with the width
                // Handle button click
                System.out.println("scrollView.getWidth() " + scrollView.getWidth() + "scrollView.getHeight() " + scrollView.getHeight());


                touchUItabView = new CustomTabView(scrollView.getContext());

                scrollView.addView(touchUItabView);

                // Preset array of button names
                String[] typeButtonNames = {"button", "checkbox", "trigCue", "nextCue", "prevCue", "initCue", "setRef", "hslider", "vslider", "trigCounter", "pad", "hbargraph", "vbargraph"};

                for (int i = 0; i < dspFaust.getParamsCount(); i++) {
                    String dataParamMotionButton = dspFaust.getMetadata(i, "SHCUI");

                    if (dataParamMotionButton != null) {

                        if (!dataParamMotionButton.isEmpty()) {
                        String[] components = dataParamMotionButton.split(" ");
                        if (components.length == 10) {
                            // Extract the values
                            String buttonType = components[1];
                            // Check if buttonName is in the preset array
                            if (!Arrays.asList(typeButtonNames).contains(buttonType)) {
                                // Button name is not in the preset array
                                Log.d("UI TYPE", "is not valid");
                                tips.setText("UI TYPE is not valid"); // or handle the error as needed
                                return;
                            }

                            if (buttonType.equals("trigCue")) {
                                newCueIsOn = true;
                            }

                            if (buttonType.equals("trigCounter")) {
                                newCounterIsOn = true;
                            }

                            // Extract the values
                            String tabViewName = components[0];
                            int x = Integer.parseInt(components[2]);
                            int y = Integer.parseInt(components[3]);
                            int width = Integer.parseInt(components[4]);
                            int height = Integer.parseInt(components[5]);
                            int colorR = Integer.parseInt(components[6]);
                            int colorG = Integer.parseInt(components[7]);
                            int colorB = Integer.parseInt(components[8]);
                            int colorA = Integer.parseInt(components[9]);

                            // Now you have the button name and the coordinates (x, y) and size (width, height) (R G B)
                            // Convert the const char* parameter to an NSString
                            String[] parts = dspFaust.getParamAddress(i).split("/");
                            String lastElement = parts[parts.length - 1];
                            String paramShortName = new String(lastElement);
                            //String paramShortName = new String(dspFaust.getParamShortName(i));
                            // Convert the const char* parameter to an NSString
                            String paramPath = new String(dspFaust.getParamAddress(i));

                            // current init value scale to 0-1
                            ArrayList<Float> initValues = new ArrayList<>();

                            if (buttonType.equals("pad")) {
                                String padXPath = paramPath + "_X";
                                String padYPath = paramPath + "_Y";
                                float initValueX = scaleBackValue(dspFaust.getParamValue(padXPath), dspFaust.getParamMin(padXPath), dspFaust.getParamMax(padXPath));
                                initValues.add(initValueX);
                                float initValueY = scaleBackValue(dspFaust.getParamValue(padYPath), dspFaust.getParamMin(padYPath), dspFaust.getParamMax(padYPath));
                                initValues.add(initValueY);
                            } else {
                                float initValue = scaleBackValue(dspFaust.getParamValue(i), dspFaust.getParamMin(i), dspFaust.getParamMax(i));
                                initValues.add(initValue);
                                //Log.d(buttonType, initValues.toString());
                                //Log.d(buttonType, "init is: " + initValues);
                            }

                            CustomButton touchUI = CustomButtonFactory.createButtonWithParams(
                                    scrollView.getContext(), buttonType, x*widthView/100, y*heightView/100, width*widthView/100, height*heightView/100, paramShortName, paramPath, i,
                                    Color.argb(colorA, colorR, colorG, colorB), initValues);

                            touchUItabView.addTab(tabViewName, touchUI);

                            if (buttonType.equals("hbargraph")) {
                                customBargraphs.add(touchUI);
                            }
                            if (buttonType.equals("vbargraph")) {
                                customBargraphs.add(touchUI);
                            }
                            if (buttonType.equals("trigCue")) {
                                touchUI.setOnClickListener(new CustomButton.OnClickListener() {
                                    @Override
                                    public void onClick(CustomButton button) {
                                        Log.d("CustomButton", "TRIG CUE Button clicked");
                                        // Log other relevant information
                                        goCue();
                                    }
                                });
                            }
                            if (buttonType.equals("nextCue")) {
                                touchUI.setOnClickListener(new CustomButton.OnClickListener() {
                                    @Override
                                    public void onClick(CustomButton button) {
                                        Log.d("CustomButton", "Next CUE Button clicked");
                                        // Log other relevant information
                                        nextCue();
                                    }
                                });
                            }
                            if (buttonType.equals("prevCue")) {
                                touchUI.setOnClickListener(new CustomButton.OnClickListener() {
                                    @Override
                                    public void onClick(CustomButton button) {
                                        Log.d("CustomButton", "Prev CUE Button clicked");
                                        // Log other relevant information
                                        prevCue();
                                    }
                                });
                            }
                            if (buttonType.equals("initCue")) {
                                touchUI.setOnClickListener(new CustomButton.OnClickListener() {
                                    @Override
                                    public void onClick(CustomButton button) {
                                        Log.d("CustomButton", "Init CUE Button clicked");
                                        // Log other relevant information
                                        initCue();
                                    }
                                });
                            }
                            if (buttonType.equals("setRef")) {
                                touchUI.setOnClickListener(new CustomButton.OnClickListener() {
                                    @Override
                                    public void onClick(CustomButton button) {
                                        Log.d("CustomButton", "setRef Button clicked");
                                        // Log other relevant information
                                        initFrame();
                                    }
                                });
                            }

                            //customTabView.setContentViewWithButtonType(buttonType, x, y, width, height, paramShortName, paramPath, i, colorR, colorG, colorB, colorA, initValues, tabViewName);
                        } else {
                            // Handle incorrect format
                            Log.d("Incorrect format", dataParamMotionButton);
                            tips.setText("Incorrect MotionButton metadata format");
                            return;
                        }
                    }

                    }
                }

                if (!cueIsOn ) {
                    if (newCueIsOn) {
                        tips.setText("You're using Cue, but forgot to declare /cue ?");
                        return;
                    }
                }


                if(cueIsOn && !newCueIsOn && !newCounterIsOn) {
                    nextCue.setVisibility(View.VISIBLE);
                    prevCue.setVisibility(View.VISIBLE);
                    initCue.setVisibility(View.VISIBLE);
                    cue.setVisibility(View.VISIBLE);
                    cueNext.setVisibility(View.VISIBLE);
                    cueText.setVisibility(View.VISIBLE);
                    cueNextText.setVisibility(View.VISIBLE);

                    scrollView.setVisibility(View.INVISIBLE);

                    //tips.setVisibility(View.VISIBLE);
                } else {
                    nextCue.setVisibility(View.INVISIBLE);
                    prevCue.setVisibility(View.INVISIBLE);
                    initCue.setVisibility(View.INVISIBLE);
                    cue.setVisibility(View.INVISIBLE);
                    cueNext.setVisibility(View.INVISIBLE);
                    cueText.setVisibility(View.INVISIBLE);
                    cueNextText.setVisibility(View.INVISIBLE);

                    scrollView.setVisibility(View.VISIBLE);
                    //tips.setVisibility(View.INVISIBLE);
                }


                if (touchGateIsOn || screenYIsOn || screenXIsOn || (cueIsOn && !newCueIsOn && !newCounterIsOn)) {

                    touche.setVisibility(View.INVISIBLE);
                } else {

                    touche.setVisibility(View.INVISIBLE);
                }


                if (cueIsOn || newCounterIsOn) {
                    tips.setVisibility(View.VISIBLE);
                    initCue();
                } else {
                    tips.setVisibility(View.INVISIBLE);
                }



            }
        });

        // Handle button click
        System.out.println("Button created");



    }


    public void checkAddress() {


        //for (int i = 0; i < dspFaustMotion.getParamsCount(); i++) {
        for (int i = 0; i < dspFaust.getParamsCount(); i++) {
            String Str = dspFaust.getMetadata(i, "showName");
            //String Str = dspFaustMotion.getMetadata(i, "showName");
            if (Str != null) {
                if (!Str.equals("")){
                    motionParamArray.add(Str);
                    motionParamAddress.add(dspFaust.getParamAddress(i));
                    //motionParamAddress.add(dspFaustMotion.getParamAddress(i));
                }
            }

        }

        //System.out.println(motionParamArray);
        //System.out.println(motionParamAddress);

        paramsOn = new boolean[motionParamArray.size()];

        for(int i = 0; i < motionParamArray.size(); i++) {
            RadioButton rdbtn = new RadioButton(this);
            rdbtn.setId(i);
            rdbtn.setTextColor(Color.WHITE);
            rdbtn.setText(motionParamArray.get(i));
            radioGroup.addView(rdbtn);
        }

        // PRINT ALL PARAMETRE ADDRESS
        for (int i = 0; i < dspFaust.getParamsCount(); i++) {
            //System.out.println(dspFaust.getParamAddress(i));

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

                cueList.clear();
                tipsList.clear();

                if (!TextUtils.isEmpty(dspFaust.getMetadata(i, "SHCUI"))) {
                    // Convert the metadata string to an NSString
                    String paramMetaString = dspFaust.getMetadata(i, "SHCUI");

                    // Split the string by space
                    String[] components = paramMetaString.split(" ");

                    // Extract the values
                    String buttonType = components[1];

                    if (!buttonType.equals("trigCue")) {
                        tips.setText("Cue metadata Only Support 'trigCue' option");
                        return;
                    }
                }


                if (!TextUtils.isEmpty(dspFaust.getMetadata(i, "touchCueManager"))) {
                    String dataParamMotionCue = dspFaust.getMetadata(i, "touchCueManager");
                    //  "{1: 'low'; 2:'mid'; 3: 'hi'}";

                    // Remove unnecessary characters
                    String cleanedString = dataParamMotionCue.replaceAll("[{}']", "");

                    // Split the string into key-value pairs
                    String[] pairs = cleanedString.split(";");

                    // Iterate through the key-value pairs and add them to the respective arrays
                    for (String pair : pairs) {
                        String[] keyValue = pair.split(":");
                        if (keyValue.length == 2) {
                            // Get the key and value
                            String key = keyValue[0].trim();
                            String rawValue = keyValue[1].trim();
                            String value = " " + rawValue;

                            // Check if the key is a non-negative integer
                            try {
                                int num = Integer.parseInt(key);
                                if (num >= dspFaust.getParamMin(i) && num <= dspFaust.getParamMax(i)) {
                                    cueList.add(key);
                                    tipsList.add("Cue " + key + " Tip: "+ value);
                                } else {
                                    // Integer is not within the valid range
                                    Log.e("Tag", "Invalid integer value: " + num);
                                    tips.setText("Invalid integer Cue meatadata value");
                                    return;
                                }
                            } catch (NumberFormatException e) {
                                // Handle incorrect format
                                Log.e("Tag", "Incorrect format: " + pair);
                                tips.setText("Incorrect Cue metadata format");
                                return;
                            }
                        } else {
                            // Handle incorrect format
                            Log.e("Tag", "Incorrect format: " + pair);
                            tips.setText("Incorrect Cue metadata format");
                            return;
                        }
                    }
                } else {
                    // Load cues from file
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

                }

                if (cueList.size() != tipsList.size()) {
                    tips.setText("!Num of cue and tips must be same!");
                    return;
                }

                System.out.println(cueList);
                System.out.println(tipsList);

            } else if (Str.endsWith("/tip")) {
                tipIsOn = true;
                tipAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/yaw")) {
                yawIsOn = true;
                yawAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/pitch")) {
                pitchIsOn = true;
                pitchAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/roll")) {
                rollIsOn = true;
                rollAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/useraccx")) {
                useraccxIsOn = true;
                useraccxAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/useraccy")) {
                useraccyIsOn = true;
                useraccyAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/useraccz")) {
                useracczIsOn = true;
                useracczAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/quaternionw")) {
                quaternionwIsOn = true;
                quaternionwAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/quaternionx")) {
                quaternionxIsOn = true;
                quaternionxAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/quaterniony")) {
                quaternionyIsOn = true;
                quaternionyAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/quaternionz")) {
                quaternionzIsOn = true;
                quaternionzAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/cue")) {
                cueIsOn = true;
                cueAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/state")) {
                stateIsOn = true;
                stateAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/setref_comp")) {
                setref_compIsOn = true;
                setref_compAddress = dspFaust.getParamAddress(i);
            } else if (Str.endsWith("/setref_rota")) {
                setref_rotaIsOn = true;
                setref_rotaAddress = dspFaust.getParamAddress(i);
            }

        }


    }


    public float scaleBackValue(float value, float min, float max) {
        return (value - min) / (max - min);
    }

    public void goCue(){
        cueIndex = cueIndexNext;
        cue.setText(cueList.get(cueIndex));
        tips.setText(tipsList.get(cueIndexNext));

        dspFaust.setParamValue(cueAddress,Float.valueOf(cueList.get(cueIndex)));

        if (cueIndexNext < cueList.size() - 1) {
            cueIndexNext++;
            cueNext.setText(cueList.get(cueIndexNext));
        }
    }

    public void nextCue(){
        if (cueIndexNext < cueList.size() -1) {
            cueIndexNext++;
            cueNext.setText(cueList.get(cueIndexNext));
            tips.setText(tipsList.get(cueIndexNext));
        }
    }

    public void prevCue(){
        if (cueIndexNext > 0) {
            cueIndexNext--;
            cueNext.setText(cueList.get(cueIndexNext));
            tips.setText(tipsList.get(cueIndexNext));
        }
    }

    public void initCue(){

        if (cueIsOn) {
            cueIndex = 0;
            cueIndexNext = 1;
            cue.setText(cueList.get(cueIndex));
            cueNext.setText(cueList.get(cueIndexNext));
            tips.setText(tipsList.get(cueIndex));

            dspFaust.setParamValue(cueAddress,Float.valueOf(cueList.get(cueIndex)));
            Log.d("initCue", "initCue");
        }

    }

    @Override

    public boolean onTouchEvent(MotionEvent event) {
        int action = event.getAction() & MotionEvent.ACTION_MASK;
        int touchCounter = event.getPointerCount();
        //touche = (ImageView) findViewById(R.id.touche);


        switch(action) {

            case MotionEvent.ACTION_DOWN: {


                if (touchCounter == 1) {
                    float pointerIndex = event.getX(0);
                    float pointerIndey = event.getY(0);
                    if (pointerIndey <= scrHeight / 2) {

                        float screenX = pointerIndex / scrWidth;
                        float screenY = pointerIndey/(scrHeight/2);

                        if (touchGateIsOn) {
                            touche.setVisibility(View.VISIBLE);
                            dspFaust.setParamValue(touchGateAddress, 1);
                        }
                        if (cueIsOn && !newCueIsOn) {
                            touche.setVisibility(View.VISIBLE);
                            goCue();
                        }

                        if (screenXIsOn) {
                            touche.setVisibility(View.VISIBLE);
                            dspFaust.setParamValue(screenXAddress, screenX);
                        }
                        if (screenYIsOn) {
                            touche.setVisibility(View.VISIBLE);
                            dspFaust.setParamValue(screenYAddress, (1.f-screenY));
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

                        float screenX = pointerIndex / scrWidth;
                        float screenY = pointerIndey/(scrHeight/2);
                        if (screenXIsOn) {
                            dspFaust.setParamValue(screenXAddress, screenX);
                        }
                        if (screenYIsOn) {
                            dspFaust.setParamValue(screenYAddress, (1.f-screenY));
                        }
                    }
                }

                break;
            }


            case MotionEvent.ACTION_UP: {

                if (touchCounter == 1) {

                    float pointerIndex = event.getX(0);
                    float pointerIndey = event.getY(0);
                    if (pointerIndey <= scrHeight / 2) {

                        float screenX = pointerIndex / scrWidth;
                        float screenY = pointerIndey/(scrHeight/2);
                        if (cueIsOn && !newCueIsOn) {
                            touche.setVisibility(View.INVISIBLE);
                        }
                        if (touchGateIsOn) {
                            touche.setVisibility(View.INVISIBLE);
                            dspFaust.setParamValue(touchGateAddress, 0);
                        }

                        if (screenXIsOn) {
                            touche.setVisibility(View.INVISIBLE);
                            dspFaust.setParamValue(screenXAddress, screenX);
                        }
                        if (screenYIsOn) {
                            touche.setVisibility(View.INVISIBLE);
                            dspFaust.setParamValue(screenYAddress, (1.f-screenY));
                        }
                    } else {
                        if (touchGateIsOn) {
                            touche.setVisibility(View.INVISIBLE);
                        }

                        if (screenXIsOn) {
                            touche.setVisibility(View.INVISIBLE);
                        }
                        if (screenYIsOn) {
                            touche.setVisibility(View.INVISIBLE);
                        }
                        if (cueIsOn && !newCueIsOn) {
                            touche.setVisibility(View.INVISIBLE);
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


    //long currentTime= System.currentTimeMillis();  //comment for now

    //if ((currentTime-lastDate) > updateInterval) {

        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            // Update acc at sensor rate

            dspFaust.propagateAcc(0, -event.values[0]);
            dspFaust.propagateAcc(1, -event.values[1]);
            dspFaust.propagateAcc(2, -event.values[2]);

            dspFaustMotion.propagateAcc(0, -event.values[0]);
            dspFaustMotion.propagateAcc(1, -event.values[1]);
            dspFaustMotion.propagateAcc(2, -event.values[2]);

        }

        if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
            // Update gyr at sensor rate

            dspFaust.propagateGyr(0, -event.values[0]);
            dspFaust.propagateGyr(1, -event.values[1]);
            dspFaust.propagateGyr(2, -event.values[2]);

            dspFaustMotion.propagateGyr(0, -event.values[0]);
            dspFaustMotion.propagateGyr(1, -event.values[1]);
            dspFaustMotion.propagateGyr(2, -event.values[2]);

        }


        if (event.sensor.getType() == Sensor.TYPE_ROTATION_VECTOR) {

            // Task 5.4: Skip motion rendering if DSP is not running to prevent OSC crash
            // This prevents crashes when sensor events fire while DSP is stopped (e.g., during Settings)
            if (dspFaust == null || !dspFaust.isRunning()) {
                Log.d("Faust", "Skipping motion render - DSP not running");
                return;
            }

            // Update rotation matrix at sensor rate
            SensorManager.getRotationMatrixFromVector(rotationMatrix, event.values);

            // iOS uses raw rotation matrix values (m11, m12, m13, m21, m22, m23, m31, m32, m33)
            // Android SensorManager.getRotationMatrixFromVector returns matrix in row-major order:
            // rotationMatrix[0]=m11, rotationMatrix[1]=m12, rotationMatrix[2]=m13,
            // rotationMatrix[3]=m21, rotationMatrix[4]=m22, rotationMatrix[5]=m23,
            // rotationMatrix[6]=m31, rotationMatrix[7]=m32, rotationMatrix[8]=m33
            //
            // COORDINATE SYSTEM FIX:
            // Android and iOS have different device coordinate systems.
            // For DspFaustMotion output parameters, we need to swap X and Y axes.
            // This is done by swapping the first two columns of the rotation matrix:
            // - Column 1 (X-axis): rotationMatrix[0], rotationMatrix[3], rotationMatrix[6] <-> Column 2 (Y-axis): rotationMatrix[1], rotationMatrix[4], rotationMatrix[7]
            // Result: [m12, m11, m13, m22, m21, m23, m32, m31, m33]
            
            // Pass to DspFaust.motionRender with X/Y axes swapped
            dspFaust.motionRender(
                    rotationMatrix[1], rotationMatrix[0], rotationMatrix[2],  // Swap m11 and m12
                    rotationMatrix[4], rotationMatrix[3], rotationMatrix[5],  // Swap m21 and m22
                    rotationMatrix[7], rotationMatrix[6], rotationMatrix[8]); // Swap m31 and m32

            // Apply the reference rotation matrix to the current rotation matrix
            if (referenceRotationMatrix != null && rotationMatrix != null) {
                if (referenceRotationMatrix.length == 9 && rotationMatrix.length == 9) {
                    float[] tempMatrix = new float[9];
                    float[] invertedReferenceRotationMatrix = new float[9];

                    // Invert the reference rotation matrix
                    boolean success = invert3x3Matrix(referenceRotationMatrix,invertedReferenceRotationMatrix);
                    if (!success) {
                        Log.e("Matrix", "Failed to invert reference rotation matrix");
                        return; // Exit the method or handle the error accordingly
                    }

                    // Multiply the current rotation matrix by the inverted reference rotation matrix
                    multiply3x3Matrices(rotationMatrix, invertedReferenceRotationMatrix, tempMatrix);

                    // Copy the result back to the rotationMatrix
                    System.arraycopy(tempMatrix, 0, rotationMatrix, 0, tempMatrix.length);

                    // Log the resulting rotation matrix for debugging
                    //Log.d("Matrix", "Resulting rotation matrix after applying reference matrix: " + Arrays.toString(rotationMatrix));
                } else {
                    Log.e("Matrix", "Invalid matrix dimensions");
                }
            } else {
                Log.e("Matrix", "Rotation matrices are null");
            }


            SensorManager.getOrientation(rotationMatrix, mOrientation);

            //SensorManager.getQuaternionFromVector(mQuaternion, event.values);

            float m00 = dspFaust.getRotationMatrix(0,0);
            float m01 = dspFaust.getRotationMatrix(0,1);
            float m02 = dspFaust.getRotationMatrix(0,2);
            float m10 = dspFaust.getRotationMatrix(1,0);
            float m11 = dspFaust.getRotationMatrix(1,1);
            float m12 = dspFaust.getRotationMatrix(1,2);
            float m20 = dspFaust.getRotationMatrix(2,0);
            float m21 = dspFaust.getRotationMatrix(2,1);
            float m22 = dspFaust.getRotationMatrix(2,2);

            float tr = m00 + m11 + m22;

            if (tr > 0) {
                float S = (float) sqrt(tr+1.0) * 2; // S=4*qw
                mQuaternion[0] = 0.25f * S;
                mQuaternion[1] = (m21 - m12) / S;
                mQuaternion[2] = (m02 - m20) / S;
                mQuaternion[3] = (m10 - m01) / S;
            } else if ((m00 > m11)&(m00 > m22)) {
                float S = (float) sqrt(1.0 + m00 - m11 - m22) * 2; // S=4*qx
                mQuaternion[0]  = (m21 - m12) / S;
                mQuaternion[1]  = 0.25f * S;
                mQuaternion[2]  = (m01 + m10) / S;
                mQuaternion[3]  = (m02 + m20) / S;
            } else if (m11 > m22) {
                float S = (float) sqrt(1.0 + m11 - m00 - m22) * 2; // S=4*qy
                mQuaternion[0] = (m02 - m20) / S;
                mQuaternion[1] = (m01 + m10) / S;
                mQuaternion[2] = 0.25f * S;
                mQuaternion[3] = (m12 + m21) / S;
            } else {
                float S = (float) sqrt(1.0 + m22 - m00 - m11) * 2; // S=4*qz
                mQuaternion[0] = (m10 - m01) / S;
                mQuaternion[1] = (m02 + m20) / S;
                mQuaternion[2] = (m12 + m21) / S;
                mQuaternion[3] = 0.25f * S;
            }


            if (yawIsOn) {
                dspFaust.setParamValue(yawAddress, mOrientation[0]);
            }
            if (pitchIsOn) {
                dspFaust.setParamValue(pitchAddress, mOrientation[1]);
            }
            if (rollIsOn) {
                dspFaust.setParamValue(rollAddress, mOrientation[2]);
            }
            if (quaternionwIsOn) {
                dspFaust.setParamValue(quaternionwAddress, mQuaternion[0]);
            }
            if (quaternionxIsOn) {
                dspFaust.setParamValue(quaternionxAddress, mQuaternion[1]*(-1.f));
            }
            if (quaternionyIsOn) {
                dspFaust.setParamValue(quaternionyAddress, mQuaternion[2]*(-1.f));
            }
            if (quaternionzIsOn) {
                dspFaust.setParamValue(quaternionzAddress, mQuaternion[3]*(-1.f));
            }



        }

        if (event.sensor.getType() == Sensor.TYPE_ORIENTATION) {


            magnetic = event.values[0];

            if (magnetic-offset>0) {
                magneticNormal = magnetic-offset;
            } else {
                magneticNormal = magnetic-offset+360.00f;
            }

            if (magneticNormal<=180) {
                magneticNew = magneticNormal /180.00f;
            } else {
                magneticNew = (360.00f - magneticNormal)/180.00f;
            }

            //Log.d("magneticNew",Float.toString(magneticNew));

            // calcul magneticBinaural: s'initialise comme mangeticNew via l'offset mais conserve l'orientation relative et est adapté au spat de faust
            // on appelera "ibinaural" ce paramter
            // position initial => 0.25
            // position tourner à gauche => 0.
            // position tourner à droite => 0.5
            // position opposée => 0.75
            if (magnetic-offset>0) {
                magneticDeg = magnetic-offset;
            } else {
                magneticDeg = magnetic-offset+360.00f;
            }

            double nn = Math.IEEEremainder((double)(((360+magneticDeg)/360)+0.25f), (double)1.f);

            if (nn<0.f){
                magneticBinaural = (float)(1+nn);
            } else {
                magneticBinaural = (float) nn;
            }

            //Log.d("magneticBinaural",Float.toString(magneticBinaural));

            if (magneticHeadingIsOn) {
                dspFaust.setParamValue(magneticHeadingAddress, magneticNew);
            }


        }


        updateGUI();

        //lastDate = currentTime;

    //}

}
};



    private void updateGUI(){

    if (stateIsOn) {
        tips.setText("State = " + dspFaust.getParamValue(stateAddress));
    }

    if (setref_compIsOn && dspFaust.getParamValue(setref_compAddress)==1) {

        if (cnt<2) {
            offset = magnetic;
            Log.d("motion","initCompass");
            cnt++;
        }
    } else{
        cnt=1;
    }

    if (setref_rotaIsOn && dspFaust.getParamValue(setref_rotaAddress)==1) {
        if (cnt2<2) {
            initFrame();
            Log.d("motion","initRotation");
            cnt2++;
        }
    } else{
        cnt2=1;
    }

    for (CustomButton bargraph : customBargraphs) {
        // Fetch the value from your data source
        float newValue = scaleBackValue(dspFaust.getParamValue(bargraph.pathForButton), dspFaust.getParamMin(bargraph.pathForButton), dspFaust.getParamMax(bargraph.pathForButton));

        if (bargraph.customButtonType.equals("hbargraph")){
            bargraph.updateVumeterXButton(newValue);
        } else if (bargraph.customButtonType.equals("vbargraph")){
            bargraph.updateVumeterYButton(newValue);
        }
    }

}


// set Ref function
private void initFrame () {

if (sensorManager!=null){

  if (dspFaust!=null){
      dspFaust.initFrame();
  }

  if (rotationMatrix != null) {
      System.arraycopy(rotationMatrix, 0, referenceRotationMatrix, 0, rotationMatrix.length);
  }

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

    // Invert a 3x3 matrix manually
    public static boolean invert3x3Matrix(float[] src, float[] dst) {
        if (src.length != 9 || dst.length != 9) {
            return false; // Invalid matrix dimensions
        }

        // Calculate the determinant of the matrix
        float determinant = src[0] * (src[4] * src[8] - src[7] * src[5])
                - src[1] * (src[3] * src[8] - src[5] * src[6])
                + src[2] * (src[3] * src[7] - src[4] * src[6]);

        // Check if the determinant is zero (matrix is not invertible)
        if (determinant == 0.0f) {
            return false;
        }

        // Calculate the reciprocal of the determinant
        float invDet = 1.0f / determinant;

        // Calculate the elements of the inverted matrix
        dst[0] = (src[4] * src[8] - src[5] * src[7]) * invDet;
        dst[1] = (src[2] * src[7] - src[1] * src[8]) * invDet;
        dst[2] = (src[1] * src[5] - src[2] * src[4]) * invDet;
        dst[3] = (src[5] * src[6] - src[3] * src[8]) * invDet;
        dst[4] = (src[0] * src[8] - src[2] * src[6]) * invDet;
        dst[5] = (src[2] * src[3] - src[0] * src[5]) * invDet;
        dst[6] = (src[3] * src[7] - src[4] * src[6]) * invDet;
        dst[7] = (src[1] * src[6] - src[0] * src[7]) * invDet;
        dst[8] = (src[0] * src[4] - src[1] * src[3]) * invDet;

        return true; // Inversion successful
    }

    private void multiply3x3Matrices(float[] A, float[] B, float[] result) {
        // Calculate each element of the resulting matrix
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result[i * 3 + j] = A[i * 3] * B[j] + A[i * 3 + 1] * B[j + 3] + A[i * 3 + 2] * B[j + 6];
            }
        }
    }

    private void displayTitle() {
        String titleString = null;

        // Get the name meta from dspFaust
        String name = dspFaust.getMeta("name");
        if (name != null) {
            titleString = name;
        }

        // Append author meta to the titleString
        String author = dspFaust.getMeta("author");
        if (author != null) {
            if (titleString != null) {
                titleString += " | " + author;
            } else {
                titleString = author;
            }
        }

        // If titleString is still null, set a default title
        if (titleString == null) {
            titleString = "faust2smartphone | Allen";
        }

        // Set the title text to the TextView
        appName.setText(titleString);
        appName.setGravity(Gravity.CENTER);
        appName.setSingleLine(true);
        appName.setEllipsize(TextUtils.TruncateAt.END);
    }

    private void saveFaustParams() {

        for (int i=0; i<dspFaust.getParamsCount(); i++){
            SharedPreWriteFloat(dspFaust.getParamAddress(i), dspFaust.getParamValue(i));
        }

        Log.d("Faust", "saveFaustParams");

    }



    private void loadDefaultParams() {

for (int i=0; i<motionParamAddress.size(); i++){
dspFaust.setParamValue(motionParamAddress.get(i),
SharedPrefRead(motionParamArray.get(i),dspFaust.getParamInit(motionParamAddress.get(i))));
//SharedPrefRead(motionParamArray.get(i),dspFaustMotion.getParamInit(motionParamAddress.get(i))));
}

        for (int i=0; i<dspFaust.getParamsCount(); i++){
            dspFaust.setParamValue(dspFaust.getParamAddress(i), SharedPrefRead(dspFaust.getParamAddress(i),dspFaust.getParamInit(i)));
        }

        Log.d("Faust", "readFaustParams");

}

    private void resetOSCParams() {

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

private void resetParams() {

//SharedPreClear();

    //for (int i=0; i<dspFaust.getParamsCount(); i++){
        //SharedPreWriteFloat(dspFaust.getParamAddress(i), dspFaust.getParamInit(i));
    //}

    for (int i=0; i<motionParamAddress.size(); i++){
        dspFaust.setParamValue(motionParamAddress.get(i), dspFaust.getParamInit(motionParamAddress.get(i)));
        SharedPreWriteFloat(motionParamArray.get(i), dspFaust.getParamInit((motionParamAddress.get(i))));
        //SharedPreWriteFloat(motionParamArray.get(i), dspFaustMotion.getParamInit((motionParamAddress.get(i))));
    }


}

    /**
     * Calculate sensor update interval to match iOS behavior.
     * iOS uses: updateInterval = 1.0/(SR/blockSize)
     * Convert to microseconds for Android SensorManager.
     */
    private void calculateSensorUpdateInterval() {
        // Match iOS: updateInterval = 1.0/(SR/blockSize)
        // Convert to microseconds for Android SensorManager
        float updateIntervalSeconds = 1.0f / (SR / (float)blockSize);
        sensorUpdateIntervalMicros = (int)(updateIntervalSeconds * 1000000);
        float updateRateHz = 1000000.0f / sensorUpdateIntervalMicros;
        Log.d("Faust", "Sensor update interval: " + sensorUpdateIntervalMicros + " μs (" + updateRateHz + " Hz)");
    }


@Override
    protected void onPause() {
        Log.d("Faust", "onPause");
        super.onPause();
        if(permissionToRecordAccepted) {

        dspFaustMotion.stop();
        dspFaust.stop();
        saveFaustParams();


        }

    }

@Override
    protected void onResume() {
        Log.d("Faust", "onResume");
        super.onResume();
        if(permissionToRecordAccepted) {

        if (!dspFaustMotion.isRunning()) {

        dspFaustMotion.start();

            Log.d("Faust", "dspFaustMotion onResume");
        }

        if (!dspFaust.isRunning()) {

        SharedPrefInit(getApplicationContext());

        if (dspFaust.getOSCIsOn()) {
        oscAddress = SharedPrefRead("oscAddress","192.168.1.5");
        oscInPort = Integer.parseInt(SharedPrefRead("oscInPort","5510"));
        oscOutPort = Integer.parseInt(SharedPrefRead("oscOutPort","5511"));

        dspFaust.setOSCValue(oscAddress, oscInPort, oscOutPort);

            Log.d("Faust", "dspFaust osc onResume");

        }

        initFrame();

        dspFaust.start();

            Log.d("Faust", "dspFaust onResume");

        checkAddress();
        dspFaust.checkAdress();
        loadDefaultParams();

        }


        }
    }

    // Task 5.5: Handle keyboard lifecycle impact on OSC state
    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        
        if (hasFocus && permissionToRecordAccepted) {
            // Window focus returned (e.g., keyboard closed)
            // Verify OSC state and re-initialize if needed
            // NOTE: setOSCValue() only works when DSP is NOT running
            // Since DSP is likely running here, we skip OSC re-init
            // The close handlers already handle OSC re-initialization
            if (dspFaust != null && dspFaust.getOSCIsOn()) {
                Log.d("Faust", "Window focus changed, DSP running: " + dspFaust.isRunning());
                // OSC re-initialization is handled by Settings close handlers
                // No action needed here
            }
        }
    }

    // ── Setting panel ────────────────────────────────────────────

    private void showSettingView() {
        // CRITICAL: Do NOT stop/start DSP when opening/closing Settings
        // DSP stop() calls fOSCUI->stop() which triggers TLS access and causes SIGBUS crash
        // DSP start() calls fOSCUI->run() which also triggers TLS access
        // Solution: Keep DSP running, only unregister sensors to prevent motion rendering
        
        // Unregister sensors to prevent motion rendering while Settings is open
        if (sensorManager != null) {
            sensorManager.unregisterListener(mSensorListener);
            Log.d("Faust", "Sensors unregistered for Settings");
        }
        
        // Do NOT stop DSP - keep it running to avoid OSC TLS issues
        // The sensor unregistration prevents motion rendering
        
        // Add overlay to the Activity content view
        final ViewGroup contentView = findViewById(android.R.id.content);

        final FrameLayout overlay = new FrameLayout(this);
        overlay.setBackgroundColor(Color.argb(240, 10, 10, 10));
        
        // Click outside to close
        overlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                contentView.removeView(overlay);
                
                // Re-register sensors (DSP is still running, no need to restart it)
                // CRITICAL: Do NOT call dspFaust.start() - it triggers OSC TLS access
                if (sensorManager != null) {
                    sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                            Sensor.TYPE_ACCELEROMETER), sensorUpdateIntervalMicros);
                    sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                            Sensor.TYPE_GYROSCOPE), sensorUpdateIntervalMicros);
                    sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                            Sensor.TYPE_ROTATION_VECTOR), sensorUpdateIntervalMicros);
                    Log.d("Faust", "Sensors re-registered after Settings close");
                }
                
                // Refresh SHCUI to fix black screen issue after keyboard input
                refreshSHCUI();
                
                // Multiple delayed refreshes to ensure keyboard is fully closed
                if (scrollView != null) {
                    scrollView.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            refreshSHCUI();
                        }
                    }, 200);
                    
                    // Second delayed refresh for slower keyboard animations
                    scrollView.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            refreshSHCUI();
                        }
                    }, 400);
                }
            }
        });

        LinearLayout container = new LinearLayout(this);
        container.setOrientation(LinearLayout.VERTICAL);
        container.setPadding(24, 48, 24, 24);
        
        // Prevent clicks on container from closing overlay
        container.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Do nothing - just consume the click
            }
        });

        // ── Top bar ──────────────────────────────────────────────
        LinearLayout topBar = new LinearLayout(this);
        topBar.setOrientation(LinearLayout.HORIZONTAL);

        TextView titleTv = new TextView(this);
        titleTv.setText("Settings");
        titleTv.setTextColor(Color.WHITE);
        titleTv.setTextSize(18);
        LinearLayout.LayoutParams titleLp = new LinearLayout.LayoutParams(0,
                ViewGroup.LayoutParams.WRAP_CONTENT, 1f);
        titleTv.setLayoutParams(titleLp);
        topBar.addView(titleTv);

        Button closeBtn = new Button(this);
        closeBtn.setText("✕");
        closeBtn.setTextColor(Color.WHITE);
        closeBtn.setBackgroundColor(Color.TRANSPARENT);
        final FrameLayout finalOverlay = overlay;
        closeBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                contentView.removeView(finalOverlay);
                
                // Re-register sensors (DSP is still running, no need to restart it)
                // CRITICAL: Do NOT call dspFaust.start() - it triggers OSC TLS access
                if (sensorManager != null) {
                    sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                            Sensor.TYPE_ACCELEROMETER), sensorUpdateIntervalMicros);
                    sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                            Sensor.TYPE_GYROSCOPE), sensorUpdateIntervalMicros);
                    sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                            Sensor.TYPE_ROTATION_VECTOR), sensorUpdateIntervalMicros);
                    Log.d("Faust", "Sensors re-registered after Settings close");
                }
                
                // Refresh SHCUI to fix black screen issue after keyboard input
                refreshSHCUI();
                
                // Multiple delayed refreshes to ensure keyboard is fully closed
                if (scrollView != null) {
                    scrollView.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            refreshSHCUI();
                        }
                    }, 200);
                    
                    // Second delayed refresh for slower keyboard animations
                    scrollView.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            refreshSHCUI();
                        }
                    }, 400);
                }
            }
        });
        topBar.addView(closeBtn);
        container.addView(topBar);

        // ── Content area ─────────────────────────────────────────
        ScrollView contentScroll = new ScrollView(this);
        LinearLayout.LayoutParams scrollLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, 0, 1f);
        contentScroll.setLayoutParams(scrollLp);

        LinearLayout settingPage = buildSettingPage();
        contentScroll.addView(settingPage);
        container.addView(contentScroll);

        LinearLayout.LayoutParams containerLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        container.setLayoutParams(containerLp);
        overlay.addView(container);
        
        // CRITICAL: Do NOT add OnAttachStateChangeListener - causes SIGBUS crash
        // Even just logging in onViewDetachedFromWindow triggers OSC TLS access
        // The overlay detach event itself seems to trigger OSC library cleanup
        
        contentView.addView(overlay);
    }

    private LinearLayout buildSettingPage() {
        LinearLayout page = new LinearLayout(this);
        page.setOrientation(LinearLayout.VERTICAL);
        page.setPadding(0, 8, 0, 8);

        // ── Section 1: Motion Lib Parameters ──────────────────────
        addSectionTitle(page, "Motion Lib Parameters");

        // Get motion lib parameters with showName metadata
        ArrayList<String> motionLibNames = new ArrayList<>();
        ArrayList<String> motionLibAddrs = new ArrayList<>();
        ArrayList<Float> motionLibMins = new ArrayList<>();
        ArrayList<Float> motionLibMaxs = new ArrayList<>();
        ArrayList<Float> motionLibInits = new ArrayList<>();

        if (dspFaustMotion != null) {
            int motionCount = dspFaustMotion.getParamsCount();
            for (int i = 0; i < motionCount; i++) {
                String showName = dspFaustMotion.getMetadata(i, "showName");
                if (showName == null || showName.isEmpty()) continue;
                
                motionLibNames.add(showName);
                motionLibAddrs.add(dspFaustMotion.getParamAddress(i));
                motionLibMins.add(dspFaustMotion.getParamMin(i));
                motionLibMaxs.add(dspFaustMotion.getParamMax(i));
                motionLibInits.add(dspFaustMotion.getParamInit(i));
            }
        }

        if (!motionLibNames.isEmpty()) {
            Spinner motionSpinner = new Spinner(this);
            motionSpinner.setPrompt("Select Motion Lib Parameter");
            ArrayAdapter<String> motionAdapter = createWhiteTextAdapter(motionLibNames);
            motionSpinner.setAdapter(motionAdapter);
            motionSpinner.setSelection(Math.min(motionLibSelectedIdx, motionLibNames.size() - 1));
            
            // Add margins for spacing
            LinearLayout.LayoutParams spinnerLp = new LinearLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
            spinnerLp.setMargins(0, 8, 0, 8);
            motionSpinner.setLayoutParams(spinnerLp);
            
            page.addView(motionSpinner);

            final EditText motionEt = new EditText(this);
            motionEt.setTextColor(Color.WHITE);
            motionEt.setHintTextColor(Color.GRAY);
            motionEt.setBackgroundColor(Color.argb(180, 40, 40, 40));
            motionEt.setInputType(InputType.TYPE_CLASS_NUMBER
                    | InputType.TYPE_NUMBER_FLAG_DECIMAL
                    | InputType.TYPE_NUMBER_FLAG_SIGNED);
            motionEt.setPadding(12, 8, 12, 8);

            if (motionLibSelectedIdx < motionLibAddrs.size()) {
                motionEt.setText(String.valueOf(
                        dspFaustMotion.getParamValue(motionLibAddrs.get(motionLibSelectedIdx))));
            }

            final ArrayList<String> finalMotionLibAddrs = motionLibAddrs;
            final ArrayList<String> finalMotionLibNames = motionLibNames;
            final ArrayList<Float> finalMotionLibMins = motionLibMins;
            final ArrayList<Float> finalMotionLibMaxs = motionLibMaxs;
            final ArrayList<Float> finalMotionLibInits = motionLibInits;

            motionSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
                @Override public void onItemSelected(AdapterView<?> p, View v, int pos, long id) {
                    motionLibSelectedIdx = pos;
                    motionEt.setText(String.valueOf(dspFaustMotion.getParamValue(finalMotionLibAddrs.get(pos))));
                }
                @Override public void onNothingSelected(AdapterView<?> p) {}
            });
            page.addView(motionEt);

            LinearLayout motionBtns = new LinearLayout(this);
            motionBtns.setOrientation(LinearLayout.HORIZONTAL);

            final Spinner finalMotionSpinner = motionSpinner;
            Button motionSet = makeSmallButton("Set", Color.argb(200, 40, 100, 40));
            motionSet.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    int idx = finalMotionSpinner.getSelectedItemPosition();
                    if (idx < 0 || idx >= finalMotionLibAddrs.size()) return;
                    try {
                        float val = Float.parseFloat(motionEt.getText().toString());
                        val = Math.max(finalMotionLibMins.get(idx), Math.min(finalMotionLibMaxs.get(idx), val));
                        dspFaustMotion.setParamValue(finalMotionLibAddrs.get(idx), val);
                        SharedPreWriteFloat(finalMotionLibNames.get(idx), val);
                    } catch (NumberFormatException ignored) {}
                }
            });

            Button motionReset = makeSmallButton("↺ Reset", Color.argb(200, 100, 40, 40));
            motionReset.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    int idx = finalMotionSpinner.getSelectedItemPosition();
                    if (idx < 0 || idx >= finalMotionLibAddrs.size()) return;
                    float init = finalMotionLibInits.get(idx);
                    dspFaustMotion.setParamValue(finalMotionLibAddrs.get(idx), init);
                    motionEt.setText(String.valueOf(init));
                    SharedPreWriteFloat(finalMotionLibNames.get(idx), init);
                }
            });

            motionBtns.addView(motionSet);
            motionBtns.addView(motionReset);
            page.addView(motionBtns);
        } else {
            addGrayNote(page, "No Motion Lib parameters available");
        }

        // ── Section 2: DSP Parameters ─────────────────────────────
        addSectionTitle(page, "DSP Parameters");

        if (!motionParamArray.isEmpty()) {
            Spinner dspSpinner = new Spinner(this);
            dspSpinner.setPrompt("Select DSP Parameter");
            ArrayAdapter<String> dspAdapter = createWhiteTextAdapter(motionParamArray);
            dspSpinner.setAdapter(dspAdapter);
            dspSpinner.setSelection(Math.min(dspParamSelectedIdx, motionParamArray.size() - 1));
            
            // Add margins for spacing
            LinearLayout.LayoutParams spinnerLp = new LinearLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
            spinnerLp.setMargins(0, 8, 0, 8);
            dspSpinner.setLayoutParams(spinnerLp);
            
            page.addView(dspSpinner);

            final EditText dspEt = new EditText(this);
            dspEt.setTextColor(Color.WHITE);
            dspEt.setHintTextColor(Color.GRAY);
            dspEt.setBackgroundColor(Color.argb(180, 40, 40, 40));
            dspEt.setInputType(InputType.TYPE_CLASS_NUMBER
                    | InputType.TYPE_NUMBER_FLAG_DECIMAL
                    | InputType.TYPE_NUMBER_FLAG_SIGNED);
            dspEt.setPadding(12, 8, 12, 8);

            if (dspParamSelectedIdx < motionParamAddress.size()) {
                dspEt.setText(String.valueOf(
                        dspFaust.getParamValue(motionParamAddress.get(dspParamSelectedIdx))));
            }

            final ArrayList<String> finalMotionParamAddress = motionParamAddress;
            final ArrayList<String> finalMotionParamArray = motionParamArray;

            dspSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
                @Override public void onItemSelected(AdapterView<?> p, View v, int pos, long id) {
                    dspParamSelectedIdx = pos;
                    if (pos < finalMotionParamAddress.size()) {
                        dspEt.setText(String.valueOf(
                                dspFaust.getParamValue(finalMotionParamAddress.get(pos))));
                    }
                }
                @Override public void onNothingSelected(AdapterView<?> p) {}
            });
            page.addView(dspEt);

            LinearLayout dspBtns = new LinearLayout(this);
            dspBtns.setOrientation(LinearLayout.HORIZONTAL);

            final Spinner finalDspSpinner = dspSpinner;
            Button dspSet = makeSmallButton("Set", Color.argb(200, 40, 100, 40));
            dspSet.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    int idx = finalDspSpinner.getSelectedItemPosition();
                    if (idx < 0 || idx >= finalMotionParamAddress.size()) return;
                    try {
                        float val = Float.parseFloat(dspEt.getText().toString());
                        dspFaust.setParamValue(finalMotionParamAddress.get(idx), val);
                        SharedPreWriteFloat(finalMotionParamArray.get(idx), val);
                    } catch (NumberFormatException ignored) {}
                }
            });

            Button dspReset = makeSmallButton("↺ Reset", Color.argb(200, 100, 40, 40));
            dspReset.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    int idx = finalDspSpinner.getSelectedItemPosition();
                    if (idx < 0 || idx >= finalMotionParamAddress.size()) return;
                    float init = dspFaust.getParamInit(idx);
                    dspFaust.setParamValue(finalMotionParamAddress.get(idx), init);
                    dspEt.setText(String.valueOf(init));
                    SharedPreWriteFloat(finalMotionParamArray.get(idx), init);
                }
            });

            dspBtns.addView(dspSet);
            dspBtns.addView(dspReset);
            page.addView(dspBtns);
        } else {
            addGrayNote(page, "No DSP parameters available");
        }

        // ── setRef button ─────────────────────────────────────────
        Button setRefBtn = makeSmallButton("Set Reference Orientation", Color.argb(200, 60, 60, 120));
        setRefBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                initFrame();
            }
        });
        LinearLayout.LayoutParams refLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        refLp.setMargins(0, 16, 0, 4);
        setRefBtn.setLayoutParams(refLp);
        page.addView(setRefBtn);

        // ── OSC section (conditional) ─────────────────────────────
        if (dspFaust != null && dspFaust.getOSCIsOn()) {
            addSectionTitle(page, "OSC Configuration");

            final EditText etIp  = makeEditRow(page, "IP Address",
                    SharedPrefRead("oscAddress", "192.168.1.5"));
            final EditText etIn  = makeEditRow(page, "Input Port",
                    SharedPrefRead("oscInPort", "5510"));
            final EditText etOut = makeEditRow(page, "Output Port",
                    SharedPrefRead("oscOutPort", "5511"));

            Button oscSet = makeSmallButton("Set OSC", Color.argb(200, 40, 100, 100));
            oscSet.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    String ip  = etIp.getText().toString().trim();
                    String in  = etIn.getText().toString().trim();
                    String out = etOut.getText().toString().trim();
                    if (ip.isEmpty()) ip = "192.168.1.5";
                    if (in.isEmpty()) in = "5510";
                    if (out.isEmpty()) out = "5511";
                    dspFaust.setOSCValue(ip, in, out);
                    SharedPrefWriteString("oscAddress", ip);
                    SharedPrefWriteString("oscInPort", in);
                    SharedPrefWriteString("oscOutPort", out);
                    Toast.makeText(MainActivity.this, "OSC set: " + ip + " in=" + in + " out=" + out + "\nRestart app to activate the new config",
                            Toast.LENGTH_LONG).show();
                }
            });
            LinearLayout.LayoutParams oscBtnLp = new LinearLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
            oscBtnLp.setMargins(0, 8, 0, 4);
            oscSet.setLayoutParams(oscBtnLp);
            page.addView(oscSet);
        }

        // ── Audio info ────────────────────────────────────────────
        addSectionTitle(page, "Audio");
        addGrayNote(page, "Sample Rate: " + SR + " Hz    Buffer: " + blockSize + " frames");

        return page;
    }

    private void addSectionTitle(LinearLayout parent, String title) {
        TextView tv = new TextView(this);
        tv.setText(title);
        tv.setTextColor(Color.WHITE);
        tv.setTextSize(16);
        tv.setTypeface(null, android.graphics.Typeface.BOLD);
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        lp.setMargins(0, 16, 0, 8);
        tv.setLayoutParams(lp);
        parent.addView(tv);
    }

    private void addGrayNote(LinearLayout parent, String text) {
        TextView tv = new TextView(this);
        tv.setText(text);
        tv.setTextColor(Color.LTGRAY);
        tv.setTextSize(13);
        tv.setTypeface(null, android.graphics.Typeface.ITALIC);
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        lp.setMargins(0, 4, 0, 4);
        tv.setLayoutParams(lp);
        parent.addView(tv);
    }

    private void refreshSHCUI() {
        Log.d("Faust", "refreshSHCUI() called - starting SHCUI refresh");
        
        // CRITICAL: Directly refresh all CustomButton instances
        // This fixes the black screen issue by forcing Paint objects to redraw
        // DO NOT call invalidate() on parent views - this causes buttons to disappear
        if (touchUItabView != null) {
            Map<String, FrameLayout> contentLayouts = touchUItabView.getContentLayouts();
            int buttonCount = 0;
            
            for (Map.Entry<String, FrameLayout> entry : contentLayouts.entrySet()) {
                FrameLayout tabContent = entry.getValue();
                Log.d("Faust", "Refreshing tab: " + entry.getKey() + " with " + tabContent.getChildCount() + " children");
                buttonCount += refreshAllCustomButtons(tabContent);
            }
            
            Log.d("Faust", "Refreshed " + buttonCount + " CustomButton instances across " + contentLayouts.size() + " tabs");
        }
        
        Log.d("Faust", "refreshSHCUI() completed");
    }

    /**
     * Recursively find and refresh all CustomButton instances in a ViewGroup.
     * Returns the count of buttons refreshed.
     */
    private int refreshAllCustomButtons(ViewGroup viewGroup) {
        int count = 0;
        for (int i = 0; i < viewGroup.getChildCount(); i++) {
            View child = viewGroup.getChildAt(i);
            
            if (child instanceof CustomButton) {
                ((CustomButton) child).forceRedraw();
                count++;
                Log.d("Faust", "Refreshed CustomButton: " + ((CustomButton) child).pathForButton);
            } else if (child instanceof ViewGroup) {
                // Recursively search in child ViewGroups
                count += refreshAllCustomButtons((ViewGroup) child);
            }
        }
        return count;
    }

    private Button makeSmallButton(String text, int bgColor) {
        Button btn = new Button(this);
        btn.setText(text);
        btn.setTextColor(Color.WHITE);
        btn.setBackgroundColor(bgColor);
        btn.setTextSize(14);
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(
                0, ViewGroup.LayoutParams.WRAP_CONTENT, 1f);
        lp.setMargins(4, 4, 4, 4);
        btn.setLayoutParams(lp);
        return btn;
    }

    private ArrayAdapter<String> createWhiteTextAdapter(ArrayList<String> items) {
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_spinner_item, items) {
            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                View view = super.getView(position, convertView, parent);
                TextView textView = (TextView) view;
                textView.setTextColor(Color.WHITE);
                textView.setTextSize(16);
                textView.setPadding(12, 12, 12, 12);
                return view;
            }

            @Override
            public View getDropDownView(int position, View convertView, ViewGroup parent) {
                View view = super.getDropDownView(position, convertView, parent);
                TextView textView = (TextView) view;
                textView.setTextColor(Color.BLACK);
                textView.setTextSize(16);
                textView.setPadding(16, 16, 16, 16);
                return view;
            }
        };
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        return adapter;
    }

    private EditText makeEditRow(LinearLayout parent, String label, String defaultValue) {
        TextView labelTv = new TextView(this);
        labelTv.setText(label);
        labelTv.setTextColor(Color.LTGRAY);
        labelTv.setTextSize(13);
        parent.addView(labelTv);

        EditText et = new EditText(this);
        et.setText(defaultValue);
        et.setTextColor(Color.WHITE);
        et.setBackgroundColor(Color.argb(180, 40, 40, 40));
        et.setPadding(12, 8, 12, 8);
        parent.addView(et);

        return et;
    }

@Override
    public void onDestroy() {
        Log.d("Faust", "onDestroy");

        super.onDestroy();

        if (dspFaustMotion != null) {
        dspFaustMotion = null;
        }

        if (dspFaust != null) {
            saveFaustParams();
        dspFaust = null;
        }

        if (sensorManager!=null){sensorManager.unregisterListener(mSensorListener);}

        sensorManager= null;

    }

@Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {

        if (AUDIO_ECHO_REQUEST != requestCode) {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
            return;
        }

        if (grantResults.length != 1 ||
                grantResults[0] != PackageManager.PERMISSION_GRANTED) {
            finish();
        } else {
            // Permission was granted
            permissionToRecordAccepted = true;
            createFaust();
        }
    }

    // For audio input request permission
    private boolean isRecordPermissionGranted() {
        return (ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) == PackageManager.PERMISSION_GRANTED);
    }

    private void requestRecordPermission() {
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.RECORD_AUDIO}, AUDIO_ECHO_REQUEST);
    }
}
