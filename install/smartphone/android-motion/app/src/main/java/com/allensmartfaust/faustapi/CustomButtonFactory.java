package com.allensmartfaust.faustapi;

import com.allensmartfaust.faustapi.CustomButton;

import android.content.Context;
import android.util.AttributeSet;
import android.view.ViewGroup;

import java.util.ArrayList;

public class CustomButtonFactory {

    private static int padding = 4;

    public static CustomButton createButton(Context context, AttributeSet attrs) {
        return new CustomButton(context, attrs);
    }

    public static CustomButton createButton(Context context) {
        return new CustomButton(context);
    }

    public static CustomButton createButtonWithParams(Context context, String buttonType,
                                                      int x, int y, int width, int height,
                                                      String name, String path, int tag,
                                                      int selectedColor, ArrayList<Float> initValues) {
        CustomButton button = new CustomButton(context);
        button.setCustomButtonType(buttonType);
        // Create layout parameters with x and y coordinates
        ViewGroup.MarginLayoutParams layoutParams = new ViewGroup.MarginLayoutParams(width - padding*2, height- padding*2);
        layoutParams.leftMargin = x + padding;
        layoutParams.topMargin = y + padding;
        button.setLayoutParams(layoutParams);
/*        ViewGroup.LayoutParams layoutParams = new ViewGroup.LayoutParams(width, height);
        button.setLayoutParams(layoutParams);
        button.setX(x);
        button.setY(y);*/
        button.setNameForButton(name);
        button.setPathForButton(path);
        button.setTag(tag);
        button.setSelectedColor(selectedColor);
        button.setInitValuesForButton(initValues);
        button.setLineWidth(2);

        // Additional setup based on button type
        switch (buttonType) {
            case "checkbox":
                button.setupToggleButton();
                break;
            case "trigCue":
                button.setupTrigCueButton();
                break;
            case "nextCue":
                button.setupNextCueButton();
                break;
            case "prevCue":
                button.setupPrevCueButton();
                break;
            case "initCue":
                button.setupInitCueButton();
                break;
            case "setRef":
                button.setupSetRefButton();
                break;
            case "trigCounter":
                button.setupTrigCounterButton();
                break;
            case "hslider":
                button.setupTouchScreenXButton();
                break;
            case "vslider":
                button.setupTouchScreenYButton();
                break;
            case "pad":
                button.setupPadButton();
                break;
            case "button":
                button.setupButton();
                break;
            default:
                break;
        }

        return button;
    }
}
