package com.p2pgotv.gotvstation;

import java.io.File;
import java.util.ArrayList;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.ListView;
import android.widget.Toast;	

public class ActivityNavigator extends ActivityListBase  
{
	private File mCurrentNode = null;
	private File mLastNode = null;
	private File mRootNode = null;
	private ArrayList<File> mFiles = new ArrayList<File>();
	private ActivityNavigatorCustomAdapter mAdapter = null;
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		setContentView(R.layout.main);
		super.onCreate(savedInstanceState);
		setPageTitle( R.string.activity_navigator_title );
		
		mAdapter = new ActivityNavigatorCustomAdapter(this, R.layout.nav_row, mFiles);
		setListAdapter(mAdapter);
		if (savedInstanceState != null) 
		{
			mRootNode = (File)savedInstanceState.getSerializable("root_node");
			mLastNode = (File)savedInstanceState.getSerializable("last_node");
			mCurrentNode = (File)savedInstanceState.getSerializable("current_node");
		}
		refreshFileList();
	}
	
	private void refreshFileList() 
	{
		if (mRootNode == null)
		{
			mRootNode = new File(Environment.getExternalStorageDirectory().toString());
		}
		if (mCurrentNode == null) mCurrentNode = mRootNode;
		mLastNode = mCurrentNode;
		File[] files = mCurrentNode.listFiles();
		mFiles.clear();
		mFiles.add(mRootNode);
		mFiles.add(mLastNode);
		if (files!=null) 
		{
			for (int i = 0; i< files.length; i++) mFiles.add(files[i]);
		}
		mAdapter.notifyDataSetChanged();
	}
	
	@Override
	protected void onSaveInstanceState(Bundle outState) 
	{
		outState.putSerializable("root_node", mRootNode);
		outState.putSerializable("current_node", mCurrentNode);
		outState.putSerializable("last_node", mLastNode);
		super.onSaveInstanceState(outState);
	}
	/**
	* Listview on click handler.
	*/
	@Override
	public void onListItemClick(ListView parent, View v, int position, long id)
	{
		File f = (File) parent.getItemAtPosition(position);
		if (position == 1) 
		{
			if (mCurrentNode.compareTo(mRootNode)!=0) 
			{
				mCurrentNode = f.getParentFile();
				refreshFileList();
			}
		} 
		else if (f.isDirectory()) 
		{
			mCurrentNode = f;
			refreshFileList();
		} 
		else 
		{
			Toast.makeText(this, "You selected: "+f.getName()+"!", Toast.LENGTH_SHORT).show();
		}
	}
}


