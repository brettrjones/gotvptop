package com.p2pgotv.gotvstation;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class ActivityConfirmShredFile extends ActivityBase
{
	//=== constants ===//
	//private static final String LOG_TAG = "ActivityConfirmShredFile:";
	   
	//=== vars ===//
	private Button 					m_AcceptBut 				= null;
	private Button  				m_CancelBut 				= null;
	private TextView  				m_AcceptText 				= null;
	private VxFileInfo  			m_FileInfo 					= null;
	private ReuseFileDisplayLogic  	m_FileDisplayLogic 			= new ReuseFileDisplayLogic();
	
    //========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.activity_confirm_shred_file);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_confirm_shred_file_title );
        m_FileInfo = m_MyApp.getCurrentFileInfo();
        if( null != m_FileInfo )
        {
        	m_FileDisplayLogic.fillFileDisplayGui( this, m_FileInfo );
        }
 	 	
		this.m_AcceptBut = (Button)this.findViewById(R.id.reuse_accept_but);
		if( null != m_AcceptBut )
		{
			m_AcceptBut.setBackgroundResource( R.drawable.button_shredder_normal );
		 	this.m_AcceptBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
	 			    m_MyApp.playButtonClick();
		 			onAcceptButClick();
		 		}
		 	});			
		}
	 	
		this.m_CancelBut = (Button)this.findViewById(R.id.reuse_cancel_but);
		if( null != m_CancelBut )
		{
		 	this.m_CancelBut.setOnClickListener(new OnClickListener() 
		 	{
		 		public void onClick(View v) 
		 		{
	 			    m_MyApp.playButtonClick();
		 			onCancelButClick();
		 		}
		 	});	
		}
	 	
	    this.m_AcceptText		= (TextView)this.findViewById( R.id.reuse_accept_text_view );
	    if( null != m_AcceptText )
	    {
	    	m_AcceptText.setText(R.string.shred_file);
	    }    
    }
	
	//========================================================================
	public void onAcceptButClick() 
	{
		Intent resultIntent = getIntent();
		setResult(Activity.RESULT_OK, resultIntent);
		finish();
	}

	//========================================================================
	public void onCancelButClick() 
	{
		onBackButtonPressed();
	}
}
