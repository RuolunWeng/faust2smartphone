package com.allensmartfaust.faustapi;

import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;


import com.DspFaust.DspFaust;

import static android.Manifest.permission.ACCESS_NETWORK_STATE;
import static android.Manifest.permission.CAMERA;
import static android.Manifest.permission.INTERNET;
import static android.Manifest.permission.READ_CONTACTS;
import static android.Manifest.permission.READ_PHONE_STATE;
import static android.Manifest.permission.RECORD_AUDIO;

public class MainActivity extends AppCompatActivity {
    DspFaust dspFaust;
    private SensorManager sensorManager;
    
    int SR = 44100;
    int blockSize = 512;
    long lastDate=0;
    int updateInterval = (int)(1000.f/(SR/blockSize));
    
    private SeekBar param1,param2;
    private TextView paramOut1,paramOut2;

    public static final int RequestPermissionCode = 1;

    private void requestPermission() {

        ActivityCompat.requestPermissions(MainActivity.this, new String[]
                {
                        RECORD_AUDIO,
                        INTERNET,
                        ACCESS_NETWORK_STATE
                }, RequestPermissionCode);

    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {

            case RequestPermissionCode:

                if (grantResults.length > 0) {

                    boolean AudioPermission = grantResults[0] == PackageManager.PERMISSION_GRANTED;
                    boolean InternetPermission = grantResults[1] == PackageManager.PERMISSION_GRANTED;
                    boolean NetworkPermission = grantResults[2] == PackageManager.PERMISSION_GRANTED;

                    if (AudioPermission && InternetPermission && NetworkPermission) {

                        Toast.makeText(MainActivity.this, "Permission Granted", Toast.LENGTH_LONG).show();
                    }
                    else {
                        Toast.makeText(MainActivity.this,"Permission Denied",Toast.LENGTH_LONG).show();

                    }
                }

                break;
        }
    }

    public boolean checkPermission() {

        int FirstPermissionResult = ContextCompat.checkSelfPermission(getApplicationContext(), RECORD_AUDIO);
        int SecondPermissionResult = ContextCompat.checkSelfPermission(getApplicationContext(), INTERNET);
        int ThirdPermissionResult = ContextCompat.checkSelfPermission(getApplicationContext(), ACCESS_NETWORK_STATE);

        return FirstPermissionResult == PackageManager.PERMISSION_GRANTED &&
                SecondPermissionResult == PackageManager.PERMISSION_GRANTED &&
                ThirdPermissionResult == PackageManager.PERMISSION_GRANTED;
    }



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        

        // TODO: SET PARAMETRE ADDRESS & VALUE
        // TODO: Change interface in .xml
        param1 = (SeekBar) findViewById(R.id.seekBar1);
        param2 = (SeekBar) findViewById(R.id.seekBar2);
        paramOut1 = (TextView) findViewById(R.id.textView1);
        paramOut2 = (TextView) findViewById(R.id.textView2);

        param1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            float value;
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                //Log.d("DEBUG", "Progress is: "+progress);
                value = progress+220.0f;
                dspFaust.setParamValue("/Oscillator/freq",value );
                paramOut1.setText("Freq:"+value+"Hz");
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        param2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int value;
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                //Log.d("DEBUG", "Progress is: "+progress);
                value = progress-96;
                dspFaust.setParamValue("/Oscillator/volume",value );
                paramOut2.setText("Volume:"+value+"dB");
            }

            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        
    }

    private final SensorEventListener mSensorListener = new SensorEventListener() {
    
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
    }

    
    public void onSensorChanged(SensorEvent event) {
    
    long currentTime= System.currentTimeMillis();
    
    if ((currentTime-lastDate) > updateInterval) {
    
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            // Update mapping at sensor rate
            dspFaust.propagateAcc(0, event.values[0] * (-9.81f));
            dspFaust.propagateAcc(1, event.values[1] * (-9.81f));
            dspFaust.propagateAcc(2, event.values[2] * (9.81f));
            }

        if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
            // Update mapping at sensor rate
            dspFaust.propagateGyr(0, event.values[0]*(-1));
            dspFaust.propagateGyr(1, event.values[1]*(-1));
            dspFaust.propagateGyr(2, event.values[2]);
            }

        // TODO: GET VALUE from FAUST
        float getParam1,getParam2;
        getParam1 = dspFaust.getParamValue("/Oscillator/freq");
        getParam2 = dspFaust.getParamValue("/Oscillator/volume");

        param1.setProgress((int)(getParam1-220.0f));
        param2.setProgress((int)(getParam2+96.0f));
        paramOut1.setText("Freq:"+getParam1+"Hz");
        paramOut2.setText("Volume:"+getParam2+"dB");
        
        lastDate = currentTime;
        
    }
        }
    };


    @Override
    protected void onPause() {
        Log.d("Faust", "onPause");
        dspFaust.stop();
        sensorManager.unregisterListener(mSensorListener);
        dspFaust.delete();
        super.onPause();
    }

    @Override
    protected void onResume() {
        Log.d("Faust", "onResume");
        super.onResume();

        sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);

        sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                Sensor.TYPE_GYROSCOPE), SensorManager.SENSOR_DELAY_FASTEST);


    }

    @Override
    protected void onStart() {
        Log.d("Faust", "onStart");
        super.onStart();
        if (!isChangingConfigurations()) {
            if(checkPermission()){

                Toast.makeText(MainActivity.this, "WELCOME", Toast.LENGTH_LONG).show();

                dspFaust = new DspFaust(SR,blockSize);
                // PRINT ALL PARAMETRE ADDRESS
                for(int i=0; i < dspFaust.getParamsCount(); i++){
                    System.out.println(dspFaust.getParamAddress(i));
                }
                dspFaust.start();

            }
            else {

                requestPermission();
            }
        }
    }

    @Override
    protected void onRestart() {
        Log.d("Faust", "onRestart");
        super.onRestart();
    }

    @Override
    protected void onStop() {
        Log.d("Faust", "onStop");
        super.onStop();

    }

    @Override
    public void onDestroy() {
        Log.d("Faust", "onDestroy");

        super.onDestroy();
    }

}

