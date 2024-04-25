package com.allensmartfaust.faustapi;

import android.util.Log;

public class CustomCounter {
    private float maxValue;
    private float minValue;
    private float step;
    private float initialValue;
    private float currentValue;

    public CustomCounter(float min, float max, float step, float initValue) {
        this.minValue = min;
        this.maxValue = max;
        this.step = step;

        if (initValue >= this.minValue && initValue <= this.maxValue) {
            this.currentValue = initValue;
            this.initialValue = initValue;
        } else {
            Log.e("CustomCounter", "Initial value is out of range. Setting to min value.");
            this.currentValue = this.minValue;
            this.initialValue = this.minValue;
        }
    }

    public void increment() {
        currentValue += step;
        if (currentValue > maxValue) {
            currentValue = minValue;
        }
    }

    public void decrement() {
        currentValue -= step;
        if (currentValue < minValue) {
            currentValue = maxValue;
        }
    }

    public void reset() {
        currentValue = initialValue;
    }

    public float getCurrentValue() {
        return currentValue;
    }
}
