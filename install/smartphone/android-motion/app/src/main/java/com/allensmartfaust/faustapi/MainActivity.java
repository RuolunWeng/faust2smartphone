package com.allensmartfaust.faustapi;

import android.Manifest;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
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
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;


import com.DspFaust.DspFaust;
import com.DspFaust.DspFaustMotion;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

import static android.R.color.white;

public class MainActivity extends AppCompatActivity {
    DspFaust dspFaust;
    DspFaustMotion dspFaustMotion;

    private SensorManager sensorManager;

    private SharedPreferences mSharedPref;

    private TextView cue,cueNext,cueText, cueNextText, tips, appName;
    private EditText paramsValue, ipAddress, inputPort, outputPort;

    private ImageView touche;
    private Button prevCue, nextCue, initCue, setMotion , defaultParams, setOSC, setRef;


    private CheckBox setParams;
    private RadioGroup radioGroup;

    int scrWidth = 0,scrHeight= 0;

    int SR = 44100;
    int blockSize = 256;
    long lastDate=0;
    int updateInterval = (int)(1000.f/(SR/blockSize));

    ArrayList<String> cueList = new ArrayList<String>();
    ArrayList<String> tipsList = new ArrayList<String>();

    ArrayList<String>  motionParamArray = new ArrayList<String>();
    ArrayList<String>  motionParamAddress = new ArrayList<String>();

    int cueIndex,cueIndexNext;

    float[] rotationMatrix = new float[9];

    String oscAddress;
    int oscInPort;
    int oscOutPort;

    String touchGateAddress;
    String screenXAddress;
    String screenYAddress;
    String magneticHeadingAddress;

    String cueAddress;
    String tipAddress;

    boolean[] paramsOn;
    boolean touchGateIsOn;
    boolean screenXIsOn;
    boolean screenYIsOn;
    boolean magneticHeadingIsOn;

    boolean cueIsOn;
    boolean tipIsOn;

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
                        createFaust();
                    }
                    else {
                        finish();
                    }
                }

                break;
        }
    }


    private void createFaust() {


        if (dspFaustMotion == null) {
            dspFaustMotion = new DspFaustMotion(SR / blockSize, 1);
            //dspFaustMotion = new DspFaustMotion(SR, blockSize);

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
        appName = (TextView) findViewById(R.id.appName);

        cue.setText(cueList.get(cueIndex));
        cueNext.setText(cueList.get(cueIndexNext));
        tips.setText(tipsList.get(cueIndex));
        appName.setText(getApplicationContext().getPackageName().replace("com.allensmartfaust."," ").concat(" | Grame"));

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
                boolean isChecked = checkedRadioButton.isChecked();
                if (isChecked)
                {
                    for (int i=0; i< motionParamArray.size(); i++) {
                        paramsOn[i]=false;
                    }
                    paramsOn[checkedId]=true;
                    paramsValue.setText( String.valueOf(dspFaustMotion.getParamValue(motionParamAddress.get(checkedId))));

                }
            }
        });


        setMotion.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                for (int i=0; i< motionParamArray.size(); i++) {
                    if (paramsOn[i]){
                        dspFaustMotion.setParamValue(motionParamAddress.get(i), Float.valueOf(paramsValue.getText().toString()));
                        SharedPreWriteFloat(motionParamArray.get(i),Float.valueOf(paramsValue.getText().toString()));
                    }

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

        for (int i = 0; i < dspFaustMotion.getParamsCount(); i++) {
            String Str = dspFaustMotion.getMetadata(i, "showName");
            if (!Str.equals("")){
                motionParamArray.add(Str);
                motionParamAddress.add(dspFaustMotion.getParamAddress(i));
            }
        }

        System.out.println(motionParamArray);
        System.out.println(motionParamAddress);

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

                        float screenX = pointerIndex / scrWidth;
                        float screenY = pointerIndey/(scrHeight/2);

                        if (touchGateIsOn) {
                            touche.setVisibility(View.VISIBLE);
                            dspFaust.setParamValue(touchGateAddress, 1);
                        }
                        if (cueIsOn) {
                            touche.setVisibility(View.VISIBLE);
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

                        float screenX = pointerIndex / scrWidth;
                        float screenY = pointerIndey/(scrHeight/2);
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

    if ((currentTime-lastDate) > updateInterval) {

        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            // Update acc at sensor rate

            dspFaust.propagateAcc(0, -event.values[0]);
            dspFaust.propagateAcc(1, -event.values[1]);
            dspFaust.propagateAcc(2, event.values[2]);

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
            // Update rotation matrix at sensor rate
            SensorManager.getRotationMatrixFromVector(rotationMatrix, event.values);

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

for (int i=0; i<motionParamAddress.size(); i++){
dspFaustMotion.setParamValue(motionParamAddress.get(i),
SharedPrefRead(motionParamArray.get(i),dspFaustMotion.getParamInit(motionParamAddress.get(i))));
}


}

private void resetParams() {

SharedPreClear();

for (int i=0; i<motionParamAddress.size(); i++){
SharedPreWriteFloat(motionParamArray.get(i), dspFaustMotion.getParamInit((motionParamAddress.get(i))));
}

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
