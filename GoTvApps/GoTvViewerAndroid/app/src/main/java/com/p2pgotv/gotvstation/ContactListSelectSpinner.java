package com.p2pgotv.gotvstation;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;

public class ContactListSelectSpinner extends Activity 
{	
	String[] m_ContactViewTypeText =  {"List Everybody Except Ignored", "List Friends And Guests", "List Anonymous Contacts", 
			"List Administrators", "List People I Ignore", "List My Prefered Relays", "List All Possible Relays"};
	int[] m_ContactViewTypeIcon =  {R.drawable.ic_guest, R.drawable.button_people_normal, R.drawable.ic_unknown, 
			R.drawable.button_administrator_normal, R.drawable.ic_ignore, R.drawable.button_proxy_normal, R.drawable.button_proxy_normal};
	
	//========================================================================
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        Spinner mySpinner = (Spinner)findViewById(R.id.contact_list_select_spinner);
        mySpinner.setAdapter(new SelectContactsCustomAdapter(ContactListSelectSpinner.this, R.layout.custom_spinner_row, m_ContactViewTypeText)); 
    }
    
    public class SelectContactsCustomAdapter extends ArrayAdapter<String>
    {
    	//========================================================================
		public SelectContactsCustomAdapter(Context context, int textViewResourceId, String[] objects) 
		{
			super(context, textViewResourceId, objects);
			// TODO Auto-generated constructor stub
		}

		//========================================================================
		@Override
		public View getDropDownView(int position, View convertView, ViewGroup parent) 
		{
			// TODO Auto-generated method stub
			return getCustomView(position, convertView, parent);
		}

		//========================================================================
		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			// TODO Auto-generated method stub
			return getCustomView(position, convertView, parent);
		}

		//========================================================================
		public View getCustomView(int position, View convertView, ViewGroup parent) 
		{
			// TODO Auto-generated method stub
			//return super.getView(position, convertView, parent);

			LayoutInflater inflater=getLayoutInflater();
			View row=inflater.inflate(R.layout.custom_spinner_row, parent, false);
			TextView label=(TextView)row.findViewById( R.id.custom_spinner_text_view );
			label.setText(m_ContactViewTypeText[position]);
			
			ImageView icon = (ImageView)row.findViewById(R.id.custom_spinner_icon);
			icon.setImageResource( m_ContactViewTypeIcon[position] );
			
			return row;
		}	
    }
}
