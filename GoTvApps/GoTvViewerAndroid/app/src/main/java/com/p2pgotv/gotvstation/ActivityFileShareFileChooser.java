package com.p2pgotv.gotvstation;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;

import java.util.ArrayList;
import java.util.List;

import com.p2pgotv.gotvstation.VxFileChooserActivity;
import com.p2pgotv.gotvstation.VxFileChooserConfig;
import com.p2pgotv.gotvstation.VxFileChooserConfig.Mode;
import com.p2pgotv.gotvstation.VxFolderChooserActivity;
import com.p2pgotv.gotvstation.VxFolderChooserConfig;
import com.p2pgotv.gotvstation.VxFolderChooserResult;

public class ActivityFileShareFileChooser extends Activity 
{
	private static final int REQCODE_showFileChooser = 1;
	private static final int REQCODE_showFolderChooser = 2;

	//============================================================================
	@Override 
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_file_share_file_chooser);
	}

	//============================================================================
	public void bShowFileChooser_click(View v) 
	{
		EditText tInitialDir = (EditText) findViewById(R.id.tInitialDir);
		EditText tTitle = (EditText) findViewById(R.id.tTitle);
		EditText tSubtitle = (EditText) findViewById(R.id.tSubtitle);
		EditText tPattern = (EditText) findViewById(R.id.tPattern);

		VxFileChooserConfig config = new VxFileChooserConfig();
		config.mode = Mode.Open;
		config.initialDir = tInitialDir.length() == 0 ? null : tInitialDir.getText().toString();
		config.title = tTitle.length() == 0 ? null : tTitle.getText().toString();
		config.subtitle = tSubtitle.length() == 0 ? null : tSubtitle.getText().toString();
		config.pattern = tPattern.length() == 0 ? null : tPattern.getText().toString();

		startActivityForResult(VxFileChooserActivity.createIntent(getApplicationContext(), config), REQCODE_showFileChooser);
	}

	//============================================================================
	public void bShowFolderChooser_click(View v) 
	{
		EditText tInitialDir = (EditText) findViewById(R.id.tInitialDir);
		EditText tInitialDir2 = (EditText) findViewById(R.id.tInitialDir2);
		EditText tTitle = (EditText) findViewById(R.id.tTitle);
		EditText tSubtitle = (EditText) findViewById(R.id.tSubtitle);
		CheckBox cShowHidden = (CheckBox) findViewById(R.id.cShowHidden);
		CheckBox cMustBeWritable = (CheckBox) findViewById(R.id.cMustBeWritable);
		CheckBox cExpandSingle = (CheckBox) findViewById(R.id.cExpandSingle);
		CheckBox cExpandMultiple = (CheckBox) findViewById(R.id.cExpandMultiple);

		List<String> roots = new ArrayList<String>();
		if (tInitialDir.length() > 0) {
			roots.add(tInitialDir.getText().toString());
		}
		if (tInitialDir2.length() > 0) {
			roots.add(tInitialDir2.getText().toString());
		}
		
		VxFolderChooserConfig config = new VxFolderChooserConfig();
		config.roots = roots;
		config.showHidden = cShowHidden.isChecked();
		config.title = tTitle.length() == 0 ? null : tTitle.getText().toString();
		config.subtitle = tSubtitle.length() == 0 ? null : tSubtitle.getText().toString();
		config.mustBeWritable = cMustBeWritable.isChecked();
		config.expandSingularRoot = cExpandSingle.isChecked();
		config.expandMultipleRoots = cExpandMultiple.isChecked();

		startActivityForResult(VxFolderChooserActivity.createIntent(getApplicationContext(), config), REQCODE_showFolderChooser);
	}

	//============================================================================
	@Override 
	protected void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		if (requestCode == REQCODE_showFileChooser) 
		{
		}
		
		if (requestCode == REQCODE_showFolderChooser) 
		{
			if (resultCode == RESULT_OK) 
			{
				VxFolderChooserResult result = VxFolderChooserActivity.obtainResult(data);
				new AlertDialog.Builder(this)
				.setTitle("Result")
				.setMessage(result.selectedFolder)
				.show();
			}
		}
	}
}

