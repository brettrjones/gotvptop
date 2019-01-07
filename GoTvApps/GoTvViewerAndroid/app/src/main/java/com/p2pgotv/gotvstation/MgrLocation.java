package com.p2pgotv.gotvstation;

import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;


public class MgrLocation implements LocationListener
{
	 //==== const ===//
	//private static final String LOG_TAG = "TodLocationMgr: ";
	
	//=== context ===//
	private MyP2PWeb 			m_oActivity;
	//private MyApp 					m_MyApp;
	private LocationManager 		m_oLocationMgr;
	private Location 				m_oMyLocation;
	
	//=== vars ===//
	
	//=== constructor ===//
    public MgrLocation(MyApp oApp) 
    {
    	//Log.i(LOG_TAG, "MgrLocation: constructed");
    	//m_MyApp = oApp;
    }
    
    //=== Startup ===//  
    public void Startup(MyP2PWeb oActivity) 
    {
    	//Log.i(LOG_TAG, "MgrLocation: Startup")
    	m_oActivity = oActivity;
    	m_oLocationMgr = (LocationManager) m_oActivity.getSystemService(Context.LOCATION_SERVICE);            
    	m_oLocationMgr.requestLocationUpdates(LocationManager.NETWORK_PROVIDER,1,1,this);            
    	m_oLocationMgr.requestLocationUpdates(LocationManager.GPS_PROVIDER,1,1,this);
    	m_oMyLocation = internalGetCurrentLocation();
    }
    public Location getCurrentLocation()
    {
    	return m_oMyLocation;
    }
	private Location internalGetCurrentLocation() 
	{		
		Location currLoc = null;		
		currLoc = m_oLocationMgr.getLastKnownLocation(LocationManager.GPS_PROVIDER);		
		if (currLoc == null) 
		{			
			currLoc = m_oLocationMgr.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);		
		}		
		return currLoc;	
	}

	//@Override
	public void onLocationChanged(Location arg0) 
	{
		m_oMyLocation = arg0;	
	}

	//@Override
	public void onProviderDisabled(String arg0) 
	{
	}

	//@Override
	public void onProviderEnabled(String provider) 
	{
	}

	//@Override
	public void onStatusChanged(String provider, int status, Bundle extras) 
	{
	}

}
