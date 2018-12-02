// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )
package com.p2pgotv.gotvstation;

import android.content.Context;
import android.graphics.drawable.Drawable;

public class ChatOption 
{	
	private String 				m_OptionName;
	private Drawable 			m_OptionIconDrawable;
		
	//========================================================================
	public ChatOption(String name, Drawable iconDrawable) 
	{
		super();
		this.m_OptionName 			= name;
		this.m_OptionIconDrawable 	= iconDrawable;
	}
	
	//========================================================================
	public ChatOption(Context context, String name, int iconResId) 
	{
		super();
		this.m_OptionName 			= name;
		this.m_OptionIconDrawable 	= context.getResources().getDrawable(iconResId);
	}
	
	//========================================================================
	public String getName() 
	{
		return m_OptionName;
	}
	
	//========================================================================
	public void setName(String name) 
	{
		this.m_OptionName = name;
	}
	
	//========================================================================
	public Drawable getIconDrawable() 
	{
		return m_OptionIconDrawable;
	}
	
	//========================================================================
	public void setIconDrawable(Drawable iconDrawable) 
	{
		this.m_OptionIconDrawable = iconDrawable;
	}
}
