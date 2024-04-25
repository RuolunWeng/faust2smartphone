package com.allensmartfaust.faustapi;

import com.allensmartfaust.faustapi.MainActivity;

import com.allensmartfaust.faustapi.CustomCounter;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewTreeObserver;

import androidx.core.graphics.ColorUtils;

import java.util.ArrayList;

public class CustomButton extends View {

    private String customButtonType;
    private String nameForButton;
    private String pathForButton;
    private int tag;
    private int selectedColor, newGrayColor;
    private int lineWidth = 2;
    private boolean selected = false;
    private Paint paint, padPaint;
    private RectF rectF;
    private OnClickListener onClickListener;
    private OnTouchListener onTouchListener;
    private RectF horizontalLine, verticalLine;
    private ArrayList<Float> initValues;

    public CustomButton(Context context) {
        super(context);
        init();
    }

    public CustomButton(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        paint = new Paint();
        padPaint = new Paint();
        paint.setAntiAlias(true);
        paint.setStyle(Paint.Style.FILL);
        rectF = new RectF();
    }

    public void setCustomButtonType(String buttonType) {
        customButtonType = buttonType;
    }

    public void setNameForButton(String name) {
        nameForButton = name;
    }

    public void setPathForButton(String path) {
        pathForButton = path;
    }

    public void setTag(int buttonTag) {
        tag = buttonTag;
    }

    public void setInitValuesForButton(ArrayList<Float> inits) {
        initValues = inits;
    }

    public void setSelectedColor(int color) {
        selectedColor = color;

        // Get the alpha component of the color
        int originalAlpha = Color.alpha(color);
        newGrayColor = ColorUtils.setAlphaComponent(Color.GRAY, originalAlpha);


        switch (customButtonType) {
            case "button":
            case "trigCue":
            case "nextCue":
            case "initCue":
            case "prevCue":
            case "trigCounter":
            case "setRef":
            case "pad":
                paint.setColor(color);
                break;
            case "checkbox":
                paint.setColor(selected ? selectedColor : newGrayColor);
                break;
            case "vslider":
            case "hslider":
                padPaint.setColor(color);
                paint.setColor(newGrayColor);
                break;
            default:
                break;
        }
    }

    public void updateButtonSelectedColor(boolean selected) {
        paint.setColor(selected ? selectedColor : newGrayColor);
    }

    public void setLineWidth(int width) {
        lineWidth = width;
    }


    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        //rectF.set(lineWidth, lineWidth, getWidth() - lineWidth, getHeight() - lineWidth);

        //canvas.drawRoundRect(rectF, 10, 10, paint);
        // Set the paint color for the button background
        //paint.setColor(selected ? selectedColor : Color.GRAY);
        rectF.set(lineWidth, lineWidth, getWidth() - lineWidth*3, getHeight() - lineWidth*3);
        canvas.drawRoundRect(rectF, 10, 10, paint);


        switch (customButtonType) {
            case "vslider":
                padPaint.setStyle(Paint.Style.FILL);
                // Draw horizontal line
                canvas.drawRoundRect(horizontalLine, 10, 10, padPaint);
                break;
            case "hslider":
                padPaint.setStyle(Paint.Style.FILL);
                // Draw horizontal line
                canvas.drawRoundRect(verticalLine, 10, 10, padPaint);
                break;
            case "pad":
                padPaint.setStyle(Paint.Style.FILL);
                // Draw horizontal line
                canvas.drawRect(horizontalLine, padPaint);
                // Draw vertical line
                canvas.drawRect(verticalLine, padPaint);
                break;
            default:
                break;
        }

        /*// Set the paint color for text
        paint.setColor(Color.BLACK);
        paint.setTextSize(30); // Adjust the text size as needed
        paint.setTextAlign(Paint.Align.CENTER);

        // Calculate the position to draw the text
        float x = getWidth() / 2.0f;
        float y = getHeight() / 2.0f + ((paint.descent() + paint.ascent()) / 2);

        // Draw the button name in the center of the button
        String buttonText = nameForButton != null ? nameForButton : "";
        canvas.drawText(buttonText, x, y, paint);*/

