//============================================================================
// Copyright (C) 2015 Brett R. Jones
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not modify or redistribute this code for any reason
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett1900@usa.com
// http://www.gotvp2p.net
//============================================================================

package com.p2pgotv.gotvstation;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import android.content.Context;

import java.util.ArrayList;

public class CropImageOptionAdapter extends ArrayAdapter<CropImageOption> 
{
	private ArrayList<CropImageOption> 	m_CropImageOptionList;
	private LayoutInflater 		m_LayoutInflater;
	
	//============================================================================
	public CropImageOptionAdapter(Context context, ArrayList<CropImageOption> options) 
	{
		super( context, R.layout.crop_image_selector, options );	
		m_CropImageOptionList 	= options;
		m_LayoutInflater		= LayoutInflater.from(context);
	}
	
	//============================================================================
	@Override
	public View getView(int position, View convertView, ViewGroup group) 
	{
		if (convertView == null)
		{
			convertView = m_LayoutInflater.inflate(R.layout.crop_image_selector, null);
		}
		
		CropImageOption item = m_CropImageOptionList.get(position);
		
		if (item != null) 
		{
			((ImageView) convertView.findViewById(R.id.iv_icon)).setImageDrawable(item.icon);
			((TextView) convertView.findViewById(R.id.tv_name)).setText(item.title);
			
			return convertView;
		}
		
		return null;
	}
}
