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

    public String customButtonType;
    private String nameForButton;
    public String pathForButton;
    private int tag;
    private int selectedColor, newGrayColor, newbgColor, newSelectedColor;
    private int lineWidth = 6; // utilise pour padding aussi
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

        // Create a new color with the specified alpha value
        newbgColor = ColorUtils.setAlphaComponent(selectedColor, 50);
        // Create a new color with the specified alpha value
        newSelectedColor = ColorUtils.setAlphaComponent(selectedColor, 255);

        switch (customButtonType) {
            case "button":
            case "trigCue":
            case "nextCue":
            case "initCue":
            case "prevCue":
            case "trigCounter":
            case "setRef":
                padPaint.setColor(color);
                paint.setColor(color);
                break;
            case "pad":
                paint.setColor(color);
                break;
            case "checkbox":
                paint.setColor(selected ? selectedColor : newGrayColor);
                break;
            case "vslider":
            case "hslider":
            case "vbargraph":
            case "hbargraph":
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

        rectF.set(lineWidth , lineWidth , getWidth() - lineWidth, getHeight() - lineWidth);
        canvas.drawRoundRect(rectF, 10, 10, paint);

        switch (customButtonType) {
            case "button":
            case "trigCue":
            case "nextCue":
            case "initCue":
            case "prevCue":
            case "trigCounter":
            case "setRef":
                padPaint.setStyle(Paint.Style.STROKE);
                // Draw horizontal line
                canvas.drawRoundRect(rectF, 10, 10, padPaint);
                break;
            case "vslider":
            case "vbargraph":
                padPaint.setStyle(Paint.Style.FILL);
                // Draw horizontal line
                canvas.drawRoundRect(horizontalLine, 10, 10, padPaint);
                break;
            case "hslider":
            case "hbargraph":
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


        // Set the paint color for text
        paint.setColor(Color.BLACK);
        paint.setTextAlign(Paint.Align.CENTER);
        paint.setTextSize(Math.min(getWidth()*0.3f, getHeight()*0.3f));

        String buttonText = nameForButton != null ? nameForButton : "";

        // Define the maximum allowed text size for height constraints
        float maxHeight = getHeight(); // Set your maximum height constraint

        // Calculate the maximum text size based on width constraint
        float textWidth = paint.measureText(buttonText);
        float availableWidth = getWidth(); // Set your available width constraint

        if (textWidth > availableWidth) {
            // Calculate the new text size to fit the width
            float widthTextSize = paint.getTextSize() * availableWidth / textWidth;

            // Check if the width-constrained text size fits within the height constraint
            paint.setTextSize(widthTextSize);
            float heightTextSize = getMaxTextSizeThatFitsHeight(buttonText, paint, maxHeight);

            // Set the text size to the minimum of width and height constrained text sizes
            float finalTextSize = Math.min(widthTextSize, heightTextSize) * 0.95f;
            paint.setTextSize(finalTextSize);
        } else {
            // Check if the current text size fits within the height constraint
            float currentTextSize = paint.getTextSize();
            float heightTextSize = getMaxTextSizeThatFitsHeight(buttonText, paint, maxHeight);

            // Set the text size to the minimum of current and height constrained text sizes
            float finalTextSize = Math.min(currentTextSize, heightTextSize) * 0.95f;
            paint.setTextSize(finalTextSize);
        }

        // Optionally, apply other text styling such as bold
        paint.setFakeBoldText(true);


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
                    case "checkbox":
                        updateButtonSelectedColor(selected);
                        break;
                    case "button":
                    case "trigCue":
                    case "nextCue":
                    case "initCue":
                    case "prevCue":
                    case "trigCounter":
                    case "setRef":
                        padPaint.setStrokeWidth(6);
                        paint.setColor(newbgColor);
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
                        padPaint.setStrokeWidth(0);
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
                    case "checkbox":
                        updateButtonSelectedColor(selected);
                        break;
                    case "button":
                    case "trigCue":
                    case "nextCue":
                    case "initCue":
                    case "prevCue":
                    case "trigCounter":
                    case "setRef":
                        paint.setColor(newbgColor);
                        padPaint.setStrokeWidth(6);
                        break;
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
                        verticalLine.set(0 + (lineWidth*2 / 2), 0 + (lineWidth*2 / 2), touchX - (lineWidth *2/ 2), getHeight() - (lineWidth *2/ 2));

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
                        horizontalLine.set(0 + (lineWidth *2/ 2), touchY + (lineWidth *2/ 2), getWidth() - (lineWidth *2/ 2), height - (lineWidth *2/ 2));

                        // Request a redraw of the button
                        invalidate();

                        break;
                    case "pad":

                        paint.setColor(newbgColor);
                        padPaint.setColor(newSelectedColor);

                        // Ensure the touch coordinates stay within the button bounds
                        touchX = Math.max(0, Math.min(getWidth(), touchX));
                        touchY = Math.max(0, Math.min(getHeight(), touchY));

                        horizontalLine.left = 0;
                        horizontalLine.right = getWidth() ;
                        horizontalLine.top = touchY - (lineWidth / 2);
                        horizontalLine.bottom = (touchY + lineWidth / 2);

                        verticalLine.left = (touchX - lineWidth / 2);
                        verticalLine.right = (touchX + lineWidth / 2);
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
                verticalLine = new RectF(0 + (lineWidth *2/ 2), 0 + (lineWidth *2/ 2), lineInitX - (lineWidth *2/ 2) , getHeight() - (lineWidth *2/ 2));

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
                horizontalLine = new RectF(0 + (lineWidth *2/ 2), lineInitY + (lineWidth *2/ 2) , getWidth() - (lineWidth *2/ 2), getHeight()  - (lineWidth *2/ 2));

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
                horizontalLine = new RectF(0 , lineInitY , getWidth() , lineInitY + lineWidth );
                verticalLine = new RectF(lineInitX , 0 , lineInitX + lineWidth , getHeight());

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


    public void setupVumeterXButton() {
        // Remove any touch event listener for vumeter, as it's passive

        paint.setColor(newGrayColor);
        padPaint.setColor(selectedColor);
        // Listen for size changes
        getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                // Remove the listener to avoid redundant calls
                getViewTreeObserver().removeOnGlobalLayoutListener(this);

                // Calculate the initial positions for lines (assuming lineInits contains X values)
                float lineInitX = mapValue(initValues.get(0), 0, 1, 0, getWidth());

                // Update the positions of the lines represented by RectF objects
                verticalLine = new RectF(0 + (lineWidth * 2 / 2), 0 + (lineWidth * 2 / 2),
                        lineInitX - (lineWidth * 2 / 2), getHeight() - (lineWidth * 2 / 2));

                // Trigger a redraw to reflect the changes
                invalidate();
            }
        });
    }

    public void updateVumeterXButton(float value) {
        // Clamp the incoming value and map it to the view width
        float normalisedX = clampValue(value, 0, 1);
        float lineWidthX = mapValue(normalisedX, 0, 1, 0, getWidth());

        paint.setColor(newGrayColor);
        padPaint.setColor(selectedColor);

        // Update the RectF for the vumeter
        verticalLine = new RectF(0 + (lineWidth * 2 / 2), 0 + (lineWidth * 2 / 2),
                lineWidthX - (lineWidth * 2 / 2), getHeight() - (lineWidth * 2 / 2));

        // Redraw the view
        invalidate();
    }

    public void setupVumeterYButton() {
        // Remove any touch event listener for vumeter, as it's passive

        paint.setColor(newGrayColor);
        padPaint.setColor(selectedColor);

        // Listen for size changes
        getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                // Remove the listener to avoid redundant calls
                getViewTreeObserver().removeOnGlobalLayoutListener(this);

                // Calculate the initial positions for lines (assuming lineInits contains Y values)
                float lineInitY = mapValue(initValues.get(0), 0, 1, getHeight(), 0);

                // Update the positions of the lines represented by RectF objects
                horizontalLine = new RectF(0 + (lineWidth * 2 / 2), lineInitY + (lineWidth * 2 / 2),
                        getWidth() - (lineWidth * 2 / 2), getHeight() - (lineWidth * 2 / 2));

                // Trigger a redraw to reflect the changes
                invalidate();
            }
        });
    }

    public void updateVumeterYButton(float value) {
        // Clamp the incoming value and map it to the view height
        float normalisedY = clampValue(value, 0, 1);
        float lineHeightY = mapValue(normalisedY, 0, 1, getHeight(), 0);

        paint.setColor(newGrayColor);
        padPaint.setColor(selectedColor);
        
        // Update the RectF for the vumeter
        horizontalLine = new RectF(0 + (lineWidth * 2 / 2), lineHeightY + (lineWidth * 2 / 2),
                getWidth() - (lineWidth * 2 / 2), getHeight() - (lineWidth * 2 / 2));

        // Redraw the view
        invalidate();
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


    // Helper function to calculate maximum text size that fits within a specified height
    private float getMaxTextSizeThatFitsHeight(String text, Paint paint, float maxHeight) {
        float textSize = paint.getTextSize();
        while (getTextHeight(text, paint) > maxHeight && textSize > 0) {
            textSize--;
            paint.setTextSize(textSize);
        }
        return textSize;
    }

    // Helper function to get the height of the text
    private float getTextHeight(String text, Paint paint) {
        Rect textBounds = new Rect();
        paint.getTextBounds(text, 0, text.length(), textBounds);
        return textBounds.height();
    }


}





