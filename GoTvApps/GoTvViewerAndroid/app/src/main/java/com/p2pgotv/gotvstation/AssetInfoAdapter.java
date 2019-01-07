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

import java.util.ArrayList;
import java.util.concurrent.Semaphore;
//import java.util.Iterator;

//import android.app.ProgressDialog;
import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

class AssetGuiInfoAdapter extends ArrayAdapter<AssetGuiInfo> 
{	
	//=== constants ===//
	private static final String LOG_TAG = "ContactsAdapter:";  
	static final int OFFLINE_COLOR 		= 0xff969696;
	static final int ONLINE_COLOR 		= 0xff00ff00;
	static final int NEARBY_COLOR 		= 0xff1515ff;
	
	//=== vars ===//
	private ArrayList<AssetGuiInfo> 	items;

	private Semaphore m_oMutex = new Semaphore(1);
	public final  ArrayList<VxNetIdent> m_HisIdentsToUpdate = new  ArrayList<VxNetIdent>();

	//=== methods ===//
	public AssetGuiInfoAdapter(Context context, int textViewResourceId, ArrayList<AssetGuiInfo> items) 
    {
		super(context, textViewResourceId, items);
		try 
		{
			m_oMutex.acquire();
		} 
		catch (InterruptedException e)  
		{
			e.printStackTrace();
		}

        this.items = items;
        m_oMutex.release();
    }
	
	//======================================================================== 
	public void clearList()
	{
		try 
		{
			m_oMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}	
		this.items.clear();
        m_oMutex.release();	
	}
	
	//======================================================================== 
    @Override
    public View getView(int position, View convertView, ViewGroup parent) 
    {
		try 
		{
			m_oMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
		
		Log.i(LOG_TAG, "getView position " + position );
    	View friendView = convertView;
        if( null == friendView ) 
        {
        	LayoutInflater vi = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        	friendView = vi.inflate(R.layout.contact_item, null);
        }
        
        AssetGuiInfo oIdent = items.get(position);
        if( null != oIdent ) 
        {
            TextView topText = (TextView) friendView.findViewById(R.id.toptext);
            TextView bottomText = (TextView) friendView.findViewById(R.id.bottomtext);
            TextView truthStatsText = (TextView) friendView.findViewById(R.id.truth_stats_text);
           
            /*
            int iMyFriendshipToHim = oIdent.getMyFriendshipToHim();
            //Log.i(LOG_TAG, "friendship " + iMyFriendshipToHim + " raw " + oIdent.m_u8FriendMatch );
            Log.i(LOG_TAG, "getView online status " + oIdent.isOnline() + " online flags " + oIdent.m_u8OnlineStatusFlags + " " + oIdent.getOnlineName() ); 
            
            int iTextColor = Constants.OFFLINE_COLOR;
        	if( oIdent.isNearby() )
        	{
                Log.d(LOG_TAG, oIdent.getOnlineName() + " is nearby " ); 
        		iTextColor = Constants.NEARBY_COLOR;
        	}
        	else if( oIdent.isOnline() )
        	{
                Log.d(LOG_TAG, oIdent.getOnlineName() + " is online " ); 
        		iTextColor = Constants.ONLINE_COLOR;
        	}
        	else
        	{
                Log.d(LOG_TAG, oIdent.getOnlineName() + " is offline " );
        	}

            if( null != topText ) 
            {
            	topText.setTextColor( iTextColor );
            	topText.setText(aoFriendshipDescriptions[ iMyFriendshipToHim ] + oIdent.getOnlineName());                            
            }
            
            if( null != bottomText ) 
            {
            	bottomText.setTextColor(iTextColor);
            	bottomText.setText( "Mood: " + oIdent.getOnlineDescription() );
            }

            if( null != truthStatsText ) 
            {
            	//truthStatsText.setTextColor(iTextColor);
            	String todText = "Truths: " + oIdent.getTruthCount() + " Dares: " + oIdent.getDareCount();
            	truthStatsText.setText( todText );
            }

            
            int iIconResource = Constants.getFriendIconResource(iMyFriendshipToHim);
 
    		ImageView view_icon = (ImageView)friendView.findViewById(R.id.friend_icon);
       	    Log.i(LOG_TAG, "icon " + view_icon.toString() );
    		view_icon.setImageResource(iIconResource);
    		*/
        }
        else
        {
            Log.e(LOG_TAG, "getView null ident at position " + position );      	
        }
        m_oMutex.release();
        return friendView;
    }
    
	//========================================================================   
    public AssetGuiInfo getFriendByPosition( int iPosition )
    {
		try 
		{
			m_oMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
    	if( iPosition < items.size() )
    	{    
    		AssetGuiInfo assetInfo = items.get( iPosition );
            m_oMutex.release();		
    		return assetInfo;
    	}
        m_oMutex.release();
   	    Log.i(LOG_TAG, "unable to get friend at " + iPosition );
		return null;
    }
    
	//========================================================================        
	public void doUpdateAssetGuiInfo( AssetGuiInfo assetInfoIn )  
    {
		try 
		{
			m_oMutex.acquire();
			boolean bFoundAsset = false;
	   	    Log.i(LOG_TAG, "doUpdateAssetGuiInfo " );  
	    	
	   	    int iPosition = 0;
	    	for( AssetGuiInfo assetInfo:  items )
	    	{
	    		if( assetInfo.m_UniqueId == assetInfoIn.m_UniqueId )
	    		{
	    			bFoundAsset = true;
	       	   	    items.set(iPosition, assetInfoIn ); 	       	   	    			
	    			break;  			
	    			
	    		}
	    		iPosition++; 
	    	}
	    	
	    	if( false == bFoundAsset )
	    	{
	    		items.add( assetInfoIn );
	    	}
	    	
	    	Log.i(LOG_TAG, "friend list count " + items.size() );	    	
	        m_oMutex.release();  
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
    }
}
