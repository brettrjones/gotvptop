package com.p2pgotv.gotvstation;

import java.util.Calendar;

public class VxTimeUtil 
{
	//============================================================================
	public static long getCurrentTime() 
	{
		return System.currentTimeMillis();
	}

	//============================================================================
	public static String getFileNameCompatibleDate( long timeStamp ) 
	{
		Calendar calendar = Calendar.getInstance();
		calendar.setTimeInMillis( timeStamp );

		int mYear 	= calendar.get(Calendar.YEAR);
		int mMonth 	= calendar.get(Calendar.MONTH);
		int mDay 	= calendar.get(Calendar.DAY_OF_MONTH);
		String timeString = String.format( "%04d_%02d_%02d", 
											mYear, 
											mMonth + 1, 
											mDay );
		return timeString;
	}

	//============================================================================
	public static String getFileNameCompatibleDateAndTime( long timeStamp ) 
	{
		Calendar calendar = Calendar.getInstance();
		calendar.setTimeInMillis( timeStamp );

		int mYear 			= calendar.get(Calendar.YEAR);
		int mMonth 			= calendar.get(Calendar.MONTH);
		int mDay 			= calendar.get(Calendar.DAY_OF_MONTH);
		int hrOfDay 		= calendar.get(Calendar.HOUR);
		int minuteOfDay 	= calendar.get(Calendar.MINUTE);
		String timeString 	= String.format( "%04d_%02d_%02d-%02d-%02d", 
												mYear, 
												mMonth + 1, 
												mDay,
												hrOfDay,
												minuteOfDay );
		return timeString;
	}	

	//============================================================================
	public static String getChatHourMinTimeStamp()
	{
		Calendar calendar = Calendar.getInstance();
		calendar.setTimeInMillis( getCurrentTime() );

		int hrOfDay 		= calendar.get(Calendar.HOUR);
		int minuteOfDay 	= calendar.get(Calendar.MINUTE);
		String timeString = String.format( " %02d:%02d ", 
											hrOfDay, 
											minuteOfDay );
		return timeString;
	}

};
