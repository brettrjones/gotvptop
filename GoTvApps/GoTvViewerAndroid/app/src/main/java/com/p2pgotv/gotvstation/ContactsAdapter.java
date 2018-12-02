//============================================================================
// Copyright (C) 2011 Brett R. Jones
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

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

class ContactsAdapter extends ArrayAdapter<VxNetIdent> 
{	
	//=== constants ===//
	private static final String LOG_TAG = "ContactsAdapter:";  
	
	//=== vars ===//
	private ArrayList<VxNetIdent> 	items;

	private Semaphore m_oMutex = new Semaphore(1);
	public final  ArrayList<VxNetIdent> m_HisIdentsToUpdate = new  ArrayList<VxNetIdent>();
	VxGUID						m_ViewingOnlineId			= new VxGUID();
	boolean						m_IsCurrentlyViewing 		= false;

	//======================================================================== 
	public ContactsAdapter(Context context, int textViewResourceId, ArrayList<VxNetIdent> items) 
    {
		super(context, textViewResourceId, items);
		lockContactsAdapter();
        this.items = items;
        unlockContactsAdapter();
    }
	
	//======================================================================== 
	public void lockContactsAdapter()
	{
		try 
		{
			m_oMutex.acquire();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}	
	}
	
	//======================================================================== 
	public void unlockContactsAdapter()
	{
        m_oMutex.release();		
	}
	
	//======================================================================== 
	public void clearList()
	{
		lockContactsAdapter();
		this.items.clear();
		unlockContactsAdapter();	
	}
	
	//======================================================================== 
    @Override
    public View getView(int position, View convertView, ViewGroup parent) 
    {
    	lockContactsAdapter();
		//Log.i(LOG_TAG, "getView position " + position );
    	View friendView = convertView;
        if( null == friendView ) 
        {
        	LayoutInflater vi = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        	friendView = vi.inflate(R.layout.contact_item, null);
        }
        
        VxNetIdent oIdent = items.get(position);
        if( null != oIdent ) 
        {
            TextView topText = (TextView) friendView.findViewById(R.id.toptext);
            TextView bottomText = (TextView) friendView.findViewById(R.id.bottomtext);
            TextView truthStatsText = (TextView) friendView.findViewById(R.id.truth_stats_text);
            //Button menuButton = (Button) friendView.findViewById(R.id.friend_menu_button);
                     
            int iMyFriendshipToHim = oIdent.getMyFriendshipToHim();
            //Log.i(LOG_TAG, "friendship " + iMyFriendshipToHim + " raw " + oIdent.m_u8FriendMatch );
            //Log.i(LOG_TAG, "getView online status " + oIdent.isOnline() + " online flags " + oIdent.m_u8OnlineStatusFlags + " " + oIdent.getOnlineName() ); 
            
         	if( oIdent.isNearby() )
        	{
                //Log.d(LOG_TAG, oIdent.getOnlineName() + " is nearby " ); 
                friendView.setBackgroundResource( R.color.nearby_bkg_color );
                //menuButton.setBackgroundResource(R.drawable.button_menu_normal);
        	}
        	else if( oIdent.isOnline() )
        	{
                //Log.d(LOG_TAG, oIdent.getOnlineName() + " is online " ); 
               friendView.setBackgroundResource( R.color.online_bkg_color );
               //menuButton.setBackgroundResource(R.drawable.button_menu_normal);
            }
        	else
        	{
                //Log.d(LOG_TAG, oIdent.getOnlineName() + " is offline " );
                friendView.setBackgroundResource( R.color.offline_bkg_color );
                //menuButton.setBackgroundResource(R.drawable.button_menu_disabled);
            }
  
            if( null != topText ) 
            {
            	topText.setText(oIdent.getOnlineName() + " - " + oIdent.describeMyFriendshipToHim() );                            
            }
            
            if( null != bottomText ) 
            {
            	bottomText.setText( "Mood: " + oIdent.getOnlineDescription() );
            }

            if( null != truthStatsText ) 
            {
            	String todText = oIdent.getTruthsAndDaresDescription();
            	truthStatsText.setText( todText );
            }
       
            int iIconResource = Constants.getFriendIconResource(iMyFriendshipToHim);
 
    		ImageView view_icon = (ImageView)friendView.findViewById(R.id.friend_icon);
       	    //Log.i(LOG_TAG, "icon " + view_icon.toString() );
    		view_icon.setImageResource(iIconResource);
           	
         	if( oIdent.getHasTextOffers() )
         	{
         		view_icon.setBackgroundResource( R.drawable.background_red );
         	}
         	else
         	{
         		view_icon.setBackgroundResource( R.drawable.background_white );
         	}

        }
        else
        {
            Log.e(LOG_TAG, "getView null ident at position " + position );      	
        }
        
        unlockContactsAdapter();;
        return friendView;
    }
    
	//========================================================================   
    public VxNetIdent getFriendByPosition( int iPosition )
    {
    	lockContactsAdapter();
    	if( iPosition < items.size() )
    	{    
    		VxNetIdent oFriend = items.get( iPosition );
            m_oMutex.release();		
    		return oFriend;
    	}
    	
    	unlockContactsAdapter();
   	    Log.i(LOG_TAG, "unable to get friend at " + iPosition );
		return null;
    }
    
