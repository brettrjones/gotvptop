

package com.p2pgotv.gotvstation;

import android.os.Parcel;
import android.text.ParcelableSpan;
import android.text.TextPaint;
import android.text.style.CharacterStyle;
import android.text.style.UpdateAppearance;

public class VxRichTextEditUnderlineSpan extends CharacterStyle implements UpdateAppearance, ParcelableSpan 
{
    public VxRichTextEditUnderlineSpan() 
    {
    }

    public VxRichTextEditUnderlineSpan(Parcel src)
    {
    }

    public int getSpanTypeId() 
    {
        return 6;
    }

    public int describeContents() 
    {
        return 0;
    }

    public void writeToParcel(Parcel dest, int flags) 
    {
    }

    @Override
    public void updateDrawState(TextPaint ds) 
    {
        ds.setUnderlineText(true);
    }
}
