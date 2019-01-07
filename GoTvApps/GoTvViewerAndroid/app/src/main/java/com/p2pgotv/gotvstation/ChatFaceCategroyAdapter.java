// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )
package com.p2pgotv.gotvstation;

import java.util.ArrayList;
import java.util.Map;
import java.util.Set;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

public class ChatFaceCategroyAdapter extends FragmentPagerAdapter implements ChatPagerSlidingTabStrip.ChatIconTabProvider
{	
	private ChatOnOperationListener 		m_OnOperationListener;
	private Map<Integer, ArrayList<String>> m_CatagoryMap;

    //========================================================================
	public ChatFaceCategroyAdapter( FragmentManager fm ) 
	{
		super(fm);	
	}

    //========================================================================	
	@Override
	public int getPageIconResId(int position) 
	{	
//		return ICONS[position];
		Set<Integer> keys = m_CatagoryMap.keySet();
		Integer[] arrayIconIds = keys.toArray(new Integer[keys.size()]);		
		return (int) arrayIconIds[position];
	}

    //========================================================================	
	@Override
	public int getCount() 
	{
		return m_CatagoryMap == null ? 0 : m_CatagoryMap.size();
	}
	
	//========================================================================	
	@Override
	public Fragment getItem( int position ) 
	{
		ChatFacePageFragment f = new ChatFacePageFragment();
		f.setOnOperationListener( m_OnOperationListener );
		Bundle b = new Bundle();
		b.putInt(ChatFacePageFragment.ARG_POSITION, position);
		b.putStringArrayList(ChatFacePageFragment.ARG_FACE_DATA, m_CatagoryMap.get(m_CatagoryMap.keySet().toArray()[position]));
//		b.putSerializable(FacePageFragment.ARG_LISTTENER,onOperationListener);
		f.setArguments(b);
		return f;
	}

	//========================================================================	
	public ChatOnOperationListener getOnOperationListener() 
	{
		return m_OnOperationListener;
	}

	//========================================================================	
	public void setOnOperationListener(ChatOnOperationListener onOperationListener) 
	{
		this.m_OnOperationListener = onOperationListener;
	}

	//========================================================================	
	public Map<Integer, ArrayList<String>> getData() 
	{
		return m_CatagoryMap;
	}

	//========================================================================	
	public void setData( Map<Integer, ArrayList<String>> data )
	{
		this.m_CatagoryMap = data;
		notifyDataSetChanged();
	}
}
