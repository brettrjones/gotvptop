// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )

package com.p2pgotv.gotvstation;

import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class ChatFunctionAdapter extends BaseAdapter 
{
	private List<ChatOption> data;

	private LayoutInflater inflater;

	private int size = 0;

	public ChatFunctionAdapter(Context context, List<ChatOption> list) 
	{
		this.inflater = LayoutInflater.from(context);
		this.data = list;
		this.size = list.size();
	}

	@Override
	public int getCount() 
	{
		return this.size;
	}

	@Override
	public Object getItem(int position) 
	{
		return data.get(position);
	}

	@Override
	public long getItemId(int position) 
	{
		return position;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) 
	{
		ChatOption option = data.get(position);
		ChatViewHolder viewHolder = null;
		if (convertView == null) 
		{
			viewHolder = new ChatViewHolder();
			convertView = inflater.inflate(R.layout.chat_function_item, null);
			viewHolder.iconImageView 	= (ImageView) convertView.findViewById(R.id.iconImageView);
			viewHolder.nameTextView 	= (TextView) convertView.findViewById(R.id.nameTextView);
			convertView.setTag(viewHolder);
		} 
		else 
		{
			viewHolder = (ChatViewHolder) convertView.getTag();
		}
		
		viewHolder.iconImageView.setImageDrawable(option.getIconDrawable());
		viewHolder.nameTextView.setText(option.getName());
		return convertView;
	}

	class ChatViewHolder 
	{

		public ImageView 	iconImageView;
		public TextView 	nameTextView;
	}
}