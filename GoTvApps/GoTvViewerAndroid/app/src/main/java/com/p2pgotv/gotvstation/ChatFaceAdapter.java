// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )
package com.p2pgotv.gotvstation;

import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;

public class ChatFaceAdapter extends BaseAdapter 
{
	private Context 		m_ChatFaceContext;
    private List<String> 	m_ChatFaceList;
    private LayoutInflater 	m_ChatFaceInflater;
    private int 			m_ChatFaceImageCount = 0;

    //========================================================================
    public ChatFaceAdapter(Context context, List<String> list) 
    {
    	this.m_ChatFaceContext 		= context;
        this.m_ChatFaceInflater 	= LayoutInflater.from(context);
        this.m_ChatFaceList			= list;
        this.m_ChatFaceImageCount 	= list.size();
    }

    //========================================================================
    @Override
    public int getCount() 
    {
        return this.m_ChatFaceImageCount;
    }

    //========================================================================
    @Override
    public Object getItem(int position) 
    {
        return m_ChatFaceList.get(position);
    }

    //========================================================================
    @Override
    public long getItemId(int position) 
    {
        return position;
    }

    //========================================================================
    @Override
    public View getView( int position, View convertView, ViewGroup parent ) 
    {
        String emoji = m_ChatFaceList.get(position);
        ViewHolder viewHolder = null;
        if( convertView == null ) 
        {
            viewHolder			= new ViewHolder();
            convertView			= m_ChatFaceInflater.inflate( R.layout.chat_face_item, null );
            viewHolder.bigFace	= (ImageView) convertView.findViewById( R.id.itemImage );
            convertView.setTag(viewHolder);
        } 
        else 
        {
            viewHolder = (ViewHolder)convertView.getTag();
        }
        
//        if(emoji.getId() == R.drawable.face_del_icon) {
//            convertView.setBackgroundDrawable(null);
//            viewHolder.bigFace.setImageResource(emoji.getId());
//        } else if(TextUtils.isEmpty(emoji.getCharacter())) {
//            convertView.setBackgroundDrawable(null);
//            viewHolder.bigFace.setImageDrawable(null);
//        } else {
//            viewHolder.bigFace.setTag(emoji);
//            viewHolder.bigFace.setImageResource(emoji.getId());
//        }
        
        
        int id = m_ChatFaceContext.getResources().getIdentifier(emoji, "drawable", m_ChatFaceContext.getPackageName());
        viewHolder.bigFace.setImageResource(id);

        return convertView;
    }

    //========================================================================
    class ViewHolder 
    {
        public ImageView bigFace;
    }
}