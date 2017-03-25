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

public class MainActivity extends AppCompatActivity implements SensorEventListener {
    DspFaust dspFaust;
    private SensorManager sensorManager;
    private Sensor accelerometer;
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
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL);
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        for (int i = 0 ;i<event.values.length;i++){
            dspFaust.propagateAcc(i, event.values[i]);
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

    @Override
    public void onDestroy(){
        super.onDestroy();
        dspFaust.stop();
    }
}

