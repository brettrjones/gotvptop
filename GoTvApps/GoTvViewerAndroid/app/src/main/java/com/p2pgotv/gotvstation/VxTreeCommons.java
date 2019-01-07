package com.p2pgotv.gotvstation;

/**
 * Storage of the utility methods for tree-related calculations.
 * 
 */
public class VxTreeCommons 
{
	/**
	 * Returns tree path from the specified ancestor to a node.
	 * 
	 * @param node
	 *            TreeNode which is the path end
	 * @param ancestor
	 *            TreeNode which is the path top
	 * 
	 * @return path from an ancestor to a node
	 */
	public static VxTreeNode[] getPathToAncestor(final VxTreeNode node, final VxTreeNode ancestor) 
	{
		return getPathToAncestor(node, ancestor, 0);
	}

	/**
	 * Returns tree path from the specified ancestor to a node limited by the depth.
	 * 
	 * @param node
	 *            TreeNode which is the path end
	 * @param ancestor
	 *            TreeNode which is the path top
	 * @param depth
	 *            int value representing the maximum path length
	 * 
	 * @return path from an ancestor to a node
	 */
	public static VxTreeNode[] getPathToAncestor(final VxTreeNode node, final VxTreeNode ancestor, final int depth) 
	{
		if (node == null) 
		{
			return new VxTreeNode[depth];
		}

		if( node == ancestor ) 
		{
			VxTreeNode[] result = new VxTreeNode[depth + 1];
			result[0] = ancestor;
			return result;
		}

		VxTreeNode[] result = getPathToAncestor(node.getParent(), ancestor, depth + 1);
		result[result.length - depth - 1] = node;
		return result;
	}
}
