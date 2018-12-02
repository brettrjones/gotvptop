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

import android.app.Activity;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;
import android.widget.TextView;

public class ReuseFriendDisplayLogic 
{
	Activity					m_Activity 				= null;
	VxNetIdent 					m_HisIdent				= null;
	ImageView					m_HisIdentIcon			= null;
 	TextView					m_HisIdentName			= null;
 	TextView					m_HisIdentMoodMsg		= null;
 	TextView					m_HisIdentTruths		= null;
	
	public void fillFriendDisplayGui( Activity activity, VxNetIdent curFriend )
	{
		m_Activity = activity;
		m_HisIdent = curFriend;
		if( ( null != m_Activity ) && ( null != m_HisIdent ) )
		{
			m_HisIdentIcon = (ImageView)m_Activity.findViewById( R.id.friend_icon );
	        if( null != m_HisIdentIcon )
	        {
	        	m_HisIdentIcon.setOnTouchListener(new OnTouchListener() 
	        	{ 
	        		//@Override
	        	    public boolean onTouch(View v, MotionEvent event) 
	        		{ 
	     	    	   switch (event.getAction()) 
	     	    	   {
	     	    	    case MotionEvent.ACTION_DOWN:
	     	    	        //some code....
	     	    	        break;
	     	    	    case MotionEvent.ACTION_UP:
	     	    	        v.performClick();
	     	    	       onFriendClick();
	     	    	        break;
	     	    	    default:
	     	    	        break;
	     	    	    }
	     	    	   
	     	    	    return true;
	        	    } 
	        	}); 
	        }
	        
	        m_HisIdentName = (TextView)m_Activity.findViewById( R.id.friend_name );
	        if( null != m_HisIdentName )
	        {
	        	m_HisIdentName.setOnTouchListener(new OnTouchListener() 
	        	{ 
	        		//@Override
	        	    public boolean onTouch(View v, MotionEvent event) 
	        		{ 
	      	    	   switch (event.getAction()) 
	      	    	   {
	      	    	    case MotionEvent.ACTION_DOWN:
	      	    	        //some code....
	      	    	        break;
	      	    	    case MotionEvent.ACTION_UP:
	      	    	        v.performClick();
	      	    	        onFriendClick();
	      	    	        break;
	      	    	    default:
	      	    	        break;
	      	    	    }
	      	    	   
	      	    	    return true;
	        		} 
	        	}); 
	        }
	        
	        m_HisIdentMoodMsg = (TextView)m_Activity.findViewById( R.id.friend_mood_msg );
	        if( null != m_HisIdentMoodMsg )
	        {
	        	m_HisIdentMoodMsg.setOnTouchListener(new OnTouchListener() 
	        	{ 
	        		//@Override
	        	    public boolean onTouch(View v, MotionEvent event) 
	        		{ 
	      	    	   switch (event.getAction()) 
	      	    	   {
	      	    	    case MotionEvent.ACTION_DOWN:
	      	    	        //some code....
	      	    	        break;
	      	    	    case MotionEvent.ACTION_UP:
	      	    	        v.performClick();
	      	    	       onFriendClick();
	      	    	        break;
	      	    	    default:
	      	    	        break;
	      	    	    }
	      	    	   
	      	    	    return true;
	        	    } 
	        	}); 
	        }
	        
	        m_HisIdentTruths = (TextView)m_Activity.findViewById( R.id.friend_truths );
	        if( null != m_HisIdentTruths )
	        {
	        	m_HisIdentTruths.setOnTouchListener(new OnTouchListener() 
	        	{ 
	        		//@Override
	        	    public boolean onTouch(View v, MotionEvent event) 
	        		{ 
	      	    	   switch (event.getAction()) 
	      	    	   {
	      	    	    case MotionEvent.ACTION_DOWN:
	      	    	        //some code....
	      	    	        break;
	      	    	    case MotionEvent.ACTION_UP:
	      	    	        v.performClick();
	      	    	       onFriendClick();
	      	    	        break;
	      	    	    default:
	      	    	        break;
	      	    	    }
	      	    	   
	      	    	    return true;
	        	    } 
	        	}); 
	        }
	       
	        fillFriend();
		}
	}

	//========================================================================
	private void  onFriendClick()
	{
	}
			
	//========================================================================
	private void  fillFriend()
	{
		if( null != m_HisIdent )
		{
			int iFriendshipType = m_HisIdent.getMyFriendshipToHim();
			if( null != m_HisIdentIcon )
			{
				m_HisIdentIcon.setImageResource( Constants.getFriendIconResource( iFriendshipType ));  
			}
			
			String strFriendship = m_HisIdent.describeHisFriendshipToMe();
			if( null != m_HisIdentName )
			{
				m_HisIdentName.setText( m_HisIdent.m_as8OnlineName + " - " + strFriendship ); 
			}
			
			if( null != m_HisIdentMoodMsg )
			{
				m_HisIdentMoodMsg.setText( m_HisIdent.getOnlineDescription() );	
			}
			
			if( null != m_HisIdentTruths )
			{
				m_HisIdentTruths.setText( m_HisIdent.getTruthsAndDaresDescription() );	
			}		
		}
	}	
}

