package com.p2pgotv.gotvstation;

import java.util.List;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class MgrSensor implements SensorEventListener 
{
	 //==== const ===//
	private static final String LOG_TAG = "SensorMgr: ";
	
	//=== context ===//
	private MyP2PWeb 	m_oActivity;
	private MyApp 			m_MyApp;
	
	//=== vars ===//
	private SensorManager sensorManager;
	private List<Sensor> sensors;
//	private Sensor m_oAccelSensor = null;
	private Sensor m_oOrientationSensor = null;
	//private long lastUpdate = -1; 
	//private long currentTime = -1;
	//private float last_x, last_y, last_z;
	//private float current_x, current_y, current_z, currenForce;
	//private static final int FORCE_THRESHOLD = 900;
	//private final int DATA_X = SensorManager.DATA_X;
	//private final int DATA_Y = SensorManager.DATA_Y;
	//private final int DATA_Z = SensorManager.DATA_Z;

//    private static native void nativeAccelEvent(float[] af32Values );
    private static native void nativeOrientationEvent(float f32PosX, float f32PosY, float f32PosZ);

	//========================================================================
    public MgrSensor(MyP2PWeb oActivity) 
	{
		m_oActivity = oActivity;
		m_MyApp = (MyApp) m_oActivity.getApplication();
		this.sensorManager = (SensorManager) m_oActivity.getSystemService(Context.SENSOR_SERVICE);
		//this.subscriber = subscriber;
//		this.sensors = sensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER);
//		if (sensors.size() > 0) 
//		{
//			m_oAccelSensor = sensors.get(0);
//		}
		if( null != sensorManager)
		{
			this.sensors = sensorManager.getSensorList(Sensor.TYPE_ORIENTATION);
			if (sensors.size() > 0) 
			{
				//Log.e(LOG_TAG, "Got Orientation sensor" );
				m_oOrientationSensor = sensors.get(0);
				sensorManager.registerListener(this, m_oOrientationSensor, SensorManager.SENSOR_DELAY_GAME);
			}
		}
	}
	
	//========================================================================
	public void onResume() 
	{
		if (m_oOrientationSensor!=null) 
		{
			//Log.e(LOG_TAG, "onResume Orientation sensor" );
			sensorManager.registerListener(this, m_oOrientationSensor, SensorManager.SENSOR_DELAY_GAME);
		}
//		if (m_oAccelSensor!=null) 
//		{
//			sensorManager.registerListener(this, m_oAccelSensor, SensorManager.SENSOR_DELAY_GAME);
//		}
	}
	
	//========================================================================	
	public void onStop () 
	{
		//Log.e(LOG_TAG, "onStop Orientation sensor" );
		sensorManager.unregisterListener(this);
	}
	
	//========================================================================
	public void onAccuracyChanged(Sensor s, int valu) 
	{
	}
	
	//========================================================================
	public void onSensorChanged(SensorEvent oEvent) 
	{
		if( m_MyApp.getIsAppPaused())
		{
			return;
		}
		
		if(oEvent.values.length < 3 )
		{
			return;
		}
		
		switch(oEvent.sensor.getType())
		{
		case  Sensor.TYPE_ORIENTATION:
			//Log.e(LOG_TAG, "Orientation sensor event" );
			nativeOrientationEvent(oEvent.values[SensorManager.DATA_X],oEvent.values[SensorManager.DATA_Y],oEvent.values[SensorManager.DATA_Z]);
			break;
//		case  Sensor.TYPE_ACCELEROMETER:
//			nativeAccelEvent(oEvent.values);
//			break;
		}
	}
}
