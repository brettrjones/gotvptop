package com.p2pgotv.gotvstation;

import com.p2pgotv.gotvstation.VxMultiGestureDetector.DragEvent;
import com.p2pgotv.gotvstation.VxMultiGestureDetector.FlickEvent;
import com.p2pgotv.gotvstation.VxMultiGestureDetector.PinchEvent;
import com.p2pgotv.gotvstation.VxMultiGestureDetector.RotateEvent;
import com.p2pgotv.gotvstation.VxMultiGestureDetector.TapEvent;

public interface VxOnMultiGestureInterface 
{
	void onDrag(DragEvent event);
	void onRotate(RotateEvent event);
	void onPinch(PinchEvent event);
	void onTap(TapEvent event);
	void onDoubleTap(TapEvent event);
	void onFlick(FlickEvent event);
}
