package com.p2pgotv.gotvstation;

public class VxTreeEvent 
{
	protected VxTreePath path;
	protected int[] childIndices;
	protected VxTreeNode[] children;

	public VxTreeEvent(final VxTreeNode[] path) 
	{
		this(path, new int[0], null);
	}

	public VxTreeEvent(final VxTreePath path) 
	{
		this(path, new int[0], null);
	}

	public VxTreeEvent(final VxTreeNode[] path, final int[] childIndices, final VxTreeNode[] children) 
	{
		this(new VxTreePath(path), childIndices, children);
	}

	public VxTreeEvent(final VxTreePath path, final int[] childIndices, final VxTreeNode[] children) 
	{
		this.path = path;
		this.childIndices = childIndices;
		this.children = children;
	}

	public VxTreePath getTreePath() 
	{
		return path;
	}

	public VxTreeNode[] getPath() 
	{
		return path != null ? path.getPath() : null;
	}

	public VxTreeNode[] getChildren() 
	{
		return children != null ? children.clone() : null;
	}

	public int[] getChildIndices() 
	{
		return childIndices != null ? (int[]) childIndices.clone() : null;
	}
}
