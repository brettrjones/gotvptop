package com.p2pgotv.gotvstation;

import java.util.*;

public abstract class VxBaseMutableTreeNode implements VxMutableTreeNode 
{
	protected VxMutableTreeNode parent;
	protected List<VxTreeNode> children;
	protected transient Object userObject;
	private boolean expanded;
	
	public VxBaseMutableTreeNode() 
	{
		this(null);
	}

	public VxBaseMutableTreeNode(final Object userObject) 
	{
		setUserObject(userObject);
	}

	@Override public void insert(final VxMutableTreeNode child, final int childIndex) 
	{
		if (child == null || isNodeAncestor(child)) 
		{
			throw new IllegalArgumentException("invalid child to insert"); //$NON-NLS-1$
		}

		if (child.getParent() instanceof VxMutableTreeNode) 
		{
			child.<VxMutableTreeNode> getParent().remove(child);
		}
		
		child.setParent(this);
		getChildren().add(childIndex, child);
	}

	@Override public void remove(final int childIndex) 
	{
		VxMutableTreeNode child = (VxMutableTreeNode) getChildren().remove(childIndex);
		child.setParent(null);
	}

	@Override public void setParent(final VxMutableTreeNode parent) 
	{
		this.parent = parent;
	}

	@SuppressWarnings("unchecked") @Override public <T extends VxTreeNode> T getParent() 
	{
		return (T) parent;
	}

	@SuppressWarnings("unchecked") @Override public <T extends VxTreeNode> T getChildAt(final int index) 
	{
		return (T) getChildren().get(index);
	}

	@Override public int getChildCount() 
	{
		return children != null ? children.size() : 0;
	}

	@Override public int getIndex(final VxTreeNode child) 
	{
		return children != null ? children.indexOf(child) : -1;
	}

	public List<VxTreeNode> children() 
	{
		return children;
	}

	@Override public void setUserObject(final Object userObject) 
	{
		this.userObject = userObject;
	}

	@SuppressWarnings("unchecked") @Override public <T> T getUserObject() 
	{
		return (T) userObject;
	}

	@Override public void removeFromParent() 
	{
		if (parent != null) 
		{
			parent.remove(this);
		}
	}

	@Override public void remove(final VxMutableTreeNode child) 
	{
		int index = -1;
		if (child == null || children == null || (index = children.indexOf(child)) == -1) 
		{
			throw new IllegalArgumentException("child null or not found"); //$NON-NLS-1$
		}
		
		remove(index);
	}

	public void removeAllChildren() 
	{
		if (children == null) 
		{
			return;
		}
		
		for (Iterator<VxTreeNode> it = children.iterator(); it.hasNext();) 
		{
			VxMutableTreeNode child = (VxMutableTreeNode) it.next();
			child.setParent(null);
			it.remove();
		}
	}

	public void add(final VxMutableTreeNode child) 
	{
		insert(child, getChildCount() - (isNodeChild(child) ? 1 : 0));
	}

	public boolean isNodeAncestor(final VxTreeNode anotherNode) 
	{
		if (anotherNode == null) 
		{
			return false;
		}
		
		VxTreeNode currentParent = this;
		while (currentParent != null) 
		{
			if (currentParent == anotherNode) 
			{
				return true;
			}
			
			currentParent = currentParent.getParent();
		}

		return false;
	}

	public boolean isNodeDescendant(final VxBaseMutableTreeNode anotherNode) 
	{
		return anotherNode != null ? anotherNode.isNodeAncestor(this) : false;
	}

	public VxTreeNode getSharedAncestor(final VxBaseMutableTreeNode anotherNode) 
	{
		VxTreeNode currentParent = anotherNode;
		while (currentParent != null) 
		{
			if (isNodeAncestor(currentParent)) 
			{
				return currentParent;
			}

			currentParent = currentParent.getParent();
		}

		return null;
	}

	public boolean isNodeRelated(final VxBaseMutableTreeNode node) 
	{
		return getSharedAncestor(node) != null;
	}

	@Override public int getDepth() 
	{
		if (children == null || children.size() == 0) 
		{
			return 0;
		}
		
		int childrenDepth = 0;
		for (Iterator<VxTreeNode> it = children.iterator(); it.hasNext();) 
		{
			VxTreeNode child = it.next();
			int childDepth = child.getDepth();
			if (childDepth > childrenDepth) 
			{
				childrenDepth = childDepth;
			}
		}
		
		return childrenDepth + 1;
	}

	@Override public int getLevel() 
	{
		int result = 0;
		VxTreeNode currentParent = getParent();
		while (currentParent != null) 
		{
			currentParent = currentParent.getParent();
			result++;
		}

		return result;
	}

	public VxTreeNode[] getPath() 
	{
		return getPathToRoot(this, 0);
	}

	public Object[] getUserObjectPath() 
	{
		VxTreeNode[] path = getPath();
		Object[] result = new Object[path.length];
		for (int i = 0; i < path.length; i++) 
		{
			result[i] = ((VxBaseMutableTreeNode) path[i]).getUserObject();
		}

		return result;
	}

	public VxTreeNode getRoot() 
	{
		VxTreeNode currentNode = this;
		while (currentNode.getParent() != null) 
		{
			currentNode = currentNode.getParent();
		}

		return currentNode;
	}

	public boolean isRoot() 
	{
		return getParent() == null;
	}

	public boolean isNodeChild(final VxTreeNode child) 
	{
		return child != null && children != null ? children.contains(child) : false;
	}

	@Override public boolean isLeaf() 
	{
		return children == null || children.isEmpty();
	}

	@Override public String toString() 
	{
		return getUserObject() != null ? getUserObject().toString() : null;
	}

	protected VxTreeNode[] getPathToRoot(final VxTreeNode node, final int depth) 
	{
		if (node == null) 
		{
			return new VxTreeNode[depth];
		}
		
		VxTreeNode[] result = getPathToRoot(node.getParent(), depth + 1);
		result[result.length - 1 - depth] = node;

		return result;
	}

	private List<VxTreeNode> getChildren() 
	{
		if (children == null) 
		{
			children = new ArrayList<VxTreeNode>();
		}

		return children;
	}

	// including me
	@Override public int getRowCount() 
	{
		if (!expanded) 
		{
			return 1;
		}
		
		int res = 1;
		for (VxTreeNode node: getChildren()) 
		{
			res += node.getRowCount();
		}
		
		return res;
	}

	@Override public boolean getExpanded() 
	{
		return expanded;
	}

	@Override public void setExpanded(boolean expanded) 
	{
		this.expanded = expanded;
	}
}
