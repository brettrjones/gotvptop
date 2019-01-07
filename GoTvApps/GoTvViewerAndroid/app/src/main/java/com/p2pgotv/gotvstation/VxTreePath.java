package com.p2pgotv.gotvstation;

import java.io.*;

public class VxTreePath implements Serializable 
{
    private VxTreeNode[] elements;
    private VxTreePath parent;
    private final int pathCount;

    public VxTreePath(final VxTreeNode[] path) 
    {
        pathCount = path.length;
        elements = new VxTreeNode[pathCount];
        System.arraycopy(path, 0, elements, 0, pathCount);
        parent = null;
    }

    public VxTreePath(final VxTreeNode singlePath) 
    {
        elements = new VxTreeNode[] {singlePath};
        pathCount = 1;
        parent = null;
    }

    protected VxTreePath() 
    {
        elements = new VxTreeNode[] {null};
        pathCount = 1;
        parent = null;
    }

    protected VxTreePath(final VxTreeNode[] path, final int length) 
    {
        pathCount = length;
        elements = new VxTreeNode[pathCount];
        System.arraycopy(path, 0, elements, 0, pathCount);
        parent = null;
    }

    protected VxTreePath(final VxTreePath parentPath, final VxTreeNode lastElement) 
    {
        elements = new VxTreeNode[] {lastElement};
        parent = parentPath;
        pathCount = (parent != null) ? parent.getPathCount() + 1 : 1;
    }

    @Override public boolean equals(final Object o) 
    {
        if (!(o instanceof VxTreePath)) 
        {
            return false;
        }

        VxTreePath path = (VxTreePath)o;
        final int numPathComponents = getPathCount();
        if (path.getPathCount() != numPathComponents) 
        {
            return false;
        }

        for (int i = 0; i < numPathComponents; i++) 
        {
            if (!path.getPathComponent(i).equals(getPathComponent(i))) 
            {
                return false;
            }
        }

        return true;
    }

    public VxTreeNode getLastPathComponent() 
    {
        return elements[elements.length - 1];
    }

    public VxTreePath getParentPath() 
    {
        if (parent != null) 
        {
            return parent;
        }

        int numParentPaths = getPathCount() - 1;
        if (numParentPaths <= 0) 
        {
            return null;
        }

        return new VxTreePath(getPath(), numParentPaths);
    }

    public VxTreeNode[] getPath() 
    {
        if (parent == null) 
        {
            return elements;
        }

        VxTreeNode[] parentPath = parent.getPath();
        VxTreeNode[] result = new VxTreeNode[parentPath.length + 1];
        System.arraycopy(parentPath, 0, result, 0, parentPath.length);
        result[result.length - 1] = getLastPathComponent();

        elements = result.clone();
        parent = null;
        return result;
    }

    public VxTreeNode getPathComponent(final int element) 
    {
        final int pathCount = getPathCount();
        if (element < 0 || element >= pathCount) 
        {
            throw new IllegalArgumentException("element index out of bounds"); //$NON-NLS-1$
        }
        
        if (parent == null) 
        {
            return elements[element];
        }

        return (element < pathCount - 1) ? parent.getPathComponent(element) :
                                           getLastPathComponent();
    }

    public int getPathCount() {
        return pathCount;
    }

    public boolean isDescendant(final VxTreePath child) 
    {
        if (child == null) 
        {
            return false;
        }

        final int numPathComponents = getPathCount();
        if (child.getPathCount() < numPathComponents) 
        {
            return false;
        }

        for (int i = 0; i < numPathComponents; i++) 
        {
            if (!child.getPathComponent(i).equals(getPathComponent(i))) 
            {
                return false;
            }
        }

        return true;
    }

    public VxTreePath pathByAddingChild(final VxTreeNode child) 
    {
        return new VxTreePath(this, child);
    }

    @Override public int hashCode() 
    {
        return getLastPathComponent().hashCode();
    }

    @Override public String toString() 
    {
        String result = null;
        final int numPathComponents = getPathCount();
        for (int i = 0; i < numPathComponents; i++) {
            if (result != null) {
                result += ", ";
            } else {
                result = "";
            }
            result += getPathComponent(i);
        }
        return "[" + result + "]";
    }
}