	//========================================================================        
	public void doGuiSetIdentHasTextOffers( VxNetIdent oIdentIn, boolean hasTextOffer )  
    {
		lockContactsAdapter();
		boolean needRefresh = false;
   	    //Log.i(LOG_TAG, "setIdentHasTextOffers " );  
    	
    	for( VxNetIdent oIdent:  items )
    	{
    		if( ( oIdent.m_u64IdLoPart == oIdentIn.m_u64IdLoPart ) &&
    			( oIdent.m_u64IdHiPart == oIdentIn.m_u64IdHiPart ) )
    		{
    			oIdent.setHasTextOffers( hasTextOffer );
    			needRefresh = true;
    			break;
    		}
     	}
    	
        unlockContactsAdapter();
        if( needRefresh )
    	{
        	this.notifyDataSetChanged();
     	}
    	
    	//Log.i(LOG_TAG, "friend list count " + items.size() );  	
     }

	//========================================================================        
	public void setAllToNoTextSessionOffers()
	{
		lockContactsAdapter();
		boolean needRefresh = false;
   	    //Log.i(LOG_TAG, "setIdentHasTextOffers " );     	
    	for( VxNetIdent netIdent:  items )
    	{
    		if( netIdent.getHasTextOffers() )
    		{
    			netIdent.setHasTextOffers( false );
    			needRefresh = true;
     		}
     	}
    	
        unlockContactsAdapter();
        if( needRefresh )
    	{
        	this.notifyDataSetChanged();
     	}		
	}
  
	//========================================================================        
	public void doUpdateFriend( VxNetIdent oIdentIn, boolean sessionTimeChange )  
    {
		lockContactsAdapter();
   	    //Log.i(LOG_TAG, "doUpdateFriend " );  
    	
   	    int listIdx = 0;
    	for( VxNetIdent oIdent:  items )
    	{
    		if( ( oIdent.m_u64IdLoPart == oIdentIn.m_u64IdLoPart )
    			&& ( oIdent.m_u64IdHiPart == oIdentIn.m_u64IdHiPart ) )
    		{
     				// remove existing then will get inserted in correct session time order
    			items.remove(  listIdx ); 	   	    			
    			break;  			
    		}
    		
    		listIdx++; 
    	}
    	
   	    // insert item according to last time started session
   	    long hisSessionTime = oIdentIn.m_s64LastSessionTime;
   	    Log.i(LOG_TAG, "adding friend online status " + oIdentIn.m_u8OnlineStatusFlags + " " + oIdentIn.getOnlineName() + " session time " + hisSessionTime );
   	    if( 0 == items.size() )
   	    {
   	   		items.add(oIdentIn);	   	    	
   	    }
   	    else
   	    {
   	    	boolean wasInserted = false;
   	    	listIdx = 0;
   	    	for( VxNetIdent oIdentInList:  items )
   	    	{
   	    		if( oIdentInList.m_s64LastSessionTime < hisSessionTime )
   	    		{
   	       	   	    items.add( listIdx, oIdentIn ); 
   	       	   	    wasInserted = true;	
   	    			break;  			
   	    		}
   	    		
   	    		listIdx++; 
   	    	}
   	    	
   	    	if( false == wasInserted )
   	    	{   		
	   	   		items.add(oIdentIn);	   	    	
   	    	}
   	    }	    

    	
    	//Log.i(LOG_TAG, "friend list count " + items.size() );
    	
        //VxNetIdent friend = items.get( iPosition );
        //Log.i(LOG_TAG, "resulting friend online status " + friend.m_u8OnlineStatusFlags + " " + friend.getOnlineName() );
    	//Collections.sort( items );
        unlockContactsAdapter();
    }

	//========================================================================        
	public void doGuiAssetViewingMessage( int eAssetActionMsg, VxGUID onlineId, int assetParam )
	{
		m_IsCurrentlyViewing = ( 0 == assetParam ) ? false : true;
		if( m_IsCurrentlyViewing )
		{
			m_ViewingOnlineId.m_u64IdHiPart = onlineId.m_u64IdHiPart;
			m_ViewingOnlineId.m_u64IdLoPart = onlineId.m_u64IdLoPart;
			setFriendHasUnviewedTextMessages( m_ViewingOnlineId, false );
		}	
	}

	//========================================================================        
	public void doGuiNewAssetMessage( int eAssetActionMsg, VxGUID onlineId, int assetParam )
	{
		if( m_IsCurrentlyViewing 
			&& ( onlineId.m_u64IdHiPart == m_ViewingOnlineId.m_u64IdHiPart )
			&& ( onlineId.m_u64IdLoPart == m_ViewingOnlineId.m_u64IdLoPart ) )
		{
			// user is viewing messages from this contact
			setFriendHasUnviewedTextMessages( onlineId, false );
			return;
		}

		setFriendHasUnviewedTextMessages( onlineId, true );		
	}
	
	//========================================================================        
	public void setFriendHasUnviewedTextMessages( VxGUID onlineId, boolean hasTextMsgs )
	{
		boolean needRefresh = false;
		lockContactsAdapter();
  	    Log.i(LOG_TAG, "setFriendHasUnviewedTextMessages " + hasTextMsgs );  

    	for( VxNetIdent oIdent:  items )
    	{
    		if( ( oIdent.m_u64IdLoPart == onlineId.m_u64IdLoPart )
    			&& ( oIdent.m_u64IdHiPart == onlineId.m_u64IdHiPart ) )
    		{
    			if( hasTextMsgs != oIdent.getHasTextOffers() )
    			{
    				oIdent.setHasTextOffers( hasTextMsgs );
    				needRefresh = true;
     			}

    			break;  			
    		}
    	}
    	
        unlockContactsAdapter();
        
    	if( needRefresh )
    	{
    		notifyDataSetChanged();
    	}		
	}
}
