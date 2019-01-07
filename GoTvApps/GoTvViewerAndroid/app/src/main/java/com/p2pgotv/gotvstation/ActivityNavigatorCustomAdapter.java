package com.p2pgotv.gotvstation;

import java.io.File;
import java.util.ArrayList;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class ActivityNavigatorCustomAdapter extends ArrayAdapter<File> 
{
	private ArrayList<File> 	m_ItemsList;
	private Context 			m_Context = null;
	/**
	* Standard Data Adapter Construction
	*/
	public ActivityNavigatorCustomAdapter(Context context, int textViewResourceId, ArrayList<File> items) 
	{
		super(context, textViewResourceId, items);
		this.m_ItemsList 		= items;
		this.m_Context 			= context;
	}
	
	/**
	* Code invoked when container notifies data set of change.
	*/
	@Override
	public View getView(int position, View convertView, ViewGroup parent) 
	{
		View v = convertView;
		if (v == null) 
		{
			LayoutInflater vi = (LayoutInflater)m_Context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			v = vi.inflate(R.layout.nav_row, null);
		}
		
		TextView filename = null;
		ImageView fileicon = null;
		File f = m_ItemsList.get(position);
		if (f != null) 
		{
			filename = (TextView) v.findViewById(R.id.filename);
			fileicon = (ImageView) v.findViewById(R.id.fileicon);
		}
		
		if (filename != null) 
		{
			if (position == 0) 
			{
				filename.setText(f.getAbsolutePath());
			} 
			else if (position == 1) 
			{
				filename.setText(f.getAbsolutePath());
			} 
			else 
			{
				filename.setText(f.getName());
			}
		}
		
		if (fileicon != null) 
		{
			if (position == 0) 
			{
				fileicon.setImageResource(R.drawable.nav_root);
			} 
			else if (position == 1) 
			{
				fileicon.setImageResource(R.drawable.nav_up);
			} 
			else if (f.isDirectory()) 
			{
				fileicon.setImageResource(R.drawable.nav_folder);
			} 
			else 
			{
				fileicon.setImageResource(R.drawable.nav_file);
			}
		}
		
		return v;
	}
}