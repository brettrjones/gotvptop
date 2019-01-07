// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )
package com.p2pgotv.gotvstation;

public interface ChatOnOperationListener 
{
	public void 				chatSend(String content);	
	public void 				chatSelectedFace(String content);
	public void 				chatSelectedFuncation(int index);	
}
