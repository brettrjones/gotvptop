package com.p2pgotv.gotvstation;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class ActivitySdCard extends ActivityBase 
{
	//=== activity vars ===//
	public static final String LOG_TAG = "ActivitySdCard:";
	
	//=== vars ===//
 	// buttons
 	Button 			m_oExitBut = null;
 	Button 			m_oTryAgainBut = null;

    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        setContentView(R.layout.sdcard);
        super.onCreate(savedInstanceState);
        setPageTitle( R.string.activity_sdcard_title );
        
	 	this.m_oExitBut = (Button)this.findViewById(R.id.sdcard_exit_button);
	 	this.m_oExitBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			OnExitButClick(v);
	 		}
	 	});
	 	
	 	this.m_oTryAgainBut = (Button)this.findViewById(R.id.sdcard_ok_button);
	 	this.m_oTryAgainBut.setOnClickListener(new OnClickListener() 
	 	{
	 		public void onClick(View v) 
	 		{
  			   	m_MyApp.playButtonClick();
	 			OnTryAgainButClick(v);
	 		}
	 	});
    }
    
    //! Implement the OnClickListener callback    
    public void OnExitButClick(View v) 
    {  
    	finish();
    }
    
    //! Implement the OnClickListener callback    
    public void OnTryAgainButClick(View v) 
    {  
    	ActivitySdCard.this.setResult(RESULT_OK);
		finish();
    }
    
    //! Implement the OnClickListener callback    
    public void OnContinueClick(View v) 
    {  
    	Intent myIntent = new Intent();
    	myIntent.putExtra( "doanyway", true );
    	ActivitySdCard.this.setResult(RESULT_OK, myIntent);
		finish();
    }

}
