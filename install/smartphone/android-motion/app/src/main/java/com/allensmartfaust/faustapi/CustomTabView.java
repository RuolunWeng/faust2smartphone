package com.allensmartfaust.faustapi;

import com.allensmartfaust.faustapi.CustomButton;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class CustomTabView extends LinearLayout {

    private Map<String, FrameLayout> contentLayouts;
    private FrameLayout contentLayout;
    private LinearLayout tabLayout;
    private List<TextView> tabButtons = new ArrayList<>(); // Declare tabButtons list

    public CustomTabView(Context context) {
        super(context);
        init();
    }

    public CustomTabView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        setOrientation(VERTICAL);
        contentLayouts = new HashMap<>();
        contentLayout = new FrameLayout(getContext());
        tabLayout = new LinearLayout(getContext());
        tabLayout.setOrientation(HORIZONTAL);
        addView(tabLayout);
        addView(contentLayout);
    }

    public void addTab(final String title, View contentView) {
        // Check if a content view with the same title already exists
        FrameLayout existingContentView = contentLayouts.get(title);
        if (existingContentView != null) {
            // Add content to the existing content view
            // Merge the new contentView with the existing one
            mergeContentViews(existingContentView, contentView);

        } else {
            // Create a new content view and add it to the map and content layout

            FrameLayout subContentLayout = new FrameLayout(getContext());
            contentLayouts.put(title, subContentLayout);
            subContentLayout.addView(contentView);

            contentLayout.addView(subContentLayout);
            //contentView.setVisibility(View.GONE); // Hide content initially

            // Create a tab button and add it to the tab layout
            TextView tabButton = createTabButton(title);
            // Add the created tab button to the list
            tabButtons.add(tabButton);
            //tabLayout.addView(tabButton);
        }

        //setupTabButtons();
    }

    private void mergeContentViews(FrameLayout existingContentViewFrameLayout, View newContentView) {
        // Perform merging operations as needed
        // For example, if both are LinearLayouts, you can merge their children
        if (newContentView instanceof CustomButton) {

            // Add the new CustomButton to the FrameLayout
            CustomButton newButton = (CustomButton) newContentView;
            existingContentViewFrameLayout.addView(newButton);

        } else {
            // Handle other types of content views as needed
        }
    }

    private TextView createTabButton(final String title) {
        final TextView tabButton = new TextView(getContext());
        tabButton.setText(title);
        tabButton.setGravity(Gravity.CENTER); // Set text alignment to center
        tabButton.setSingleLine(true); // Ensure that the text is displayed in a single line
        tabButton.setEllipsize(TextUtils.TruncateAt.END); // Truncate the text if it's too long
        tabButton.setTextSize(TypedValue.COMPLEX_UNIT_SP, 16); // Set the initial text size

        // Add a ViewTreeObserver to adjust the text size when the view is laid out
        tabButton.getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener() {
            @Override
            public void onGlobalLayout() {
                // Calculate the available width for the text
                int availableWidth = tabButton.getWidth() - tabButton.getPaddingLeft() - tabButton.getPaddingRight();

                // Get the text width
                float textWidth = tabButton.getPaint().measureText(title);

                // Adjust the text size to fit the available width
                if (textWidth > availableWidth) {
                    // Calculate the new text size to fit the width
                    float newTextSize = tabButton.getTextSize() * availableWidth / textWidth;

                    // Set the new text size
                    tabButton.setTextSize(TypedValue.COMPLEX_UNIT_PX, newTextSize);
                }

                // Remove the ViewTreeObserver to prevent multiple calls
                tabButton.getViewTreeObserver().removeOnGlobalLayoutListener(this);
            }
        });

        // Set the layout params to match_parent for width
        LayoutParams layoutParams = new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.MATCH_PARENT);
        tabButton.setLayoutParams(layoutParams);

        tabButton.setTextColor(Color.WHITE);
        // Set background color for the tab button
        // Set background drawable with rounded corners
        float radius = 20; // Adjust the radius as needed
        GradientDrawable background = new GradientDrawable();
        background.setShape(GradientDrawable.RECTANGLE);
        background.setCornerRadius(radius);
        background.setColor(Color.argb(255,50,50,50)); // Set background color
        tabButton.setBackground(background);
        //tabButton.setBackgroundColor(Color.argb(255,50,50,50)); // Example color, you can customize this
        tabButton.setPadding(16, 8, 16, 8); // Adjust padding as needed

        tabButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // Deselect all other tab buttons
                for (TextView button : tabButtons) {
                    // Set background drawable with rounded corners
                    float radius = 20; // Adjust the radius as needed
                    GradientDrawable background = new GradientDrawable();
                    background.setShape(GradientDrawable.RECTANGLE);
                    background.setCornerRadius(radius);
                    background.setColor(Color.argb(255,50,50,50)); // Set background color
                    button.setBackground(background);
                }

                // Select the clicked tab button
                // Set background drawable with rounded corners
                float radius = 20; // Adjust the radius as needed
                GradientDrawable background = new GradientDrawable();
                background.setShape(GradientDrawable.RECTANGLE);
                background.setCornerRadius(radius);
                background.setColor(Color.argb(255,122,0,0)); // Set background color
                tabButton.setBackground(background);

                // Show the corresponding content view
                String selectedTitle = tabButton.getText().toString();
                if (contentLayouts.containsKey(selectedTitle)) {
                    showContentView(selectedTitle);
                }
            }
        });

        return tabButton;
    }


    public void setupTabButtons() {

        if (tabButtons.size() == 0) {
            return; // No tab buttons to set up
        }

        tabLayout.removeAllViews();
        // Sort the tab buttons alphabetically based on their text
        Collections.sort(tabButtons, new Comparator<TextView>() {
            @Override
            public int compare(TextView button1, TextView button2) {
                return button1.getText().toString().compareToIgnoreCase(button2.getText().toString());
            }
        });


        int buttonWidth = getWidth() / tabButtons.size();
        int buttonHeight = 120; // Set a fixed height for the tab buttons
        int buttonY = 0;
        for (int i = 0; i < tabButtons.size(); i++) {
            final TextView currentButton = tabButtons.get(i); // Declare currentButton as final
            int buttonX = i * buttonWidth;
            currentButton.setWidth(buttonWidth);
            currentButton.setHeight(buttonHeight);
            currentButton.setX(buttonX);
            currentButton.setY(buttonY);
            tabLayout.addView(currentButton);
        }

        if (tabButtons.size()>0) {
            // Show the corresponding content view
            String selectedTitle = tabButtons.get(0).getText().toString();
            // Select the clicked tab button
            float radius = 20; // Adjust the radius as needed
            GradientDrawable background = new GradientDrawable();
            background.setShape(GradientDrawable.RECTANGLE);
            background.setCornerRadius(radius);
            background.setColor(Color.argb(255,122,0,0)); // Set background color
            tabButtons.get(0).setBackground(background);

            if (contentLayouts.containsKey(selectedTitle)) {
                showContentView(selectedTitle);
            }
        }

    }

    @Override
    protected void onLayout(boolean changed, int left, int top, int right, int bottom) {
        super.onLayout(changed, left, top, right, bottom);

        if (changed) {
            setupTabButtons();
        }

    }

    public void showContentView(final String title) {
        /*// Iterate through all content views
        for (Map.Entry<String, View> entry : contentViews.entrySet()) {
            String contentViewTitle = entry.getKey();
            View contentView = entry.getValue();
            // Check if the current content view matches the title
            if (contentViewTitle.equals(title)) {
                // Show the current content view
                contentView.setVisibility(View.VISIBLE);
            } else {
                // Hide other content views
                contentView.setVisibility(View.INVISIBLE);
            }
        }*/

        // Iterate through all content views
        for (Map.Entry<String, FrameLayout> entry : contentLayouts.entrySet()) {
            String contentViewTitle = entry.getKey();
            FrameLayout contentLayout = entry.getValue();
            // Check if the current content view matches the title
            if (contentViewTitle.equals(title)) {
                setVisibilityForAllViews(contentLayout,View.VISIBLE);
                // Show the current content view
            } else {
                // Hide other content views
                setVisibilityForAllViews(contentLayout,View.INVISIBLE);
            }
        }
    }


    public static void setVisibilityForAllViews(ViewGroup viewGroup, int visibility) {
        for (int i = 0; i < viewGroup.getChildCount(); i++) {
            View child = viewGroup.getChildAt(i);
            child.setVisibility(visibility);
            if (child instanceof ViewGroup) {
                // If the child is a ViewGroup, recursively set visibility for its children
                setVisibilityForAllViews((ViewGroup) child, visibility);
            }
        }
    }


}