        // Set the paint color for text
        paint.setColor(Color.BLACK);
        paint.setTextAlign(Paint.Align.CENTER);
        paint.setTextSize(500);

        String buttonText = nameForButton != null ? nameForButton : "";

// Calculate the maximum text size that fits within the available width
        float textWidth = paint.measureText(buttonText);
        float availableWidth = getWidth();
        float textSize = paint.getTextSize();
        if (textWidth > availableWidth) {
            // Calculate the new text size to fit the width
            textSize *= availableWidth / textWidth;
        }

// Set the adjusted text size
        paint.setTextSize(textSize*0.95f);

// Calculate the position to draw the text
        float x = getWidth() / 2.0f;
        float y = getHeight() / 2.0f - ((paint.descent() + paint.ascent()) / 2); // Adjusted y position

// Draw the button name in the center of the button
        canvas.drawText(buttonText, x, y, paint);


    }

    @Override
    protected void onVisibilityChanged(View changedView, int visibility) {
        super.onVisibilityChanged(changedView, visibility);

        if (visibility == View.VISIBLE) {
            // The view has become visible, trigger a redraw
            setSelectedColor(selectedColor);
            invalidate();
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                if (onClickListener != null) {
                    onClickListener.onClick(this);
                }
                if (onTouchListener != null) {
                    onTouchListener.onTouchDown(event, this);
                }
                switch (customButtonType) {
                    case "button":
                    case "trigCue":
                    case "nextCue":
                    case "initCue":
                    case "prevCue":
                    case "trigCounter":
                    case "setRef":
                        paint.setColor(newGrayColor);
                        break;
                    case "pad":
                    case "vslider":
                    case "hslider":
                        paint.setColor(newGrayColor);
                        padPaint.setColor(selectedColor);
                        break;
                    default:
                        break;
                }
                break;
            case MotionEvent.ACTION_UP:
                //setSelected(false);
                //paint.setColor(Color.GRAY);

                switch (customButtonType) {
                    case "checkbox":
                        selected = !selected;
                        updateButtonSelectedColor(selected);
                        break;
                    case "button":
                    case "trigCue":
                    case "nextCue":
                    case "initCue":
                    case "prevCue":
                    case "trigCounter":
                    case "setRef":
                        paint.setColor(selectedColor);
                        break;
                    case "pad":
                        paint.setColor(selectedColor);
                        padPaint.setColor(Color.BLACK);
                        break;
                    case "vslider":
                    case "hslider":
                        paint.setColor(newGrayColor);
                        padPaint.setColor(selectedColor);
                        break;
                    default:
                        break;
                }

                if (onTouchListener != null) {
                    onTouchListener.onTouchUp(event, this);
                }

                break;
            case MotionEvent.ACTION_MOVE:
                if (onTouchListener != null) {
                    onTouchListener.onTouchMove(event, this);
                }
                // Update the positions of the lines based on touch input
                float touchX = event.getX();
                float touchY = event.getY();

                switch (customButtonType) {
                    case "hslider":
                        paint.setColor(newGrayColor);
                        padPaint.setColor(selectedColor);

                        float width = getWidth();

                        // Ensure the touch X coordinate stays within the button bounds
                        touchX = Math.max(0, Math.min(width, touchX));

                        // Calculate the new width of the button based on touch X coordinate
                        //float newWidth = width - touchX;

                        // Update the RectF with the new position and size
                        //verticalLine.set(touchX, 0, width, getHeight());
                        verticalLine.set(0, 0, touchX, getHeight());

                        // Request a redraw of the button
                        invalidate();

                        break;
                    case "vslider":
                        paint.setColor(newGrayColor);
                        padPaint.setColor(selectedColor);

                        float height = getHeight();

                        // Ensure the touch Y coordinate stays within the button bounds
                        touchY = Math.max(0, Math.min(height, touchY));

                        // Calculate the new height of the button based on touch Y coordinate
                        //float newHeight = height - touchY;

                        // Update the RectF with the new position and size
                        horizontalLine.set(0, touchY, getWidth(), height);

                        // Request a redraw of the button
                        invalidate();

                        break;
                    case "pad":
                        // Create a new color with the specified alpha value
                        int newbgColor = ColorUtils.setAlphaComponent(selectedColor, 50);
                        // Create a new color with the specified alpha value
                        int newSelectedColor = ColorUtils.setAlphaComponent(selectedColor, 255);

                        paint.setColor(newbgColor);
                        padPaint.setColor(newSelectedColor);

                        // Ensure the touch coordinates stay within the button bounds
                        touchX = Math.max(0, Math.min(getWidth(), touchX));
                        touchY = Math.max(0, Math.min(getHeight(), touchY));

                        horizontalLine.left = 0;
                        horizontalLine.right = getWidth();
                        horizontalLine.top = touchY - lineWidth / 2;
                        horizontalLine.bottom = touchY + lineWidth / 2;

                        verticalLine.left = touchX - lineWidth / 2;
                        verticalLine.right = touchX + lineWidth / 2;
                        verticalLine.top = 0;
                        verticalLine.bottom = getHeight();

                        // Invalidate the view to trigger a redraw
                        invalidate();
                    default:
                        break;
                }

                break;
        }
        invalidate();
        return true;
    }

    public void setOnClickListener(OnClickListener listener) {
        onClickListener = listener;
    }

    public void setOnTouchListener(OnTouchListener listener) {
        onTouchListener = listener;
    }

    public interface OnClickListener {
        void onClick(CustomButton button);
    }

    public interface OnTouchListener {
        void onTouchDown(MotionEvent event, CustomButton button);
        void onTouchUp(MotionEvent event, CustomButton button);
        void onTouchMove(MotionEvent event, CustomButton button);
        // Add other touch listener methods as needed
    }


    // Setup methods for different button types
    public void setupToggleButton() {
        setSelectedColor(selectedColor);

        if (initValues.get(0) == 1) {
            selected = true;
        } else {
            selected = false;
        }

        updateButtonSelectedColor(selected);

        setOnTouchListener(new CustomButton.OnTouchListener() {
            @Override
            public void onTouchDown(MotionEvent event, CustomButton button) {
                // Handle ACTION_DOWN event
            }

            @Override
            public void onTouchUp(MotionEvent event, CustomButton button) {
                // Handle ACTION_UP event
                MainActivity.dspFaust.setParamValue(pathForButton,selected? 1:0);
                Log.d("CustomButton", "Button clicked: " + pathForButton + " " + selected);
            }

            @Override
            public void onTouchMove(MotionEvent event, CustomButton button) {
                // Handle ACTION_MOVE event
            }
        });
    }

    public void setupTrigCueButton() {
        setNameForButton("TrigCue");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);

