package com.p2pgotv.gotvstation;

import android.os.*;

public class VxFolderChooserResult implements Parcelable 
{
	public static final String TAG = VxFolderChooserResult.class.getSimpleName();

	public String selectedFolder;

	@Override public int describeContents() {
		return 0;
	}

	@Override public void writeToParcel(Parcel dest, int flags) {
		dest.writeString(selectedFolder);
	}

	public static final Parcelable.Creator<VxFolderChooserResult> CREATOR = new Parcelable.Creator<VxFolderChooserResult>() {
		@Override public VxFolderChooserResult[] newArray(int size) {
			return new VxFolderChooserResult[size];
		}

		@Override public VxFolderChooserResult createFromParcel(Parcel in) {
			VxFolderChooserResult res = new VxFolderChooserResult();
			res.selectedFolder = in.readString();
			return res;
		}
	};
}
