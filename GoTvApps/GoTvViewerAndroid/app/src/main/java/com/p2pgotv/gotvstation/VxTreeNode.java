package com.p2pgotv.gotvstation;

import android.view.*;


public interface VxTreeNode 
{
    <T extends VxTreeNode> T getChildAt(int childIndex);
    int getChildCount();
    <T extends VxTreeNode> T getParent();
    int getIndex(VxTreeNode node);
    boolean isLeaf();
    
    // yuku's additions
    int getDepth();
    int getLevel();
    
    // for converting to list
    int getRowCount();
    boolean getExpanded();
    void setExpanded(boolean expanded);
    View getView(int position, View convertView, ViewGroup parent, int level, VxTreeNodeIconType iconType, int[] lines);
}
