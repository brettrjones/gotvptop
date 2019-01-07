package com.p2pgotv.gotvstation;

public interface VxTreeListener 
{
    void onTreeNodesChanged(VxTreeEvent e);
    void onTreeNodesInserted(VxTreeEvent e);
    void onTreeNodesRemoved(VxTreeEvent e);
    void onTreeStructureChanged(VxTreeEvent e);
}
