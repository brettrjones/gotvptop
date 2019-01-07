package com.p2pgotv.gotvstation;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.Toast;

import com.p2pgotv.gotvstation.rteditor.RTEditText;
import com.p2pgotv.gotvstation.rteditor.api.format.RTFormat;

public class VxHtmlEditor extends RTEditText
{
	public static final String 	LOG_TAG 				= "VxHtmlEditor:";
	private String 				m_HtmlFileName			= "";
	private Context 			m_Context				= null;

    //============================================================================
    public VxHtmlEditor(Context context) 
    {
        super(context);
        m_Context = context;
    }

    //============================================================================
    public VxHtmlEditor(Context context, AttributeSet attrs) 
    {
        super(context, attrs);
        m_Context = context;
     }

    //============================================================================
    public VxHtmlEditor(Context context, AttributeSet attrs, int defStyle) 
    {
        super(context, attrs, defStyle);
        m_Context = context;
    }

    //============================================================================
    public void initVxHtmlEditor( String rootPath, String htmlFile ) 
    {
    	if( null != rootPath )
    	{
    		setRootPath( rootPath );
    	}
    	
    	if( null != htmlFile )
    	{
        	m_HtmlFileName = htmlFile;   		
    	}
    }

    
	//========================================================================
    @Override
	public void onSaveContentToFile()
    {
    	saveToFile();
    }
	
	//========================================================================
	public void loadFromFile() 
	{
		if( m_HtmlFileName.isEmpty() )
		{
			return;
		}
		
		String htmlContent = VxFileUtil.readTextFile( m_HtmlFileName, false );
		if( ( null == htmlContent ) || htmlContent.isEmpty() )
		{
			htmlContent = "";
		}
		
		setRichTextEditing( getRootPath(), true, htmlContent );
	}
	
	//========================================================================
	public boolean saveToFile() 
	{
		if( m_HtmlFileName.isEmpty() )
		{
			return false;
		}
		//BRJ temp till can spend more time on this.. it is in rich text format without html markup.. add wrappings
		String strHdr = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" name=\"description\" content=\"My P2P Web :: Storyboard Web Page - Share your story in your storyboard web page served by your own device\"></head><body bgcolor=\"#F0E2B4\">";
		String strFooter = "</body></html>\r\n\r\n";
		String strBody = getText( RTFormat.HTML );
		
		strBody = strBody.replace( "&amp;#0;", "" );

		
		if( null == VxFileUtil.writeTextFile( m_Context, m_HtmlFileName,  strHdr + strBody + strFooter ) )
		{
			String toastMsg = m_Context.getString( R.string.save_as_failure, m_HtmlFileName );
			Toast.makeText( m_Context, toastMsg, Toast.LENGTH_LONG ).show();	
			return false;
		}
		else
		{
			String toastMsg = m_Context.getString( R.string.save_as_success, m_HtmlFileName );
			Toast.makeText( m_Context, toastMsg, Toast.LENGTH_LONG ).show();
			return true;
		}
	}
}
