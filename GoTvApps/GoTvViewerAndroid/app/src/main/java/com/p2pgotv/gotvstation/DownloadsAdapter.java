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
import android.widget.Button;
import android.widget.TextView;

class DownloadsAdapter extends ArrayAdapter<GuiOfferSession> 
{	
	//=== constants ===//
	private static final String LOG_TAG = "DownloadsAdapter:";  

	//=== vars ===//
	VxNetIdent							m_HisIdentToUpdate;
	private ArrayList<GuiOfferSession> 	items;

	private Semaphore 					m_oMutex 	= new Semaphore(1); 
	private MyApp						m_MyApp		= null;

	//=== methods ===//
	public DownloadsAdapter(MyApp context, int textViewResourceId, ArrayList<GuiOfferSession> items) 
    {
		super(context, textViewResourceId, items);
		m_MyApp = context;
		
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
	public void lockOffersList()
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
	public void unlockOffersList()
	{
		 m_oMutex.release();
	}
	
	//======================================================================== 
	public void clearList()
	{
		lockOffersList();
		this.items.clear();
		unlockOffersList();	
	}
	
	//======================================================================== 
    @Override
    public View getView(int position, View convertView, ViewGroup parent) 
    {
    	lockOffersList();
		
		Log.i(LOG_TAG, "getView position " + position );
    	View friendView = convertView;
        if( null == friendView ) 
        {
        	LayoutInflater vi = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        	friendView = vi.inflate(R.layout.offer_item, null);
        }
        
        GuiOfferSession offerSession = items.get(position);
        if( null != offerSession ) 
        {
        	VxNetIdent oIdent = offerSession.getHisIdent();
            TextView topText = (TextView) friendView.findViewById(R.id.toptext);
            TextView bottomText = (TextView) friendView.findViewById(R.id.bottomtext);
            int iMyFriendshipToHim = oIdent.getMyFriendshipToHim();
            //Log.i(LOG_TAG, "friendship " + iMyFriendshipToHim + " raw " + oIdent.m_u8FriendMatch );
            Log.i(LOG_TAG, "getView online status " + oIdent.isOnline() + " online flags " + oIdent.m_u8OnlineStatusFlags + " " + oIdent.getOnlineName() ); 
            
            int iTextColor = 0xFF000000;
        	if( oIdent.isNearby() )
        	{
                Log.d(LOG_TAG, oIdent.getOnlineName() + " is nearby " ); 
                friendView.setBackgroundResource( R.color.nearby_bkg_color );
        	}
        	else if( oIdent.isOnline() )
        	{
                Log.d(LOG_TAG, oIdent.getOnlineName() + " is online " ); 
                friendView.setBackgroundResource( R.color.online_bkg_color );
        	}
        	else
        	{
                Log.d(LOG_TAG, oIdent.getOnlineName() + " is offline " );
                friendView.setBackgroundResource( R.color.offline_bkg_color );
        	}

            if( null != topText ) 
            {
            	topText.setTextColor( iTextColor );
            	topText.setText(oIdent.getOnlineName() + " - " + Constants.describeFriendState( iMyFriendshipToHim ) );                            
            }
            
            if( null != bottomText ) 
            {
            	bottomText.setTextColor(iTextColor);
            	String offerMsg = offerSession.getOfferMsg();
            	if( 0 != offerMsg.length() )
            	{
            		bottomText.setText( offerMsg );
            	}
            }
            
            TextView missedCallLabel = (TextView) friendView.findViewById(R.id.missed_call_label);
            TextView missedCallCount = (TextView) friendView.findViewById(R.id.missed_call_count);
            if( null != missedCallLabel && null != missedCallCount ) 
            {
            	if( 0 != offerSession.m_MissedCallCount )
            	{
                	missedCallLabel.setTextColor(iTextColor);
                	missedCallCount.setTextColor(iTextColor);
                	missedCallLabel.setVisibility( View.VISIBLE );
            		missedCallCount.setVisibility( View.VISIBLE );
            		String missedCnt = String.valueOf( offerSession.m_MissedCallCount );
            		missedCallCount.setText( missedCnt );             	            		
            	}
            	else
            	{
            		missedCallLabel.setVisibility( View.GONE );
            		missedCallCount.setVisibility( View.GONE );           		
            	}
            }  
            
             
            int iIconResource = MyIcons.getPluginIcon(offerSession.m_ePluginType, Constants.ePluginAccessOk); 
            Button offerIcon = (Button)friendView.findViewById(R.id.offer_icon);
        	offerIcon.setBackgroundResource(iIconResource);
    		
       		Button acceptButton = (Button)friendView.findViewById(R.id.offer_accept_button);
       		if( ( false == oIdent.isOnline() ) 
       			|| offerSession.getIsSessionEnded() )
       		{
       			acceptButton.setBackgroundResource(R.drawable.button_accept_disabled);
       			acceptButton.setEnabled( false );			
       		}
       		else
       		{
       			acceptButton.setBackgroundResource(R.drawable.button_accept_normal);
      			acceptButton.setEnabled( true );
       		}
       		
       		Button rejectButton = (Button)friendView.findViewById(R.id.offer_reject_button);
       		rejectButton.setBackgroundResource(R.drawable.button_cancel_normal);
         }
        else
        {
            Log.e(LOG_TAG, "getView null offer at position " + position );      	
        }
        
        unlockOffersList();	
        return friendView;
    }
    
	//========================================================================   
    public GuiOfferSession getOfferByPosition( int iPosition )
    {
    	if( iPosition < items.size() )
    	{   
    		GuiOfferSession offerSession = items.get( iPosition );
    		return offerSession;
    	}
    	
   	    Log.i(LOG_TAG, "unable to get offer at " + iPosition );
		return null;
    }  
    
	//========================================================================   
    public GuiOfferSession findAvailableAndActiveOffer( int ePluginType, VxNetIdent netIdent )
    {
 	   	for( GuiOfferSession oSession:  items )
    	{
    		VxNetIdent oIdent = oSession.getHisIdent();
    		if( ( oIdent.m_u64IdLoPart == netIdent.m_u64IdLoPart ) &&
    			( oIdent.m_u64IdHiPart == netIdent.m_u64IdHiPart ) &&
    			( oSession.m_ePluginType == ePluginType ) )
    		{
    			return oSession;
     		}   		
    	}
    	
		return null;
    }
    
	//========================================================================        
	public int getOfferCount()  
    {
		return items.size();
    }
	
	//========================================================================        
	public void doUpdateOffer( GuiOfferSession offerSession )  
    {
		lockOffersList();
		
		boolean bFoundSession = false;
   	    Log.i(LOG_TAG, "DoUpdateOffer " );  
    	
   	    int iPosition = 0;
    	for( GuiOfferSession oSession:  items )
    	{
    		VxNetIdent oIdent = oSession.getHisIdent();
    		if( ( oIdent.m_u64IdLoPart == offerSession.getHisIdent().m_u64IdLoPart ) &&
    			( oIdent.m_u64IdHiPart == offerSession.getHisIdent().m_u64IdHiPart ) &&
    			( oSession.m_ePluginType == offerSession.m_ePluginType ) )
    		{
    			bFoundSession = true;
       	   	    Log.i(LOG_TAG, "found friend with online status " + oIdent.m_u8OnlineStatusFlags  + " " + oIdent.getOnlineName() );  
       	   	    offerSession.setMissedCallCount( oSession.getMissedCallCount() );
       	   	    items.set(iPosition, offerSession ); 
       	   	    Log.i(LOG_TAG, "found friend updating with online status " + offerSession.getHisIdent().m_u8OnlineStatusFlags  + " " + offerSession.getHisIdent().getOnlineName() );    						
    			break;  			
    		}
    		
    		iPosition++; 
    	}
 
    	if( false == bFoundSession )
    	{
	   	    Log.i(LOG_TAG, "adding offer from " + offerSession.getHisIdent().getOnlineName() );  
	   	    offerSession.m_bRmtInitiated = true;
    		items.add(offerSession);
    		m_MyApp.playSoundFromThread( ESndDef.eSndDefNotify1 );
    	}
    	
    	Log.i(LOG_TAG, "offer list count " + items.size() );
    	
        m_oMutex.release();  
    }

	//========================================================================
	public void removeAtPosition(int position) 
	{
		if( ( 0 <= position )
			&& ( items.size() > position ) )
		{
			items.remove( position );
		}		
	}
	
	//========================================================================
	//! add offer to notify list
	public void	toGuiRxedPluginOffer( GuiOfferSession offerSession )
	{
		Log.i( LOG_TAG, "toGuiRxedPluginOffer" );
		doUpdateOffer( offerSession );
	}

	//========================================================================
	public void	toGuiPluginSessionEnded( GuiOfferSession offerSession )
	{
		Log.i( LOG_TAG, "toGuiPluginSessionEnded" );
		lockOffersList();
		
    	for( GuiOfferSession itemSession:  items )
    	{
    		VxNetIdent oIdent = itemSession.getHisIdent();
    		if( ( oIdent.m_u64IdLoPart == offerSession.getHisIdent().m_u64IdLoPart ) &&
    			( oIdent.m_u64IdHiPart == offerSession.getHisIdent().m_u64IdHiPart ) &&
    			( itemSession.m_ePluginType == offerSession.m_ePluginType ) )
    		{
    			itemSession.incMissedCallCount();
    			itemSession.setIsSessionEnded( true );
    			break;  			
    		}
    	}
 
    	unlockOffersList();	
	}

	//============================================================================
	public void toGuiContactOffline( VxNetIdent friendIdent )
	{
		Log.i( LOG_TAG, "toGuiPluginSessionEnded" );
		lockOffersList();
		
    	for( GuiOfferSession itemSession:  items )
    	{
    		VxNetIdent itemIdent = itemSession.getHisIdent();
    		if( ( itemIdent.m_u64IdLoPart == friendIdent.m_u64IdLoPart ) &&
    			( itemIdent.m_u64IdHiPart == friendIdent.m_u64IdHiPart ) ) 
    		{
    			itemSession.incMissedCallCount();
    			itemSession.setIsSessionEnded( true );
    			itemIdent.setIsOnline( false );			
    		}
    	}
 
    	unlockOffersList();	
	}

	//============================================================================
	public void toGuiRxedOfferReply(GuiOfferSession offerReply) 
	{
		Log.i( LOG_TAG, "toGuiPluginSessionEnded" );
		lockOffersList();
		
		VxNetIdent friendIdent = offerReply.getHisIdent();
		for( GuiOfferSession itemSession:  items )
    	{
    		VxNetIdent itemIdent = itemSession.getHisIdent();
    		if( ( itemIdent.m_u64IdLoPart == friendIdent.m_u64IdLoPart ) &&
    			( itemIdent.m_u64IdHiPart == friendIdent.m_u64IdHiPart ) &&
    			( itemSession.m_ePluginType == offerReply.m_ePluginType ) ) 
    		{
    			if( ( Constants.eOfferResponseEndSession == offerReply.getOfferResponse() )
    				|| ( Constants.eOfferResponseCancelSession == offerReply.getOfferResponse() ) )
    			{
    				itemSession.incMissedCallCount();
    				itemSession.setIsSessionEnded( true );
    			}
     		}
    	}
 
		unlockOffersList();	
	} 
}
