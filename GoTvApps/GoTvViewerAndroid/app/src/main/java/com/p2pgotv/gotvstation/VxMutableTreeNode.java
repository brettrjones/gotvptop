package com.p2pgotv.gotvstation;

public interface VxMutableTreeNode extends VxTreeNode 
{
    void insert(VxMutableTreeNode child, int index);
    void remove(int index);
    void remove(VxMutableTreeNode node);
    void setUserObject(Object object);
    <T> T getUserObject();
    void removeFromParent();
    void setParent(VxMutableTreeNode parent);
}