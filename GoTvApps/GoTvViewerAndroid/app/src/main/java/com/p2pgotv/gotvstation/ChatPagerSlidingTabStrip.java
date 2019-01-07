/*
 * Copyright (C) 2013 Andreas Stuetz <andreas.stuetz@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.p2pgotv.gotvstation;

import java.util.Locale;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.Typeface;
import android.os.Build;
import android.os.Parcel;
import android.os.Parcelable;
import android.support.v4.view.ViewPager;
import android.support.v4.view.ViewPager.OnPageChangeListener;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewTreeObserver.OnGlobalLayoutListener;
import android.widget.HorizontalScrollView;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;

//========================================================================
@SuppressLint("NewApi")
public class ChatPagerSlidingTabStrip extends HorizontalScrollView 
{
	public interface ChatIconTabProvider 
	{
		public int getPageIconResId(int position);
	}

	// @formatter:off
	private static final int[] ATTRS = new int[] 
	{
		android.R.attr.textSize,
		android.R.attr.textColor
    };
	
	// @formatter:on
	private LinearLayout.LayoutParams m_DefaultTabLayoutParams;
	private LinearLayout.LayoutParams m_ExpandedTabLayoutParams;

	private final PageListener 		m_PageListener 			= new PageListener();
	public OnPageChangeListener 	m_DelegatePageListener;

	private LinearLayout 			m_TabsContainer;
	private ViewPager 				m_Pager;

	private int 					m_TabCount;

	private int 					m_CurrentPosition 		= 0;
	private float 					m_CurrentPositionOffset = 0f;

	private Paint 					m_RectPaint;
	private Paint 					m_DividerPaint;

	private int 					m_IndicatorColor 		= 0xFF666666;
	private int 					m_UnderlineColor 		= 0x1A000000;
	private int 					m_DividerColor 			= 0x1A000000;

	private boolean 				m_ShouldExpand 			= false;
	private boolean 				m_TextAllCaps 			= true;

	private int 					m_ScrollOffset 			= 52;
	private int 					m_IndicatorHeight 		= 8;
	private int 					m_UnderlineHeight 		= 2;
	private int 					m_DividerPadding 		= 12;
	private int 					m_TabPadding 			= 24;
	private int 					m_DividerWidth 			= 1;

	private int 					m_TabTextSize 			= 12;
	private int 					m_TabTextColor 			= 0xFF666666;
	private Typeface 				m_TabTypeface 			= null;
	private int 					m_TabTypefaceStyle 		= Typeface.BOLD;

	private int 					m_LastScrollX 			= 0;

	private int 					m_TabBackgroundResId 	= R.drawable.chat_background_tab;
	private Locale 					m_Locale;

	//========================================================================
	public ChatPagerSlidingTabStrip(Context context) 
	{
		this(context, null);
	}

	//========================================================================
	public ChatPagerSlidingTabStrip(Context context, AttributeSet attrs) 
	{
		this(context, attrs, 0);
	}

	//========================================================================
	public ChatPagerSlidingTabStrip(Context context, AttributeSet attrs, int defStyle) 
	{
		super(context, attrs, defStyle);

		setFillViewport(true);
		setWillNotDraw(false);

		m_TabsContainer = new LinearLayout(context);
		m_TabsContainer.setOrientation(LinearLayout.HORIZONTAL);
		m_TabsContainer.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
		addView(m_TabsContainer);

		DisplayMetrics dm = getResources().getDisplayMetrics();

		m_ScrollOffset 		= (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, m_ScrollOffset, dm);
		m_IndicatorHeight 	= (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, m_IndicatorHeight, dm);
		m_UnderlineHeight 	= (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, m_UnderlineHeight, dm);
		m_DividerPadding 	= (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, m_DividerPadding, dm);
		m_TabPadding 		= (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, m_TabPadding, dm);
		m_DividerWidth 		= (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, m_DividerWidth, dm);
		m_TabTextSize 		= (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_SP, m_TabTextSize, dm);

		// get system attrs (android:textSize and android:textColor)
		TypedArray a 		= context.obtainStyledAttributes(attrs, ATTRS);

		m_TabTextSize 		= a.getDimensionPixelSize(0, m_TabTextSize);
		m_TabTextColor 		= a.getColor(1, m_TabTextColor);

		a.recycle();
		// get custom attrs

		a = context.obtainStyledAttributes(attrs, R.styleable.ChatPagerSlidingTabStrip);

		m_IndicatorColor 		= a.getColor(R.styleable.ChatPagerSlidingTabStrip_pstsIndicatorColor, m_IndicatorColor);
		m_UnderlineColor 		= a.getColor(R.styleable.ChatPagerSlidingTabStrip_pstsUnderlineColor, m_UnderlineColor);
		m_DividerColor 			= a.getColor(R.styleable.ChatPagerSlidingTabStrip_pstsDividerColor, m_DividerColor);
		m_IndicatorHeight 		= a.getDimensionPixelSize(R.styleable.ChatPagerSlidingTabStrip_pstsIndicatorHeight, m_IndicatorHeight);
		m_UnderlineHeight 		= a.getDimensionPixelSize(R.styleable.ChatPagerSlidingTabStrip_pstsUnderlineHeight, m_UnderlineHeight);
		m_DividerPadding 		= a.getDimensionPixelSize(R.styleable.ChatPagerSlidingTabStrip_pstsDividerPadding, m_DividerPadding);
		m_TabPadding 			= a.getDimensionPixelSize(R.styleable.ChatPagerSlidingTabStrip_pstsTabPaddingLeftRight, m_TabPadding);
		m_TabBackgroundResId 	= a.getResourceId(R.styleable.ChatPagerSlidingTabStrip_pstsTabBackground, m_TabBackgroundResId);
		m_ShouldExpand 			= a.getBoolean(R.styleable.ChatPagerSlidingTabStrip_pstsShouldExpand, m_ShouldExpand);
		m_ScrollOffset 			= a.getDimensionPixelSize(R.styleable.ChatPagerSlidingTabStrip_pstsScrollOffset, m_ScrollOffset);
		m_TextAllCaps 			= a.getBoolean(R.styleable.ChatPagerSlidingTabStrip_pstsTextAllCaps, m_TextAllCaps);

		a.recycle();

		m_RectPaint 				= new Paint();
		m_RectPaint.setAntiAlias(true);
		m_RectPaint.setStyle(Style.FILL);

		m_DividerPaint 				= new Paint();
		m_DividerPaint.setAntiAlias(true);
		m_DividerPaint.setStrokeWidth(m_DividerWidth);

		m_DefaultTabLayoutParams 	= new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.MATCH_PARENT);
		m_ExpandedTabLayoutParams 	= new LinearLayout.LayoutParams(0, LayoutParams.MATCH_PARENT, 1.0f);

		if (m_Locale == null) 
		{
			m_Locale = getResources().getConfiguration().locale;
		}
	}

	//========================================================================
	public void setViewPager(ViewPager pager) 
	{
		this.m_Pager = pager;
		if( null == pager.getAdapter() ) 
		{
			throw new IllegalStateException("ViewPager does not have adapter instance.");
		}

		pager.setOnPageChangeListener( m_PageListener );

		notifyDataSetChanged();
	}

	//========================================================================
	public void setOnPageChangeListener(OnPageChangeListener listener) 
	{
		this.m_DelegatePageListener = listener;
	}

	//========================================================================
	public void notifyDataSetChanged() 
	{
		m_TabsContainer.removeAllViews();
		m_TabCount = m_Pager.getAdapter().getCount();

		for (int i = 0; i < m_TabCount; i++) 
		{
			if( m_Pager.getAdapter() instanceof ChatIconTabProvider ) 
			{
				addIconTab(i, ((ChatIconTabProvider) m_Pager.getAdapter()).getPageIconResId(i));
			} 
			else 
			{
				addTextTab( i, m_Pager.getAdapter().getPageTitle(i).toString() );
			}
		}

		updateTabStyles();

		getViewTreeObserver().addOnGlobalLayoutListener(new OnGlobalLayoutListener() 
		{
			@SuppressWarnings("deprecation")
			@SuppressLint("NewApi")
			@Override
			public void onGlobalLayout() 
			{
				if (Build.VERSION.SDK_INT < Build.VERSION_CODES.JELLY_BEAN) 
				{
					getViewTreeObserver().removeGlobalOnLayoutListener(this);
				} 
				else 
				{
					getViewTreeObserver().removeOnGlobalLayoutListener(this);
				}

				m_CurrentPosition = m_Pager.getCurrentItem();
				scrollToChild(m_CurrentPosition, 0);
			}
		});
	}

	//========================================================================
	private void addTextTab(final int position, String title) 
	{
		TextView tab = new TextView(getContext());
		tab.setText(title);
		tab.setGravity(Gravity.CENTER);
		tab.setSingleLine();

		addTab(position, tab);
	}

	//========================================================================
	private void addIconTab(final int position, int resId) 
	{
		ImageButton tab = new ImageButton(getContext());
		tab.setImageResource(resId);

		addTab(position, tab);
	}

	//========================================================================
	private void addTab(final int position, View tab) 
	{
		tab.setFocusable(true);
		tab.setOnClickListener(new OnClickListener() 
		{
			@Override
			public void onClick(View v) 
			{
	        	//m_MyApp.playButtonClick();
				m_Pager.setCurrentItem(position);
			}
		});

		tab.setPadding(m_TabPadding, 0, m_TabPadding, 0);
		m_TabsContainer.addView( tab, position, m_ShouldExpand ? m_ExpandedTabLayoutParams : m_DefaultTabLayoutParams );
	}

	//========================================================================
	private void updateTabStyles() 
	{
		for (int i = 0; i < m_TabCount; i++) 
		{
			View v = m_TabsContainer.getChildAt(i);
			v.setBackgroundResource( m_TabBackgroundResId );
			if( v instanceof TextView ) 
			{
				TextView tab = (TextView) v;
				tab.setTextSize(TypedValue.COMPLEX_UNIT_PX, m_TabTextSize);
				tab.setTypeface(m_TabTypeface, m_TabTypefaceStyle);
				tab.setTextColor(m_TabTextColor);

				// setAllCaps() is only available from API 14, so the upper case is made manually if we are on a
				// pre-ICS-build
				if( m_TextAllCaps ) 
				{
					if( Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH ) 
					{
						tab.setAllCaps(true);
					} 
					else 
					{
						tab.setText( tab.getText().toString().toUpperCase( m_Locale ) );
					}
				}
			}
		}
	}

	//========================================================================
	private void scrollToChild(int position, int offset) 
	{
		if( m_TabCount == 0 ) 
		{
			return;
		}

		int newScrollX = m_TabsContainer.getChildAt(position).getLeft() + offset;

		if (position > 0 || offset > 0) 
		{
			newScrollX -= m_ScrollOffset;
		}

		if (newScrollX != m_LastScrollX) 
		{
			m_LastScrollX = newScrollX;
			scrollTo(newScrollX, 0);
		}
	}

	//========================================================================
	@Override
	protected void onDraw(Canvas canvas) 
	{
		super.onDraw(canvas);

		if (isInEditMode() || m_TabCount == 0) 
		{
			return;
		}

		final int height = getHeight();

		// draw indicator line
		m_RectPaint.setColor(m_IndicatorColor);

		// default: line below current tab
		View currentTab 	= m_TabsContainer.getChildAt(m_CurrentPosition);
		float lineLeft 		= currentTab.getLeft();
		float lineRight 	= currentTab.getRight();

		// if there is an offset, start interpolating left and right coordinates between current and next tab
		if( m_CurrentPositionOffset > 0f && m_CurrentPosition < m_TabCount - 1 ) 
		{
			View nextTab = m_TabsContainer.getChildAt(m_CurrentPosition + 1);
			final float nextTabLeft = nextTab.getLeft();
			final float nextTabRight = nextTab.getRight();

			lineLeft = (m_CurrentPositionOffset * nextTabLeft + (1f - m_CurrentPositionOffset) * lineLeft);
			lineRight = (m_CurrentPositionOffset * nextTabRight + (1f - m_CurrentPositionOffset) * lineRight);
		}

		canvas.drawRect( lineLeft, height - m_IndicatorHeight, lineRight, height, m_RectPaint );

		// draw underline
		m_RectPaint.setColor( m_UnderlineColor );
		canvas.drawRect( 0, height - m_UnderlineHeight, m_TabsContainer.getWidth(), height, m_RectPaint );

		// draw divider
		m_DividerPaint.setColor(m_DividerColor);
		for (int i = 0; i < m_TabCount - 1; i++) 
		{
			View tab = m_TabsContainer.getChildAt(i);
			canvas.drawLine(tab.getRight(), m_DividerPadding, tab.getRight(), height - m_DividerPadding, m_DividerPaint);
		}
	}

	//========================================================================
	private class PageListener implements OnPageChangeListener 
	{
		@Override
		public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) 
		{
			m_CurrentPosition = position;
			m_CurrentPositionOffset = positionOffset;

			scrollToChild(position, (int) (positionOffset * m_TabsContainer.getChildAt(position).getWidth()));

			invalidate();

			if( m_DelegatePageListener != null ) 
			{
				m_DelegatePageListener.onPageScrolled(position, positionOffset, positionOffsetPixels);
			}
		}

		@Override
		public void onPageScrollStateChanged(int state) 
		{
			if (state == ViewPager.SCROLL_STATE_IDLE) 
			{
				scrollToChild(m_Pager.getCurrentItem(), 0);
			}

			if( m_DelegatePageListener != null ) 
			{
				m_DelegatePageListener.onPageScrollStateChanged(state);
			}
		}

		@Override
		public void onPageSelected(int position) 
		{
			if( m_DelegatePageListener != null ) 
			{
				m_DelegatePageListener.onPageSelected(position);
			}
		}
	}

	//========================================================================
	public void setIndicatorColor(int indicatorColor) 
	{
		this.m_IndicatorColor = indicatorColor;
		invalidate();
	}

	//========================================================================
	public void setIndicatorColorResource(int resId) 
	{
		this.m_IndicatorColor = getResources().getColor(resId);
		invalidate();
	}

	//========================================================================
	public int getIndicatorColor() 
	{
		return this.m_IndicatorColor;
	}

	//========================================================================
	public void setIndicatorHeight(int indicatorLineHeightPx) 
	{
		this.m_IndicatorHeight = indicatorLineHeightPx;
		invalidate();
	}

	//========================================================================
	public int getIndicatorHeight() 
	{
		return m_IndicatorHeight;
	}

	//========================================================================
	public void setUnderlineColor(int underlineColor) 
	{
		this.m_UnderlineColor = underlineColor;
		invalidate();
	}

	//========================================================================
	public void setUnderlineColorResource(int resId) 
	{
		this.m_UnderlineColor = getResources().getColor(resId);
		invalidate();
	}

	//========================================================================
	public int getUnderlineColor() 
	{
		return m_UnderlineColor;
	}

	//========================================================================
	public void setDividerColor(int dividerColor) 
	{
		this.m_DividerColor = dividerColor;
		invalidate();
	}

	//========================================================================
	public void setDividerColorResource(int resId) 
	{
		this.m_DividerColor = getResources().getColor(resId);
		invalidate();
	}

	//========================================================================
	public int getDividerColor()
	{
		return m_DividerColor;
	}

	//========================================================================
	public void setUnderlineHeight(int underlineHeightPx) 
	{
		this.m_UnderlineHeight = underlineHeightPx;
		invalidate();
	}

	//========================================================================
	public int getUnderlineHeight() 
	{
		return m_UnderlineHeight;
	}

	//========================================================================
	public void setDividerPadding(int dividerPaddingPx) 
	{
		this.m_DividerPadding = dividerPaddingPx;
		invalidate();
	}

	//========================================================================
	public int getDividerPadding() 
	{
		return m_DividerPadding;
	}

	//========================================================================
	public void setScrollOffset(int scrollOffsetPx) 
	{
		this.m_ScrollOffset = scrollOffsetPx;
		invalidate();
	}

	//========================================================================
	public int getScrollOffset() 
	{
		return m_ScrollOffset;
	}

	//========================================================================
	public void setShouldExpand(boolean shouldExpand) 
	{
		this.m_ShouldExpand = shouldExpand;
		requestLayout();
	}

	//========================================================================
	public boolean getShouldExpand() 
	{
		return m_ShouldExpand;
	}

	//========================================================================
	public boolean isTextAllCaps() 
	{
		return m_TextAllCaps;
	}

	//========================================================================
	public void setAllCaps(boolean textAllCaps) 
	{
		this.m_TextAllCaps = textAllCaps;
	}

	//========================================================================
	public void setTextSize(int textSizePx) 
	{
		this.m_TabTextSize = textSizePx;
		updateTabStyles();
	}

	//========================================================================
	public int getTextSize() 
	{
		return m_TabTextSize;
	}

	//========================================================================
	public void setTextColor(int textColor) 
	{
		this.m_TabTextColor = textColor;
		updateTabStyles();
	}

	//========================================================================
	public void setTextColorResource(int resId) 
	{
		this.m_TabTextColor = getResources().getColor(resId);
		updateTabStyles();
	}

	//========================================================================
	public int getTextColor() 
	{
		return m_TabTextColor;
	}

	//========================================================================
	public void setTypeface(Typeface typeface, int style) 
	{
		this.m_TabTypeface = typeface;
		this.m_TabTypefaceStyle = style;
		updateTabStyles();
	}

	//========================================================================
	public void setTabBackground(int resId) 
	{
		this.m_TabBackgroundResId = resId;
	}

	//========================================================================
	public int getTabBackground() 
	{
		return m_TabBackgroundResId;
	}

	//========================================================================
	public void setTabPaddingLeftRight(int paddingPx) 
	{
		this.m_TabPadding = paddingPx;
		updateTabStyles();
	}

	//========================================================================
	public int getTabPaddingLeftRight() 
	{
		return m_TabPadding;
	}

	//========================================================================
	@Override
	public void onRestoreInstanceState(Parcelable state) 
	{
		SavedState savedState = (SavedState) state;
		super.onRestoreInstanceState(savedState.getSuperState());
		m_CurrentPosition = savedState.currentPosition;
		requestLayout();
	}

	//========================================================================
	@Override
	public Parcelable onSaveInstanceState() 
	{
		Parcelable superState = super.onSaveInstanceState();
		SavedState savedState = new SavedState(superState);
		savedState.currentPosition = m_CurrentPosition;
		return savedState;
	}

	//========================================================================
	static class SavedState extends BaseSavedState 
	{
		int currentPosition;

		public SavedState(Parcelable superState) 
		{
			super(superState);
		}

		private SavedState(Parcel in) 
		{
			super(in);
			currentPosition = in.readInt();
		}

		@Override
		public void writeToParcel(Parcel dest, int flags) 
		{
			super.writeToParcel(dest, flags);
			dest.writeInt(currentPosition);
		}

		public static final Parcelable.Creator<SavedState> CREATOR = new Parcelable.Creator<SavedState>() 
		{
			@Override
			public SavedState createFromParcel(Parcel in) 
			{
				return new SavedState(in);
			}

			@Override
			public SavedState[] newArray(int size) 
			{
				return new SavedState[size];
			}
		};
	}
}
