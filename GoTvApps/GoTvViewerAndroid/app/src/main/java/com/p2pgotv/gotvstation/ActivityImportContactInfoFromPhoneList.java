//============================================================================
//Copyright (C) 2015 Brett R. Jones
//All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
//You may not modify or redistribute this code for any reason
//without written consent of Brett R. Jones
//
//This code is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//brett1900@usa.com
//http://www.gotvp2p.net
//============================================================================

package com.p2pgotv.gotvstation;
/*
import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

import android.content.ContentProviderOperation;

import android.content.OperationApplicationException;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.RemoteException;
import android.provider.ContactsContract;
import android.provider.ContactsContract.CommonDataKinds;
import android.provider.ContactsContract.CommonDataKinds.Phone;
import android.provider.ContactsContract.CommonDataKinds.Photo;
import android.provider.ContactsContract.CommonDataKinds.StructuredName;
import android.provider.ContactsContract.RawContacts;
import android.view.Menu;

import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;
*/

import android.view.View;
import android.view.View.OnClickListener;
import android.os.Bundle;
import android.content.Intent;
import android.widget.ListView;
import android.database.Cursor;
import android.content.ContentResolver;
import android.util.Log;

public class ActivityImportContactInfoFromPhoneList extends ActivityBase 
{
	private static final String 		LOG_TAG = "Contact Import:";
	private final int 			PICK_PHOTO 					= 1;
    ListView 					m_ContactsListView;
    PhoneContactsListAdapter 	m_ContactsAdapter 			= null;
    Cursor 						m_ContentCursor;
    ContentResolver 			m_ContentResolver;

    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_import_contact_info_from_phone_book);
        
	
        m_ContactsListView = (ListView) findViewById(R.id.lv_addcontact);
 	    Log.e(LOG_TAG, "lv_addcontacts" );

        //CustomAdapterAddContacts myad = new CustomAdapterAddContacts();
 	    m_ContactsAdapter = new PhoneContactsListAdapter( this );

	    Log.e(LOG_TAG, "setAdapter" );
	    m_ContactsListView.setAdapter( m_ContactsAdapter );
    }
    
    // Defining OnClick listener for the photo
    OnClickListener photoClickListener = new OnClickListener() 
    {	
		@Override
		public void onClick( View v ) 
		{
		    m_MyApp.playButtonClick();
			Intent intent = new Intent(Intent.ACTION_PICK);
			intent.setType("image/*");
			startActivityForResult(intent, PICK_PHOTO);
		}
	};

    /*
    class CustomAdapterAddContacts extends BaseAdapter 
    {
        @Override
        public int getCount() 
        {
            Log.e(LOG_TAG, "CustomAdapterAddContacts getCount " + m_ContentCursor.getCount() );
            return m_ContentCursor.getCount(); // c.getCount();
        }

        @Override
        public Object getItem(int position) 
        {
        	Log.e(LOG_TAG, "CustomAdapterAddContacts getItem " + position );
            return position;
        }

        @Override
        public long getItemId(int position) 
        {
        	Log.e(LOG_TAG, "CustomAdapterAddContacts getItemId " + position );        	
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) 
        {
        	Log.e(LOG_TAG, "CustomAdapterAddContacts getView position " + position );  
            ContactViewHolder contactViewHolder;

            if (convertView == null) 
            {

            	Log.e(LOG_TAG, "getView inflate" );
                // Inflate the layout
                LayoutInflater li = getLayoutInflater();
                convertView = li.inflate(
                        R.layout.contact_add_list_item, null);

            	Log.e(LOG_TAG, "new ContactViewHolder" );
                contactViewHolder = new ContactViewHolder();

                contactViewHolder.imgContact = (ImageView) convertView
                        .findViewById(R.id.imgView_addcontact);
                contactViewHolder.txtViewContactName = (TextView) convertView
                        .findViewById(R.id.txtView_addcontact_contactname);
                contactViewHolder.txtViewPhoneNumber = (TextView) convertView
                        .findViewById(R.id.txtview_addcontact_phonenumber);
                contactViewHolder.chbkAddContact = (CheckBox) convertView.findViewById(R.id.chbk_addcontact);

            	Log.e(LOG_TAG, "setTag" );
                convertView.setTag(contactViewHolder);
            } 
            else 
            {
                contactViewHolder = (ContactViewHolder) convertView.getTag();
            }

           	Log.e(LOG_TAG, "moveToPosition " + position );
           	m_ContentCursor.moveToPosition(position);

            // Add Contact Name //
            String name = m_ContentCursor
                    .getString(m_ContentCursor
                            .getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME));

           	if (name != null)
           	{
                contactViewHolder.txtViewContactName.setText(name);
          	    Log.e(LOG_TAG, "position " + position + " name " + name );
           	}
          	else
          	{
                contactViewHolder.txtViewContactName.setText("Unknown");
          	}

            // Add Phone Number //
            String phoneNumber = m_ContentCursor
                    .getString(m_ContentCursor
                            .getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));
           	Log.e(LOG_TAG, "position " + position + " phoneNumber " + phoneNumber );
            if (phoneNumber != null)
                contactViewHolder.txtViewPhoneNumber.setText(phoneNumber);
            else
                contactViewHolder.txtViewPhoneNumber.setText("Unknown");

           	Log.e(LOG_TAG, "get Photo from phone num " );
           	String contactId = fetchContactIdFromPhoneNumber(phoneNumber);
Z
                Uri uri = getPhotoUri( Long.parseLong( contactId ) );

                if (uri != null) 
                {
                   	Log.e(LOG_TAG, "setImageURI " + uri );
                   	contactViewHolder.imgContact.setImageURI(uri);
                } 
                else 
                {
                   	Log.e(LOG_TAG, "getPhotoUri = null " );
                   	contactViewHolder.imgContact
                            .setImageResource(R.drawable.ic_add_contact_grey);
                }        		
           	}
            else 
            {
               	Log.e(LOG_TAG, "getPhotoUri = no contact id" );
               	contactViewHolder.imgContact
                        .setImageResource(R.drawable.ic_add_contact_grey);
            }        		

            return convertView;
        }

        private String fetchContactIdFromPhoneNumber(String phoneNumber) 
        {
            String contactId = "";
           	if( ( null == phoneNumber )
           		|| ( 0 == phoneNumber.length() ) )
           	{
               	Log.e(LOG_TAG, "fetchContactIdFromPhoneNumber No Phone Number" );
         		return contactId;
           	}

           	Uri uri = Uri.withAppendedPath(PhoneLookup.CONTENT_FILTER_URI,
                    Uri.encode(phoneNumber));
           	Log.e(LOG_TAG, "fetchContactIdFromPhoneNumber uri " + uri );
           	Cursor cFetch = getContentResolver().query(uri,
                    new String[] { PhoneLookup.DISPLAY_NAME, PhoneLookup._ID },
                    null, null, null);



           	Log.e(LOG_TAG, "cFetch.moveToFirst() " );
            if (cFetch.moveToFirst()) 
            {

                cFetch.moveToFirst();

                    contactId = cFetch.getString(cFetch
                            .getColumnIndex(PhoneLookup._ID));
            }

           	Log.e(LOG_TAG, "contactId " + contactId );
           	System.out.println(contactId);
            return contactId;       
        }

        public Uri getPhotoUri(long contactId) 
        {
           	Log.e(LOG_TAG, "getPhotoUri " );
            ContentResolver contentResolver = getContentResolver();
            try 
            {
                Cursor cursor = contentResolver
                        .query(ContactsContract.Data.CONTENT_URI,
                                null,
                                ContactsContract.Data.CONTACT_ID
                                        + "="
                                        + contactId
                                        + " AND "

                                        + ContactsContract.Data.MIMETYPE
                                        + "='"
                                        + ContactsContract.CommonDataKinds.Photo.CONTENT_ITEM_TYPE
                                        + "'", null, null);

                if (cursor != null) 
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
            Uri person = ContentUris.withAppendedId(
                    ContactsContract.Contacts.CONTENT_URI, contactId);
            return Uri.withAppendedPath(person,
                    ContactsContract.Contacts.Photo.CONTENT_DIRECTORY);
        }

        public class ContactViewHolder 
        {
            ImageView imgContact;
            TextView txtViewContactName;
            TextView txtViewPhoneNumber;
            CheckBox chbkAddContact;
        }
    }

    private void readContacts() 
    {
        m_ContentResolver = getContentResolver();
        m_ContentCursor = m_ContentResolver.query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
                null, null, null, null);
    }
    */

    @Override
    protected void onDestroy() 
    {
        super.onDestroy();
        if( m_ContentCursor != null ) 
        {
        	m_ContentCursor.close();
        }
    }
}

