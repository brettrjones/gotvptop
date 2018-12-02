//============================================================================
// Copyright (C) 2009 Brett R. Jones
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not modify or redistribute this code for any reason
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett1900@usa.com
// http://www.gotvp2p.net
//============================================================================

package com.p2pgotv.gotvstation;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.database.Cursor;
import android.net.Uri;
import android.provider.ContactsContract;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class PhoneContactsListAdapter extends BaseAdapter
{
	private static final String LOG_TAG = "ContactsAdapter:";
    Activity 					m_ParentActivity			= null;
    List<PhoneContactInfo> 		m_ContactList				= new ArrayList<PhoneContactInfo>();
    ContentResolver 			m_ContentResolver			= null;
    Cursor 						m_ContactsCursor			= null;
    
	Uri 						CONTACT_CONTENT_URI 		= ContactsContract.Contacts.CONTENT_URI;
	String 						CONTACT_ID 					= ContactsContract.Contacts._ID;
	String 						CONTACT_DISPLAY_NAME 		= ContactsContract.Contacts.DISPLAY_NAME;
	String 						CONTACT_HAS_PHONE_NUMBER 	= ContactsContract.Contacts.HAS_PHONE_NUMBER;
	
	Uri 						PHONE_CONTENT_URI 			= ContactsContract.CommonDataKinds.Phone.CONTENT_URI;
	String 						PHONE_CONTACT_ID 			= ContactsContract.CommonDataKinds.Phone.CONTACT_ID;
	String 						PHONE_NUMBER 				= ContactsContract.CommonDataKinds.Phone.NUMBER;
	
	Uri 						EMAIL_CONTENT_URI 			= ContactsContract.CommonDataKinds.Email.CONTENT_URI;
	String 						EMAIL_CONTACT_ID 			= ContactsContract.CommonDataKinds.Email.CONTACT_ID;
	String 						EMAIL_DATA 					= ContactsContract.CommonDataKinds.Email.DATA;


    public PhoneContactsListAdapter( Activity activity )
    {
    	m_ParentActivity 	= activity;
        m_ContentResolver 	= m_ParentActivity.getContentResolver();
        m_ContactsCursor 	= m_ContentResolver.query( CONTACT_CONTENT_URI, null, null, null, null );
        fillContactsList( m_ContactsCursor );
        m_ContactsCursor.close();
        m_ContactsCursor = null; 
    }

	@Override
	public int getCount() 
	{
		return m_ContactList.size();
	}

	@Override
	public Object getItem( int position ) 
	{
		/*
		if( ( 0 <= position ) 
			&&  ( m_ContactList.size() > position ) )
		{
			return m_ContactList.get( position );
		}

		return null;
		*/
		return position;
	}

	@Override
	public long getItemId( int position ) 
	{
		/*
		if( ( 0 <= position ) 
			&&  ( m_ContactList.size() > position ) )
		{
			return m_ContactList.get( position ).m_ContactId;
		}
		
		return 0;
		*/
		return position;
	}
	
    void fillContactsList( Cursor contactsCursor )
    {
		// Loop for every contact in the phone
		if( contactsCursor.getCount() > 0 ) 
		{		
			while( contactsCursor.moveToNext() ) 
			{			
				String contactId = contactsCursor.getString(contactsCursor.getColumnIndex( CONTACT_ID ));
				String displayName = contactsCursor.getString(contactsCursor.getColumnIndex( CONTACT_DISPLAY_NAME ));
				if( ( null == displayName )
					|| ( 0 == displayName.length() ) )
				{
					continue; // no display name
				}

				String phoneNumber = "";
				List<String> phoneNumList = new ArrayList<String>();
				// Query and loop for every phone number of the contact
				Cursor phoneCursor = m_ContentResolver.query( PHONE_CONTENT_URI, null, PHONE_CONTACT_ID + " = ?", new String[] { contactId }, null);			
				if( null != phoneCursor )
				{
					while( ( null != phoneCursor ) && phoneCursor.moveToNext() ) 
					{
						phoneNumber = phoneCursor.getString(phoneCursor.getColumnIndex( PHONE_NUMBER ));
						if( ( null == phoneNumber ) || ( 0 == phoneNumber.length() ) )
						{
							continue;
						}
						
						Log.d(LOG_TAG, " found phone num " + phoneNumber );						
						if( '#' == phoneNumber.charAt(0) )
						{
							Log.d( LOG_TAG, "Ignoring phone number begining with #" );
							continue;
						}
						
						if( '*' == phoneNumber.charAt(0) )
						{
							Log.d( LOG_TAG, "Ignoring phone number begining with *" );
							continue;
						}
						
						boolean isDuplicate = false;
						for( int i = 0; i < phoneNumList.size(); i++ )
						{
							if( phoneNumber.contentEquals( phoneNumList.get( i ) ) )
							{
								// ignore duplicate
								isDuplicate = true;
								break;
							}
						}

						if( false == isDuplicate )
						{
							phoneNumList.add( phoneNumber );
						}
					}
					
					phoneCursor.close();						
				}

				if( 0 == phoneNumList.size() )
				{
					Log.d( LOG_TAG, "Skipping " + displayName + " because no valid phone number " );
					continue;
				}
				
				// we have enough for contact even if no email or photo
				PhoneContactInfo contactInfo 	= new PhoneContactInfo();
				contactInfo.m_ContactId 		= contactId;
				contactInfo.m_DisplayName		= displayName;
				for( int i = 0; i < phoneNumList.size(); i++ )
				{
					
					contactInfo.m_PhoneNumList.add( phoneNumList.get(i) );
				}

				// Query and loop for every email of the contact
				Cursor emailCursor = m_ContentResolver.query( EMAIL_CONTENT_URI, null, EMAIL_CONTACT_ID + " = ?", new String[] { contactId }, null);
				String emailAddr = "";
				while (emailCursor.moveToNext()) 
				{
					emailAddr = emailCursor.getString( emailCursor.getColumnIndex( EMAIL_DATA ) );	
					if( ( null == emailAddr ) || ( 0 == emailAddr.length() ) )
					{
						continue;
					}
	
					boolean isDuplicate = false;
					for( int i = 0; i <contactInfo.m_EmailAddress.size(); i++ )
					{
						if( emailAddr.contentEquals( contactInfo.m_EmailAddress.get( i ) ) )
						{
							// ignore duplicate
							isDuplicate = true;
							break;
						}
					}

					if( ! isDuplicate )
					{
						contactInfo.m_EmailAddress.add( emailAddr );
					}
				}

				emailCursor.close();
				
	           	if( ( null != contactId ) 
	               		&& ( 0 != contactId.length() ) )
	            {
	           		contactInfo.m_ContactPhotoUri = getContactPhotoUri( Long.parseLong(contactId) );
	            }
	           	
				m_ContactList.add( contactInfo );		
			}
		}
		else
		{
			Log.d( LOG_TAG, "No Contacts in list" );
		}
	}    
    
    public Uri getContactPhotoUri( long contactId ) 
    {
       	Log.e(LOG_TAG, "getPhotoUri " );
        try 
        {
            Cursor cursor = m_ContentResolver.query(ContactsContract.Data.CONTENT_URI,
                            						null,
                            						ContactsContract.Data.CONTACT_ID
				                                    + "="
				                                    + contactId
				                                    + " AND "
				
				                                    + ContactsContract.Data.MIMETYPE
				                                    + "='"
				                                    + ContactsContract.CommonDataKinds.Photo.CONTENT_ITEM_TYPE
				                                    + "'", null, null);

            if( cursor != null ) 
            {
                if (!cursor.moveToFirst()) 
                {
                   	Log.e(LOG_TAG, "getPhotoUri no photo" );
                    return null; // no photo
                }
            } 
            else 
            {
               	Log.e(LOG_TAG, "getPhotoUri error in cursor process" );
               return null; // error in cursor process
            }
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            return null;
        }

       	Log.e(LOG_TAG, "getPhotoUri withAppendedPath" );
        Uri person = ContentUris.withAppendedId( ContactsContract.Contacts.CONTENT_URI, contactId );
        return Uri.withAppendedPath( person, ContactsContract.Contacts.Photo.CONTENT_DIRECTORY );
    }

	@Override
	public android.view.View getView( int position, android.view.View convertView, ViewGroup parent ) 
	{
    	Log.e(LOG_TAG, "CustomAdapterAddContacts getView position " + position );  
        PhoneContactViewHolder contactViewHolder = null;
        if( convertView == null ) 
        {
        	Log.e(LOG_TAG, "getView inflate" );
            // Inflate the layout
            LayoutInflater li = m_ParentActivity.getLayoutInflater();
            convertView = li.inflate( R.layout.phone_contact_list_item, null );

        	Log.e(LOG_TAG, "new ContactViewHolder" );
            contactViewHolder = new PhoneContactViewHolder();

            contactViewHolder.m_ContactImageView = (ImageView) convertView
                    .findViewById(R.id.phone_contact_imageview);
            contactViewHolder.m_ContactNameTextView = (TextView) convertView
                    .findViewById(R.id.phone_contact_contactname_textview);
            contactViewHolder.m_ContactPhoneNumberTextView = (TextView) convertView
                    .findViewById(R.id.phone_contact_phonenumber_textview);
            contactViewHolder.m_ContactEmailTextView = (TextView) convertView
            		.findViewById(R.id.phone_contact_email_addr_textview);

        	Log.e(LOG_TAG, "setTag" );
            convertView.setTag(contactViewHolder);
        } 
        else 
        {
            contactViewHolder = (PhoneContactViewHolder) convertView.getTag();
        }
        
        if( ( null != contactViewHolder )
            	&& ( position < m_ContactList.size() ) )
            {
            	PhoneContactInfo contactInfo = m_ContactList.get( position );
            	if( null != contactInfo )
            	{
            		contactViewHolder.m_ContactNameTextView.setText( contactInfo.m_DisplayName );
            		String phoneNumber = contactInfo.getPhoneNumbers();
        	        if( null != phoneNumber )
        	        {
        	        	contactViewHolder.m_ContactPhoneNumberTextView.setText(phoneNumber);
        	        }
        	        else
        	        {
        	        	contactViewHolder.m_ContactPhoneNumberTextView.setText("Unknown");
        	        }
        	        
        	        contactViewHolder.m_ContactEmailTextView.setText( contactInfo.getEmailAddresses() );
     
    				Uri photoUri = contactInfo.m_ContactPhotoUri;
    				if( null != photoUri ) 
    				{
    				   	Log.e(LOG_TAG, "setImageURI " + photoUri );
    				   	contactViewHolder.m_ContactImageView.setImageURI( photoUri );
    				   	if( null == contactViewHolder.m_ContactImageView.getDrawable() )
    				   	{
    				   		// photo uri is invalid
    		              	contactViewHolder.m_ContactImageView.setImageResource(R.drawable.ic_add_contact_grey);
    		              	contactInfo.m_ContactPhotoUri = null;
    				   	}
    				} 
    				else
    				{
    	              	contactViewHolder.m_ContactImageView.setImageResource(R.drawable.ic_add_contact_grey);					
    				}
            	}
            	else
            	{
                   	Log.e(LOG_TAG, " getView position " + position + " has null contact info" );          		
            	}  	
            }
            else
            {
               	Log.e(LOG_TAG, " getView " + position + " unavailable position" );      	
            }

        return convertView;
	}
}