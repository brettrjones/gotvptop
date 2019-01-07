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

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.Button;

public class ButtonPro extends Button 
{
	public final static int 	eButtonIconNormal				= 1;
	public final static int 	eButtonIconDisabled				= 2;
	public final static int 	eButtonIconCancel				= 3;
	public final static int 	eButtonIconRed					= 4;
	public final static int 	eButtonIconYellow				= 5;
	
	int 						m_ImageResIdNormal				= 0;
	int 						m_ImageResIdDisabled			= 0;
	int 						m_ImageResIdCancel				= 0;
	int 						m_ImageResIdRed					= 0;
	int							m_ImageResIdYellow				= 0;
	boolean						m_HasExtendedIcons				= false;
	boolean						m_BlinkIsEnabled				= false;
	int 						m_BlinkState = 0;

	//========================================================================
	public ButtonPro( Context context ) 
	{
		super( context );
	}
	
	//========================================================================
	public ButtonPro( Context context, AttributeSet attrs ) 
	{
		super( context, attrs );
	}

	//========================================================================
	public ButtonPro( Context context, AttributeSet attrs, int defStyle ) 
	{
		super( context, attrs, defStyle );
	}
	//========================================================================
	@Override
	public void setEnabled( boolean enable ) 
	{
		super.setEnabled( enable );
		if( enable && ( 0 != m_ImageResIdNormal ) )
		{
			setIcon( eButtonIconNormal );
		}
		else if( !enable && ( 0 != m_ImageResIdNormal ) )
		{
			setIcon( eButtonIconDisabled );
		}
	}
	
	//========================================================================
	public void enableBlink( boolean enable )
	{
		if( m_BlinkIsEnabled != enable )
		{
			if( enable )
			{
				if( this.isEnabled() 
					&& ( 0 != m_ImageResIdRed ) )
				{
					m_BlinkState = 0;
					setIcon( eButtonIconRed );
					m_BlinkIsEnabled = true;
				}
			}
			else
			{
				m_BlinkIsEnabled = false;
				if( isEnabled() )
				{
					setIcon( eButtonIconNormal );
				}
				else
				{
					setIcon( eButtonIconDisabled );
				}
			}	
		}
	}
	
	//========================================================================
	public void onOncePerBlink()
	{
		if( m_BlinkIsEnabled )
		{
			m_BlinkState = ( 0 == m_BlinkState ) ? 1 : 0;
			if( 0 == m_BlinkState )
			{
				setIcon( eButtonIconRed );
			}
			else
			{
				setIcon( eButtonIconYellow );
			}	
		}
	}

	//========================================================================
	public void setIcon( int eButtonIconType )
	{
		int resId = 0;
		switch( eButtonIconType )
		{
		case eButtonIconNormal:
			resId = m_ImageResIdNormal;
			break;
			
		case eButtonIconDisabled:
			resId = m_ImageResIdDisabled;
			break;
			
		case eButtonIconCancel:
			resId = m_ImageResIdCancel;
			break;
			
		case eButtonIconRed:
			resId = m_ImageResIdRed;
			break;
			
		case eButtonIconYellow:
			resId = m_ImageResIdYellow;
			break;
			
		default:
			break;
		}
		
		if( 0 != resId )
		{
			setButtonImage( resId );
		}
	}
	
	//========================================================================
	public void setIconResources(	int buttonImageResIdNormal,
									int buttonImageResIdDisabled, 
									int buttonImageResIdCancel )
	{
		m_ImageResIdNormal				= buttonImageResIdNormal;
		m_ImageResIdDisabled			= buttonImageResIdDisabled;
		m_ImageResIdCancel				= buttonImageResIdCancel;
		if( isEnabled() )
		{
			setButtonImage( m_ImageResIdNormal );
		}
		else
		{
			setButtonImage( m_ImageResIdDisabled );
		}		
	}

	//========================================================================
	public void setIconResources(	int buttonImageResIdNormal,
									int buttonImageResIdDisabled, 
									int buttonImageResIdCancel,
									int buttonImageResIdRed, 
									int buttonImageResIdYellow ) 
	{
		m_ImageResIdNormal				= buttonImageResIdNormal;
		m_ImageResIdDisabled			= buttonImageResIdDisabled;
		m_ImageResIdCancel				= buttonImageResIdCancel;
		m_ImageResIdRed					= buttonImageResIdRed;
		m_ImageResIdYellow				= buttonImageResIdYellow;
		m_HasExtendedIcons = true;
		if( isEnabled() )
		{
			setButtonImage( m_ImageResIdNormal );
		}
		else
		{
			setButtonImage( m_ImageResIdDisabled );
		}	
	}
	
	//============================================================================
	void setVisible( boolean visible )
	{
		if( visible ) 
			setVisibility( View.VISIBLE );	 
		else
			setVisibility( View.GONE );				
	}

	//========================================================================
	public void setButtonImage( int buttonImageResourceId )
	{
		setBackgroundResource( buttonImageResourceId );
	}

}
