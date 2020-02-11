package com.allensmartfaust.faustapi;

import android.content.Context;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
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

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import static android.Manifest.permission.ACCESS_NETWORK_STATE;
import static android.Manifest.permission.CAMERA;
import static android.Manifest.permission.INTERNET;
import static android.Manifest.permission.READ_CONTACTS;
import static android.Manifest.permission.READ_PHONE_STATE;
import static android.Manifest.permission.RECORD_AUDIO;

import android.os.Build;

// For audio input request permission
import android.support.v4.app.ActivityCompat;
import android.Manifest;
import android.widget.Toast;
import android.support.annotation.NonNull;
import android.content.pm.PackageManager;

public class MainActivity extends AppCompatActivity
implements ActivityCompat.OnRequestPermissionsResultCallback {

    DspFaust dspFaust;
    private SensorManager sensorManager;

    int SR = 44100;
    int blockSize = 512;
    long lastDate=0;
    int updateInterval = (int)(1000.f/(SR/blockSize));

    private SeekBar param1,param2;
    private TextView paramOut1,paramOut2;

    // For audio input request permission
    private static final int AUDIO_ECHO_REQUEST = 0;
    private boolean permissionToRecordAccepted = false;

    private void createFaust() {
        if (dspFaust == null) {
            Toast.makeText(MainActivity.this, "WELCOME", Toast.LENGTH_LONG).show();

                dspFaust = new DspFaust(SR,blockSize);
                // PRINT ALL PARAMETRE ADDRESS
                for(int i=0; i < dspFaust.getParamsCount(); i++){
                    System.out.println(dspFaust.getParamAddress(i));
                }

        }
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

                // check if audio files were saved in internal storage
          String[] internalStorageList = getFilesDir().list();
          boolean fileWereCopied = false;
          for(int i=0; i<internalStorageList.length; i++){
              if(internalStorageList[i].contains(".aif") || internalStorageList[i].contains(".wav") || internalStorageList[i].contains(".flac")) {
                  fileWereCopied = true;
                  break;
              }
          }

          if (Build.VERSION.SDK_INT >= 23 && !isRecordPermissionGranted()){
                requestRecordPermission();
            } else {
                permissionToRecordAccepted = true;
                createFaust();
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
            dspFaust.propagateAcc(0, -event.values[0]);
            dspFaust.propagateAcc(1, -event.values[1]);
            dspFaust.propagateAcc(2, -event.values[2]);
            }

        if (event.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
            // Update mapping at sensor rate
            dspFaust.propagateGyr(0, event.values[0]);
            dspFaust.propagateGyr(1, event.values[1]);
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
        super.onPause();

        if(permissionToRecordAccepted) {
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
            
            if (!dspFaust.isRunning()) {
                dspFaust.start();
                sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                    Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);
    
                sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
                    Sensor.TYPE_GYROSCOPE), SensorManager.SENSOR_DELAY_FASTEST);
            }

        }

    }

    @Override
    protected void onStart() {
        Log.d("Faust", "onStart");
        super.onStart();

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
        if (dspFaust != null) {
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