/*        setOnClickListener(new CustomButton.OnClickListener() {
            @Override
            public void onClick(CustomButton button) {
                Log.d("CustomButton", "TRIG CUE Button clicked: " + path);
                // Log other relevant information
            }
        });*/
    }

    public void setupNextCueButton() {
        setNameForButton("NextCue");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);

    }

    public void setupPrevCueButton() {
        setNameForButton("PrevCue");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);

    }

    public void setupInitCueButton() {
        setNameForButton("InitCue");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);

    }

    public void setupSetRefButton() {
        setNameForButton("SetRef");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);

    }

    public void setupTrigCounterButton() {
        //setNameForButton("TrigCounter");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);

        float minValue = MainActivity.dspFaust.getParamMin(pathForButton);
        float maxValue = MainActivity.dspFaust.getParamMax(pathForButton);
        float step = MainActivity.dspFaust.getParamStep(tag);
        float initialValue = MainActivity.dspFaust.getParamValue(pathForButton);

        // Create a CustomCounter instance with the desired range and initial value
        final CustomCounter counter = new CustomCounter(minValue, maxValue, step, initialValue);

        // Reset the counter
        counter.reset();

        // Get the current value of the counter
        float currentValue = counter.getCurrentValue();
        MainActivity.dspFaust.setParamValue(pathForButton,currentValue);
        MainActivity.tips.setText("Counter_"+nameForButton+": "+currentValue);

        setOnClickListener(new CustomButton.OnClickListener() {
            @Override
            public void onClick(CustomButton button) {
                Log.d("CustomButton", "TRIG Counter Button clicked: " + pathForButton);

                // Increment the counter
                counter.increment();

                // Get the current value of the counter
                float currentValue = counter.getCurrentValue();

                MainActivity.dspFaust.setParamValue(pathForButton,currentValue);
                MainActivity.tips.setText("Counter_"+nameForButton+": "+currentValue);
            }
        });


    }

    public void setupTouchScreenXButton() {
        //setNameForButton("TouchScreenX");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);


        // Listen for size changes
        getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                // Remove the listener to avoid redundant calls
                getViewTreeObserver().removeOnGlobalLayoutListener(this);

                // Calculate the initial positions for lines (assuming lineInits contains X and Y values)
                float lineInitX = mapValue(initValues.get(0), 0, 1, 0, getWidth());

                // Update the positions of the lines represented by RectF objects
                verticalLine = new RectF(0, 0, lineInitX, getHeight());

                // Trigger a redraw to reflect the changes
                invalidate();
            }
        });

        setOnTouchListener(new CustomButton.OnTouchListener() {
            @Override
            public void onTouchDown(MotionEvent event, CustomButton button) {
                // Handle ACTION_DOWN event
            }

            @Override
            public void onTouchUp(MotionEvent event, CustomButton button) {
                // Handle ACTION_UP event
            }

            @Override
            public void onTouchMove(MotionEvent event, CustomButton button) {
                // Handle ACTION_MOVE event
                float normalisedX = clampValue(event.getX()/getWidth(),0,1);
                //Log.d("CustomButton", "hslider " + pathForButton + " touched: Nor_X = " + normalisedX);
                float scaledX = scaleValue(normalisedX,MainActivity.dspFaust.getParamMin(pathForButton),MainActivity.dspFaust.getParamMax(pathForButton));
                MainActivity.dspFaust.setParamValue(pathForButton,scaledX);
            }
        });
    }

    public void setupTouchScreenYButton() {
        //setNameForButton("TouchScreenY");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);

        // Listen for size changes
        getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                // Remove the listener to avoid redundant calls
                getViewTreeObserver().removeOnGlobalLayoutListener(this);

                // Calculate the initial positions for lines (assuming lineInits contains X and Y values)
                float lineInitY = mapValue(initValues.get(0), 0, 1, getHeight(),0);

                // Update the positions of the lines represented by RectF objects
                horizontalLine = new RectF(0, lineInitY, getWidth(), getHeight());

                // Trigger a redraw to reflect the changes
                invalidate();
            }
        });



        setOnTouchListener(new CustomButton.OnTouchListener() {
            @Override
            public void onTouchDown(MotionEvent event, CustomButton button) {
                // Handle ACTION_DOWN event
            }

            @Override
            public void onTouchUp(MotionEvent event, CustomButton button) {
                // Handle ACTION_UP event
            }

            @Override
            public void onTouchMove(MotionEvent event, CustomButton button) {
                // Handle ACTION_MOVE event
                float normalisedY = clampValue(1-(event.getY()/getHeight()),0,1);
                //Log.d("CustomButton", "vslider " + pathForButton + " touched: Nor_Y = " + normalisedY);
                float scaledY = scaleValue(normalisedY,MainActivity.dspFaust.getParamMin(pathForButton),MainActivity.dspFaust.getParamMax(pathForButton));
                MainActivity.dspFaust.setParamValue(pathForButton,scaledY);
            }
        });
    }

    public void setupPadButton() {
        //setNameForButton("Pad");
        //setPathForButton(path);
        //setSelectedColor(selectedColor);

        // Listen for size changes
        getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                // Remove the listener to avoid redundant calls
                getViewTreeObserver().removeOnGlobalLayoutListener(this);

                // Calculate the initial positions for lines (assuming lineInits contains X and Y values)
                float lineInitX = mapValue(initValues.get(0), 0, 1, 0, getWidth());
                float lineInitY = mapValue(initValues.get(1), 0, 1, getHeight(), 0);

                // Update the positions of the lines represented by RectF objects
                horizontalLine = new RectF(0, lineInitY, getWidth(), lineInitY + lineWidth);
                verticalLine = new RectF(lineInitX, 0, lineInitX + lineWidth, getHeight());

                // Trigger a redraw to reflect the changes
                invalidate();
            }
        });


        setOnTouchListener(new CustomButton.OnTouchListener() {
            @Override
            public void onTouchDown(MotionEvent event, CustomButton button) {
                // Handle ACTION_DOWN event
                Log.d("CustomButton", "Button clicked: " + pathForButton + " 1");
                MainActivity.dspFaust.setParamValue(pathForButton,1);
            }

            @Override
            public void onTouchUp(MotionEvent event, CustomButton button) {
                // Handle ACTION_UP event
                Log.d("CustomButton", "Button clicked: " + pathForButton + " 0");
                MainActivity.dspFaust.setParamValue(pathForButton,0);
            }

            @Override
            public void onTouchMove(MotionEvent event, CustomButton button) {
                // Handle ACTION_MOVE event
                //Log.d("CustomButton", "Pad " + pathForButton + " touched: X = " + event.getX() + ", Y = " + event.getY());

                float normalisedX = clampValue(event.getX()/getWidth(),0,1);
                //Log.d("CustomButton", "pad_x " + pathForButton+"_X" + " touched: Nor_X = " + normalisedX);
                float scaledX = scaleValue(normalisedX,MainActivity.dspFaust.getParamMin(pathForButton+"_X"),MainActivity.dspFaust.getParamMax(pathForButton+"_X"));
                MainActivity.dspFaust.setParamValue(pathForButton+"_X",scaledX);

                float normalisedY = clampValue(1-(event.getY()/getHeight()),0,1);
                //Log.d("CustomButton", "pad_y " + pathForButton+"_Y" + " touched: Nor_Y = " + normalisedY);
                float scaledY = scaleValue(normalisedY,MainActivity.dspFaust.getParamMin(pathForButton+"_Y"),MainActivity.dspFaust.getParamMax(pathForButton+"_Y"));
                MainActivity.dspFaust.setParamValue(pathForButton+"_Y",scaledY);

            }
        });

    }

    public void setupButton() {
        //setPathForButton(path);
        //setSelectedColor(selectedColor);
        // Additional setup specific to the "button" type

        setOnTouchListener(new CustomButton.OnTouchListener() {
            @Override
            public void onTouchDown(MotionEvent event, CustomButton button) {
                // Handle ACTION_DOWN event
                Log.d("CustomButton", "Button clicked: " + pathForButton + " 1");
                // Log other relevant information
                MainActivity.dspFaust.setParamValue(pathForButton,1);
            }

            @Override
            public void onTouchUp(MotionEvent event, CustomButton button) {
                // Handle ACTION_UP event
                Log.d("CustomButton", "Button clicked: " + pathForButton + " 0");
                // Log other relevant information
                MainActivity.dspFaust.setParamValue(pathForButton,0);
            }

            @Override
            public void onTouchMove(MotionEvent event, CustomButton button) {
                // Handle ACTION_MOVE event
            }
        });


    }





    //
    // Utility functions for mapping and clamping values

    // Maps a value from one range to another
    public static float mapValue(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
        return toLow + (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow);
    }

    // Clamps a value within a specified range
    public static float clampValue(float value, float min, float max) {
        return Math.max(min, Math.min(max, value));
    }


    public float scaleValue(float value, float min, float max) {
        return min + (max - min) * value;
    }


}

