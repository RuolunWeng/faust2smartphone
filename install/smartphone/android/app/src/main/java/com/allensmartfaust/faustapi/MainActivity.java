package com.allensmartfaust.faustapi;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;
import android.widget.SeekBar;
import android.widget.TextView;


import com.DspFaust.DspFaust;

public class MainActivity extends AppCompatActivity {
    DspFaust dspFaust;
    private SensorManager sensorManager;
    
    private SeekBar param1,param2;
    private TextView paramOut1,paramOut2;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        int SR = 44100;
        int blockSize = 256;
        dspFaust = new DspFaust(SR,blockSize);
        dspFaust.start();
        dspFaust.setParamValue("/Oscillator/volume", -20);
        dspFaust.setParamValue("/Oscillator/freq", 220);

        // PRINT ALL PARAMETRE ADDRESS
        for(int i=0; i < dspFaust.getParamsCount(); i++){
            System.out.println(dspFaust.getParamAddress(i));
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
        for (int i = 0 ;i<event.values.length;i++){
            dspFaust.propagateAcc(i, event.values[i]*(-1));
        }


        // TODO: GET VALUE from FAUST
        float getParam1,getParam2;
        getParam1 = dspFaust.getParamValue("/Oscillator/freq");
        getParam2 = dspFaust.getParamValue("/Oscillator/volume");

        param1.setProgress((int)(getParam1-220.0f));
        param2.setProgress((int)(getParam2+96.0f));
        paramOut1.setText("Freq:"+getParam1+"Hz");
        paramOut2.setText("Volume:"+getParam2+"dB");

        }
    };


    @Override
    protected void onPause() {
        Log.d("Faust", "onPause");
        sensorManager.unregisterListener(mSensorListener);
        super.onPause();
    }

    @Override
    protected void onResume() {
        Log.d("Faust", "onResume");
        super.onResume();
        sensorManager.registerListener(mSensorListener, sensorManager.getDefaultSensor(
        Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_FASTEST);
    }

    @Override
    protected void onStart() {
        Log.d("Faust", "onStart");
        super.onStart();
        if (!isChangingConfigurations()) {
        dspFaust.start();

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
        // only stops audio when the user press the return button (and not when the screen is rotated)
        if (!isChangingConfigurations()) {
        dspFaust.stop();
        dspFaust.delete();

        }
        super.onDestroy();
    }

}

