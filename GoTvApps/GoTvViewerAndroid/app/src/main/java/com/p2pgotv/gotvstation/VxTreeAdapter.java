package com.p2pgotv.gotvstation;

import android.view.*;
import android.widget.*;

public class VxTreeAdapter extends BaseAdapter 
{
	public static final String TAG = VxTreeAdapter.class.getSimpleName();

	private VxTreeNode root;
	private boolean rootVisible = true;
	private VxTreeListener listener;

	@Override public int getCount() 
	{
		if (root == null) 
		{
			return 0;
		} 
		else 
		{
			return root.getRowCount() - (rootVisible? 0: 1);
		}
	}

	@Override public VxTreeNode getItem(int position) 
	{
		if (rootVisible && position == 0) return root;
		
		return searchItem(root, rootVisible? 0: -1, position);
	}

	private static VxTreeNode searchItem(VxTreeNode cur, int base, int target) 
	{
		if (base == target) return cur;
		
		int pos = base + 1; // first child is always one row after
		
		for (int i = 0, len = cur.getChildCount(); i < len; i++) {
			VxTreeNode child = cur.getChildAt(i);
			int max = pos + child.getRowCount();
			
			// range covered is pos..<max 
			if (target >= pos && target < max) {
				return searchItem(child, pos, target);
			}
			
			pos = max;
		}
		
		throw new RuntimeException("invalid target: " + target);
	}

	@Override public long getItemId(int position) 
	{
		return position;
	}

	@Override public View getView(int position, View convertView, ViewGroup parent) 
	{
		VxTreeNode node = getItem(position);
		return node.getView(position, convertView, parent, node.getLevel(), VxTreeNodeIconType.up, null);
	}

	public void setRoot(VxTreeNode root) 
	{
		this.root = root;
		notifyDataSetChanged();
		
		if (root != null) 
		{
			dispatchNodeStructureChanged(root);
		} 
		else 
		{
			notifyRootChangedToNull(this);
		}
	}

	public boolean getRootVisible() 
	{
		return rootVisible;
	}

	public void setRootVisible(boolean visible) 
	{
		this.rootVisible = visible;
		notifyDataSetChanged();
	}

	public void setTreeListener(final VxTreeListener l) 
	{
		listener = l;
	}

	@SuppressWarnings("unchecked") public <T extends VxTreeNode> T getRoot() 
	{
		return (T) root;
	}

	public int getIndexOfChild(VxTreeNode parent, VxTreeNode child) 
	{
		if (parent == null || child == null) 
		{
			return -1;
		}

		int numChildren = parent.getChildCount();
		for (int i = 0; i < numChildren; i++) 
		{
			if (child.equals(parent.getChildAt(i))) 
			{
				return i;
			}
		}

		return -1;
	}

	public void reload() 
	{
		reload(root);
	}

	public void reload(final VxTreeNode node) 
	{
		dispatchNodeStructureChanged(node);
	}

	public void insertNodeInto(final VxMutableTreeNode newChild, final VxMutableTreeNode parent, final int index) 
	{
		parent.insert(newChild, index);
		dispatchNodesWereInserted(parent, new int[] { index });
	}

	public void removeNodeFromParent(final VxMutableTreeNode node) 
	{
		VxMutableTreeNode parent = node.getParent();
		int index = parent.getIndex(node);
		parent.remove(node);
		dispatchNodesWereRemoved(parent, new int[] { index }, new VxTreeNode[] { node });
	}

	public void dispatchNodeChanged(final VxTreeNode node) 
	{
		if (node == root) 
		{
			dispatchNodesChanged(node, null);
			return;
		}
		
		if (node == null) 
		{
			return;
		}
		
		final VxTreeNode parent = node.getParent();
		if (parent == null) 
		{
			return;
		}
		
		dispatchNodesChanged(parent, new int[] { getIndexOfChild(parent, node) });
	}

	public void dispatchNodesChanged(final VxTreeNode node, final int[] childIndices) 
	{
		if (node == null || node != root || childIndices == null || childIndices.length == 0) 
		{
			return;
		}

		notifyTreeNodesChanged(getPathToRoot(node), childIndices, getNodeChildren(node, childIndices));
	}

	public void dispatchNodesWereInserted(final VxTreeNode node, final int[] childIndices) 
	{
		if( node == null || childIndices == null || childIndices.length == 0 ) 
		{
			return;
		}

		notifyTreeNodesInserted( this, getPathToRoot(node), childIndices, getNodeChildren(node, childIndices) );
	}

	public void dispatchNodesWereRemoved(final VxTreeNode node, final int[] childIndices, final VxTreeNode[] removedChildren) 
	{
		if (node == null || childIndices == null || childIndices.length == 0) 
		{
			return;
		}
		
		notifyTreeNodesRemoved(this, getPathToRoot(node), childIndices, removedChildren);
	}

	public void dispatchNodeStructureChanged(final VxTreeNode node) 
	{
		if (node == null) 
		{
			return;
		}
		
		notifyTreeStructureChanged(this, getPathToRoot(node), null, null);
	}

	public VxTreeNode[] getPathToRoot(final VxTreeNode aNode) 
	{
		if (aNode == null) 
		{
			return new VxTreeNode[0];
		}

		return getPathToRoot(aNode, 0);
	}

	protected VxTreeNode[] getPathToRoot(final VxTreeNode aNode, final int depth) 
	{
		return VxTreeCommons.getPathToAncestor(aNode, root, depth);
	}

	protected void notifyTreeNodesChanged(final VxTreeNode[] path, final int[] childIndices, final VxTreeNode[] children) 
	{
		if (listener == null) return;
		
		VxTreeEvent event = new VxTreeEvent(path, childIndices, children);
		listener.onTreeNodesChanged(event);
	}

	protected void notifyTreeNodesInserted(final Object source, final VxTreeNode[] path, final int[] childIndices, final VxTreeNode[] children) 
	{
		if (listener == null) return;

		VxTreeEvent event = new VxTreeEvent(path, childIndices, children);
		listener.onTreeNodesInserted(event);
	}

	protected void notifyTreeNodesRemoved(final Object source, final VxTreeNode[] path, final int[] childIndices, final VxTreeNode[] children) 
	{
		if( listener == null ) 
			return;

		VxTreeEvent event = new VxTreeEvent(path, childIndices, children);
		listener.onTreeNodesRemoved(event);
	}

	protected void notifyTreeStructureChanged(final Object source, final VxTreeNode[] path, final int[] childIndices, final VxTreeNode[] children) 
	{
		if( listener == null ) 
			return;

		VxTreeEvent event = new VxTreeEvent(path, childIndices, children);
		listener.onTreeStructureChanged(event);
	}

	private void notifyRootChangedToNull(final Object source) 
	{
		VxTreeEvent event = new VxTreeEvent((VxTreePath) null);
		listener.onTreeStructureChanged(event);
	}

	private VxTreeNode[] getNodeChildren(final VxTreeNode node, final int[] childIndices) 
	{
		if (childIndices == null) 
		{
			return null;
		}

		VxTreeNode[] result = new VxTreeNode[childIndices.length];
		for (int i = 0; i < result.length; i++) 
		{
			result[i] = node.getChildAt(childIndices[i]);
		}
		
		return result;
	}
}
