package com.p2pgotv.gotvstation;

import android.os.*;

public class VxFileChooserResult implements Parcelable 
{
	public static final String TAG = VxFileChooserResult.class.getSimpleName();

	public String currentDir;
	public String firstFilename;
	
	@Override
	public int describeContents() 
	{
		return 0;
	}

	@Override
	public void writeToParcel(Parcel dest, int flags) 
	{
		dest.writeString(currentDir);
		dest.writeString(firstFilename);
	}
	
	public static final Parcelable.Creator<VxFileChooserResult> CREATOR = new Parcelable.Creator<VxFileChooserResult>() 
	{
		@Override
		public VxFileChooserResult[] newArray(int size) 
		{
			return new VxFileChooserResult[size];
		}
		
		@Override
		public VxFileChooserResult createFromParcel(Parcel in) 
		{
			VxFileChooserResult res = new VxFileChooserResult();
			res.currentDir = in.readString();
			res.firstFilename = in.readString();
			return res;
		}
	};
}
